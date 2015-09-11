/**
 *
 *  2015/5/26
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include "private/LDMath_private.h"

#include "LDTriangle.h"
#include "PointUtil.h"

namespace live2d {

struct LDCircle
{
public:
	LDCircle(LDPoint center,float radius);

	LDPoint center;
	float radius;

	//円に外接する正三角形を求める
	LDPolygon getCircumscribedTriangle()
	{
		float x=center.x();
		float y=center.y();

		// 重心は、円の中心に等しい
		// 一辺の長さは 2√3･r
		float x1 = (float) (x - qSqrt(3) * radius);
		float y1 = (float) (y - radius);
		LDPoint p1(x1,y1);

		float x2 = (float) (x + qSqrt(3) * radius);
		float y2 = (float) (y - radius);
		LDPoint p2(x2,y2);

		float x3 = (float) x;
		float y3 = (float) (y + 2 * radius);
		LDPoint p3(x3,y3);

		return LDPolygon({p1,p2,p3});
	}

	// 三角形を与えてその外接円を求める
	static LDCircle getCircumscribedCirclesOfTriangle(const LDPointList& form,const LDTriangle& t )
	{
		// 三角形の各頂点座標を (x1, y1), (x2, y2), (x3, y3) とし、
		// その外接円の中心座標を (x, y) とすると、
		//     (x - x1) * (x - x1) + (y - y1) * (y - y1)
		//   = (x - x2) * (x - x2) + (y - y2) * (y - y2)
		//   = (x - x3) * (x - x3) + (y - y3) * (y - y3)
		// より、以下の式が成り立つ
		//
		// x = { (y3 - y1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)
		//     + (y1 - y2) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1)} / c
		//
		// y = { (x1 - x3) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)
		//     + (x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1)} / c
		//
		// ただし、
		//   c = 2 * {(x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)}

		LDPoint p1 = t.getPoint1(form);
		LDPoint p2 = t.getPoint2(form);
		LDPoint p3 = t.getPoint3(form);
		float x1 = (float) p1.x();
		float y1 = (float) p1.y();
		float x2 = (float) p2.x();
		float y2 = (float) p2.y();
		float x3 = (float) p3.x();
		float y3 = (float) p3.y();

		float c = 2.0f * ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1));
		float x = ((y3 - y1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)
				+ (y1 - y2) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1)) / c;
		float y = ((x1 - x3) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)
				+ (x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1)) / c;

		LDPoint center(x, y);

		// 外接円の半径 r は、半径から三角形の任意の頂点までの距離に等しい
		double r =  math::PointUtil::distance(center, p1);

		return LDCircle(center, r);
	}
};

} // namespace live2d


