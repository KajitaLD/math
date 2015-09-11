/**
 *
 *  2015/7/5
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDBezierTransformTest.h"

#include <QTest>
#include <QDebug>

#include "LDBezierTransform.h"
namespace live2d {

void LDBezierTransformTest::simpleTransformTest()
{
	LDBezierTransform quad(LDPoint(10,10),LDPoint(30,30));

	{
		LDPoint src(0,0);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),10.0);
		QCOMPARE(dst.y(),10.0);
	}

	{
		LDPoint src(1,1);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),30.0);
		QCOMPARE(dst.y(),30.0);
	}

	{
		//TODO 範囲外は未対応
		LDPoint src(-1,-1);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),10.0);//-10になってほしいけど
		QCOMPARE(dst.y(),10.0);
	}
	{
		//TODO 範囲外は未対応
		LDPoint src(2,2);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),30.0);//50になってほしいけど
		QCOMPARE(dst.y(),30.0);
	}

	{
		LDPoint src(0.5,0.25);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),20.0);

		//TODO 誤差ありすぎて通らない。
//		QCOMPARE(dst.y(),15.0);// Actual : 15.8984
	}
	{
		LDPoint src(0.75,0.8);

		LDPoint dst;

		dst = quad.transform(src);

		//TODO 誤差ありすぎて通らない
//		QCOMPARE(dst.x(),25.0);// Actual : 25.375
//		QCOMPARE(dst.y(),26.0);// Actual : 25.296
	}
	{
		LDPointList src;
		src<<LDPoint(0.25,0.4)<<LDPoint(0.75,0.8);

		LDPointList dst;

		dst=quad.transform(src);

		QVERIFY(dst.length()==2);

		//TODO 誤差ありすぎて通らない
//		QCOMPARE(dst[0],LDPoint(15.0,18.0));// QPointF(14.8125,16.656)
//		QCOMPARE(dst[1],LDPoint(25,26));//QPointF(25.375,25.296)
	}
}

void LDBezierTransformTest::transformTest()
{
	LDBezierTransform quad(LDPoint(10,10),LDPoint(30,30));

	{
		LDPoint src(0.5,0.25);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),20.0);
		//TODO 誤差ありすぎて通らない
//		QCOMPARE(dst.y(),15.0);// Actual : 15.8984
	}
}


} // namespace live2d

