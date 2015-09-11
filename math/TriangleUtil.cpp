/**
 *
 *  2015/5/26
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDCircle.h"
#include "LDMathUtil.h"
#include "PointUtil.h"
#include "TriangleUtil.h"
#include <QVector3D>
#include <QtMath>

namespace live2d {
namespace math {

LDPolygon TriangleUtil::getHugeTriangle(const LDRectF& rect)
{
	Q_ASSERT(rect.left()<rect.right());
	Q_ASSERT(rect.top()<rect.bottom());

	// 1) 与えられた矩形を包含する円を求める
	//      円の中心 c = 矩形の中心
	//      円の半径 r = |p - c| + ρ
	//    ただし、pは与えられた矩形の任意の頂点
	//    ρは任意の正数
	QVector2D center(rect.center());
	QVector2D topLeft(rect.topLeft());
	float radius = center.distanceToPoint(topLeft);

	radius += 1.0f;//適当に大きくする

	// 2) その円に外接する正三角形を求める
	LDCircle circle(center.toPointF(),radius);
	return circle.getCircumscribedTriangle();
}

LDPolygon TriangleUtil::getHugeTriangle(const LDPointList& form)
{
	return getHugeTriangle(PointUtil::getBoundingRect(form));
}

bool TriangleUtil::containsPoint(const LDPoint& p1, const LDPoint& p2, const LDPoint& p3, const LDPoint& p, bool onLine)
{
	int i=pointInTriangle(p1,p2,p3,p);
	Q_ASSERT(i==-1||i==0||i==1);

	if(i==1)
	{
		// 三角形の内側
		return true;
	}

	if (onLine) {
		if(i==-1)
		{
			// 三角形の線上にある場合も含むとみなす
			return true;
		}
	}

	// 三角形の外側
	return false;
}

bool TriangleUtil::containsPoint(const LDPolygon& t, const LDPoint& p, bool onLine)
{
	Q_ASSERT(t.size()==3);
	return containsPoint(t[0],t[1],t[2],p,onLine);
}

int TriangleUtil::pointInTriangle(const LDPoint& p1, const LDPoint& p2, const LDPoint& p3, const LDPoint& p)
{
	// 有向線分 (p2,p1), (p2,p3) の外積の z 成分を求める
	double p12 = LDMathUtil::crossProductValue(p1, p, p2);
	double p23 = LDMathUtil::crossProductValue(p2, p, p3);
	double p31 = LDMathUtil::crossProductValue(p3, p, p1);

	// 三角形の内側
	if ((0 < p12) && (0 < p23) && (0 < p31))
		return 1; // 点 p が常に左側にある（時計回り）
	if ((0 > p12) && (0 > p23) && (0 > p31))
		return 1; // 点 p が常に右側にある（反時計回り）

	// 三角形の線上
	if ((0 <= p12) && (0 <= p23) && (0 <= p31))
		return -1; // 点 p が常に左側にある（時計回り）
	if ((0 >= p12) && (0 >= p23) && (0 >= p31))
		return -1; // 点 p が常に右側にある（反時計回り）

	// 三角形の外側
	return 0;
}

bool TriangleUtil::isObtuseTriangle(const LDPoint& p1, const LDPoint& p2, const LDPoint& p3)
{
	QVector2D __a(p1);
	QVector2D __b(p2);
	QVector2D __c(p3);


	QVector2D _a=__a-__b;
	QVector2D _b=__b-__c;
	QVector2D _c=__c-__a;
	//良く考えたら三角形全部の角度調べるだけでよかった。
	if(QVector2D::dotProduct(_a,_b)<0 )
		return true;
	if(QVector2D::dotProduct(_a,_c)<0 )
		return true;
	if(QVector2D::dotProduct(_b,_c)<0 )
		return true;
	
	return false;
	
//	float a=_a.length();
//	float b=_b.length();
//	float c=_c.length();
//	int longestIndex;
//	if ( a>=b  && a >=c )
//	{
//		longestIndex=0;
//	}
//	else if ( b >=a &&b >=c )
//	{
//		longestIndex=1;
//	}
//	else
//	{
//		longestIndex=2;
//	}

//	if ( longestIndex==0 )
//	{
//		if ( a*a<=b*b+c*c )
//		{
//			return false;
//		}
//		return true;
//	}
//	if ( longestIndex==1 )
//	{
//		if ( b*b<=a*a+c*c )
//		{
//			return false;
//		}
//		return true;
//	}
//	if ( longestIndex==2 )
//	{
//		if ( c*c<=b*b+a*a )
//		{
//			return false;
//		}
//		return true;
//	}
//	//ここまでのどこかに引っかかるはず 引っかからなかったらこの関数のどこかにバグがあるはず
//	Q_ASSERT( !" error" );
//	return false;
	
}

bool TriangleUtil::isObtuseAngle(LDPoint p1, LDPoint p2, LDPoint target)
{
	QVector2D a(p1);
	QVector2D b(p2);
	QVector2D c(target);


	QVector2D ab=a-b;
	QVector2D bc=b-c;
	QVector2D ca=c-a;
	
	if(QVector2D::dotProduct(bc,ca)<0 )
		return true;
	
	return false;
}

bool TriangleUtil::isTriangle(LDPoint p1, LDPoint p2, LDPoint p3)
{
	if( ( p1.x()*p2.y()+p2.x()*p3.y()+p3.x()*p1.y() ) - (p1.x()*p3.y()+p2.x()*p1.y()+p3.x()*p2.y()) !=0 )
		return true;
	return false;
}

float TriangleUtil::getTriangleHeight(const LDPoint& p1, const LDPoint& p2, const LDPoint& p3)
{
	LDPoint ab=p2-p1;
	LDPoint ac=p3-p1;
	float D=abs( ab.x()*ac.y() - ab.y()*ac.x() );
	float L = PointUtil::distance(p1,p2);
	float H= D/L;
	return H;
}

LDPoint TriangleUtil::getSimilarityTrianglePoint(const LDPoint &_s0, const LDPoint &_s1, const LDPoint &_s2, const LDPoint &_t0, const LDPoint &_t1)
{

	QVector2D s0(_s0);
	QVector2D s1(_s1);
	QVector2D s2(_s2);	
	QVector2D t0(_t0);
	QVector2D t1(_t1);
	
	QVector2D ss2=s2+t0-s0;
	float angle=LDMathUtil::getAngle(s1-s0,t1-t0);	
	LDPoint sss2=LDMathUtil::rotatePoint(_t0,ss2.toPointF(),-angle);
	QVector2D v_s(s1-s0);
	QVector2D v_t(t1-t0);
	float scale=v_t.length()/v_s.length();
	LDPoint t2=LDMathUtil::scalePoint(_t0,sss2,scale);
	return t2;
	
}




} // namespace math
} // namespace live2d

