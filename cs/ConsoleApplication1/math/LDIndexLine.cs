using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using live2d.math;

namespace live2d
{
    public class LDIndexLine
    {
        //必ず index1 < index2 の関係とする。代入時に自動調整される。
        private int m_index1;
        private int m_index2;


        public LDIndexLine()
        {
            m_index1 = -1;
            m_index2 = -1;
        }
        public LDIndexLine(int a, int b)
        {
            m_index1 = a;
            m_index2 = b;
        }

        public LDLine toLine(LDPointList form)
        {
            Debug.Assert(form.length() > m_index1);
            Debug.Assert(form.length() > m_index2);

            return new LDLine(form.at(m_index1), form.at(m_index2));

        }

        //一致の確認は順番関係なし
        public static bool operator ==(LDIndexLine a, LDIndexLine b)
        {
            if (a.m_index1 == b.m_index1 && a.m_index2 == b.m_index2)
            {
                return true;
            }
            if (a.m_index1 == b.m_index2 && a.m_index2 == b.m_index1)
            {
                return true;
            }
            return false;
        }

        public static bool operator !=(LDIndexLine a, LDIndexLine b)
        {
            return !(a == b);
        }

        public int getIndex1() { return this.m_index1; }
        public void setIndex(int m_index1, int m_index2) { this.m_index1 = m_index1; this.m_index2 = m_index2; }
        public int getIndex2() { return this.m_index2; }

        public bool hasIndex(int index) {
            if (m_index1 == index || m_index2 == index)
            {
                return true;
            }
            return false;
        }

        public bool isEnabled()
        {
            return (m_index1 >= 0) && (m_index2 >= 0);
        }
        public bool isHit(LDPointList form , LDPoint p, float hitRange){
            LDLine l = this.toLine(form);

            LDPoint startPt = l.p1();
            LDPoint endPt = l.p2();

            //端点から一定の距離内だったら当たり
            if (PointUtil.isHit(startPt, p, hitRange))
                return true;
            if (PointUtil.isHit(endPt, p, hitRange))
                return true;


            //点が一直線上にないか確認
            if (TriangleUtil.isTriangle(startPt, endPt, p))
            {
                //鈍角三角形なら判定外
                if (TriangleUtil.isObtuseAngle(startPt, endPt, p))
                {
                    return false;
                }

                //三角形の面積を算出して、その底面で割れば高さ＝線と点の距離
                float distance = TriangleUtil.getTriangleHeight(startPt, endPt, p);

                if (distance <= hitRange)
                {
                    return true;
                }
                return false;

            }
            //一直線上にあるが線分外にあるか判定
            LDVector2 ab = new LDVector2(endPt - startPt);
            LDVector2 ap = new LDVector2(p - startPt);
            LDVector2 bp = new LDVector2(p - endPt);
            float omega = 0.0001f;//NOTE:誤差の基準値 かなり適当に指定
            if (ap.length() + bp.length() > ab.length() + omega)
            {
                return false;
            }
            return true;

        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;
            if (obj.GetType() != this.GetType()) return false;
            var p = obj as LDIndexLine;
            return this == p;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

    }
}
