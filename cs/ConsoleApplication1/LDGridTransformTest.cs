using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d
{
    public class LDGridTransformTest : ITest
    {
        public void test()
        {
            this.simpleTransformTest();
            this.inverseTransformTest();
            this.getQuadTest();
            this.extendedTransformTest();
            this.hitTest();

        }

        /*
        public void serializeTest()
        {
            string name = "gridMesh";
            LDGridTransform src = new LDGridTransform(0, 0, 100, 100, 2, 2));

            //シリアライズ
            SerializeHelper.writeBoostXml(name, src);

            //デシリアライズ
            var dst = SerializeHelper.readBoostXml<LDGridTransform>(name);

            TestUtil.VERIFY(dst->getGridPoints() == src->getGridPoints());
        }
        */
        public void simpleTransformTest()
        {
            LDGridTransform grid = new LDGridTransform(20, 20, 40, 40, 1, 1);

            {
                LDPoint src = new LDPoint(0.5f, 0.5f);

                LDPoint dst;

                dst = grid.transform(src);

                TestUtil.COMPARE(dst.x(), 40.0);
                TestUtil.COMPARE(dst.y(), 40.0);
            }

            {
                LDPointList src = new LDPointList();
                src.add(new LDPoint(0.25f, 0.25f)).add(new LDPoint(0.75f, 0.75f));

                LDPointList dst;

                dst = grid.transform(src);

                TestUtil.VERIFY(dst.length() == 2);
                TestUtil.COMPARE(dst[0], new LDPoint(30.0f, 30));
                TestUtil.COMPARE(dst[1], new LDPoint(50.0f, 50));
            }

            {
                LDGridTransform src = new LDGridTransform(0.5f, 0.5f, 0.5f, 0.5f, 1, 1);

                LDGridTransform dst = new LDGridTransform();

                dst = grid.transform(src);

                TestUtil.COMPARE(dst.getPoint(0, 0),new LDPoint(40, 40));
                TestUtil.COMPARE(dst.getPoint(0, 1),new LDPoint(60, 40));
                TestUtil.COMPARE(dst.getPoint(1, 1),new LDPoint(60, 60));
                TestUtil.COMPARE(dst.getPoint(1, 0),new LDPoint(40, 60));
            }

            {
                LDAffineTransform src = new LDAffineTransform();
                src.translate(0.5f, 0.5f);
                src.rotate(30);
                src.scale(2, 2);

                LDAffineTransform dst = new LDAffineTransform();

                dst = grid.transform(src);

                TestUtil.COMPARE(dst.getTranslate(), new LDPoint(40, 40));
            }
        }

        public void getQuadTest()
        {


            {
                LDGridTransform grid = new LDGridTransform(20, 20, 60, 60, 3, 3);
                var outline = grid.getOutlineQuadTransform();

                TestUtil.COMPARE(outline.getTopLeft(), new LDPoint(20, 20));
                TestUtil.COMPARE(outline.getTopRight(), new LDPoint(80, 20));
                TestUtil.COMPARE(outline.getBottomRight(), new LDPoint(80, 80));
                TestUtil.COMPARE(outline.getBottomLeft(), new LDPoint(20, 80));

                //0行0列目(左上)の四角変形
                var quad00 = grid.getQuadTransform(0, 0);
                TestUtil.COMPARE(quad00.getTopLeft(), new LDPoint(20, 20));
                TestUtil.COMPARE(quad00.getTopRight(), new LDPoint(40, 20));
                TestUtil.COMPARE(quad00.getBottomRight(), new LDPoint(40, 40));
                TestUtil.COMPARE(quad00.getBottomLeft(), new LDPoint(20, 40));

                //0行1列目の四角変形
                var quad01 = grid.getQuadTransform(0, 1);
                TestUtil.COMPARE(quad01.getTopLeft(), new LDPoint(40, 20));
                TestUtil.COMPARE(quad01.getTopRight(), new LDPoint(60, 20));
                TestUtil.COMPARE(quad01.getBottomRight(), new LDPoint(60, 40));
                TestUtil.COMPARE(quad01.getBottomLeft(), new LDPoint(40, 40));

                //0行2列目の四角変形
                var quad02 = grid.getQuadTransform(0, 2);
                TestUtil.COMPARE(quad02.getTopLeft(), new LDPoint(60, 20));
                TestUtil.COMPARE(quad02.getTopRight(), new LDPoint(80, 20));
                TestUtil.COMPARE(quad02.getBottomRight(), new LDPoint(80, 40));
                TestUtil.COMPARE(quad02.getBottomLeft(), new LDPoint(60, 40));

                //1行1列目(中央)の四角変形
                var quad11 = grid.getQuadTransform(1, 1);
                TestUtil.COMPARE(quad11.getTopLeft(), new LDPoint(40, 40));
                TestUtil.COMPARE(quad11.getTopRight(), new LDPoint(60, 40));
                TestUtil.COMPARE(quad11.getBottomRight(), new LDPoint(60, 60));
                TestUtil.COMPARE(quad11.getBottomLeft(), new LDPoint(40, 60));

                //2行2列目(右下)の四角変形
                var quad22 = grid.getQuadTransform(2, 2);
                TestUtil.COMPARE(quad22.getTopLeft(), new LDPoint(60, 60));
                TestUtil.COMPARE(quad22.getTopRight(), new LDPoint(80, 60));
                TestUtil.COMPARE(quad22.getBottomRight(), new LDPoint(80, 80));
                TestUtil.COMPARE(quad22.getBottomLeft(), new LDPoint(60, 80));
            }

            {
                LDGridTransform grid = new LDGridTransform(20, 20, 60, 60, 3, 3);
                //列の幅を変更
                grid.setPoint(0, 1, new LDPoint(35, 20));
                grid.setPoint(1, 1, new LDPoint(35, 40));
                grid.setPoint(2, 1, new LDPoint(35, 60));
                grid.setPoint(3, 1, new LDPoint(35, 80));

                grid.setPoint(0, 2, new LDPoint(50, 20));
                grid.setPoint(1, 2, new LDPoint(50, 40));
                grid.setPoint(2, 2, new LDPoint(50, 60));
                grid.setPoint(3, 2, new LDPoint(50, 80));

                var outline = grid.getOutlineQuadTransform();

                TestUtil.COMPARE(outline.getTopLeft(), new LDPoint(20, 20));
                TestUtil.COMPARE(outline.getTopRight(), new LDPoint(80, 20));
                TestUtil.COMPARE(outline.getBottomRight(), new LDPoint(80, 80));
                TestUtil.COMPARE(outline.getBottomLeft(), new LDPoint(20, 80));

                //0行0列目(左上)の四角変形
                var quad00 = grid.getQuadTransform(0, 0);
                TestUtil.COMPARE(quad00.getTopLeft(), new LDPoint(20, 20));
                TestUtil.COMPARE(quad00.getTopRight(), new LDPoint(35, 20));
                TestUtil.COMPARE(quad00.getBottomRight(), new LDPoint(35, 40));
                TestUtil.COMPARE(quad00.getBottomLeft(), new LDPoint(20, 40));

                //1行1列目(中央)の四角変形
                var quad11 = grid.getQuadTransform(1, 1);
                TestUtil.COMPARE(quad11.getTopLeft(), new LDPoint(35, 40));
                TestUtil.COMPARE(quad11.getTopRight(), new LDPoint(50, 40));
                TestUtil.COMPARE(quad11.getBottomRight(), new LDPoint(50, 60));
                TestUtil.COMPARE(quad11.getBottomLeft(), new LDPoint(35, 60));

                //2行2列目(右下)の四角変形
                var quad22 = grid.getQuadTransform(2, 2);
                TestUtil.COMPARE(quad22.getTopLeft(), new LDPoint(50, 60));
                TestUtil.COMPARE(quad22.getTopRight(), new LDPoint(80, 60));
                TestUtil.COMPARE(quad22.getBottomRight(), new LDPoint(80, 80));
                TestUtil.COMPARE(quad22.getBottomLeft(), new LDPoint(50, 80));
            }
            {
                LDGridTransform grid = new LDGridTransform(20, 20, 60, 60, 3, 3);
                //行の幅を変更
                grid.setPoint(1, 0, new LDPoint(20, 35));
                grid.setPoint(1, 1, new LDPoint(40, 35));
                grid.setPoint(1, 2, new LDPoint(60, 35));
                grid.setPoint(1, 3, new LDPoint(80, 35));

                grid.setPoint(2, 0, new LDPoint(20, 50));
                grid.setPoint(2, 1, new LDPoint(40, 50));
                grid.setPoint(2, 2, new LDPoint(60, 50));
                grid.setPoint(2, 3, new LDPoint(80, 50));

                var outline = grid.getOutlineQuadTransform();

                TestUtil.COMPARE(outline.getTopLeft(), new LDPoint(20, 20));
                TestUtil.COMPARE(outline.getTopRight(), new LDPoint(80, 20));
                TestUtil.COMPARE(outline.getBottomRight(), new LDPoint(80, 80));
                TestUtil.COMPARE(outline.getBottomLeft(), new LDPoint(20, 80));

                //0行0列目(左上)の四角変形
                var quad00 = grid.getQuadTransform(0, 0);
                TestUtil.COMPARE(quad00.getTopLeft(), new LDPoint(20, 20));
                TestUtil.COMPARE(quad00.getTopRight(), new LDPoint(40, 20));
                TestUtil.COMPARE(quad00.getBottomRight(), new LDPoint(40, 35));
                TestUtil.COMPARE(quad00.getBottomLeft(), new LDPoint(20, 35));

                //1行1列目(中央)の四角変形
                var quad11 = grid.getQuadTransform(1, 1);
                TestUtil.COMPARE(quad11.getTopLeft(), new LDPoint(40, 35));
                TestUtil.COMPARE(quad11.getTopRight(), new LDPoint(60, 35));
                TestUtil.COMPARE(quad11.getBottomRight(), new LDPoint(60, 50));
                TestUtil.COMPARE(quad11.getBottomLeft(), new LDPoint(40, 50));

                //2行2列目(右下)の四角変形
                var quad22 = grid.getQuadTransform(2, 2);
                TestUtil.COMPARE(quad22.getTopLeft(), new LDPoint(60, 50));
                TestUtil.COMPARE(quad22.getTopRight(), new LDPoint(80, 50));
                TestUtil.COMPARE(quad22.getBottomRight(), new LDPoint(80, 80));
                TestUtil.COMPARE(quad22.getBottomLeft(), new LDPoint(60, 80));
            }
            {
                LDGridTransform grid = new LDGridTransform(20, 20, 60, 60, 3, 3);

                grid.setPoint(0, 1, new LDPoint(35, 25));
                grid.setPoint(1, 0, new LDPoint(10, 35));
                grid.setPoint(1, 1, new LDPoint(30, 40));

                //0行0列目(左上)の四角変形
                var quad00 = grid.getQuadTransform(0, 0);
                TestUtil.COMPARE(quad00.getTopLeft(), new LDPoint(20, 20));
                TestUtil.COMPARE(quad00.getTopRight(), new LDPoint(35, 25));
                TestUtil.COMPARE(quad00.getBottomRight(), new LDPoint(30, 40));
                TestUtil.COMPARE(quad00.getBottomLeft(), new LDPoint(10, 35));

                //1行1列目(中央)の四角変形
                var quad11 = grid.getQuadTransform(1, 1);
                TestUtil.COMPARE(quad11.getTopLeft(), new LDPoint(30, 40));
                TestUtil.COMPARE(quad11.getTopRight(), new LDPoint(60, 40));
                TestUtil.COMPARE(quad11.getBottomRight(), new LDPoint(60, 60));
                TestUtil.COMPARE(quad11.getBottomLeft(), new LDPoint(40, 60));


            }
        }

        public void hitTest()
        {
            LDGridTransform grid = new LDGridTransform(20, 20, 40, 40, 2, 2);

            TestUtil.VERIFY(!grid.isPreHit(new LDPoint(0, 0)));
            TestUtil.VERIFY(grid.isPreHit(new LDPoint(30, 30)));
            TestUtil.VERIFY(grid.isPreHit(new LDPoint(19, 19), 5));
            TestUtil.VERIFY(!grid.isHitOutline(new LDPoint(0, 0), 5));
            TestUtil.VERIFY(grid.isHitOutline(new LDPoint(21, 21), 5));
        }

        public void inverseTransformTest()
        {
            {
                LDGridTransform grid = new LDGridTransform(20, 20, 40, 40, 2, 2);
                LDPoint src = new LDPoint(30, 30);

                LDPoint dst = new LDPoint();

                dst = grid.inverseTransform(src);

                TestUtil.COMPARE(dst.x(), 0.25);
                TestUtil.COMPARE(dst.y(), 0.25);
            }

            {
                LDGridTransform grid = new LDGridTransform(20, 20, 40, 40, 2, 2);
                LDPointList src = new LDPointList();
                src.add(new LDPoint(30, 30)).add(new LDPoint(50, 50));

                LDPointList dst;

                dst = grid.inverseTransform(src);

                TestUtil.COMPARE(dst[0], new LDPoint(0.25f, 0.25f));
                TestUtil.COMPARE(dst[1], new LDPoint(0.75f, 0.75f));
            }
            /*
            {
                LDGridTransform grid = new LDGridTransform(20, 20, 40, 40, 2, 2);
                LDGridTransform src = new LDGridTransform(24, 24, 52 - 24, 52 - 24, 2, 2);

                LDGridTransform dst = src;

                var points = grid.inverseTransform(src.toForm());


                dst.setForm(points);
                LDFUZZY_COMPARE(dst.getPoint(0, 0).x(), 0.1f, 0.0000001f);
                LDFUZZY_COMPARE(dst.getPoint(2, 2).x(), 0.8f, 0.0000001f);
                LDFUZZY_COMPARE(dst.getPoint(2, 0).x(), 0.1f, 0.0000001f);
                LDFUZZY_COMPARE(dst.getPoint(2, 0).y(), 0.8f, 0.0000001f);
            }
            */
            {
                LDGridTransform grid = new LDGridTransform(20.53125f, 20.62423f, 40.614312f, 40.94645f, 2, 2);
                LDGridTransform src = new LDGridTransform(24.0134623f, 24.9143f, 52 - 24.090023f, 52 - 24.00001f, 2, 2);

                LDGridTransform dst = new LDGridTransform(src);

                var points = grid.inverseTransform(src.toForm());
                var rest = grid.transform(points);

                dst.setForm(points);
                TestUtil.VERIFY(LDMathUtil.fuzzyCompare(rest, src.toForm(), 0.0000001f));
            }
            {
                LDGridTransform grid=new LDGridTransform(2530.53125f, 2540.62423f, 4015.614312f, 4026.94645f, 2, 2);
                LDGridTransform src=new LDGridTransform(2594.0134623f, 2594.9143f, 5274 - 2594.090023f, 5276 - 2594.00001f, 2, 2);

                LDGridTransform dst = new LDGridTransform( src);

                var points = grid.inverseTransform(src.toForm());
                var rest = grid.transform(points);

                dst.setForm(points);
                TestUtil.VERIFY(LDMathUtil.fuzzyCompare(rest, src.toForm(), 0.0000001f));
            }
            {
                LDGridTransform grid=new LDGridTransform(
                           new LDPoint(20.53125f, 20.62423f)
                            , new LDPoint(40.53125f, 20.62423f)
                            , new LDPoint(45.53125f, 45.62423f)
                            , new LDPoint(20.614312f, 40.94645f), 2, 2);
                LDGridTransform src=new LDGridTransform(34.0134623f, 24.9143f, 52 - 24.090023f, 52 - 24.00001f, 8, 8);

                LDGridTransform dst = new LDGridTransform(src);

                var points = grid.inverseTransform(src.toForm());
                var rest = grid.transform(points);

                dst.setForm(points);
                TestUtil.VERIFY(LDMathUtil.fuzzyCompare(rest, src.toForm(), 0.0000001f));
            }
            {
                LDGridTransform grid=new LDGridTransform(
                            new LDPoint(2012.53125f, 2051.62423f)
                            , new LDPoint(4097.53125f, 2033.62423f)
                            , new LDPoint(4575.53125f, 4566.62423f)
                            , new LDPoint(2062.614312f, 4000.94645f), 2, 2);
                LDGridTransform src=new LDGridTransform(3444.0134623f, 2442.9143f, 5242 - 2412.090023f, 5211 - 2467.00001f, 8, 8);

                LDGridTransform dst = new LDGridTransform(src);

                var points = grid.inverseTransform(src.toForm());
                var rest = grid.transform(points);

                dst.setForm(points);
                TestUtil.VERIFY(LDMathUtil.fuzzyCompare(rest, src.toForm(), 0.0000001f));
            }
        }

        public void extendedTransformTest()
        {
            {
                //拡張したGridの取得
                LDGridTransform src=new LDGridTransform(20, 20, 40, 40, 3, 3);
                LDGridTransform dst = src.createExtendedGrid();

                TestUtil.COMPARE(dst.getRow(), 4);
                TestUtil.COMPARE(dst.getColumn(), 4);
                TestUtil.COMPARE(dst.getPoint(0, 0), new LDPoint(-20, -20));
                TestUtil.COMPARE(dst.getPoint(0, 1), new LDPoint(10, -20));
                TestUtil.COMPARE(dst.getPoint(0, 2), new LDPoint(40, -20));
                TestUtil.COMPARE(dst.getPoint(0, 3), new LDPoint(70, -20));
                TestUtil.COMPARE(dst.getPoint(0, 4), new LDPoint(100, -20));
                TestUtil.COMPARE(dst.getPoint(1, 1), new LDPoint(20, 20));
            }

            {
                //範囲外 順変換 クリッピング
                LDGridTransform grid=new LDGridTransform(20, 20, 40, 40, 1, 1);
                LDPoint src=new LDPoint(-1, -1);

                LDPoint dst;

                dst = grid.transform(src, true);

                TestUtil.COMPARE(dst.x(), 20.0);
                TestUtil.COMPARE(dst.y(), 20.0);
            }
            {
                //範囲外 順変換
                LDGridTransform grid=new LDGridTransform(20, 20, 40, 40, 1, 1);
                LDPoint src=new LDPoint(-1, -1);

                LDPoint dst;

                dst = grid.transform(src);

                TestUtil.COMPARE(dst.x(), -20.0);
                TestUtil.COMPARE(dst.y(), -20.0);
            }
            {
                //範囲外 順変換
                LDGridTransform grid=new LDGridTransform(20, 20, 40, 40, 1, 1);
                LDPoint src=new LDPoint(-10, -10);

                LDPoint dst;

                dst = grid.transform(src);

                TestUtil.COMPARE(dst.x(), -380.0);
                TestUtil.COMPARE(dst.y(), -380.0);
            }
            {
                //範囲外 逆変換 クリッピング
                LDGridTransform grid=new LDGridTransform(20, 20, 40, 40, 2, 2);
                LDPoint src=new LDPoint(-20, -20);

                LDPoint dst;

                dst = grid.inverseTransform(src, true);

                TestUtil.COMPARE(dst.x(), 0.0);
                TestUtil.COMPARE(dst.y(), 0.0);
            }
            {
                //範囲外 逆変換
                LDGridTransform grid=new LDGridTransform(20, 20, 40, 40, 2, 2);
                LDPoint src=new LDPoint(-20, -20);

                LDPoint dst;

                dst = grid.inverseTransform(src);

                TestUtil.COMPARE(dst.x(), -1.0);
                TestUtil.COMPARE(dst.y(), -1.0);
            }

            {
                LDGridTransform grid=new LDGridTransform(
                            new LDPoint(20.53125f, 20.62423f)
                            ,new  LDPoint(40.53125f, 20.62423f)
                            ,new  LDPoint(45.53125f, 45.62423f)
                            , new LDPoint(20.614312f, 40.94645f), 2, 2);
                LDGridTransform src=new LDGridTransform(3425.0134623f, 2412.9143f, 5252 - 2412.090023f, 5212 - 2451.00001f, 2, 8);

                LDGridTransform dst = src;

                var points = grid.inverseTransform(src.toForm());
                var rest = grid.transform(points);

                dst.setForm(points);
                TestUtil.VERIFY(LDMathUtil.fuzzyCompare(rest, src.toForm(), 0.0000001f));
            }
            {
                LDGridTransform grid=new LDGridTransform(
                            new LDPoint(2012.53125f, 2051.62423f)
                            , new LDPoint(4097.53125f, 2033.62423f)
                            , new LDPoint(4575.53125f, 4566.62423f)
                            , new LDPoint(2062.614312f, 4000.94645f), 2, 2);
                LDGridTransform src=new LDGridTransform(34.0134623f, 24.9143f, 52 - 24.090023f, 52 - 24.00001f, 8, 2);

                LDGridTransform dst = src;

                var points = grid.inverseTransform(src.toForm());
                var rest = grid.transform(points);

                dst.setForm(points);
                TestUtil.VERIFY(LDMathUtil.fuzzyCompare(rest, src.toForm(), 0.0000001f));
            }
        }
    }
}
