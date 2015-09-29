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

//一定の範囲外補間に使わない場合、下記defineを有効にする
//#define LIMITED
#ifdef LIMITED
#define MAX 1
#define MIN 0
#endif //LIMITED

//(はみ出すことは可能だが)0~1区間のはずが大きすぎる値になってるときは、どこかで壊れた可能性が高い
#define SAFE_CHK
#ifdef SAFE_CHK
#define OUT_OVER 10000
#endif //SAFE_CHK

QDebug operator<<( QDebug dbg, const LDQuadTransform& quad )
{
	dbg.nospace() << quad.getPointList();

	return dbg;
}

LDQuadTransform::LDQuadTransform( const LDPoint& topLeft, const LDPoint& bottomRight )
{
	setSize( topLeft,bottomRight );
}


LDQuadTransform::LDQuadTransform( const LDPoint& topLeft, const LDPoint& topRight, const LDPoint& bottomRight, const LDPoint& bottomLeft )
{
	m_topLeft=topLeft;
	m_bottomRight=bottomRight;
	m_topRight=topRight;
	m_bottomLeft=bottomLeft;
}


LDPoint LDQuadTransform::transform( const LDUvPoint& t ,bool clip ) const
{
	return transform( t.x(),t.y(),clip );
}

LDPointList LDQuadTransform::transform( const LDUvPointList& pList,bool clip ) const
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
	Q_ASSERT(checkLimitedIfDefine(LDUvPoint(tx,ty)));

	if ( true )
	{
		tx=LDMathUtil::clamp( tx,0.0,1.0 );
		ty=LDMathUtil::clamp( ty,0.0,1.0 );
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

	if ( isnan( x )||isnan( y ) )
	{
		qWarning()<<"Quad Transform Result is Nan!";
	}

	return LDPoint( x,y );
}

LDUvPoint LDQuadTransform::inverseTransform( const LDPoint& pt,bool& success,bool clip ) const
{
	return inverseTransform( pt.x(),pt.y(), success, clip );
}

LDUvPointList LDQuadTransform::inverseTransform( const LDUvPointList& pList,bool& success,bool clip ) const
{
	LDUvPointList	result;
	foreach ( const auto& pt, pList )
	{
		result.push_back( inverseTransform( pt, success, clip ) );
	}
	return result;
}

LDUvPoint LDQuadTransform::inverseTransform( double x, double y, bool& success,bool clip ) const
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
	//境界上にあるときは誤差によって不安定なので明示的にチェック
	LDPoint pt=LDPoint(x,y);
	if(m_topLeft==pt)return LDUvPoint(0,0);
	if(m_topRight==pt)return LDUvPoint(1,0);
	if(m_bottomLeft==pt)return LDUvPoint(0,1);
	if(m_bottomRight==pt)return LDUvPoint(1,1);


	double tx,ty;
	success = LDMathUtil::inverseLerp2D( m_topLeft,m_topRight,m_bottomLeft,m_bottomRight,LDPoint( x,y ),tx,ty );
	if ( true )
	{
		tx=LDMathUtil::clamp( tx,0.0,1.0 );
		ty=LDMathUtil::clamp( ty,0.0,1.0 );
	}

//	if ( isnan( tx )||isnan( ty ) )
//	{
//		LDMathUtil::inverseLerp2D( m_topLeft,m_topRight,m_bottomLeft,m_bottomRight,LDPoint( x,y ),tx,ty );

//		qWarning()<<"Quad Inv Transform Result is Nan!";
//	}
//	if( ! checkLimitedIfDefine(LDUvPoint(tx,ty)))
//	{
//		LDMathUtil::inverseLerp2D( m_topLeft,m_topRight,m_bottomLeft,m_bottomRight,LDPoint( x,y ),tx,ty );

//	}
	Q_ASSERT(checkLimitedIfDefine(LDUvPoint(tx,ty)));

	return LDUvPoint( tx,ty );
}

bool LDQuadTransform::contains( const LDPoint& map ) const
{
	//境界上にあるときは誤差によって不安定なので明示的にチェック
	if(map==m_topLeft)return true;
	if(map==m_topRight)return true;
	if(map==m_bottomLeft)return true;
	if(map==m_bottomRight)return true;
	return getPolygon().containsPoint( map,Qt::WindingFill );
}

