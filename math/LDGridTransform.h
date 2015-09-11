/**
 *
 *  2015/6/6
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once
#include "private/LDMath_private.h"
#include "LDMathUtil.h"
#include "LDSerialize.h"
#include "LDQuadTransform.h"
#include "LDIndexLineList.h"

namespace live2d
{
class LDAffineTransform;

/**
 * 格子状に並んだ変形のための点列
 *
 * 頂点の並び
 * 0 1 2 3
 * 4 5 6 7
 * 8 9 10 11
 */
class LDGridTransform
{
public:
	LDGridTransform(float x=0,float y=0,float width=1,float height=1,int row=1,int col=1);

	LDGridTransform(const LDPoint& topLeft,const LDPoint& bottomRight,int row=1,int col=1);

	//時計回りに4点
	LDGridTransform(const LDPoint& topLeft,const LDPoint& topRight,const LDPoint& bottomRight,const LDPoint& bottomLeft,int row=1,int col=1);

	int getRow()const;
	int getColumn()const;

	//配列の頂点の長さ。row+1
	int getRowArrayLength()const;
	int getColumnArrayLength()const;

	//平面上の点を変換した結果を返す。pは基本0..1の範囲
	LDPoint transform( const LDPoint& pt ,bool clip=false)const;
	LDPointList transform(const LDPointList& points,bool clip=false)const;

	LDPoint inverseTransform(const LDPoint& pt,bool clip=false)const;
	LDPointList inverseTransform(const LDPointList& points,bool clip=false)const;

	//Grid自体を変換した結果を返す。基本0..1の範囲
	LDGridTransform transform(const LDGridTransform& grid,bool clip=false)const;

	//Affine変換を変換した結果を返す
	LDAffineTransform transform(const LDAffineTransform& affine,bool clip=false)const;



	//最左の列からの内分率。2分割で内分率0.6であれば、結果は0.1
	double getRateXFromLeftCol( double rate )const;
	double getRateYFromAboveRow( double rate )const;
	int getIncludingColumnNo( double rate )const;
	int getIncludingRowNo( double rate )const;

	QPoint getQuadIndex( const LDPoint& t )const;
	LDPoint getLocalPoint( const LDPoint& t)const;//Gridの内分率からQuadのローカルな内分率を取得する

//	LDPoint getMappingFrom( int row,int col,const LDPoint& map )const;
	QPoint getMapedQuadIndex( const LDPoint& map )const;

	bool isOutside( int row,int col)const;
	LDQuadTransform getQuadTransform( int row,int col )const;
	LDQuadTransform createOutsideQuadTransform( int row,int col )const;
	LDQuadTransform getOutlineQuadTransform()const;

	//格子番号から正規化された点を取得
	LDPoint getNormalizedPoint( int row,int col )const;

	//格子番号からマッピングされた点を取得
	LDPoint getPoint( int row,int col )const;
	LDPoint getPoint( int index )const;
	int getPointIndex( int row,int col )const;

	LDLine getLine(const LDIndexLine& line)const;
	LDIndexLine getIndexLine(int row1,int col1,int row2,int col2)const;


	QList<QList<LDPoint> > getGridPoints() const;
	void setGridPoints( const QList<QList<LDPoint> >& value );

	//四角形の状態を保っているか。保っているなら自由に分割可能である。
	bool isRectangle()const;

	void setDivide(int row,int col);
	void setPoint(int row,int col,const LDPoint& pt);
	void setPointX(int row,int col,float x);
	void setPointY(int row,int col,float y);

	LDPointList toForm()const;
	void setForm(const LDPointList& value);
	int getPointCount()const;

	//外周の頂点インデックスを取得。(row,col)(0,0)が一番小さい点から時計周りで取得。
	QList<int> getOutlinePointIndices()const;
	LDIndexLineList getIndexOutline()const;
	LDLineList getOutline()const;
	LDPointList getOutlinePoints()const;
	QPolygonF getOutlinePolygon()const;

	QList<int> getInnerLinePointIndices()const;
	LDIndexLineList getInnerIndexLines()const;
	LDLineList getInnerLines()const;


	//外周の周辺で判定
	bool isHitOutline(const LDPoint& pt, float hitRange)const;


	LDRectF getBounds()const;

	//矩形に含まれるかどうかの軽量な簡易当たり判定
	bool isPreHit(const LDPoint& pt,float hitRange=0)const;

	LDGridTransform createExtendedGrid(int extend=1)const;

	void copyFrom(const LDGridTransform& src);
	void copyFrom(const LDGridTransform& src,int row,int col);//指定位置からのコピー

private:
	void clearBoundsCache();

private:
	QList<QList<LDPoint>> m_gridPoints;
	LDRectF m_originRect;

	//当たり判定最適化のため、編集のない間は矩形を使いまわす
	mutable LDRectF m_cacheBounds;

	LD_SERIALIZABLE;
};

bool operator ==( const LDGridTransform& a , const LDGridTransform& b ) ;
bool operator !=( const LDGridTransform& a , const LDGridTransform& b ) ;

QDebug operator<<( QDebug dbg, const LDGridTransform& grid );

} // namespace live2d


