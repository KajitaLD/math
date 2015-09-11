/**
 * 	
 *  2015/7/2
 *	Imai
 *  
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDTrianglListTest.h"
#include <QTest>
#include <QDebug>
#include <LDTriangleList.h>
namespace live2d {

LDTriangleList simpleTriangle(){
	LDTriangleList triangles;
	LDTriangle t1(0,1,2);
	triangles.push_back(t1);
	return triangles;	
}


void LDTrianglListTest::findTest_simple()
{
	LDTriangleList triangles=simpleTriangle();	
	LDTriangleList compare=simpleTriangle();
	LDIndexLine line(0,2);
	LDTriangleList resulut=triangles.find(line);
	QCOMPARE(resulut,compare);
	
}

void LDTrianglListTest::toIndexLineListTest_simple()
{
	LDTriangleList triangles=simpleTriangle();

	LDIndexLineList compare;
	LDIndexLine line_1(0,1);
	LDIndexLine line_2(1,2);
	LDIndexLine line_3(2,0);	
	compare.push_back(line_1);
	compare.push_back(line_2);
	compare.push_back(line_3);
	
	LDIndexLineList result= triangles.toIndexLineList();
	
	QCOMPARE(result,compare);
}

void LDTrianglListTest::getOutlinePointIndicesTest_simple()
{
	LDTriangleList triangles=simpleTriangle();
	
	LDPointList points;
	points.push_back(LDPoint(0,0));
	points.push_back(LDPoint(0,100));	
	points.push_back(LDPoint(100,100));
	
	QList<int> compare;
	compare.push_back(0);
	compare.push_back(1);
	compare.push_back(2);
	
	QList<int> result=triangles.getOutlinePointIndices(points);
	
	QCOMPARE(result,compare);	
}

void LDTrianglListTest::getOutlinePointsTest_simple()
{
	LDTriangleList triangles=simpleTriangle();
	LDPointList points;
	points.push_back(LDPoint(0,0));
	points.push_back(LDPoint(0,100));	
	points.push_back(LDPoint(100,100));
	
	LDPointList compare=points;
	
	LDPointList result=triangles.getOutlinePoints(points);

	QCOMPARE(result,compare);	
	
	
}

void LDTrianglListTest::getOutlinePolygonTest_simple()
{
	LDTriangleList triangles=simpleTriangle();
	LDPointList points;
	points.push_back(LDPoint(0,0));
	points.push_back(LDPoint(0,100));	
	points.push_back(LDPoint(100,100));
	
	QPolygonF compare;
	compare.push_back(LDPoint(0,0));
	compare.push_back(LDPoint(0,100));
	compare.push_back(LDPoint(100,100));
	
	QPolygonF result=triangles.getOutlinePolygon(points);
	
	QCOMPARE(result,compare);	
	
}

void LDTrianglListTest::getRelatedTrianglesTest_simple()
{
	LDTriangleList triangles=simpleTriangle();

	LDTriangleList compare=simpleTriangle();
	
	LDTriangleList result = triangles.getRelatedTriangles(0);
	QCOMPARE(result,compare);	
	
}

void LDTrianglListTest::getRelatedLinesTest_simple()
{
	LDTriangleList triangles=simpleTriangle();
	LDIndexLineList compare;
	compare.push_back(LDIndexLine(0,1));
	compare.push_back(LDIndexLine(0,2));
	
	LDIndexLineList result=triangles.getRelatedLines(0);
	QCOMPARE(result,compare);	
	
	
}

void LDTrianglListTest::getRelatedPointIndicesTest_simple()
{
	LDTriangleList triangles=simpleTriangle();
	QList<int> compare;
	compare.push_back(1);
	compare.push_back(2);
	
	QList<int> result=triangles.getRelatedPointIndices(0);
	QCOMPARE(result,compare);	
		
}

} // namespace live2d
