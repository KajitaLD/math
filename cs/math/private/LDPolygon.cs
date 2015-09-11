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
        public void swap(LDPolygon other) { throw new NotImplementedException(); } // prevent QVector<LDPoint><->LDPolygon swaps

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
            throw new NotImplementedException();
        }

        public LDPolygon translated(float dx, float dy)
        {
            return translated(new LDPoint(dx, dy));
        }
        public LDPolygon translated(LDPoint offset)
        {
            throw new NotImplementedException();
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
            throw new NotImplementedException();
        }

        public bool containsPoint(LDPoint pt, FillRule fillRule)
        {
            throw new NotImplementedException();
        }

        public LDPolygon united(LDPolygon r)
        {
            throw new NotImplementedException();
        }
        public LDPolygon intersected(LDPolygon r)
        {
            throw new NotImplementedException();
        }
        public LDPolygon subtracted(LDPolygon r)
        {
            throw new NotImplementedException();
        }

        //operator QVariant();
    }
}
