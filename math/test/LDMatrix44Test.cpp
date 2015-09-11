#include "LDMatrix44Test.h"
#include "../serialize/SerializeHelper.h"

namespace live2d
{
//------ EMatrix44.cpp ------
void LDMatrix44Test::identityTest()
{
	LDMatrix44 actual;
	LDMatrix44 expected;
	//ld_float delta = 0.00001f;

	// 単位行列に初期化できているかテスト
	expected.m11 = 1.0f;
	expected.m12 = 0.0f;
	expected.m13 = 0.0f;
	expected.m14 = 0.0f;
	expected.m21 = 0.0f;
	expected.m22 = 1.0f;
	expected.m23 = 0.0f;
	expected.m24 = 0.0f;
	expected.m31 = 0.0f;
	expected.m32 = 0.0f;
	expected.m33 = 1.0f;
	expected.m34 = 0.0f;
	expected.m41 = 0.0f;
	expected.m42 = 0.0f;
	expected.m43 = 0.0f;
	expected.m44 = 1.0f;
	actual.identity();
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m14, actual.m14 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m24, actual.m24 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m34, actual.m34 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );
	QCOMPARE( expected.m44, actual.m44 );
}

void LDMatrix44Test::setMatrixTest()
{
	LDMatrix44 matrix;
	LDMatrix44 actual;
	LDMatrix44 expected;
	//ld_float delta = 0.00001f;
	ld_float m[16];

	// EMatrix44::setMatrix( const ld_float* _m )　のテスト
	for ( int i = 0; i < 16; ++i )
	{
		m[i] = 1.0f;
	}
	actual.setMatrix( m );
	expected.m11 = 1.0f;
	expected.m12 = 1.0f;
	expected.m13 = 1.0f;
	expected.m14 = 1.0f;
	expected.m21 = 1.0f;
	expected.m22 = 1.0f;
	expected.m23 = 1.0f;
	expected.m24 = 1.0f;
	expected.m31 = 1.0f;
	expected.m32 = 1.0f;
	expected.m33 = 1.0f;
	expected.m34 = 1.0f;
	expected.m41 = 1.0f;
	expected.m42 = 1.0f;
	expected.m43 = 1.0f;
	expected.m44 = 1.0f;
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m14, actual.m14 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m24, actual.m24 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m34, actual.m34 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );
	QCOMPARE( expected.m44, actual.m44 );

	// EMatrix43::setMatrix( const EMatrix43 &m2 )　のテスト
	for ( int i = 0; i < 16; ++i )
	{
		m[i] = 2.0f;
	}
	matrix.setMatrix( m );
	actual.setMatrix( matrix );
	expected.m11 = 2.0f;
	expected.m12 = 2.0f;
	expected.m13 = 2.0f;
	expected.m14 = 2.0f;
	expected.m21 = 2.0f;
	expected.m22 = 2.0f;
	expected.m23 = 2.0f;
	expected.m24 = 2.0f;
	expected.m31 = 2.0f;
	expected.m32 = 2.0f;
	expected.m33 = 2.0f;
	expected.m34 = 2.0f;
	expected.m41 = 2.0f;
	expected.m42 = 2.0f;
	expected.m43 = 2.0f;
	expected.m44 = 2.0f;
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m14, actual.m14 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m24, actual.m24 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m34, actual.m34 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );
	QCOMPARE( expected.m44, actual.m44 );
}

