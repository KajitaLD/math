/**
 *
 *  2015/6/28
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDQuadTransformTest.h"

#include <QTest>
#include <QDebug>

#include "LDQuadTransform.h"
#include "TestUtil.h"
namespace live2d {

void LDQuadTransformTest::simpleTransformTest()
{

	LDQuadTransform quad(LDPoint(10,10),LDPoint(30,30));

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
		LDPoint src(0.5,0.25);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),20.0);
		QCOMPARE(dst.y(),15.0);
	}
	{
		LDPoint src(0.75,0.8);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),25.0);
		QCOMPARE(dst.y(),26.0);
	}
	{
		LDPointList src;
		src<<LDPoint(0.25,0.4)<<LDPoint(0.75,0.8);

		LDPointList dst;

		dst=quad.transform(src);

		QVERIFY(dst.length()==2);

		QCOMPARE(dst[0],LDPoint(15.0,18.0));
		QCOMPARE(dst[1],LDPoint(25,26));
	}

//	{
//		LDGridTransform src(0.5,0.5,0.5,0.5,1,1);

//		LDGridTransform dst;

//		dst=grid.transform(src);

//		QCOMPARE(dst.getPoint(0,0),LDPoint(40,40));
//		QCOMPARE(dst.getPoint(0,1),LDPoint(60,40));
//		QCOMPARE(dst.getPoint(1,1),LDPoint(60,60));
//		QCOMPARE(dst.getPoint(1,0),LDPoint(40,60));
//	}

//	{
//		LDAffineTransform src;
//		src.translate(0.5,0.5);
//		src.rotate(30);
//		src.scale(2,2);

//		LDAffineTransform dst;

//		dst=grid.transform(src);

//		QCOMPARE(dst.getTranslate(),LDPoint(40,40));
	//	}
}

void LDQuadTransformTest::transformTest()
{
	{
		LDQuadTransform quad(LDPoint(10,10),LDPoint(30,30));
		LDPoint src(0.5,0.25);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),20.0);
		QCOMPARE(dst.y(),15.0);
	}

	{
		LDQuadTransform quad(LDPoint(10,10),LDPoint(20,10),LDPoint(100,100),LDPoint(10,20));
		LDPoint src(0.9,0.9);

		LDPoint dst;

		dst = quad.transform(src);

//		QCOMPARE(dst.x(),83.8);
//		QCOMPARE(dst.y(),83.8);
		LDFUZZY_COMPARE(dst.x(),83.8,0.0000001);
		LDFUZZY_COMPARE(dst.y(),83.8,0.0000001);

//		LDFUZZY_COMPARE(dst.x(),83,0.001);
//		LDFUZZY_COMPARE(dst.y(),83,0.001);
	}
}

void LDQuadTransformTest::inverseTransformTest()
{
	{
		LDQuadTransform quad(LDPoint(10,10),LDPoint(30,30));
		LDPoint src(20,15);

		LDPoint dst;

		dst = quad.inverseTransform(src);

		QCOMPARE(dst.x(),0.5);
		QCOMPARE(dst.y(),0.25);
	}
	{
		LDQuadTransform quad(LDPoint(10,10),LDPoint(20,10),LDPoint(100,100),LDPoint(10,20));
		LDPoint src(83.8,83.8);

		LDPoint dst;

		dst = quad.inverseTransform(src);
//		QCOMPARE(dst.x(),0.9);
//		QCOMPARE(dst.y(),0.9);
		LDFUZZY_COMPARE(dst.x(),0.9,0.0000001);
		LDFUZZY_COMPARE(dst.y(),0.9,0.0000001);
	}
	{
		LDQuadTransform quad(LDPoint(10,10),LDPoint(30,30));
		LDPoint src(20,25);

		LDPoint dst;

		dst = quad.inverseTransform(src);

		QCOMPARE(dst.x(),0.5);
		QCOMPARE(dst.y(),0.75);
	}
	{
		//(0,0),(100,100)を90度回転
		LDQuadTransform quad(
					LDPoint(100,0),
					LDPoint(100,100),
					LDPoint(0,100),
					LDPoint(0,0)
					);
		LDPoint src(75,50);

		LDPoint dst;

		dst = quad.inverseTransform(src);
		QCOMPARE(dst.x(),0.5);
		QCOMPARE(dst.y(),0.25);
	}

	{
		//大きめの数字
		LDQuadTransform quad(LDPoint(1024,1024),LDPoint(3500,3500));
		LDPoint src(2000,2000);

		LDPoint dst;

		dst = quad.inverseTransform(src);

		LDFUZZY_COMPARE(dst.x(),0.394184,0.00001);
		LDFUZZY_COMPARE(dst.y(),0.394184,0.00001);
	}
	{
		//斜め
		LDQuadTransform quad(LDPoint(10,10),LDPoint(20,20),LDPoint(20,30),LDPoint(10,20));
		LDPoint src(15,20);

		LDPoint dst;

		dst = quad.inverseTransform(src);

		QCOMPARE(dst.x(),0.5);
		QCOMPARE(dst.y(),0.5);
	}

	{
		LDQuadTransform quad(LDPoint(10.12345,10.12321),LDPoint(20.1102,20.034),LDPoint(20.11111,30.22222),LDPoint(10.232697,20.00008));
		LDPoint src(15.8731,20.5396);

		LDPoint dst;
		LDPoint rest;
		dst = quad.inverseTransform(src);
		rest=quad.transform(dst);

		LDFUZZY_COMPARE(src.x(),rest.x(),0.0000001);
		LDFUZZY_COMPARE(src.y(),rest.y(),0.0000001);
	}
	{
		LDQuadTransform quad(LDPoint(1023.12345,1041.12321),LDPoint(2075.1102,2032.034),LDPoint(2034.11111,3061.22222),LDPoint(1023.232697,2088.00008));
		LDPoint src(1515.8731,2072.5396);

		LDPoint dst;
		LDPoint rest;
		dst = quad.inverseTransform(src);
		rest=quad.transform(dst);

		LDFUZZY_COMPARE(src.x(),rest.x(),0.0000001);
		LDFUZZY_COMPARE(src.y(),rest.y(),0.0000001);
	}
}

void LDQuadTransformTest::rotationTest()
{
	{
		//(0,0),(100,100)を90度回転
		LDQuadTransform quad(
					LDPoint(100,0),
					LDPoint(100,100),
					LDPoint(0,100),
					LDPoint(0,0)
					);
		LDPoint src(0.5,0.25);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),75.0);
		QCOMPARE(dst.y(),50.0);
	}
	{
		//(0,0),(100,100)を180度回転
		LDQuadTransform quad(
					LDPoint(100,100),
					LDPoint(0,100),
					LDPoint(0,0),
					LDPoint(100,0)
					);
		LDPoint src(0.5,0.25);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),50.0);
		QCOMPARE(dst.y(),75.0);
	}
}

void LDQuadTransformTest::extendedTransformTest()
{
	//範囲外補間
	//仕様変更によりこのテストは無効となりました
	return ;
	{
		LDQuadTransform quad(LDPoint(10,10),LDPoint(30,30));

		LDPoint src(-1,-1);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),-10.0);
		QCOMPARE(dst.y(),-10.0);
	}
	{
		LDQuadTransform quad(
					LDPoint(20,20),
					LDPoint(40,21),
					LDPoint(40,60),
					LDPoint(20,60));

		LDPoint src(-1,0.5);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),0.0);
		QCOMPARE(dst.y(),39.5);
	}
	{
		LDQuadTransform quad(LDPoint(10,10),LDPoint(30,30));

		LDPoint src(-1,-1);

		LDPoint dst;

		dst = quad.transform(src,true);//範囲内にクリッピングする

		QCOMPARE(dst.x(),10.0);
		QCOMPARE(dst.y(),10.0);
	}

	{
		LDQuadTransform quad(LDPoint(10,10),LDPoint(30,30));

		LDPoint src(2,2);

		LDPoint dst;

		dst = quad.transform(src);

		QCOMPARE(dst.x(),50.0);
		QCOMPARE(dst.y(),50.0);
	}

	{
		LDQuadTransform quad(LDPoint(10,10),LDPoint(30,30));
		LDPoint src(40,40);

		LDPoint dst;

		dst = quad.inverseTransform(src);

		QCOMPARE(dst.x(),1.5);
		QCOMPARE(dst.y(),1.5);
	}

	{
		LDQuadTransform quad(LDPoint(10,10),LDPoint(30,30));
		LDPoint src(40,40);

		LDPoint dst;

		dst = quad.inverseTransform(src,true);

		QCOMPARE(dst.x(),1.0);
		QCOMPARE(dst.y(),1.0);
	}

	{
		LDQuadTransform quad(LDPoint(10.12345,10.12321),LDPoint(20.1102,20.034),LDPoint(20.11111,30.22222),LDPoint(10.232697,20.00008));
		LDPoint src(45.8731,60.5396);

		LDPoint dst;
		LDPoint rest;
		dst = quad.inverseTransform(src);
		rest=quad.transform(dst);

		LDFUZZY_COMPARE(src.x(),rest.x(),0.0000001);
		LDFUZZY_COMPARE(src.y(),rest.y(),0.0000001);
	}
	{
		LDQuadTransform quad(LDPoint(1023.12345,1041.12321),LDPoint(2075.1102,2032.034),LDPoint(2034.11111,3061.22222),LDPoint(1023.232697,2088.00008));
		LDPoint src(11515.8731,62072.5396);

		LDPoint dst;
		LDPoint rest;
		dst = quad.inverseTransform(src);
		rest=quad.transform(dst);

		LDFUZZY_COMPARE(src.x(),rest.x(),0.0000001);
		LDFUZZY_COMPARE(src.y(),rest.y(),0.0000001);
	}
	{
		LDQuadTransform quad(LDPoint(1023.12345,1041.12321),LDPoint(2075.1102,2032.034),LDPoint(2034.11111,3061.22222),LDPoint(1023.232697,2088.00008));
		LDPoint src(5.8731,72.5396);

		LDPoint dst;
		LDPoint rest;
		dst = quad.inverseTransform(src);
		rest=quad.transform(dst);

		LDFUZZY_COMPARE(src.x(),rest.x(),0.0000001);
		LDFUZZY_COMPARE(src.y(),rest.y(),0.0000001);
	}
}

} // namespace live2d
