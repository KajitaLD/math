/**
 * 	
 *  2015/7/2
 *	Imai
 *  
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include <QObject>

namespace live2d {
class LDTrianglListTest: public QObject
{
	Q_OBJECT
private Q_SLOTS:
	void findTest_simple();
	void toIndexLineListTest_simple();
	void getOutlinePointIndicesTest_simple();
	void getOutlinePointsTest_simple();
	void getOutlinePolygonTest_simple();
	void getRelatedTrianglesTest_simple();
	void getRelatedLinesTest_simple();
	void getRelatedPointIndicesTest_simple();
	
	
};


} // namespace live2d