void LDMatrix44Test::multTest()
{
	LDMatrix44 matrix1;
	LDMatrix44 matrix2;
	LDMatrix44 expected;
	LDMatrix44 actual;
	//ld_float delta = 0.00001f;

	// Input : matrix1 = 単位行列, matrix2 = 単位行列 (mult_fastのテスト)
	matrix1.mult( matrix2, &actual );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m14, actual.m14 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m24, actual.m24 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m34, actual.m34 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );
	QCOMPARE( expected.m44, actual.m44 );

	// Input : matrix1, matrix2 = 任意の値 (mult_fastのテスト)
	matrix1.m11 = 1.0f;
	matrix1.m12 = 2.0f;
	matrix1.m13 = 3.0f;
	matrix1.m14 = 4.0f;
	matrix1.m21 = 1.0f;
	matrix1.m22 = 2.0f;
	matrix1.m23 = 3.0f;
	matrix1.m24 = 4.0f;
	matrix1.m31 = 1.0f;
	matrix1.m32 = 2.0f;
	matrix1.m33 = 3.0f;
	matrix1.m34 = 4.0f;
	matrix1.m41 = 1.0f;
	matrix1.m42 = 2.0f;
	matrix1.m43 = 3.0f;
	matrix1.m44 = 4.0f;
	matrix2.m11 = 1.0f;
	matrix2.m12 = 2.0f;
	matrix2.m13 = 3.0f;
	matrix2.m14 = 4.0f;
	matrix2.m21 = 1.0f;
	matrix2.m22 = 2.0f;
	matrix2.m23 = 3.0f;
	matrix2.m24 = 4.0f;
	matrix2.m31 = 1.0f;
	matrix2.m32 = 2.0f;
	matrix2.m33 = 3.0f;
	matrix2.m34 = 4.0f;
	matrix2.m41 = 1.0f;
	matrix2.m42 = 2.0f;
	matrix2.m43 = 3.0f;
	matrix2.m44 = 4.0f;
	expected.m[0] = matrix1.m[0] * matrix2.m[0] + matrix1.m[4] * matrix2.m[1] +
	                matrix1.m[8] * matrix2.m[2] + matrix1.m[12]* matrix2.m[3];
	expected.m[1] = matrix1.m[1] * matrix2.m[0] + matrix1.m[5] * matrix2.m[1] +
	                matrix1.m[9] * matrix2.m[2] + matrix1.m[13]* matrix2.m[3];
	expected.m[2] = matrix1.m[2] * matrix2.m[0] + matrix1.m[6] * matrix2.m[1] +
	                matrix1.m[10]* matrix2.m[2] + matrix1.m[14]* matrix2.m[3];
	expected.m[3] = matrix1.m[3] * matrix2.m[0] + matrix1.m[7] * matrix2.m[1] +
	                matrix1.m[11]* matrix2.m[2] + matrix1.m[15]* matrix2.m[3];
	expected.m[4] = matrix1.m[0] * matrix2.m[4] + matrix1.m[4] * matrix2.m[5] +
	                matrix1.m[8] * matrix2.m[6] + matrix1.m[12]* matrix2.m[7];
	expected.m[5] = matrix1.m[1] * matrix2.m[4] + matrix1.m[5] * matrix2.m[5] +
	                matrix1.m[9] * matrix2.m[6] + matrix1.m[13]* matrix2.m[7];
	expected.m[6] = matrix1.m[2] * matrix2.m[4] + matrix1.m[6] * matrix2.m[5] +
	                matrix1.m[10]* matrix2.m[6] + matrix1.m[14]* matrix2.m[7];
	expected.m[7] = matrix1.m[3] * matrix2.m[4] + matrix1.m[7] * matrix2.m[5] +
	                matrix1.m[11]* matrix2.m[6] + matrix1.m[15]* matrix2.m[7];
	expected.m[8] = matrix1.m[0] * matrix2.m[8] + matrix1.m[4] * matrix2.m[9] +
	                matrix1.m[8] * matrix2.m[10]+ matrix1.m[12]* matrix2.m[11];
	expected.m[9] = matrix1.m[1] * matrix2.m[8] + matrix1.m[5] * matrix2.m[9] +
	                matrix1.m[9] * matrix2.m[10]+ matrix1.m[13]* matrix2.m[11];
	expected.m[10]= matrix1.m[2] * matrix2.m[8] + matrix1.m[6] * matrix2.m[9] +
	                matrix1.m[10]* matrix2.m[10]+ matrix1.m[14]* matrix2.m[11];
	expected.m[11]= matrix1.m[3] * matrix2.m[8] + matrix1.m[7] * matrix2.m[9] +
	                matrix1.m[11]* matrix2.m[10] + matrix1.m[15]* matrix2.m[11];
	expected.m[12]= matrix1.m[0] * matrix2.m[12]+ matrix1.m[4] * matrix2.m[13] +
	                matrix1.m[8] * matrix2.m[14]+ matrix1.m[12]* matrix2.m[15];
	expected.m[13]= matrix1.m[1] * matrix2.m[12]+ matrix1.m[5] * matrix2.m[13] +
	                matrix1.m[9] * matrix2.m[14]+ matrix1.m[13]* matrix2.m[15];
	expected.m[14]= matrix1.m[2] * matrix2.m[12]+ matrix1.m[6] * matrix2.m[13] +
	                matrix1.m[10]* matrix2.m[14]+ matrix1.m[14]* matrix2.m[15];
	expected.m[15]= matrix1.m[3] * matrix2.m[12] + matrix1.m[7] * matrix2.m[13] +
	                matrix1.m[11]* matrix2.m[14] + matrix1.m[15]* matrix2.m[15];

	matrix1.mult( matrix2, &actual );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m14, actual.m14 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m24, actual.m24 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m34, actual.m34 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );
	QCOMPARE( expected.m44, actual.m44 );

	// Input : matrix1, matrix2 = 任意の値 (mult_safeのテスト) <- assertのため分岐できず
	//matrix1.mult(matrix2, &matrix1);
}

