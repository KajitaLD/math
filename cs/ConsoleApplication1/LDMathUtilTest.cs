using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d
{
    using ld_float = Single;
    public class LDMathUtilTest : ITest
    {
        public void test()
        {
            this.wrapPiTest();
            this.getAngleDiffTest();
            this.safeAcosTest();
            this.sinCosTest();
        }

        public void wrapPiTest()
        {
            ld_float actual;
            ld_float expected;
            ld_float theta;
            //ld_float delta = 0.00001f;

            // Input : 0.0
            theta = 0.0f;
            expected = 0.0f;
            actual = LDMathUtil.wrapPi(theta);
            TestUtil.COMPARE(expected, actual);

            // Input : 2PI
            theta = LDMathUtil.PI2;
            expected = 0.0f;
            actual = LDMathUtil.wrapPi(theta);
            TestUtil.COMPARE(expected, actual);

            // Input : PI, PI±0.01におけるラップテスト
            theta = LDMathUtil.PI - 0.01f;
            expected = LDMathUtil.PI - 0.01f;
            actual = LDMathUtil.wrapPi(theta);
            TestUtil.COMPARE(expected, actual);

            theta = LDMathUtil.PI;
            expected = LDMathUtil.PI;
            actual = LDMathUtil.wrapPi(theta);
            TestUtil.COMPARE(expected, actual);

            theta = LDMathUtil.PI + 0.01f;
            expected = 0.01f - LDMathUtil.PI;
            actual = LDMathUtil.wrapPi(theta);
            TestUtil.COMPARE(expected, actual);

            // Input : -PI, -PI±0.01におけるラップテスト
            theta = -LDMathUtil.PI - 0.01f;
            expected = LDMathUtil.PI - 0.01f;
            actual = LDMathUtil.wrapPi(theta);
            TestUtil.COMPARE(expected, actual);

            theta = -LDMathUtil.PI;
            expected = -LDMathUtil.PI;
            actual = LDMathUtil.wrapPi(theta);
            TestUtil.COMPARE(expected, actual);

            theta = -LDMathUtil.PI + 0.01f;
            expected = -LDMathUtil.PI + 0.01f;
            actual = LDMathUtil.wrapPi(theta);
            TestUtil.COMPARE(expected, actual);
        }

        public void getAngleDiffTest()
        {
            ld_float actual;
            ld_float expected;
            ld_float Q1, Q2;
            //ld_float delta = 0.00001f;

            // Input : Q1 = 0.0, Q2 = 0.0
            Q1 = 0.0f;
            Q2 = 0.0f;
            expected = 0.0f;
            actual = LDMathUtil.getAngleDiff(Q1, Q2);
            TestUtil.COMPARE(expected, actual);

            // Input : Q1 = PI, Q2 = 0.0
            Q1 = LDMathUtil.PI;
            Q2 = 0.0f;
            expected = LDMathUtil.PI;
            actual = LDMathUtil.getAngleDiff(Q1, Q2);
            TestUtil.COMPARE(expected, actual);

            // Input : Q1 = PI+0.1, Q2 = 0.0
            Q1 = LDMathUtil.PI + 0.1f;
            Q2 = 0.0f;
            expected = -LDMathUtil.PI + 0.1f;
            actual = LDMathUtil.getAngleDiff(Q1, Q2);
            TestUtil.COMPARE(expected, actual);

            // Input : Q1 = -PI, Q2 = 0.0
            Q1 = -LDMathUtil.PI;
            Q2 = 0.0f;
            expected = -LDMathUtil.PI;
            actual = LDMathUtil.getAngleDiff(Q1, Q2);
            TestUtil.COMPARE(expected, actual);

            // Input : Q1 = -PI-0.1, Q2 = 0.0
            Q1 = -LDMathUtil.PI - 0.1f;
            Q2 = 0.0f;
            expected = LDMathUtil.PI - 0.1f;
            actual = LDMathUtil.getAngleDiff(Q1, Q2);
            TestUtil.COMPARE(expected, actual);
        }

        public void safeAcosTest()
        {
            ld_float actual;
            ld_float expected;
            ld_float x;
            //ld_float delta = 0.00001f;

            // Input : x = -1.0f
            x = -1.0f;
            expected = LDMathUtil.PI;
            actual = LDMathUtil.safeAcos(x);
            TestUtil.COMPARE(expected, actual);

            // Input : x = 1.0f
            x = 1.0f;
            expected = 0.0f;
            actual = LDMathUtil.safeAcos(x);
            TestUtil.COMPARE(expected, actual);
        }

        public void sinCosTest()
        {
            // sin(), cos()が呼ばれているだけなので省略します
        }
    }
}
