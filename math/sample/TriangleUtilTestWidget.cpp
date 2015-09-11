/**
 * 	TriangleUtilTestWidget.cpp
 *  2015/7/31
 *	Imai
 *  
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#include "TriangleUtilTestWidget.h"
#include "ui_TriangleUtilTestWidget.h"
#include "TriangleUtil.h"

#include <LDMathUtil.h>
#include <QKeyEvent>
#include <QPainter>
#include <LDMathUtil.h>
using namespace live2d;
using namespace live2d::math;

TriangleUtilTestWidget::TriangleUtilTestWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TriangleUtilTestWidget),
	m_s0(0+30,0+30),
	m_s1(100+30,0+30),
	m_s2(50+30,50+30),
	m_t0(150+30,0+30),
	m_t1(250+30,0+30)
{
	ui->setupUi(this);
}

TriangleUtilTestWidget::~TriangleUtilTestWidget()
{
	delete ui;
}

double getAngle(QVector2D v1 , QVector2D v2){
	double q1 = atan2( v1.y() , v1.x() ) ;
	double q2 = atan2( v2.y() , v2.x() ) ;
	double ret =  q2 - q1  ;//v2の角度からv1 の角度を引く

	if( ret < 0 ) ret += 2*LDMathUtil::PI ;//0より小さければ、360度足す
	return ret ;
}
double AngleOf2Vector(QVector2D A, QVector2D B )
{
	//　※ベクトルの長さが0だと答えが出ませんので注意してください。

	//ベクトルAとBの長さを計算する
	double length_A = A.length();
	double length_B = B.length();

	//内積とベクトル長さを使ってcosθを求める
	double cos_sita = QVector2D::dotProduct(A,B) / ( length_A * length_B );

	//cosθからθを求める
	double sita = acos( cos_sita );	

	//ラジアンでなく0～180の角度でほしい場合はコメント外す
	//sita = sita * 180.0 / PI;

	return sita;
}

void TriangleUtilTestWidget::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);	
	QPen pen;pen.setWidth(6);
	painter.setPen(pen);
		
	QVector2D s0(m_s0);
	QVector2D s1(m_s1);
	QVector2D s2(m_s2);	
	QVector2D t0(m_t0);
	QVector2D t1(m_t1);
	QVector2D ss2=s2+t0-s0;
	//float angle=LDMathUtil::getAngle(s1-s0,t1-t0);	
//	qDebug()<<getAngle(s1-s0,t1-t0);
//	qDebug()<<
			   float angle=AngleOf2Vector(s1-s0,t1-t0);
	
	LDPoint sss2=LDMathUtil::rotatePoint(m_t0,ss2.toPointF(),angle);
	painter.drawPoint(sss2);
	
	LDPoint _t2=	TriangleUtil::getSimilarityTrianglePoint(m_s0,m_s1,m_s2,m_t0,m_t1);
	painter.setPen(Qt::red);
	painter.drawLine(m_s0,m_s1);
	painter.drawLine(m_s1,m_s2);
	painter.drawLine(m_s2,m_s0);
	painter.setPen(Qt::blue);
	painter.drawLine(m_t0,m_t1);
	painter.drawLine(m_t1,_t2);
	painter.drawLine(_t2,m_t0);

	painter.setPen(Qt::black);
	painter.drawText(m_s0,"s0");	
	painter.drawText(m_s1,"s1");	
	painter.drawText(m_s2,"s2");	
	painter.drawText(m_t0,"t0");	
	painter.drawText(m_t1,"t1");	
	painter.drawText(_t2,"_t2");	
	
	
}

void TriangleUtilTestWidget::keyPressEvent(QKeyEvent *e)
{
	if(e->key()==Qt::Key_Q)
	{
		if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
			m_s0.setX(m_s0.x()+1);
		else
			m_s0.setX(m_s0.x()-1);			
	}
	if(e->key()==Qt::Key_W)
	{
		if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
			m_s0.setY(m_s0.y()+1);
		else
			m_s0.setY(m_s0.y()-1);
	}

	if(e->key()==Qt::Key_E)
	{
		if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))		
		m_s1.setX(m_s1.x()+1);
		else
			m_s1.setX(m_s1.x()-1);			
	}
	if(e->key()==Qt::Key_R)
	{
		if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))		
		m_s1.setY(m_s1.y()+1);
		else
			m_s1.setY(m_s1.y()-1);
			
	}

	if(e->key()==Qt::Key_T)
	{
		if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))		
		m_s2.setX(m_s2.x()+1);
		else
			m_s2.setX(m_s2.x()-1);
			
	}
	if(e->key()==Qt::Key_Y)
	{
		if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))		
		m_s2.setY(m_s2.y()+1);
		else
			m_s2.setY(m_s2.y()-1);
			
	}


	if(e->key()==Qt::Key_U)
	{
		if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))		
		m_t0.setX(m_t0.x()+1);
		else
			m_t0.setX(m_t0.x()-1);
			
	}
	if(e->key()==Qt::Key_I)
	{
		if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))		
		m_t0.setY(m_t0.y()+1);
		else
			m_t0.setY(m_t0.y()-1);
	}

	if(e->key()==Qt::Key_O)
	{
		if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))		
		m_t1.setX(m_t1.x()+1);
		else
			m_t1.setX(m_t1.x()-1);
			
	}
	if(e->key()==Qt::Key_P)
	{
		if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))		
		m_t1.setY(m_t1.y()+1);
		else
			m_t1.setY(m_t1.y()-1);
	}
	

	
	update();
	
}
