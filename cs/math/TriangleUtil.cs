using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace live2d.math
{
    public class TriangleUtil
    {
        public static LDPolygon getHugeTriangle(LDRect rect)
        {
            Debug.Assert(rect.left() < rect.right());
            Debug.Assert(rect.top() < rect.bottom());

            // 1) 与えられた矩形を包含する円を求める
            //      円の中心 c = 矩形の中心
            //      円の半径 r = |p - c| + ρ
            //    ただし、pは与えられた矩形の任意の頂点
            //    ρは任意の正数
            LDVector2 center=new LDVector2(rect.center());
            LDVector2 topLeft=new LDVector2(rect.topLeft());
            float radius = center.distanceToPoint(topLeft);

            radius += 1.0f;//適当に大きくする

            // 2) その円に外接する正三角形を求める
            LDCircle circle=new LDCircle(center.toPoint(), radius);
            return circle.getCircumscribedTriangle();
        }

        // 点群を包含する十分大きな正三角形を求める
        public static LDPolygon getHugeTriangle(LDPointList form)
        {
            return getHugeTriangle(PointUtil.getBoundingRect(form));
        }



        //点 p が三角形 t(a,b,c) に含まれるか調べる。onLineがtrueなら線上にあっても範囲内にあるという判断
        public static bool containsPoint(LDPoint p1, LDPoint p2, LDPoint p3, LDPoint p, bool onLine = false)
        {
            int i = pointInTriangle(p1, p2, p3, p);
            Debug.Assert(i == -1 || i == 0 || i == 1);

            if (i == 1)
            {
                // 三角形の内側
                return true;
            }

            if (onLine)
            {
                if (i == -1)
                {
                    // 三角形の線上にある場合も含むとみなす
                    return true;
                }
            }

            // 三角形の外側
            return false;
        }


        public static bool containsPoint(LDPolygon t, LDPoint p, bool onLine = false)
        {
            Debug.Assert(t.size() == 3);
            return containsPoint(t[0], t[1], t[2], p, onLine);
        }

        //点 p が三角形 t(a,b,c) に含まれるか調べる。
        //点 p が三角形 t の内側にある場合  1 を、
        //　   　三角形 t の線上にある場合 -1 を、
        //　   　三角形 t の外側にある場合  0 を返す。
        public static int pointInTriangle(LDPoint p1, LDPoint p2, LDPoint p3, LDPoint p)
        {
            // 有向線分 (p2,p1), (p2,p3) の外積の z 成分を求める
            double p12 = LDMathUtil.crossProductValue(p1, p, p2);
            double p23 = LDMathUtil.crossProductValue(p2, p, p3);
            double p31 = LDMathUtil.crossProductValue(p3, p, p1);

            // 三角形の内側
            if ((0 < p12) && (0 < p23) && (0 < p31))
                return 1; // 点 p が常に左側にある（時計回り）
            if ((0 > p12) && (0 > p23) && (0 > p31))
                return 1; // 点 p が常に右側にある（反時計回り）

            // 三角形の線上
            if ((0 <= p12) && (0 <= p23) && (0 <= p31))
                return -1; // 点 p が常に左側にある（時計回り）
            if ((0 >= p12) && (0 >= p23) && (0 >= p31))
                return -1; // 点 p が常に右側にある（反時計回り）

            // 三角形の外側
            return 0;
        }

        //点p1 ,p2 ,p3 で構成される三角形が鈍角三角形か判定する
        public static bool isObtuseTriangle(LDPoint p1, LDPoint p2, LDPoint p3)
        {
            LDVector2 __a=new LDVector2(p1);
            LDVector2 __b=new LDVector2(p2);
            LDVector2 __c=new LDVector2(p3);


            LDVector2 _a = __a - __b;
            LDVector2 _b = __b - __c;
            LDVector2 _c = __c - __a;
            //良く考えたら三角形全部の角度調べるだけでよかった。
            if (LDVector2.dotProduct(_a, _b) < 0)
                return true;
            if (LDVector2.dotProduct(_a, _c) < 0)
                return true;
            if (LDVector2.dotProduct(_b, _c) < 0)
                return true;

            return false;

            //	float a=_a.length();
            //	float b=_b.length();
            //	float c=_c.length();
            //	int longestIndex;
            //	if ( a>=b  && a >=c )
            //	{
            //		longestIndex=0;
            //	}
            //	else if ( b >=a &&b >=c )
            //	{
            //		longestIndex=1;
            //	}
            //	else
            //	{
            //		longestIndex=2;
            //	}

            //	if ( longestIndex==0 )
            //	{
            //		if ( a*a<=b*b+c*c )
            //		{
            //			return false;
            //		}
            //		return true;
            //	}
            //	if ( longestIndex==1 )
            //	{
            //		if ( b*b<=a*a+c*c )
            //		{
            //			return false;
            //		}
            //		return true;
            //	}
            //	if ( longestIndex==2 )
            //	{
            //		if ( c*c<=b*b+a*a )
            //		{
            //			return false;
            //		}
            //		return true;
            //	}
            //	//ここまでのどこかに引っかかるはず 引っかからなかったらこの関数のどこかにバグがあるはず
            //	Debug.Assert( !" error" );
            //	return false;

        }

        //点p1 ,p2 ,targetで構成される三角形で、traget点での角度が鈍角か判定
        public static bool isObtuseAngle(LDPoint p1, LDPoint p2, LDPoint target)
        {
            LDVector2 a = new LDVector2(p1);
            LDVector2 b = new LDVector2(p2);
            LDVector2 c = new LDVector2(target);


            LDVector2 ab = a - b;
            LDVector2 bc = b - c;
            LDVector2 ca = c - a;

            if (LDVector2.dotProduct(bc, ca) < 0)
                return true;

            return false;
        }

        //点p1 ,p2 ,p3 から三角形が作れるかを判定(3点が一直線上にないか判定)
        public static bool isTriangle(LDPoint p1, LDPoint p2, LDPoint p3)
        {
            if ((p1.x() * p2.y() + p2.x() * p3.y() + p3.x() * p1.y()) - (p1.x() * p3.y() + p2.x() * p1.y() + p3.x() * p2.y()) != 0)
                return true;
            return false;
        }

        //三角形の高さ (底辺p12からp3までの高さ)
        public static float getTriangleHeight(LDPoint p1, LDPoint p2, LDPoint p3)
        {
            LDPoint ab = p2 - p1;
            LDPoint ac = p3 - p1;
            float D = Math.Abs(ab.x() * ac.y() - ab.y() * ac.x());
            float L = PointUtil.distance(p1, p2);
            float H = D / L;
            return H;
        }
        //s1,s2,s3で構成される三角形とt1,t2,t3が相似な三角形であるとき、、s1とs2の線とt1とt1を対応する線分である場合のt3の点を返す
        public static LDPoint getSimilarityTrianglePoint(LDPoint _s0, LDPoint _s1, LDPoint _s2, LDPoint _t0, LDPoint _t1)
        {

            LDVector2 s0 = new LDVector2(_s0);
            LDVector2 s1 = new LDVector2(_s1);
            LDVector2 s2 = new LDVector2(_s2);
            LDVector2 t0 = new LDVector2(_t0);
            LDVector2 t1 = new LDVector2(_t1);

            LDVector2 ss2 = s2 + t0 - s0;
            float angle = (float)LDMathUtil.getAngle(s1 - s0, t1 - t0);
            LDPoint sss2 = LDMathUtil.rotatePoint(_t0, ss2.toPoint(), -angle);
            LDVector2 v_s = s1 - s0;
            LDVector2 v_t = t1 - t0;
            float scale = v_t.length() / v_s.length();
            LDPoint t2 = LDMathUtil.scalePoint(_t0, sss2, scale);
            return t2;

        }
    }
}
