/**
 *
 *  2015/5/21
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDTriangle.h"

namespace live2d
{

LDTriangle::LDTriangle():
	m_index1( -1 ),m_index2( -1 ),m_index3( -1 )
{

}

LDTriangle::LDTriangle( int a, int b, int c )
{
	setIndex( a,b,c );
}

LDTriangle::~LDTriangle()
{

}

LDPolygon LDTriangle::toPolygon( const LDPointList& points ) const
{
	Q_ASSERT( points.length() > m_index1 );
	Q_ASSERT( points.length() > m_index2 );
	Q_ASSERT( points.length() > m_index3 );

	QVector<LDPoint> v;
	v<<points.at( m_index1 )<<points.at( m_index2 )<<points.at( m_index3 );
	return LDPolygon( v );
}

void LDTriangle::setClockWise( const LDPointList& form, ClockWise clockWise )
{
	Q_ASSERT( form.length() > m_index1 );
	Q_ASSERT( form.length() > m_index2 );
	Q_ASSERT( form.length() > m_index3 );

	LDPoint v0=form.at( m_index1 );
	LDPoint v1=form.at( m_index2 );
	LDPoint v2=form.at( m_index3 );

	//行列式で時計回りか判定
	//行列式の計算。 QMatrix3x3にはないので手動で作成。

	double m[3][3]=
	{
		v0.x(),v0.y(),1,
		v1.x(),v1.y(),1,
		v2.x(),v2.y(),1
	};

	double determinant=  m[0][0]*m[1][1]*m[2][2]
						 +m[0][1]*m[1][2]*m[2][0]
						 +m[0][2]*m[1][0]*m[2][1]
						 -m[0][2]*m[1][1]*m[2][0]
						 -m[0][0]*m[1][2]*m[2][1]
						 -m[0][1]*m[1][0]*m[2][2];
	ClockWise current;
	if ( determinant<0 ) //CW
	{
		current=ClockWise::CW;
	}
	else            //CCWまたは3点が一直線上など
	{
		current=ClockWise::CCW;
	}

	if ( clockWise!=current ) //設定した順番と異なる場合 Indexを入れ替える
	{
		std::swap( m_index1,m_index2 );
	}
}

void LDTriangle::setIndex( int a,int b,int c )
{
	Q_ASSERT( a!=b );
	Q_ASSERT( b!=c );
	Q_ASSERT( a!=c );
	m_index1=a;
	m_index2=b;
	m_index3=c;
}

int LDTriangle::getIndex1() const
{
	return m_index1;
}

int LDTriangle::getIndex2() const
{
	return m_index2;
}
int LDTriangle::getIndex3() const
{
	return m_index3;
}

int LDTriangle::getIndexWithoutLine( LDIndexLine l ) const
{
	Q_ASSERT( containsLine( l ) );

	if ( ! l.hasIndex( m_index1 ) )
	{
		return m_index1;
	}
	if ( ! l.hasIndex( m_index2 ) )
	{
		return m_index2;
	}
	if ( ! l.hasIndex( m_index3 ) )
	{
		return m_index3;
	}
	return -1;
}

LDPoint LDTriangle::getPoint1( const LDPointList& points ) const
{
	return points[m_index1];
}

LDPoint LDTriangle::getPoint2( const LDPointList& points ) const
{
	return points[m_index2];
}

LDPoint LDTriangle::getPoint3( const LDPointList& points ) const
{
	return points[m_index3];
}

LDIndexLine LDTriangle::getLine1() const
{
	return LDIndexLine( m_index1,m_index2 );
}

LDIndexLine LDTriangle::getLine2() const
{
	return LDIndexLine( m_index2,m_index3 );
}

LDIndexLine LDTriangle::getLine3() const
{
	return LDIndexLine( m_index1,m_index3 );
}

LDIndexLineList LDTriangle::getRelatedLines( int pointIndex ) const
{
	LDIndexLineList result;

	LDIndexLine line1=getLine1();
	LDIndexLine line2=getLine2();
	LDIndexLine line3=getLine3();
	if ( line1.hasIndex( pointIndex ) )
	{
		result.push_back( line1 );
	}
	if ( line2.hasIndex( pointIndex ) )
	{
		result.push_back( line2 );
	}
	if ( line3.hasIndex( pointIndex ) )
	{
		result.push_back( line3 );
	}

	return result;
}

bool LDTriangle::hasIndex( int pointIndex ) const
{
	if ( m_index1==pointIndex )
	{
		return true;
	}
	if ( m_index2==pointIndex )
	{
		return true;
	}
	if ( m_index3==pointIndex )
	{
		return true;
	}
	return false;
}

bool LDTriangle::containsLine( LDIndexLine l ) const
{
	if ( l.hasIndex( m_index1 ) && l.hasIndex( m_index2 ) )
	{
		return true;
	}
	if ( l.hasIndex( m_index2 ) && l.hasIndex( m_index3 ) )
	{
		return true;
	}
	if ( l.hasIndex( m_index1 ) && l.hasIndex( m_index3 ) )
	{
		return true;
	}

	return false;
}

bool LDTriangle::isSharedLine( LDTriangle t ) const
{
	if ( containsLine( t.getLine1() ) )
	{
		return true;
	}
	if ( containsLine( t.getLine2() ) )
	{
		return true;
	}
	if ( containsLine( t.getLine3() ) )
	{
		return true;
	}

	return false;
}

bool LDTriangle::operator ==( const LDTriangle& rop )
{
	if ( m_index1==rop.m_index1 && m_index2==rop.m_index2 && m_index3==rop.m_index3 )
	{
		return true;
	}
	if ( m_index1==rop.m_index1 && m_index2==rop.m_index3 && m_index3==rop.m_index2 )
	{
		return true;
	}
	if ( m_index1==rop.m_index2 && m_index2==rop.m_index1 && m_index3==rop.m_index3 )
	{
		return true;
	}
	if ( m_index1==rop.m_index2 && m_index2==rop.m_index3 && m_index3==rop.m_index1 )
	{
		return true;
	}
	if ( m_index1==rop.m_index3 && m_index2==rop.m_index2 && m_index3==rop.m_index1 )
	{
		return true;
	}
	if ( m_index1==rop.m_index3 && m_index2==rop.m_index1 && m_index3==rop.m_index2 )
	{
		return true;
	}
	return false;
}

//***************************************
// Serialize
//***************************************
template<class Archive>
void LDTriangle::serialize( Archive& ar, unsigned int /*version*/ )
{
	LD_SERIALIZE_VALUE( ar, m_index1 );
	LD_SERIALIZE_VALUE( ar, m_index2 );
	LD_SERIALIZE_VALUE( ar, m_index3 );
}
LD_SERIALIZE_IMPL( LDTriangle );


QDebug operator<<( QDebug dbg, const LDTriangle& tr )
{
	dbg.nospace() << QString( "LDTriangle(%1,%2,%3)" ).arg( tr.getIndex1() ).arg( tr.getIndex2() ).arg( tr.getIndex3() );

	return dbg;
}

} // namespace live2d

