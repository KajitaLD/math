using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDLineList : List<LDLine>
    {
        public int length()
        {
            return this.Count;
        }
    }
}
