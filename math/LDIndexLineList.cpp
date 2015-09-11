/**
 *
 *  2015/5/24
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "LDIndexLineList.h"

namespace live2d {

namespace {

bool letssThan( const LDIndexLine & e1, const LDIndexLine & e2 )
{
   if(e1.getIndex1()<e2.getIndex1())
	   return true;
   if(e1.getIndex1()==e2.getIndex1())
	   if(e1.getIndex2()<e2.getIndex2())
		   return true;
   return false;
}
}

LDIndexLineList::LDIndexLineList()
{
}

LDIndexLineList::LDIndexLineList(QList<int> indices)
{
	Q_ASSERT(indices.length()>2);

	for (int i = 0; i < indices.length()-1; ++i) {
		LDIndexLine line(indices[i],indices[i+1]);
		push_back(line);
	}
	LDIndexLine last(indices.last(),indices.first());
	push_back(last);
}

bool LDIndexLineList::hasIndexLine(LDIndexLine line)
{

	for(int i=0;i<this->size();i++)
	{
		if(line==this->at(i))//NOTE this->at(i) ==line だとコンパイルエラー
			return true;		
	}
	return false;
}

void LDIndexLineList::sort()
{
	qSort(begin(),end(),letssThan);
}

bool LDIndexLineList::isHit(const LDPointList &form, LDPoint p, float hitRange)
{
	for(int i=0;i<this->size();i++)
	{
		if(this->at(i).isHit(form,p,hitRange))
		{
			return true;
		}					
	}
	return false;
}

LDLineList LDIndexLineList::getLines(const LDPointList& points) const
{
	LDLineList result;

	for(int i=0;i<size();i++)
	{
		int index1=this->at(i).getIndex1();
		int index2=this->at(i).getIndex2();
		LDPoint point1=points.at(index1);
		LDPoint point2=points.at(index2);
		result.push_back(LDLine(point1,point2));
	}
	return result;
}



//***************************************
// Serialize
//***************************************
template<class Archive>
void LDIndexLineList::serialize( Archive& ar, unsigned int /*version*/ )
{
	LD_SERIALIZE_SUPER(ar, QList );
}
LD_SERIALIZE_IMPL(LDIndexLineList);

} // namespace live2d

LD_SERIALIZE_CHILD_CLASS_CPP(live2d::LDIndexLineList)
