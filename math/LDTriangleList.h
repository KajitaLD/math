/**
 *
 *  2015/5/24
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once
#include "LDTriangle.h"
#include "LDIndexLineList.h"

namespace live2d {

class LDTriangleList:public QList<LDTriangle>
{
public:
	LDTriangleList();

	//すべての線分から三角形を再構成
	void update(const LDIndexLineList& lines);
	void setClockWise(const LDPointList& points,ClockWise cw);
	LDTriangleList find(const LDIndexLine& line)const;
	LDIndexLineList toIndexLineList()const;
	//頂点のインデックスから関連する三角形を削除
	void removePoint(int pointIndex);

	//外周の頂点インデックスを取得。yが一番小さい点から時計周りで取得。
	QList<int> getOutlinePointIndices(const LDPointList& points)const;
	LDPointList getOutlinePoints(const LDPointList& points)const;
	QPolygonF getOutlinePolygon(const LDPointList& points)const;

	//その頂点を含む三角形リストを取得
	LDTriangleList getRelatedTriangles(int pointIndex)const;
	//その頂点を含む線分リストを取得
	LDIndexLineList getRelatedLines(int pointIndex)const;
	//その頂点と接続される点のリストを取得
	QList<int> getRelatedPointIndices(int pointIndex)const;

	LDLineList getLines(const LDPointList& points) const;
private:
	//特定の線分から隣接する三角形を作成
	QList<LDTriangle> create(int index,const LDIndexLineList& lines);

	LD_SERIALIZABLE;
};

} // namespace live2d

LD_SERIALIZE_CHILD_CLASS_H(live2d::LDTriangleList)

