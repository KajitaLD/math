/**
 *
 *  2015/8/2
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once
#include "private/LDMath_private.h"
#include "LDIndexLineList.h"
#include "LDSerialize.h"
#include "LDTriangleList.h"

namespace live2d
{

class LDUvMesh
{
public:
	LDUvMesh();

	void copyFrom( const LDUvMesh& src );

	LDPoint getPoint( int index ) const;
	int getVertexCount() const;
	bool verify()const;

	void reset();

	void dump( int nest=0 )const;
	void dumpDetail( int nest=0 )const;



	int getTriangleCount() const;
	LDPoint getUv( int index )const;
	LDTriangle getTriangle( int index )const;

	LDPointList getPointList() const;
	LDTriangleList getTriangles() const;
	LDUvMap getUvMap() const;

	bool isHit( const LDPoint& pt )const;

	void replacePoint( int index,LDPoint pt );
	void replaceForm( const LDPointList& form );

	bool existsLine( LDIndexLine line )const; //既にある線かチェックする
	int getLineCount() const;
	LDIndexLine getLine( int index )const;
	LDIndexLineList getLines() const;



	void replaceUv( int index,LDPoint uv );

	//追加。UV経由での追加しかできない。Positionは自動で計算される
	void addUv( LDPoint uv,bool clamp=true );
	void addUv( float u,float v,bool clamp=true );

	void insertUv( int index,LDPoint uv );
	bool removeUv( LDPoint uv );

	void addLine( LDIndexLine line );
	void addLine( int index1,int index2 );

	bool deleteLine( LDIndexLine line );
	bool deleteLine( int vertexIndex );

	void updateLinesForPointInsert( int pointIndex ); //NOTE： もっと分かりやすい名前にする
	void updateLinesForPointDeleted( int pointIndex );

	void updateUvMap( QSizeF ImageSize );
	void updateLines();
	void updatePolygons();

	void triangulation();

	void setLines( const LDIndexLineList& value );
	void setUvMap( const LDUvMap& value );
	void setTriangles( const LDTriangleList& value );

	void replacePointList( const LDPointList& value );

	bool operator ==( const LDUvMesh& rop );
private:
	LDPoint getCalcAddVertex( LDPoint uv ) const;

private:
	LDPointList m_points;//UV上にマッピングされた点。
	LDUvMap m_uvMap;

	LDIndexLineList m_lines;
	LDTriangleList m_triangles;

	LD_SERIALIZABLE;
};

} // namespace live2d


