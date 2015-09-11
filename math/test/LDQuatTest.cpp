#include "LDQuatTest.h"
#include "TestUtil.h"

namespace live2d
{
//------ EQuat.cpp ------
void LDQuatTest::getAxisTest()
{
	LDQuat quat( 0.0f, 0.0f, 0.0f, 0.0f );
	LDVector3 actual;
	LDVector3 expected;
	//ld_float delta = 0.00001f;

	// Input : x = 0.0, y = 0.0, z = 0.0, w = 0.0 (ゼロクォータニオン)
	expected.zero();
	actual = quat.getAxis();
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );

	// Input : x = 0.0, y = 0.0, z = 0.0, w = 1.0 (単位クォータニオン)
	quat.x = 0.0f;
	quat.y = 0.0f;
	quat.z = 0.0f;
	quat.w = 1.0f;
	expected.x = 1.0f;
	expected.y = 0.0f;
	expected.z = 0.0f;
	actual = quat.getAxis();
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );

	// Input : x = 1.0, y = 2.0, z = 3.0, w = 0.5 (任意の値)
	quat.x = 1.0f;
	quat.y = 2.0f;
	quat.z = 3.0f;
	quat.w = 0.5f;
	expected.x = quat.x * 1.0f / sqrt( 1.0f - quat.w * quat.w );
	expected.y = quat.y * 1.0f / sqrt( 1.0f - quat.w * quat.w );
	expected.z = quat.z * 1.0f / sqrt( 1.0f - quat.w * quat.w );
	actual = quat.getAxis();
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
}


void LDQuatTest::setToRotationArcTest()
{
	LDVector3 vector1;
	LDVector3 vector2;
	LDVector3 vector3;
	LDQuat actual;
	LDQuat expected;
	//ld_float delta = 0.00001f;
	ld_float d;

	// Input : vector1{x = 0.0, y = 0.0, z = 0.0}, vector2 {x = 0.0, y = 0.0, z = 0.0}, useNormalize = false
	//         actual {x = 0.0, y = 0.0, z = 0.0, w = 0.0}
	// useNormalize = false, (ゼロベクトル)
	vector1.zero();
	vector2.zero();
	actual.x = 0.0f;
	actual.y = 0.0f;
	actual.z = 0.0f;
	actual.w = 0.0f;
	expected.x = 0.0f;
	expected.y = 0.0f;
	expected.z = 0.0f;
	expected.w = sqrt( 2.0f ) / 2.0f;
	actual.setToRotationArc( vector1, vector2, false );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	LDFUZZY_COMPARE( expected.w, actual.w ,TEST_TOLERANCE );
	//	QVERIFY(qFuzzyCompare(expected.w, actual.w));
	//	QCOMPARE(expected.w, actual.w);//極小誤差によりFalse

	// Input : vector1{x = 0.0, y = 0.0, z = 0.0}, vector2 {x = 0.0, y = 0.0, z = 0.0}, useNormalize = true
	//         actual {x = 0.0, y = 0.0, z = 0.0, w = 0.0}
	// useNormalize = true, (ゼロベクトル)
	vector1.zero();
	vector2.zero();
	actual.x = 0.0f;
	actual.y = 0.0f;
	actual.z = 0.0f;
	actual.w = 0.0f;
	expected.x = 0.0f;
	expected.y = 0.0f;
	expected.z = 0.0f;
	expected.w = sqrt( 2.0f ) / 2.0f;
	actual.setToRotationArc( vector1, vector2, true );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	LDFUZZY_COMPARE( expected.w, actual.w,TEST_TOLERANCE );
	//	QCOMPARE(expected.w, actual.w);//極小誤差によりFalse

	// Input : vector1{x = 1.0, y = 2.0, z = 3.0}, vector2 {x = 4.0, y = 5.0, z = 6.0}, useNormalize = false
	//         actual {x = 1.0, y = 2.0, z = 3.0, w = 0.5}
	// useNormalize = false, (任意の値)
	vector1.x = 1.0f;
	vector1.y = 2.0f;
	vector1.z = 3.0f;
	vector2.x = 4.0f;
	vector2.y = 5.0f;
	vector2.z = 6.0f;
	actual.x = 1.0f;
	actual.y = 2.0f;
	actual.z = 3.0f;
	actual.w = 0.5f;

	vector3 = crossProduct( vector1, vector2 );
	d = vector1.dotProduct( vector2 );

	expected.x = vector3.x / sqrt( ( 1+d )*2 );
	expected.y = vector3.y / sqrt( ( 1+d )*2 );
	expected.z = vector3.z / sqrt( ( 1+d )*2 );
	expected.w = sqrt( ( 1+d )*2 ) / 2.0f;
	actual.setToRotationArc( vector1, vector2, false );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );

	// Input : vector1{x = 1.0, y = 2.0, z = 3.0}, vector2 {x = 4.0, y = 5.0, z = 6.0}, useNormalize = true
	//         actual {x = 1.0, y = 2.0, z = 3.0, w = 0.5}
	// useNormalize = true, (任意の値)
	vector1.x = 1.0f;
	vector1.y = 2.0f;
	vector1.z = 3.0f;
	vector2.x = 4.0f;
	vector2.y = 5.0f;
	vector2.z = 6.0f;
	actual.x = 1.0f;
	actual.y = 2.0f;
	actual.z = 3.0f;
	actual.w = 0.5f;

	vector1.normalize();
	vector2.normalize();
	vector3 = crossProduct( vector1, vector2 );
	d = vector1.dotProduct( vector2 );

	expected.x = vector3.x / sqrt( ( 1+d )*2 );
	expected.y = vector3.y / sqrt( ( 1+d )*2 );
	expected.z = vector3.z / sqrt( ( 1+d )*2 );
	expected.w = sqrt( ( 1+d )*2 ) / 2.0f;
	actual.setToRotationArc( vector1, vector2, true );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );
}