void LDMatrix44Test::translateTest()
{
	LDMatrix44 expected;
	LDMatrix44 actual;
	//ld_float delta = 0.00001f;

	// Input : actual = 単位行列, x = 0.0, y = 0.0, z = 0.0 (ゼロ)
	actual.translate( 0.0, 0.0, 0.0 );
	QCOMPARE( expected.m14, actual.m14 );
	QCOMPARE( expected.m24, actual.m24 );
	QCOMPARE( expected.m34, actual.m34 );
	QCOMPARE( expected.m44, actual.m44 );

	// Input : actual = 単位行列, x = 1.0, y = 2.0, z = 3.0 (任意の値)
	expected.m14 = 1.0f;
	expected.m24 = 2.0f;
	expected.m34 = 3.0f;
	expected.m44 = 1.0f;
	actual.translate( 1.0, 2.0, 3.0 );
	QCOMPARE( expected.m14, actual.m14 );
	QCOMPARE( expected.m24, actual.m24 );
	QCOMPARE( expected.m34, actual.m34 );
	QCOMPARE( expected.m44, actual.m44 );

	// Input : actual = 任意の値, x = 1.0, y = 2.0, z = 3.0 (任意の値)
	ld_float x = 1.0f;
	ld_float y = 2.0f;
	ld_float z = 3.0f;
	actual.m11 = 1.0f;
	actual.m12 = 2.0f;
	actual.m13 = 3.0f;
	actual.m14 = 4.0f;
	actual.m21 = 1.0f;
	actual.m22 = 2.0f;
	actual.m23 = 3.0f;
	actual.m24 = 4.0f;
	actual.m31 = 1.0f;
	actual.m32 = 2.0f;
	actual.m33 = 3.0f;
	actual.m34 = 4.0f;
	actual.m41 = 1.0f;
	actual.m42 = 2.0f;
	actual.m43 = 3.0f;
	actual.m44 = 4.0f;
	expected.m14 = actual.m11 * x + actual.m12 * y + actual.m13 * z + actual.m14;
	expected.m24 = actual.m21 * x + actual.m22 * y + actual.m23 * z + actual.m24;
	expected.m34 = actual.m31 * x + actual.m32 * y + actual.m33 * z + actual.m34;
	expected.m44 = actual.m41 * x + actual.m42 * y + actual.m43 * z + actual.m44;
	actual.translate( x, y, z );
	QCOMPARE( expected.m14, actual.m14 );
	QCOMPARE( expected.m24, actual.m24 );
	QCOMPARE( expected.m34, actual.m34 );
	QCOMPARE( expected.m44, actual.m44 );
}

