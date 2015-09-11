/**
 *
 *  2015/5/21
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once
#include "LDTriangleList.h"
#include "LDIndexLineList.h"
#include "LDCircle.h"

namespace live2d {
namespace math {

/**
 * 三角分割
 *
 * 与えられた点群から三角形への分割を生成する
 * すでにある線分を書き換えないように制限できる。(予定)
 *
 * 参考
 *	ドロネー三角形分割
 *	http://www.riken.jp/brict/Ijiri/study/DelaunayTriangulation.htm
 */
class Triangulation
{
public:
	//formに一時的に頂点を追加するためコピーを受け取ります。
	static LDTriangleList exec(LDPointList form);//TODO ,LDProgress progress
//	static LDTriangleList exec(LDPointList& form,LDIndexLineList limitedLines);//TODO ,LDProgress progress

private:
	static void triangulationFromPoint(const LDPointList& form,const LDPoint& p,LDTriangleList& triangles);

	//特定の三角形から始めて、周辺の四角形をフリップすることで分割形状を最適化する。
	static void optimizePolygonSeparate(const LDPointList& form,LDTriangle firstTriangle,LDTriangleList& triangles);

	//四角形のポリゴン割りをフリップ(割り方を変更)。アルゴリズムのための未チェックの線分を返す
	static LDIndexLineList flipTriangles(LDTriangle ta, LDTriangle tb, LDIndexLine l ,LDTriangleList& triangles );

};

} // namespace math
} // namespace live2d



