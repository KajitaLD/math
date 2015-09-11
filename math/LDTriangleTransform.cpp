/**
 *
 *  2015/6/28
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDTriangleTransform.h"
#include <QtMath>
#include "LDMathUtil.h"

namespace live2d
{

LDTriangleTransform::LDTriangleTransform( const LDPoint& p0, const LDPoint& p1, const LDPoint& p2 )
	:m_p0( p0 ),m_p1( p1 ),m_p2( p2 )
{

}

LDPoint LDTriangleTransform::transform( float tx, float ty ) const
{
//	LDPoint result=m_p0
//			+tx*(m_p1-m_p0)
//			+ty*(m_p2-m_p0);
//	return result;
	//TODO 上記計算だとdouble精度。予期せぬ場所で計算が合わない。
	float x=m_p0.x()
			+tx*( m_p1.x()-m_p0.x() )
			+ty*( m_p2.x()-m_p0.x() );


	float y=m_p0.y()
			+tx*( m_p1.y()-m_p0.y() )
			+ty*( m_p2.y()-m_p0.y() );

//	float x=m_p0.x()
//			+tx*( qAbs(m_p1.x()-m_p0.x()) )
//			+ty*( qAbs(m_p2.x()-m_p0.x()) );


//	float y=m_p0.y()
//			+tx*( qAbs(m_p1.y()-m_p0.y()) )
//			+ty*( qAbs(m_p2.y()-m_p0.y()) );

	return LDPoint(x,y);
}

LDPoint LDTriangleTransform::transformOneMinusT(float tx, float ty) const
{
//	LDPoint result=m_p2
//			+(1-tx)*(m_p1-m_p2)
//			+(1-ty)*(m_p0-m_p2);
//	return result;
	//TODO transform()と同じ問題
	float x=m_p2.x()
			+(1-tx)*( m_p1.x()-m_p2.x() )
			+(1-ty)*( m_p0.x()-m_p2.x() );


	float y=m_p2.y()
			+(1-tx)*( m_p1.y()-m_p2.y() )
			+(1-ty)*( m_p0.y()-m_p2.y() );

	return LDPoint(x,y);
}

LDPoint LDTriangleTransform::inverseTransform(float x, float y) const
{
	//三角形の1点を基準点とする(この場合index0番)
	//基準点から2辺に向かうベクトルをV1,V2とし、(x,y)へ向かうベクトルをV0とする
	//V0 = s*V1 + t*V2
	//とするとき
	//(s,t) = ((V1*V2)の逆行列) * V0

	//Cubismから移植。
	QVector2D v0(LDPoint(x,y)-m_p0);
	QVector2D v1(m_p1-m_p0);
	QVector2D v2(m_p2-m_p0);

	double det=v1.x()*v2.y()-v1.y()*v2.x();

	double tx=(v2.y()*v0.x()-v2.x()*v0.y())/det;
	double ty=(-v1.y()*v0.x()+v1.x()*v0.y())/det;

	return LDPoint(tx,ty);
}

LDPoint LDTriangleTransform::inverseTransformOneMinusT(float x, float y) const
{
	//Cubismから移植。
	QVector2D v0(LDPoint(x,y)-m_p2);
	QVector2D v1(m_p1-m_p2);
	QVector2D v2(m_p0-m_p2);
	double det=v1.x()*v2.y()-v1.y()*v2.x();

	double tx=(v2.y()*v0.x()-v2.x()*v0.y())/det;
	double ty=(-v1.y()*v0.x()+v1.x()*v0.y())/det;

	return LDPoint(1-tx,1-ty);
}

} // namespace live2d

