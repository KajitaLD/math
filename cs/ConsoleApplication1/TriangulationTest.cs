using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d.math
{
    public class TriangulationTest : ITest
    {
        public void test()
        {
            triangulationTest();
        }
        public void triangulationTest()
        {
            {
                //0個の頂点を分割。0個の三角形を取得
                LDPointList form = new LDPointList();

                LDTriangleList result = Triangulation.exec(form);

                TestUtil.COMPARE(result.length(), 0);
            }
            {
                //1個の頂点を分割。0個の三角形を取得
                LDPointList form = new LDPointList();
                form.add(new LDPoint(0, 0));
                LDTriangleList result = Triangulation.exec(form);

                TestUtil.COMPARE(result.length(), 0);
            }
            {
                //2個の頂点を分割。0個の三角形を取得
                LDPointList form = new LDPointList();
                form.add(new LDPoint(0, 0)).add(new LDPoint(1, 1));
                LDTriangleList result = Triangulation.exec(form);

                TestUtil.COMPARE(result.length(), 0);
            }
            {
                //3個の頂点を分割。1個の三角形を取得
                LDPointList form = new LDPointList();
                form.add(new LDPoint(0, 0)).add(new LDPoint(1, 1)).add(new LDPoint(1, 0));
                LDTriangleList result = Triangulation.exec(form);

                TestUtil.COMPARE(result.length(), 1);
                TestUtil.VERIFY(result[0] == new LDTriangle(0, 1, 2));
            }
            {
                //4個の頂点を分割。2個の三角形を取得
                LDPointList form = new LDPointList();
                form.add(new LDPoint(0, 0)).add(new LDPoint(1, 1)).add(new LDPoint(1, 0)).add(new LDPoint(0, 1));
                LDTriangleList result = Triangulation.exec(form);

                TestUtil.COMPARE(result.length(), 2);
                TestUtil.VERIFY(result.Contains(new LDTriangle(0, 1, 2)));
                TestUtil.VERIFY(result.Contains(new LDTriangle(0, 1, 3)));
            }

            //	{
            //		LDPointList form;
            //		form).add( new LDPoint(20,0)).add( new LDPoint(1,1)).add( new LDPoint(1,0)).add( new LDPoint(0,1)
            //			).add( new LDPoint(0,15.5)).add( new LDPoint(11,12)).add( new LDPoint(1,0)).add( new LDPoint(100,0.1);
            //		LDTriangleList result=Triangulation.exec(form);
            //		qDebug()).add( new result;
            //	}
        }


    }
}
