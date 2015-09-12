using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace live2d
{
    public class LDIndexLineList : List<LDIndexLine>, IComparer<LDIndexLine>
    {
        public LDIndexLineList() { }
        public int size()
        {
            return this.Count;
        }
        public int length()
        {
            return this.Count;
        }

        public LDIndexLine at(int index)
        {
            return this[index];
        }
        public LDIndexLineList(List<int> indices)
        {
            Debug.Assert(indices.Count > 2);

            for (int i = 0; i < indices.Count - 1; ++i)
            {
                LDIndexLine line = new LDIndexLine(indices[i], indices[i + 1]);
                this.Add(line);
            }
            LDIndexLine last = new LDIndexLine(indices.ElementAt(indices.Count - 1), indices.ElementAt(indices.Count - 1));
            this.Add(last);
        }

        public bool hasIndexLine(LDIndexLine line)
        {
            for (int i = 0; i < this.size(); i++)
            {
                if (line == this.at(i))//NOTE this->at(i) ==line だとコンパイルエラー
                    return true;
            }
            return false;
        }
        public void sort()
        {
            this.Sort(this.Compare);
        }
        public bool isHit(LDPointList form, LDPoint p, float hitRange)
        {
            for (int i = 0; i < this.size(); i++)
            {
                if (this.at(i).isHit(form, p, hitRange))
                {
                    return true;
                }
            }
            return false;
        }
        public void replace(int index, LDIndexLine item)
        {
            this[index] = item;
        }
        public LDLineList getLines(LDPointList points)
        {
            LDLineList result = new LDLineList();

            for (int i = 0; i < size(); i++)
            {
                int index1 = this.at(i).getIndex1();
                int index2 = this.at(i).getIndex2();
                LDPoint point1 = points.at(index1);
                LDPoint point2 = points.at(index2);
                result.Add(new LDLine(point1, point2));
            }
            return result;
        }

        private bool letssThan(LDIndexLine e1, LDIndexLine e2)
        {
            if (e1.getIndex1() < e2.getIndex1())
                return true;
            if (e1.getIndex1() == e2.getIndex1())
                if (e1.getIndex2() < e2.getIndex2())
                    return true;
            return false;
        }

        public int Compare(LDIndexLine e1, LDIndexLine e2)
        {
            if (e1.getIndex1() < e2.getIndex1())
                return 1;
            if (e1.getIndex1() == e2.getIndex1())
                if (e1.getIndex2() < e2.getIndex2())
                    return 1;
            return -1;
        }
        //LD_SERIALIZABLE;
    }
}
