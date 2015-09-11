#include <QString>
#include <QtTest>
#include "LDMatrix43.h"

namespace live2d
{
class LDMatrix43Test: public QObject
{
	Q_OBJECT
private Q_SLOTS:
	void identityTest();

	void setMatrixTest();

	void multTest();

	void translateTest();

	void scaleTest();

	void rotateXTest();

	void rotateYTest();

	void rotateZTest();

	void transformTest();

	void fromQuaterionTest();

	void getInverseTest();
};
} // namespace live2d
