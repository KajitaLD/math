using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d
{
    using ld_float = Single;

    public class LDEulerAnglesTest:ITest
    {
        public void test()
        {
            this.canonizeTest();
            this.fromInertialToObjectQuaternionTest();
            this.fromObjectToInertialQuaternionTest();
            this.fromWorldToObjectMatrixTest();
        }

        public void canonizeTest()
        {
            
            LDEulerAngles actual=new LDEulerAngles();
            LDEulerAngles expected = new LDEulerAngles();
            //ld_float delta = 0.00001f;

            // Input : heading = 0.0, pitch = 0.0, bank = 0.0 (ゼロ)
            actual.identity();
            expected.identity();
            actual.canonize();
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);

            // Input : heading = EMathUtil.PI_OVER_2, pitch = -EMathUtil.PI_OVER_2 - 0.1,
            //       bank    = EMathUtil.PI_OVER_2 (pitch < - EMathUtil.PI_OVER_2のケース)
            actual.heading = LDMathUtil.PI_OVER_2;
            actual.pitch = -LDMathUtil.PI_OVER_2 - 0.1f;
            actual.bank = LDMathUtil.PI_OVER_2;
            expected.heading = LDMathUtil.wrapPi(actual.heading + LDMathUtil.PI);
            expected.pitch = -LDMathUtil.PI - actual.pitch;
            expected.bank = LDMathUtil.wrapPi(actual.bank + LDMathUtil.PI);
            actual.canonize();
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);

            // Input : heading = EMathUtil.PI_OVER_2, pitch = EMathUtil.PI_OVER_2 + 0.1,
            //       bank    = EMathUtil.PI_OVER_2 (pitch > EMathUtil.PI_OVER_2のケース)
            actual.heading = LDMathUtil.PI_OVER_2;
            actual.pitch = LDMathUtil.PI_OVER_2 + 0.1f;
            actual.bank = LDMathUtil.PI_OVER_2;
            expected.heading = LDMathUtil.wrapPi(actual.heading + LDMathUtil.PI);
            expected.pitch = LDMathUtil.PI - actual.pitch;
            expected.bank = LDMathUtil.wrapPi(actual.bank + LDMathUtil.PI);
            actual.canonize();
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);

            // Input : heading = EMathUtil.PI_OVER_2, pitch = EMathUtil.PI_OVER_2,
            //       bank    = EMathUtil.PI_OVER_2 (全てPI_OVER_2, ジンバルロックのケース)
            actual.heading = LDMathUtil.PI_OVER_2;
            actual.pitch = LDMathUtil.PI_OVER_2;
            actual.bank = LDMathUtil.PI_OVER_2;
            expected.heading = actual.heading + actual.bank;
            expected.pitch = LDMathUtil.PI_OVER_2;
            expected.bank = 0.0f;
            actual.canonize();
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);
        }

        public void fromObjectToInertialQuaternionTest()
        {
            LDQuat quat=new LDQuat(0.0f, 0.0f, 0.0f, 0.0f );
            LDEulerAngles actual=new LDEulerAngles();
            LDEulerAngles expected=new LDEulerAngles();
            //ld_float delta = 0.00001f;
            ld_float sp;

            // Input : x = 0.0, y = 0.0, z = 0.0, w = 0.0 (ゼロクォータニオン)
            actual.identity();
            expected.identity();
            actual.fromObjectToInertialQuaternion(quat);
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);

            // Input : x = 1.0, y = 0.0, z = 0.0, w = 1.0 (ジンバルロックのケース)
            quat.x = 1.0f;
            quat.y = 0.0f;
            quat.z = 0.0f;
            quat.w = 1.0f;
            sp = -2.0f * (quat.y * quat.z - quat.w * quat.x);
            expected.heading = (float)Math.Atan2(-quat.x * quat.z + quat.w * quat.y,
                                      0.5f - quat.y * quat.y - quat.z * quat.z);
            expected.pitch = LDMathUtil.PI_OVER_2 * sp;
            expected.bank = 0.0f;
            actual.fromObjectToInertialQuaternion(quat);
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);

            // Input : x = 1.0, y = 0.25, z = 0.25, w = 0.5 (任意の値. 角度計算のケース)
            quat.x = 1.0f;
            quat.y = 0.25f;
            quat.z = 0.25f;
            quat.w = 0.5f;
            sp = -2.0f * (quat.y * quat.z - quat.w * quat.x);
            expected.heading = (float)Math.Atan2(quat.x * quat.z + quat.w * quat.y,
                                      0.5f - quat.x * quat.x - quat.y * quat.y);
            expected.pitch = (float)Math.Asin(sp);
            expected.bank = (float)Math.Atan2(quat.x * quat.y + quat.w * quat.z,
                                      0.5f - quat.x * quat.x - quat.z * quat.z);
            actual.fromObjectToInertialQuaternion(quat);
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);
        }

        public void fromInertialToObjectQuaternionTest()
        {
            LDQuat quat=new LDQuat(0.0f, 0.0f, 0.0f, 0.0f );
            LDEulerAngles actual=new LDEulerAngles();
            LDEulerAngles expected=new LDEulerAngles();
            //ld_float delta = 0.00001f;
            ld_float sp;

            // Input : x = 0.0, y = 0.0, z = 0.0, w = 0.0 (ゼロクォータニオン)
            actual.identity();
            expected.identity();
            actual.fromInertialToObjectQuaternion(quat);
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);

            // Input : x = 1.0, y = 0.0, z = 0.0, w = 1.0 (ジンバルロックのケース)
            quat.x = 1.0f;
            quat.y = 0.0f;
            quat.z = 0.0f;
            quat.w = 1.0f;
            sp = -2.0f * (quat.y * quat.z - quat.w * quat.x);
            expected.heading = (float)Math.Atan2(-quat.x * quat.z + quat.w * quat.y,
                                      0.5f - quat.y * quat.y - quat.z * quat.z);
            expected.pitch = LDMathUtil.PI_OVER_2 * sp;
            expected.bank = 0.0f;
            actual.fromObjectToInertialQuaternion(quat);
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);

            // Input : x = 1.0, y = 0.25, z = 0.25, w = 0.5 (任意の値. 角度計算のケース)
            quat.x = 1.0f;
            quat.y = 0.25f;
            quat.z = 0.25f;
            quat.w = 0.5f;
            sp = -2.0f * (quat.y * quat.z - quat.w * quat.x);
            expected.heading = (float)Math.Atan2(quat.x * quat.z + quat.w * quat.y,
                                      0.5f - quat.x * quat.x - quat.y * quat.y);
            expected.pitch = (float)Math.Asin(sp);
            expected.bank = (float)Math.Atan2(quat.x * quat.y + quat.w * quat.z,
                                      0.5f - quat.x * quat.x - quat.z * quat.z);
            actual.fromObjectToInertialQuaternion(quat);
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);
        }

       public void fromWorldToObjectMatrixTest()
        {
            LDMatrix44 matrix=new LDMatrix44();
            LDEulerAngles actual=new LDEulerAngles();
            LDEulerAngles expected=new LDEulerAngles();
            //ld_float delta = 0.00001f;

            // Input : (単位行列)
            actual.identity();
            expected.identity();
            actual.fromWorldToObjectMatrix(matrix);
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);

            // Input : matrix.m23 = 1.0 (ジンバルロックのケース)
            matrix.m23 = 1.0f;
            expected.heading = (float)Math.Atan2(-matrix.m31, matrix.m11);
            expected.pitch = LDMathUtil.PI_OVER_2 * -matrix.m23;
            expected.bank = 0.0f;
            actual.fromWorldToObjectMatrix(matrix);
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);

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
            expected.heading = (float)Math.Atan2(matrix.m13, matrix.m33);
            expected.pitch = (float)Math.Asin(-matrix.m23);
            expected.bank = (float)Math.Atan2(matrix.m21, matrix.m22);
            actual.fromWorldToObjectMatrix(matrix);
            TestUtil.COMPARE(expected.heading, actual.heading);
            TestUtil.COMPARE(expected.pitch, actual.pitch);
            TestUtil.COMPARE(expected.bank, actual.bank);
        }
    }
}
