QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    lab2.cpp \
    Tests/UnitTest.cpp \
    Tests/TestCluster.cpp \
    Tests/TestRunner.cpp \
    Tests/DynamicArrayTests/DynamicArrayTests.cpp \
    Tests/LinkedListTests/LinkedListTests.cpp \
    Tests/ArraySequenceTests/ArraySequenceTests.cpp \
    Tests/ListSequenceTests/ListSequenceTests.cpp \
    MyExceptions/TestFailedException.cpp


HEADERS += \
    lab2.h \
    Data_Classes/DynamicArray.hpp \
    Data_Classes/LinkedList.hpp \
    IEnumerators/IEnumerable.hpp \
    IEnumerators/IEnumerator.hpp \
    MyExceptions/TestFailedException.hpp \
    Options/Options.hpp \
    Sequences/Sequence.hpp \
    Sequences/ArraySequence.hpp \
    Sequences/ListSequence.hpp \
    Tests/TestRunner.hpp \
    Tests/DynamicArrayTests/DynamicArrayTests.hpp \
    Tests/LinkedListTests/LinkedListTests.hpp \
    Tests/ArraySequenceTests/ArraySequenceTests.hpp \
    Tests/ListSequenceTests/ListSequenceTests.hpp


FORMS += \
    lab2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
