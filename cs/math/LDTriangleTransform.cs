using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class LDTriangleTransform
    {
        public LDTriangleTransform(LDPoint p0, LDPoint p1, LDPoint p2)
        {
            m_p0 = p0;
            m_p1 = p1;
            m_p2 = p2;
        }

        public LDPoint transform(float tx, float ty)
        {
            //	LDPoint result=m_p0
            //			+tx*(m_p1-m_p0)
            //			+ty*(m_p2-m_p0);
            //	return result;
            //TODO 上記計算だとdouble精度。予期せぬ場所で計算が合わない。
            float x = m_p0.x()
                    + tx * (m_p1.x() - m_p0.x())
                    + ty * (m_p2.x() - m_p0.x());


            float y = m_p0.y()
                    + tx * (m_p1.y() - m_p0.y())
                    + ty * (m_p2.y() - m_p0.y());

            //	float x=m_p0.x()
            //			+tx*( qAbs(m_p1.x()-m_p0.x()) )
            //			+ty*( qAbs(m_p2.x()-m_p0.x()) );


            //	float y=m_p0.y()
            //			+tx*( qAbs(m_p1.y()-m_p0.y()) )
            //			+ty*( qAbs(m_p2.y()-m_p0.y()) );

            return new LDPoint(x, y);
        }
        public LDPoint transformOneMinusT(float tx, float ty)
        {
            //	LDPoint result=m_p2
            //			+(1-tx)*(m_p1-m_p2)
            //			+(1-ty)*(m_p0-m_p2);
            //	return result;
            //TODO transform()と同じ問題
            float x = m_p2.x()
                    + (1 - tx) * (m_p1.x() - m_p2.x())
                    + (1 - ty) * (m_p0.x() - m_p2.x());


            float y = m_p2.y()
                    + (1 - tx) * (m_p1.y() - m_p2.y())
                    + (1 - ty) * (m_p0.y() - m_p2.y());

            return new LDPoint(x, y);
        }

        public LDPoint inverseTransform(float x, float y)
        {
            //三角形の1点を基準点とする(この場合index0番)
            //基準点から2辺に向かうベクトルをV1,V2とし、(x,y)へ向かうベクトルをV0とする
            //V0 = s*V1 + t*V2
            //とするとき
            //(s,t) = ((V1*V2)の逆行列) * V0

            //Cubismから移植。
            LDVector2 v0 = new LDVector2(new LDPoint(x, y) - m_p0);
            LDVector2 v1 = new LDVector2(m_p1 - m_p0);
            LDVector2 v2 = new LDVector2(m_p2 - m_p0);

            double det = v1.x() * v2.y() - v1.y() * v2.x();

            double tx = (v2.y() * v0.x() - v2.x() * v0.y()) / det;
            double ty = (-v1.y() * v0.x() + v1.x() * v0.y()) / det;

            return new LDPoint((float)tx, (float)ty);
        }
        public LDPoint inverseTransformOneMinusT(float x, float y)
        {
            //Cubismから移植。
            LDVector2 v0 = new LDVector2(new LDPoint(x, y) - m_p2);
            LDVector2 v1 = new LDVector2(m_p1 - m_p2);
            LDVector2 v2 = new LDVector2(m_p0 - m_p2);
            double det = v1.x() * v2.y() - v1.y() * v2.x();

            double tx = (v2.y() * v0.x() - v2.x() * v0.y()) / det;
            double ty = (-v1.y() * v0.x() + v1.x() * v0.y()) / det;

            return new LDPoint(1 - (float)tx, 1 - (float)ty);
        }
        //時計回り
        public LDPoint m_p0;
        public LDPoint m_p1;
        public LDPoint m_p2;
    }
}
