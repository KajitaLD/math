/**
 *
 *  2015/4/9
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include <QTest>

#include <QString>
#include <QtTest>
#include "LDEulerAnglesTest.h"
#include "LDMathUtilTest.h"
#include "LDMatrix43Test.h"
#include "LDMatrix44Test.h"
#include "LDVector3Test.h"
#include "LDQuatTest.h"
#include "LDIndexLineListTest.h"
#include "TestUtil.h"
#include "TriangulationTest.h"
#include "LDGridTransformTest.h"
#include "LDQuadTransformTest.h"
#include "LDAffineTransformTest.h"
#include "LDTrianglListTest.h"
#include "LDBezierTransformTest.h"
#include "LDSimpleAffineTransformTest.h"
using namespace live2d;
using namespace live2d::math;


int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);
//QGuiApplication a(argc,argv);

	LDTEST( TriangulationTest )

	//BUG: テスト失敗。ld_float がdoubleのときに成功するように作ってある。えー
	LDTEST( LDEulerAnglesTest );
	LDTEST( LDMathUtilTest );
	LDTEST( LDMatrix43Test );
	LDTEST( LDMatrix44Test );
	LDTEST( LDVector3Test);
	LDTEST( LDQuatTest);
	LDTEST( LDIndexLineListTest);
	LDTEST( LDQuadTransformTest);
	LDTEST( LDAffineTransformTest);
	LDTEST( LDSimpleAffineTransformTest);
	LDTEST( LDGridTransformTest);
	LDTEST( LDBezierTransformTest);
	LDTEST( LDTrianglListTest);


}
