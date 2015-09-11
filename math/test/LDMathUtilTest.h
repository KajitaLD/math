#include <QString>
#include <QtTest>
#include "LDMathUtil.h"

namespace live2d
{
class LDMathUtilTest: public QObject
{
	Q_OBJECT

private Q_SLOTS:
	void wrapPiTest();
	void getAngleDiffTest();
	void safeAcosTest();
	void sinCosTest();
};
} // namespace live2d
