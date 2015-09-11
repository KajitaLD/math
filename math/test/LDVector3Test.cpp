#include "LDVector3Test.h"

namespace live2d
{
//------ EVector3.h ------
void LDVector3Test::normalizeTest()
{
	LDVector3 vector;
	ld_float expected_x;
	ld_float expected_y;
	ld_float expected_z;
	//ld_float delta = 0.00001f;

	// Input : x = 0.0, y = 0.0, z = 0.0 (ゼロベクトル)
	vector.zero();
	expected_x = 0.0f;
	expected_y = 0.0f;
	expected_z = 0.0f;
	vector.normalize();
	QCOMPARE( expected_x, vector.x );
	QCOMPARE( expected_y, vector.y );
	QCOMPARE( expected_z, vector.z );

	// Input : x = 1.0, y = 2.0, z = 3.0 (任意の値)
	vector.x = 1.0f;
	vector.y = 2.0f;
	vector.z = 3.0f;
	expected_x = vector.x / sqrt( vector.x * vector.x + vector.y * vector.y + vector.z * vector.z );
	expected_y = vector.y / sqrt( vector.x * vector.x + vector.y * vector.y + vector.z * vector.z );
	expected_z = vector.z / sqrt( vector.x * vector.x + vector.y * vector.y + vector.z * vector.z );
	vector.normalize();
	QCOMPARE( expected_x, vector.x );
	QCOMPARE( expected_y, vector.y );
	QCOMPARE( expected_z, vector.z );
}

void LDVector3Test::lengthTest()
{
	LDVector3 vector;
	ld_float actual;
	ld_float expected;
	//ld_float delta = 0.00001f;

	// Input : x = 0.0, y = 0.0, z = 0.0 (ゼロベクトル)
	vector.zero();
	expected = 0.0f;
	actual = vector.length();
	QCOMPARE( expected, actual );

	// Input : x = 1.0, y = 2.0, z = 3.0 (任意の値)
	vector.x = 1.0f;
	vector.y = 2.0f;
	vector.z = 3.0f;
	expected = sqrt( vector.x * vector.x + vector.y * vector.y + vector.z * vector.z );
	actual = vector.length();
	QCOMPARE( expected, actual );

	// 非メンバ関数lengthのテスト

	// Input : x = 0.0, y = 0.0, z = 0.0 (ゼロベクトル)
	vector.zero();
	expected = 0.0f;
	actual = length( vector );
	QCOMPARE( expected, actual );

	// Input : x = 1.0, y = 2.0, z = 3.0 (任意の値)
	vector.x = 1.0f;
	vector.y = 2.0f;
	vector.z = 3.0f;
	expected = sqrt( vector.x * vector.x + vector.y * vector.y + vector.z * vector.z );
	actual = length( vector );
	QCOMPARE( expected, actual );
}

void LDVector3Test::dotProductTest()
{
	LDVector3 vector1;
	LDVector3 vector2;
	ld_float actual;
	ld_float expected;
	//ld_float delta = 0.00001f;

	// Input : vector1{x = 0.0, y = 0.0, z = 0.0}, vector2{x = 0.0, y = 0.0, z = 0.0} (ゼロベクトル)
	vector1.zero();
	vector2.zero();
	expected = 0.0f;
	actual = vector1.dotProduct( vector2 );
	QCOMPARE( expected, actual );

	// Input : vector1{x = 1.0, y = 2.0, z = 3.0}, vector2{x = 1.0, y = 2.0, z = 3.0} (任意の値)
	vector1.x = 1.0f;
	vector1.y = 2.0f;
	vector1.z = 3.0f;
	vector2.x = 1.0f;
	vector2.y = 2.0f;
	vector2.z = 3.0f;
	expected = 14.0f;
	actual = vector1.dotProduct( vector2 );
	QCOMPARE( expected, actual );
}

//====================================================
//	非メンバ関数のテスト
//====================================================
void LDVector3Test::crossProductTest()
{
	LDVector3 vector1;
	LDVector3 vector2;
	LDVector3 actual;
	LDVector3 expected;
	//ld_float delta = 0.00001f;

	// Input : vector1{x = 0.0, y = 0.0, z = 0.0}, vector2{x = 0.0, y = 0.0, z = 0.0} (ゼロベクトル)
	vector1.zero();
	vector2.zero();
	expected.zero();
	actual = crossProduct( vector1, vector2 );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );

