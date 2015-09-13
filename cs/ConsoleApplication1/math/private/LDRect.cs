using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDRect
    {
        private float xp;
        private float yp;
        private float w;
        private float h;

        public LDRect() { this.xp = 0; this.yp = 0; this.w = 0; this.h = 0; }
        public LDRect(LDPoint topleft, LDSize size)
        {
            this.xp = topleft.x();
            this.yp = topleft.y();
            this.w = size.width();
            this.h = size.height();
        }
        public LDRect(LDPoint topleft, LDPoint bottomRight)
        {
            this.xp = topleft.x();
            this.yp = topleft.y();
            this.w = bottomRight.x() - topleft.x();
            this.h = bottomRight.y() - topleft.y();
        }
        public LDRect(float left, float top, float width, float height)
        {
            this.xp = left;
            this.yp = top;
            this.w = width;
            this.h = height;
        }
        public LDRect(LDRect rect)
        {
            this.xp = rect.xp;
            this.yp = rect.yp;
            this.w = rect.w;
            this.h = rect.h;
        }

        public bool isNull()
        {
            return w == 0 && h == 0;
        }
        public bool isEmpty()
        {
            return w <= 0 || h <= 0;
        }
        public bool isValid()
        {
            return w > 0 && h > 0;
        }
        public LDRect normalized()
        {
            LDRect normalized = new LDRect(this);
            if (normalized.w < 0)
            {
                normalized.xp = this.right();
                normalized.w *= -1;
            }
            if (normalized.h < 0)
            {
                normalized.yp = this.bottom();
                normalized.h *= -1;
            }
            return normalized;
        }
        public float left() { return xp; }
        public float top() { return yp; }
        public float right() { return xp + w; }
        public float bottom() { return yp + h; }

        public float x() { return xp; }
        public float y() { return yp; }
        public void setLeft(float pos)
        {
            float diff = pos - this.xp; this.xp += diff; this.w -= diff;
        }
        public void setTop(float pos)
        {
            float diff = pos - this.yp; this.yp += diff; this.h -= diff;
        }
        public void setRight(float pos)
        {
            this.w = pos - this.xp;
        }
        public void setBottom(float pos)
        {
            this.h = pos - yp;
        }
        public void setX(float pos) { setLeft(pos); }
        public void setY(float pos) { setTop(pos); }

        public LDPoint topLeft() { return new LDPoint(this.xp, this.yp); }
        public LDPoint bottomRight() { return new LDPoint(this.xp + w, this.yp + h); }
        public LDPoint topRight() { return new LDPoint(this.xp + w, this.yp); }
        public LDPoint bottomLeft() { return new LDPoint(this.xp, this.yp + h); }
        public LDPoint center()
        {
            return new LDPoint(this.xp + this.w / 2, this.yp + this.h / 2);
        }
        public void setTopLeft(LDPoint p) { setLeft(p.x()); setTop(p.y()); }
        public void setBottomRight(LDPoint p) { setRight(p.x()); setTop(p.y()); }
        public void setTopRight(LDPoint p) { setLeft(p.x()); setBottom(p.y()); }
        public void setBottomLeft(LDPoint p) { setRight(p.x()); setBottom(p.y()); }

        public void moveLeft(float pos) { xp = pos; }
        public void moveTop(float pos) { yp = pos; }
        public void moveRight(float pos) { xp = pos - w; }
        public void moveBottom(float pos) { yp = pos - h; }
        public void moveTopLeft(LDPoint p) { moveLeft(p.x()); moveTop(p.y()); }
        public void moveTopRight(LDPoint p) { moveRight(p.x()); moveTop(p.y()); }
        public void moveBottomLeft(LDPoint p) { moveLeft(p.x()); moveBottom(p.y()); }
        public void moveBottomRight(LDPoint p) { moveRight(p.x()); moveBottom(p.y()); }
        public void moveCenter(LDPoint p) { xp = p.x() - w / 2; yp = p.y() - h / 2; }

        public void translate(float dx, float dy)
        {
            this.xp += dx;
            this.yp += dy;
        }
        public void translate(LDPoint p)
        {
            this.xp += p.x();
            this.yp += p.y();
        }

        public LDRect translated(float dx, float dy) { return new LDRect(xp + dx, yp + dy, w, h); }
        public LDRect translated(LDPoint p) { return new LDRect(xp + p.x(), yp + p.y(), w, h); }

        public void moveTo(float x, float y)
        {
            this.xp = x;
            this.yp = y;
        }
        public void moveTo(LDPoint p)
        {
            this.xp = p.x();
            this.yp = p.y();
        }

        public void setRect(float x, float y, float w, float h)
        {
            this.xp = x;
            this.yp = y;
            this.w = w;
            this.h = h;
        }
        public void getRect(out float x, out float y, out float w, out float h)
        {
            x = this.xp;
            y = this.yp;
            w = this.w;
            h = this.h;
        }

        public void setCoords(float x1, float y1, float x2, float y2)
        {
            this.xp = x1;
            this.yp = y1;
            this.w = x2 - x1;
            this.h = y2 - y1;
        }
        public void getCoords(out float x1, out float y1, out float x2, out float y2)
        {
            x1 = this.xp;
            y1 = this.yp;
            x2 = this.xp + this.w;
            y2 = this.yp + this.h;
        }

        public void adjust(float x1, float y1, float x2, float y2)
        {
            this.xp += x1;
            this.yp += y1;
            this.w += x2 - x1;
            this.h += y2 - y1;
        }
        public LDRect adjusted(float x1, float y1, float x2, float y2)
        {
            return new LDRect(this.xp + x1, this.yp + y1, this.w + x2 - x1, this.h + y2 - y1);
        }

        public LDSize size() { return new LDSize(this.w, this.h); }
        public float width() { return this.w; }
        public float height() { return this.h; }
        public void setWidth(float w) { this.w = w; }
        public void setHeight(float h) { this.h = h; }
        public void setSize(LDSize s)
        {
            this.w = s.width();
            this.h = s.height();
        }

        public static LDRect operator |(LDRect a, LDRect b)
        {
            return new LDRect(a.united(b));
        }
        public static LDRect operator &(LDRect a, LDRect b)
        {
            return new LDRect(a.intersected(b));
        }

        public bool contains(LDRect r)
        {
            return this.contains(r.topLeft()) && this.contains(r.topRight()) && this.contains(r.bottomLeft()) && this.contains(r.bottomRight());

        }
        public bool contains(LDPoint p)
        {
            var a = this.normalized();
            return a.left() <= p.x() && a.right() >= p.x() && a.top() <= p.y() && a.bottom() >= p.y();
        }

        public bool contains(float x, float y) { return this.contains(new LDPoint(x, y)); }

        public LDRect united(LDRect other)
        {
            LDRect a = this.normalized();
            LDRect b = other.normalized();

            LDRect intersected = new LDRect(0, 0, 0, 0);
            intersected.setTop(Math.Min(a.top(), b.top()));
            intersected.setBottom(Math.Max(a.bottom(), b.bottom()));
            intersected.setLeft(Math.Min(a.left(), b.left()));
            intersected.setRight(Math.Max(a.right(), b.right()));
            return intersected;
        }

        public LDRect intersected(LDRect other)
        {
            LDRect a = this.normalized();
            LDRect b = other.normalized();

            LDRect intersected = new LDRect(0, 0, 0, 0);
            intersected.setTop(Math.Max(a.top(), b.top()));
            intersected.setBottom(Math.Min(a.bottom(), b.bottom()));
            intersected.setLeft(Math.Max(a.left(), b.left()));
            intersected.setRight(Math.Min(a.right(), b.right()));
            return intersected;
        }


        public bool intersects(LDRect r)
        {
            return this.intersected(r).isValid();
        }

        public LDRect marginsAdded(LDMargins margins)
        {
            return new LDRect(new LDPoint(xp - margins.left(), yp - margins.top()),
                  new LDSize(w + margins.left() + margins.right(), h + margins.top() + margins.bottom()));
        }
        public LDRect marginsRemoved(LDMargins margins)
        {
            return new LDRect(new LDPoint(xp + margins.left(), yp + margins.top()),
                  new LDSize(w - margins.left() - margins.right(), h - margins.top() - margins.bottom()));
        }

        public static LDRect operator +(LDRect a, LDMargins margins)
        {
            return a.marginsAdded(margins);
        }
        public static LDRect operator -(LDRect a, LDMargins margins)
        {
            return a.marginsRemoved(margins);
        }

        public static bool operator ==(LDRect r1, LDRect r2)
        {
            return MathFunctions.uFuzzyCompare(r1.xp, r2.xp) && MathFunctions.uFuzzyCompare(r1.yp, r2.yp)
           && MathFunctions.uFuzzyCompare(r1.w, r2.w) && MathFunctions.uFuzzyCompare(r1.h, r2.h);
        }
        public static bool operator !=(LDRect r1, LDRect r2)
        {
            return !MathFunctions.uFuzzyCompare(r1.xp, r2.xp) || !MathFunctions.uFuzzyCompare(r1.yp, r2.yp)
           || !MathFunctions.uFuzzyCompare(r1.w, r2.w) || !MathFunctions.uFuzzyCompare(r1.h, r2.h);
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;
            if (obj.GetType() != this.GetType()) return false;
            var p = obj as LDRect;
            return this == p;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }
}
