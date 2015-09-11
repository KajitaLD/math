/**
 *
 *  2015/6/14
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDMathUtil.h"
#include "LDSimpleAffineTransform.h"
#include <math.h>

namespace live2d {

LDSimpleAffineTransform::LDSimpleAffineTransform()
	:originX(0),originY(0),scale(1),rotate(0)
{

}

float LDSimpleAffineTransform::transform(float p) const
{
	LDPoint tmp=transform(LDPoint(p,0));
	return tmp.x();
}

LDPoint LDSimpleAffineTransform::transform(const LDPoint& p) const
{
	float rx=p.x()*cosf(rotate)-p.y()*sinf(rotate);
	float ry=p.x()*sinf(rotate)+p.y()*cosf(rotate);

	float x=rx*scale+originX;
	float y=ry*scale+originY;

	return LDPoint(x,y);
}

LDPointList LDSimpleAffineTransform::transform(const LDPointList& form) const
{
	LDPointList result;
	foreach (const auto& pt, form) {
		result.push_back(transform(pt));
	}

	return result;
}

LDPoint LDSimpleAffineTransform::inverseTransform(const LDPoint& pt) const
{
	float sx=(pt.x()-originX)/scale;
	float sy=(pt.y()-originY)/scale;

	float rx=sx*cosf(-rotate)-sy*sinf(-rotate);
	float ry=sx*sinf(-rotate)+sy*cosf(-rotate);

	return LDPoint(rx,ry);
}

LDPointList LDSimpleAffineTransform::inverseTransform(const LDPointList& points) const
{
	LDPointList result;
	foreach (const auto& pt, points) {
		result.push_back(inverseTransform(pt));
	}

	return result;
}

float LDSimpleAffineTransform::getScale() const
{
	return scale;
}

void LDSimpleAffineTransform::setScale(float value)
{
	scale = value;
}

float LDSimpleAffineTransform::getRotate() const
{
	return rotate;
}

void LDSimpleAffineTransform::setRotate(float value)
{
	rotate = value;
}

float LDSimpleAffineTransform::getRotateDeg() const
{
	return rotate/LDMathUtil::PI*180.0f;
}

void LDSimpleAffineTransform::setRotateDeg(float degree)
{
	rotate = degree/180.0f*LDMathUtil::PI;
}

float LDSimpleAffineTransform::getOriginX() const
{
	return originX;
}

void LDSimpleAffineTransform::setOriginX(float value)
{
	originX = value;
}
float LDSimpleAffineTransform::getOriginY() const
{
	return originY;
}

void LDSimpleAffineTransform::setOriginY(float value)
{
	originY = value;
}

bool operator ==(const LDSimpleAffineTransform& a, const LDSimpleAffineTransform& b)
{
	if(a.getOriginX()!=b.getOriginX())return false;
	if(a.getOriginY()!=b.getOriginY())return false;
	if(a.getScale()!=b.getScale())return false;
	if(a.getRotateDeg()!=b.getRotateDeg())return false;
	return true;
}

bool operator !=(const LDSimpleAffineTransform& a, const LDSimpleAffineTransform& b)
{
	return !(a==b);
}

//***************************************
// Serialize
//***************************************
template<class Archive>
void LDSimpleAffineTransform::serialize( Archive& ar, unsigned int /*version*/ )
{
	LD_SERIALIZE_VALUE(ar, originX );
	LD_SERIALIZE_VALUE(ar, originY);
	LD_SERIALIZE_VALUE(ar, scale );
	LD_SERIALIZE_VALUE(ar, rotate);
}
LD_SERIALIZE_IMPL(LDSimpleAffineTransform);

QDebug operator<<(QDebug dbg, const LDSimpleAffineTransform& affine)
{
	dbg.nospace().noquote()
			<< "origin("<<affine.getOriginX()<<","<<affine.getOriginY()<<")"
			<<" scale("<<affine.getScale()<<")"
		   << " rotateDeg("<<affine.getRotateDeg()<<")";

	return dbg;
}


} // namespace live2d

