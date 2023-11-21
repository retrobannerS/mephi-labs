QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    lab1.cpp

HEADERS += \
    lab1.h

FORMS += \
    lab1.ui

INCLUDEPATH += \
    $$PWD/../../../libs/lab3_lib/includes \
    $$PWD/../../../libs/lab2_lib/includes \
    $$PWD/../../../libs/lab5_lib/includes

LIBS += \
    -L$$PWD/../../../libs/lab3_lib/lib/lab3_library_mac.a \
    -L$$PWD/../../../libs/lab2_lib/lib/lab2_library_mac.a



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
