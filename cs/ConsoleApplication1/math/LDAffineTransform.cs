using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    using ld_float = System.Single;
    
    //2Dのアフィン変換を行う
    public class LDAffineTransform
    {
        private LDMatrix44 m_matrix=new LDMatrix44();
        public LDAffineTransform() { m_matrix.identity(); }
        public void translate(ld_float x, ld_float y) { m_matrix.translate(x, y, 0); }
        public void translate(LDPoint pt) { translate(pt.x(), pt.y()); }
        public void scale(ld_float scaleX, ld_float scaleY) {
            float tx = m_matrix.tx;
            float ty = m_matrix.ty;

            m_matrix.setToTranslate(-tx, -ty, 0);
            m_matrix.scale(scaleX, scaleY, 1);
            m_matrix.setToTranslate(tx, ty, 0);
        }
        public void rotate(ld_float theta) { m_matrix.rotateZ(theta); }
        public void setToTranslate(ld_float x, ld_float y) { m_matrix.setToTranslate(x, y, 0); }
        public void setToTranslate(LDPoint pt) { setToTranslate(pt.x(), pt.y()); }
        public LDPoint getTranslate() { return new LDPoint(m_matrix.tx, m_matrix.ty); }
        public float transform(float p) {
            LDVector3 srcVec = new LDVector3(p,0, 0);
            LDVector3 dstVec = m_matrix.transform(srcVec);

            return dstVec.x;
        }
        public LDPoint transform(LDPoint p) {
            LDVector3 srcVec=new LDVector3(p.x(), p.y(), 0);
            LDVector3 dstVec = m_matrix.transform(srcVec);

            return new LDPoint(dstVec.x, dstVec.y);
        }
        public LDMatrix44 getMatrix() { return m_matrix; }
        //LD_SERIALIZABLE;
        public static bool operator ==(LDAffineTransform a, LDAffineTransform b)
        {
            return a.getMatrix() == b.getMatrix();
        }
        public static bool operator !=(LDAffineTransform a, LDAffineTransform b)
        {
            return a.getMatrix() != b.getMatrix();
        }
        public override bool Equals(object obj)
        {
            if (obj == null) return false;
            if (obj.GetType() != this.GetType()) return false;
            var p = obj as LDAffineTransform;
            return this == p;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }

    

    //QDebug operator <<(QDebug dbg,  LDAffineTransform line );
}
