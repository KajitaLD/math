using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace live2d
{
    public class LDIndexLineListTest : ITest
    {
        public void test()
        {
            this.constructTest();
            this.hitTest();
        }

        /*
        public void serializeTest()
        {
            const char* name = "lineList";
            QSharedPointer<LDIndexLineList> src(new LDIndexLineList);
            src->push_back(LDIndexLine(0, 1));

            //シリアライズ
            SerializeHelper::writeBoostXml(name, src);

            //デシリアライズ
            auto dst = SerializeHelper::readBoostXml<LDIndexLineList>(name);

            QVERIFY(*(dst.data()) == *(src.data()));
        }
        */

        public void hitTest()
        {
            LDIndexLineList lines = new LDIndexLineList();
            LDIndexLine line_1 = new LDIndexLine(0, 1);
            LDIndexLine line_2 = new LDIndexLine(1, 2);
            LDIndexLine line_3 = new LDIndexLine(2, 3);
            LDIndexLine line_4 = new LDIndexLine(3, 0);
            lines.add(line_1);
            lines.add(line_2);
            lines.add(line_3);
            lines.add(line_4);

            LDPointList points = new LDPointList();
            points.Add(new LDPoint(0, 0));
            points.Add(new LDPoint(100, 0));
            points.Add(new LDPoint(100, 100));
            points.Add(new LDPoint(0, 100));


            TestUtil.COMPARE(lines.isHit(points, new LDPoint(0, 0), 1), true);//頂点上
            TestUtil.COMPARE(lines.isHit(points, new LDPoint(50, 0), 1), true);//線上
            TestUtil.COMPARE(lines.isHit(points, new LDPoint(50, 1), 3), true);//線からちょっと離れたところ
            TestUtil.COMPARE(lines.isHit(points, new LDPoint(50, 4), 3), false);//線から範囲外に離れたところ
            TestUtil.COMPARE(lines.isHit(points, new LDPoint(200, 0), 3), false);//線の延長戦上に離れたところ
            TestUtil.COMPARE(lines.isHit(points, new LDPoint(200, 1), 3), false);//線の延長戦上に離れたところ





        }

        public void constructTest()
        {
            List<int> int_list = new List<int>();
            int_list.Add(0);
            int_list.Add(1);
            int_list.Add(2);
            int_list.Add(3);
            //	int_list.push_back(0);
            LDIndexLineList list = new LDIndexLineList(int_list);

            LDIndexLineList compare = new LDIndexLineList();
            compare.Add(new LDIndexLine(0, 1));
            compare.Add(new LDIndexLine(1, 2));
            compare.Add(new LDIndexLine(2, 3));
            compare.Add(new LDIndexLine(3, 0));
            TestUtil.COMPARE(list, compare);
        }
    }
}