void LDQuatTest::setToRotateObjectToInertialTest()
{
	LDEulerAngles angle1;
	LDQuat actual;
	LDQuat expected;
	//ld_float delta = 0.00001f;

	// Input : angle1{heading = 0.0, pitch = 0.0, bank = 0.0} (ゼロベクトル)
	angle1.heading = 0.0f;
	angle1.pitch = 0.0f;
	angle1.bank = 0.0f;
	expected.x = 0.0f;
	expected.y = 0.0f;
	expected.z = 0.0f;
	expected.w = 1.0f;
	actual.setToRotateObjectToInertial( angle1 );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );

	// Input : angle1{heading = PI/4, pitch = PI/2, bank = PI} (任意の値)
	angle1.heading = LDMathUtil::PI / 4.0f;
	angle1.pitch = LDMathUtil::PI / 2.0f;
	angle1.bank = LDMathUtil::PI;
	expected.x =  cos( angle1.heading * 0.5f ) * sin( angle1.pitch * 0.5f ) * cos( angle1.bank * 0.5f ) +
	              sin( angle1.heading * 0.5f ) * cos( angle1.pitch * 0.5f ) * sin( angle1.bank * 0.5f );
	expected.y = -cos( angle1.heading * 0.5f ) * sin( angle1.pitch * 0.5f ) * sin( angle1.bank * 0.5f ) +
	             sin( angle1.heading * 0.5f ) * cos( angle1.pitch * 0.5f ) * cos( angle1.bank * 0.5f );
	expected.z = -sin( angle1.heading * 0.5f ) * sin( angle1.pitch * 0.5f ) * cos( angle1.bank * 0.5f ) +
	             cos( angle1.heading * 0.5f ) * cos( angle1.pitch * 0.5f ) * sin( angle1.bank * 0.5f );
	expected.w =  cos( angle1.heading * 0.5f ) * cos( angle1.pitch * 0.5f ) * cos( angle1.bank * 0.5f ) +
	              sin( angle1.heading * 0.5f ) * sin( angle1.pitch * 0.5f ) * sin( angle1.bank * 0.5f );
	actual.setToRotateObjectToInertial( angle1 );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );
}

