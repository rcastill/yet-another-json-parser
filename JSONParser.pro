TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cc \
    indexbuffer.cc \
    buffer.cc \
    tokenizer.cc \
    parser.cc \
    jsonobject.cc \
    jsonarray.cc \
    jsonvalue.cc \
    parser_util.cc

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    indexbuffer.h \
    types.h \
    buffer.h \
    tokenizer.h \
    parser.h \
    jsonobject.h \
    jsonarray.h \
    jsonvalue.h \
    parser_util.h

