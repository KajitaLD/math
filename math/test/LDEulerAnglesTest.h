#include <QString>
#include <QtTest>
#include "LDEulerAngles.h"
#include "LDMathUtil.h"
#include "LDQuat.h"
#include "LDMatrix44.h"

namespace live2d
{

class LDEulerAnglesTest: public QObject
{
	Q_OBJECT
private Q_SLOTS:
	void canonizeTest();
	void fromObjectToInertialQuaternionTest();
	void fromInertialToObjectQuaternionTest();
	void fromWorldToObjectMatrixTest();
};

} // namespace live2d
