using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDQuadTransform
    {
        public LDQuadTransform(LDPoint topLeft, LDPoint bottomRight)
        {
            m_topLeft = topLeft;
            m_bottomRight = bottomRight;

            m_topRight.setX(bottomRight.x());
            m_topRight.setY(topLeft.y());

            m_bottomLeft.setX(topLeft.x());
            m_bottomLeft.setY(bottomRight.y());
        }

        //時計回りに4点
        public LDQuadTransform(LDPoint topLeft, LDPoint topRight, LDPoint bottomRight, LDPoint bottomLeft)
        {
            m_topLeft = topLeft;
            m_bottomRight = bottomRight;
            m_topRight = topRight;
            m_bottomLeft = bottomLeft;
        }

        //clipがtrueのときは必ず範囲内にクリッピングされる
        public LDPoint transform(LDPoint t, bool clip = false)
        {
            return transform(t.x(), t.y(), clip);
        }
        public LDPointList transform(LDPointList pList, bool clip = false)
        {
            LDPointList result=new LDPointList();
            foreach ( var pt in pList )
	{
                result.Add(transform(pt, clip));
            }
            return result;
        }
        public LDPoint transform(double tx, double ty, bool clip = false)
        {
            if (clip)
            {
                tx = LDMathUtil.clamp(tx, 0.0, 1.0);
                ty = LDMathUtil.clamp(ty, 0.0, 1.0);
            }

            /*
                if ( tx + ty < 1 )
                {
                    //左上三角
                    LDTriangleTransform tr(m_topLeft,m_topRight,m_bottomLeft);
                    return tr.transform(tx,ty);
                }
                else
                {
                    //右下三角
                    //TODO SDKでは計算式を(1-t)にしている。違いがある?
            //		LDTriangleTransform tr(m_bottomLeft,m_bottomRight,m_topRight);
            //		return tr.transform(tx,ty);
                    LDTriangleTransform tr(m_topRight,m_bottomLeft,m_bottomRight);
                    return tr.transformOneMinusT(tx,ty);
                }
            */

            double x = LDMathUtil.lerp2D(
                        m_topLeft.x(), m_topRight.x(), tx,
                        m_bottomLeft.x(), m_bottomRight.x(), ty
                    );
            double y = LDMathUtil.lerp2D(
                        m_topLeft.y(), m_topRight.y(), tx,
                        m_bottomLeft.y(), m_bottomRight.y(), ty
                    );
            return new LDPoint((float)x, (float)y);
        }

        public LDPoint inverseTransform(LDPoint pt, bool clip = false)
        {
            return inverseTransform(pt.x(), pt.y(), clip);
        }

        public LDPointList inverseTransform(LDPointList pList, bool clip = false)
        {
            LDPointList result=new LDPointList();
            foreach ( var pt in pList )
	{
                result.Add(inverseTransform(pt, clip));
            }
            return result;
        }
        public LDPoint inverseTransform(double x, double y, bool clip = false)
        {

            /*
                QPolygonF p;
                p.Add(m_topLeft);
                p.Add(m_topRight);
                p.Add(m_bottomLeft);
            //	p<<m_topLeft<<m_topRight<<m_bottomLeft;

                if ( p.containsPoint(LDPoint(x,y),Qt.WindingFill))
                {
                    //左上三角
                    LDTriangleTransform tr(m_topLeft,m_topRight,m_bottomLeft);
                    return tr.inverseTransform(x,y);
                }
                else
                {
                    //右下三角
                    //TODO SDKでは計算式を(1-t)にしている。違いがある?
            //		LDTriangleTransform tr(m_bottomLeft,m_bottomRight,m_topRight);
            //		return tr.transform(tx,ty);
                    LDTriangleTransform tr(m_topRight,m_bottomLeft,m_bottomRight);
                    return tr.inverseTransformOneMinusT(x,y);
                }
            */
            double tx, ty;
            LDMathUtil.inverseLerp2D(m_topLeft, m_topRight, m_bottomLeft, m_bottomRight,new LDPoint((float)x, (float)y),out tx, out ty);

            if (clip)
            {
                tx = LDMathUtil.clamp(tx, 0.0, 1.0);
                ty = LDMathUtil.clamp(ty, 0.0, 1.0);
            }

            return new LDPoint((float)tx, (float)ty);
        }

        //マッピングされた座標系に含まれるかどうか
        public bool contains(LDPoint map)
        {
            return getPolygon().containsPoint(map, FillRule.WindingFill);
        }
        public LDPolygon getPolygon()
        {

            LDPolygon p = new LDPolygon();
            p.Add(m_topLeft);
            p.Add(m_topRight);
            p.Add(m_bottomRight);
            p.Add(m_bottomLeft);
            return p;
        }

        public LDPointList getPointList()
        {
            LDPointList result=new LDPointList();
            result.Add(m_topLeft);
            result.Add(m_topRight);
            result.Add(m_bottomRight);
            result.Add(m_bottomLeft);

            return result;
        }

        public LDPoint getTopLeft() { return m_topLeft; }
        public LDPoint getTopRight() { return m_topRight; }
        public LDPoint getBottomRight() { return m_bottomRight; }
        public LDPoint getBottomLeft() { return m_bottomLeft; }

        private LDPoint m_topLeft;
        private LDPoint m_topRight;
        private LDPoint m_bottomRight;
        private LDPoint m_bottomLeft;
    }
}
