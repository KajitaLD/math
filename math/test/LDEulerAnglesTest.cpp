#include "LDEulerAnglesTest.h"

namespace live2d
{

//------ EEulerAngles.cpp ------
void LDEulerAnglesTest::canonizeTest()
{
	LDEulerAngles actual;
	LDEulerAngles expected;
	//ld_float delta = 0.00001f;

	// Input : heading = 0.0, pitch = 0.0, bank = 0.0 (ゼロ)
	actual.identity();
	expected.identity();
	actual.canonize();
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );

	// Input : heading = EMathUtil::PI_OVER_2, pitch = -EMathUtil::PI_OVER_2 - 0.1,
	//       bank    = EMathUtil::PI_OVER_2 (pitch < - EMathUtil::PI_OVER_2のケース)
	actual.heading   = LDMathUtil::PI_OVER_2;
	actual.pitch     = -LDMathUtil::PI_OVER_2 - 0.1;
	actual.bank      = LDMathUtil::PI_OVER_2;
	expected.heading = LDMathUtil::wrapPi( actual.heading + LDMathUtil::PI );
	expected.pitch   = -LDMathUtil::PI - actual.pitch;
	expected.bank    = LDMathUtil::wrapPi( actual.bank + LDMathUtil::PI );
	actual.canonize();
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );

	// Input : heading = EMathUtil::PI_OVER_2, pitch = EMathUtil::PI_OVER_2 + 0.1,
	//       bank    = EMathUtil::PI_OVER_2 (pitch > EMathUtil::PI_OVER_2のケース)
	actual.heading   = LDMathUtil::PI_OVER_2;
	actual.pitch     = LDMathUtil::PI_OVER_2 + 0.1;
	actual.bank      = LDMathUtil::PI_OVER_2;
	expected.heading = LDMathUtil::wrapPi( actual.heading + LDMathUtil::PI );
	expected.pitch   = LDMathUtil::PI - actual.pitch;
	expected.bank    = LDMathUtil::wrapPi( actual.bank + LDMathUtil::PI );
	actual.canonize();
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );

	// Input : heading = EMathUtil::PI_OVER_2, pitch = EMathUtil::PI_OVER_2,
	//       bank    = EMathUtil::PI_OVER_2 (全てPI_OVER_2, ジンバルロックのケース)
	actual.heading   = LDMathUtil::PI_OVER_2;
	actual.pitch     = LDMathUtil::PI_OVER_2;
	actual.bank      = LDMathUtil::PI_OVER_2;
	expected.heading = actual.heading + actual.bank;
	expected.pitch   = LDMathUtil::PI_OVER_2;
	expected.bank    = 0.0f;
	actual.canonize();
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );
}

void LDEulerAnglesTest::fromObjectToInertialQuaternionTest()
{
	LDQuat quat( 0.0f, 0.0f, 0.0f, 0.0f );
	LDEulerAngles actual;
	LDEulerAngles expected;
	//ld_float delta = 0.00001f;
	ld_float sp;

	// Input : x = 0.0, y = 0.0, z = 0.0, w = 0.0 (ゼロクォータニオン)
	actual.identity();
	expected.identity();
	actual.fromObjectToInertialQuaternion( quat );
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );

	// Input : x = 1.0, y = 0.0, z = 0.0, w = 1.0 (ジンバルロックのケース)
	quat.x = 1.0f;
	quat.y = 0.0f;
	quat.z = 0.0f;
	quat.w = 1.0f;
	sp = -2.0f * ( quat.y * quat.z - quat.w * quat.x );
	expected.heading = atan2( -quat.x * quat.z + quat.w * quat.y,
	                          0.5f - quat.y * quat.y - quat.z * quat.z );
	expected.pitch   = LDMathUtil::PI_OVER_2 * sp;
	expected.bank    = 0.0f;
	actual.fromObjectToInertialQuaternion( quat );
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );

	// Input : x = 1.0, y = 0.25, z = 0.25, w = 0.5 (任意の値. 角度計算のケース)
	quat.x = 1.0f;
	quat.y = 0.25f;
	quat.z = 0.25f;
	quat.w = 0.5f;
	sp = -2.0f * ( quat.y * quat.z - quat.w * quat.x );
	expected.heading = atan2( quat.x * quat.z + quat.w * quat.y,
	                          0.5f - quat.x * quat.x - quat.y * quat.y );
	expected.pitch   = asin( sp );
	expected.bank    = atan2( quat.x * quat.y + quat.w * quat.z,
	                          0.5f - quat.x * quat.x - quat.z * quat.z );
	actual.fromObjectToInertialQuaternion( quat );
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );
}