void LDQuatTest::setToRotateInertialToObjectTest()
{
	LDEulerAngles angle1;
	LDQuat actual;
	LDQuat expected;
	//ld_float delta = 0.00001f;

	// Input : angle1{heading = 0.0, pitch = 0.0, bank = 0.0} (ゼロベクトル)
	angle1.heading = 0.0f;
	angle1.pitch = 0.0f;
	angle1.bank = 0.0f;
	expected.x = 0.0f;
	expected.y = 0.0f;
	expected.z = 0.0f;
	expected.w = 1.0f;
	actual.setToRotateObjectToInertial( angle1 );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );

	// Input : angle1{heading = PI/4, pitch = PI/2, bank = PI} (任意の値)
	angle1.heading = LDMathUtil::PI / 4.0f;
	angle1.pitch = LDMathUtil::PI / 2.0f;
	angle1.bank = LDMathUtil::PI;
	expected.x = -cos( angle1.heading * 0.5f ) * sin( angle1.pitch * 0.5f ) * cos( angle1.bank * 0.5f ) -
	             sin( angle1.heading * 0.5f ) * cos( angle1.pitch * 0.5f ) * sin( angle1.bank * 0.5f );
	expected.y =  cos( angle1.heading * 0.5f ) * sin( angle1.pitch * 0.5f ) * sin( angle1.bank * 0.5f ) -
	              sin( angle1.heading * 0.5f ) * cos( angle1.pitch * 0.5f ) * cos( angle1.bank * 0.5f );
	expected.z =  sin( angle1.heading * 0.5f ) * sin( angle1.pitch * 0.5f ) * cos( angle1.bank * 0.5f ) -
	              cos( angle1.heading * 0.5f ) * cos( angle1.pitch * 0.5f ) * sin( angle1.bank * 0.5f );
	expected.w =  cos( angle1.heading * 0.5f ) * cos( angle1.pitch * 0.5f ) * cos( angle1.bank * 0.5f ) +
	              sin( angle1.heading * 0.5f ) * sin( angle1.pitch * 0.5f ) * sin( angle1.bank * 0.5f );
	actual.setToRotateInertialToObject( angle1 );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );
}

void LDQuatTest::slerpTest()
{
	LDQuat quat1, quat2;
	LDQuat actual;
	LDQuat expected;
	//ld_float delta = 0.00001f;
	ld_float t;

	// Input : quat1{x = 1.0, y = 2.0, z = 3.0, w = 0.1}, quat2{x = 4.0, y = 5.0, z = 6.0, w = 0.2}, t = 0.0
	// 範囲外t <= 0.0fのケース
	quat1.x = 1.0f;
	quat1.y = 2.0f;
	quat1.z = 3.0f;
	quat1.w = 0.1f;
	quat2.x = 4.0f;
	quat2.y = 5.0f;
	quat2.z = 6.0f;
	quat2.w = 0.2f;
	t = 0.0f;
	expected.x = 4.0f;
	expected.y = 5.0f;
	expected.z = 6.0f;
	expected.w = 0.2f;
	actual = quat2.slerp( quat1, t );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );

	// Input : quat1{x = 1.0, y = 2.0, z = 3.0, w = 0.1}, quat2{x = 4.0, y = 5.0, z = 6.0, w = 0.2}, t = 1.0
	// 範囲外t >= 1.0fのケース
	quat1.x = 1.0f;
	quat1.y = 2.0f;
	quat1.z = 3.0f;
	quat1.w = 0.1f;
	quat2.x = 4.0f;
	quat2.y = 5.0f;
	quat2.z = 6.0f;
	quat2.w = 0.2f;
	t = 1.0f;
	expected.x = 1.0f;
	expected.y = 2.0f;
	expected.z = 3.0f;
	expected.w = 0.1f;
	actual = quat2.slerp( quat1, t );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );

	// Input : quat1{x = 0.0, y = 0.0, z = 0.0, w = 1.0}, quat2{x = 0.0, y = 0.0, z = 0.0, w = 1.0}, t = 0.5
	// cosOmega > 0.9999fのケース
	quat1.x = 0.0f;
	quat1.y = 0.0f;
	quat1.z = 0.0f;
	quat1.w = 1.0f;
	quat2.x = 0.0f;
	quat2.y = 0.0f;
	quat2.z = 0.0f;
	quat2.w = 1.0f;
	t = 0.5f;
	expected.x = 0.0f;
	expected.y = 0.0f;
	expected.z = 0.0f;
	expected.w = 1.0f;
	actual = quat2.slerp( quat1, t );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );

	// Input : quat1{x = 0.49, y = 0.5, z = 0.5, w = 0.5}, quat2{x = 0.5, y = 0.49, z = 0.5, w = 0.5}, t = 0.5
	// cosOmega <= 0.9999fのケース
	quat1.x = 0.49f;
	quat1.y = 0.5f;
	quat1.z = 0.5f;
	quat1.w = 0.5f;
	quat2.x = 0.5f;
	quat2.y = 0.49f;
	quat2.z = 0.5f;
	quat2.w = 0.5f;
	t = 0.5;

	ld_float cosOmega = quat2.dot( quat1 );
	ld_float sinOmega = sqrt( 1.0f - cosOmega*cosOmega );
	ld_float  omega   = atan2( sinOmega , cosOmega ) ;
	ld_float  one_overSinOmega = 1.0f / sinOmega ;
	ld_float k0 = sin( ( 1.0f-t )*omega ) * one_overSinOmega ;
	ld_float k1 = sin( t*omega ) * one_overSinOmega ;

	expected.x = k0 * quat2.x + k1 * quat1.x;
	expected.y = k0 * quat2.y + k1 * quat1.y;
	expected.z = k0 * quat2.z + k1 * quat1.z;
	expected.w = k0 * quat2.w + k1 * quat1.w;
	actual = quat2.slerp( quat1, t );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );
}