void LDMatrix44Test::scaleTest()
{
	LDMatrix44 expected;
	LDMatrix44 actual;
	//ld_float delta = 0.00001f;

	// Input : actual = 単位行列, x = 0.0, y = 0.0, z = 0.0 (ゼロ)
	expected.m11 = 0.0f;
	expected.m12 = 0.0f;
	expected.m13 = 0.0f;
	expected.m21 = 0.0f;
	expected.m22 = 0.0f;
	expected.m23 = 0.0f;
	expected.m31 = 0.0f;
	expected.m32 = 0.0f;
	expected.m33 = 0.0f;
	expected.m41 = 0.0f;
	expected.m42 = 0.0f;
	expected.m43 = 0.0f;
	actual.scale( 0.0, 0.0, 0.0 );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );

	// Input : actual = 任意の値, x = 1.0, y = 2.0, z = 3.0 (任意の値)
	ld_float x = 1.0f;
	ld_float y = 2.0f;
	ld_float z = 3.0f;
	actual.m11 = 1.0f;
	actual.m12 = 2.0f;
	actual.m13 = 3.0f;
	actual.m21 = 1.0f;
	actual.m22 = 2.0f;
	actual.m23 = 3.0f;
	actual.m31 = 1.0f;
	actual.m32 = 2.0f;
	actual.m33 = 3.0f;
	actual.m41 = 1.0f;
	actual.m42 = 2.0f;
	actual.m43 = 3.0f;
	expected.m11 = actual.m11 * x;
	expected.m12 = actual.m12 * y;
	expected.m13 = actual.m13 * z;
	expected.m21 = actual.m21 * x;
	expected.m22 = actual.m22 * y;
	expected.m23 = actual.m23 * z;
	expected.m31 = actual.m31 * x;
	expected.m32 = actual.m32 * y;
	expected.m33 = actual.m33 * z;
	expected.m41 = actual.m41 * x;
	expected.m42 = actual.m42 * y;
	expected.m43 = actual.m43 * z;
	actual.scale( x, y, z );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );
}

void LDMatrix44Test::rotateXTest()
{
	LDMatrix44 expected;
	LDMatrix44 actual;
	//ld_float delta = 0.00001f;
	ld_float tmp;
	ld_float theta;

	// Input : actual = 単位行列, theta = 0.0 (ゼロ)
	tmp = expected.m12;
	expected.m12 = tmp * cos( 0.0f ) + expected.m13 * sin( 0.0f );
	expected.m13 = tmp * -sin( 0.0f ) + expected.m13 * cos( 0.0f );
	tmp = expected.m22;
	expected.m22 = tmp * cos( 0.0f ) + expected.m23 * sin( 0.0f );
	expected.m23 = tmp * -sin( 0.0f ) + expected.m23 * cos( 0.0f );
	tmp = expected.m32;
	expected.m32 = tmp * cos( 0.0f ) + expected.m33 * sin( 0.0f );
	expected.m33 = tmp * -sin( 0.0f ) + expected.m33 * cos( 0.0f );
	tmp = expected.m42;
	expected.m42 = tmp * cos( 0.0f ) + expected.m43 * sin( 0.0f );
	expected.m43 = tmp * -sin( 0.0f ) + expected.m43 * cos( 0.0f );
	actual.rotateX( 0.0f );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );

	// Input : actual = 任意の値, theta = PI/4.0f; (任意の値)
	theta = LDMathUtil::PI / 4.0f;
	actual.m11 = 1.0f;
	actual.m12 = 2.0f;
	actual.m13 = 3.0f;
	actual.m21 = 1.0f;
	actual.m22 = 2.0f;
	actual.m23 = 3.0f;
	actual.m31 = 1.0f;
	actual.m32 = 2.0f;
	actual.m33 = 3.0f;
	actual.m41 = 1.0f;
	actual.m42 = 2.0f;
	actual.m43 = 3.0f;
	expected.m11 = 1.0f;
	expected.m12 = 2.0f;
	expected.m13 = 3.0f;
	expected.m21 = 1.0f;
	expected.m22 = 2.0f;
	expected.m23 = 3.0f;
	expected.m31 = 1.0f;
	expected.m32 = 2.0f;
	expected.m33 = 3.0f;
	expected.m41 = 1.0f;
	expected.m42 = 2.0f;
	expected.m43 = 3.0f;
	tmp = expected.m12;
	expected.m12 = tmp * cos( theta ) + expected.m13 * sin( theta );
	expected.m13 = tmp * -sin( theta ) + expected.m13 * cos( theta );
	tmp = expected.m22;
	expected.m22 = tmp * cos( theta ) + expected.m23 * sin( theta );
	expected.m23 = tmp * -sin( theta ) + expected.m23 * cos( theta );
	tmp = expected.m32;
	expected.m32 = tmp * cos( theta ) + expected.m33 * sin( theta );
	expected.m33 = tmp * -sin( theta ) + expected.m33 * cos( theta );
	tmp = expected.m42;
	expected.m42 = tmp * cos( theta ) + expected.m43 * sin( theta );
	expected.m43 = tmp * -sin( theta ) + expected.m43 * cos( theta );
	actual.rotateX( theta );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );
}

