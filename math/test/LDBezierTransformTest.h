/**
 *
 *  2015/7/5
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include <QObject>

namespace live2d {

class LDBezierTransformTest : public QObject
{
	Q_OBJECT
private Q_SLOTS:
	void simpleTransformTest();
	void transformTest();
};

} // namespace live2d