	// Input : vector1{x = 1.0, y = 2.0, z = 3.0}, vector2{x = 1.0, y = 2.0, z = 3.0} (任意の値)
	vector1.x = 1.0f;
	vector1.y = 2.0f;
	vector1.z = 3.0f;
	vector2.x = 1.0f;
	vector2.y = 2.0f;
	vector2.z = 3.0f;
	expected.x = vector1.y * vector2.z - vector1.z * vector2.y;
	expected.y = vector1.z * vector2.x - vector1.x * vector2.z;
	expected.z = vector1.x * vector2.y - vector1.y * vector2.x;
	actual = crossProduct( vector1, vector2 );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
}

void LDVector3Test::dotTest()
{
	LDVector3 vector1;
	LDVector3 vector2;
	ld_float actual;
	ld_float expected;
	//ld_float delta = 0.00001f;

	// Input : vector1{x = 0.0, y = 0.0, z = 0.0}, vector2{x = 0.0, y = 0.0, z = 0.0} (ゼロベクトル)
	vector1.zero();
	vector2.zero();
	expected = 0.0f;
	actual = dot( vector1, vector2 );
	QCOMPARE( expected, actual );

	// Input : vector1{x = 1.0, y = 2.0, z = 3.0}, vector2{x = 1.0, y = 2.0, z = 3.0} (任意の値)
	vector1.x = 1.0f;
	vector1.y = 2.0f;
	vector1.z = 3.0f;
	vector2.x = 1.0f;
	vector2.y = 2.0f;
	vector2.z = 3.0f;
	expected = vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
	actual = dot( vector1, vector2 );
	QCOMPARE( expected, actual );
}

void LDVector3Test::distanceTest()
{
	LDVector3 vector1;
	LDVector3 vector2;
	ld_float actual;
	ld_float expected;
	//ld_float delta = 0.00001f;

	// Input : vector1{x = 0.0, y = 0.0, z = 0.0}, vector2{x = 0.0, y = 0.0, z = 0.0} (ゼロベクトル)
	vector1.zero();
	vector2.zero();
	expected = 0.0f;
	actual = distance( vector1, vector2 );
	QCOMPARE( expected, actual );

	// Input : vector1{x = 1.0, y = 2.0, z = 3.0}, vector2{x = 4.0, y = 5.0, z = 6.0} (任意の値)
	vector1.x = 1.0f;
	vector1.y = 2.0f;
	vector1.z = 3.0f;
	vector2.x = 4.0f;
	vector2.y = 5.0f;
	vector2.z = 6.0f;

	ld_float dx = vector1.x - vector2.x;
	ld_float dy = vector1.y - vector2.y;
	ld_float dz = vector1.z - vector2.z;
	expected = sqrt( dx * dx + dy * dy + dz * dz );
	actual = distance( vector1, vector2 );
	QCOMPARE( expected, actual );
}

void LDVector3Test::blendTest()
{
	LDVector3 vector1;
	LDVector3 vector2;
	LDVector3 actual;
	LDVector3 expected;
	//ld_float delta = 0.00001f;
	ld_float t1;
	ld_float t2;

	// Input : vector1{x = 0.0, y = 0.0, z = 0.0}
	//		   vector2{x = 0.0, y = 0.0, z = 0.0}, t1 = 0.0, t2 = 0.0 (ゼロベクトル)
	vector1.zero();
	vector2.zero();
	t1 = 0.0f;
	t2 = 0.0f;
	expected.zero();
	actual = blend( vector1, vector2, t1, t2 );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );

	// Input : vector1{x = 1.0, y = 2.0, z = 3.0}
	//		   vector2{x = 4.0, y = 5.0, z = 6.0}, t1 = 1.0, t2 = 2.0 (任意の値)
	vector1.x = 1.0f;
	vector1.y = 2.0f;
	vector1.z = 3.0f;
	vector2.x = 4.0f;
	vector2.y = 5.0f;
	vector2.z = 6.0f;
	t1 = 1.0f;
	t2 = 2.0f;
	expected.x = vector1.x * t1 + vector2.x * t2;
	expected.y = vector1.y * t1 + vector2.y * t2;
	expected.z = vector1.z * t1 + vector2.z * t2;
	actual = blend( vector1, vector2, t1, t2 );
	QCOMPARE( expected.x, actual.x );
	QCOMPARE( expected.y, actual.y );
	QCOMPARE( expected.z, actual.z );
}
} // namespace live2d
