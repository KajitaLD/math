/**
 *
 *  2015/6/8
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include "common.h"
#include "private/LDMath_private.h"
#include "LDSerialize.h"
#include "LDMatrix44.h"

namespace live2d {

//2Dのアフィン変換を行う
class LDAffineTransform
{
public:
	LDAffineTransform();

	void translate( ld_float x , ld_float y  );
	void translate( LDPoint pt );
	void scale( ld_float scaleX , ld_float scaleY );
	void rotate( ld_float theta );

	void setToTranslate(ld_float x , ld_float y);
	void setToTranslate(LDPoint pt);

	LDPoint getTranslate()const;

	float transform(float p)const;
	LDPoint transform( const LDPoint& p  ) const;

	LDMatrix44 getMatrix()const;

private:
	LDMatrix44 m_matrix;

	LD_SERIALIZABLE;
};

bool operator ==( const LDAffineTransform& a , const LDAffineTransform& b ) ;
bool operator !=( const LDAffineTransform& a , const LDAffineTransform& b ) ;

QDebug operator<<( QDebug dbg, const LDAffineTransform& line );

} // namespace live2d


