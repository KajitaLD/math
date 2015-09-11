/**
 *
 *  2015/5/24
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once
#include "LDIndexLine.h"
#include <QStringList>
namespace live2d {

class LDIndexLineList :public QList<LDIndexLine>
{
public:
	LDIndexLineList();
	//インデックス列から線群を生成
	LDIndexLineList(QList<int> indices);
	bool hasIndexLine(LDIndexLine line);
	void sort();
	bool isHit(const LDPointList &form,LDPoint p,float hitRange);

	LDLineList getLines(const LDPointList& points) const;
	LD_SERIALIZABLE;
};

} // namespace live2d

LD_SERIALIZE_CHILD_CLASS_H(live2d::LDIndexLineList)
