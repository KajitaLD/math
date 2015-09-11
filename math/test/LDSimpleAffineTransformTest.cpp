/**
 *
 *  2015/8/1
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDSimpleAffineTransformTest.h"

#include <QTest>
#include <QDebug>
#include <LDSimpleAffineTransform.h>
#include "../serialize/SerializeHelper.h"
#include "LDSerialize.h"
#include "TestUtil.h"

namespace live2d
{
using namespace serialize;

void LDSimpleAffineTransformTest::serializeTest()
{
	const char* name="simpleAffine";
	QSharedPointer<LDSimpleAffineTransform> src( new LDSimpleAffineTransform() );

	//シリアライズ
	SerializeHelper::writeBoostXml( name,src );

	//デシリアライズ
	auto dst=SerializeHelper::readBoostXml<LDSimpleAffineTransform>( name );

	QVERIFY( *src==*dst );
}

void LDSimpleAffineTransformTest::simpleTransformTest()
{
	{
		LDSimpleAffineTransform t;

		t.setOrigin( LDPoint( 100,100 ) );
		t.setRotateDeg( 90 );
		LDPoint src(1,0);
		LDPoint dst;
		dst=t.transform( src );


		QCOMPARE( dst.x(),( double )100 );
		QCOMPARE( dst.y(),( double )100+1 );

	}
	{
		LDSimpleAffineTransform t;

		t.setOrigin( LDPoint( 100,100 ) );
		t.setRotateDeg( 90 );
		t.setScale( 2 );

		LDPoint src(5,5);
		LDPoint dst;

		dst=t.transform( src );

		QCOMPARE( dst.x(),90.0 );
		QCOMPARE( dst.y(),110.0 );

	}
}

void LDSimpleAffineTransformTest::inverseTransformTest()
{
	{
		LDSimpleAffineTransform t;

		t.setOrigin( LDPoint( 100,100 ) );
		t.setRotateDeg( 90 );
		LDPoint src(100,101);
		LDPoint dst;
		dst=t.inverseTransform( src );


		QCOMPARE( dst.x(),( double )1 );
		LDFUZZY_COMPARE( dst.y(),( double )0,0.0001 );

	}
}

} // namespace live2d

