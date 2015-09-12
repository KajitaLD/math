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
    /// <summary>
    /// 代入演算子オーバーロード不可につき、CopyFromを用意
    /// </summary>
    public class LDVector3
    {

        public ld_float x; //!< @brief 行列の要素：x
        public ld_float y; //!< @brief 行列の要素：y
        public ld_float z; //!< @brief 行列の要素：z


        /**
        * @brief コンストラクタ
        */
        public LDVector3() { this.x = 0; this.y = 0; this.z = 0; }

        /**
        * @brief コンストラクタ
        * @param v EVector3をセットする
        */
        public LDVector3(LDVector3 v)
        {
            this.x = v.x;
            this.y = v.y;
            this.z = v.z;
        }

        /**
        * @brief コンストラクタ
        * @param vx EVector3の行列要素xをセットする
        * @param vy EVector3の行列要素yをセットする
        * @param vz EVector3の行列要素zをセットする
        */
        public LDVector3(ld_float vx, ld_float vy, ld_float vz)
        {
            this.x = vx;
            this.y = vy;
            this.z = vz;
        }

        /**
        * @brief 代入する
        * @param v EVector3をセットする
        * @return 自身を返す
        */
        public void CopyFrom(LDVector3 v)
        {
            this.x = v.x;
            this.y = v.y;
            this.z = v.z;
        }

        /**
        * @brief すべての要素が一致するか確認する
        * @param v EVector3をセットする
        * @return 要素が一致していればtrue, そうでなければfalseを返す
        */
        public static ld_bool operator ==(LDVector3 a, LDVector3 v)
        {
            return a.x == v.x && a.y == v.y && a.z == v.z;
        }

        /**
        * @brief 一致しない要素があるか確認する
        * @param v EVector3をセットする
        * @return 一致しない要素があればtrue, そうでなければfalseを返す
*/
        public static ld_bool operator !=(LDVector3 a, LDVector3 v)
        {
            return a.x != v.x || a.y != v.y || a.z != v.z;
        }

        /**
        * @brief ゼロベクトル化
        */
        public void zero()
        {
            x = y = z = 0.0f;
        }

        /**
        * @brief ベクトル(Evector3)を正規化する
*/
        public void normalize()
        {
            ld_float magSq = x * x + y * y + z * z;
            if (magSq > 0.0)  //0-divide check
            {
                ld_float invMag = 1.0f / (ld_float)Math.Sqrt(magSq);
                x *= invMag;
                y *= invMag;
                z *= invMag;
            }
        }

        /**
        * @brief 単項演算子のマイナス
        * @return EVector3(-x,-y,-z)を返す
*/
        public static LDVector3 operator -(LDVector3 v)
        {
            return new LDVector3(-v.x, -v.y, -v.z);
        }

        /**
        * @brief 二項演算子の"+"
        * @param v Evector3をセットする
        * @return EVector3( x + v.x , y + v.y , z + v.z )を返す
        */
        public static LDVector3 operator +(LDVector3 a, LDVector3 v)
        {
            return new LDVector3(a.x + v.x, a.y + v.y, a.z + v.z);
        }

        /**
        * @brief 二項演算子の"-"
        * @param v Evector3をセットする
        * @return EVector3( x - v.x , y - v.y , z - v.z )を返す
        */
        public static LDVector3 operator -(LDVector3 a,LDVector3 v)
        {
            return new LDVector3(a.x - v.x, a.y - v.y, a.z - v.z);
        }

        /**
        * @brief 二項演算子の"*"
        * @param a 行列の要素にかける係数をセットする
        * @return EVector3( a *x , a *y , a *z )を返す
        */
        public static LDVector3 operator *(LDVector3 a, ld_float b)
        {
            return new LDVector3(b * a.x, b * a.y, b * a.z);
        }
        public static LDVector3 operator *(ld_float b, LDVector3 a)
        {
            return new LDVector3(b * a.x, b * a.y, b * a.z);
        }

        /**
        * @brief 二項演算子の"/"
        * @param a 行列の要素を割る係数をセットする
        * @return EVector3( inv *x , inv *y , inv *z )を返す
        */
        public static LDVector3 operator /(LDVector3 a, ld_float b)
        {
            ld_float inv = 1.0f / b;
            return new LDVector3(inv * a.x, inv * a.y, inv * a.z);
        }


        /**
        * @brief ベクトルの内積 (乗算演算子のオーバーロード)
        * @param v EVector3をセットする
        * @return ベクトルの内積を返す
*/
        public static ld_float operator *(LDVector3 a, LDVector3 b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        /**
        * @brief ベクトルの長さ　（メンバ関数 v1.length() と　外部関数の length( v1 ) が共に利用可能）
        * @return ベクトルの長さを返す
        */
        public ld_float length()
        {
            return (ld_float)Math.Sqrt(x * x + y * y + z * z);
        }

        /**
        * @brief ベクトルの内積
        * @param v2 EVector3をセットする
        * @return ベクトルの内積を返す
        */
        public ld_float dotProduct(LDVector3 v2)
        {
            return this.x * v2.x + this.y * v2.y + this.z * v2.z;
        }

        //------ Debug ------
        /// <summary>
        /// 未実装
        /// </summary>
        /// <param name="title"></param>
        /// <param name="newline"></param>
        /// <param name="keta"></param>
        public void dump(string title = "", ld_bool newline = true, ld_int32 keta = 3)
        {
            if (keta == 3)
            {
                Console.WriteLine(title + "{" + x + " ," + y + " ," + z + " }(len=" + length() + ")" + (newline ? "\n" : ""));
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
                string dst = new string(' ', 32);//絶対超えないサイズにする

                //sprintf(dst, "%%s{%%7.%df,%%7.%df,%%7.%df %7.3f }%s", keta, keta, keta, length(), (newline ? "\n" : ""));

                Console.WriteLine(dst, title, x, y, z);
            }
        }



        //====================================================
        //	非メンバ関数
        //====================================================
        /**
        * @brief ベクトルの長さ
        * @param v EVector3をセットする
        * @return ベクトルの長さを返す
*/
        public static ld_float length(LDVector3 v)
        {
            return (ld_float)Math.Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        }

        /**
        * @brief ベクトルの外積
        * @param v1 EVector3をセットする
        * @param v2 EVector3をセットする
        * @return ベクトルの外積を返す
*/
        public static LDVector3 crossProduct(LDVector3 v1, LDVector3 v2)
        {
            return new LDVector3(v1.y * v2.z - v1.z * v2.y,
                              v1.z * v2.x - v1.x * v2.z,
                              v1.x * v2.y - v1.y * v2.x);
        }

        /**
        * @brief ベクトルの内積
        * @param v1 EVector3をセットする
        * @param v2 EVector3をセットする
        * @return ベクトルの内積を返す
*/
        public static ld_float dot(LDVector3 v1, LDVector3 v2)
        {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        }

        /**
        * @brief ２つの点の距離を取得する
        * @param v1 EVector3をセットする
        * @param v2 EVector3をセットする
        * @return ２つの点の距離を返す
*/
        public static ld_float distance(LDVector3 v1, LDVector3 v2)
        {
            ld_float dx = v1.x - v2.x;
            ld_float dy = v1.y - v2.y;
            ld_float dz = v1.z - v2.z;
            return (ld_float)Math.Sqrt(dx * dx + dy * dy + dz * dz);
        }

        /**
        * @brief ２つのベクトルをブレンドする
        * @param v1 EVector3をセットする
        * @param v2 EVector3をセットする
        * @param t1 v1にかけるスカラー値t1をセットする
        * @param t2 v2にかけるスカラー値t2をセットする
        * @return ブレンドしたベクトルを返す
*/
        public static LDVector3 blend(LDVector3 v1, LDVector3 v2, ld_float t1, ld_float t2)
        {
            return new LDVector3(v1.x * t1 + v2.x * t2, v1.y * t1 + v2.y * t2, v1.z * t1 + v2.z * t2);
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;
            if (obj.GetType() != this.GetType()) return false;
            var p = obj as LDVector3;
            return this == p;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }
}