void LDQuatTest::mySlerpTest()
{
	LDQuat quat1, quat2;
	LDQuat actual;
	LDQuat expected;
	//ld_float delta = 0.00001f;
	ld_float t;

	// Input : quat1{x = 1.0, y = 2.0, z = 3.0, w = 0.1}, quat2{x = 4.0, y = 5.0, z = 6.0, w = 0.2}, t = 0.0
	// 範囲外t <= 0.0fのケース
	quat1.x = 1.0f;
	quat1.y = 2.0f;
	quat1.z = 3.0f;
	quat1.w = 0.1f;
	quat2.x = 4.0f;
	quat2.y = 5.0f;
	quat2.z = 6.0f;
	quat2.w = 0.2f;
	t = 0.0f;
	expected.x = 4.0f;
	expected.y = 5.0f;
	expected.z = 6.0f;
	expected.w = 0.2f;
	actual = quat2.mySlerp( quat1, t );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );

	// Input : quat1{x = 1.0, y = 2.0, z = 3.0, w = 0.1}, quat2{x = 4.0, y = 5.0, z = 6.0, w = 0.2}, t = 1.0
	// 範囲外t >= 1.0fのケース
	quat1.x = 1.0f;
	quat1.y = 2.0f;
	quat1.z = 3.0f;
	quat1.w = 0.1f;
	quat2.x = 4.0f;
	quat2.y = 5.0f;
	quat2.z = 6.0f;
	quat2.w = 0.2f;
	t = 1.0f;
	expected.x = 1.0f;
	expected.y = 2.0f;
	expected.z = 3.0f;
	expected.w = 0.1f;
	actual = quat2.mySlerp( quat1, t );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );

	// Input : quat1{x = 0.49, y = 0.5, z = 0.5, w = 0.5}, quat2{x = 0.5, y = 0.49, z = 0.5, w = 0.5}, t = 0.5
	// cosOmega <= 0.9999fのケース
	quat1.x = 0.49f;
	quat1.y = 0.5f;
	quat1.z = 0.5f;
	quat1.w = 0.5f;
	quat2.x = 0.5f;
	quat2.y = 0.49f;
	quat2.z = 0.5f;
	quat2.w = 0.5f;
	t = 0.5f;
	LDVector3 n0 = quat2.getAxis();
	LDVector3 n1 = quat1.getAxis();
	ld_float  a0 = quat2.getAngle();
	ld_float  a1 = quat1.getAngle();
	ld_float  adiff = LDMathUtil::getAngleDiff( a1,a0 );
	ld_float  at = a0 + adiff * t;
	LDVector3 nt = blend( n0, n1, 1-t, t );
	nt.normalize();
	expected.setToRotateAxis( nt, at );
	actual = quat2.mySlerp( quat1, t );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );
}

