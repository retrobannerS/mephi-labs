QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChooseWindow.cpp \
    dequewindow.cpp \
    hanoi.cpp \
    main.cpp \
    primenumbers.cpp \
    priorityqueuewindow.cpp \
    queuewindow.cpp \
    sequencewindow.cpp \
    set.cpp \
    stackwindow.cpp

HEADERS += \
    ChooseWindow.h \
    dequewindow.h \
    hanoi.h \
    primenumbers.h \
    priorityqueuewindow.h \
    queuewindow.h \
    sequencewindow.h \
    set.h \
    stackwindow.h

FORMS += \
    ChooseWindow.ui \
    dequewindow.ui \
    hanoi.ui \
    primenumbers.ui \
    priorityqueuewindow.ui \
    queuewindow.ui \
    sequencewindow.ui \
    set.ui \
    stackwindow.ui

INCLUDEPATH += \
    $$PWD/../../libs/lab3_lib/includes \
    $$PWD/../../libs/lab2_lib/includes

LIBS += \
    -L$$PWD/../../libs/lab3_lib/lib -llab3_library \
    -L$$PWD/../../libs/lab2_lib/lib -llab2_library


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
