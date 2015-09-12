using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDUvMap : List<LDPoint>
    {
        public int length()
        {
            return this.Count;
        }
        public void replace(int index, LDPoint uv)
        {
            this[index] = uv;
        }
    }
}
