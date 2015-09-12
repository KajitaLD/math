using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            refTest test = new refTest();
            Console.WriteLine(test.ToString());
            refTest.write(test);
            Console.WriteLine(test.ToString());


        }
    }
}
