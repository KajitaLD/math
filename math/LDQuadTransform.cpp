/**
 *
 *  2015/6/11
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDQuadTransform.h"
#include "LDTriangleTransform.h"
#include "LDMathUtil.h"
namespace live2d
{

QDebug operator<<( QDebug dbg, const LDQuadTransform& quad )
{
	dbg.nospace() << quad.getPointList();

	return dbg;
}

LDQuadTransform::LDQuadTransform( const LDPoint& topLeft, const LDPoint& bottomRight )
{
	m_topLeft=topLeft;
	m_bottomRight=bottomRight;

	m_topRight.setX( bottomRight.x() );
	m_topRight.setY( topLeft.y() );

	m_bottomLeft.setX( topLeft.x() );
	m_bottomLeft.setY( bottomRight.y() );
}


LDQuadTransform::LDQuadTransform( const LDPoint& topLeft, const LDPoint& topRight, const LDPoint& bottomRight, const LDPoint& bottomLeft )
{
	m_topLeft=topLeft;
	m_bottomRight=bottomRight;
	m_topRight=topRight;
	m_bottomLeft=bottomLeft;
}


LDPoint LDQuadTransform::transform( const LDPoint& t ,bool clip) const
{
	return transform( t.x(),t.y(),clip );
}

LDPointList LDQuadTransform::transform( const LDPointList& pList,bool clip ) const
{
	LDPointList	result;
	foreach ( const auto& pt, pList )
	{
		result.push_back( transform( pt,clip ) );
	}
	return result;
}


LDPoint LDQuadTransform::transform( double tx, double ty,bool clip ) const
{
	if(clip)
	{
		tx=LDMathUtil::clamp(tx,0.0,1.0);
		ty=LDMathUtil::clamp(ty,0.0,1.0);
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

	double x=LDMathUtil::lerp2D(
				m_topLeft.x(),m_topRight.x(),tx,
				m_bottomLeft.x(),m_bottomRight.x(),ty
			);
	double y=LDMathUtil::lerp2D(
				m_topLeft.y(),m_topRight.y(),tx,
				m_bottomLeft.y(),m_bottomRight.y(),ty
			);
	return LDPoint( x,y );
}

LDPoint LDQuadTransform::inverseTransform(const LDPoint& pt,bool clip) const
{
	return inverseTransform( pt.x(),pt.y() ,clip);
}

LDPointList LDQuadTransform::inverseTransform(const LDPointList& pList,bool clip) const
{
	LDPointList	result;
	foreach ( const auto& pt, pList )
	{
		result.push_back( inverseTransform( pt,clip ) );
	}
	return result;
}

LDPoint LDQuadTransform::inverseTransform(double x, double y,bool clip) const
{

/*
	QPolygonF p;
	p.push_back(m_topLeft);
	p.push_back(m_topRight);
	p.push_back(m_bottomLeft);
//	p<<m_topLeft<<m_topRight<<m_bottomLeft;

	if ( p.containsPoint(LDPoint(x,y),Qt::WindingFill))
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
	double tx,ty;
	LDMathUtil::inverseLerp2D(m_topLeft,m_topRight,m_bottomLeft,m_bottomRight,LDPoint(x,y),tx,ty);

	if(clip)
	{
		tx=LDMathUtil::clamp(tx,0.0,1.0);
		ty=LDMathUtil::clamp(ty,0.0,1.0);
	}

	return LDPoint( tx,ty );
}

bool LDQuadTransform::contains(const LDPoint& map) const
{
	return getPolygon().containsPoint(map,Qt::WindingFill);
}

QPolygonF LDQuadTransform::getPolygon() const
{
	QPolygonF p;
	p.push_back(m_topLeft);
	p.push_back(m_topRight);
	p.push_back(m_bottomRight);
	p.push_back(m_bottomLeft);
	return p;
}


LDPointList LDQuadTransform::getPointList() const
{
	LDPointList result;
	result.push_back( m_topLeft );
	result.push_back( m_topRight );
	result.push_back( m_bottomRight );
	result.push_back( m_bottomLeft );

	return result;
}
LDPoint LDQuadTransform::getTopLeft() const
{
	return m_topLeft;
}
LDPoint LDQuadTransform::getTopRight() const
{
	return m_topRight;
}
LDPoint LDQuadTransform::getBottomRight() const
{
	return m_bottomRight;
}
LDPoint LDQuadTransform::getBottomLeft() const
{
	return m_bottomLeft;
}





} // namespace live2d
