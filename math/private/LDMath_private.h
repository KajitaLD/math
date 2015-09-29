/**
 *
 *  2015/5/21
 *	aso
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#pragma once

#include <math.h>

#include <QtMath>
#include <QVector>
#include <QPointF>
#include <QLine>
#include <QPolygon>
#include <QVector2D>
#include <QString>
#include <QDebug>

namespace live2d {

//描画オブジェクトの形状
using ld_radian = double;

using LDPoint = QPointF;
using LDUvPoint = QPointF;//0-1区間であることを明示したいときに使う
using LDLine = QLineF;
using LDRect = QRect;
using LDRectF = QRectF;
using LDBounds = QPair<QRectF,ld_radian>;//Boundsは回転する矩形とする。
using LDPolygon =QPolygonF;
using LDPointList = QVector<LDPoint>;
using LDUvPointList = QVector<LDUvPoint>;
using LDUvMap = QVector<LDUvPoint>;
using LDLineList = QVector<LDLine>;

} // namespace live2d



