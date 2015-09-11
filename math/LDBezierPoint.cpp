/**
 *
 *  2015/7/5
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDBezierPoint.h"

namespace live2d
{
LDBezierPoint::LDBezierPoint()
{

}

void LDBezierPoint::reset(
		const LDPoint& top,
		const LDPoint& bottom,
		const LDPoint& left,
		const LDPoint& right)
{
	m_top=m_anchor+(top - m_anchor)/4.0f;
	m_bottom=m_anchor+(bottom - m_anchor)/4.0f;
	m_left=m_anchor+(left - m_anchor)/4.0f;
	m_right=m_anchor+(right - m_anchor)/4.0f;
}

void LDBezierPoint::resetToRightAngle(
		const LDPoint& top,
		const LDPoint& bottom,
		const LDPoint& left,
		const LDPoint& right)
{
	reset(top,bottom,left,right);

	m_top.setX(m_anchor.x());
	m_bottom.setX(m_anchor.x());
	m_left.setX(m_anchor.y());
	m_right.setX(m_anchor.y());
}

} // namespace live2d
