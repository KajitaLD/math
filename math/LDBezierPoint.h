/**
 *
 *  2015/7/5
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include "private/LDMath_private.h"
namespace live2d
{

struct LDBezierPoint
{
public:
	LDBezierPoint();

	void reset(
			const LDPoint& top,
			const LDPoint& bottom,
			const LDPoint& left,
			const LDPoint& right);

	void resetToRightAngle(
			const LDPoint& top,
			const LDPoint& bottom,
			const LDPoint& left,
			const LDPoint& right);
public:
	//アンカーポイント
	LDPoint m_anchor;

	//上下左右へのコントロールポイント
	LDPoint m_top;
	LDPoint m_bottom;
	LDPoint m_right;
	LDPoint m_left;


};


} // namespace live2d
