/**
 *
 *  2015/6/8
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDAffineTransform.h"
#include "LDMatrix44.h"

namespace live2d {

LDAffineTransform::LDAffineTransform()
{
	m_matrix.identity();
}

void LDAffineTransform::translate(ld_float x, ld_float y)
{
	m_matrix.translate(x,y,0);
}

void LDAffineTransform::translate(LDPoint pt)
{
	translate(pt.x(),pt.y());
}

void LDAffineTransform::scale(ld_float scaleX, ld_float scaleY)
{
	float tx=m_matrix.tx;
	float ty=m_matrix.ty;

	m_matrix.setToTranslate(-tx,-ty,0);
	m_matrix.scale(scaleX,scaleY,1);
	m_matrix.setToTranslate(tx,ty,0);
}

void LDAffineTransform::rotate(ld_float theta)
{
	m_matrix.rotateZ(theta);
}

void LDAffineTransform::setToTranslate(ld_float x, ld_float y)
{
	m_matrix.setToTranslate(x,y,0);
}

void LDAffineTransform::setToTranslate(LDPoint pt)
{
	setToTranslate(pt.x(),pt.y());
}

LDPoint LDAffineTransform::getTranslate() const
{
	return LDPoint(m_matrix.tx,m_matrix.ty);
}

float LDAffineTransform::transform(float p)const
{
	LDVector3 srcVec(p,0,0);
	LDVector3 dstVec = m_matrix.transform(srcVec);

	return dstVec.x;
}

LDPoint LDAffineTransform::transform(const LDPoint& p)const
{
	LDVector3 srcVec(p.x(),p.y(),0);
	LDVector3 dstVec = m_matrix.transform(srcVec);

	return LDPoint(dstVec.x,dstVec.y);
}

LDMatrix44 LDAffineTransform::getMatrix()const
{
	return m_matrix;
}

bool operator ==(const LDAffineTransform& a, const LDAffineTransform& b)
{
	return a.getMatrix()==b.getMatrix();
}

bool operator !=(const LDAffineTransform& a, const LDAffineTransform& b)
{
	return a.getMatrix()!=b.getMatrix();
}

//***************************************
// Serialize
//***************************************
template<class Archive>
void LDAffineTransform::serialize( Archive& ar, unsigned int /*version*/ )
{
	LD_SERIALIZE_VALUE(ar, m_matrix );
}
LD_SERIALIZE_IMPL(LDAffineTransform);

QDebug operator<<(QDebug dbg, const LDAffineTransform& affine)
{
	dbg.nospace() << affine.getMatrix();

	return dbg;
}

} // namespace live2d

