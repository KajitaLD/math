/**
 *
 *  2015/6/6
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDGridTransformTest.h"

#include <QTest>
#include <QDebug>
#include <LDAffineTransform.h>
#include "../serialize/SerializeHelper.h"
#include "LDSerialize.h"
#include "LDGridTransform.h"
#include "TestUtil.h"

namespace live2d {

using namespace serialize;

void LDGridTransformTest::serializeTest()
{
	const char* name="gridMesh";
	QSharedPointer<LDGridTransform> src(new LDGridTransform(0,0,100,100,2,2));

	//シリアライズ
	SerializeHelper::writeBoostXml( name,src );

	//デシリアライズ
	auto dst=SerializeHelper::readBoostXml<LDGridTransform>( name );

	QVERIFY(dst->getGridPoints()==src->getGridPoints());
}

void LDGridTransformTest::simpleTransformTest()
{
	LDGridTransform grid(20,20,40,40,1,1);

	{
		LDPoint src(0.5,0.5);

		LDPoint dst;

		dst = grid.transform(src);

		QCOMPARE(dst.x(),40.0);
		QCOMPARE(dst.y(),40.0);
	}

	{
		LDPointList src;
		src<<LDPoint(0.25,0.25)<<LDPoint(0.75,0.75);

		LDPointList dst;

		dst=grid.transform(src);

		QVERIFY(dst.length()==2);
		QCOMPARE(dst[0],LDPoint(30.0,30));
		QCOMPARE(dst[1],LDPoint(50.0,50));
	}

	{
		LDGridTransform src(0.5,0.5,0.5,0.5,1,1);

		LDGridTransform dst;

		dst=grid.transform(src);

		QCOMPARE(dst.getPoint(0,0),LDPoint(40,40));
		QCOMPARE(dst.getPoint(0,1),LDPoint(60,40));
		QCOMPARE(dst.getPoint(1,1),LDPoint(60,60));
		QCOMPARE(dst.getPoint(1,0),LDPoint(40,60));
	}

	{
		LDAffineTransform src;
		src.translate(0.5,0.5);
		src.rotate(30);
		src.scale(2,2);

		LDAffineTransform dst;

		dst=grid.transform(src);

		QCOMPARE(dst.getTranslate(),LDPoint(40,40));
	}
}

void LDGridTransformTest::getQuadTest()
{


	{
		LDGridTransform grid(20,20,60,60,3,3);
		auto outline=grid.getOutlineQuadTransform();

		QCOMPARE(outline.getTopLeft(),LDPoint(20,20));
		QCOMPARE(outline.getTopRight(),LDPoint(80,20));
		QCOMPARE(outline.getBottomRight(),LDPoint(80,80));
		QCOMPARE(outline.getBottomLeft(),LDPoint(20,80));

		//0行0列目(左上)の四角変形
		auto quad00=grid.getQuadTransform(0,0);
		QCOMPARE(quad00.getTopLeft(),LDPoint(20,20));
		QCOMPARE(quad00.getTopRight(),LDPoint(40,20));
		QCOMPARE(quad00.getBottomRight(),LDPoint(40,40));
		QCOMPARE(quad00.getBottomLeft(),LDPoint(20,40));

		//0行1列目の四角変形
		auto quad01=grid.getQuadTransform(0,1);
		QCOMPARE(quad01.getTopLeft(),LDPoint(40,20));
		QCOMPARE(quad01.getTopRight(),LDPoint(60,20));
		QCOMPARE(quad01.getBottomRight(),LDPoint(60,40));
		QCOMPARE(quad01.getBottomLeft(),LDPoint(40,40));

		//0行2列目の四角変形
		auto quad02=grid.getQuadTransform(0,2);
		QCOMPARE(quad02.getTopLeft(),LDPoint(60,20));
		QCOMPARE(quad02.getTopRight(),LDPoint(80,20));
		QCOMPARE(quad02.getBottomRight(),LDPoint(80,40));
		QCOMPARE(quad02.getBottomLeft(),LDPoint(60,40));

		//1行1列目(中央)の四角変形
		auto quad11=grid.getQuadTransform(1,1);
		QCOMPARE(quad11.getTopLeft(),LDPoint(40,40));
		QCOMPARE(quad11.getTopRight(),LDPoint(60,40));
		QCOMPARE(quad11.getBottomRight(),LDPoint(60,60));
		QCOMPARE(quad11.getBottomLeft(),LDPoint(40,60));

		//2行2列目(右下)の四角変形
		auto quad22=grid.getQuadTransform(2,2);
		QCOMPARE(quad22.getTopLeft(),LDPoint(60,60));
		QCOMPARE(quad22.getTopRight(),LDPoint(80,60));
		QCOMPARE(quad22.getBottomRight(),LDPoint(80,80));
		QCOMPARE(quad22.getBottomLeft(),LDPoint(60,80));
	}

	{
		LDGridTransform grid(20,20,60,60,3,3);
		//列の幅を変更
		grid.setPoint(0,1,LDPoint(35,20));
		grid.setPoint(1,1,LDPoint(35,40));
		grid.setPoint(2,1,LDPoint(35,60));
		grid.setPoint(3,1,LDPoint(35,80));

		grid.setPoint(0,2,LDPoint(50,20));
		grid.setPoint(1,2,LDPoint(50,40));
		grid.setPoint(2,2,LDPoint(50,60));
		grid.setPoint(3,2,LDPoint(50,80));

		auto outline=grid.getOutlineQuadTransform();

		QCOMPARE(outline.getTopLeft(),LDPoint(20,20));
		QCOMPARE(outline.getTopRight(),LDPoint(80,20));
		QCOMPARE(outline.getBottomRight(),LDPoint(80,80));
		QCOMPARE(outline.getBottomLeft(),LDPoint(20,80));

		//0行0列目(左上)の四角変形
		auto quad00=grid.getQuadTransform(0,0);
		QCOMPARE(quad00.getTopLeft(),LDPoint(20,20));
		QCOMPARE(quad00.getTopRight(),LDPoint(35,20));
		QCOMPARE(quad00.getBottomRight(),LDPoint(35,40));
		QCOMPARE(quad00.getBottomLeft(),LDPoint(20,40));

		//1行1列目(中央)の四角変形
		auto quad11=grid.getQuadTransform(1,1);
		QCOMPARE(quad11.getTopLeft(),LDPoint(35,40));
		QCOMPARE(quad11.getTopRight(),LDPoint(50,40));
		QCOMPARE(quad11.getBottomRight(),LDPoint(50,60));
		QCOMPARE(quad11.getBottomLeft(),LDPoint(35,60));

		//2行2列目(右下)の四角変形
		auto quad22=grid.getQuadTransform(2,2);
		QCOMPARE(quad22.getTopLeft(),LDPoint(50,60));
		QCOMPARE(quad22.getTopRight(),LDPoint(80,60));
		QCOMPARE(quad22.getBottomRight(),LDPoint(80,80));
		QCOMPARE(quad22.getBottomLeft(),LDPoint(50,80));
	}
	{
		LDGridTransform grid(20,20,60,60,3,3);
		//行の幅を変更
		grid.setPoint(1,0,LDPoint(20,35));
		grid.setPoint(1,1,LDPoint(40,35));
		grid.setPoint(1,2,LDPoint(60,35));
		grid.setPoint(1,3,LDPoint(80,35));

		grid.setPoint(2,0,LDPoint(20,50));
		grid.setPoint(2,1,LDPoint(40,50));
		grid.setPoint(2,2,LDPoint(60,50));
		grid.setPoint(2,3,LDPoint(80,50));

		auto outline=grid.getOutlineQuadTransform();

		QCOMPARE(outline.getTopLeft(),LDPoint(20,20));
		QCOMPARE(outline.getTopRight(),LDPoint(80,20));
		QCOMPARE(outline.getBottomRight(),LDPoint(80,80));
		QCOMPARE(outline.getBottomLeft(),LDPoint(20,80));

		//0行0列目(左上)の四角変形
		auto quad00=grid.getQuadTransform(0,0);
		QCOMPARE(quad00.getTopLeft(),LDPoint(20,20));
		QCOMPARE(quad00.getTopRight(),LDPoint(40,20));
		QCOMPARE(quad00.getBottomRight(),LDPoint(40,35));
		QCOMPARE(quad00.getBottomLeft(),LDPoint(20,35));

		//1行1列目(中央)の四角変形
		auto quad11=grid.getQuadTransform(1,1);
		QCOMPARE(quad11.getTopLeft(),LDPoint(40,35));
		QCOMPARE(quad11.getTopRight(),LDPoint(60,35));
		QCOMPARE(quad11.getBottomRight(),LDPoint(60,50));
		QCOMPARE(quad11.getBottomLeft(),LDPoint(40,50));

		//2行2列目(右下)の四角変形
		auto quad22=grid.getQuadTransform(2,2);
		QCOMPARE(quad22.getTopLeft(),LDPoint(60,50));
		QCOMPARE(quad22.getTopRight(),LDPoint(80,50));
		QCOMPARE(quad22.getBottomRight(),LDPoint(80,80));
		QCOMPARE(quad22.getBottomLeft(),LDPoint(60,80));
	}
	{
		LDGridTransform grid(20,20,60,60,3,3);

		grid.setPoint(0,1,LDPoint(35,25));
		grid.setPoint(1,0,LDPoint(10,35));
		grid.setPoint(1,1,LDPoint(30,40));

		//0行0列目(左上)の四角変形
		auto quad00=grid.getQuadTransform(0,0);
		QCOMPARE(quad00.getTopLeft(),LDPoint(20,20));
		QCOMPARE(quad00.getTopRight(),LDPoint(35,25));
		QCOMPARE(quad00.getBottomRight(),LDPoint(30,40));
		QCOMPARE(quad00.getBottomLeft(),LDPoint(10,35));

		//1行1列目(中央)の四角変形
		auto quad11=grid.getQuadTransform(1,1);
		QCOMPARE(quad11.getTopLeft(),LDPoint(30,40));
		QCOMPARE(quad11.getTopRight(),LDPoint(60,40));
		QCOMPARE(quad11.getBottomRight(),LDPoint(60,60));
		QCOMPARE(quad11.getBottomLeft(),LDPoint(40,60));


	}
}

void LDGridTransformTest::hitTest()
{
	LDGridTransform grid(20,20,40,40,2,2);

	QVERIFY( ! grid.isPreHit(LDPoint(0,0)));
	QVERIFY( grid.isPreHit(LDPoint(30,30)));
	QVERIFY( grid.isPreHit(LDPoint(19,19),5));
	QVERIFY( ! grid.isHitOutline(LDPoint(0,0),5));
	QVERIFY( grid.isHitOutline(LDPoint(21,21),5));
}

void LDGridTransformTest::inverseTransformTest()
{
	{
		LDGridTransform grid(20,20,40,40,2,2);
		LDPoint src(30,30);

		LDPoint dst;

		dst = grid.inverseTransform(src);

		QCOMPARE(dst.x(),0.25);
		QCOMPARE(dst.y(),0.25);
	}

	{
		LDGridTransform grid(20,20,40,40,2,2);
		LDPointList src;
		src<<LDPoint(30,30)<<LDPoint(50,50);

		LDPointList dst;

		dst=grid.inverseTransform(src);

		QCOMPARE(dst[0],LDPoint(0.25,0.25));
		QCOMPARE(dst[1],LDPoint(0.75,0.75));
	}

	{
		LDGridTransform grid(20,20,40,40,2,2);
		LDGridTransform src(24,24,52-24,52-24,2,2);

		LDGridTransform dst=src;

		auto points=grid.inverseTransform(src.toForm());


		dst.setForm(points);
		LDFUZZY_COMPARE(dst.getPoint(0,0).x(),0.1,0.0000001);
		LDFUZZY_COMPARE(dst.getPoint(2,2).x(),0.8,0.0000001);
		LDFUZZY_COMPARE(dst.getPoint(2,0).x(),0.1,0.0000001);
		LDFUZZY_COMPARE(dst.getPoint(2,0).y(),0.8,0.0000001);
	}

	{
		LDGridTransform grid(20.53125,20.62423,40.614312,40.94645,2,2);
		LDGridTransform src(24.0134623,24.9143,52-24.090023,52-24.00001,2,2);

		LDGridTransform dst=src;

		auto points=grid.inverseTransform(src.toForm());
		auto rest=grid.transform(points);

		dst.setForm(points);
		QVERIFY(LDMathUtil::fuzzyCompare(rest,src.toForm(),0.0000001));
	}
	{
		LDGridTransform grid(2530.53125,2540.62423,4015.614312,4026.94645,2,2);
		LDGridTransform src(2594.0134623,2594.9143,5274-2594.090023,5276-2594.00001,2,2);

		LDGridTransform dst=src;

		auto points=grid.inverseTransform(src.toForm());
		auto rest=grid.transform(points);

		dst.setForm(points);
		QVERIFY(LDMathUtil::fuzzyCompare(rest,src.toForm(),0.0000001));
	}
	{
		LDGridTransform grid(
					LDPoint(20.53125,20.62423)
					,LDPoint(40.53125,20.62423)
					,LDPoint(45.53125,45.62423)
					,LDPoint(20.614312,40.94645),2,2);
		LDGridTransform src(34.0134623,24.9143,52-24.090023,52-24.00001,8,8);

		LDGridTransform dst=src;

		auto points=grid.inverseTransform(src.toForm());
		auto rest=grid.transform(points);

		dst.setForm(points);
		QVERIFY(LDMathUtil::fuzzyCompare(rest,src.toForm(),0.0000001));
	}
	{
		LDGridTransform grid(
					LDPoint(2012.53125,2051.62423)
					,LDPoint(4097.53125,2033.62423)
					,LDPoint(4575.53125,4566.62423)
					,LDPoint(2062.614312,4000.94645),2,2);
		LDGridTransform src(3444.0134623,2442.9143,5242-2412.090023,5211-2467.00001,8,8);

		LDGridTransform dst=src;

		auto points=grid.inverseTransform(src.toForm());
		auto rest=grid.transform(points);

		dst.setForm(points);
		QVERIFY(LDMathUtil::fuzzyCompare(rest,src.toForm(),0.0000001));
	}
}

void LDGridTransformTest::extendedTransformTest()
{
	{
		//拡張したGridの取得
		LDGridTransform src(20,20,40,40,3,3);
		LDGridTransform dst=src.createExtendedGrid();

		QCOMPARE(dst.getRow(),4);
		QCOMPARE(dst.getColumn(),4);
		QCOMPARE(dst.getPoint(0,0),LDPoint(-20,-20));
		QCOMPARE(dst.getPoint(0,1),LDPoint(10,-20));
		QCOMPARE(dst.getPoint(0,2),LDPoint(40,-20));
		QCOMPARE(dst.getPoint(0,3),LDPoint(70,-20));
		QCOMPARE(dst.getPoint(0,4),LDPoint(100,-20));
		QCOMPARE(dst.getPoint(1,1),LDPoint(20,20));
	}

	{
		//範囲外 順変換 クリッピング
		LDGridTransform grid(20,20,40,40,1,1);
		LDPoint src(-1,-1);

		LDPoint dst;

		dst = grid.transform(src,true);

		QCOMPARE(dst.x(),20.0);
		QCOMPARE(dst.y(),20.0);
	}
	{
		//範囲外 順変換
		LDGridTransform grid(20,20,40,40,1,1);
		LDPoint src(-1,-1);

		LDPoint dst;

		dst = grid.transform(src);

		QCOMPARE(dst.x(),-20.0);
		QCOMPARE(dst.y(),-20.0);
	}
	{
		//範囲外 順変換
		LDGridTransform grid(20,20,40,40,1,1);
		LDPoint src(-10,-10);

		LDPoint dst;

		dst = grid.transform(src);

		QCOMPARE(dst.x(),-380.0);
		QCOMPARE(dst.y(),-380.0);
	}
	{
		//範囲外 逆変換 クリッピング
		LDGridTransform grid(20,20,40,40,2,2);
		LDPoint src(-20,-20);

		LDPoint dst;

		dst = grid.inverseTransform(src,true);

		QCOMPARE(dst.x(),0.0);
		QCOMPARE(dst.y(),0.0);
	}
	{
		//範囲外 逆変換
		LDGridTransform grid(20,20,40,40,2,2);
		LDPoint src(-20,-20);

		LDPoint dst;

		dst = grid.inverseTransform(src);

		QCOMPARE(dst.x(),-1.0);
		QCOMPARE(dst.y(),-1.0);
	}

	{
		LDGridTransform grid(
					LDPoint(20.53125,20.62423)
					,LDPoint(40.53125,20.62423)
					,LDPoint(45.53125,45.62423)
					,LDPoint(20.614312,40.94645),2,2);
		LDGridTransform src(3425.0134623,2412.9143,5252-2412.090023,5212-2451.00001,2,8);

		LDGridTransform dst=src;

		auto points=grid.inverseTransform(src.toForm());
		auto rest=grid.transform(points);

		dst.setForm(points);
		QVERIFY(LDMathUtil::fuzzyCompare(rest,src.toForm(),0.0000001));
	}
	{
		LDGridTransform grid(
					LDPoint(2012.53125,2051.62423)
					,LDPoint(4097.53125,2033.62423)
					,LDPoint(4575.53125,4566.62423)
					,LDPoint(2062.614312,4000.94645),2,2);
		LDGridTransform src(34.0134623,24.9143,52-24.090023,52-24.00001,8,2);

		LDGridTransform dst=src;

		auto points=grid.inverseTransform(src.toForm());
		auto rest=grid.transform(points);

		dst.setForm(points);
		QVERIFY(LDMathUtil::fuzzyCompare(rest,src.toForm(),0.0000001));
	}
}

} // namespace live2d

