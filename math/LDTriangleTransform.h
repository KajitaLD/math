/**
 *
 *  2015/6/28
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once
#include "private/LDMath_private.h"

namespace live2d {

class LDTriangleTransform
{
public:
	LDTriangleTransform(const LDPoint& p0,const LDPoint& p1,const LDPoint& p2);

	LDPoint transform(float tx,float ty)const;
	LDPoint transformOneMinusT(float tx,float ty)const;

	LDPoint inverseTransform(float x,float y)const;
	LDPoint inverseTransformOneMinusT(float x,float y)const;
private:
	//時計回り
	LDPoint m_p0;
	LDPoint m_p1;
	LDPoint m_p2;
};

} // namespace live2d


