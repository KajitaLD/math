/**
 *
 *  2015/5/24
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once

#include <QObject>

namespace live2d {

class LDIndexLineListTest : public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void serializeTest();
	void hitTest();
	void constructTest();
	
};

} // namespace live2d


