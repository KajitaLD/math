include(../../../config/_config.pri)
include(../../../config/_config_lib.pri)

include(src.pri)
QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = math

INCLUDEPATH += $$PWD/../core/ \
		$$PWD/../common/	\



# core/serialize
LIBS +=$$libFunc( serialize, $$E_PROJECT/bin)
PRE_TARGETDEPS+=$$libTargetFunc( serialize, $$E_PROJECT/bin)
INCLUDEPATH += $$E_CORE/serialize
DEPENDPATH += $$E_CORE/serialize
