using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace live2d
{
    public class LDTriangleList : List<LDTriangle>,IComparable
    {
        public LDTriangleList() { }

        //すべての線分から三角形を再構成
        public void update(LDIndexLineList lines)
        {
            this.Clear();
            for (int i = 0; i < lines.size(); i++)
            {
                this.AddRange(create(i, lines));
            }
        }

        public int size()
        {
            return this.Count;
        }
        public int length()
        {
            return this.Count;
        }
        public LDTriangle at(int i)
        {
            return this[i];
        }

        public void setClockWise(LDPointList form, ClockWise cw)
        {
            for (int i = 0; i < size(); i++)
            {
                this[i].setClockWise(form, cw);
            }
        }
        public LDTriangleList find(LDIndexLine line)
        {
            LDTriangleList result = new LDTriangleList();
            foreach (var t in this)
            {
                if (t.containsLine(line))
                {
                    result.Add(t);
                }
            }
            return result;
        }

        public LDIndexLineList toIndexLineList()
        {
            //NOTE: もっと効率化できる気がするが、ボトルネックになったらやる
            LDIndexLineList lineList = new LDIndexLineList();
            for (int i = 0; i < this.size(); i++)
            {
                LDTriangle tri = this.at(i);

                LDIndexLine line1 = tri.getLine1();
                if (!lineList.hasIndexLine(line1))
                {
                    lineList.Add(line1);
                }

                LDIndexLine line2 = tri.getLine2();
                if (!lineList.hasIndexLine(line2))
                {
                    lineList.Add(line2);
                }

                LDIndexLine line3 = tri.getLine3();
                if (!lineList.hasIndexLine(line3))
                {
                    lineList.Add(line3);
                }


            }
            return lineList;

        }
        //頂点のインデックスから関連する三角形を削除
        public void removePoint(int pointIndex)
        {
            for (int i = 0; i < length();)
            {
                var t = at(i);
                if (t.hasIndex(pointIndex))
                {
                    this.RemoveAll(num => num ==t);
                }
                else
                {
                    i++;
                }
            }
        }

        //外周の頂点インデックスを取得。yが一番小さい点から時計周りで取得。
        public List<int> getOutlinePointIndices(LDPointList points)
        {
            List<int> result = new List<int>();

            // 外周をたどる。始点に戻ったら終了。
            int startIndex = math.PointUtil.findMinYPointIndex(points);

            Debug.Assert(startIndex >= 0);

            result.Add(startIndex);

            int lastIndex = -1;
            int currentIndex = startIndex;

            for (int i = 0; i < points.length(); ++i)
            {
                //現在の頂点と接続される点一覧を取得し、その中から進行方向に対してもっとも左側に位置するものを取得
                List<int> related = getRelatedPointIndices(currentIndex);

                LDPoint lastPoint;
                LDPoint currentPoint = points[currentIndex];
                if (lastIndex == -1)
                {
                    lastPoint = currentPoint - new LDPoint(0, 1);
                }
                else
                {
                    lastPoint = points[lastIndex];
                }


                int nextIndex = -1;
                double minAngle = 360;
                foreach (var targetIndex in related)
                {
                    LDPoint targetPoint = points[targetIndex];
                    if (targetIndex == lastIndex)
                    {
                        continue;
                    }
                    LDVector2 v1 = new LDVector2(lastPoint - currentPoint);
                    LDVector2 v2 = new LDVector2(targetPoint - currentPoint);

                    double angle = LDMathUtil.getAngle(v2, v1);
                    if (angle < minAngle)
                    {
                        minAngle = angle;
                        nextIndex = targetIndex;
                    }
                }

                if (nextIndex == startIndex)
                {
                    //一周した
                    break;
                }
                result.Add(nextIndex);

                lastIndex = currentIndex;
                currentIndex = nextIndex;
            }

            return result;
        }

        public LDPointList getOutlinePoints(LDPointList points)
        {
            List<int> indices = getOutlinePointIndices(points);

            LDPointList result = new LDPointList();

            foreach (var index in indices)
            {
                common.LD_ASSERT_OUT_OF_INDEX(points, index);
                result.Add(points[index]);
            }
            return result;
        }
        public LDPolygon getOutlinePolygon(LDPointList points)
        {
            List<int> indices = getOutlinePointIndices(points);

            LDPolygon result = new LDPolygon();

            foreach (var index in indices)
            {
                common.LD_ASSERT_OUT_OF_INDEX(points, index);
                result.Add(points[index]);
            }
            return result;
        }

        //その頂点を含む三角形リストを取得
        public LDTriangleList getRelatedTriangles(int pointIndex)
        {
            LDTriangleList result = new LDTriangleList();

            foreach (var t in this)
            {
                if (t.hasIndex(pointIndex))
                {
                    result.Add(t);
                }
            }

            return result;
        }
        //その頂点を含む線分リストを取得
        public LDIndexLineList getRelatedLines(int pointIndex)
        {
            LDIndexLineList result = new LDIndexLineList();

            foreach (var t in this)
            {
                LDIndexLineList lines = t.getRelatedLines(pointIndex);

                foreach (var line in lines)
                {
                    result.Add(line);
                }
            }

            return result;
        }
        //その頂点と接続される点のリストを取得
        public List<int> getRelatedPointIndices(int pointIndex)
        {
            List<int> result=new List<int>();

            foreach (var t in this)
            {
                if (t.hasIndex(pointIndex))
                {
                    int index1 = t.getIndex1();
                    int index2 = t.getIndex2();
                    int index3 = t.getIndex3();
                    if (index1 != pointIndex)
                    {
                        result.Add(index1);
                    }
                    if (index2 != pointIndex)
                    {
                        result.Add(index2);
                    }
                    if (index3 != pointIndex)
                    {
                        result.Add(index3);
                    }
                }
            }

            return result;
        }

        public LDLineList getLines(LDPointList points)
        {
            return toIndexLineList().getLines(points);
        }

        //特定の線分から隣接する三角形を作成
        private List<LDTriangle> create(int index, LDIndexLineList lines)
        {
            Debug.Assert(lines.length() > index);

            List<LDTriangle> indexs = new List<LDTriangle>();
            int i_1 = lines.at(index).getIndex1();
            int i_2 = lines.at(index).getIndex2();


            for (int i = index; ; i++)
            {
                if (i > lines.size() - 1)
                {
                    break;
                }
                if (lines.at(i).getIndex1() != i_1)
                {
                    break;
                }
                int i_3 = lines.at(i).getIndex2();
                bool hit = false;
                for (int j = i; j < lines.size(); j++)
                {
                    if (lines.at(j).getIndex1() == i_2 && lines.at(j).getIndex2() == i_3)
                    {
                        hit = true;
                        break;
                    }
                }
                if (hit)
                {
                    LDTriangle poly = new LDTriangle(i_1, i_2, i_3);
                    indexs.Add(poly);
                }
            }
            return indexs;
        }

        public int CompareTo(object obj)
        {
            if (obj.GetType() != this.GetType()) return -1;
            var p =  obj as LDTriangleList;
            if(p.Count == this.Count)
            {
                for(int i =0; i< this.Count; i++)
                {
                    if(p[i] != this[i])
                    {
                        return -1;
                    }
                }
                return 0;
            }
            else
            {
                return -1;
            }
        }
    }
}
