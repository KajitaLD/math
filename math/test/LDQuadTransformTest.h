/**
 *
 *  2015/6/28
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include <QObject>

namespace live2d
{


class LDQuadTransformTest : public QObject
{
	Q_OBJECT
private Q_SLOTS:
	void simpleTransformTest();
	void transformTest();
	void inverseTransformTest();
	void rotationTest();

	void extendedTransformTest();
};


} // namespace live2d
