TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    token.h \
    stoken.h \
    integer.h \
    double.h \
    openparen.h \
    closeparen.h \
    oper.h \
    constants.h \
    variable.h \
    function.h \
    Points.h \
    SVGgraph.h \
    invalidfuncexception.h \
    missingparenexception.h \
    missingoperatorexception.h \
    missingoperargumentexception.h

