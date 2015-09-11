/**
 *
 *  2015/5/21
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include <QLine>
#include <QVector2D>

#include "private/LDMath_private.h"
#include "LDIndexLine.h"

namespace live2d {
namespace math {

class LineUtil
{
public:
	LineUtil();
	~LineUtil();

	//2つの線分の交点を求める。
	static LDPoint getCrossPoint(LDPoint a0,LDPoint a1,LDPoint b0,LDPoint b1,bool &isCross)
	{
		//TODO コピペコード
		double ksi, eta, delta;
		double ramda, mu;

		ksi = ( b1.y()-b0.y() )*( b1.x()-a0.x() ) -
			( b1.x()-b0.x() )*( b1.y()-a0.y() );

		eta = ( a1.x()-a0.x() )*( b1.y()-a0.y() ) -
			( a1.y()-a0.y() )*( b1.x()-a0.x() );

		delta = ( a1.x()-a0.x() )*( b1.y()-b0.y() ) -
			( a1.y()-a0.y() )*( b1.x()-b0.x() );

		ramda = ksi / delta;
		mu    = eta / delta;

		if ( ( ramda >= 0 && ramda <= 1 ) && ( mu >= 0 && mu <= 1 ) )
		{
			float x= a0.x() + ramda*( a1.x()-a0.x() );
			float y= a0.y() + ramda*( a1.y()-a0.y() );

			isCross=true;
			return LDPoint(x,y);
		}

		isCross=false;
		return LDPoint(0,0);
	}

	static LDPoint getCrossPoint(const LDLine& a,const LDLine& b,bool &isCross)
	{
		return getCrossPoint(LDPoint(a.p1()),LDPoint(a.p2()),LDPoint(b.p1()),LDPoint(b.p2()),isCross);
	}

	static LDPoint getCrossPoint(const LDIndexLine& a,const LDIndexLine& b,const LDPointList& form,bool &isCross)
	{
		return getCrossPoint(a.toLine(form),b.toLine(form),isCross);
	}


};

} // namespace math
} // namespace live2d



