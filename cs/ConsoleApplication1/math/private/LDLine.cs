using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDLine
    {
        public enum IntersectType { NoIntersection, BoundedIntersection, UnboundedIntersection };

        private LDPoint pt1;
        private LDPoint pt2;
        
        public LDLine()
        {
            pt1 = new LDPoint(); pt2 = new LDPoint();
        }

        public LDLine(LDPoint apt1, LDPoint apt2)
        {
            this.pt1 = new LDPoint(apt1);
            this.pt2 = new LDPoint(apt2);
        }

        public LDLine(float x1pos, float y1pos, float x2pos, float y2pos)
        {
            this.pt1 = new LDPoint(x1pos, y1pos);
            this.pt2 = new LDPoint(x2pos, y2pos);
        }

        public LDLine(LDLine line)
        {
            this.pt1 = new LDPoint(line.pt1);
            this.pt2 = new LDPoint(line.pt2);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        static LDLine fromPolar(float length, float angle)
        {
            return new LDLine(new LDPoint(0, 0), new LDPoint((float)Math.Cos(angle), (float)Math.Sin(angle)));
        }

        public float x1()
        {
            return this.pt1.x();
        }

        public float y1()
        {
            return this.pt1.y();
        }

        public float x2()
        {
            return this.pt2.x();
        }

        public float y2()
        {
            return this.pt2.y();
        }

        public bool isNull()
        {
            return MathFunctions.uFuzzyCompare(pt1.x(), pt2.x()) &&  MathFunctions.uFuzzyCompare(pt1.y(), pt2.y());
        }

        public LDPoint p1()
        {
            return this.pt1;
        }

        public LDPoint p2()
        {
            return this.pt1;
        }

        public float dx()
        {
            return this.pt2.x() - this.pt1.x();
        }

        public float dy()
        {
            return this.pt2.y() - this.pt1.y();
        }

        public void setP1(LDPoint ap1)
        {
            this.pt1 = ap1;
        }
        public void setP2(LDPoint ap2)
        {
            this.pt2 = ap2;
        }
        public void setPoints(LDPoint aP1, LDPoint aP2)
        {
            this.pt1 = aP1;
            this.pt2 = aP2;
        }
        public void setLine(float aX1, float aY1, float aX2, float aY2)
        {
            this.pt1 = new LDPoint(aX1, aY1);
            this.pt2 = new LDPoint(aX2, aY2);
        }



        public LDLine normalVector()
        {
            return new LDLine(p1(), p1() + new LDPoint(this.dy(), -this.dx()));
        }

        public void translate(LDPoint point)
        {
            this.pt1 += point;
            this.pt2 += point;
        }

        public void translate(float adx, float ady)
        {
            this.translate(new LDPoint(adx, ady));
        }

        public LDLine translated(LDPoint p)
        {
            return new LDLine(pt1 + p, pt2 + p);
        }

        public LDLine translated(float adx, float ady)
        {
            return this.translated(new LDPoint(adx, ady));
        }

        public float length()
        {
            return (float)Math.Pow(this.dx() * this.dx() + this.dy() * this.dy(), 0.5);
        }
        public void setLength(float len)
        {
            if (this.isNull())
            {
                return;
            }
            LDLine v = this.unitVector();
            this.pt2 = new LDPoint(this.pt1.x() + v.dx() * len, this.pt1.y() + v.dy() * len);
        }


        public float angle()
        {
            if(this.isNull())
            {
                return 0;
            }
            double f = Math.Atan2(this.dx(), this.dy()) / Math.PI * 180;
            return f >= 0 ? (float)f : (float)(360 + f);
        }
        public void setAngle(float angle)
        {
            if (this.isNull())
            {
                return;
            }
            this.length();
            this.pt2 = new LDPoint((float)(this.pt1.x() + this.length() * Math.Cos(angle)), (float)(this.pt1.y() + this.length() * Math.Sin(angle)));
        }
        public float angleTo(LDLine l)
        {
            return l.angle()- this.angle() >= 0 ? l.angle() - this.angle() : l.angle() - this.angle() + 360;
        }

        public LDPoint pointAt(float t)
        {
            return new LDPoint(pt1.x() + (pt2.x() - pt1.x()) * t, pt1.y() + (pt2.y() - pt1.y()) * t);
        }

        public static bool operator ==(LDLine a, LDLine b)
        {
            return a.pt1 == b.pt1 && a.pt2 == b.pt2;
        }

        public static bool operator !=(LDLine a, LDLine b)
        {
            return !(a==b);
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;
            if (obj.GetType() != this.GetType()) return false;
            var p = obj as LDLine;
            return this == p;
        }

        /// <summary>
        /// out Upoint 未実装
        /// </summary>
        /// <param name="l"></param>
        /// <param name="point"></param>
        /// <returns></returns>
        public IntersectType intersect(LDLine l, out LDPoint point)
        {
            IntersectType intersect;
            if (MathFunctions.uFuzzyCompare(this.angle(), l.angle()))
            {
                point = null;
                intersect = IntersectType.NoIntersection;
            }
            else
            {
                LDLine lp12 = new LDLine(this.pt1, l.pt1);
                LDLine lp22 = new LDLine(this.pt1, l.pt2);

                LDLine lp11 = new LDLine(l.pt1, this.pt1);
                LDLine lp21 = new LDLine(l.pt1, this.pt2);

                if (((this.angleTo(lp12) - 180f) * (this.angleTo(lp22) - 180f) < 0)
                    && ((this.angleTo(lp11) - 180f) * (this.angleTo(lp21) - 180f) < 0))
                {
                    point = null;
                    intersect = IntersectType.BoundedIntersection;
                }
                else
                {
                    point = null;
                    intersect = IntersectType.UnboundedIntersection;
                }
            }
            return intersect;

        }



        public LDLine unitVector()
        {
            if(this.length() == 0)
            {
                return this;
            }
            LDLine unit = new LDLine(this);
            unit.setP2(new LDPoint(unit.pt1.x() + unit.dx() / this.length(), unit.pt1.y() + unit.dy() / this.length()));
            return unit;
        }
    }

}

