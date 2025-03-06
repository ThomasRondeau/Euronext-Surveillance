QT += core gui widgets charts network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += $$PWD/include


#Lien vers lib Json nécéssaire aux appels de l'API, ici path pour mac
INCLUDEPATH += /opt/homebrew/Cellar/jsoncpp/1.9.6/include
LIBS += -L/opt/homebrew/Cellar/jsoncpp/1.9.6/lib -ljsoncpp

#Lien vers lib curl nécéssaire aux appels de l'API, ici path pour mac
INCLUDEPATH += /opt/homebrew/opt/curl/include
LIBS += -L/opt/homebrew/opt/curl/lib -lcurl


# Include all .cpp files from the src folder
SOURCES += \
    SearchableTableWidget.cpp \
    Surveillancewindow.cpp \
    adminwindow.cpp \
    instrumentmanagerwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    loginwindow.cpp \
    APIManager.cpp \
    multipleViewsWindow.cpp \
    traderwindow.cpp

# Include all .h files from the include folder
HEADERS += \
    SearchableTableWidget.h \
    Surveillancewindow.h \
    adminwindow.h \
    instrumentmanagerwindow.h \
    mainwindow.h \
    loginwindow.h \
    APIManager.h \
    multipleViewsWindow.h \
    traderwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
