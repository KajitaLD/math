using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    public class refTest
    {
        public int i1;
        public int i2;
        public int i3;
        public refTest()
        {
            this.i1 = 0;
            this.i2 = 0;
            this.i3 = 0;
        }
        public static void write(refTest test)
        {
            test.i1 = 10;
            test.i2 = 10;
            test.i3 = 10;
        }
        public override string ToString()
        {
            return this.i1.ToString() + "\n" + this.i2.ToString() + "\n"+ this.i3.ToString() + "\n";
        }
    }
}
