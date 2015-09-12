using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDMargins
    {
        private float m_left;
        private float m_top;
        private float m_right;
        private float m_bottom;

        public LDMargins()
        {
            this.m_left = 0;
            this.m_top = 0;
            this.m_right = 0;
            this.m_bottom = 0;
        }
        public LDMargins(float left, float top, float right, float bottom)
        {
            this.m_left = left;
            this.m_top = top;
            this.m_right = right;
            this.m_bottom = bottom;
        }
        public LDMargins(LDMargins margins)
        {
            this.m_left = margins.m_left;
            this.m_top = margins.m_top;
            this.m_right = margins.m_right;
            this.m_bottom = margins.m_bottom;
        }

        public bool isNull()
        {
            return MathFunctions.uFuzzyIsNull(m_left) && MathFunctions.uFuzzyIsNull(m_top) && MathFunctions.uFuzzyIsNull(m_right) && MathFunctions.uFuzzyIsNull(m_bottom);
        }

        public float left() { return this.m_left; }
        public float top() { return this.m_top; }
        public float right() { return this.m_right; }
        public float bottom() { return this.m_bottom; }

        public void setLeft(float left) { this.m_left = left; }
        public void setTop(float top) { this.m_top = top; }
        public void setRight(float right) { this.m_right = right; }
        public void setBottom(float bottom) { this.m_bottom = bottom; }

        public static LDMargins operator +(LDMargins a, LDMargins b)
        {
            return new LDMargins(a.m_left   + b.m_left,
                                a.m_top    + b.m_top, 
                                a.m_right  + b.m_right, 
                                a.m_bottom + b.m_bottom);
        }
        public static LDMargins operator -(LDMargins a, LDMargins b)
        {
            return new LDMargins(a.m_left   - b.m_left,
                                a.m_top    - b.m_top,
                                a.m_right  - b.m_right,
                                a.m_bottom - b.m_bottom);
        }
        public static LDMargins operator +(LDMargins a, float addend)
        {
            return new LDMargins(a.m_left   + addend,
                                a.m_top    + addend,
                                a.m_right  + addend,
                                a.m_bottom + addend);
        }
        public static LDMargins operator -(LDMargins a, float subtrahend)
        {
            return new LDMargins(a.m_left   - subtrahend,
                                a.m_top    - subtrahend,
                                a.m_right  - subtrahend,
                                a.m_bottom - subtrahend);
        }
        public static LDMargins operator *(LDMargins a, float factor)
        {
            return new LDMargins(a.m_left   * factor,
                                a.m_top    * factor,
                                a.m_right  * factor,
                                a.m_bottom * factor);
        }
        public static LDMargins operator /(LDMargins a, float divisor)
        {
            return new LDMargins(a.m_left   / divisor,
                                a.m_top    / divisor,
                                a.m_right  / divisor,
                                a.m_bottom / divisor);
        }


    }
}
