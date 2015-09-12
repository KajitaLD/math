using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDPolygon : List<LDPoint>
    {
        public LDPolygon() { }
        public LDPolygon(int size) : base(size) { }
        public LDPolygon(LDPolygon a) : base(a) { }
        public LDPolygon(List<LDPoint> v) : base(v) { }
        public LDPolygon(LDRect r)
        {
            this.Add(r.topLeft());
            this.Add(r.topRight());
            this.Add(r.bottomRight());
            this.Add(r.bottomLeft());
        }
        public void swap(LDPolygon other) { throw new NotImplementedException(); }

        public int size()
        {
            return this.Count;
        }

        public void translate(float dx, float dy)
        {
            translate(new LDPoint(dx, dy));
        }

        public void translate(LDPoint offset)
        {
            foreach (var p in this)
            {
                p.setX(p.x() + offset.x());
                p.setX(p.y() + offset.y());
            }
        }

        public LDPolygon translated(float dx, float dy)
        {
            return translated(new LDPoint(dx, dy));
        }
        public LDPolygon translated(LDPoint offset)
        {
            LDPolygon translated = new LDPolygon();
            foreach (var p in this)
            {
                translated.Add(new LDPoint(p.x() + offset.x(), p.y() + offset.y()));
            }
            return translated;
        }

        public bool isClosed()
        {
            return !(isEmpty()) && first() == last();
        }

        public LDPoint first()
        {
            return this[0];
        }
        public LDPoint last()
        {
            return this[this.Count - 1];
        }

        public bool isEmpty()
        {
            return this.Count > 0 ? false : true;
        }


        public LDRect boundingRect()
        {
            if(this.Count == 0) { return new LDRect(0, 0, 0, 0); }

            LDRect boundingRect = new LDRect(this[0],this[0]);
            foreach (var p in this)
            {
                boundingRect.setBottom(Math.Max(p.y(), boundingRect.bottom()));
                boundingRect.setRight(Math.Max(p.x(), boundingRect.right()));
                boundingRect.setLeft(Math.Min(p.x(), boundingRect.left()));
                boundingRect.setTop(Math.Min(p.y(), boundingRect.top()));
            }
            return boundingRect;
        }

        public bool containsPoint(LDPoint pt, FillRule fillRule)
        {
            if (fillRule == FillRule.OddEvenFill)
            {
                int cn = 0;
                int k = this.isClosed() ? 2 : 1;
                for (int i = 0; i < this.Count - k; i++)
                {
                    // 上向きの辺。点Pがy軸方向について、始点と終点の間にある。ただし、終点は含まない。(ルール1)
                    if (((this[i].y() <= pt.y()) && (this[i + 1].y() > pt.y()))
                        // 下向きの辺。点Pがy軸方向について、始点と終点の間にある。ただし、始点は含まない。(ルール2)
                        || ((this[i].y() > pt.y()) && (this[i + 1].y() <= pt.y())))
                    {
                        // ルール1,ルール2を確認することで、ルール3も確認できている。

                        // 辺は点pよりも右側にある。ただし、重ならない。(ルール4)
                        // 辺が点pと同じ高さになる位置を特定し、その時のxの値と点pのxの値を比較する。
                        var vt = (pt.y() - this[i].y()) / (this[i + 1].y() - this[i].y());
                        if (pt.x() < (this[i].x() + (vt * (this[i + 1].x() - this[i].x()))))
                        {
                            ++cn;
                        }
                    }
                }
                return cn % 2 == 0 ? false : true;
            }
            else
            {
                int wn = 0;
                int k = this.isClosed() ? 2 : 1;
                for (int i = 0; i < this.Count - k; i++)
                {
                    // 上向きの辺、下向きの辺によって処理が分かれる。
                    // 上向きの辺。点Pがy軸方向について、始点と終点の間にある。ただし、終点は含まない。(ルール1)
                    if ((this[i].y() <= pt.y()) && (this[i + 1].y() > pt.y()))
                    {
                        // 辺は点pよりも右側にある。ただし、重ならない。(ルール4)
                        // 辺が点pと同じ高さになる位置を特定し、その時のxの値と点pのxの値を比較する。
                        var vt = (pt.y() - this[i].y()) / (this[i + 1].y() - this[i].y());
                        if (pt.x() < (this[i].x() + (vt * (this[i + 1].x() - this[i].x()))))
                        {

                            ++wn;  //ここが重要。上向きの辺と交差した場合は+1

                        }
                    }
                    // 下向きの辺。点Pがy軸方向について、始点と終点の間にある。ただし、始点は含まない。(ルール2)
                    else if ((this[i].y() > pt.y()) && (this[i + 1].y() <= pt.y()))
                    {
                        // 辺は点pよりも右側にある。ただし、重ならない。(ルール4)
                        // 辺が点pと同じ高さになる位置を特定し、その時のxの値と点pのxの値を比較する。
                        var vt = (pt.y() - this[i].y()) / (this[i + 1].y() - this[i].y());
                        if (pt.x() < (this[i].x() + (vt * (this[i + 1].x() - this[i].x()))))
                        {

                            --wn;  //ここが重要。下向きの辺と交差した場合は-1

                        }
                    }
                    // ルール1,ルール2を確認することで、ルール3も確認できている。
                }
                return wn == 0 ? false : true;
            }

        }

        /// <summary>
        /// 未実装
        /// </summary>
        /// <param name="r"></param>
        /// <returns></returns>
        public LDPolygon united(LDPolygon r)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// 未実装
        /// </summary>
        /// <param name="r"></param>
        /// <returns></returns>
        public LDPolygon intersected(LDPolygon r)
        {
            throw new NotImplementedException();
        }
        
        /// <summary>
        /// 未実装
        /// </summary>
        /// <param name="r"></param>
        /// <returns></returns>
        public LDPolygon subtracted(LDPolygon r)
        {
            throw new NotImplementedException();
        }

        //operator QVariant();
    }
}
