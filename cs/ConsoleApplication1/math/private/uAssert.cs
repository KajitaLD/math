using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class Util
    {
        public static void uAssert(bool cond)
        {
            try
            {
                if (cond) { return; }
                throw new Exception();
            }
            catch (Exception ex)
            {
                Console.WriteLine("ASSERT: 'cond' in file" + ex.TargetSite.ToString() );
            }
        }
    }
}
