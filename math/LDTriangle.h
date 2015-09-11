/**
 *
 *  2015/5/21
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include "private/LDMath_private.h"
#include <utility>

#include "LDIndexLine.h"
#include "LDIndexLineList.h"
#include "LDSerialize.h"

namespace live2d
{

enum struct ClockWise
{
	CW,
	CCW
};

/**
 * 頂点へのインデックスで表された三角ポリゴン
 *
 */
class LDTriangle
{
public:
	LDTriangle();
	LDTriangle( int a,int b,int c );
	~LDTriangle();

	LDPolygon toPolygon( const LDPointList& points )const;

	void setClockWise( const LDPointList& form,ClockWise clockWise );

	void setIndex( int a,int b,int c );
	int getIndex1() const;
	int getIndex2() const;
	int getIndex3() const;

	int getIndexWithoutLine( LDIndexLine l )const;

	LDPoint getPoint1( const LDPointList& points )const;
	LDPoint getPoint2( const LDPointList& points )const;
	LDPoint getPoint3( const LDPointList& points )const;

	LDIndexLine getLine1()const;
	LDIndexLine getLine2()const;
	LDIndexLine getLine3()const;

	LDIndexLineList getRelatedLines(int pointIndex)const;

	bool hasIndex( int pointIndex )const;
	bool containsLine( LDIndexLine l )const;

	//一つでも線を共有してるかどうか。同じ三角形でも当然共有してる
	bool isSharedLine( LDTriangle t )const;

	//一致の確認は順番関係なし
	bool operator ==( const LDTriangle& rop );


private:
	int m_index1;
	int m_index2;
	int m_index3;

	LD_SERIALIZABLE;
};

QDebug operator<<( QDebug dbg, const LDTriangle& tr );

} // namespace live2d



