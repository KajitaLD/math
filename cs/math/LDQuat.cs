using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace live2d
{
    using ld_float = System.Single;
    using ld_bool = System.Boolean;
    using ld_int32 = System.Int32;

    public class LDQuat
    {

        public ld_float x; //!< @brief クォータニオンの要素：x
        public ld_float y; //!< @brief クォータニオンの要素：y
        public ld_float z; //!< @brief クォータニオンの要素：z
        public ld_float w; //!< @brief クォータニオンの要素：w

        //------ ructor ------

        /**
        * @brief 高速化のため初期化は行わない
        */
        public LDQuat() { }

        /**
        * @brief 全ての値を val で初期化する
        * @param val 初期値をセットする
        */
        public LDQuat(ld_float val) { x = y = z = w = val; }

        /**
        * @brief x,y,z,w を指定して初期化
        * @param x 初期値をセットする
        * @param y 初期値をセットする
        * @param z 初期値をセットする
        * @param w 初期値をセットする
        */
        public LDQuat(ld_float _x, ld_float _y, ld_float _z, ld_float _w)
        {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }

        /**
        * @brief vector3 ,w を指定して初期化
        * @param _v EVector3をセットする
        * @param w 初期値をセットする
        */
        public LDQuat(LDVector3 _v, ld_float _w)
        {
            x = _v.x;
            y = _v.y;
            z = _v.z;
            w = _w;
        }

        /**
        * @brief コピーコンストラクタ
        * @param quat EQuatをセットする
        */
        public LDQuat(LDQuat quat)
        {
            x = quat.x;
            y = quat.y;
            z = quat.z;
            w = quat.w;
        }

        //------ static factory ------
        static public LDQuat getIdentity()
        {
            return new LDQuat(0, 0, 0, 1);
        }

        /**
        * @brief 軸と回転角を指定して、クォータニオンを返す
        * @param unitVec EVector3をセットする
        * @param radian 回転角[rad]をセットする
        * @return クォータニオンを返す
        */
        static public LDQuat getRotation(LDVector3 unitVec, float radian)
        {
            throw new NotImplementedException();
        }

        /**
        * @brief 単位ベクトル1 から 単位ベクトル2への回転を表すクォータニオンを返す
        * @param unitVec1 EVector3をセットする
        * @param unitVec2 EVector3をセットする
        * @return クォータニオンを返す
        */
        static public LDQuat getRotation(LDVector3 unitVec1, LDVector3 unitVec2)
        {
            throw new NotImplementedException();

        }

        // 指定の回転のクォータニオンを生成する
        /**
        * @brief 指定の回転のクォータニオンを生成する
        * @param radian 回転角[rad]をセットする
        * @return クォータニオンを返す
        */
        static public LDQuat getRotateX(ld_float radian)
        {
            throw new NotImplementedException();

        }

        /**
        * @brief 指定の回転のクォータニオンを生成する
        * @param radian 回転角[rad]をセットする
        * @return クォータニオンを返す
        */
        static public LDQuat getRotateY(ld_float radian)
        {
            throw new NotImplementedException();

        }

        /**
        * @brief 指定の回転のクォータニオンを生成する
        * @param radian 回転角[rad]をセットする
        * @return クォータニオンを返す
        */
        static public LDQuat getRotateZ(ld_float radian)
        {
            throw new NotImplementedException();

        }

        //--------------------
        /**
        * @brief 回転角を取り出して返す
        */
        public ld_float getAngle()
        {
            return LDMathUtil.safeAcos(w) * 2.0f;
        }

        /**
        * @brief 回転軸を取り出して返す
        * @return 回転軸を返す
        */
        LDVector3 getAxis()
        {
            ld_float sinQ_over2Sq = 1.0f - w * w;

            if (sinQ_over2Sq <= 0.0f)
            {
                return new LDVector3(1.0f, 0.0f, 0.0f);
            }

            ld_float one_overSinQ_over2 = 1.0f / (ld_float)Math.Sqrt(sinQ_over2Sq);

            return new LDVector3(
                       x * one_overSinQ_over2,
                       y * one_overSinQ_over2,
                       z * one_overSinQ_over2
                   );
        } //not public

        /**
        * @brief クォータニオンの長さを返す
        * @return クォータニオンの長さを返す
        */
        public ld_float length()
        {
            return (ld_float)Math.Sqrt(w * w + x * x + y * y + z * z);
        }

        /**
        * @brief 正規化
        */
        public void normalize()
        {
            ld_float mag = (ld_float)Math.Sqrt(w * w + x * x + y * y + z * z);

            if (mag > 0.0f)
            {
                ld_float oneOverMag = 1.0f / mag;
                w *= oneOverMag;
                x *= oneOverMag;
                y *= oneOverMag;
                z *= oneOverMag;
            }
            else
            {
                // 不正な状態
                Debug.Assert(false);

                // リリースビルドではとりあえず動作させる
                setToIdentity();
            }
        }

        /**
        * @brief クォータニオンを初期化する
        */
        public void setToIdentity()
        {
            w = 1.0f;
            x = y = z = 0.0f;
        }

        /**
        * @brief X軸に特定の角度を設定
        * @param q X軸の角度をセットする
        */
        public void setToRotateX(ld_float theta)
        {
            ld_float theta_over2 = theta * 0.5f;
            w = (ld_float)Math.Cos(theta_over2);
            x = (ld_float)Math.Sin(theta_over2);
            y = 0.0f;
            z = 0.0f;
        }

        /**
        * @brief Y軸に特定の角度を設定
        * @param q Y軸の角度をセットする
        */
        public void setToRotateY(ld_float theta)
        {
            ld_float theta_over2 = theta * 0.5f;
            w = (ld_float)Math.Cos(theta_over2);
            x = 0.0f;
            y = (ld_float)Math.Sin(theta_over2);
            z = 0.0f;
        }

        /**
        * @brief Z軸に特定の角度を設定
        * @param q Z軸の角度をセットする
        */
        public void setToRotateZ(ld_float theta)
        {
            ld_float theta_over2 = theta * 0.5f;
            w = (ld_float)Math.Cos(theta_over2);
            x = 0.0f;
            y = 0.0f;
            z = (ld_float)Math.Sin(theta_over2);
        }

        public void setToRotateAxis(LDVector3 axis, ld_float theta)
        {
            Debug.Assert(Math.Abs(axis.length() - 1.0f) < 0.01f);

            ld_float theta_over2 = theta * 0.5f;
            ld_float sinQ_over2 = (ld_float)Math.Sin(theta_over2);

            w = (ld_float)Math.Cos(theta_over2);
            x = axis.x * sinQ_over2;
            y = axis.y * sinQ_over2;
            z = axis.z * sinQ_over2;
        }

        /**
        * @brief 最小弧クォータニオン　二点を結ぶ最小の弧を描く。(v1,v2が単位ベクトルであることがわかっている場合は useNormalizeを　false にすると計算量が多少減る)
        * @param &v1 EVector3をセットする
        * @param &v2 EVector3をセットする
        * @param useNormalize 正規化する場合はtrue, そうでない場合はfalseをセットする。(入力無き場合はtrue)
        */
        void setToRotationArc(LDVector3 v1, LDVector3 v2, bool useNormalize = true)
        {
            LDVector3 vv1;
            LDVector3 vv2;
            LDVector3 tmp1;
            LDVector3 tmp2;

            if (useNormalize)
            {
                tmp1 = v1;
                tmp1.normalize();

                tmp2 = v2;
                tmp2.normalize();
                vv1 = tmp1;
                vv2 = tmp2;
            }
            else
            {
                vv1 = v1;
                vv2 = v2;
            }

            LDVector3 c = LDVector3.crossProduct(vv1, vv2);
            ld_float d = vv1.dotProduct(vv2);

            ld_float s = (ld_float)Math.Sqrt((1 + d) * 2);
            this.x = c.x / s;
            this.y = c.y / s;
            this.z = c.z / s;
            this.w = s / 2.0f;
        } // not public

        // オブジェクト空間->慣性空間への回転
        //public void		setToRotateObjectToInertial(  EEulerAngles & orientation ) ;
        //public void		setToRotateInertialToObject(  EEulerAngles & orientation ) ;
        /**
        * @brief オブジェクト空間->慣性空間への回転
        * @param &orientation オイラー角(EEulerAngles)をセットする
        */
        void setToRotateObjectToInertial(LDEulerAngles orientation)
        {
            ld_float sp, sb, sh;
            ld_float cp, cb, ch;

            LDMathUtil.sinCos(out sp, out cp, orientation.pitch * 0.5f);
            LDMathUtil.sinCos(out sb, out cb, orientation.bank * 0.5f);
            LDMathUtil.sinCos(out sh, out ch, orientation.heading * 0.5f);

            w = ch * cp * cb + sh * sp * sb;
            x = ch * sp * cb + sh * cp * sb;
            y = -ch * sp * sb + sh * cp * cb;
            z = -sh * sp * cb + ch * cp * sb;
        }

        /**
        * @brief 慣性空間->オブジェクト空間への回転
        * @param &orientation オイラー角(EEulerAngles)をセットする
        */
        void setToRotateInertialToObject(LDEulerAngles orientation)
        {
            ld_float sp, sb, sh;
            ld_float cp, cb, ch;

            LDMathUtil.sinCos(out sp, out cp, orientation.pitch * 0.5f);
            LDMathUtil.sinCos(out sb, out cb, orientation.bank * 0.5f);
            LDMathUtil.sinCos(out sh, out ch, orientation.heading * 0.5f);

            w = ch * cp * cb + sh * sp * sb;
            x = -ch * sp * cb - sh * cp * sb;
            y = ch * sp * sb - sh * cp * cb;
            z = sh * sp * cb - ch * cp * sb;
        }

        /**
        * @brief 球面線形補間
        * @param &q1 クォータニオン(EQuat)をセットする
        * @param t　補間位置を表す数値をセットする
        * @return 補間結果を返す
        */
        LDQuat slerp(LDQuat q1, ld_float t)
        {
            LDQuat q0 = this;

            // 範囲外の時は端点を返す
            if (t <= 0.0f)
            {
                return q0;
            }
            if (t >= 1.0f)
            {
                return q1;
            }

            // 内積でクォータニオン間の角度のcosを計算する
            ld_float cosOmega = q0.dot(q1);

            ld_float q1w = q1.w;
            ld_float q1x = q1.x;
            ld_float q1y = q1.y;
            ld_float q1z = q1.z;

            if (cosOmega < 0.0f)
            {
                q1w = -q1w;
                q1x = -q1x;
                q1y = -q1y;
                q1z = -q1z;
                cosOmega = -cosOmega;
            }

            // 各クォータニオンは、単位クォータニオンである必要があり、内積は <= 1.0 になるはず
            Debug.Assert(cosOmega < 1.1f);

            ld_float k0, k1;
            if (cosOmega > 0.9999f)
            {
                // 非常に近いので、単純に線形補間を用いる（0-divideを防ぐ）
                k0 = 1.0f - t;
                k1 = t;
            }
            else
            {
                ld_float sinOmega = (ld_float)Math.Sqrt(1.0f - cosOmega * cosOmega);
                ld_float omega = (ld_float)Math.Atan2(sinOmega, cosOmega);
                ld_float one_overSinOmega = 1.0f / sinOmega;
                k0 = (ld_float)Math.Sin((1.0f - t) * omega) * one_overSinOmega;
                k1 = (ld_float)Math.Sin(t * omega) * one_overSinOmega;
            }

            // 補間する
            LDQuat result = new LDQuat();
            result.x = k0 * q0.x + k1 * q1x;
            result.y = k0 * q0.y + k1 * q1y;
            result.z = k0 * q0.z + k1 * q1z;
            result.w = k0 * q0.w + k1 * q1w;

            return result;
        } // not public

        /**
        * @brief 独自の球面線形補間（回転角度を保つ）。y軸90度、z軸90度の回転をSLERPで計算する場合、t　が変化した時、軸は最小距離を移動するが、角度は、90度ではなく小さな値となる。この計算を 90度の回転を保って、中心を通る計算についてテスト実装
        * @param &q1 クォータニオン(EQuat)をセットする
        * @param t　補間位置を表す数値をセットする
        * @return 補間結果を返す
        */
        LDQuat mySlerp(LDQuat q1, ld_float t)
        {
            LDQuat q0 = this;

            // 範囲外の時は端点を返す
            if (t <= 0.0f)
            {
                return q0;
            }
            if (t >= 1.0f)
            {
                return q1;
            }

            LDVector3 n0 = q0.getAxis();
            LDVector3 n1 = q1.getAxis();
            ld_float a0 = q0.getAngle();
            ld_float a1 = q1.getAngle();

            //
            ld_float adiff = LDMathUtil.getAngleDiff(a1, a0);
            ld_float at = a0 + adiff * t;
            LDVector3 nt = LDVector3.blend(n0, n1, 1 - t, t);
            nt.normalize();

            LDQuat ret = new LDQuat();
            ret.setToRotateAxis(nt, at);
            return ret;
        }

        public static LDQuat slerp(LDQuat q0, LDQuat q1, ld_float t)
        {
            return q0.slerp(q1, t);
        }

        public static LDQuat mySlerp(LDQuat q0, LDQuat q1, ld_float t)
        {
            return q0.mySlerp(q1, t);
        }

        /**
        * @brief 共役 conjugate
*/
        public LDQuat conjugate()
        {
            return new LDQuat(-x, -y, -z, w);
        }

        /**
        * @brief 累乗 pow
        * @param exponent クォータニオンの乗数をセットする
        * @return クォータニオンの累乗を返す
*/
        LDQuat pow(ld_float exponent)
        {
            LDQuat q = this;
            if (Math.Abs(q.w) > 0.9999f)
            {
                return q;    //0-divideを防ぐ
            }

            ld_float alpha = (ld_float)Math.Acos(q.w);
            ld_float newAlpha = alpha * exponent;
            LDQuat result = new LDQuat();
            result.w = (ld_float)Math.Cos(newAlpha);

            ld_float mult = (ld_float)Math.Sin(newAlpha) / (ld_float)Math.Sin(alpha);
            result.x = q.x * mult;
            result.y = q.y * mult;
            result.z = q.z * mult;

            return result;
        } // not public

        /**
        * @brief 内積
*/
        public ld_float dot(LDQuat b)
        {
            return w * b.w + x * b.x + y * b.y + z * b.z;
        }

        //------ operator ------
        /**
        * @brief 外積
*/
        public static LDQuat operator *(LDQuat a, LDQuat b)
        {
            LDQuat result = new LDQuat();

            result.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
            result.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
            result.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
            result.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;

            //	result.w = w*a.w - x*a.x - y*a.y - z*a.z ;
            //	result.x = w*a.x + x*a.w + y*a.y - z*a.z ;
            //	result.y = w*a.y + x*a.w + y*a.z - z*a.x ;
            //	result.z = w*a.z + x*a.w + y*a.x - z*a.y ;

            return result;
        }

        //------ Debug ------
        public void dump(string title = "", ld_bool newline = true, ld_int32 keta = 3)
        {
            throw new NotImplementedException();
            if (keta == 3)
            {
                //printf("%s{%7.3f ,%7.3f ,%7.3f ,%7.3f }(len=%7.3f)%s", title, w, x, y, z, length(), (newline ? "\n" : ""));
            }
            else
            {
                if (keta < 0)
                {
                    keta = 0;
                }
                else if (keta > 5)
                {
                    keta = 5;
                }
                //char dst[32];//絶対超えないサイズにする

                //sprintf(dst, "%%s{%%7.%df,%%7.%df,%%7.%df,%%7.%df %7.3f }%s", keta, keta, keta, keta, length(), (newline ? "\n" : ""));

                //printf(dst, title, w, x, y, z);
            }
        }

    }
}
