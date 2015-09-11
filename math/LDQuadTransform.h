/**
 *
 *  2015/6/11
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include "private/LDMath_private.h"


namespace live2d
{
class LDQuadTransform
{
public:
	LDQuadTransform(const LDPoint& topLeft,const LDPoint& bottomRight);

	//時計回りに4点
	LDQuadTransform(const LDPoint& topLeft,const LDPoint& topRight,const LDPoint& bottomRight,const LDPoint& bottomLeft);

	//clipがtrueのときは必ず範囲内にクリッピングされる
	LDPoint transform(const LDPoint& t,bool clip=false)const;
	LDPointList transform(const LDPointList& t,bool clip=false)const;
	LDPoint transform(double tx, double ty, bool clip=false)const;

	LDPoint inverseTransform(const LDPoint& pt,bool clip=false)const;
	LDPointList inverseTransform(const LDPointList& pt,bool clip=false)const;
	LDPoint inverseTransform(double x,double y,bool clip=false)const;

	//マッピングされた座標系に含まれるかどうか
	bool contains(const LDPoint& map)const;
	QPolygonF getPolygon()const;

	LDPointList getPointList()const;

	LDPoint getTopLeft() const;
	LDPoint getTopRight() const;
	LDPoint getBottomRight() const;
	LDPoint getBottomLeft() const;

private:
	LDPoint m_topLeft;
	LDPoint m_topRight;
	LDPoint m_bottomRight;
	LDPoint m_bottomLeft;

};

QDebug operator<<( QDebug dbg, const LDQuadTransform& quad );

} // namespace live2d

