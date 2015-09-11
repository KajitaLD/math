/**
 *
 *  2015/6/14
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include "common.h"
#include "private/LDMath_private.h"
#include "LDSerialize.h"

namespace live2d {

class LDSimpleAffineTransform
{
public:
	LDSimpleAffineTransform();

	float transform( float p  )const ;
	LDPoint transform( const LDPoint& p  )const ;
	LDPointList transform( const LDPointList& form  )const ;

	LDPoint inverseTransform(const LDPoint& pt)const;
	LDPointList inverseTransform(const LDPointList& points)const;


	float getScale() const;
	void setScale(float value);

	float getRotate() const;
	void setRotate(float value);

	float getRotateDeg() const;
	void setRotateDeg(float value);

	LDPoint getOrigin()const
	{
		return LDPoint(originX,originY);
	}

	void setOrigin(LDPoint value)
	{
		originX=value.x();
		originY=value.y();
	}

	float getOriginX() const;
	void setOriginX(float value);

	float getOriginY() const;
	void setOriginY(float value);

private:
	float originX;
	float originY;
	float scale;
	float rotate;//ラジアン。範囲なしで、ｎ回転を表現できる。

	LD_SERIALIZABLE;
};



bool operator ==( const LDSimpleAffineTransform& a , const LDSimpleAffineTransform& b ) ;
bool operator !=( const LDSimpleAffineTransform& a , const LDSimpleAffineTransform& b ) ;

QDebug operator<<( QDebug dbg, const LDSimpleAffineTransform& line );
} // namespace live2d
