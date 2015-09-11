/**
 *
 *  2015/8/1
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once
#include <QObject>



namespace live2d {

class LDSimpleAffineTransformTest: public QObject
{
	Q_OBJECT
private Q_SLOTS:
	void serializeTest();
	void simpleTransformTest();
	void inverseTransformTest();
};

} // namespace live2d


