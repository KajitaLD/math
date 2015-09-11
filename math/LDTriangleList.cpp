/**
 *
 *  2015/5/24
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDTriangleList.h"
#include "PointUtil.h"
#include "LDMathUtil.h"

namespace live2d
{

LDTriangleList::LDTriangleList()
{

}

void LDTriangleList::update( const LDIndexLineList& lines )
{
	clear();
	for ( int i=0; i<lines.size(); i++ )
	{
		( *this )<<create( i,lines );
	}


}

void LDTriangleList::setClockWise( const LDPointList& form, ClockWise cw )
{
	for ( int i=0; i<size(); i++ )
	{
		( *this )[i].setClockWise( form,cw );
	}
}

LDTriangleList LDTriangleList::find( const LDIndexLine& line ) const
{
	LDTriangleList result;
	foreach ( const LDTriangle& t, *this )
	{
		if ( t.containsLine( line ) )
		{
			result.push_back( t );
		}
	}
	return result;
}

LDIndexLineList LDTriangleList::toIndexLineList() const
{
	//NOTE: もっと効率化できる気がするが、ボトルネックになったらやる
	LDIndexLineList lineList;
	for ( int i=0; i<this->size(); i++ )
	{
		LDTriangle tri= this->at( i );

		LDIndexLine line1= tri.getLine1();
		if ( ! lineList.hasIndexLine( line1 ) )
		{
			lineList.push_back( line1 );
		}

		LDIndexLine line2= tri.getLine2();
		if ( ! lineList.hasIndexLine( line2 ) )
		{
			lineList.push_back( line2 );
		}

		LDIndexLine line3= tri.getLine3();
		if ( ! lineList.hasIndexLine( line3 ) )
		{
			lineList.push_back( line3 );
		}


	}
	return lineList;

}

void LDTriangleList::removePoint( int pointIndex )
{
	for ( int i = 0; i < length(); )
	{
		auto t=at( i );
		if ( t.hasIndex( pointIndex ) )
		{
			removeAll( t );
		}
		else
		{
			i++;
		}
	}
}

QList<int> LDTriangleList::getOutlinePointIndices( const LDPointList& points ) const
{
	QList<int> result;

	// 外周をたどる。始点に戻ったら終了。
	int startIndex=math::PointUtil::findMinYPointIndex( points );

	Q_ASSERT(startIndex>=0);

	result.push_back(startIndex);

	int lastIndex=-1;
	int currentIndex=startIndex;

	for ( int i = 0; i < points.length(); ++i )
	{
		//現在の頂点と接続される点一覧を取得し、その中から進行方向に対してもっとも左側に位置するものを取得
		QList<int> related=getRelatedPointIndices( currentIndex );

		LDPoint lastPoint;
		LDPoint currentPoint=points[currentIndex];
		if ( lastIndex==-1 )
		{
			lastPoint=currentPoint-LDPoint(0,1);
		}
		else
		{
			lastPoint=points[lastIndex];
		}


		int nextIndex=-1;
		double minAngle=360;
		foreach (int targetIndex, related) {
			LDPoint targetPoint=points[targetIndex];
			if(targetIndex==lastIndex)
			{
				continue;
			}
			QVector2D v1(lastPoint-currentPoint);
			QVector2D v2(targetPoint-currentPoint);

			double angle = LDMathUtil::getAngle(v2,v1);
			if(angle<minAngle)
			{
				minAngle=angle;
				nextIndex=targetIndex;
			}
		}

		if(nextIndex==startIndex)
		{
			//一周した
			break;
		}
		result.push_back(nextIndex);

		lastIndex=currentIndex;
		currentIndex=nextIndex;
	}

	return result;
}

LDPointList LDTriangleList::getOutlinePoints(const LDPointList& points) const
{
	QList<int> indices=getOutlinePointIndices(points);

	LDPointList result;

	foreach (int index, indices) {
		LD_ASSERT_OUT_OF_INDEX(points,index);
		result.push_back(points[index]);
	}
	return result;
}

QPolygonF LDTriangleList::getOutlinePolygon(const LDPointList& points) const
{
	QList<int> indices=getOutlinePointIndices(points);

	QPolygonF result;

	foreach (int index, indices) {
		LD_ASSERT_OUT_OF_INDEX(points,index);
		result.push_back(points[index]);
	}
	return result;
}

LDTriangleList LDTriangleList::getRelatedTriangles( int pointIndex ) const
{
	LDTriangleList result;

	foreach ( const LDTriangle& t, *this )
	{
		if ( t.hasIndex( pointIndex ) )
		{
			result.push_back( t );
		}
	}

	return result;
}

LDIndexLineList LDTriangleList::getRelatedLines( int pointIndex ) const
{
	LDIndexLineList result;

	foreach ( const LDTriangle& t, *this )
	{
		LDIndexLineList lines=t.getRelatedLines( pointIndex );

		foreach ( const auto& line, lines )
		{
			result.push_back( line );
		}
	}

	return result;
}

QList<int> LDTriangleList::getRelatedPointIndices(int pointIndex) const
{
	QList<int> result;

	foreach ( const LDTriangle& t, *this )
	{
		if ( t.hasIndex( pointIndex ) )
		{
			int index1=t.getIndex1();
			int index2=t.getIndex2();
			int index3=t.getIndex3();
			if(index1!=pointIndex)
			{
				result.push_back(index1);
			}
			if(index2!=pointIndex)
			{
				result.push_back(index2);
			}
			if(index3!=pointIndex)
			{
				result.push_back(index3);
			}
		}
	}

	return result;
}

LDLineList LDTriangleList::getLines(const LDPointList& points) const
{
	return toIndexLineList().getLines(points);
}

//TODO 説明増やしてコード整理してください。あとテスト。
QList<LDTriangle> LDTriangleList::create( int index, const LDIndexLineList& lines )
{
	Q_ASSERT( lines.length() > index );

	QList<LDTriangle> indexs;
	int i_1= lines.at( index ).getIndex1();
	int i_2=lines.at( index ).getIndex2();


	for ( int i=index;; i++ )
	{
		if ( i>lines.size()-1 )
		{
			break;
		}
		if ( lines.at( i ).getIndex1()!=i_1 )
		{
			break;
		}
		int i_3=lines.at( i ).getIndex2();
		bool hit=false;
		for ( int j=i; j<lines.size(); j++ )
		{
			if ( lines.at( j ).getIndex1()==i_2 && lines.at( j ).getIndex2() == i_3 )
			{
				hit=true;
				break;
			}
		}
		if ( hit )
		{
			LDTriangle poly( i_1,i_2,i_3 );
			indexs.push_back( poly );
		}
	}
	return indexs;
}

//***************************************
// Serialize
//***************************************
template<class Archive>
void LDTriangleList::serialize( Archive& ar, unsigned int /*version*/ )
{
	LD_SERIALIZE_SUPER( ar, QList );
}
LD_SERIALIZE_IMPL( LDTriangleList );

} // namespace live2d

LD_SERIALIZE_CHILD_CLASS_CPP( live2d::LDTriangleList )
