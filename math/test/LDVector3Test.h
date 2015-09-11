#include <QString>
#include <QtTest>
#include "LDVector3.h"

namespace live2d
{
class LDVector3Test: public QObject
{
	Q_OBJECT
public:
	void normalizeTest();

	void lengthTest();

	void dotProductTest();

	//====================================================
	//	非メンバ関数のテスト
	//====================================================
	void crossProductTest();

	void dotTest();

	void distanceTest();

	void blendTest();
};
} // namespace live2d
