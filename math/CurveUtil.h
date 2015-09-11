/**
 *
 *  2015/7/5
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include "LDBezierPoint.h"
namespace live2d
{

class CurveUtil
{
public:
	CurveUtil();

	//2次ベジエ曲線上の点を求める。t=0:開始点 t=1:終了点
	static LDPoint quadraticBezierPoint(
		const LDPoint& start,
		const LDPoint& control,
		const LDPoint& end,float t )
	{
		double t1=( 1-t )*( 1-t );
		double t2=2 * t * ( 1-t );
		double t3=t*t;

		return t1 * start
			   + t2 * control
			   + t3 * end;
	}

	//3次ベジエ曲線上の点を求める。t=0:開始点 t=1:終了点
	static LDPoint cubicBezierPoint(
		const LDPoint& start,
		const LDPoint& control1,
		const LDPoint& control2,
		const LDPoint& end,float t )
	{
		double t1=( double )( 1-t )*( 1-t )*( 1-t );
		double t2=( double )3 * t * ( 1-t )* ( 1-t );
		double t3=( double )3*t*t* ( 1-t );
		double t4=( double )t*t*t;

		return t1 * start
			   + t2 * control1
			   + t3 * control2
			   + t4 * end;
	}


	//エルミート曲線上の点を求める。t=0:開始点 t=1:終了点
	static LDPoint cubicHermitePoint(
			const LDPoint& start,
			const LDPoint& startVec,
			const LDPoint& end,
			const LDPoint& endVec,
			float t)
	{
//		P(t) = at3 + bt2 + ct + d
//		a = 2(P0 - P1) + m0 + m1
//		b = -3(P0 - P1) - 2m0 - m1
//		c = m0
//		d = P0
		float t2  = t*t;
		float t3  = t*t*t;
		LDPoint a = 2*(start - end) + startVec + endVec;
		LDPoint b = -3*(start - end) - 2*startVec - endVec;
		return a*t3+b*t2+startVec*t+start;
	}

};

} // namespace live2d


