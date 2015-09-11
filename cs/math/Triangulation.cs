using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace live2d.math
{
    public class Triangulation
    {
        public static LDTriangleList exec(LDPointList form)//TODO ,LDProgress progress
        {
            //Debug.Assert(form.length() == form.toList().toSet().size());

            LDTriangleList result = new LDTriangleList();
            int formSize = form.size();

            if (formSize < 2)
            {
                return result;
            }

            //A1) 点群を包含する十分大きな三角形(super triangle)を追加する
            LDPolygon hugeTriangle = TriangleUtil.getHugeTriangle(form);

            int index1 = form.length();
            int index2 = index1 + 1;
            int index3 = index2 + 1;

            form.Add(hugeTriangle[0]);
            form.Add(hugeTriangle[1]);
            form.Add(hugeTriangle[2]);

            LDTriangle t = new LDTriangle(index1, index2, index3);
            result.Add(t);

            //A2) i番目の頂点piを三角形分割図形に追加

            for (int i = 0; i < formSize; i++)
            {
                LDPoint pi = form[i];

                //  A2-1) 	piを含む三角形ABCを発見し, この三角形をAB pi, BC pi, CA pi の3個の三角形に分割．
                triangulationFromPoint(form, pi, result);
            }

            // 最後に、外部三角形の頂点を削除
            result.removePoint(index1);
            result.removePoint(index2);
            result.removePoint(index3);


            return result;
        }                                                    //	static LDTriangleList exec(LDPointList form,LDIndexLineList limitedLines);//TODO ,LDProgress progress


        private static void triangulationFromPoint(LDPointList form, LDPoint p, LDTriangleList triangles)
        {
            //  A2-1) 	piを含む三角形ABCを発見し, この三角形をAB pi, BC pi, CA pi の3個の三角形に分割．
            //  		この時, 辺AB, BC, CAをスタックSに積む (最初の一点のときには，super triangleが見つかる)
            for (int i = 0; i < triangles.length();)
            {
                LDTriangle t = triangles[i];

                if (!TriangleUtil.containsPoint(t.toPolygon(form), p))
                {
                    //対象の三角形の外側なら次へ
                    i++;
                    continue;
                }

                // 古い三角形をリストから削除して、分割した三角形を追加
                triangles.RemoveAll(item => item == t);

                int index = form.IndexOf(p);
                Debug.Assert(index >= 0);
                triangles.Add(new LDTriangle(index, t.getIndex1(), t.getIndex2()));
                triangles.Add(new LDTriangle(index, t.getIndex2(), t.getIndex3()));
                triangles.Add(new LDTriangle(index, t.getIndex3(), t.getIndex1()));

                //TODO すでにある線分で制限する機能が未移植
                //		if ( limitLineList.size() != 0 )
                //		{
                //			flipCheckWithLimit( t.p1, t.p2, t.p3 , pg );
                //		}
                //		else
                //		{
                optimizePolygonSeparate(form, t, triangles);
                //		}

            }
        }

        //特定の三角形から始めて、周辺の四角形をフリップすることで分割形状を最適化する。
        private static void optimizePolygonSeparate(LDPointList form, LDTriangle firstTriangle, LDTriangleList triangles)
        {
            LDIndexLineList uncheckedLines = new LDIndexLineList();
            uncheckedLines.Add(firstTriangle.getLine1());
            uncheckedLines.Add(firstTriangle.getLine2());
            uncheckedLines.Add(firstTriangle.getLine3());

            //A2-2) スタックSが空になるまで以下を繰り返す
            while (uncheckedLines.size() != 0)
            {
                //A2-2-1) スタックSの一番上のedgeをpopする．これを辺ABとする
                LDIndexLine lineAB = uncheckedLines.Last();

                //線と接する2つの三角形を取得
                LDTriangleList relatedTriangles = triangles.find(lineAB);

                //外周はチェックしない
                if (relatedTriangles.size() == 1)
                    continue;

                //三角形がダブってるのは不正。隣接0もなにかおかしい
                Debug.Assert(relatedTriangles.size() == 2);

                //A2-2-2) 辺ABを含む2個の三角形をABCとABDとする
                // if(三角形ABCの外接円内にDが入 る) 辺ABをflipし，辺AD/DB/BC/CAをスタックSにpushする
                //else 何もしない
                LDTriangle triangleABC = relatedTriangles.at(0);
                LDTriangle triangleABD = relatedTriangles.at(1);

                int index = triangleABD.getIndexWithoutLine(lineAB);
                Debug.Assert(form.length() > index);
                LDPoint pd = form[index];

                // 外接円を求める
                LDCircle c = LDCircle.getCircumscribedCirclesOfTriangle(form, triangleABC);
                double dist = PointUtil.distance(c.center, pd);

                //誤差の範囲ならフリップしない
                if (dist < c.radius && Math.Abs(c.radius - dist) > 0.00001)
                {
                    //不正な辺
                    uncheckedLines.AddRange(flipTriangles(triangleABC, triangleABD, lineAB, triangles));
                }
            }
        }

        //四角形のポリゴン割りをフリップ(割り方を変更)。アルゴリズムのための未チェックの線分を返す
        private static LDIndexLineList flipTriangles(LDTriangle ta, LDTriangle tb, LDIndexLine l, LDTriangleList triangles)
        {
            Debug.Assert(!(ta == tb));
            Debug.Assert(ta.isSharedLine(tb));

            LDIndexLineList uncheckedLines=new LDIndexLineList();

            //指定の線で繋がっていない点を取得
            int index1 = ta.getIndexWithoutLine(l);
            int index2 = tb.getIndexWithoutLine(l);

            LDTriangle tc=new LDTriangle(index1, index2, l.getIndex1());
            LDTriangle td = new LDTriangle(index1, index2, l.getIndex2());

            triangles.RemoveAll(triangle => triangle == ta);
            triangles.RemoveAll(triangle => triangle == tb);
            triangles.Add(tc);
            triangles.Add(td);

            uncheckedLines.Add(new LDIndexLine(index1, l.getIndex1()));
            uncheckedLines.Add(new LDIndexLine(index2, l.getIndex1()));
            uncheckedLines.Add(new LDIndexLine(index1, l.getIndex2()));
            uncheckedLines.Add(new LDIndexLine(index2, l.getIndex2()));

            return uncheckedLines;
        }

        private static uint qHash(LDPoint key)
        {
            return (uint)key.x().GetHashCode();//適当。xだけでハッシュ
        }
    }
}
