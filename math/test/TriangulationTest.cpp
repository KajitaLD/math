/**
 *
 *  2015/5/28
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#include <QTest>
#include "TriangulationTest.h"
#include "Triangulation.h"
namespace live2d {
namespace math {

void TriangulationTest::triangulationTest()
{
	{
		//0個の頂点を分割。0個の三角形を取得
		LDPointList form;

		LDTriangleList result=Triangulation::exec(form);

		QCOMPARE(result.length(),0);
	}
	{
		//1個の頂点を分割。0個の三角形を取得
		LDPointList form;
		form<<LDPoint(0,0);
		LDTriangleList result=Triangulation::exec(form);

		QCOMPARE(result.length(),0);
	}
	{
		//2個の頂点を分割。0個の三角形を取得
		LDPointList form;
		form<<LDPoint(0,0)<<LDPoint(1,1);
		LDTriangleList result=Triangulation::exec(form);

		QCOMPARE(result.length(),0);
	}
	{
		//3個の頂点を分割。1個の三角形を取得
		LDPointList form;
		form<<LDPoint(0,0)<<LDPoint(1,1)<<LDPoint(1,0);
		LDTriangleList result=Triangulation::exec(form);

		QCOMPARE(result.length(),1);
		QVERIFY(result[0]==LDTriangle(0,1,2));
	}
	{
		//4個の頂点を分割。2個の三角形を取得
		LDPointList form;
		form<<LDPoint(0,0)<<LDPoint(1,1)<<LDPoint(1,0)<<LDPoint(0,1);
		LDTriangleList result=Triangulation::exec(form);

		QCOMPARE(result.length(),2);
		QVERIFY(result.contains(LDTriangle(0,1,2)));
		QVERIFY(result.contains(LDTriangle(0,1,3)));
	}

//	{
//		LDPointList form;
//		form<<LDPoint(20,0)<<LDPoint(1,1)<<LDPoint(1,0)<<LDPoint(0,1)
//			<<LDPoint(0,15.5)<<LDPoint(11,12)<<LDPoint(1,0)<<LDPoint(100,0.1);
//		LDTriangleList result=Triangulation::exec(form);
//		qDebug()<<result;
//	}
}



} // namespace math
} // namespace live2d

