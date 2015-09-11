/**
 *
 *  2015/8/2
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDUvMesh.h"
#include "LDMathUtil.h"
#include "TriangleUtil.h"
#include "Triangulation.h"

namespace live2d
{

LDUvMesh::LDUvMesh()
{

}

void LDUvMesh::copyFrom( const LDUvMesh& src )
{
	m_points=src.m_points;
	m_uvMap=src.m_uvMap;
	m_lines=src.m_lines;
	m_triangles=src.m_triangles;
}

//***************************************
// Debug
//***************************************
void LDUvMesh::dumpDetail( int nest )const
{
	qDebug().noquote().nospace()
			<< QString( nest,QChar( '\t' ) )
			<< "Mesh:"
			<< QString( " Vertices %1" ).arg( getVertexCount() )
			<< QString( " Polygons %1" ).arg( getTriangleCount() ) ;

	qDebug().noquote().nospace()
			<<QString( nest+1,QChar( '\t' ) )
			<<"form:"<<m_points;
	qDebug().noquote().nospace()
			<<QString( nest+1,QChar( '\t' ) )
			<<"uvmap:"<<m_uvMap;
	qDebug().noquote().nospace()
			<<QString( nest+1,QChar( '\t' ) )
			<<"lines:"<<m_lines;
	qDebug().noquote().nospace()
			<<QString( nest+1,QChar( '\t' ) )
			<<"polygons:"<<m_triangles;
}

void LDUvMesh::replaceUv( int index, LDPoint uv )
{
	LD_ASSERT_OUT_OF_INDEX( m_uvMap,index );

	m_uvMap.replace( index,uv );
}
void LDUvMesh::replacePoint( int index, LDPoint vertex )
{
	LD_ASSERT_OUT_OF_INDEX( m_points,index );

	m_points.replace( index,vertex );
}

void LDUvMesh::replacePointList( const LDPointList& form )
{
	Q_ASSERT( m_points.length()==form.length() );

	for ( int i = 0; i < form.length(); ++i )
	{
		m_points.replace( i,form[i] );
	}
}

bool LDUvMesh::operator ==( const LDUvMesh& rop )
{
	if ( m_points!=rop.m_points )
	{
		return false;
	}

	if ( m_uvMap!=rop.m_uvMap )
	{
		return false;
	}
	if ( m_triangles!=rop.m_triangles )
	{
		return false;
	}

	return true;
}
LDPoint LDUvMesh::getCalcAddVertex( LDPoint uv ) const
{
	LDPoint calcAddVertex( -1,-1 ); //とりあえず  -1,-1で初期化

	if ( m_points.size()==0 ) //最初の頂点がなければuvと同じ座標位置にformをする
	{
		calcAddVertex=LDPoint( 0,0 ) ;
	}
	else if ( m_points.size()==1 ) //頂点数が一つだけならばその座標を原点としてuvと同じ比率の座標をformにする
	{
		LDPoint p0= m_points.at( 0 );
		calcAddVertex= LDPoint( p0.x()+uv.x(),p0.y()+uv.y() );
	}
	//	else if ( m_points.size()==2 )// NOTE 計算あまり検証していない
	//	{
	//		//uvと頂点の縮尺を計算
	//		float scale_x=0;
	//		if ( ( m_uvMap[1].x()-m_uvMap[0].x() )==0 )
	//		{
	//			scale_x=1;
	//		}
	//		else
	//		{
	//			scale_x=( m_points[1].x()-m_points[0].x() )/( m_uvMap[1].x()-m_uvMap[0].x() );
	//		}

	//		float scale_y=0;
	//		if ( ( m_uvMap[1].y()-m_uvMap[0].y() )==0 )
	//		{
	//			scale_y=1;
	//		}
	//		else
	//		{
	//			scale_y=( m_points[1].y()-m_points[0].y() )/( m_uvMap[1].y()-m_uvMap[0].y() );
	//		}

	//		calcAddVertex =LDPoint( uv.x()*scale_x,uv.y()*scale_y ) ;
	//	}
	else if ( m_points.size()>=2 )
	{
		LDPoint s0=m_uvMap[0];
		LDPoint s1=m_uvMap[1];
		LDPoint s2=m_uvMap.last();

		LDPoint t0=m_points[0];
		LDPoint t1=m_points[1];
		calcAddVertex=math::TriangleUtil::getSimilarityTrianglePoint( s0,s1,s2,t0,t1 );
	}

	return calcAddVertex;
}
LDUvMap LDUvMesh::getUvMap() const
{
	return m_uvMap;
}
bool LDUvMesh::isHit( const LDPoint& pt ) const
{
	QPolygonF polygon=m_triangles.getOutlinePolygon( m_points );
	//第二引数のFillRuleはQPainterPathのリファレンスがわかりやすい
	return polygon.containsPoint( pt,Qt::WindingFill );
}
bool LDUvMesh::verify() const
{
	if ( getVertexCount()<3 )
	{
		//三角形を満たしてない
		qWarning( "Invalid mesh! Too few points." );
		return false;
	}
	if ( getVertexCount()-2 > getTriangleCount() )
	{
		//三角分割しきれてない。飛び地があるはず
		qWarning( "Invalid mesh! Too few triangles." );
		return false;
	}
	return true;
}
void LDUvMesh::setUvMap( const LDUvMap& value )
{
	m_uvMap = value;
}


void LDUvMesh::addUv( LDPoint uv,bool clamp )
{
	if ( clamp )
	{
		//0-1区間の縛りに引っかかる処理が多いので、デフォルトでは自動で直す
		uv=LDMathUtil::clamp( uv,LDPoint( 0,0 ),LDPoint( 1,1 ) );
	}
	else
	{
		LD_ASSERT_OUT_OF_RANGE( uv.x(),0,1 );
		LD_ASSERT_OUT_OF_RANGE( uv.y(),0,1 );
	}


	m_uvMap.push_back( uv );
	//頂点の計算
	m_points.push_back(	getCalcAddVertex( uv ) );
}
void LDUvMesh::insertUv( int index, LDPoint uv )
{
	m_uvMap.insert( index,uv );
	m_points.insert( index,getCalcAddVertex( uv ) );
	//form.insert( index,p );

	updateLinesForPointInsert( index );
}
void LDUvMesh::addUv( float u, float v ,bool clamp )
{
	addUv( LDPoint( u,v ) ,clamp );
}
bool LDUvMesh::removeUv( LDPoint uv )
{
	int index=m_uvMap.indexOf( uv );

	if ( index<0 )
	{
		//一致なしなら何もしない
		return false;
	}

	deleteLine( index ); //まずは線を消す
	m_points.remove( index ); //頂点削除
	m_uvMap.remove( index ); //uv削除
	//updateLinesForPointInsert(index);
	updateLinesForPointDeleted( index );

	return true;
}
void LDUvMesh::addLine( LDIndexLine line )
{
	if ( ! existsLine( line ) )
	{
		m_lines.push_back( line );
	}
	else
	{
		qCritical()<<"exist line came ! check line before this method called";
	}
	m_lines.sort();
}

void LDUvMesh::addLine( int index1, int index2 )
{
	addLine( LDIndexLine( index1,index2 ) );
}

bool LDUvMesh::deleteLine( LDIndexLine line )
{
	return m_lines.removeOne( line );
}

bool LDUvMesh::deleteLine( int vertexIndex )
{
	auto it=m_lines.begin();
	bool deleted=false;
	while ( it != m_lines.end() )
	{
		LDIndexLine line=static_cast<LDIndexLine>( *it );

		if ( line.hasIndex( vertexIndex ) )
		{
			deleted=true;
			it=m_lines.erase( it );
		}
		else
		{
			it++;
		}
	}

	qDebug()<<m_lines;
	return deleted;
}

bool LDUvMesh::existsLine( LDIndexLine line )const
{
	return m_lines.contains( line );
}
void LDUvMesh::updateLinesForPointInsert( int pointIndex )
{
	//頂点挿入によりずれたIndexを修正//もっと効率化できるはずだがもっさりしていたらやる
	for ( int i=0; i<m_lines.size(); i++ )
	{
		int first=m_lines.at( i ).getIndex1();
		int second=m_lines.at( i ).getIndex2();
		if ( first>=pointIndex )
		{
			first+=1;
		}
		if ( second>=pointIndex )
		{
			second+=1;
		}
		m_lines.replace( i,LDIndexLine( first,second ) );
	}
}

void LDUvMesh::updateLinesForPointDeleted( int pointIndex )
{
	//頂点挿入によりずれたIndexを修正//もっと効率化できるはずだがもっさりしていたらやる
	for ( int i=0; i<m_lines.size(); i++ )
	{
		int first=m_lines.at( i ).getIndex1();
		int second=m_lines.at( i ).getIndex2();
		if ( first>=pointIndex )
		{
			first-=1;
		}
		if ( second>pointIndex )
		{
			second-=1;
		}
		m_lines.replace( i,LDIndexLine( first,second ) );
	}
}
void LDUvMesh::updateUvMap( QSizeF ImageSize )
{
	m_uvMap.clear();
	for ( int i=0; i<m_points.size(); i++ )
	{
		float u=m_points[i].x()/ImageSize.width();
		float v=m_points[i].y()/ImageSize.height();

		LDMathUtil::clamp( u,0.0f,1.0f );
		LDMathUtil::clamp( v,0.0f,1.0f );

		m_uvMap.push_back( LDPoint( u,v ) );
	}
}

void LDUvMesh::updateLines()
{
	m_lines.sort();
}

void LDUvMesh::updatePolygons()
{
	m_triangles.update( m_lines );
	m_triangles.setClockWise( m_points,ClockWise::CCW ); //反時計回りに指定
}



void LDUvMesh::triangulation()
{
	m_triangles=math::Triangulation::exec( m_points );
	m_lines=m_triangles.toIndexLineList();
}
int LDUvMesh::getTriangleCount() const
{
	return m_triangles.length();
}

int LDUvMesh::getLineCount() const
{
	return m_lines.length();
}
LDPoint LDUvMesh::getUv( int index )const
{
	LD_ASSERT_OUT_OF_INDEX( m_uvMap,index );

	return m_uvMap[index];
}

LDTriangle LDUvMesh::getTriangle( int index ) const
{
	LD_ASSERT_OUT_OF_INDEX( m_triangles,index );

	return m_triangles[index];
}

LDIndexLine LDUvMesh::getLine( int index ) const
{
	LD_ASSERT_OUT_OF_INDEX( m_lines,index );

	return m_lines[index];
}
LDPointList LDUvMesh::getPointList() const
{
	return m_points;
}
LDIndexLineList LDUvMesh::getLines() const
{
	return m_lines;
}

void LDUvMesh::setLines( const LDIndexLineList& value )
{
	m_lines = value;
}
LDTriangleList LDUvMesh::getTriangles() const
{
	return m_triangles;
}

void LDUvMesh::setTriangles( const LDTriangleList& value )
{
	m_triangles = value;
}
LDPoint LDUvMesh::getPoint( int index ) const
{
	LD_ASSERT_OUT_OF_INDEX( m_points,index );

	return m_points[index];
}

int LDUvMesh::getVertexCount() const
{
	return m_points.length();
}

void LDUvMesh::reset()
{
	m_points.clear();
	m_uvMap.clear();
	m_lines.clear();
	m_triangles.clear();
}

void LDUvMesh::dump( int nest ) const
{
	qDebug().noquote().nospace()
			<< QString( nest,QChar( '\t' ) )
			<< "Mesh:"
			<< QString( " Vertices %1" ).arg( getVertexCount() )
			<< QString( " Polygons %1" ).arg( getTriangleCount() )
			<<" Points:"<<m_points;
}


//***************************************
// Serialize
//***************************************
template<class Archive>
void LDUvMesh::serialize( Archive& ar, unsigned int /*version*/ )
{
	LD_SERIALIZE_VALUE( ar,m_points );
	LD_SERIALIZE_VALUE( ar,m_uvMap );
	LD_SERIALIZE_VALUE( ar,m_triangles );
}



LD_SERIALIZE_IMPL( LDUvMesh );
} // namespace live2d

