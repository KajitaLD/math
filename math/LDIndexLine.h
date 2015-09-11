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
#include <QDebug>

#include "LDSerialize.h"

namespace live2d
{

/**
 * 頂点へのインデックスで表された線分
 *
 */
class LDIndexLine
{

public:
	LDIndexLine();
	LDIndexLine( int a,int b );
	~LDIndexLine();


	LDLine toLine( const LDPointList& form ) const;

	//一致の確認は順番関係なし
	bool operator ==( const LDIndexLine& rop )
	{
		if ( m_index1==rop.m_index1 && m_index2==rop.m_index2 )
		{
			return true;
		}
		if ( m_index1==rop.m_index2 && m_index2==rop.m_index1 )
		{
			return true;
		}
		return false;
	}
	int getIndex1() const;
	void setIndex( int m_index1,int m_index2 );
	int getIndex2() const;

	bool hasIndex( int index )const;
	bool isEnabled()const;
	bool isHit( const LDPointList& form ,LDPoint p, float hitRange )const;
private:
	//必ず index1 < index2 の関係とする。代入時に自動調整される。
	int m_index1;
	int m_index2;

	LD_SERIALIZABLE;
};

QDebug operator<<( QDebug dbg, const LDIndexLine& line );

} // namespace live2d



