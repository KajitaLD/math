#include <QString>
#include <QtTest>
#include "LDMatrix44.h"

namespace live2d
{
class LDMatrix44Test: public QObject
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

	void serializeTest();
};
} // namespace live2d
