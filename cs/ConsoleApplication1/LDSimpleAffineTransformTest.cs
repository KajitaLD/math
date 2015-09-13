using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d
{
    public class LDSimpleAffineTransformTest : ITest
    {
        public void test()
        {
            simpleTransformTest();
            inverseTransformTest();
        }
        public void simpleTransformTest()
        {
            {
                LDSimpleAffineTransform t=new LDSimpleAffineTransform();

                t.setOrigin(new LDPoint(100, 100));
                t.setRotateDeg(90);
                LDPoint src=new LDPoint(1, 0);
                LDPoint dst;
                dst = t.transform(src);


                TestUtil.COMPARE(dst.x(), (double)100);
                TestUtil.COMPARE(dst.y(), (double)100 + 1);

            }
            {
                LDSimpleAffineTransform t=new LDSimpleAffineTransform();

                t.setOrigin(new LDPoint(100, 100));
                t.setRotateDeg(90);
                t.setScale(2);

                LDPoint src=new LDPoint(5, 5);
                LDPoint dst;

                dst = t.transform(src);

                TestUtil.COMPARE(dst.x(), 90.0);
                TestUtil.COMPARE(dst.y(), 110.0);

            }
        }

        public void inverseTransformTest()
        {
            {
                LDSimpleAffineTransform t=new LDSimpleAffineTransform();

                t.setOrigin(new LDPoint(100, 100));
                t.setRotateDeg(90);
                LDPoint src=new LDPoint(100, 101);
                LDPoint dst;
                dst = t.inverseTransform(src);


                TestUtil.COMPARE(dst.x(), (double)1);
                TestUtil.LDFUZZY_COMPARE(dst.y(), (double)0, 0.0001);

            }
        }
    }
}