QPolygonF LDQuadTransform::getPolygon() const
{
	QPolygonF p;
	p.push_back( m_topLeft );
	p.push_back( m_topRight );
	p.push_back( m_bottomRight );
	p.push_back( m_bottomLeft );
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

LDLineList LDQuadTransform::getLineList() const
{
	LDLineList result;
	result.push_back(LDLine( m_topLeft,m_topRight) );
	result.push_back(LDLine( m_topRight,m_bottomRight) );
	result.push_back(LDLine( m_bottomRight,m_bottomLeft) );
	result.push_back(LDLine( m_bottomLeft,m_topLeft) );

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

LDPoint LDQuadTransform::getVectorRow0() const
{
	return LDPoint(getTopRight()-getTopLeft());
}

LDPoint LDQuadTransform::getVectorRow1() const
{
	return LDPoint(getBottomRight()-getBottomLeft());
}

LDPoint LDQuadTransform::getVectorColumn0() const
{
	return LDPoint(getBottomLeft()-getTopLeft());
}

LDPoint LDQuadTransform::getVectorColumn1() const
{
	return LDPoint(getBottomRight()-getTopRight());
}

LDPoint LDQuadTransform::getAverageCenter() const
{
	//四隅の平均を簡易中心とする
	return ( m_topLeft+m_topRight+m_bottomLeft+m_bottomRight )/4.0;
}

LDLine LDQuadTransform::getDiagonal1() const
{
	return LDLine( m_topLeft,m_bottomRight );
}

LDLine LDQuadTransform::getDiagonal2() const
{
	return LDLine( m_bottomLeft,m_topRight );
}

QRectF LDQuadTransform::getAverageRect() const
{
	auto diagonal1=getDiagonal1();
	auto diagonal2=getDiagonal2();
	// 対角１（左上から右下へ）を求める
	double v1x = diagonal1.x2() - diagonal1.x1() ;
	double v1y = diagonal1.y2() - diagonal1.y1() ;

	// 対角2（左下から右上へ）を求める
	double v2x = diagonal2.x2() - diagonal2.x1() ;
	double v2y = diagonal2.y1() - diagonal2.y2() ;

	LDPoint vectorS;
	LDPoint vectorT;
	LDPoint vectorST=( vectorS+vectorT )/2.0;

	// 横軸を求める（対角の２ベクトルを足して、2で割ると、およその横向きベクトルとなる）
	vectorS.setX( ( v1x + v2x ) * 0.5 );
	vectorS.setY( ( v1y + v2y ) * 0.5 );

	// 縦軸を求める
	vectorT.setX( ( v1x - v2x ) * 0.5f );
	vectorT.setY( ( v1y - v2y ) * 0.5f );

	LDPoint centerST = getAverageCenter();

	LDPoint origin( centerST-vectorST*0.5 );

	return QRectF( origin,vectorST-centerST );
}

void LDQuadTransform::setSize( const LDPoint& topLeft, const LDPoint& bottomRight )
{
	m_topLeft=topLeft;
	m_bottomRight=bottomRight;

	m_topRight.setX( bottomRight.x() );
	m_topRight.setY( topLeft.y() );

	m_bottomLeft.setX( topLeft.x() );
	m_bottomLeft.setY( bottomRight.y() );
}

LDPoint LDQuadTransform::getOutsidePoint( int row, int col ) const
{
	//元の四隅のとき
	if(row==0&&col==0)
	{
		return getTopLeft();
	}
	else if(row==1&&col==0)
	{
		return getBottomLeft();
	}
	else if(row==0&&col==1)
	{
		return getTopRight();
	}
	else if(row==1&&col==1)
	{
		return getBottomRight();
	}
	//元の四隅の平行線上のとき
//	else if(row==0)
//	{
//		return m_topLeft+getVectorRow0()*col;
//	}
//	else if(row==1)
//	{
//		return getBottomLeft()+getVectorRow1()*col;
//	}
//	else if(col==0)
//	{
//		return m_topLeft+row*getVectorColumn0();
//	}
//	else if(col==1)
//	{
//		return getBottomLeft()+row*getVectorColumn1();
//	}
	//外側の四隅のとき
	else if(row>=0 && col>=0)
	{
		//右下
		return m_topLeft+row*getVectorColumn1()+col*getVectorRow1();
	}
	else if(row>=0 && col<0)
	{
		//左下
		return m_topLeft+row*getVectorColumn0()+col*getVectorRow1();
	}
	else if(row<0 && col>=0)
	{
		//右上
		return m_topLeft+row*getVectorColumn1()+col*getVectorRow0();
	}
	else if(row<0 && col<0)
	{
		//左上
		return m_topLeft+row*getVectorColumn0()+col*getVectorRow0();
	}

	//条件チェック忘れ
	Q_ASSERT(false);
	return LDPoint();
}

bool LDQuadTransform::isSquare() const
{
	if ( m_topLeft.x()!=m_bottomLeft.x() )
	{
		return false;
	}
	if ( m_topRight.x()!=m_bottomRight.x() )
	{
		return false;
	}
	if ( m_topLeft.y()!=m_topRight.x() )
	{
		return false;
	}
	if ( m_bottomLeft.y()!=m_bottomRight.x() )
	{
		return false;
	}
	return true;
}

LDSquareTransform LDQuadTransform::toSquareTransform() const
{
	return LDSquareTransform( m_topLeft,m_bottomRight );
}

LDQuadTransform LDQuadTransform::createExtend(int extend) const
{
	if(extend==0)return *this;
	return LDQuadTransform(
				getOutsidePoint(-extend,-extend),
				getOutsidePoint(-extend,1+extend),
				getOutsidePoint(1+extend,1+extend),
				getOutsidePoint(1+extend,-extend)
				);
}

bool LDQuadTransform::isOutsideLocal(const LDUvPoint& t) const
{
	//境界線上は外側ではないと判断
	return t.x()<0 || t.x()>1 || t.y()<0 || t.y()>1;
}

bool LDQuadTransform::checkLimitedIfDefine(LDUvPoint t) const
{
#ifdef LIMITED
	if(t.x()>MAX)return false;
	if(t.x()<MIN)return false;
	if(t.y()>MAX)return false;
	if(t.y()<MIN)return false;
#endif //LIMITED

#ifdef SAFE_CHK
//	Q_ASSERT(fabs(t.x())<OUT_OVER);
//	Q_ASSERT(fabs(t.y())<OUT_OVER);
#endif //SAFE_CHK
	return true;
}

//TODO リアルタイムで何度も呼んだら重そう。必要になったら誰か書いてください
//LDPoint LDQuadTransform::CenterOfGravity() const
//{
////	1)四角形の対角線を結びます。対角線により、4つの三角形に分割されます。
////	2)4つの三角形において、それぞれ重心を求めます。
////	3)4つの三角形のうち、向かい合っている三角形の重心を結びます。その交点が求める四角形の重心となります。
//}





} // namespace live2d
