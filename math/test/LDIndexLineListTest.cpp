/**
 *
 *  2015/5/24
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDIndexLineListTest.h"

#include <QTest>
#include <QDebug>
#include "../serialize/SerializeHelper.h"
#include "LDIndexLineList.h"
#include "LDSerialize.h"
namespace live2d {

using namespace serialize;


void LDIndexLineListTest::serializeTest()
{
	const char* name="lineList";
	QSharedPointer<LDIndexLineList> src(new LDIndexLineList);
	src->push_back(LDIndexLine(0,1));

	//シリアライズ
	SerializeHelper::writeBoostXml( name,src );

	//デシリアライズ
	auto dst=SerializeHelper::readBoostXml<LDIndexLineList>( name );

	QVERIFY(*(dst.data())==*(src.data()));
}

void LDIndexLineListTest::hitTest()
{
	LDIndexLineList lines;
	LDIndexLine line_1(0,1);
	LDIndexLine line_2(1,2);
	LDIndexLine line_3(2,3);
	LDIndexLine line_4(3,0);
	lines<<line_1;
	lines<<line_2;
	lines<<line_3;
	lines<<line_4;

	LDPointList points;
	points.push_back(LDPoint(0,0));
	points.push_back(LDPoint(100,0));
	points.push_back(LDPoint(100,100));
	points.push_back(LDPoint(0,100));
	
	
	QCOMPARE(lines.isHit(points, LDPoint(0,0),1),true);//頂点上
	QCOMPARE(lines.isHit(points, LDPoint(50,0),1),true);//線上
	QCOMPARE(lines.isHit(points, LDPoint(50,1),3),true);//線からちょっと離れたところ
	QCOMPARE(lines.isHit(points, LDPoint(50,4),3),false);//線から範囲外に離れたところ
	QCOMPARE(lines.isHit(points, LDPoint(200,0),3),false);//線の延長戦上に離れたところ
	QCOMPARE(lines.isHit(points, LDPoint(200,1),3),false);//線の延長戦上に離れたところ
	
	
	
	
	
}

void LDIndexLineListTest::constructTest()
{
	QList<int> int_list;
	int_list.push_back(0);
	int_list.push_back(1);
	int_list.push_back(2);	
	int_list.push_back(3);
//	int_list.push_back(0);
	
	
	LDIndexLineList list(int_list);
	
	
	
	LDIndexLineList compare;
	compare.push_back(LDIndexLine(0,1));
	compare.push_back(LDIndexLine(1,2));
	compare.push_back(LDIndexLine(2,3));
	compare.push_back(LDIndexLine(3,0));
	
	QCOMPARE(list,compare);
	
	
}

} // namespace live2d

