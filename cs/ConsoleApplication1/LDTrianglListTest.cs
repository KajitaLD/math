using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d
{
    public class LDTrianglListTest : ITest
    {
        public void test()
        {
            findTest_simple();
            toIndexLineListTest_simple();
            getOutlinePointIndicesTest_simple();
            getOutlinePointsTest_simple();
            getOutlinePolygonTest_simple();
            getRelatedTrianglesTest_simple();
            getRelatedLinesTest_simple();
            getRelatedPointIndicesTest_simple();
        }
        LDTriangleList simpleTriangle()
        {
            LDTriangleList triangles=new LDTriangleList();
            LDTriangle t1=new LDTriangle(0, 1, 2);
            triangles.Add(t1);
            return triangles;
        }


        public void findTest_simple()
        {
            LDTriangleList triangles = simpleTriangle();
            LDTriangleList compare = simpleTriangle();
            LDIndexLine line=new LDIndexLine(0, 2);
            LDTriangleList resulut = triangles.find(line);
            TestUtil.COMPARE(resulut, compare);

        }

        public void toIndexLineListTest_simple()
        {
            LDTriangleList triangles = simpleTriangle();

            LDIndexLineList compare=new LDIndexLineList();
            LDIndexLine line_1=new LDIndexLine(0, 1);
            LDIndexLine line_2=new LDIndexLine(1, 2);
            LDIndexLine line_3 = new LDIndexLine(2, 0);
            compare.Add(line_1);
            compare.Add(line_2);
            compare.Add(line_3);

            LDIndexLineList result = triangles.toIndexLineList();

            TestUtil.COMPARE(result, compare);
        }

        public void getOutlinePointIndicesTest_simple()
        {
            LDTriangleList triangles = simpleTriangle();

            LDPointList points=new LDPointList();
            points.Add(new LDPoint(0, 0));
            points.Add(new LDPoint(0, 100));
            points.Add(new LDPoint(100, 100));

            List<int> compare=new List<int>();
            compare.Add(0);
            compare.Add(1);
            compare.Add(2);

            List<int> result = triangles.getOutlinePointIndices(points);

            TestUtil.COMPARELIST(result, compare);
        }

        public void getOutlinePointsTest_simple()
        {
            LDTriangleList triangles = simpleTriangle();
            LDPointList points=new LDPointList();
            points.Add(new LDPoint(0, 0));
            points.Add(new LDPoint(0, 100));
            points.Add(new LDPoint(100, 100));

            LDPointList compare = points;

            LDPointList result = triangles.getOutlinePoints(points);

            TestUtil.COMPARE(result, compare);


        }

        public void getOutlinePolygonTest_simple()
        {
            LDTriangleList triangles = simpleTriangle();
            LDPointList points=new LDPointList();
            points.Add(new LDPoint(0, 0));
            points.Add(new LDPoint(0, 100));
            points.Add(new LDPoint(100, 100));

            LDPolygon compare=new LDPolygon();
            compare.Add(new LDPoint(0, 0));
            compare.Add(new LDPoint(0, 100));
            compare.Add(new LDPoint(100, 100));

            LDPolygon result = triangles.getOutlinePolygon(points);

            TestUtil.COMPARE(result, compare);

        }

        public void getRelatedTrianglesTest_simple()
        {
            LDTriangleList triangles = simpleTriangle();

            LDTriangleList compare = simpleTriangle();

            LDTriangleList result = triangles.getRelatedTriangles(0);
            TestUtil.COMPARE(result, compare);

        }

        public void getRelatedLinesTest_simple()
        {
            LDTriangleList triangles = simpleTriangle();
            LDIndexLineList compare=new LDIndexLineList();
            compare.Add(new LDIndexLine(0, 1));
            compare.Add(new LDIndexLine(0, 2));

            LDIndexLineList result = triangles.getRelatedLines(0);
            TestUtil.COMPARE(result, compare);


        }

        public void getRelatedPointIndicesTest_simple()
        {
            LDTriangleList triangles = simpleTriangle();
            List<int> compare=new List<int>();
            compare.Add(1);
            compare.Add(2);

            List<int> result = triangles.getRelatedPointIndices(0);
            TestUtil.COMPARELIST(result, compare);

        }

    }
}
