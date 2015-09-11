using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDVector2
    {

        private float xp;
        private float yp;

        public LDVector2() { }
        public LDVector2(float xpos, float ypos) { this.xp = xpos; this.yp = ypos; }
        public LDVector2(LDPoint point) { this.xp = point.x(); this.xp = point.y(); }

        public bool isNull() { return MathFunctions.uIsNull(xp) && MathFunctions.uIsNull(yp); }

        public float x() { return this.xp; }
        public float y() { return this.yp; }

        public void setX(float x) { this.xp = x; }
        public void setY(float y) { this.yp = y; }

        public float this[int i]
        {
            set
            {
                if (i == 0) { this.xp = value; }
                if (i == 1) { this.yp = value; }
                else { throw new KeyNotFoundException(); }
            }
            get
            {
                if (i == 0) { return this.xp; }
                if (i == 1) { return this.yp; }
                else { throw new KeyNotFoundException(); }
            }
        }

        public float length() { return (float)Math.Pow(this.lengthSquared(), 0.5); }
        public float lengthSquared() { return this.xp * this.xp + this.yp * this.yp; } //In Qt 6 convert to inline and expr

        /// <summary>
        /// 未実装
        /// </summary>
        /// <returns></returns>
        public LDVector2 normalized() { throw new NotImplementedException(); }
        public void normalize()
        {
            LDVector2 normalized = this.normalized();
            this.xp = normalized.xp;
            this.yp = normalized.yp;
        }

        /// <summary>
        /// 未実装
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        public float distanceToPoint(LDVector2 point) { throw new NotImplementedException(); }
        public float distanceToLine(LDVector2 point, LDVector2 direction) { throw new NotImplementedException(); }

        public static LDVector2 operator +(LDVector2 v1, LDVector2 v2)
        {
            return new LDVector2(v1.xp + v2.xp, v1.yp + v2.yp);
        }
        public static LDVector2 operator -(LDVector2 v1, LDVector2 v2)
        {
            return new LDVector2(v1.xp - v2.xp, v1.yp - v2.yp);
        }
        public static LDVector2 operator *(LDVector2 v1, float factor)
        {
            return new LDVector2(v1.xp *factor, v1.yp * factor);
        }

        public static LDVector2 operator *( float factor, LDVector2 v1)
        {
            return new LDVector2(v1.xp * factor, v1.yp * factor);
        }
        public static LDVector2 operator *(LDVector2 v1, LDVector2 v2)
        {
            return new LDVector2(v1.xp *v2.xp, v1.yp * v2.yp);
        }
        public static LDVector2 operator /(LDVector2 v1, float divisor)
        {
            return new LDVector2(v1.xp / divisor, v1.yp / divisor);
        }

        public static float dotProduct(LDVector2 v1, LDVector2 v2)
        {
            return v1.xp * v2.xp + v1.yp * v2.yp;
        }

        public static bool operator ==(LDVector2 v1, LDVector2 v2)
        {
            return v1.xp == v2.xp && v1.yp == v2.yp;
        }
        public static bool operator !=(LDVector2 v1, LDVector2 v2)
        {
            return v1.xp != v2.xp || v1.yp != v2.yp;
        }

        public bool uFuzzyCompare(LDVector2 v1, LDVector2 v2)
        {
            return MathFunctions.uFuzzyCompare(v1.xp, v2.xp) && MathFunctions.uFuzzyCompare(v1.yp, v2.yp);
        }
        public LDPoint toPoint()
        {
            return new LDPoint(this.xp, this.yp);
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;
            if (obj.GetType() != this.GetType()) return false;
            var p = obj as LDVector2;
            return this == p;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }
}