void LDMatrix44Test::rotateYTest()
{
	LDMatrix44 expected;
	LDMatrix44 actual;
	//ld_float delta = 0.00001f;
	ld_float tmp;
	ld_float theta;

	// Input : actual = 単位行列, theta = 0.0 (ゼロ)
	tmp = expected.m11;
	expected.m11 = tmp * cos( 0.0f ) + expected.m13 * -sin( 0.0f );
	expected.m13 = tmp * sin( 0.0f ) + expected.m13 * cos( 0.0f );
	tmp = expected.m21;
	expected.m21 = tmp * cos( 0.0f ) + expected.m23 * -sin( 0.0f );
	expected.m23 = tmp * sin( 0.0f ) + expected.m23 * cos( 0.0f );
	tmp = expected.m31;
	expected.m31 = tmp * cos( 0.0f ) + expected.m33 * -sin( 0.0f );
	expected.m33 = tmp * sin( 0.0f ) + expected.m33 * cos( 0.0f );
	tmp = expected.m41;
	expected.m41 = tmp * cos( 0.0f ) + expected.m43 * -sin( 0.0f );
	expected.m43 = tmp * sin( 0.0f ) + expected.m43 * cos( 0.0f );
	actual.rotateY( 0.0f );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );

	// Input : actual = 任意の値, theta = PI/4.0f; (任意の値)
	theta = LDMathUtil::PI / 4.0f;
	actual.m11 = 1.0f;
	actual.m12 = 2.0f;
	actual.m13 = 3.0f;
	actual.m21 = 1.0f;
	actual.m22 = 2.0f;
	actual.m23 = 3.0f;
	actual.m31 = 1.0f;
	actual.m32 = 2.0f;
	actual.m33 = 3.0f;
	actual.m41 = 1.0f;
	actual.m42 = 2.0f;
	actual.m43 = 3.0f;
	expected.m11 = 1.0f;
	expected.m12 = 2.0f;
	expected.m13 = 3.0f;
	expected.m21 = 1.0f;
	expected.m22 = 2.0f;
	expected.m23 = 3.0f;
	expected.m31 = 1.0f;
	expected.m32 = 2.0f;
	expected.m33 = 3.0f;
	expected.m41 = 1.0f;
	expected.m42 = 2.0f;
	expected.m43 = 3.0f;
	tmp = expected.m11;
	expected.m11 = tmp * cos( theta ) + expected.m13 * -sin( theta );
	expected.m13 = tmp * sin( theta ) + expected.m13 * cos( theta );
	tmp = expected.m21;
	expected.m21 = tmp * cos( theta ) + expected.m23 * -sin( theta );
	expected.m23 = tmp * sin( theta ) + expected.m23 * cos( theta );
	tmp = expected.m31;
	expected.m31 = tmp * cos( theta ) + expected.m33 * -sin( theta );
	expected.m33 = tmp * sin( theta ) + expected.m33 * cos( theta );
	tmp = expected.m41;
	expected.m41 = tmp * cos( theta ) + expected.m43 * -sin( theta );
	expected.m43 = tmp * sin( theta ) + expected.m43 * cos( theta );
	actual.rotateY( theta );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );
}

