/**
 * 	TriangleUtilTestWidget.h
 *  2015/7/31
 *	Imai
 *  
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#ifndef TRIANGLEUTILTESTWIDGET_H
#define TRIANGLEUTILTESTWIDGET_H

#include <QWidget>
#include <private/LDMath_private.h>
namespace Ui {
class TriangleUtilTestWidget;
}

class TriangleUtilTestWidget : public QWidget
{
	Q_OBJECT
	
public:
	explicit TriangleUtilTestWidget(QWidget *parent = 0);
	~TriangleUtilTestWidget();
	void paintEvent(QPaintEvent *e);
	void keyPressEvent(QKeyEvent *e);
	
private:
	Ui::TriangleUtilTestWidget *ui;
	live2d::LDPoint m_s0;
	live2d::LDPoint m_s1;
	live2d::LDPoint m_s2;
	live2d::LDPoint m_t0;
	live2d::LDPoint m_t1;
	
	
};

#endif // TRIANGLEUTILTESTWIDGET_H
