using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace live2d
{
    public enum ClockWise
    {
        CW,
        CCW
    }

    public class LDTriangle
    {

        private int m_index1;
        private int m_index2;
        private int m_index3;

        public LDTriangle() { this.m_index1 = -1; this.m_index2 = -1; this.m_index3 = -1; }
        public LDTriangle(int a, int b, int c) { setIndex(a, b, c); }

        public LDPolygon toPolygon(LDPointList points)
        {
            Debug.Assert((points.length() > m_index1));
            Debug.Assert(points.length() > m_index2);
            Debug.Assert(points.length() > m_index3);

            LDPolygon v = new LDPolygon();

            v.Add(new LDPoint( points.at(m_index1)));
            v.Add(new LDPoint(points.at(m_index2)));
            v.Add(new LDPoint(points.at(m_index3)));
            return v;
        }

        public void setClockWise(LDPointList form, ClockWise clockWise)
        {
            Debug.Assert(form.length() > m_index1);
            Debug.Assert(form.length() > m_index2);
            Debug.Assert(form.length() > m_index3);

            LDPoint v0 = form.at(m_index1);
            LDPoint v1 = form.at(m_index2);
            LDPoint v2 = form.at(m_index3);

            //行列式で時計回りか判定
            //行列式の計算。 QMatrix3x3にはないので手動で作成。

            double[,] m = new double[3, 3]{{ v0.x(),v0.y(),1 },
                                           { v1.x(),v1.y(),1 },
                                           { v2.x(),v2.y(),1 }};

            double determinant = m[0, 0] * m[1, 1] * m[2, 2]
                                 + m[0, 1] * m[1, 2] * m[2, 0]
                                 + m[0, 2] * m[1, 0] * m[2, 1]
                                 - m[0, 2] * m[1, 1] * m[2, 0]
                                 - m[0, 0] * m[1, 2] * m[2, 1]
                                 - m[0, 1] * m[1, 0] * m[2, 2];
            ClockWise current;
            if (determinant < 0) //CW
            {
                current = ClockWise.CW;
            }
            else            //CCWまたは3点が一直線上など
            {
                current = ClockWise.CCW;
            }

            if (clockWise != current) //設定した順番と異なる場合 Indexを入れ替える
            {
                var p = m_index1;
                m_index1 = m_index2;
                m_index2 = p;
            }
        }
        public void setIndex(int a, int b, int c)
        {
            Debug.Assert(a != b);
            Debug.Assert(b != c);
            Debug.Assert(a != c);
            m_index1 = a;
            m_index2 = b;
            m_index3 = c;
        }
        public int getIndex1()
        {
            return m_index1;
        }
        public int getIndex2()
        {
            return m_index2;
        }
        public int getIndex3()
        {
            return m_index3;
        }

        public int getIndexWithoutLine(LDIndexLine l)
        {
            Debug.Assert(containsLine(l));

            if (!l.hasIndex(m_index1))
            {
                return m_index1;
            }
            if (!l.hasIndex(m_index2))
            {
                return m_index2;
            }
            if (!l.hasIndex(m_index3))
            {
                return m_index3;
            }
            return -1;
        }
        public LDPoint getPoint1(LDPointList points)
        {
            return points[m_index1];
        }
        public LDPoint getPoint2(LDPointList points)
        {
            return points[m_index2];
        }
        public LDPoint getPoint3(LDPointList points)
        {
            return points[m_index2];
        }
        public LDIndexLine getLine1()
        {
            return new LDIndexLine(m_index1, m_index2);
        }
        public LDIndexLine getLine2()
        {
            return new LDIndexLine(m_index2, m_index3);
        }
        public LDIndexLine getLine3()
        {
            return new LDIndexLine(m_index1, m_index3);
        }
        public LDIndexLineList getRelatedLines(int pointIndex)
        {
            LDIndexLineList result=new LDIndexLineList();

            LDIndexLine line1 = getLine1();
            LDIndexLine line2 = getLine2();
            LDIndexLine line3 = getLine3();
            if (line1.hasIndex(pointIndex))
            {
                result.Add(line1);
            }
            if (line2.hasIndex(pointIndex))
            {
                result.Add(line2);
            }
            if (line3.hasIndex(pointIndex))
            {
                result.Add(line3);
            }

            return result;
        }
        public bool hasIndex(int pointIndex)
        {
            if (m_index1 == pointIndex)
            {
                return true;
            }
            if (m_index2 == pointIndex)
            {
                return true;
            }
            if (m_index3 == pointIndex)
            {
                return true;
            }
            return false;
        }
        public bool containsLine(LDIndexLine l)
        {
            if (l.hasIndex(m_index1) && l.hasIndex(m_index2))
            {
                return true;
            }
            if (l.hasIndex(m_index2) && l.hasIndex(m_index3))
            {
                return true;
            }
            if (l.hasIndex(m_index1) && l.hasIndex(m_index3))
            {
                return true;
            }

            return false;
        }
        //一つでも線を共有してるかどうか。同じ三角形でも当然共有してる
        public bool isSharedLine(LDTriangle t)
        {
            if (containsLine(t.getLine1()))
            {
                return true;
            }
            if (containsLine(t.getLine2()))
            {
                return true;
            }
            if (containsLine(t.getLine3()))
            {
                return true;
            }

            return false;
        }
        //一致の確認は順番関係なし
        public static bool operator ==(LDTriangle a, LDTriangle b)
        {
            if (a.m_index1 == b.m_index1 && a.m_index2 == b.m_index2 && a.m_index3 == b.m_index3)
            {
                return true;
            }
            if (a.m_index1 == b.m_index1 && a.m_index2 == b.m_index3 && a.m_index3 == b.m_index2)
            {
                return true;
            }
            if (a.m_index1 == b.m_index2 && a.m_index2 == b.m_index1 && a.m_index3 == b.m_index3)
            {
                return true;
            }
            if (a.m_index1 == b.m_index2 && a.m_index2 == b.m_index3 && a.m_index3 == b.m_index1)
            {
                return true;
            }
            if (a.m_index1 == b.m_index3 && a.m_index2 == b.m_index2 && a.m_index3 == b.m_index1)
            {
                return true;
            }
            if (a.m_index1 == b.m_index3 && a.m_index2 == b.m_index1 && a.m_index3 == b.m_index2)
            {
                return true;
            }
            return false;
        }
        public static bool operator !=(LDTriangle a, LDTriangle b)
        {
            return !(a==b);
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;
            if (obj.GetType() != this.GetType()) return false;
            var p = obj as LDTriangle;
            return this == p;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        //LD_SERIALIZABLE;
    }
}
