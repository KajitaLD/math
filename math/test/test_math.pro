#-------------------------------------------------
#
# Project created by QtCreator 2014-11-30T15:14:12
#
#-------------------------------------------------


QT       += testlib

QT       += core gui

TARGET = QtMathTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include($$PWD/../../../../config/_config.pri)
include($$PWD/../src.pri)

INCLUDEPATH += \
    $$PWD/../ \
    $$E_COMMON \
    $$E_PROJECT/src/core/test/

SOURCES += \
	   LDMathUtilTest.cpp \
	   LDMatrix43Test.cpp \
	   LDMatrix44Test.cpp \
	   LDVector3Test.cpp \
	   LDQuatTest.cpp \
	   LDEulerAnglesTest.cpp \
    main.cpp \
    LDIndexLineListTest.cpp \
    TriangulationTest.cpp \
    LDGridTransformTest.cpp \
    LDQuadTransformTest.cpp \
    LDAffineTransformTest.cpp \
    LDTrianglListTest.cpp \
    LDBezierTransformTest.cpp \
    LDSimpleAffineTransformTest.cpp

HEADERS +=\
	   LDEulerAnglesTest.h \
	   LDMathUtilTest.h \
	   LDMatrix43Test.h \
	   LDMatrix44Test.h \
	   LDVector3Test.h \
	   LDQuatTest.h \
	    ../../test/TestUtil.h \
    LDIndexLineListTest.h \
    TriangulationTest.h \
    LDGridTransformTest.h \
    LDQuadTransformTest.h \
    LDAffineTransformTest.h \
    LDTrianglListTest.h \
    LDBezierTransformTest.h \
    LDSimpleAffineTransformTest.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"

# core/serialize
LIBS +=$$libFunc( serialize, $$E_PROJECT/bin)
PRE_TARGETDEPS+=$$libTargetFunc( serialize, $$E_PROJECT/bin)
INCLUDEPATH += $$E_CORE/serialize
DEPENDPATH += $$E_CORE/serialize



QMAKE_LFLAGS_DEBUG += /INCREMENTAL:NO
