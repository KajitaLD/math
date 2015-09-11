/**
 *
 *  2015/5/21
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDIndexLine.h"
#include "TriangleUtil.h"
#include "PointUtil.h"

namespace live2d {

using namespace math;

LDIndexLine::LDIndexLine():
	m_index1( -1 ),m_index2( -1 )
{

}

LDIndexLine::LDIndexLine( int a, int b )
{
	setIndex( a,b );
}

LDIndexLine::~LDIndexLine()
{

}

int LDIndexLine::getIndex1() const
{
	return m_index1;
}

int LDIndexLine::getIndex2() const
{
	return m_index2;
}

bool LDIndexLine::hasIndex( int index ) const
{
	if ( m_index1==index || m_index2==index )
	{
		return true;
	}
	return false;
}

bool LDIndexLine::isEnabled() const
{
	return ( m_index1>=0 )&&( m_index2>=0 );
}

bool LDIndexLine::isHit(const LDPointList &form, LDPoint p, float hitRange) const
{
	LDLine l=this->toLine(form);

	LDPoint startPt=l.p1();
	LDPoint endPt=l.p2();

	//端点から一定の距離内だったら当たり
	if(PointUtil::isHit(startPt,p,hitRange))
		return true;
	if(PointUtil::isHit(endPt,p,hitRange))
		return true;


	//点が一直線上にないか確認
	if ( math::TriangleUtil::isTriangle( startPt,endPt,p ) )
	{
		//鈍角三角形なら判定外
		if ( math::TriangleUtil::isObtuseAngle( startPt,endPt,p ) )
		{
			return false;
		}

		//三角形の面積を算出して、その底面で割れば高さ＝線と点の距離
		float distance=TriangleUtil::getTriangleHeight(startPt,endPt,p);

		if ( distance<=hitRange )
		{
			return true;
		}
		return false;

	}
	//一直線上にあるが線分外にあるか判定
	QVector2D ab(endPt-startPt);
	QVector2D ap(p-startPt);
	QVector2D bp(p-endPt);
	float omega=0.0001f;//NOTE:誤差の基準値 かなり適当に指定
	if ( ap.length()+bp.length()>ab.length()+omega )
	{
		return false;
	}	
	return true;

}

void LDIndexLine::setIndex( int index1,int index2 )
{
	Q_ASSERT( index1>=0 );
	Q_ASSERT( index2>=0 );
	Q_ASSERT( index1 != index2 );

	if ( index1<index2 )
	{
		m_index1=index1;
		m_index2=index2;
	}
	else
	{
		//順番を正しく入れ替え
		m_index1=index2;
		m_index2=index1;
	}
}


LDLine LDIndexLine::toLine( const LDPointList& form ) const
{
	Q_ASSERT( form.length() > m_index1 );
	Q_ASSERT( form.length() > m_index2 );

	return LDLine( form.at( m_index1 ),form.at( m_index2 ) );
}

//***************************************
// Serialize
//***************************************
template<class Archive>
void LDIndexLine::serialize( Archive& ar, unsigned int /*version*/ )
{
	LD_SERIALIZE_VALUE( ar, m_index1 );
	LD_SERIALIZE_VALUE( ar, m_index2 );
}
LD_SERIALIZE_IMPL( LDIndexLine );

QDebug operator<<( QDebug dbg, const LDIndexLine& line )
{
	dbg.nospace() << QString( "LDIndexLine(%1,%2)" ).arg( line.getIndex1() ).arg( line.getIndex2() );

	return dbg;
}


} // namespace live2d