void LDMatrix44Test::rotateZTest()
{
	LDMatrix44 expected;
	LDMatrix44 actual;
	//ld_float delta = 0.00001f;
	ld_float tmp;
	ld_float theta;

	// Input : actual = 単位行列, theta = 0.0 (ゼロ)
	tmp = expected.m11;
	expected.m11 = tmp * cos( 0.0f ) + expected.m12 * sin( 0.0f );
	expected.m12 = tmp * -sin( 0.0f ) + expected.m12 * cos( 0.0f );
	tmp = expected.m21;
	expected.m21 = tmp * cos( 0.0f ) + expected.m22 * sin( 0.0f );
	expected.m22 = tmp * -sin( 0.0f ) + expected.m22 * cos( 0.0f );
	tmp = expected.m31;
	expected.m31 = tmp * cos( 0.0f ) + expected.m32 * sin( 0.0f );
	expected.m32 = tmp * -sin( 0.0f ) + expected.m32 * cos( 0.0f );
	tmp = expected.m41;
	expected.m41 = tmp * cos( 0.0f ) + expected.m32 * sin( 0.0f );
	expected.m42 = tmp * -sin( 0.0f ) + expected.m32 * cos( 0.0f );
	actual.rotateZ( 0.0f );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );

	// Input : actual = 任意の値, theta = PI/4.0f; (任意の値)
	theta = LDMathUtil::PI / 4.0f;
	actual.m11 = 1.0f;
	actual.m12 = 2.0f;
	actual.m13 = 3.0f;
	actual.m21 = 1.0f;
	actual.m22 = 2.0f;
	actual.m23 = 3.0f;
	actual.m31 = 1.0f;
	actual.m32 = 2.0f;
	actual.m33 = 3.0f;
	actual.m41 = 1.0f;
	actual.m42 = 2.0f;
	actual.m43 = 3.0f;
	expected.m11 = 1.0f;
	expected.m12 = 2.0f;
	expected.m13 = 3.0f;
	expected.m21 = 1.0f;
	expected.m22 = 2.0f;
	expected.m23 = 3.0f;
	expected.m31 = 1.0f;
	expected.m32 = 2.0f;
	expected.m33 = 3.0f;
	expected.m41 = 1.0f;
	expected.m42 = 2.0f;
	expected.m43 = 3.0f;
	tmp = expected.m11;
	expected.m11 = tmp * cos( theta ) + expected.m12 * sin( theta );
	expected.m12 = tmp * -sin( theta ) + expected.m12 * cos( theta );
	tmp = expected.m21;
	expected.m21 = tmp * cos( theta ) + expected.m22 * sin( theta );
	expected.m22 = tmp * -sin( theta ) + expected.m22 * cos( theta );
	tmp = expected.m31;
	expected.m31 = tmp * cos( theta ) + expected.m32 * sin( theta );
	expected.m32 = tmp * -sin( theta ) + expected.m32 * cos( theta );
	tmp = expected.m41;
	expected.m41 = tmp * cos( theta ) + expected.m42 * sin( theta );
	expected.m42 = tmp * -sin( theta ) + expected.m42 * cos( theta );
	actual.rotateZ( theta );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );
}

