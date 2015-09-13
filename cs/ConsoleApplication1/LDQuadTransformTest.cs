using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d
{
    public class LDQuadTransformTest : ITest
    {
        public void test()
        {
            simpleTransformTest();
            transformTest();
            inverseTransformTest();
            rotationTest();
            extendedTransformTest();
        }


        public void simpleTransformTest()
        {

            LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10), new LDPoint(30, 30));

            {
                LDPoint src=new LDPoint(0, 0);

                LDPoint dst;

                dst = quad.transform(src);

                TestUtil.COMPARE(dst.x(), 10.0);
                TestUtil.COMPARE(dst.y(), 10.0);
            }

            {
                LDPoint src=new LDPoint(1, 1);

                LDPoint dst;

                dst = quad.transform(src);

                TestUtil.COMPARE(dst.x(), 30.0);
                TestUtil.COMPARE(dst.y(), 30.0);
            }


            {
                LDPoint src=new LDPoint(0.5f, 0.25f);

                LDPoint dst;

                dst = quad.transform(src);

                TestUtil.COMPARE(dst.x(), 20.0f);
                TestUtil.COMPARE(dst.y(), 15.0f);
            }
            {
                LDPoint src=new LDPoint(0.75f, 0.8f);

                LDPoint dst;

                dst = quad.transform(src);

                TestUtil.COMPARE(dst.x(), 25.0f);
                TestUtil.COMPARE(dst.y(), 26.0f);
            }
            {
                LDPointList src=new LDPointList();
                src.add(new LDPoint(0.25f, 0.4f)).add( new LDPoint(0.75f, 0.8f));

                LDPointList dst;

                dst = quad.transform(src);

                TestUtil.VERIFY(dst.length() == 2);

                TestUtil.COMPARE(dst[0],new LDPoint(15.0f, 18.0f));
                TestUtil.COMPARE(dst[1],new LDPoint(25, 26));
            }

            //	{
            //		LDGridTransform src(0.5,0.5,0.5,0.5,1,1);

            //		LDGridTransform dst;

            //		dst=grid.transform(src);

            //		TestUtil.COMPARE(dst.getPoint(0,0),LDPoint(40,40));
            //		TestUtil.COMPARE(dst.getPoint(0,1),LDPoint(60,40));
            //		TestUtil.COMPARE(dst.getPoint(1,1),LDPoint(60,60));
            //		TestUtil.COMPARE(dst.getPoint(1,0),LDPoint(40,60));
            //	}

            //	{
            //		LDAffineTransform src;
            //		src.translate(0.5,0.5);
            //		src.rotate(30);
            //		src.scale(2,2);

            //		LDAffineTransform dst;

            //		dst=grid.transform(src);

            //		TestUtil.COMPARE(dst.getTranslate(),LDPoint(40,40));
            //	}
        }

        public void transformTest()
        {
            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10),new LDPoint(30, 30));
                LDPoint src=new LDPoint(0.5f, 0.25f);

                LDPoint dst=new LDPoint();

                dst = quad.transform(src);

                TestUtil.COMPARE(dst.x(), 20.0);
                TestUtil.COMPARE(dst.y(), 15.0);
            }

            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10),new  LDPoint(20, 10), new LDPoint(100, 100), new LDPoint(10, 20));
                LDPoint src=new LDPoint(0.9f, 0.9f);

                LDPoint dst=new LDPoint();

                dst = quad.transform(src);

                //		TestUtil.COMPARE(dst.x(),83.8);
                //		TestUtil.COMPARE(dst.y(),83.8);
                TestUtil.LDFUZZY_COMPARE(dst.x(), 83.8, 0.0000001);
                TestUtil.LDFUZZY_COMPARE(dst.y(), 83.8, 0.0000001);

                //		TestUtil.LDFUZZY_COMPARE(dst.x(),83,0.001);
                //		TestUtil.LDFUZZY_COMPARE(dst.y(),83,0.001);
            }
        }

        public void inverseTransformTest()
        {
            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10),new LDPoint(30, 30));
                LDPoint src=new LDPoint(20, 15);

                LDPoint dst=new LDPoint();

                dst = quad.inverseTransform(src);

                TestUtil.COMPARE(dst.x(), 0.5);
                TestUtil.COMPARE(dst.y(), 0.25);
            }
            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10), new LDPoint(20, 10), new LDPoint(100, 100), new LDPoint(10, 20));
                LDPoint src=new LDPoint(83.8f, 83.8f);

                LDPoint dst;

                dst = quad.inverseTransform(src);
                //		TestUtil.COMPARE(dst.x(),0.9);
                //		TestUtil.COMPARE(dst.y(),0.9);
                TestUtil.LDFUZZY_COMPARE(dst.x(), 0.9, 0.0000001);
                TestUtil.LDFUZZY_COMPARE(dst.y(), 0.9, 0.0000001);
            }
            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10), new LDPoint(30, 30));
                LDPoint src=new LDPoint(20, 25);

                LDPoint dst;

                dst = quad.inverseTransform(src);

                TestUtil.COMPARE(dst.x(), 0.5);
                TestUtil.COMPARE(dst.y(), 0.75);
            }
            {
                //(0,0),(100,100)を90度回転
                LDQuadTransform quad=new LDQuadTransform(
                           new LDPoint(100, 0),
                           new LDPoint(100, 100),
                           new LDPoint(0, 100),
                           new LDPoint(0, 0)
        					);
                LDPoint src=new LDPoint(75, 50);

                LDPoint dst;

                dst = quad.inverseTransform(src);
                TestUtil.COMPARE(dst.x(), 0.5);
                TestUtil.COMPARE(dst.y(), 0.25);
            }

            {
                //大きめの数字
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(1024, 1024), new LDPoint(3500, 3500));
                LDPoint src=new LDPoint(2000, 2000);

                LDPoint dst;

                dst = quad.inverseTransform(src);

                TestUtil.LDFUZZY_COMPARE(dst.x(), 0.394184, 0.00001);
                TestUtil.LDFUZZY_COMPARE(dst.y(), 0.394184, 0.00001);
            }
            {
                //斜め
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10),new LDPoint(20, 20),new LDPoint(20, 30),new LDPoint(10, 20));
                LDPoint src=new LDPoint(15, 20);

                LDPoint dst;

                dst = quad.inverseTransform(src);

                TestUtil.COMPARE(dst.x(), 0.5);
                TestUtil.COMPARE(dst.y(), 0.5);
            }

            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10.12345f, 10.12321f),new LDPoint(20.1102f, 20.034f),new LDPoint(20.11111f, 30.22222f), new LDPoint(10.232697f, 20.00008f));
                LDPoint src=new LDPoint(15.8731f, 20.5396f);

                LDPoint dst;
                LDPoint rest;
                dst = quad.inverseTransform(src);
                rest = quad.transform(dst);

                TestUtil.LDFUZZY_COMPARE(src.x(), rest.x(), 0.0000001);
                TestUtil.LDFUZZY_COMPARE(src.y(), rest.y(), 0.0000001);
            }
            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(1023.12345f, 1041.12321f),new LDPoint(2075.1102, 2032.034),new LDPoint(2034.11111, 3061.22222),new LDPoint(1023.232697, 2088.00008));
                LDPoint src=new LDPoint(1515.8731, 2072.5396);

                LDPoint dst;
                LDPoint rest;
                dst = quad.inverseTransform(src);
                rest = quad.transform(dst);

                TestUtil.LDFUZZY_COMPARE(src.x(), rest.x(), 0.0000001);
                TestUtil.LDFUZZY_COMPARE(src.y(), rest.y(), 0.0000001);
            }
        }

        public void rotationTest()
        {
            {
                //(0,0),(100,100)を90度回転
                LDQuadTransform quad=new LDQuadTransform(
                           new LDPoint(100, 0),
                           new LDPoint(100, 100),
                           new LDPoint(0, 100),
                           new LDPoint(0, 0)
        					);
                LDPoint src=new LDPoint(0.5, 0.25);

                LDPoint dst;

                dst = quad.transform(src);

                TestUtil.COMPARE(dst.x(), 75.0);
                TestUtil.COMPARE(dst.y(), 50.0);
            }
            {
                //(0,0),(100,100)を180度回転
                LDQuadTransform quad=new LDQuadTransform(
                           new LDPoint(100, 100),
                           new LDPoint(0, 100),
                           new LDPoint(0, 0),
                           new LDPoint(100, 0)
        					);
                LDPoint src=new LDPoint(0.5, 0.25);

                LDPoint dst;

                dst = quad.transform(src);

                TestUtil.COMPARE(dst.x(), 50.0);
                TestUtil.COMPARE(dst.y(), 75.0);
            }
        }

        public void extendedTransformTest()
        {
            //範囲外補間

            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10),new LDPoint(30, 30));

                LDPoint src=new LDPoint(-1, -1);

                LDPoint dst;

                dst = quad.transform(src);

                TestUtil.COMPARE(dst.x(), -10.0);
                TestUtil.COMPARE(dst.y(), -10.0);
            }

            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10),new LDPoint(30, 30));

                LDPoint src=new LDPoint(-1, -1);

                LDPoint dst;

                dst = quad.transform(src, true);//範囲内にクリッピングする

                TestUtil.COMPARE(dst.x(), 10.0);
                TestUtil.COMPARE(dst.y(), 10.0);
            }

            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10),new LDPoint(30, 30));

                LDPoint src=new LDPoint(2, 2);

                LDPoint dst;

                dst = quad.transform(src);

                TestUtil.COMPARE(dst.x(), 50.0);
                TestUtil.COMPARE(dst.y(), 50.0);
            }

            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10),new LDPoint(30, 30));
                LDPoint src= new LDPoint(40, 40);

                LDPoint dst;

                dst = quad.inverseTransform(src);

                TestUtil.COMPARE(dst.x(), 1.5);
                TestUtil.COMPARE(dst.y(), 1.5);
            }

            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10, 10),new LDPoint(30, 30));
                LDPoint src=new LDPoint(40, 40);

                LDPoint dst;

                dst = quad.inverseTransform(src, true);

                TestUtil.COMPARE(dst.x(), 1.0);
                TestUtil.COMPARE(dst.y(), 1.0);
            }

            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(10.12345, 10.12321), new LDPoint(20.1102, 20.034), new LDPoint(20.11111, 30.22222), new LDPoint(10.232697, 20.00008));
                LDPoint src=new LDPoint(45.8731, 60.5396);

                LDPoint dst;
                LDPoint rest;
                dst = quad.inverseTransform(src);
                rest = quad.transform(dst);

                TestUtil.LDFUZZY_COMPARE(src.x(), rest.x(), 0.0000001);
                TestUtil.LDFUZZY_COMPARE(src.y(), rest.y(), 0.0000001);
            }
            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(1023.12345, 1041.12321), new LDPoint(2075.1102, 2032.034), new LDPoint(2034.11111, 3061.22222), new LDPoint(1023.232697, 2088.00008));
                LDPoint src=new LDPoint(11515.8731, 62072.5396);

                LDPoint dst;
                LDPoint rest;
                dst = quad.inverseTransform(src);
                rest = quad.transform(dst);

                TestUtil.LDFUZZY_COMPARE(src.x(), rest.x(), 0.0000001);
                TestUtil.LDFUZZY_COMPARE(src.y(), rest.y(), 0.0000001);
            }
            {
                LDQuadTransform quad=new LDQuadTransform(new LDPoint(1023.12345, 1041.12321), new LDPoint(2075.1102, 2032.034), new LDPoint(2034.11111, 3061.22222), new LDPoint(1023.232697, 2088.00008));
                LDPoint src=new LDPoint(5.8731, 72.5396);

                LDPoint dst;
                LDPoint rest;
                dst = quad.inverseTransform(src);
                rest = quad.transform(dst);

                TestUtil.LDFUZZY_COMPARE(src.x(), rest.x(), 0.0000001);
                TestUtil.LDFUZZY_COMPARE(src.y(), rest.y(), 0.0000001);
            }
        }

    }
}
