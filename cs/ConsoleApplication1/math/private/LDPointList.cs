using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDPointList:List<LDPoint>
    {
        public int length()
        {
            return this.Count;
        }
        public int size()
        {
            return this.Count;
        }
        public LDPoint at(int t)
        {
            return this[t];
        }
        public void replace(int index, LDPoint p)
        {
            this[index] = p;
        }
        public LDPointList add(LDPoint point)
        {
            this.Add(point);
            return this;
        }
    }
}
