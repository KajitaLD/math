using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using LDRect = live2d.LDRect;

namespace live2d
{
    

    static class MathFunctions
    {
        

        static public bool uIsNull(float f)
        {
            var val = System.BitConverter.ToUInt32(System.BitConverter.GetBytes(f), 0);
            return (val & 0x7fffffff) == 0;
        }
        static public bool uFuzzyIsNull(float f)
        {
            return Math.Abs(f) <= 0.00001f;
        }

        static public bool uFuzzyCompare(float p1, float p2)
        {
            return (Math.Abs(p1 - p2) * 100000f <= Math.Min(Math.Abs(p1), Math.Abs(p2)));
        }

        
    }
    public enum FillRule
    {
        OddEvenFill,
        WindingFill
    }
}


