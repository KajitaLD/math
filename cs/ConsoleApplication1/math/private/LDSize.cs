using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDSize
    {
        private float wd;
        private float ht;

        public enum AspectRatioMode
        {
            IgnoreAspectRatio,
            KeepAspectRatio,
            KeepAspectRatioByExpanding
        };

        public LDSize()
        {
            this.wd = -1;
            this.ht = -1;
        }

        public LDSize(LDSize sz)
        {
            this.wd = sz.wd;
            this.ht = sz.ht;
        }

        public LDSize(float w, float h)
        {
            this.wd = w;
            this.ht = h;
        }

        public bool isNull()
        {
            return MathFunctions.uIsNull(wd) && MathFunctions.uIsNull(ht);
        }

        public bool isEmpty()
        {
            return wd <= 0 || ht <= 0;
        }
        public bool isValid()
        {
            return wd >= 0 && ht >= 0;
        }

        public float width()
        {
            return this.wd;
        }

        public float height()
        {
            return this.ht;
        }

        public void setWidth(float w)
        {
            this.wd = w;
        }

        public void setHeight(float h)
        {
            this.ht = h;
        }

        public void transpose()
        {
            float buff = this.wd;
            this.wd = ht;
            this.ht = buff;
        }

        public LDSize transposed()
        {
            return new LDSize(ht, wd);
        }

        public void scale(float w, float h,AspectRatioMode mode)
        {
            this.scale(new LDSize(w, h), mode);
        }

        public void scale(LDSize s, AspectRatioMode mode)
        {
            LDSize size = this.scaled(s, mode);
            this.wd = size.wd;
            this.ht = size.ht;
        }

        public LDSize scaled(float w, float h, AspectRatioMode mode)
        {
            return this.scaled(new LDSize(w, h), mode);
        }

        public LDSize scaled(LDSize s, AspectRatioMode mode)
        {
            if (s.isEmpty()) return new LDSize();
            LDSize S;
            switch (mode)
            {
                case AspectRatioMode.IgnoreAspectRatio:
                    S = s;
                    break;
                case AspectRatioMode.KeepAspectRatio:
                    S = new LDSize(this.wd * Math.Min(s.wd / this.wd, s.ht / this.ht), this.ht * Math.Min(s.wd / this.wd, s.ht / this.ht));
                    break;
                case AspectRatioMode.KeepAspectRatioByExpanding:
                    S = new LDSize(this.wd * Math.Max(s.wd / this.wd, s.ht / this.ht), this.ht * Math.Max(s.wd / this.wd, s.ht / this.ht));
                    break;
                default:
                    S = null;
                    break;
            }
            return S;
        }

        public LDSize expandedTo(LDSize s)
        {
            return new LDSize(Math.Max(this.wd, s.wd), Math.Max(this.wd, this.ht));
        }
        public LDSize boundedTo(LDSize s)
        {
            return new LDSize(Math.Min(this.wd, s.wd), Math.Min(this.wd, this.ht));
        }

        public float rwidth()
        {
            return wd;
        }
        public float rheight()
        {
            return ht;
        }

        public static LDSize operator+(LDSize a, LDSize b)
        {
            return new LDSize(a.wd + b.wd, a.ht + b.ht);
        }
        public static LDSize operator-(LDSize a, LDSize b)
        {
            return new LDSize(a.wd - b.wd, a.ht - b.ht);
        }
        public static LDSize operator *(LDSize a, float c)
        {
            return new LDSize(a.wd * c, a.ht * c);
        }
        public static LDSize operator *(float c, LDSize a)
        {
            return new LDSize(a.wd * c, a.ht * c);
        }
        public static LDSize operator /(LDSize a, float b)
        {
            return new LDSize(a.wd / b, a.ht / b);
        }

        public static bool operator ==(LDSize a, LDSize b)
        {
            return (MathFunctions.uFuzzyIsNull(a.wd - b.wd)) && (a.ht == b.ht);
        }
        public static bool operator !=(LDSize a, LDSize b)
        {
            return !(a == b);
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;
            if (obj.GetType() != this.GetType()) return false;
            var p = obj as LDSize;
            return this == p;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }
}
