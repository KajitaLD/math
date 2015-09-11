#include <QString>
#include <QtTest>
#include "LDMathUtil.h"
#include "LDQuat.h"

namespace live2d
{
class LDQuatTest: public QObject
{
	Q_OBJECT
private Q_SLOTS:
	void getAxisTest();

	void setToRotationArcTest();

	void setToRotateObjectToInertialTest();

	void setToRotateInertialToObjectTest();

	void slerpTest();

	void mySlerpTest();

	void powTest();

	void setToRotateAxisTest();

	void normalizeTest();
};
} // namespace live2d
