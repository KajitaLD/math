using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace live2d
{
    namespace math
    {
        using ld_float = System.Single;
        public class PointUtil
        {

            //2点が一定差以内(d以下)にあるかどうか。

            public static bool isNearSimple(LDPoint a, LDPoint b, float d)
            {
                if (Math.Abs(a.x() - b.x()) > d) return false;
                if (Math.Abs(a.y() - b.y()) > d) return false;

                return true;
            }

            //与えられた点群すべてを含む矩形を取得
            public static LDRect getBoundingRect(LDPointList form)
            {
                float maxX = float.MinValue;
                float minX = float.MaxValue;
                float maxY = float.MinValue;
                float minY = float.MaxValue;
                foreach (var p in form)
                {
                    float x = p.x();
                    float y = p.y();
                    if (x < minX)
                    {
                        minX = x;    //  最小のx
                    }
                    if (x > maxX)
                    {
                        maxX = x;    //  最大のx
                    }
                    if (y < minY)
                    {
                        minY = y;    //  最小のy
                    }
                    if (y > maxY)
                    {
                        maxY = y;    //  最大のy
                    }
                }

                LDRect rect = new LDRect();
                rect.setLeft(minX);
                rect.setRight(maxX);
                rect.setTop(minY);
                rect.setBottom(maxY);
                return rect;
            }

            //文字列にする
            public static String toString(LDPoint p)
            {
                return "Point (" + p.x() + "," + p.y() + ")";
            }

            public static bool isHit(LDPoint pt, LDPoint target, float hitRange)
            {
                return (new LDVector2(pt).distanceToPoint(new LDVector2(target)) <= hitRange);
            }

            public static float distance(LDPoint a, LDPoint b)
            {
                return new LDVector2(a).distanceToPoint(new LDVector2(b));
            }

            //yが最小の点を探す。複数あるならxが低い方
            public static int findMinYPointIndex(LDPointList points)
            {

                if (points.length() == 0)
                {
                    return -1;
                }
                int length = points.length();

                double minY = points[0].y();
                for (int i = 0; i < length; ++i)
                {
                    if (points[i].y() < minY)
                    {
                        minY = points[i].y();
                    }
                }

                List<int> minYList = new List<int>();
                for (int i = 0; i < length; ++i)
                {
                    if (points[i].y() == minY)
                    {
                        minYList.Add(i);
                    }
                }

                Debug.Assert(minYList.Count != 0);

                if (minYList.Count == 1)
                {
                    return minYList[0];
                }

                float minX = points[minYList[0]].x();
                int minXIndex = minYList[0];
                for (int i = 0; i < minYList.Count; ++i)
                {
                    int index = minYList[i];
                    if (points[index].x() < minX)
                    {
                        minXIndex = index;
                    }
                }

                return minXIndex;
            }

            public static LDPoint interporate(LDPoint p1, LDPoint p2, ld_float factor)
            {
                var d = (p2 - p1) * factor;
                return p1 + d;
            }

            private PointUtil() { }

        }
    }
}
