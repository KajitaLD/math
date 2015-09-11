/**
 *
 *  2015/7/3
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once
#include "private/LDMath_private.h"
#include "LDBezierPoint.h"


namespace live2d {

class LDBezierTransform
{
public:
	LDBezierTransform(const LDPoint& topLeft,const LDPoint& bottomRight);

	//時計回りに4点
	LDBezierTransform(const LDPoint& topLeft,const LDPoint& topRight,const LDPoint& bottomRight,const LDPoint& bottomLeft);

	LDPoint transform(const LDPoint& t)const;
	LDPointList transform(const LDPointList& t)const;

	LDPoint transform(float tx,float ty)const;

	//上下左右の曲線上の点を取得
	LDPoint getTopCurvePt(float t)const;
	LDPoint getBottomCurvePt(float t)const;
	LDPoint getLeftCurvePt(float t)const;
	LDPoint getRightCurvePt(float t)const;

	LDPointList getPointList()const;


	//コントロールポイントを隣接するアンカーで自動調節する。隣接アンカーが存在しない方向は反対側を反転して使う
	void resetControlPt();
	void resetTopLeftControlPt();
	void resetTopRightControlPt();
	void resetBottomRightControlPt();
	void resetBottomLeftControlPt();

	LDBezierPoint getTopLeft() const;
	void setTopLeft(const LDBezierPoint& topLeft);

	LDBezierPoint getTopRight() const;
	void setTopRight(const LDBezierPoint& topRight);

	LDBezierPoint getBottomRight() const;
	void setBottomRight(const LDBezierPoint& bottomRight);

	LDBezierPoint getBottomLeft() const;
	void setBottomLeft(const LDBezierPoint& bottomLeft);

private:
	LDBezierPoint m_topLeft;
	LDBezierPoint m_topRight;
	LDBezierPoint m_bottomRight;
	LDBezierPoint m_bottomLeft;

};

QDebug operator<<( QDebug dbg, const LDBezierTransform& quad );

} // namespace live2d


