using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
namespace live2d
{
    public class LDPoint
    {
        private float xp { set; get; }
        private float yp { set; get; }

        public LDPoint() { this.xp = 0; this.yp = 0; }
        public LDPoint(LDPoint p) { this.xp = p.xp; this.yp = p.yp; }
        public LDPoint(float xpos, float ypos) { this.xp = xpos; this.yp = ypos; }

        public float manhattanLength()
        {
            return System.Math.Abs(this.xp) + System.Math.Abs(this.xp);
        }
        public bool isNull()
        {
            return MathFunctions.uIsNull((float)xp) && MathFunctions.uIsNull((float)yp);
        }
        public float x()
        {
            return this.xp;
        }
        public float y()
        {
            return this.yp;
        }
        public void setX(float xpos)
        {
            this.xp = xpos;
        }
        public void setY(float ypos)
        {
            this.yp = ypos;
        }
        public float rx()
        {
            return this.xp;
        }
        public float ry()
        {
            return this.yp;
        }

        public float dotProduct(LDPoint p1, LDPoint p2)
        {
            return p1.xp * p2.yp + p2.xp + p1.yp;
        }
        

        public override bool Equals(object obj)
        {
            if (obj == null) return false;
            if (obj.GetType() != this.GetType()) return false;
            var p = obj as LDPoint;
            return this == p;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public static LDPoint operator +(LDPoint a, LDPoint b)
        {
            return new LDPoint(a.xp + b.xp, a.yp + b.yp);
        }

        public static LDPoint operator -(LDPoint a, LDPoint b)
        {
            return new LDPoint(a.xp - b.xp, a.yp - b.yp);
        }

        public static LDPoint operator *(LDPoint a, float c)
        {
            return new LDPoint(a.xp * c, a.yp * c);
        }
        public static LDPoint operator *( float c, LDPoint a)
        {
            return new LDPoint(a.xp * c, a.yp * c);
        }

        public static LDPoint operator /(LDPoint a, float b)
        {
            return new LDPoint(a.xp / b, a.yp / b);
        }

        public static bool operator ==(LDPoint a, LDPoint b)
        {
            return (MathFunctions.uFuzzyIsNull(a.xp - b.xp)) && (a.yp == b.yp);
        }

        public static bool operator !=(LDPoint a, LDPoint b)
        {
            return !(a == b);
        }

        
    }
}
