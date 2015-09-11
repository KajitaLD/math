/**
 *
 *  2015/5/21
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "TriangleUtil.h"
#include "Triangulation.h"
#include <vector>
#include <QSet>

//QSet<QPoint>はデフォルトでは有効ではない?
//http://stackoverflow.com/questions/24498993/cannot-use-qpoint-as-qhash-key
//inline uint qHash (const QPoint & key)
//{
//	return qHash (static_cast <qint64> (key.x () ) << 32 | key.y () );
//}
inline uint qHash (const QPointF & key)
{
	return qHash ( key.x () );//適当。xだけでハッシュ
}



namespace live2d
{
namespace math
{

LDTriangleList Triangulation::exec( LDPointList form )
{
	//重複チェック。
	Q_ASSERT(form.length()==form.toList().toSet().size());

	LDTriangleList result;
	int formSize = form.size();

	if (formSize<2) {
		return result;
	}

	//A1) 点群を包含する十分大きな三角形(super triangle)を追加する
	LDPolygon hugeTriangle = TriangleUtil::getHugeTriangle( form );

	int index1=form.length();
	int index2=index1+1;
	int index3=index2+1;

	form.append( hugeTriangle[0] );
	form.append( hugeTriangle[1] );
	form.append( hugeTriangle[2] );

	LDTriangle t( index1,index2,index3 );
	result.push_back( t );

	//A2) i番目の頂点piを三角形分割図形に追加

	for ( int i = 0; i < formSize; i++ )
	{
		LDPoint pi = form[i];

		//  A2-1) 	piを含む三角形ABCを発見し, この三角形をAB pi, BC pi, CA pi の3個の三角形に分割．
		triangulationFromPoint( form,pi,result );
	}

	// 最後に、外部三角形の頂点を削除
	result.removePoint(index1);
	result.removePoint(index2);
	result.removePoint(index3);


	return result;
}

void Triangulation::triangulationFromPoint( const LDPointList& form, const LDPoint& p, LDTriangleList& triangles )
{
	//  A2-1) 	piを含む三角形ABCを発見し, この三角形をAB pi, BC pi, CA pi の3個の三角形に分割．
	//  		この時, 辺AB, BC, CAをスタックSに積む (最初の一点のときには，super triangleが見つかる)
	for ( int i = 0; i < triangles.length(); )
	{
		LDTriangle t=triangles[i];

		if ( !TriangleUtil::containsPoint( t.toPolygon( form ),p ) )
		{
			//対象の三角形の外側なら次へ
			i++;
			continue;
		}

		// 古い三角形をリストから削除して、分割した三角形を追加
		triangles.removeAll( t );

		int index=form.indexOf(p);
		Q_ASSERT(index>=0);
		triangles.push_back( LDTriangle( index,t.getIndex1(),t.getIndex2() ) );
		triangles.push_back( LDTriangle( index,t.getIndex2(),t.getIndex3() ) );
		triangles.push_back( LDTriangle( index,t.getIndex3(),t.getIndex1() ) );

		//TODO すでにある線分で制限する機能が未移植
		//		if ( limitLineList.size() != 0 )
		//		{
		//			flipCheckWithLimit( t.p1, t.p2, t.p3 , pg );
		//		}
		//		else
		//		{
		optimizePolygonSeparate( form, t, triangles );
		//		}

	}
}

void Triangulation::optimizePolygonSeparate(const LDPointList& form, LDTriangle firstTriangle, LDTriangleList& triangles){
	LDIndexLineList uncheckedLines;
	uncheckedLines.push_back(firstTriangle.getLine1());
	uncheckedLines.push_back(firstTriangle.getLine2());
	uncheckedLines.push_back(firstTriangle.getLine3());

	//A2-2) スタックSが空になるまで以下を繰り返す
	while (uncheckedLines.size() != 0) {
		//A2-2-1) スタックSの一番上のedgeをpopする．これを辺ABとする
		LDIndexLine lineAB = uncheckedLines.takeLast();

		//線と接する2つの三角形を取得
		LDTriangleList relatedTriangles = triangles.find(lineAB);

		//外周はチェックしない
		if (relatedTriangles.size() ==1)
			continue;

		//三角形がダブってるのは不正。隣接0もなにかおかしい
		Q_ASSERT(relatedTriangles.size()==2);

		//A2-2-2) 辺ABを含む2個の三角形をABCとABDとする
		// if(三角形ABCの外接円内にDが入 る) 辺ABをflipし，辺AD/DB/BC/CAをスタックSにpushする
		//else 何もしない
		LDTriangle triangleABC = relatedTriangles.at(0);
		LDTriangle triangleABD = relatedTriangles.at(1);

		int index=triangleABD.getIndexWithoutLine(lineAB);
		Q_ASSERT(form.length()>index);
		LDPoint pd = form[index];

		// 外接円を求める
		LDCircle c = LDCircle::getCircumscribedCirclesOfTriangle(form,triangleABC);
		double dist=PointUtil::distance(c.center, pd);

		//誤差の範囲ならフリップしない
		if ( dist < c.radius && qAbs(c.radius-dist)>0.00001) {
			//不正な辺
			uncheckedLines << flipTriangles(triangleABC, triangleABD, lineAB, triangles);
		}
	}
}

LDIndexLineList Triangulation::flipTriangles(LDTriangle ta, LDTriangle tb, LDIndexLine l, LDTriangleList& triangles) {
	Q_ASSERT(!(ta==tb));
	Q_ASSERT(ta.isSharedLine(tb));

	LDIndexLineList uncheckedLines;

	//指定の線で繋がっていない点を取得
	int index1 = ta.getIndexWithoutLine(l);
	int index2 = tb.getIndexWithoutLine(l);

	LDTriangle tc(index1,index2,l.getIndex1());
	LDTriangle td(index1,index2,l.getIndex2());

	triangles.removeAll(ta);
	triangles.removeAll(tb);
	triangles.push_back(tc);
	triangles.push_back(td);

	uncheckedLines.push_back(LDIndexLine(index1,l.getIndex1()));
	uncheckedLines.push_back(LDIndexLine(index2,l.getIndex1()));
	uncheckedLines.push_back(LDIndexLine(index1,l.getIndex2()));
	uncheckedLines.push_back(LDIndexLine(index2,l.getIndex2()));

	return uncheckedLines;
}



} // namespace math
} // namespace live2d

