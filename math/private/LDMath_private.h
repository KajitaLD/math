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

using LDPoint = QPointF;
using LDLine = QLineF;
using LDRect = QRect;
using LDRectF = QRectF;
using LDPolygon =QPolygonF;
using LDPointList = QVector<LDPoint>;
using LDUvMap = QVector<LDPoint>;
using LDLineList = QVector<LDLine>;

} // namespace live2d



