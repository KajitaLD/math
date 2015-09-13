using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDPointList:List<LDPoint> , IComparable
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

        public int CompareTo(object obj)
        {
            if (obj.GetType() != this.GetType()) return -1;
            var p = obj as LDPointList;
            if (p.Count == this.Count)
            {
                for (int i = 0; i < this.Count; i++)
                {
                    if (p[i] != this[i])
                    {
                        return -1;
                    }
                }
                return 0;
            }
            else
            {
                return -1;
            }
        }
    }
}
