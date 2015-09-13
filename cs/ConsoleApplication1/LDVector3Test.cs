using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d
{
    using ld_float = System.Single;
    public class LDVector3Test : ITest
    {
        public void test()
        {
            normalizeTest();

            lengthTest();

            dotProductTest();

            //====================================================
            //	非メンバ関数のテスト
            //====================================================
            crossProductTest();

            dotTest();

            distanceTest();

            blendTest();

        }
        public void normalizeTest()
        {
            LDVector3 vector = new LDVector3();
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
            TestUtil.COMPARE(expected_x, vector.x);
            TestUtil.COMPARE(expected_y, vector.y);
            TestUtil.COMPARE(expected_z, vector.z);

            // Input : x = 1.0, y = 2.0, z = 3.0 (任意の値)
            vector.x = 1.0f;
            vector.y = 2.0f;
            vector.z = 3.0f;
            expected_x = vector.x / (ld_float)Math.Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
            expected_y = vector.y / (ld_float)Math.Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
            expected_z = vector.z / (ld_float)Math.Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
            vector.normalize();
            TestUtil.COMPARE(expected_x, vector.x);
            TestUtil.COMPARE(expected_y, vector.y);
            TestUtil.COMPARE(expected_z, vector.z);
        }

        public void lengthTest()
        {
            LDVector3 vector = new LDVector3();
            ld_float actual;
            ld_float expected;
            //ld_float delta = 0.00001f;

            // Input : x = 0.0, y = 0.0, z = 0.0 (ゼロベクトル)
            vector.zero();
            expected = 0.0f;
            actual = vector.length();
            TestUtil.COMPARE(expected, actual);

            // Input : x = 1.0, y = 2.0, z = 3.0 (任意の値)
            vector.x = 1.0f;
            vector.y = 2.0f;
            vector.z = 3.0f;
            expected = (ld_float)Math.Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
            actual = vector.length();
            TestUtil.COMPARE(expected, actual);

            // 非メンバ関数lengthのテスト

            // Input : x = 0.0, y = 0.0, z = 0.0 (ゼロベクトル)
            vector.zero();
            expected = 0.0f;
            actual = LDVector3.length(vector);
            TestUtil.COMPARE(expected, actual);

            // Input : x = 1.0, y = 2.0, z = 3.0 (任意の値)
            vector.x = 1.0f;
            vector.y = 2.0f;
            vector.z = 3.0f;
            expected = (ld_float)Math.Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
            actual = LDVector3.length(vector);
            TestUtil.COMPARE(expected, actual);
        }

        public void dotProductTest()
        {
            LDVector3 vector1 = new LDVector3();
            LDVector3 vector2 = new LDVector3();
            ld_float actual;
            ld_float expected;
            //ld_float delta = 0.00001f;

            // Input : vector1{x = 0.0, y = 0.0, z = 0.0}, vector2{x = 0.0, y = 0.0, z = 0.0} (ゼロベクトル)
            vector1.zero();
            vector2.zero();
            expected = 0.0f;
            actual = vector1.dotProduct(vector2);
            TestUtil.COMPARE(expected, actual);

            // Input : vector1{x = 1.0, y = 2.0, z = 3.0}, vector2{x = 1.0, y = 2.0, z = 3.0} (任意の値)
            vector1.x = 1.0f;
            vector1.y = 2.0f;
            vector1.z = 3.0f;
            vector2.x = 1.0f;
            vector2.y = 2.0f;
            vector2.z = 3.0f;
            expected = 14.0f;
            actual = vector1.dotProduct(vector2);
            TestUtil.COMPARE(expected, actual);
        }

        //====================================================
        //	非メンバ関数のテスト
        //====================================================
        public void crossProductTest()
        {
            LDVector3 vector1 = new LDVector3();
            LDVector3 vector2 = new LDVector3();
            LDVector3 actual = new LDVector3();
            LDVector3 expected = new LDVector3();
            //ld_float delta = 0.00001f;

            // Input : vector1{x = 0.0, y = 0.0, z = 0.0}, vector2{x = 0.0, y = 0.0, z = 0.0} (ゼロベクトル)
            vector1.zero();
            vector2.zero();
            expected.zero();
            actual = LDVector3.crossProduct(vector1, vector2);
            TestUtil.COMPARE(expected.x, actual.x);
            TestUtil.COMPARE(expected.y, actual.y);
            TestUtil.COMPARE(expected.z, actual.z);

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
            actual = LDVector3.crossProduct(vector1, vector2);
            TestUtil.COMPARE(expected.x, actual.x);
            TestUtil.COMPARE(expected.y, actual.y);
            TestUtil.COMPARE(expected.z, actual.z);
        }

        public void dotTest()
        {
            LDVector3 vector1 = new LDVector3();
            LDVector3 vector2 = new LDVector3();
            ld_float actual;
            ld_float expected;
            //ld_float delta = 0.00001f;

            // Input : vector1{x = 0.0, y = 0.0, z = 0.0}, vector2{x = 0.0, y = 0.0, z = 0.0} (ゼロベクトル)
            vector1.zero();
            vector2.zero();
            expected = 0.0f;
            actual = LDVector3.dot(vector1, vector2);
            TestUtil.COMPARE(expected, actual);

            // Input : vector1{x = 1.0, y = 2.0, z = 3.0}, vector2{x = 1.0, y = 2.0, z = 3.0} (任意の値)
            vector1.x = 1.0f;
            vector1.y = 2.0f;
            vector1.z = 3.0f;
            vector2.x = 1.0f;
            vector2.y = 2.0f;
            vector2.z = 3.0f;
            expected = vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
            actual = LDVector3.dot(vector1, vector2);
            TestUtil.COMPARE(expected, actual);
        }

        public void distanceTest()
        {
            LDVector3 vector1 = new LDVector3();
            LDVector3 vector2 = new LDVector3();
            ld_float actual;
            ld_float expected;
            //ld_float delta = 0.00001f;

            // Input : vector1{x = 0.0, y = 0.0, z = 0.0}, vector2{x = 0.0, y = 0.0, z = 0.0} (ゼロベクトル)
            vector1.zero();
            vector2.zero();
            expected = 0.0f;
            actual = LDVector3.distance(vector1, vector2);
            TestUtil.COMPARE(expected, actual);

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
            expected = (ld_float)Math.Sqrt(dx * dx + dy * dy + dz * dz);
            actual = LDVector3.distance(vector1, vector2);
            TestUtil.COMPARE(expected, actual);
        }

        public void blendTest()
        {
            LDVector3 vector1 = new LDVector3();
            LDVector3 vector2 = new LDVector3();
            LDVector3 actual = new LDVector3();
            LDVector3 expected = new LDVector3();
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
            actual = LDVector3.blend(vector1, vector2, t1, t2);
            TestUtil.COMPARE(expected.x, actual.x);
            TestUtil.COMPARE(expected.y, actual.y);
            TestUtil.COMPARE(expected.z, actual.z);

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
            actual = LDVector3.blend(vector1, vector2, t1, t2);
            TestUtil.COMPARE(expected.x, actual.x);
            TestUtil.COMPARE(expected.y, actual.y);
            TestUtil.COMPARE(expected.z, actual.z);
        }
    }
}
