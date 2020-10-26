QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_DEBUG += -Og
QMAKE_CXXFLAGS += -std=c++17

QT += core
QT += widgets
QT += network


# DEBUG CONFIG
CONFIG(debug, debug|release) {
  message("DEBUG")
  CONFIG += console
  TARGET = mariongicieldebug
  DESTDIR = runnable/debug
  Debug:OBJECTS_DIR = debug/.obj
  Debug:MOC_DIR = debug/.moc
  Debug:RCC_DIR = debug/.rcc
  Debug:UI_DIR = debug/.ui
}

# RELEASE CONFIG
CONFIG(release, debug|release) {
  message("RELEASE")
  TARGET = mariongiciel
  DESTDIR = runnable/release
  Release:OBJECTS_DIR = release/.obj
  Release:MOC_DIR = release/.moc
  Release:RCC_DIR = release/.rcc
  Release:UI_DIR = release/.ui
}

win32 | win64 {
    #mingw32-make install
    #your lib path
    LIBDIR = D:\Qt\5.13.2\mingw73_64

    #RELEASE DEP
    DESTDIR = $${OUT_PWD}\runnable\release
    DLL.path    = $${DESTDIR}
    DLL.files   += $${LIBDIR}\bin\Qt5Gui.dll
    DLL.files   += $${LIBDIR}\bin\Qt5Network.dll
    DLL.files   += $${LIBDIR}\bin\Qt5Core.dll
    DLL.files   += $${LIBDIR}\bin\Qt5Widgets.dll
    DLL.files   += $${LIBDIR}\bin\libstdc++-6.dll
    DLL.files   += $${LIBDIR}\bin\libgcc_s_seh-1.dll
    DLL.files   += $${LIBDIR}\bin\libwinpthread-1.dll
    INSTALLS       += DLL

    #OPENSSL for WINx64
    LIBDIR = D:\Qt\Tools\OpenSSL\Win_x64
    openssl.path    = $${DESTDIR}
    openssl.files   += $${LIBDIR}\bin\libcrypto-1_1-x64.dll
    openssl.files   += $${LIBDIR}\bin\libssl-1_1-x64.dll
    INSTALLS += openssl

    #PLUGINS
    platforms.path    = $${DESTDIR}\platforms
    platforms.files   += $${LIBDIR}\plugins\platforms\*
    imageformats.path    = $${DESTDIR}\imageformats
    imageformats.files   += $${LIBDIR}\plugins\imageformats\*
    INSTALLS       += platforms imageformats

    #RCS
    rcs.path    = $${DESTDIR}\rcs
    rcs.files   += $${OUT_PWD}\..\rcs\config
    rcs.files   += $${OUT_PWD}\..\rcs\css
    rcs.files   += $${OUT_PWD}\..\rcs\icon

    INSTALLS += rcs

    #RCS
    sources.path    = $${DESTDIR}\sources
    sources.files   += $${OUT_PWD}\..\mariongiciel\*
    INSTALLS += sources

#DEBUG DEP
DESTDIR = $${OUT_PWD}\runnable\debug
DLLD.path    = $${DESTDIR}
DLLD.files   += $${LIBDIR}\bin\Qt5Guid.dll
DLLD.files   += $${LIBDIR}\bin\Qt5Networkd.dll
DLLD.files   += $${LIBDIR}\bin\Qt5Cored.dll
DLLD.files   += $${LIBDIR}\bin\Qt5Widgetsd.dll
DLLD.files   += $${LIBDIR}\bin\libstdc++-6.dll
DLLD.files   += $${LIBDIR}\bin\libgcc_s_seh-1.dll
DLLD.files   += $${LIBDIR}\bin\libwinpthread-1.dll
INSTALLS       += DLLD

#OPENSSL for WINx64
LIBDIR = D:\Qt\Tools\OpenSSL\Win_x64
OPENSSLDLL.path    = $${DESTDIR}
OPENSSLDLL.files   += $${LIBDIR}\bin\libcrypto-1_1-x64.dll
OPENSSLDLL.files   += $${LIBDIR}\bin\libssl-1_1-x64.dll
INSTALLS += OPENSSLDLL
}

RC_ICONS = api.ico

SOURCES += \
    core/account.cpp \
    core/filter.cpp \
    core/iomanagement.cpp \
    core/network/authentication.cpp \
    core/network/referencial.cpp \
    core/network/request.cpp \
    core/network/search.cpp \
    core/referencialdata.cpp \
    core/response.cpp \
    core/searchquery.cpp \
    gui/accountwidget.cpp \
    gui/dropdown/dropdown.cpp \
    gui/mainwindow.cpp \
    gui/menutoolbar.cpp \
    gui/referencialdialog.cpp \
    gui/referencialwidget.cpp \
    gui/searchparammanager.cpp \
    gui/searchwidget.cpp \
    main.cpp

HEADERS += \
    core/account.h \
    core/crypto.h \
    core/filter.h \
    core/iomanagement.h \
    core/network/authentication.h \
    core/network/referencial.h \
    core/network/request.h \
    core/network/search.h \
    core/referencialdata.h \
    core/response.h \
    core/searchquery.h \
    core/utility.h \
    global.h \
    gui/accountwidget.h \
    gui/dropdown/dropdown.h \
    gui/mainwindow.h \
    gui/menutoolbar.h \
    gui/referencialdialog.h \
    gui/referencialwidget.h \
    gui/searchparammanager.h \
    gui/searchwidget.h

#LIBS += -LD:\Qt\Tools\OpenSSL\Win_x64\bin -llibcrypto-1_1-x64.dll -llibssl-1_1-x64.dll
#INCLUDEPATH += D:\Qt\Tools\OpenSSL\Win_x64\include\openssl

#INCLUDEPATH += D:/Qt/Tools/OpenSSL/Win_x64/include/
#LIBS += -LD:/Qt/Tools/OpenSSL/Win_x64/lib -llibssl
#LIBS += -LD:/Qt/Tools/OpenSSL/Win_x64/lib -llibcrypto

INCLUDEPATH += D:/Qt/Tools/OpenSSL/Win_x64/include/
LIBS += -LD:/Qt/Tools/OpenSSL/Win_x64/bin -llibssl-1_1-x64
LIBS += -LD:/Qt/Tools/OpenSSL/Win_x64/bin -llibcrypto-1_1-x64