void LDEulerAnglesTest::fromInertialToObjectQuaternionTest()
{
	LDQuat quat( 0.0f, 0.0f, 0.0f, 0.0f );
	LDEulerAngles actual;
	LDEulerAngles expected;
	//ld_float delta = 0.00001f;
	ld_float sp;

	// Input : x = 0.0, y = 0.0, z = 0.0, w = 0.0 (ゼロクォータニオン)
	actual.identity();
	expected.identity();
	actual.fromInertialToObjectQuaternion( quat );
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );

	// Input : x = 1.0, y = 0.0, z = 0.0, w = 1.0 (ジンバルロックのケース)
	quat.x = 1.0f;
	quat.y = 0.0f;
	quat.z = 0.0f;
	quat.w = 1.0f;
	sp = -2.0f * ( quat.y * quat.z - quat.w * quat.x );
	expected.heading = atan2( -quat.x * quat.z + quat.w * quat.y,
	                          0.5f - quat.y * quat.y - quat.z * quat.z );
	expected.pitch   = LDMathUtil::PI_OVER_2 * sp;
	expected.bank    = 0.0f;
	actual.fromObjectToInertialQuaternion( quat );
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );

	// Input : x = 1.0, y = 0.25, z = 0.25, w = 0.5 (任意の値. 角度計算のケース)
	quat.x = 1.0f;
	quat.y = 0.25f;
	quat.z = 0.25f;
	quat.w = 0.5f;
	sp = -2.0f * ( quat.y * quat.z - quat.w * quat.x );
	expected.heading = atan2( quat.x * quat.z + quat.w * quat.y,
	                          0.5f - quat.x * quat.x - quat.y * quat.y );
	expected.pitch   = asin( sp );
	expected.bank    = atan2( quat.x * quat.y + quat.w * quat.z,
	                          0.5f - quat.x * quat.x - quat.z * quat.z );
	actual.fromObjectToInertialQuaternion( quat );
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );
}

void LDEulerAnglesTest::fromWorldToObjectMatrixTest()
{
	LDMatrix44 matrix;
	LDEulerAngles actual;
	LDEulerAngles expected;
	//ld_float delta = 0.00001f;

	// Input : (単位行列)
	actual.identity();
	expected.identity();
	actual.fromWorldToObjectMatrix( matrix );
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );

	// Input : matrix.m23 = 1.0 (ジンバルロックのケース)
	matrix.m23 = 1.0f;
	expected.heading = atan2( -matrix.m31, matrix.m11 );
	expected.pitch   = LDMathUtil::PI_OVER_2 * -matrix.m23;
	expected.bank    = 0.0f;
	actual.fromWorldToObjectMatrix( matrix );
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );

	// Input : matrix.m23 = 1.0 (任意の値. 角度計算のケース)
	matrix.m11 = 0.1f;
	matrix.m12 = 0.2f;
	matrix.m13 = 0.3f;
	matrix.m14 = 0.4f;
	matrix.m21 = 0.1f;
	matrix.m22 = 0.2f;
	matrix.m23 = 0.3f;
	matrix.m24 = 0.4f;
	matrix.m31 = 0.1f;
	matrix.m32 = 0.2f;
	matrix.m33 = 0.3f;
	matrix.m34 = 0.4f;
	matrix.m41 = 0.1f;
	matrix.m42 = 0.2f;
	matrix.m43 = 0.3f;
	matrix.m44 = 0.4f;
	expected.heading = atan2( matrix.m13, matrix.m33 );
	expected.pitch   = asin( -matrix.m23 );
	expected.bank    = atan2( matrix.m21, matrix.m22 );
	actual.fromWorldToObjectMatrix( matrix );
	QCOMPARE( expected.heading, actual.heading );
	QCOMPARE( expected.pitch, actual.pitch );
	QCOMPARE( expected.bank, actual.bank );
}
} // namespace live2d
