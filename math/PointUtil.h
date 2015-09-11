/**
 *
 *  2015/5/21
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include "common.h"
#include "private/LDMath_private.h"

#include <QPointF>
#include <QRect>
#include <QtMath>

namespace live2d {
namespace math {

class PointUtil
{
public:
	//2点が一定差以内(d以下)にあるかどうか。
	template<typename T>
	static bool isNearSimple(const T& a,const T& b,float d)
	{
		if(qAbs(a.x()-b.x()) > d)return false;
		if(qAbs(a.y()-b.y()) > d)return false;

		return true;
	}

	//与えられた点群すべてを含む矩形を取得
	static LDRectF getBoundingRect(const LDPointList& form);

	//文字列にする
	static QString toString(const QPoint& p);
	static QString toStringF(const QPointF& p);

	static bool isHit(const LDPoint& pt,const LDPoint& target,float hitRange)
	{
		return QVector2D(pt).distanceToPoint(QVector2D(target)) <= hitRange;
	}

	static float distance(const LDPoint& a,const LDPoint& b)
	{
		return QVector2D(a).distanceToPoint(QVector2D(b));
	}

	//yが最小の点を探す。複数あるならxが低い方
	static int findMinYPointIndex(const LDPointList& points);

	template <typename P>
	static LDPoint interporate( P p1, P p2, ld_float factor )
	{
		const auto d = ( p2 - p1 ) * factor;
		return p1 + d;
	}

private:
	PointUtil(){}
	~PointUtil(){}
};

} // namespace math
} // namespace live2d



