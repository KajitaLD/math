using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d
{
    using ld_float = Single;
    public class LDMatrix43Test : ITest
    {
        public void test()
        {
            this.identityTest();
            this.setMatrixTest();
            this.multTest();
            this.translateTest();
            this.scaleTest();
            this.rotateXTest();
            this.rotateYTest();
            this.rotateZTest();
            this.transformTest();
            this.fromQuaterionTest();
            this.getInverseTest();
        }
        //------ EMatrix43.cpp ------
        public void identityTest()
        {
            LDMatrix43 actual=new LDMatrix43();
            LDMatrix43 expected = new LDMatrix43();
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
            actual.identity();
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m14, actual.m14);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m24, actual.m24);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
            TestUtil.COMPARE(expected.m34, actual.m34);
        }

        public void setMatrixTest()
        {
            LDMatrix43 matrix = new LDMatrix43();
            LDMatrix43 actual = new LDMatrix43();
            LDMatrix43 expected = new LDMatrix43();
            //ld_float delta = 0.00001f;
            ld_float[] m=new ld_float[12];

            // EMatrix43.setMatrix( const ld_float* _m )　のテスト
            for (int i = 0; i < 12; ++i)
            {
                m[i] = 1.0f;
            }
            actual.setMatrix(m);
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
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m14, actual.m14);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m24, actual.m24);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
            TestUtil.COMPARE(expected.m34, actual.m34);

            // EMatrix43.setMatrix( const EMatrix43 &m2 )　のテスト
            for (int i = 0; i < 12; ++i)
            {
                m[i] = 2.0f;
            }
            matrix.setMatrix(m);
            actual.setMatrix(matrix);
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
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m14, actual.m14);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m24, actual.m24);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
            TestUtil.COMPARE(expected.m34, actual.m34);
        }

        public void multTest()
        {
            LDMatrix43 matrix1 = new LDMatrix43();
            LDMatrix43 matrix2 = new LDMatrix43();
            LDMatrix43 expected = new LDMatrix43();
            LDMatrix43 actual = new LDMatrix43();
            //ld_float delta = 0.00001f;

            // Input : matrix1 = 単位行列, matrix2 = 単位行列 (mult_fastのテスト)
            matrix1.mult(matrix2, actual);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m14, actual.m14);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m24, actual.m24);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
            TestUtil.COMPARE(expected.m34, actual.m34);

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

            expected.m[0] = matrix1.m[0] * matrix2.m[0] + matrix1.m[4] * matrix2.m[1] +
                            matrix1.m[8] * matrix2.m[1];
            expected.m[1] = matrix1.m[1] * matrix2.m[0] + matrix1.m[5] * matrix2.m[1] +
                            matrix1.m[9] * matrix2.m[2];
            expected.m[2] = matrix1.m[2] * matrix2.m[0] + matrix1.m[6] * matrix2.m[1] +
                            matrix1.m[10] * matrix2.m[2];
            expected.m[4] = matrix1.m[0] * matrix2.m[4] + matrix1.m[4] * matrix2.m[5] +
                            matrix1.m[8] * matrix2.m[6];
            expected.m[5] = matrix1.m[1] * matrix2.m[4] + matrix1.m[5] * matrix2.m[5] +
                            matrix1.m[9] * matrix2.m[6];
            expected.m[6] = matrix1.m[2] * matrix2.m[4] + matrix1.m[6] * matrix2.m[5] +
                            matrix1.m[10] * matrix2.m[6];
            expected.m[8] = matrix1.m[0] * matrix2.m[8] + matrix1.m[4] * matrix2.m[9] +
                            matrix1.m[8] * matrix2.m[10];
            expected.m[9] = matrix1.m[1] * matrix2.m[8] + matrix1.m[5] * matrix2.m[9] +
                            matrix1.m[9] * matrix2.m[10];
            expected.m[10] = matrix1.m[2] * matrix2.m[8] + matrix1.m[6] * matrix2.m[9] +
                            matrix1.m[10] * matrix2.m[10];
            //expected.m[12]= matrix1.m[0] * matrix2.m[12]+ matrix1.m[4] * matrix2.m[13] +
            //        matrix1.m[8] * matrix2.m[14]+ matrix1.m[12];
            //expected.m[13]= matrix1.m[1] * matrix2.m[12]+ matrix1.m[5] * matrix2.m[13] +
            //        matrix1.m[9] * matrix2.m[14]+ matrix1.m[13];
            //expected.m[14]= matrix1.m[2] * matrix2.m[12]+ matrix1.m[6] * matrix2.m[13] +
            //        matrix1.m[10]* matrix2.m[14]+ matrix1.m[14];

            matrix1.mult(matrix2, actual);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m14, actual.m14);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m24, actual.m24);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
            TestUtil.COMPARE(expected.m34, actual.m34);

            // Input : matrix1, matrix2 = 任意の値 (mult_safeのテスト) <- assertのため分岐できず
            //matrix1.mult(matrix2, &matrix1);
        }

        public void translateTest()
        {
            LDMatrix43 expected = new LDMatrix43();
            LDMatrix43 actual = new LDMatrix43();
            //ld_float delta = 0.00001f;

            // Input : actual = 単位行列, x = 0.0, y = 0.0, z = 0.0 (ゼロ)
            actual.translate(0.0f, 0.0f, 0.0f);
            TestUtil.COMPARE(expected.m14, actual.m14);
            TestUtil.COMPARE(expected.m24, actual.m24);
            TestUtil.COMPARE(expected.m34, actual.m34);

            // Input : actual = 単位行列, x = 1.0, y = 2.0, z = 3.0 (任意の値)
            expected.m14 = 1.0f;
            expected.m24 = 2.0f;
            expected.m34 = 3.0f;
            actual.translate(1.0f, 2.0f, 3.0f);
            TestUtil.COMPARE(expected.m14, actual.m14);
            TestUtil.COMPARE(expected.m24, actual.m24);
            TestUtil.COMPARE(expected.m34, actual.m34);

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
            expected.m14 = actual.m11 * x + actual.m12 * y + actual.m13 * z + actual.m14;
            expected.m24 = actual.m21 * x + actual.m22 * y + actual.m23 * z + actual.m24;
            expected.m34 = actual.m31 * x + actual.m32 * y + actual.m33 * z + actual.m34;
            actual.translate(x, y, z);
            TestUtil.COMPARE(expected.m14, actual.m14);
            TestUtil.COMPARE(expected.m24, actual.m24);
            TestUtil.COMPARE(expected.m34, actual.m34);
        }

        public void scaleTest()
        {
            LDMatrix43 expected = new LDMatrix43();
            LDMatrix43 actual = new LDMatrix43();
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
            actual.scale(0.0f, 0.0f, 0.0f);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);

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
            expected.m11 = actual.m11 * x;
            expected.m12 = actual.m12 * y;
            expected.m13 = actual.m13 * z;
            expected.m21 = actual.m21 * x;
            expected.m22 = actual.m22 * y;
            expected.m23 = actual.m23 * z;
            expected.m31 = actual.m31 * x;
            expected.m32 = actual.m32 * y;
            expected.m33 = actual.m33 * z;
            actual.scale(x, y, z);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
        }

        public void rotateXTest()
        {
            LDMatrix43 expected = new LDMatrix43();
            LDMatrix43 actual = new LDMatrix43();
            //ld_float delta = 0.00001f;
            ld_float tmp;
            ld_float theta;

            // Input : actual = 単位行列, theta = 0.0 (ゼロ)
            tmp = expected.m12;
            expected.m12 = tmp * (float)Math.Cos(0.0f) + expected.m13 * (float)Math.Sin(0.0f);
            expected.m13 = tmp * -(float)Math.Sin(0.0f) + expected.m13 * (float)Math.Cos(0.0f);
            tmp = expected.m22;
            expected.m22 = tmp * (float)Math.Cos(0.0f) + expected.m23 * (float)Math.Sin(0.0f);
            expected.m23 = tmp * -(float)Math.Sin(0.0f) + expected.m23 * (float)Math.Cos(0.0f);
            tmp = expected.m32;
            expected.m32 = tmp * (float)Math.Cos(0.0f) + expected.m33 * (float)Math.Sin(0.0f);
            expected.m33 = tmp * -(float)Math.Sin(0.0f) + expected.m33 * (float)Math.Cos(0.0f);
            actual.rotateX(0.0f);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);

            // Input : actual = 任意の値, theta = PI/4.0f; (任意の値)
            theta = LDMathUtil.PI / 4.0f;
            actual.m11 = 1.0f;
            actual.m12 = 2.0f;
            actual.m13 = 3.0f;
            actual.m21 = 1.0f;
            actual.m22 = 2.0f;
            actual.m23 = 3.0f;
            actual.m31 = 1.0f;
            actual.m32 = 2.0f;
            actual.m33 = 3.0f;
            expected.m11 = 1.0f;
            expected.m12 = 2.0f;
            expected.m13 = 3.0f;
            expected.m21 = 1.0f;
            expected.m22 = 2.0f;
            expected.m23 = 3.0f;
            expected.m31 = 1.0f;
            expected.m32 = 2.0f;
            expected.m33 = 3.0f;
            tmp = expected.m12;
            expected.m12 = tmp * (float)Math.Cos(theta) + expected.m13 * (float)Math.Sin(theta);
            expected.m13 = tmp * -(float)Math.Sin(theta) + expected.m13 * (float)Math.Cos(theta);
            tmp = expected.m22;
            expected.m22 = tmp * (float)Math.Cos(theta) + expected.m23 * (float)Math.Sin(theta);
            expected.m23 = tmp * -(float)Math.Sin(theta) + expected.m23 * (float)Math.Cos(theta);
            tmp = expected.m32;
            expected.m32 = tmp * (float)Math.Cos(theta) + expected.m33 * (float)Math.Sin(theta);
            expected.m33 = tmp * -(float)Math.Sin(theta) + expected.m33 * (float)Math.Cos(theta);
            actual.rotateX(theta);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
        }

        public void rotateYTest()
        {
            LDMatrix43 expected = new LDMatrix43();
            LDMatrix43 actual = new LDMatrix43();
            //ld_float delta = 0.00001f;
            ld_float tmp;
            ld_float theta;

            // Input : actual = 単位行列, theta = 0.0 (ゼロ)
            tmp = expected.m11;
            expected.m11 = tmp * (float)Math.Cos(0.0f) + expected.m13 * -(float)Math.Sin(0.0f);
            expected.m13 = tmp * (float)Math.Sin(0.0f) + expected.m13 * (float)Math.Cos(0.0f);
            tmp = expected.m21;
            expected.m21 = tmp * (float)Math.Cos(0.0f) + expected.m23 * -(float)Math.Sin(0.0f);
            expected.m23 = tmp * (float)Math.Sin(0.0f) + expected.m23 * (float)Math.Cos(0.0f);
            tmp = expected.m31;
            expected.m31 = tmp * (float)Math.Cos(0.0f) + expected.m33 * -(float)Math.Sin(0.0f);
            expected.m33 = tmp * (float)Math.Sin(0.0f) + expected.m33 * (float)Math.Cos(0.0f);
            actual.rotateY(0.0f);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);

            // Input : actual = 任意の値, theta = PI/4.0f; (任意の値)
            theta = LDMathUtil.PI / 4.0f;
            actual.m11 = 1.0f;
            actual.m12 = 2.0f;
            actual.m13 = 3.0f;
            actual.m21 = 1.0f;
            actual.m22 = 2.0f;
            actual.m23 = 3.0f;
            actual.m31 = 1.0f;
            actual.m32 = 2.0f;
            actual.m33 = 3.0f;
            expected.m11 = 1.0f;
            expected.m12 = 2.0f;
            expected.m13 = 3.0f;
            expected.m21 = 1.0f;
            expected.m22 = 2.0f;
            expected.m23 = 3.0f;
            expected.m31 = 1.0f;
            expected.m32 = 2.0f;
            expected.m33 = 3.0f;
            tmp = expected.m11;
            expected.m11 = tmp * (float)Math.Cos(theta) + expected.m13 * -(float)Math.Sin(theta);
            expected.m13 = tmp * (float)Math.Sin(theta) + expected.m13 * (float)Math.Cos(theta);
            tmp = expected.m21;
            expected.m21 = tmp * (float)Math.Cos(theta) + expected.m23 * -(float)Math.Sin(theta);
            expected.m23 = tmp * (float)Math.Sin(theta) + expected.m23 * (float)Math.Cos(theta);
            tmp = expected.m31;
            expected.m31 = tmp * (float)Math.Cos(theta) + expected.m33 * -(float)Math.Sin(theta);
            expected.m33 = tmp * (float)Math.Sin(theta) + expected.m33 * (float)Math.Cos(theta);
            actual.rotateY(theta);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
        }

        public void rotateZTest()
        {
            LDMatrix43 expected = new LDMatrix43();
            LDMatrix43 actual = new LDMatrix43();
            //ld_float delta = 0.00001f;
            ld_float tmp;
            ld_float theta;

            // Input : actual = 単位行列, theta = 0.0 (ゼロ)
            tmp = expected.m11;
            expected.m11 = tmp * (float)Math.Cos(0.0f) + expected.m12 * (float)Math.Sin(0.0f);
            expected.m12 = tmp * -(float)Math.Sin(0.0f) + expected.m12 * (float)Math.Cos(0.0f);
            tmp = expected.m21;
            expected.m21 = tmp * (float)Math.Cos(0.0f) + expected.m22 * (float)Math.Sin(0.0f);
            expected.m22 = tmp * -(float)Math.Sin(0.0f) + expected.m22 * (float)Math.Cos(0.0f);
            tmp = expected.m31;
            expected.m31 = tmp * (float)Math.Cos(0.0f) + expected.m32 * (float)Math.Sin(0.0f);
            expected.m32 = tmp * -(float)Math.Sin(0.0f) + expected.m32 * (float)Math.Cos(0.0f);
            actual.rotateZ(0.0f);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);

            // Input : actual = 任意の値, theta = PI/4.0f; (任意の値)
            theta = LDMathUtil.PI / 4.0f;
            actual.m11 = 1.0f;
            actual.m12 = 2.0f;
            actual.m13 = 3.0f;
            actual.m21 = 1.0f;
            actual.m22 = 2.0f;
            actual.m23 = 3.0f;
            actual.m31 = 1.0f;
            actual.m32 = 2.0f;
            actual.m33 = 3.0f;
            expected.m11 = 1.0f;
            expected.m12 = 2.0f;
            expected.m13 = 3.0f;
            expected.m21 = 1.0f;
            expected.m22 = 2.0f;
            expected.m23 = 3.0f;
            expected.m31 = 1.0f;
            expected.m32 = 2.0f;
            expected.m33 = 3.0f;
            tmp = expected.m11;
            expected.m11 = tmp * (float)Math.Cos(theta) + expected.m12 * (float)Math.Sin(theta);
            expected.m12 = tmp * -(float)Math.Sin(theta) + expected.m12 * (float)Math.Cos(theta);
            tmp = expected.m21;
            expected.m21 = tmp * (float)Math.Cos(theta) + expected.m22 * (float)Math.Sin(theta);
            expected.m22 = tmp * -(float)Math.Sin(theta) + expected.m22 * (float)Math.Cos(theta);
            tmp = expected.m31;
            expected.m31 = tmp * (float)Math.Cos(theta) + expected.m32 * (float)Math.Sin(theta);
            expected.m32 = tmp * -(float)Math.Sin(theta) + expected.m32 * (float)Math.Cos(theta);
            actual.rotateZ(theta);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
        }

        public void transformTest()
        {
            LDVector3 vector=new LDVector3();
            LDVector3 expected = new LDVector3();
            LDVector3 actual = new LDVector3();
            LDMatrix43 matrix=new LDMatrix43();
            //ld_float delta = 0.00001f;

            // Input : matrix = 単位行列, vector = 0.0 (ゼロ)
            vector.zero();
            expected.x = 0.0f;
            expected.y = 0.0f;
            expected.z = 0.0f;
            actual = matrix.transform(vector);
            TestUtil.COMPARE(expected.x, actual.x);
            TestUtil.COMPARE(expected.y, actual.y);
            TestUtil.COMPARE(expected.z, actual.z);

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
            actual = matrix.transform(vector);
            TestUtil.COMPARE(expected.x, actual.x);
            TestUtil.COMPARE(expected.y, actual.y);
            TestUtil.COMPARE(expected.z, actual.z);

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
            matrix.transform(vector, out vector);
            TestUtil.COMPARE(expected.x, vector.x);
            TestUtil.COMPARE(expected.y, actual.y);
            TestUtil.COMPARE(expected.z, actual.z);
        }

        public void fromQuaterionTest()
        {
            LDQuat quat=new LDQuat(0.0f, 0.0f, 0.0f, 0.0f );
            LDMatrix43 expected=new LDMatrix43();
            LDMatrix43 actual=new LDMatrix43();
            //ld_float delta = 0.00001f;

            // Input : actual = 単位行列, quat = 0.0 (ゼロ)
            actual.fromQuaterion(quat);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);

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
            actual.fromQuaterion(quat);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
        }

        public void getInverseTest()
        {
            LDMatrix43 expected=new LDMatrix43();
            LDMatrix43 actual = new LDMatrix43();
            LDMatrix43 matrix = new LDMatrix43();
            //ld_float delta = 0.00001f;
            ld_float d;

            // Input : matrix = 単位行列
            d = matrix.getDeterminant();
            expected.m11 = (matrix.m22 * matrix.m33 - matrix.m23 * matrix.m32) * d;
            expected.m12 = (matrix.m13 * matrix.m32 - matrix.m12 * matrix.m33) * d;
            expected.m13 = (matrix.m12 * matrix.m23 - matrix.m13 * matrix.m22) * d;
            expected.m21 = (matrix.m23 * matrix.m31 - matrix.m21 * matrix.m33) * d;
            expected.m22 = (matrix.m11 * matrix.m33 - matrix.m13 * matrix.m31) * d;
            expected.m23 = (matrix.m13 * matrix.m21 - matrix.m11 * matrix.m23) * d;
            expected.m31 = (matrix.m21 * matrix.m32 - matrix.m22 * matrix.m31) * d;
            expected.m32 = (matrix.m12 * matrix.m31 - matrix.m11 * matrix.m32) * d;
            expected.m33 = (matrix.m11 * matrix.m22 - matrix.m12 * matrix.m21) * d;
            expected.tx = -(matrix.tx * expected.m11 + matrix.ty * expected.m21 + matrix.tz * expected.m31);
            expected.ty = -(matrix.tx * expected.m12 + matrix.ty * expected.m22 + matrix.tz * expected.m32);
            expected.tz = -(matrix.tx * expected.m13 + matrix.ty * expected.m23 + matrix.tz * expected.m33);
            matrix.getInverse(out actual);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
            TestUtil.COMPARE(expected.tx, actual.tx);
            TestUtil.COMPARE(expected.ty, actual.ty);
            TestUtil.COMPARE(expected.tz, actual.tz);

            /*
            // Input : matrix = 得意行列のケース。assertが起こるためコメントアウト
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
            d = matrix.getDeterminant();
            expected.m11 = (matrix.m22 * matrix.m33 - matrix.m23 * matrix.m32) * d;
            expected.m12 = (matrix.m13 * matrix.m32 - matrix.m12 * matrix.m33) * d;
            expected.m13 = (matrix.m12 * matrix.m23 - matrix.m13 * matrix.m22) * d;
            expected.m21 = (matrix.m23 * matrix.m31 - matrix.m21 * matrix.m33) * d;
            expected.m22 = (matrix.m11 * matrix.m33 - matrix.m13 * matrix.m31) * d;
            expected.m23 = (matrix.m13 * matrix.m21 - matrix.m11 * matrix.m23) * d;
            expected.m31 = (matrix.m21 * matrix.m32 - matrix.m22 * matrix.m31) * d;
            expected.m32 = (matrix.m12 * matrix.m31 - matrix.m11 * matrix.m32) * d;
            expected.m33 = (matrix.m11 * matrix.m22 - matrix.m12 * matrix.m21) * d;
            expected.tx  =-(matrix.tx * expected.m11 + matrix.ty * expected.m21 + matrix.tz * expected.m31);
            expected.ty  =-(matrix.tx * expected.m12 + matrix.ty * expected.m22 + matrix.tz * expected.m32);
            expected.tz  =-(matrix.tx * expected.m13 + matrix.ty * expected.m23 + matrix.tz * expected.m33);
            matrix.getInverse(&actual);
            TestUtil.COMPARE(expected.m11, actual.m11);
            TestUtil.COMPARE(expected.m12, actual.m12);
            TestUtil.COMPARE(expected.m13, actual.m13);
            TestUtil.COMPARE(expected.m21, actual.m21);
            TestUtil.COMPARE(expected.m22, actual.m22);
            TestUtil.COMPARE(expected.m23, actual.m23);
            TestUtil.COMPARE(expected.m31, actual.m31);
            TestUtil.COMPARE(expected.m32, actual.m32);
            TestUtil.COMPARE(expected.m33, actual.m33);
            TestUtil.COMPARE(expected.tx, actual.tx);
            TestUtil.COMPARE(expected.ty, actual.ty);
            TestUtil.COMPARE(expected.tz, actual.tz);
            */
        }
    }
}
