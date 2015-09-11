/**
 * 	
 *  2015/7/31
 *	Imai
 *  
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include <QApplication>

#include "TriangleUtilTestWidget.h"
int main( int argc, char* argv[] )
{
	QApplication a( argc, argv );
	
	TriangleUtilTestWidget w;
	w.show();

	return a.exec();
}
