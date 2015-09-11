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

	clearBoundsCache();
}

LDGridTransform::LDGridTransform( const LDPoint& topLeft, const LDPoint& bottomRight, int row, int col )
	:LDGridTransform( topLeft.x(),topLeft.y(),bottomRight.x()-topLeft.x(),bottomRight.y()-topLeft.y(),row,col )
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

	clearBoundsCache();
}

int LDGridTransform::getRow()const
{
	return m_gridPoints.length()-1;
}

int LDGridTransform::getColumn()const
{
	if ( m_gridPoints.length()==0 )
	{
		return 0;
	}
	return m_gridPoints[0].length()-1;
}

int LDGridTransform::getRowArrayLength() const
{
	return m_gridPoints.length();
}

int LDGridTransform::getColumnArrayLength() const
{
	if ( m_gridPoints.length()==0 )
	{
		return 0;
	}
	return m_gridPoints[0].length();
}

LDPoint LDGridTransform::transform( const LDPoint& t,bool clip )const
{
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
	QPoint index=getQuadIndex( LDPoint( tx,ty ) );
	int col = index.x() ;
	int row = index.y() ;

	LDPoint local=getLocalPoint( LDPoint( tx,ty ) );

	if ( isOutside( row,col ) )
	{
		LDQuadTransform quad=createOutsideQuadTransform( row,col );
		return quad.transform( LDPoint( tx,ty ) );
	}
	else
	{
		LDQuadTransform quad=getQuadTransform( row,col );
		return quad.transform( local );
	}
}

LDPointList LDGridTransform::transform( const LDPointList& points,bool clip ) const
{
	LDPointList result;
	int length = points.length() ;

	for ( int i = 0 ; i < length ; i ++ )
	{
		result.push_back( transform( points[i],clip ) );
	}
	return result;
}

LDPoint LDGridTransform::inverseTransform( const LDPoint& pt,bool clip ) const
{
	if ( getColumn()==0 && getRow()==0 )
	{
		//メッシュがない場合はそのままの値を返す
		return pt;
	}

	double x=pt.x();
	double y=pt.y();


	//Gridからマッピング先のQuadを見つける
	QPoint index=getMapedQuadIndex( LDPoint( x,y ) );
	int col = index.x() ;
	int row = index.y() ;

	if ( clip )
	{
		//Grid内にClipする。QuadをClipして変換するのではない
		col=LDMathUtil::clamp( col,0,getColumn() );
		row=LDMathUtil::clamp( row,0,getRow() );
	}

	LDPoint local;

	if ( isOutside( row,col ) )
	{
		LDQuadTransform quad=createOutsideQuadTransform( row,col );
		return quad.inverseTransform( pt,clip );
		local= quad.inverseTransform( pt,clip );

		LDPoint internal;
		internal.setX( ( col+1 )*( 1.0f/( getColumn()+2 ) )+local.x()/( getColumn()+2 ) );
		internal.setY( ( row+1 )*( 1.0f/( getRow()+2 ) )+local.y()/( getRow()+2 ) );

		LDQuadTransform tmp( LDPoint( -1,-1 ),LDPoint( getColumn()+1,getRow()+1 ) );
		return tmp.transform( internal );
	}
	else
	{
		LDQuadTransform quad=getQuadTransform( row,col );
		local= quad.inverseTransform( pt,clip );

		LDPoint internal;
		internal.setX( col*( 1.0f/getColumn() )+local.x()/getColumn() );
		internal.setY( row*( 1.0f/getRow() )+local.y()/getRow() );



		return internal;
	}



}

LDPointList LDGridTransform::inverseTransform( const LDPointList& points,bool clip ) const
{
	LDPointList result;
	int length = points.length() ;

	for ( int i = 0 ; i < length ; i ++ )
	{
		result.push_back( inverseTransform( points[i],clip ) );
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

QPoint LDGridTransform::getQuadIndex( const LDPoint& t ) const
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
	else
	{
		col= static_cast<int>( tx*getColumn() );
	}

	if ( ty==1 )
	{
		row= getRow()-1;
	}
	else
	{
		row= static_cast<int>( ty*getRow() );
	}


	return QPoint( col,row );
}

LDPoint LDGridTransform::getLocalPoint( const LDPoint& t ) const
{
	double tx=t.x();
	double ty=t.y();

	LDPoint localT;
	if ( tx==0 )
	{
		localT.setX( 0 );
	}
	else if ( tx==1 )
	{
		localT.setX( 1 );
	}
	else
	{
		double scaled=tx*getColumn();
		//小数部を求める
		localT.setX( scaled-static_cast<int>( scaled ) );
	}


	if ( ty==0 )
	{
		localT.setY( 0 );
	}
	else if ( ty==1 )
	{
		localT.setY( 1 );
	}
	else
	{
		double scaled=ty*getRow();
		//小数部を求める
		localT.setY( scaled-static_cast<int>( scaled ) );
	}

	return localT;
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

	//範囲外を検索する。
	//TODO 保険として範囲が広すぎるときはAssert。キャンバスのサイズでどうにか最大値を求めるべき
	//TODO あまりに無駄が多い
	auto extended=createExtendedGrid();
	QPoint pt=extended.getMapedQuadIndex( map );
	return QPoint( pt.x()-1,pt.y()-1 );
}

bool LDGridTransform::isOutside( int row, int col ) const
{
	return row<0 || row>=getRow() || col<0 || col>=getColumn();
}


LDQuadTransform LDGridTransform::getQuadTransform( int row, int col )const
{
	if ( isOutside( row,col ) )
	{
		qDebug( "xxx" );
	}
	Q_ASSERT( ! isOutside( row,col ) );

	LDQuadTransform quad(
		getPoint( row,col ),
		getPoint( row,col+1 ),
		getPoint( row+1,col+1 ),
		getPoint( row+1,col ) );

	return quad;
}

LDQuadTransform LDGridTransform::createOutsideQuadTransform( int /*row*/, int /*col*/ ) const
{
	return getOutlineQuadTransform();
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

LDPoint LDGridTransform::getNormalizedPoint( int row, int col )const
{
	LDPoint p;
	p.setX( 1.0f/getColumn()*row );
	p.setY( 1.0f/getRow()*col );
	return p;
}

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
	return getIndexOutline().getLines(toForm());
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

LDGridTransform LDGridTransform::createExtendedGrid( int extend ) const
{
	QRectF bounds=getBounds();
	LDGridTransform grid(
		getPoint( 0,0 ).x()-bounds.width(),
		getPoint( 0,0 ).y()-bounds.height(),
		bounds.width()+bounds.width()*2,
		bounds.height()+bounds.height()*2,
		getRow()+1,getColumn()+1
	);

	grid.copyFrom( *this,1,1 );
	return grid;
}

void LDGridTransform::copyFrom( const LDGridTransform& src )
{
	m_gridPoints=src.m_gridPoints;
	m_originRect=src.m_originRect;
}

void LDGridTransform::copyFrom( const LDGridTransform& src, int row, int col )
{
	for ( int i = row; i < getRow()+1; ++i )
	{
		if ( src.getRow()<i )
		{
			continue;
		}
		for ( int j = col; j < getColumn()+1; ++j )
		{
			if ( src.getColumn()<j )
			{
				continue;
			}
			setPoint( j,i,src.getPoint( j-col,i-row ) );
		}
	}
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

