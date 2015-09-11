#define LD_CORE_ENABLE_CS

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    using ld_float = System.Single;

    public class LDMathUtil
    {
        #region 定数
        /// <summary>
        ///  3.14159265f
        /// </summary>
        public const ld_float PI = 3.14159265f;

        /// <summary>
        /// EUC_PI * 2.0f ;
        /// </summary>
        public const ld_float PI2 = PI * 2.0f;

        /// <summary>
        /// EUC_PI / 2.0f ;
        /// </summary>
        public const ld_float PI_OVER_2 = PI / 2.0f;

        /// <summary>
        /// 1.0f / EUC_PI ;
        /// </summary>
        public const ld_float ONE_OVER_PI = 1.0f / PI;

        /// <summary>
        /// 1.0f / EUC_2PI ;
        /// </summary>
        public const ld_float ONE_OVER_PI2 = 1.0f / PI2;

        /// <summary>
        /// 通常計算時の許容誤差 ;
        /// </summary>
        public const ld_float TOLERANCE = 0.0001f;

        /// <summary>
        /// ジンバルロック時の許容誤差 ;
        /// </summary>
        public const ld_float GINBAL_TOLERANCE = 0.0001f;
        #endregion
        /**
	    * @brief 2PIの倍数を加える事で角度を -PI .. PI にラップする
	    * @param theta 位相角[rad]をセットする
	    * @return -PIからPIにラップした位相角[rad]を返す
	    */
        public static ld_float wrapPi(ld_float theta)
        {
            theta += PI;
            theta -= (ld_float)Math.Floor(theta * ONE_OVER_PI2) * PI2;
            theta -= PI;
            return theta;
        }

        /**
        * @brief Q2からQ1への、角の変化量を取得する
        * @param Q1 位相角Q1[rad]をセットする
        * @param Q2 位相角Q2[rad]をセットする
        * @return Q2からQ1への、角の変化量[rad]を返す
        */
        public static ld_float getAngleDiff(ld_float Q1, ld_float Q2)
        {
            ld_float ret = Q1 - Q2;
            while (ret < -PI)
            {
                ret += PI2;    //-180より小さければ、360度足す
            }
            while (ret > PI)
            {
                ret -= PI2;    //　180より大きければ、360度引く
            }
            return ret;
        }

        /**
        * @brief 安全な逆三角関数。acos(x)と同じ。ただし、x が範囲外のとき、最も近い有効な値にクランプ処理される
        * @param x acos()に入力する数値
        * @return 　acos()の値（Cのacosと同様に 0..PI である）
        */
        public static ld_float safeAcos(ld_float x)
        {
            if (x <= -1.0f)
            {
                return PI;
            }
            if (x >= 1.0f)
            {
                return 0.0f;
            }
            return (ld_float)Math.Acos(x);
        }

        /// <summary>
        /// Sin Cos を一回で求める
        /// returnSin sin(theta)の計算結果を受け取るポインタをセットする
        /// returnCos cos(theta)の計算結果を受け取るポインタをセットする
        /// theta 位相角[rad]をセットする
        /// </summary>
        public static void sinCos(out ld_float returnSin, out ld_float returnCos, ld_float theta)
        {
            returnSin = (ld_float)Math.Sin(theta);
            returnCos = (ld_float)Math.Cos(theta);
        }

        //float4つを見やすく表示するための文字列を返す
        public static System.String format4args(ld_float a, ld_float b, ld_float c, ld_float d)
        {
            return a.ToString() + " " + b.ToString() + " " + c.ToString() + " " + d.ToString();
        }

        //float3つを見やすく表示するための文字列を返す
        public static System.String format3args(ld_float a, ld_float b, ld_float c)
        {
            return a.ToString() + " " + b.ToString() + " " + c.ToString();
        }

        public static double crossProductValue(LDPoint pa, LDPoint pb, LDPoint pc)
        {
            // 有向線分 (pa,pb), (pa,pc) の外積の z 成分を求める
            double n = pb.x() * (pa.y() - pc.y()) + pa.x() * (pc.y() - pb.y()) + pc.x()
                    * (pb.y() - pa.y());

            return n;
        }

        public static double crossProductValue(LDPoint pa, LDPoint pb)
        {
            // pa と pb の外積の z 成分を求める
            double n = pa.x() * pb.y() - pa.y() * pb.x();

            return n;
        }

        /**
         * v1からv2への反時計回りの角度 (0~2pi)
         */
        public static double getAngle(LDVector2 v1, LDVector2 v2)
        {
            double q1 = Math.Atan2(v1.y(), v1.x());
            double q2 = Math.Atan2(v2.y(), v2.x());
            double ret = q2 - q1;//v2の角度からv1 の角度を引く

            if (ret < 0) ret += 2 * PI;//0より小さければ、360度足す
            return ret;
        }

        public static LDPoint rotatePoint(LDPoint origin, LDPoint pt, ld_float rad)
        {
            LDPoint tmp = pt - origin;
            float x = (float)(tmp.x() * Math.Cos(rad) + tmp.y() * Math.Sin(rad));
            float y = ((float)(-tmp.x() * Math.Sin(rad) + tmp.y() * Math.Cos(rad)));
            return new LDPoint(x + origin.x(), y + origin.y());
        }
        public static LDPoint scalePoint(LDPoint origin, LDPoint pt, ld_float scale)
        {
            LDPoint tmp = pt - origin;
            float x = tmp.x() * scale;
            float y = tmp.y() * scale;
            return new LDPoint(x + origin.x(), y + origin.y());
        }
        public static LDPoint scalePoint(LDPoint origin, LDPoint pt, ld_float scale_x, ld_float scale_y)
        {
            LDPoint tmp = pt - origin;
            float x = tmp.x() * scale_x;
            float y = tmp.y() * scale_y;
            return new LDPoint(x + origin.x(), y + origin.y());
        }


        /**
         * 2つの値の間を線形補間する
         */
        public static T lerp<T>(T from, T to, float t)
        {
            return (1 - t) * from + t * to;
        }


        public static float inverseLerp<T>(T from, T to, T value)
        {
            return (value - from) / (to - from);
        }

        /**
         * 4つの値の間を二次元線形補間する
         */
        public static T lerp2D<T>(T from1, T to1, double t1, T from2, T to2, double t2)
        {
            T tmp1 = (1 - t1) * from1 + t1 * to1;
            T tmp2 = (1 - t1) * from2 + t1 * to2;
            return (1 - t2) * tmp1 + t2 * tmp2;
        }

        #region inverseLerp2D
        /* C#では使用できない　ジェネリクスと値間の演算
        public static void inverseLerp2D<T>(T from1, T to1, T from2, T to2, T value, out double t1, out double t2)
        {
            //		参考 stackoverflow "Inverse Bilinear Interpolation?"
            //		http://stackoverflow.com/questions/808441/inverse-bilinear-interpolation
            //		p2 --- p3
            //	     |      |
            //	   t |  p   |
            //	     |      |
            //	     p0 --- p1
            //	        s
            //		A = (p0-p) X (p0-p2)
            //		B = ( (p0-p) X (p1-p3) + (p1-p) X (p0-p2) ) / 2
            //		C = (p1-p) X (p1-p3)
            //		s = ( (A-B) +- sqrt(B^2 - A*C) ) / ( A - 2*B + C )

            double a = crossProductValue(from2 - value, from2 - from1);
            double b = (crossProductValue(from2 - value, to2 - to1) + crossProductValue(to2 - value, from2 - from1)) / 2;
            double c = crossProductValue(to2 - value, to2 - to1);

            double d = (a - 2 * b + c);

            if (d == 0 || Math.Abs(d) < 0.0001)
            {
                t1 = a / (a - c);
                //			qDebug()<<"d==0"<<t1;
            }
            else
            {
                t1 = ((a - b) + Math.Sqrt(b * b - a * c)) / d;//NOTE:ここに入ると変換の形状が壊れる
                                                              //			qDebug()<<"d!=0"<<t1<<"or"<<((a-b)-sqrt(b*b-a*c))/d;
            }

            //		t = ( (1-s)*(x0-x) + s*(x1-x) ) / ( (1-s)*(x0-x2) + s*(x1-x3) )
            //		t2=((1-t1)*(from2.y()-value.y())+t1*(to2.y()-value.y())) / ((1-t1)*(from2.y()-from1.y())+t1*(to2.y()-to1.y()));
            LDPoint tmp1 = ((1 - t1) * (from2 - value) + t1 * (to2 - value));
            LDPoint tmp2 = ((1 - t1) * (from2 - from1) + t1 * (to2 - to1));


            Util.uAssert(!(tmp2.x() == 0 && tmp2.y() == 0));

            if (tmp2.x() == 0 && tmp2.y() != 0)
            {
                t2 = tmp1.y() / tmp2.y();
            }
            else //if(tmp2.y()==0&&tmp2.x()!=0)
            {
                t2 = tmp1.x() / tmp2.x();
            }
            //		else
            //		{
            //			LDPoint tmp(tmp1.x()/tmp2.x(),tmp1.y()/tmp2.y());
            //			t2=tmp.x()+tmp.y()/2;
            ////			t2=sqrt(tmp.x()*tmp.x()+tmp.y()*tmp.y());
            //		}

            t2 = 1 - t2;
        }
        */
        public static void inverseLerp2D(LDPoint from1, LDPoint to1, LDPoint from2, LDPoint to2, LDPoint value, out double t1, out double t2)
        {
            //		参考 stackoverflow "Inverse Bilinear Interpolation?"
            //		http://stackoverflow.com/questions/808441/inverse-bilinear-interpolation
            //		p2 --- p3
            //	     |      |
            //	   t |  p   |
            //	     |      |
            //	     p0 --- p1
            //	        s
            //		A = (p0-p) X (p0-p2)
            //		B = ( (p0-p) X (p1-p3) + (p1-p) X (p0-p2) ) / 2
            //		C = (p1-p) X (p1-p3)
            //		s = ( (A-B) +- sqrt(B^2 - A*C) ) / ( A - 2*B + C )

            double a = crossProductValue(from2 - value, from2 - from1);
            double b = (crossProductValue(from2 - value, to2 - to1) + crossProductValue(to2 - value, from2 - from1)) / 2;
            double c = crossProductValue(to2 - value, to2 - to1);

            double d = (a - 2 * b + c);

            if (d == 0 || Math.Abs(d) < 0.0001)
            {
                t1 = a / (a - c);
                //			qDebug()<<"d==0"<<t1;
            }
            else
            {
                t1 = ((a - b) + Math.Sqrt(b * b - a * c)) / d;//NOTE:ここに入ると変換の形状が壊れる
                                                              //			qDebug()<<"d!=0"<<t1<<"or"<<((a-b)-sqrt(b*b-a*c))/d;
            }

            //		t = ( (1-s)*(x0-x) + s*(x1-x) ) / ( (1-s)*(x0-x2) + s*(x1-x3) )
            //		t2=((1-t1)*(from2.y()-value.y())+t1*(to2.y()-value.y())) / ((1-t1)*(from2.y()-from1.y())+t1*(to2.y()-to1.y()));
            LDPoint tmp1 = ((1 - (float)t1) * (from2 - value) + (float)t1 * (to2 - value));
            LDPoint tmp2 = ((1 - (float)t1) * (from2 - from1) + (float)t1 * (to2 - to1));


            Util.uAssert(!(tmp2.x() == 0 && tmp2.y() == 0));

            if (tmp2.x() == 0 && tmp2.y() != 0)
            {
                t2 = tmp1.y() / tmp2.y();
            }
            else //if(tmp2.y()==0&&tmp2.x()!=0)
            {
                t2 = tmp1.x() / tmp2.x();
            }
            //		else
            //		{
            //			LDPoint tmp(tmp1.x()/tmp2.x(),tmp1.y()/tmp2.y());
            //			t2=tmp.x()+tmp.y()/2;
            ////			t2=sqrt(tmp.x()*tmp.x()+tmp.y()*tmp.y());
            //		}

            t2 = 1 - t2;
        }
        #endregion

        public static Type clamp<Type>(Type value, Type min, Type max)
            where Type : IComparable<Type>
        {
            if (value < min) return min;
            if (value > max) return max;
            return value;
        }

        public static LDPoint clamp(LDPoint value, LDPoint min, LDPoint max)
        {
            return new LDPoint(
                        clamp(value.x(), min.x(), max.x()),
                        clamp(value.y(), min.y(), max.y()));
        }

        
        public static bool fuzzyCompare<T>(T a, T b, float fuzz)
        {
            return Math.Abs(a - b) <= fuzz;
        }


    public static bool fuzzyCompare(LDPointList a, LDPointList b, float fuzz)
        {
            if (a.length() != b.length())
            {
                return false;
            }
            for (int i = 0; i < a.length(); ++i)
            {
                if (Math.Abs(a[i].x() - b[i].x()) > fuzz)
                {
                    return false;
                }
                if (Math.Abs(a[i].y() - b[i].y()) > fuzz)
                {
                    return false;
                }
            }
            return true;
        }
    }
}
