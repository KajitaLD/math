/**
 *
 *  2015/6/6
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include <QObject>

namespace live2d {

class LDGridTransformTest : public QObject
{
	Q_OBJECT
private Q_SLOTS:
	void serializeTest();
	void simpleTransformTest();
	void getQuadTest();
	void hitTest();
	void inverseTransformTest();
	void extendedTransformTest();
};

} // namespace live2d


