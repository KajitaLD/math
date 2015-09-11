/**
 *
 *  2015/7/3
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDBezierTransform.h"
#include "CurveUtil.h"
#include "LDMathUtil.h"

namespace live2d {

QDebug operator<<( QDebug dbg, const LDBezierTransform& quad )
{
	dbg.nospace() << quad.getPointList();

	return dbg;
}

LDBezierTransform::LDBezierTransform( const LDPoint& topLeft, const LDPoint& bottomRight )
{
	m_topLeft.m_anchor=topLeft;
	m_bottomRight.m_anchor=bottomRight;

	m_topRight.m_anchor.setX( bottomRight.x() );
	m_topRight.m_anchor.setY( topLeft.y() );

	m_bottomLeft.m_anchor.setX( topLeft.x() );
	m_bottomLeft.m_anchor.setY( bottomRight.y() );

	resetControlPt();
}

LDBezierTransform::LDBezierTransform( const LDPoint& topLeft, const LDPoint& topRight, const LDPoint& bottomRight, const LDPoint& bottomLeft )
{
	m_topLeft.m_anchor=topLeft;
	m_bottomRight.m_anchor=bottomRight;
	m_topRight.m_anchor=topRight;
	m_bottomLeft.m_anchor=bottomLeft;
	resetControlPt();
}


LDPoint LDBezierTransform::transform( const LDPoint& t ) const
{
	return transform( t.x(),t.y() );
}

LDPointList LDBezierTransform::transform( const LDPointList& pList ) const
{
	LDPointList	result;
	foreach ( const auto& pt, pList )
	{
		result.push_back( transform( pt ) );
	}
	return result;
}


LDPoint LDBezierTransform::transform( float tx, float ty ) const
{
	//TODO 範囲外計算は未対応
	tx=LDMathUtil::clamp(tx,0.0f,1.0f);
	ty=LDMathUtil::clamp(ty,0.0f,1.0f);

	LDPoint top=getTopCurvePt(tx);
	LDPoint bottom=getBottomCurvePt(tx);
	LDPoint left=getLeftCurvePt(ty);
	LDPoint right=getRightCurvePt(ty);

	return LDMathUtil::lerp2D(left,right,tx,top,bottom,ty);
}

LDPoint LDBezierTransform::getTopCurvePt(float t)const
{
	return CurveUtil::cubicBezierPoint(
				m_topLeft.m_anchor,
				m_topLeft.m_right,
				m_topRight.m_left,
				m_topRight.m_anchor,t);
}

LDPoint LDBezierTransform::getBottomCurvePt(float t)const
{
	return CurveUtil::cubicBezierPoint(
				m_bottomLeft.m_anchor,
				m_bottomLeft.m_right,
				m_bottomRight.m_left,
				m_bottomRight.m_anchor,t);
}

LDPoint LDBezierTransform::getLeftCurvePt(float t)const
{
	return CurveUtil::cubicBezierPoint(
				m_topLeft.m_anchor,
				m_topLeft.m_bottom,
				m_bottomLeft.m_top,
				m_bottomLeft.m_anchor,t);
}

LDPoint LDBezierTransform::getRightCurvePt(float t)const
{
	return CurveUtil::cubicBezierPoint(
				m_topRight.m_anchor,
				m_topRight.m_bottom,
				m_bottomRight.m_top,
				m_bottomRight.m_anchor,t);
}


LDPointList LDBezierTransform::getPointList() const
{
	LDPointList result;
	result.push_back( m_topLeft.m_anchor );
	result.push_back( m_topRight.m_anchor );
	result.push_back( m_bottomRight.m_anchor );
	result.push_back( m_bottomLeft.m_anchor );

	return result;
}


void LDBezierTransform::resetControlPt()
{
	resetTopLeftControlPt();
	resetTopRightControlPt();
	resetBottomRightControlPt();
	resetBottomLeftControlPt();
}

void LDBezierTransform::resetTopLeftControlPt()
{
	m_topLeft.reset(m_topLeft.m_anchor-m_bottomLeft.m_anchor
					,m_bottomLeft.m_anchor
					,m_topLeft.m_anchor-m_topRight.m_anchor
					,m_topRight.m_anchor);
}

void LDBezierTransform::resetTopRightControlPt()
{
	m_topRight.reset(m_topRight.m_anchor-m_bottomRight.m_anchor
					,m_bottomRight.m_anchor
					,m_topLeft.m_anchor
					,m_topRight.m_anchor-m_topLeft.m_anchor);
}

void LDBezierTransform::resetBottomRightControlPt()
{
	m_bottomRight.reset(m_topRight.m_anchor
					,m_bottomRight.m_anchor-m_topRight.m_anchor
					,m_bottomLeft.m_anchor
					,m_bottomRight.m_anchor-m_bottomLeft.m_anchor);
}

void LDBezierTransform::resetBottomLeftControlPt()
{
	m_bottomLeft.reset(m_topLeft.m_anchor
					,m_bottomLeft.m_anchor-m_topLeft.m_anchor
					,m_bottomLeft.m_anchor-m_bottomRight.m_anchor
					   ,m_bottomRight.m_anchor);
}

LDBezierPoint LDBezierTransform::getTopLeft() const
{
	return m_topLeft;
}

void LDBezierTransform::setTopLeft(const LDBezierPoint& topLeft)
{
	m_topLeft = topLeft;
}
LDBezierPoint LDBezierTransform::getTopRight() const
{
	return m_topRight;
}

void LDBezierTransform::setTopRight(const LDBezierPoint& topRight)
{
	m_topRight = topRight;
}
LDBezierPoint LDBezierTransform::getBottomRight() const
{
	return m_bottomRight;
}

void LDBezierTransform::setBottomRight(const LDBezierPoint& bottomRight)
{
	m_bottomRight = bottomRight;
}
LDBezierPoint LDBezierTransform::getBottomLeft() const
{
	return m_bottomLeft;
}

void LDBezierTransform::setBottomLeft(const LDBezierPoint& bottomLeft)
{
	m_bottomLeft = bottomLeft;
}






} // namespace live2d

