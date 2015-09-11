/**
 *
 *  2015/5/26
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once


#include "LDTriangle.h"

namespace live2d {
namespace math {

class TriangleUtil
{
public:
	// 任意の矩形を包含する十分大きな正三角形を求める
	static LDPolygon getHugeTriangle(const LDRectF& rect);

	// 点群を包含する十分大きな正三角形を求める
	static LDPolygon getHugeTriangle(const LDPointList& form);



	//点 p が三角形 t(a,b,c) に含まれるか調べる。onLineがtrueなら線上にあっても範囲内にあるという判断
	static bool containsPoint(const LDPoint& p1, const LDPoint& p2, const LDPoint& p3,const LDPoint& p,bool onLine=false);
	static bool containsPoint(const LDPolygon& t,const LDPoint& p,bool onLine=false);

	//点 p が三角形 t(a,b,c) に含まれるか調べる。
	//点 p が三角形 t の内側にある場合  1 を、
	//　   　三角形 t の線上にある場合 -1 を、
	//　   　三角形 t の外側にある場合  0 を返す。
	static int pointInTriangle(const LDPoint& p1, const LDPoint& p2, const LDPoint& p3,const LDPoint& p);
	
	//点p1 ,p2 ,p3 で構成される三角形が鈍角三角形か判定する
	static bool isObtuseTriangle(const LDPoint& p1, const LDPoint& p2, const LDPoint& p3);
	
	//点p1 ,p2 ,targetで構成される三角形で、traget点での角度が鈍角か判定
	static bool isObtuseAngle(LDPoint p1, LDPoint p2, LDPoint target);
	
	//点p1 ,p2 ,p3 から三角形が作れるかを判定(3点が一直線上にないか判定)
	static bool isTriangle(LDPoint p1, LDPoint p2, LDPoint p3);

	//三角形の高さ (底辺p12からp3までの高さ)
	static float getTriangleHeight(const LDPoint& p1,const LDPoint& p2,const LDPoint& p3);
	//s1,s2,s3で構成される三角形とt1,t2,t3が相似な三角形であるとき、、s1とs2の線とt1とt1を対応する線分である場合のt3の点を返す
	static LDPoint getSimilarityTrianglePoint(const LDPoint& s0,const LDPoint& s1,const LDPoint& s2,const LDPoint& t0,const LDPoint& t1);
};

} // namespace math
} // namespace live2d


