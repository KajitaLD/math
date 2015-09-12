using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace live2d
{
    public class common
    {
        public static void LD_ASSERT_OUT_OF_INDEX<T>(IEnumerable<T> list, int index)
        {
            System.Diagnostics.Debug.Assert(0 <= index && index < list.Count(), "index check", index.ToString());
        }
        public static void Warning(string str)
        {
            System.Diagnostics.Debug.WriteLine(str);
        }
        public static void Critical(string str)
        {
            System.Diagnostics.Debug.WriteLine(str);
        }
        public static void Debug(string str)
        {
            System.Diagnostics.Debug.WriteLine(str);
        }
        public static void LD_ASSERT_OUT_OF_RANGE(double x, double min, double max)
        {
            System.Diagnostics.Debug.Assert(min <= x && x <= max);
        }
        public static void LD_ASSERT_OUT_OF_RANGE(float x, float min , float max)
        {
            System.Diagnostics.Debug.Assert(min <= x && x <= max);
        }
    }
}
