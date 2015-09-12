using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDSimpleAffineTransform
    {
        public LDSimpleAffineTransform()
        {
            originX = 0;
            originY = 0;
            scale = 1;
            rotate = 0;
        }

        public float transform(float p)
        {
            LDPoint tmp = transform(new LDPoint(p, 0));
            return tmp.x();
        }
        public LDPoint transform(LDPoint p)
        {
            float rx = p.x() * (float)Math.Cos(rotate) - p.y() * (float)Math.Sin(rotate);
            float ry = p.x() * (float)Math.Sin(rotate) + p.y() * (float)Math.Cos(rotate);

            float x = rx * scale + originX;
            float y = ry * scale + originY;

            return new LDPoint(x, y);
        }
        public LDPointList transform(LDPointList form)
        {
            LDPointList result= new LDPointList();
            foreach (var pt in form) {
                result.Add(transform(pt));
            }

            return result;
        }

        public LDPoint inverseTransform(LDPoint pt)
        {
            float sx = (pt.x() - originX) / scale;
            float sy = (pt.y() - originY) / scale;

            float rx = sx * (float)Math.Cos(-rotate) - sy * (float)Math.Sin(-rotate);
            float ry = sx * (float)Math.Sin(-rotate) + sy * (float)Math.Cos(-rotate);

            return new LDPoint(rx, ry);
        }
        public LDPointList inverseTransform(LDPointList points)
        {
            LDPointList result= new LDPointList();
            foreach (var pt in points) {
                result.Add(inverseTransform(pt));
            }

            return result;
        }


        public float getScale()
        {
            return scale;
        }
        public void setScale(float value)
        {
            scale = value;
        }

        public float getRotate()
        {
            return rotate;
        }
        public void setRotate(float value)
        {
            rotate = value;
        }

        public float getRotateDeg()
        {
            return rotate / LDMathUtil.PI * 180.0f;
        }
        public void setRotateDeg(float value)
        {
            rotate = value / 180.0f * LDMathUtil.PI;
        }

        public LDPoint getOrigin()
        {
            return new LDPoint(originX, originY);
        }

        public void setOrigin(LDPoint value)
        {
            originX = value.x();
            originY = value.y();
        }

        public float getOriginX()
        {
            return originX;
        }
        public void setOriginX(float value)
        {
            originX = value;
        }

        public float getOriginY()
        {
            return originY;
        }
        public void setOriginY(float value)
        {
            originY = value;
        }


        private float originX;
        private float originY;
        private float scale;
        private float rotate;//ラジアン。範囲なしで、ｎ回転を表現できる。

        //LD_SERIALIZABLE;

        public static bool operator ==(LDSimpleAffineTransform a, LDSimpleAffineTransform b)
        {
            if (a.getOriginX() != b.getOriginX()) return false;
            if (a.getOriginY() != b.getOriginY()) return false;
            if (a.getScale() != b.getScale()) return false;
            if (a.getRotateDeg() != b.getRotateDeg()) return false;
            return true;
        }
        public static bool operator !=(LDSimpleAffineTransform a, LDSimpleAffineTransform b)
        {
            return !(a == b);
        }

    }
}
