using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    using ld_float = Single;
    public class LDEulerAngles
    {

        public ld_float heading;  //!< @brief heading
        public ld_float pitch;    //!< @brief pitch
        public ld_float bank;     //!< @brief bank

        /**
        * @brief コンストラクタ
        */
        public LDEulerAngles() { }

        /**
        * @brief コンストラクタ
        * @param h headingをセットする
        * @param p pitchをセットする
        * @param b bankをセットする
        */
        public LDEulerAngles(ld_float h, float p, float b)
        {
            heading = h; pitch = p; bank = b;
        }

        /**
        * @brief オイラー角を初期化する
        */
        public void identity()
        {
            heading = pitch = bank = 0.0f;
        }

        /**
        * @brief 正準オイラー角の３つ組を決定する
        */
        public void canonize()
        {
            pitch = LDMathUtil.wrapPi(pitch);

            if (pitch < -LDMathUtil.PI_OVER_2)
            {
                pitch = -LDMathUtil.PI - pitch;
                heading += LDMathUtil.PI;
                bank += LDMathUtil.PI;
            }
            else if (pitch > LDMathUtil.PI_OVER_2)
            {
                pitch = LDMathUtil.PI - pitch;
                heading += LDMathUtil.PI;
                bank += LDMathUtil.PI;
            }

            // ジンバルロックのケースをチェックする
            if (Math.Abs(pitch) > LDMathUtil.PI_OVER_2 - LDMathUtil.GINBAL_TOLERANCE)
            {
                // ジンバルロック内にいる。回転を差し替える
                heading += bank;
                bank = 0.0f;
            }
            else
            {
                bank = LDMathUtil.wrapPi(bank);
            }

            heading = LDMathUtil.wrapPi(heading);
        }

        /**
        * @brief オブジェクト空間->慣性空間へのクォータニオンからオイラー角を設定
        * @param &q クォータニオンをセットする
        */
        public void fromObjectToInertialQuaternion(LDQuat q)
        {
            ld_float sp = -2.0f * (q.y * q.z - q.w * q.x);

            // ジンバルロックチェック
            if (Math.Abs(sp) > 1.0f - LDMathUtil.GINBAL_TOLERANCE)
            {
                // 真上か下を向いている
                pitch = LDMathUtil.PI_OVER_2 * sp;
                heading = (ld_float)Math.Atan2(-q.x * q.z + q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
                bank = 0.0f;
            }
            else
            {
                // 角度を計算する
                pitch = (ld_float)Math.Asin(sp);
                heading = (ld_float)Math.Atan2(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
                bank = (ld_float)Math.Atan2(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
            }
        }

        /**
        * @brief 慣性空間->オブジェクト空間へのクォータニオンからオイラー角を設定
        * @param &q クォータニオンをセットする
        */
        public void fromInertialToObjectQuaternion(LDQuat q)
        {
            ld_float sp = -2.0f * (q.y * q.z + q.w * q.x);

            if ((ld_float)Math.Abs(sp) > 1.0f - LDMathUtil.GINBAL_TOLERANCE)
            {
                //真上か真下を向いている
                pitch = LDMathUtil.PI_OVER_2 * sp;
                heading = (ld_float)Math.Atan2(-q.x * q.z - q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
                bank = 0.0f;
            }
            else
            {
                pitch = (ld_float)Math.Asin(sp);
                heading = (ld_float)Math.Atan2(q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
                bank = (ld_float)Math.Atan2(q.x * q.y - q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
            }
        }

        /**
        * @brief オブジェクト空間->世界座標への変換行列をオイラー角に変換する(この行列は直交している必要がある)
        * @param &m Ematrix44をセットする
        */
        public void fromObjectToWorldMatrix(LDMatrix44 m)
        {

            throw new NotImplementedException();

        }

        /**
	    * @brief 世界座標->オブジェクト空間への変換行列をオイラー角に変換する(この行列は直交している必要がある)
	    * @param &m Ematrix44をセットする
	    */
        public void fromWorldToObjectMatrix(LDMatrix44 m)
        {
            // m23からsin(pitch)を取り出す
            ld_float sp = -m.m23;

            // ジンバルロックのチェック
            if ((ld_float)Math.Abs(sp) > 1.0f - LDMathUtil.GINBAL_TOLERANCE)
            {
                //真上か真下
                pitch = LDMathUtil.PI_OVER_2 * sp;
                heading = (ld_float)Math.Atan2(-m.m31, m.m11);
                bank = 0.0f;
            }
            else
            {
                heading = (ld_float)Math.Atan2(m.m13, m.m33);
                pitch = (ld_float)Math.Asin(sp);
                bank = (ld_float)Math.Atan2(m.m21, m.m22);
            }
        }


        /**
        * @brief 回転行列をオイラー角に変換する
        * @param &m RotationMatrixをセットする
        */
        //	void  fromRotationMatrix( const RotationMatrix &m ) ;
    }
}
