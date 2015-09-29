/**
 *
 *  2015/6/6
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDGridTransform.h"
#include "LDAffineTransform.h"
#include "PointUtil.h"

namespace live2d
{

//理論上巨大な格子でも問題無いはずだが、アプリケーションで利用する範囲は限られている。
//限定された範囲で使われているかをチェックしたいときには下記のdefineを有効にする
#define SAFE_CHK
#ifdef SAFE_CHK
#define MAYBE_MAX_ROW 1000
#define MAYBE_MAX_COL 1000
#endif //SAFE_CHK


LDGridTransform::LDGridTransform( float x,float y, float width, float height,int row,int col )
{
	Q_ASSERT( width>0 );
	Q_ASSERT( height>0 );
	Q_ASSERT( row>0 );
	Q_ASSERT( col>0 );

	m_originRect.setTopLeft( QPointF( x,y ) );
	m_originRect.setBottomRight( QPointF( x+width,y+height ) );
	for ( int i = 0; i < row+1; ++i )
	{
		m_gridPoints.push_back( QList<LDPoint>() );
		for ( int j = 0; j < col+1; ++j )
		{
			m_gridPoints[i].push_back( LDPoint( x+width/col*j,y+height/row*i ) );
		}
	}
	extendRate = 100;
	clearBoundsCache();
}

LDGridTransform::LDGridTransform( const LDPoint& topLeft, const LDPoint& bottomRight, int row, int col )
	:LDGridTransform( topLeft.x(),topLeft.y(),bottomRight.x()-topLeft.x(),bottomRight.y()-topLeft.y(),row,col )
{

}

LDGridTransform::LDGridTransform( const LDQuadTransform& quad, int row, int col )
	:LDGridTransform( quad.getTopLeft(),quad.getTopRight(),quad.getBottomRight(),quad.getBottomLeft(),row,col )
{

}

LDGridTransform::LDGridTransform( const LDPoint& topLeft, const LDPoint& topRight, const LDPoint& bottomRight, const LDPoint& bottomLeft, int row, int col )
{
	m_originRect=math::PointUtil::getBoundingRect( {topLeft,topRight,bottomLeft,bottomRight} );

	LDQuadTransform quad( topLeft,topRight,bottomRight,bottomLeft );

	for ( int i = 0; i < row+1; ++i )
	{
		m_gridPoints.push_back( QList<LDPoint>() );
		for ( int j = 0; j < col+1; ++j )
		{
			m_gridPoints[i].push_back( quad.transform( ( float )j/col,( float )i/row ) );
		}
	}
	extendRate = 100;
	clearBoundsCache();
}

int LDGridTransform::getRow()const
{
#ifdef SAFE_CHK
	Q_ASSERT( m_gridPoints.length()-1<MAYBE_MAX_ROW );
#endif //SAFE_CHK
	return m_gridPoints.length()-1;
}

int LDGridTransform::getColumn()const
{
	if ( m_gridPoints.length()==0 )
	{
		return 0;
	}
#ifdef SAFE_CHK
	Q_ASSERT( m_gridPoints[0].length()-1<MAYBE_MAX_COL );
#endif //SAFE_CHK
	return m_gridPoints[0].length()-1;
}

int LDGridTransform::getRowArrayLength() const
{
#ifdef SAFE_CHK
	Q_ASSERT( m_gridPoints.length()<MAYBE_MAX_ROW+1 );
#endif //SAFE_CHK
	return m_gridPoints.length();
}

int LDGridTransform::getColumnArrayLength() const
{
	if ( m_gridPoints.length()==0 )
	{
		return 0;
	}
#ifdef SAFE_CHK
	Q_ASSERT( m_gridPoints[0].length()<MAYBE_MAX_COL+1 );
#endif //SAFE_CHK
	return m_gridPoints[0].length();
}

LDPoint LDGridTransform::transform( const LDUvPoint& t,bool clip )const
{
#ifdef SAFE_CHK
	Q_ASSERT( t.x()<MAYBE_MAX_COL );
	Q_ASSERT( t.y()<MAYBE_MAX_ROW );
#endif //SAFE_CHK
	if ( getColumn()==0 && getRow()==0 )
	{
		//メッシュがない場合はそのままの値を返す
		return t;
	}

	double tx=t.x();
	double ty=t.y();

	if ( clip )
	{
		//Grid内にClipする。QuadをClipして変換するのではない
		tx=LDMathUtil::clamp( tx,0.0,1.0 );
		ty=LDMathUtil::clamp( ty,0.0,1.0 );
	}

	//Gridから対象のQuadを見つける
	auto clipedST=LDUvPoint( tx,ty );
	auto quad=getQuadTransformFromGridCoord( clipedST );

	auto local=getLocalPoint( clipedST );

	return quad.transform( local );

}

LDPointList LDGridTransform::transform( const LDUvPointList& points,bool clip ) const
{
	LDPointList result;
	int length = points.length() ;

	for ( int i = 0 ; i < length ; i ++ )
	{
		result.push_back( transform( points[i],clip ) );
	}
	return result;
}

LDUvPoint LDGridTransform::tryInverseTransform( const LDPoint& pt, bool& success, bool clip ) const
{
	if ( getColumn()==0 && getRow()==0 )
	{
		//メッシュがない場合はそのままの値を返す
		return pt;
	}

	//Gridからマッピング先のQuadを見つける
	bool chk=false;
	LDTableIndex index;
	auto quad=getQuadTransformFromMapCoord( pt,chk,index,clip );

	if ( ! chk )
	{
		success=false;
		return LDUvPoint();
	}
	else
	{
		success=true;
	}
	LDPoint quadLocal;

	int col = index.x() ;
	int row = index.y() ;

	if ( isOutside( row,col ) )
	{
		//		return quad.inverseTransform( pt,clip );
		//		LDPoint tmp=pt;
		//		if(row>=getRow())tmp.setX(tmp.x()+1);
		//		if(col>=getColumn())tmp.setY(tmp.y()+1);
		quadLocal= quad.inverseTransform( pt,success,clip );

		if(quad.isOutsideLocal(quadLocal))
		{
			//TODO 動かしすぎると正常に計算できない。範囲に収まるはずが大きな値になっている。なにかおかしい?
			success=false;
			return LDUvPoint();
		}
		LDUvPoint internal;
		if ( col<0 )
		{
			//グリッド座標でマイナスのときはそのままマイナス座標を使う
			internal.setX( col+quadLocal.x() );
		}
		else if ( col<getColumn() )
		{
			//範囲内のときは四角形の座標からグリッド座標へ変換
			internal.setX( ( float )( col +quadLocal.x() )/getColumn() );
		}
		else
		{
			//+側にはみ出しているときははみ出した分だけ加算
			internal.setX( col-( getColumn()-1 )+quadLocal.x() );
		}

		if ( row<0 )
		{
			internal.setY( row+quadLocal.y() );
		}
		else if ( row<getRow() )
		{
			internal.setY( ( float )( row +quadLocal.y() )/getRow() );
		}
		else
		{
			internal.setY( row-( getRow()-1 )+quadLocal.y() );

		}
		//		internal.setX( col*( 1.0f/getColumn() )+local.x()/getColumn() );
		//		internal.setY( row*( 1.0f/getRow() )+local.y()/getRow() );
#ifdef SAFE_CHK
	Q_ASSERT( internal.x()<MAYBE_MAX_COL );
	Q_ASSERT( internal.y()<MAYBE_MAX_ROW );
#endif //SAFE_CHK
		return internal;
	}
	else
	{
		quadLocal= quad.inverseTransform( pt,success,clip );

		LDUvPoint internal;
		internal.setX( col*( 1.0f/getColumn() )+quadLocal.x()/getColumn() );
		internal.setY( row*( 1.0f/getRow() )+quadLocal.y()/getRow() );
#ifdef SAFE_CHK
	Q_ASSERT( internal.x()<MAYBE_MAX_COL );
	Q_ASSERT( internal.y()<MAYBE_MAX_ROW );
#endif //SAFE_CHK
		return internal;
	}
}

LDUvPointList LDGridTransform::tryInverseTransform( const LDPointList& points, bool& success, bool clip ) const
{
	LDUvPointList result;
	int length = points.length() ;

	for ( int i = 0 ; i < length ; i ++ )
	{
		bool chk=false;
		result.push_back( tryInverseTransform( points[i],chk,clip ) );
		if ( ! chk )
		{
			success=false;
			return result;
		}
	}
	success=true;
	return result;
}


LDUvPoint LDGridTransform::inverseTransform( const LDPoint& pt,bool& success,bool clip ) const
{
	auto result=tryInverseTransform( pt,success,clip );
	if ( !success )
	{
		return result;
	}
	Q_ASSERT( success );
	return result;

}

LDUvPointList LDGridTransform::inverseTransform( const LDPointList& points,bool& success,bool clip ) const
{
	LDUvPointList result;
	int length = points.length() ;

	for ( int i = 0 ; i < length ; i ++ )
	{
		result.push_back( inverseTransform( points[i],success,clip ) );
	}
	return result;
}

LDGridTransform LDGridTransform::transform( const LDGridTransform& grid,bool clip ) const
{
	LDGridTransform result=grid;

	for ( int i = 0 ; i < grid.getRow()+1 ; i ++ )
	{
		for ( int j = 0; j < grid.getColumn()+1; ++j )
		{
			LDPoint newPt=transform( grid.getPoint( i,j ),clip );
			result.setPoint( i,j,newPt );
		}
	}

	return result;
}

LDAffineTransform LDGridTransform::transform( const LDAffineTransform& affine,bool clip ) const
{
	LDAffineTransform result=affine;

	//Cubismと違い位置しか移動しない
	result.setToTranslate( transform( affine.getTranslate(),clip ) );


	return result;
}


double LDGridTransform::getRateXFromLeftCol( double x )const
{
	Q_ASSERT( x>=0 );
	Q_ASSERT( x<=1 );

	if ( x==0 )
	{
		return 0;
	}
	if ( x==1 )
	{
		return 1;
	}

	double scaled=x*getColumn();

	//小数部を求める
	return scaled-static_cast<int>( scaled );
}

double LDGridTransform::getRateYFromAboveRow( double y )const
{
	Q_ASSERT( y>=0 );
	Q_ASSERT( y<=1 );

	if ( y==0 )
	{
		return 0;
	}
	if ( y==1 )
	{
		return 1;
	}

	double scaled=y*getRow();

	//小数部を求める
	return scaled-static_cast<int>( scaled );
}

int LDGridTransform::getIncludingColumnNo( double x )const
{
	Q_ASSERT( x>=0 );
	Q_ASSERT( x<=1 );

	if ( x==1 )
	{
		return getColumn()-1;
	}
	return static_cast<int>( x*getColumn() );
}

int LDGridTransform::getIncludingRowNo( double y )const
{
	Q_ASSERT( y>=0 );
	Q_ASSERT( y<=1 );

	if ( y==1 )
	{
		return getRow()-1;
	}
	return static_cast<int>( y*getRow() );
}

LDTableIndex LDGridTransform::getQuadIndex( const LDUvPoint& t ) const
{
	double tx=t.x();
	double ty=t.y();

	//	Q_ASSERT( tx>=0 );
	//	Q_ASSERT( tx<=1 );
	//	Q_ASSERT( ty>=0 );
	//	Q_ASSERT( ty<=1 );

	int row,col;
	if ( tx==1 )
	{
		col= getColumn()-1;
	}
	else if ( tx<0 )
	{
		col=floor( tx );
	}
	else if ( 1<tx )
	{
		col=getColumn()+tx-1;
	}
	else
	{
		col= static_cast<int>( tx*getColumn() );
	}

	if ( ty==1 )
	{
		row= getRow()-1;
	}
	else if ( ty<0 )
	{
		row=floor( ty );
	}
	else if ( 1<ty )
	{
		row=getRow()+ty-1;
	}
	else
	{
		row= static_cast<int>( ty*getRow() );
	}


	return LDTableIndex( col,row );
}

LDUvPoint LDGridTransform::getLocalPoint( const LDUvPoint& t ) const
{
	double tx=t.x();
	double ty=t.y();

	LDUvPoint local;
	if ( tx==0 )
	{
		local.setX( 0 );
	}
	else if ( tx==1 )
	{
		local.setX( 1 );
	}
	else if ( tx<0 )
	{
		//外側なら分割されない
		double tmp=tx - static_cast<int>( tx );
		if ( tmp==0 )
		{
			//小数部が0なら内側判定
			local.setX( 0 );
		}
		else
		{
			local.setX( 1+tmp );
		}
	}
	else if ( 1<tx )
	{
		//外側なら分割されない
		double tmp=tx - static_cast<int>( tx );
		if ( tmp==0 )
		{
			//小数部が0なら内側判定
			local.setX( 0 );
		}
		else
		{
			local.setX( tmp );
		}
	}
	else
	{
		double scaled=tx*getColumn();
		//小数部を求める
		local.setX( scaled-static_cast<int>( scaled ) );
	}


	if ( ty==0 )
	{
		local.setY( 0 );
	}
	else if ( ty==1 )
	{
		local.setY( 1 );
	}
	else if ( ty<0 )
	{
		//外側なら分割されない
		double tmp=ty - static_cast<int>( ty );
		if ( tmp==0 )
		{
			//小数部が0なら内側判定
			local.setY( 0 );
		}
		else
		{
			local.setY( 1+tmp );
		}
	}
	else if ( 1<ty )
	{
		//外側なら分割されない
		double tmp=ty - static_cast<int>( ty );
		if ( tmp==0 )
		{
			//小数部が0なら内側判定
			local.setY( 0 );
		}
		else
		{
			local.setY( tmp );
		}
	}
	else
	{
		double scaled=ty*getRow();
		//小数部を求める
		local.setY( scaled-static_cast<int>( scaled ) );
	}

	return local;
}

//LDPoint LDGridTransform::getMappingFrom(int row, int col, const LDPoint& map) const
//{
//	LDPoint result;
//	auto quad=getQuadTransform(row,col);
//	result.setX();

//	return result;
//}

QPoint LDGridTransform::getMapedQuadIndex( const LDPoint& map ) const
{
	//TODO 最適化可能
	for ( int row = 0; row < getRow(); ++row )
	{
		for ( int col = 0; col < getColumn(); ++col )
		{
			auto quad=getQuadTransform( row,col );
			if ( quad.contains( map ) )
			{
				return QPoint( col,row );
			}
		}
	}
	Q_ASSERT( false );
	//	Q_ASSERT( ! isHit(map));


}

QPoint LDGridTransform::getOutsideMapedQuadIndex( const LDPoint& map ) const
{
	//範囲外を検索する。
	//TODO 保険として範囲が広すぎるときはAssert。キャンバスのサイズでどうにか最大値を求めるべき
	//TODO あまりに無駄が多い
	auto extended=createExtendedGrid();
	QPoint pt=extended.getMapedQuadIndex( map );
	Q_ASSERT( pt.x()<5 );
	Q_ASSERT( pt.y()<5 );
	return QPoint( pt.x()-1,pt.y()-1 );
}

QPoint LDGridTransform::getOutsideMapedQuadIndex2( const LDPoint& map ) const
{
	auto extended=createExtendedGrid().createExtendedGrid();
	QPoint pt=extended.getMapedQuadIndex( map );
	Q_ASSERT( pt.x()<5 );
	Q_ASSERT( pt.y()<5 );
	return QPoint( pt.x()-1,pt.y()-1 );
}

bool LDGridTransform::isOutside( int row, int col ) const
{
	return row<0 || row>=getRow() || col<0 || col>=getColumn();
}

bool LDGridTransform::isOutsideLocal( const LDUvPoint& t ) const
{
	//境界線上は外側ではないと判断
	return t.x()<0 || t.x()>1 || t.y()<0 || t.y()>1;
}

bool LDGridTransform::isOutsideLocal(const LDUvPointList& pts) const
{
	for(auto& pt:pts)
	{
		if(isOutsideLocal(pt))
		{
			return true;
		}
	}
	return false;
}

bool LDGridTransform::isOutsideMap( const LDPoint& pt ) const
{
	//TODO 最適化可能
	for ( int row = 0; row < getRow(); ++row )
	{
		for ( int col = 0; col < getColumn(); ++col )
		{
			auto quad=getQuadTransform( row,col );
			if ( quad.contains( pt ) )
			{
				return false;
			}
		}
	}
	return true;
}

bool LDGridTransform::isOutsideMap(const LDPointList& pts) const
{
	for(auto& pt:pts)
	{
		if(isOutsideMap(pt))
		{
			return true;
		}
	}
	return false;
}

LDQuadTransform LDGridTransform::getQuadTransform( int row, int col )const
{
	Q_ASSERT( ! isOutside( row,col ) );

	LDQuadTransform quad(
		getPoint( row,col ),
		getPoint( row,col+1 ),
		getPoint( row+1,col+1 ),
		getPoint( row+1,col ) );

	return quad;
}

LDQuadTransform LDGridTransform::getQuadTransformFromGridCoord( const LDUvPoint& t ) const
{
	auto index=getQuadIndex( t );
	int col = index.x() ;
	int row = index.y() ;

	if ( isOutside( row,col ) )
	{
		auto quad=createOutsideQuadTransform( row,col );
		return quad;
	}
	else
	{
		auto quad=getQuadTransform( row,col );
		return quad;
	}
}

LDQuadTransform LDGridTransform::getQuadTransformFromMapCoord( const LDPoint& pt,bool& success,LDTableIndex& index, bool clip ) const
{
	if ( ! isOutsideMap( pt ) )
	{
		index=getMapedQuadIndex( pt );
	}
	else
	{
		auto extended=createExtendedGrid();
		if ( ! extended.isOutsideMap( pt ) )
		{
			index=extended.getMapedQuadIndex( pt );
			index.setX( index.x()-1 );
			index.setY( index.y()-1 );
		}
		else
		{
//			auto extended2=extended.createExtendedGrid();
//			if ( ! extended2.isOutsideMap( pt ) )
//			{
//				index=extended2.getMapedQuadIndex( pt );
//				index.setX( index.x()-2 );
//				index.setY( index.y()-2 );
//			}
//			else
			{
				success=false;

				//				Q_ASSERT(false);
				return LDQuadTransform( LDPoint( 0,0 ),LDPoint( 0,0 ) );
			}
		}
	}


	if ( clip )
	{
		//Grid内にClipする。QuadをClipして変換するのではない
		index=clipIndex( index );
	}
	int col = index.x() ;
	int row = index.y() ;

	success=true;
	if ( isOutside( row,col ) )
	{
		LDQuadTransform quad=createOutsideQuadTransform( row,col );
		return quad;
	}
	else
	{
		LDQuadTransform quad=getQuadTransform( row,col );
		return quad;
	}
}

LDQuadTransform LDGridTransform::getQuadTransformFromMapCoord( const LDPoint& pt, bool clip ) const
{
	bool success;
	LDTableIndex index;
	return getQuadTransformFromMapCoord( pt,success,index,clip );
}

LDQuadTransform LDGridTransform::createOutsideQuadTransform( int row, int col ) const
{
	int tmp1=row;
	int tmp2=col;
	auto tmp=createExtendedGrid();
	tmp.setExtendRate(extendRate);
	row++;
	col++;
	if ( !tmp.isOutside( row,col ) )
	{
		return tmp.getQuadTransform( row,col );
	}
	int count=0;
	while ( true )
	{
		auto extended=tmp.createExtendedGrid();
		extended.setExtendRate(tmp.getExtendRate());
		row++;
		col++;
		if ( ! extended.isOutside( row,col ) )
		{
			return extended.getQuadTransform( row,col );
		}
		tmp=extended;

		count++;
		if ( count>10 )
		{
			qDebug()<<"row:"<<tmp1;
			qDebug()<<"col:"<<tmp2;
		}
		//		Q_ASSERT(count<10);//なにかおかしい
	}
	Q_ASSERT( false );
	//TODO 簡易処理
	//	return getOutlineQuadTransform();
	if ( row<0 )
	{
		row=0;
	}
	else if ( row>=getRow() )
	{
		row=getRow()-1;
	}

	if ( col<0 )
	{
		col=0;
	}
	else if ( col>=getColumn() )
	{
		col=getColumn()-1;
	}
	return getQuadTransform( row,col );
	//	return getOutlineSquareTransform();
	//	auto extended=createExtendedGrid();
	//拡張前の行と列を拡張後の行と列に変更
	//	return extended.getQuadTransform(row+1,col+1);
}

LDQuadTransform LDGridTransform::getOutlineQuadTransform() const
{
	int rightIndex=getColumn();
	int bottomIndex=getRow();
	LDQuadTransform quad(
		getPoint( 0,0 ),
		getPoint( 0, rightIndex ),
		getPoint( bottomIndex,rightIndex ),
		getPoint( bottomIndex,0 ) );
	return quad;
}

LDQuadTransform LDGridTransform::getOutlineSquareTransform() const
{
	int rightIndex=getColumn();
	int bottomIndex=getRow();
	LDQuadTransform quad(
		getPoint( 0,0 ),
		getPoint( bottomIndex,rightIndex ) );
	return quad;
}

//LDPoint LDGridTransform::getNormalizedPoint( int row, int col )const
//{
//	LDPoint p;
//	p.setX( 1.0f/getColumn()*row );
//	p.setY( 1.0f/getRow()*col );
//	return p;
//}

LDPoint LDGridTransform::getPoint( int row, int col )const
{
	Q_ASSERT( m_gridPoints.length()>row );
	Q_ASSERT( m_gridPoints[0].length()>col );
	return m_gridPoints[row][col];
}

LDPoint LDGridTransform::getPoint( int index ) const
{
	int row=index/( getColumn()+1 );
	int col=index%( getColumn()+1 );
	return getPoint( row,col );
}

int LDGridTransform::getPointIndex( int row, int col ) const
{
	Q_ASSERT( m_gridPoints.length()>row );
	Q_ASSERT( m_gridPoints[0].length()>col );
	return row*( getColumn()+1 )+col;
}

LDLine LDGridTransform::getLine( const LDIndexLine& line ) const
{
	return LDLine( getPoint( line.getIndex1() ),getPoint( line.getIndex2() ) );
}

LDIndexLine LDGridTransform::getIndexLine( int row1, int col1, int row2, int col2 ) const
{
	return LDIndexLine( getPointIndex( row1,col1 ),getPointIndex( row2,col2 ) );
}

QList<QList<LDPoint> > LDGridTransform::getGridPoints() const
{
	return m_gridPoints;
}

void LDGridTransform::setGridPoints( const QList<QList<LDPoint> >& value )
{
	m_gridPoints = value;

	m_cacheBounds.setSize( QSizeF( 0,0 ) );
}

bool LDGridTransform::isRectangle() const
{
	//TODO 回転の考慮なし
	for ( int i = 0; i < getColumn()+1; ++i )
	{
		if ( getPoint( 0,i ).y()!=m_originRect.y() )
		{
			return false;
		}
	}
	for ( int i = 0; i < getColumn()+1; ++i )
	{
		if ( getPoint( getRow(),i ).y()!=m_originRect.bottom() )
		{
			return false;
		}
	}
	for ( int i = 0; i < getRow()+1; ++i )
	{
		if ( getPoint( i,0 ).x()!=m_originRect.left() )
		{
			return false;
		}
	}
	for ( int i = 0; i < getRow()+1; ++i )
	{
		if ( getPoint( i,getColumn() ).x()!=m_originRect.right() )
		{
			return false;
		}
	}
	return true;
}

void LDGridTransform::setDivide( int row, int col )
{
	//矩形でない場合は変形情報を失うため、変更不可。工夫次第である程度対応できるが現状未対応
	Q_ASSERT( isRectangle() );

	float x=m_originRect.x();
	float y=m_originRect.y();
	float width=m_originRect.width();
	float height=m_originRect.height();

	m_gridPoints.clear();

	for ( int i = 0; i < row+1; ++i )
	{
		m_gridPoints.push_back( QList<LDPoint>() );
		for ( int j = 0; j < col+1; ++j )
		{
			m_gridPoints[i].push_back( LDPoint( x+width/col*j,y+height/row*i ) );
		}
	}
}

void LDGridTransform::setPoint( int row, int col, const LDPoint& pt )
{
	Q_ASSERT( m_gridPoints.length()!=0 );
	LD_ASSERT_OUT_OF_INDEX( m_gridPoints,row );
	LD_ASSERT_OUT_OF_INDEX( m_gridPoints[0],col );
	m_gridPoints[row][col]=pt;

	clearBoundsCache();
}

void LDGridTransform::setTopPoint( int col, const LDPoint& pt )
{
	setPoint( 0,col,pt );
}

void LDGridTransform::setBottomPoint( int col, const LDPoint& pt )
{
	setPoint( getRow(),col,pt );
}

void LDGridTransform::setLeftPoint( int row, const LDPoint& pt )
{
	setPoint( row,0,pt );
}

void LDGridTransform::setRightPoint( int row, const LDPoint& pt )
{
	setPoint( row,getColumn(),pt );
}

void LDGridTransform::setPointX( int row, int col, float x )
{
	auto pt=getPoint( row,col );
	pt.setX( x );
	setPoint( row,col,pt );
}

void LDGridTransform::setPointY( int row, int col, float y )
{
	auto pt=getPoint( row,col );
	pt.setY( y );
	setPoint( row,col,pt );
}

LDPointList LDGridTransform::toForm() const
{
	LDPointList result;
	for ( int i = 0; i < getRow()+1; ++i )
	{
		for ( int j = 0; j < getColumn()+1; ++j )
		{
			result.push_back( m_gridPoints[i][j] );
		}
	}
	return result;
}

void LDGridTransform::setForm( const LDPointList& value )
{
	Q_ASSERT( getPointCount()==value.length() );
	for ( int i = 0; i < getRow()+1; ++i )
	{
		for ( int j = 0; j < getColumn()+1; ++j )
		{
			m_gridPoints[i][j]=value[i*( getColumn()+1 )+j];
		}
	}

	clearBoundsCache();
}

int LDGridTransform::getPointCount() const
{
	return ( getRow()+1 )*( getColumn()+1 );
}

QList<int> LDGridTransform::getOutlinePointIndices() const
{
	QList<int> result;

	for ( int i = 0; i < getColumn()+1; ++i )
	{
		result.push_back( getPointIndex( 0,i ) );
	}
	for ( int i = 1; i < getRow()+1; ++i )
	{
		result.push_back( getPointIndex( i,getColumn() ) );
	}
	for ( int i = getColumn()-1; i >= 0; --i )
	{
		result.push_back( getPointIndex( getRow(),i ) );
	}
	for ( int i = getRow()-1; i >= 1; --i )
	{
		result.push_back( getPointIndex( i,0 ) );
	}

	return result;
}

LDLineList LDGridTransform::getOutline() const
{
	return getIndexOutline().getLines( toForm() );
}

LDIndexLineList LDGridTransform::getIndexOutline() const
{
	LDIndexLineList result( getOutlinePointIndices() );
	return result;
}

LDPointList LDGridTransform::getOutlinePoints() const
{
	QList<int> indices=getOutlinePointIndices();

	LDPointList result;

	foreach ( int index, indices )
	{
		result.push_back( getPoint( index ) );
	}
	return result;
}

QPolygonF LDGridTransform::getOutlinePolygon() const
{
	QList<int> indices=getOutlinePointIndices();

	QPolygonF result;

	foreach ( int index, indices )
	{
		result.push_back( getPoint( index ) );
	}
	return result;
}

QList<int> LDGridTransform::getInnerLinePointIndices() const
{
	QList<int> result;

	for ( int row = 0; row < getRowArrayLength(); ++row )
	{
		if ( row==0||row+1==getRowArrayLength() )
		{
			continue;
		}
		for ( int col = 0; col < getColumnArrayLength(); ++col )
		{
			if ( col==0||col+1==getColumnArrayLength() )
			{
				continue;
			}
			result.push_back( getPointIndex( row,col ) );
		}
	}

	return result;
}

LDIndexLineList LDGridTransform::getInnerIndexLines() const
{
	LDIndexLineList result;

	for ( int row = 0; row < getRowArrayLength(); ++row )
	{
		if ( row==0||row+1==getRowArrayLength() )
		{
			continue;
		}
		for ( int col = 0; col < getColumnArrayLength(); ++col )
		{
			if ( col==0||col+1==getColumnArrayLength() )
			{
				continue;
			}
			//その点から左と上
			result.push_back( getIndexLine( row,col-1,row,col ) );
			result.push_back( getIndexLine( row-1,col,row,col ) );

			if ( row+2==getRowArrayLength() )
			{
				//最後だけ下も追加
				result.push_back( LDIndexLine( getPointIndex( row,col ),getPointIndex( row+1,col ) ) );
			}

			if ( col+2==getColumnArrayLength() )
			{
				//最後だけ右も追加
				result.push_back( LDIndexLine( getPointIndex( row,col ),getPointIndex( row,col+1 ) ) );
			}
		}
	}

	return result;
}

LDLineList LDGridTransform::getInnerLines() const
{
	LDIndexLineList lines=getInnerIndexLines();

	LDLineList result;

	foreach ( auto line, lines )
	{
		result.push_back( getLine( line ) );
	}
	return result;
}


bool LDGridTransform::isHitOutline( const LDPoint& pt, float hitRange ) const
{
	if ( ! isPreHit( pt,hitRange ) )
	{
		return false;
	}
	LDIndexLineList outline=getIndexOutline();

	return outline.isHit( toForm(),pt,hitRange );
}

LDRectF LDGridTransform::getBounds() const
{
	if ( m_cacheBounds.size()==QSize( 0,0 ) )
	{
		//TODO const関数内でのmutableの変更はスレッドセーフにしないといけない?
		m_cacheBounds=math::PointUtil::getBoundingRect( toForm() );
	}

	return m_cacheBounds;
}

bool LDGridTransform::isPreHit( const LDPoint& pt, float hitRange ) const
{
	QRectF rect=getBounds();

	//上下左右を拡張
	rect.adjust( -hitRange,-hitRange,hitRange,hitRange );

	return rect.contains( pt );
}

bool LDGridTransform::isHit( const LDPoint& pt ) const
{
	auto polygon=getOutlinePolygon();
	return polygon.containsPoint( pt,Qt::WindingFill );
}

LDGridTransform LDGridTransform::createExtendedGrid( ) const
{

	//一回り大きい四角形を元にする
	//	auto quad=getOutlineQuadTransform();
	auto extendedQuad=createExtendedQuad( extendRate );
	LDGridTransform extendedGrid( extendedQuad,getRow()+2,getColumn()+2 );

	//現在のグリッドを内側にコピー
	extendedGrid.copyFrom( *this,1,1 );


	//外側のうち、四隅の四角形に含まれる点を設定。分割にかかわらず決まる
	extendedGrid.setTopPoint( 1,extendedQuad.transform( LDUvPoint((ld_float) extendRate/(2 * extendRate + 1),0 ) ) ); //左上四角の右上の点。
	extendedGrid.setLeftPoint( 1,extendedQuad.transform( LDUvPoint( 0,(ld_float) extendRate/(2 * extendRate + 1)) ) );

	extendedGrid.setTopPoint( extendedGrid.getColumn()-1,extendedQuad.transform( LDUvPoint( (ld_float) (extendRate+1)/(2 * extendRate + 1),0 ) ) );
	extendedGrid.setRightPoint( 1,extendedQuad.transform( LDUvPoint( 1,(ld_float) extendRate/(2 * extendRate + 1) ) ) );

	extendedGrid.setRightPoint( extendedGrid.getRow()-1,extendedQuad.transform( LDUvPoint( 1,(ld_float) (extendRate+1)/(2 * extendRate + 1) ) ) );
	extendedGrid.setBottomPoint( extendedGrid.getColumn()-1,extendedQuad.transform( LDUvPoint( (ld_float) (extendRate+1)/(2 * extendRate + 1),1 ) ) );

	extendedGrid.setBottomPoint( 1,extendedQuad.transform( LDUvPoint( (ld_float) extendRate/(2 * extendRate + 1),1 ) ) );
	extendedGrid.setLeftPoint( extendedGrid.getRow()-1,extendedQuad.transform( LDUvPoint( 0,(ld_float) (extendRate+1)/(2 * extendRate + 1) ) ) );


	//外周を設定
	extendedGrid.normalizeRow( 0,1,extendedGrid.getColumn()-1 ); //0行目、2列からcol-1列目までを一定幅にマッピングを正規化
	extendedGrid.normalizeRow( extendedGrid.getRow(),1,extendedGrid.getColumn()-1 );
	extendedGrid.normalizeColumn( 0,1,extendedGrid.getRow()-1 );
	extendedGrid.normalizeColumn( extendedGrid.getColumn(),1,extendedGrid.getRow()-1 );

	return extendedGrid;
}

void LDGridTransform::setExtendRate(int rate)
{
	extendRate = rate;
}
int LDGridTransform::getExtendRate() const
{
	return extendRate;
}

LDQuadTransform LDGridTransform::createExtendedQuad( int extend ) const
{
	return getOutlineQuadTransform().createExtend( extend );
}

void LDGridTransform::copyFrom( const LDGridTransform& src )
{
	m_gridPoints=src.m_gridPoints;
	m_originRect=src.m_originRect;
}

void LDGridTransform::copyFrom( const LDGridTransform& src, int row, int col )
{
	for ( int i = row; i < getRowArrayLength()+1; ++i )
	{
		if ( src.getRowArrayLength()<i )
		{
			//コピー元がない
			continue;
		}
		for ( int j = col; j < getColumnArrayLength()+1; ++j )
		{
			if ( src.getColumnArrayLength()<j )
			{
				//コピー元がない
				continue;
			}
			setPoint( i,j,src.getPoint( i-row,j-col ) );
		}
	}
}

void LDGridTransform::normalizeRow( int row, int startCol, int endCol )
{
	auto start=getPoint( row,startCol );
	auto end=getPoint( row,endCol );
	for ( int col = startCol+1; col < endCol; ++col )
	{
		float t=( float )( col-startCol )/( endCol-startCol );
		setPoint( row,col,LDMathUtil::lerp( start,end,t ) );
	}
}

void LDGridTransform::normalizeColumn( int col, int startRow, int endRow )
{
	auto start=getPoint( startRow,col );
	auto end=getPoint( endRow,col );
	for ( int row = startRow+1; row < endRow; ++row )
	{
		float t=( float )( row-startRow )/( endRow-startRow );
		setPoint( row,col,LDMathUtil::lerp( start,end,t ) );
	}
}

LDTableIndex LDGridTransform::clipIndex( const LDTableIndex& index ) const
{
	LDTableIndex result;
	result.setX( LDMathUtil::clamp( index.x(),0,getColumn() ) );
	result.setY( LDMathUtil::clamp( index.y(),0,getRow() ) );
	return result;
}

void LDGridTransform::clearBoundsCache()
{
	m_cacheBounds.setSize( QSizeF( 0,0 ) );
}

bool operator ==( const LDGridTransform& a, const LDGridTransform& b )
{
	return a.getGridPoints()==b.getGridPoints();
}

bool operator !=( const LDGridTransform& a, const LDGridTransform& b )
{
	return a.getGridPoints()!=b.getGridPoints();
}

//***************************************
// Serialize
//***************************************
template<class Archive>
void LDGridTransform::serialize( Archive& ar, unsigned int /*version*/ )
{
	LD_SERIALIZE_VALUE( ar, m_gridPoints );
	LD_SERIALIZE_VALUE( ar, m_originRect );
}
LD_SERIALIZE_IMPL( LDGridTransform );

QDebug operator<<( QDebug dbg, const LDGridTransform& grid )
{
	dbg.nospace() << grid.getGridPoints();

	return dbg;
}



} // namespace live2d