void LDMatrix44Test::transformTest()
{
	LDVector3 vector;
	LDVector3 expected;
	LDVector3 actual;
	LDMatrix44 matrix;
	//ld_float delta = 0.00001f;

	// Input : matrix = 単位行列, vector = 0.0 (ゼロ)
	vector.zero();
	expected.x = 0.0f;
	expected.y = 0.0f;
	expected.z = 0.0f;
	actual = matrix.transform( vector );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );

	// Input : matrix = 任意の値, x = 1.0, y = 2.0, z = 3.0 (任意の値)
	vector.x = 1.0f;
	vector.y = 2.0f;
	vector.z = 3.0f;
	matrix.m11 = 1.0f;
	matrix.m12 = 2.0f;
	matrix.m13 = 3.0f;
	matrix.m14 = 4.0f;
	matrix.m21 = 1.0f;
	matrix.m22 = 2.0f;
	matrix.m23 = 3.0f;
	matrix.m24 = 4.0f;
	matrix.m31 = 1.0f;
	matrix.m32 = 2.0f;
	matrix.m33 = 3.0f;
	matrix.m34 = 4.0f;
	expected.x = matrix.m11 * vector.x + matrix.m12 * vector.y + matrix.m13 * vector.z + matrix.m14;
	expected.y = matrix.m21 * vector.x + matrix.m22 * vector.y + matrix.m13 * vector.z + matrix.m24;
	expected.z = matrix.m31 * vector.y + matrix.m32 * vector.y + matrix.m13 * vector.z + matrix.m34;
	actual = matrix.transform( vector );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );

	// Input : matrix = 任意の値, x = 1.0, y = 2.0, z = 3.0 (任意の値) (p == dstの場合)
	vector.x = 1.0f;
	vector.y = 2.0f;
	vector.z = 3.0f;
	matrix.m11 = 1.0f;
	matrix.m12 = 2.0f;
	matrix.m13 = 3.0f;
	matrix.m14 = 4.0f;
	matrix.m21 = 1.0f;
	matrix.m22 = 2.0f;
	matrix.m23 = 3.0f;
	matrix.m24 = 4.0f;
	matrix.m31 = 1.0f;
	matrix.m32 = 2.0f;
	matrix.m33 = 3.0f;
	matrix.m34 = 4.0f;
	expected.x = matrix.m11 * vector.x + matrix.m12 * vector.y + matrix.m13 * vector.z + matrix.m14;
	expected.y = matrix.m21 * vector.x + matrix.m22 * vector.y + matrix.m13 * vector.z + matrix.m24;
	expected.z = matrix.m31 * vector.y + matrix.m32 * vector.y + matrix.m13 * vector.z + matrix.m34;
	matrix.transform( vector, &vector );
	QCOMPARE( expected.x, vector.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
}

void LDMatrix44Test::fromQuaterionTest()
{
	LDQuat quat( 0.0f, 0.0f, 0.0f, 0.0f );
	LDMatrix44 expected;
	LDMatrix44 actual;
	//ld_float delta = 0.00001f;

	// Input : actual = 単位行列, quat = 0.0 (ゼロ)
	actual.fromQuaterion( quat );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );

	// Input : actual = 単位行列, quat x = 1.0, y = 2.0, z = 3.0, w = 0.5 (任意の値)
	quat.x = 1.0f;
	quat.y = 2.0f;
	quat.z = 3.0f;
	quat.w = 0.5f;
	ld_float xx = 2.0f * quat.x;
	ld_float yy = 2.0f * quat.y;
	ld_float zz = 2.0f * quat.z;
	ld_float ww = -2.0f * quat.w;
	expected.m11 = 1.0f - yy * quat.y - zz * quat.z;
	expected.m12 = xx * quat.y + ww * quat.z;
	expected.m13 = xx * quat.z - ww * quat.y;
	expected.m21 = xx * quat.y - ww * quat.z;
	expected.m22 = 1.0f - xx * quat.x - zz * quat.z;
	expected.m23 = yy * quat.z + ww * quat.x;
	expected.m31 = xx * quat.z + ww * quat.y;
	expected.m32 = yy * quat.z - ww * quat.x;
	expected.m33 = 1.0f - xx * quat.x - yy * quat.y;
	actual.fromQuaterion( quat );
	QCOMPARE( expected.m11, actual.m11 );
	QCOMPARE( expected.m12, actual.m12 );
	QCOMPARE( expected.m13, actual.m13 );
	QCOMPARE( expected.m21, actual.m21 );
	QCOMPARE( expected.m22, actual.m22 );
	QCOMPARE( expected.m23, actual.m23 );
	QCOMPARE( expected.m31, actual.m31 );
	QCOMPARE( expected.m32, actual.m32 );
	QCOMPARE( expected.m33, actual.m33 );
	QCOMPARE( expected.m41, actual.m41 );
	QCOMPARE( expected.m42, actual.m42 );
	QCOMPARE( expected.m43, actual.m43 );
}

void LDMatrix44Test::serializeTest()
{
	using namespace live2d::serialize;
	const char* name="matrix44";
	QSharedPointer<LDMatrix44> src(new LDMatrix44);
	src->m12=0.0015;

	//シリアライズ
	SerializeHelper::writeBoostXml( name,src );

	//デシリアライズ
	auto dst=SerializeHelper::readBoostXml<LDMatrix44>( name );

	QVERIFY(*(dst.data())==*(src.data()));
}
} // namespace live2d
