TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    definitions/consts.c \
    printing/print.c \
    processing/parameters.c \
    warehouse/warehouse.c \
    processing/loader.c \
    processing/processor.c

LIBS += -lpng
DESTDIR = ../[bin]

HEADERS += \
    definitions/messages.h \
    definitions/types.h \
    xmacro/xerrors.h \
    definitions/consts.h \
    printing/print.h \
    xmacro/xparameters.h \
    processing/parameters.h \
    definitions/helpers.h \
    warehouse/warehouse.h \
    processing/loader.h \
    processing/processor.h
