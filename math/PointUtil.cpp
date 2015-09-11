/**
 *
 *  2015/5/21
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#include "private/LDMath_private.h"
#include "PointUtil.h"
#include <limits>

namespace live2d
{
namespace math
{

LDRectF PointUtil::getBoundingRect(const LDPointList& form )
{
	float maxX=std::numeric_limits<float>::min();
	float minX=std::numeric_limits<float>::max();
	float maxY=std::numeric_limits<float>::min();
	float minY=std::numeric_limits<float>::max();
	foreach ( const LDPoint& p, form )
	{
		float x = p.x();
		float y = p.y();
		if ( x < minX )
		{
			minX= x;    //  最小のx
		}
		if ( x > maxX )
		{
			maxX= x;    //  最大のx
		}
		if ( y < minY )
		{
			minY= y;    //  最小のy
		}
		if ( y > maxY )
		{
			maxY= y;    //  最大のy
		}
	}

	LDRectF rect;
	rect.setLeft( minX );
	rect.setRight( maxX );
	rect.setTop( minY );
	rect.setBottom( maxY );
	return rect;
}

QString PointUtil::toString( const QPoint& p )
{
	return QString( "Point (%1,%2)" ).arg( p.x() ).arg( p.y() );
}

QString PointUtil::toStringF( const QPointF& p )
{
	return QString( "PointF (%1,%2)" ).arg( p.x() ).arg( p.y() );
}

int PointUtil::findMinYPointIndex(const LDPointList& points)
{
	if (points.length()==0) {
		return -1;
	}
	int length=points.length();

	double minY=points[0].y();
	for (int i = 0; i < length; ++i) {
		if(points[i].y()<minY)
		{
			minY=points[i].y();
		}
	}

	QList<int> minYList;
	for (int i = 0; i < length; ++i) {
		if(points[i].y()==minY)
		{
			minYList.push_back(i);
		}
	}

	Q_ASSERT(minYList.length()!=0);

	if (minYList.length()==1) {
		return minYList[0];
	}

	float minX=points[ minYList[0] ].x();
	int minXIndex=minYList[0];
	for (int i = 0; i < minYList.length(); ++i) {
		int index=minYList[i];
		if(points[index].x()<minX)
		{
			minXIndex=index;
		}
	}

	return minXIndex;
}

} // namespace math
} // namespace live2d

