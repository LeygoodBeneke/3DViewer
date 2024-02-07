QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += core widgets

CONFIG += c++17 

LIBS += -lglut -lGL -lGLU

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    glwidget.cpp \
    ../model.cpp \
    ../parser.cpp \
    ../transformation.cpp \
    viewer.cpp

HEADERS += \
    glwidget.h \
    ../obj_data.h \
    ../parser.h \
    ../transformation.h \
    viewer.h

FORMS += \
    viewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
