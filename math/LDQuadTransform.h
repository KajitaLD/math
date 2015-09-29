/**
 *
 *  2015/6/11
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include "private/LDMath_private.h"

#include "LDSquareTransform.h"


namespace live2d
{
class LDQuadTransform
{
public:
	LDQuadTransform( const LDPoint& topLeft,const LDPoint& bottomRight );

	//時計回りに4点
	LDQuadTransform( const LDPoint& topLeft,const LDPoint& topRight,const LDPoint& bottomRight,const LDPoint& bottomLeft );

	//clipがtrueのときは必ず範囲内にクリッピングされる
	LDPoint transform( const LDUvPoint& t,bool clip=false )const;
	LDPointList transform( const LDUvPointList& t,bool clip=false )const;
	LDPoint transform( double tx, double ty, bool clip=false )const;

	LDUvPoint inverseTransform( const LDPoint& pt,bool& success,bool clip=false )const;
	LDUvPointList inverseTransform( const LDPointList& pt,bool& success,bool clip=false )const;
	LDUvPoint inverseTransform( double x,double y,bool& success,bool clip=false )const;

	//マッピングされた座標系に含まれるかどうか
	bool contains( const LDPoint& map )const;
	QPolygonF getPolygon()const;

	LDPointList getPointList()const;
	LDLineList getLineList()const;

	LDPoint getTopLeft() const;
	LDPoint getTopRight() const;
	LDPoint getBottomRight() const;
	LDPoint getBottomLeft() const;

	LDPoint getVectorRow0()const;
	LDPoint getVectorRow1()const;
	LDPoint getVectorColumn0()const;
	LDPoint getVectorColumn1()const;

	//簡易的に中心を求める
	LDPoint getAverageCenter()const;
	//	LDPoint CenterOfGravity()const;

	LDLine getDiagonal1()const;//対角線。左上から右下
	LDLine getDiagonal2()const;//対角線。左下から右上

	//対角線のベクトルから計算した簡易領域。
	QRectF getAverageRect()const;

	void setSize(const LDPoint& topLeft,const LDPoint& bottomRight );

	LDPoint getOutsidePoint(int row,int col)const;

	//正方形かどうか
	bool isSquare()const;
	LDSquareTransform toSquareTransform()const;

	//一回り大きくしたものを生成
	LDQuadTransform createExtend(int extend)const;

	bool isOutsideLocal( const LDUvPoint& t)const;

	//デバッグ用
	bool checkLimitedIfDefine(LDUvPoint t)const;
private:
	LDPoint m_topLeft;
	LDPoint m_topRight;
	LDPoint m_bottomRight;
	LDPoint m_bottomLeft;

};

QDebug operator<<( QDebug dbg, const LDQuadTransform& quad );

} // namespace live2d