void LDQuatTest::powTest()
{
	LDQuat quat;
	LDQuat actual;
	LDQuat expected;
	//ld_float delta = 0.00001f;
	ld_float exponent;

	// Input : quat1{x = 0.0, y = 0.0, z = 0.0, w = 1.0}, exponent = 0.0 (単位クォータニオン)
	quat.x = 0.0f;
	quat.y = 0.0f;
	quat.z = 0.0f;
	quat.w = 1.0f;
	exponent = 0.0f;
	expected.x = 0.0f;
	expected.y = 0.0f;
	expected.z = 0.0f;
	expected.w = 1.0f;
	actual = quat.pow( exponent );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );

	// Input : quat1{x = 0.1, y = 0.2, z = 0.3, w = 0.4}, exponent = 2.0 (任意の値)
	quat.x = 0.1f;
	quat.y = 0.2f;
	quat.z = 0.3f;
	quat.w = 0.4f;
	exponent = 2.0f;
	ld_float  alpha = acos( quat.w ) ;
	ld_float  newAlpha = alpha * exponent ;
	ld_float  mult = sin( newAlpha ) / sin( alpha ) ;
	expected.x = quat.x * mult;
	expected.y = quat.y * mult;
	expected.z = quat.z * mult;
	expected.w = cos( newAlpha );
	actual = quat.pow( exponent );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );
}

//------ EQuat.h ------

void LDQuatTest::setToRotateAxisTest()
{
	LDVector3 vector;
	LDQuat actual;
	LDQuat expected;
	//ld_float delta = 0.00001f;
	ld_float theta;

	// Input : vector{x = 1.0, y = 0.0, z = 0.0}, theta = 0.0 (単位ベクトル)
	vector.x = 1.0f;
	vector.y = 0.0f;
	vector.z = 0.0f;
	vector.normalize();
	theta = 0.0f;
	expected.x = 0.0f;
	expected.y = 0.0f;
	expected.z = 0.0f;
	actual.setToRotateAxis( vector, theta );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );

	// Input : vector{x = 1.0, y = 2.0, z = 3.0}, theta = EUC_PI_OVER_2 (任意の値)
	vector.x = 1.0f;
	vector.y = 2.0f;
	vector.z = 3.0f;
	vector.normalize();
	theta = LDMathUtil::PI_OVER_2;
	expected.x = vector.x * sin( theta * 0.5f );
	expected.y = vector.y * sin( theta * 0.5f );
	expected.z = vector.z * sin( theta * 0.5f );
	expected.w = cos( theta * 0.5f );
	actual.setToRotateAxis( vector, theta );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );
}

void LDQuatTest::normalizeTest()
{
	LDQuat actual;
	LDQuat expected;
	//ld_float delta = 0.00001f;
	ld_float oneOverMag;

	// Input : vector{x = 0.0, y = 0.0, z = 0.0, w = 1.0} (単位クォータニオン)
	actual.x = 0.0f;
	actual.y = 0.0f;
	actual.z = 0.0f;
	actual.w = 1.0f;
	expected.x = 0.0f;
	expected.y = 0.0f;
	expected.z = 0.0f;
	expected.w = 1.0f;
	actual.normalize();
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );

	// Input : vector{x = 1.0, y = 2.0, z = 3.0, w = 4.0} (任意の値)
	actual.x = 1.0f;
	actual.y = 2.0f;
	actual.z = 3.0f;
	actual.w = 4.0f;
	oneOverMag = 1.0f / ( ld_float )sqrt( actual.w * actual.w + actual.x * actual.x
	                                      + actual.y * actual.y + actual.z * actual.z );
	expected.x = 1.0f * oneOverMag;
	expected.y = 2.0f * oneOverMag;
	expected.z = 3.0f * oneOverMag;
	expected.w = 4.0f * oneOverMag;
	actual.normalize();
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
	QCOMPARE( expected.w, actual.w );
}
} // namespace live2d
