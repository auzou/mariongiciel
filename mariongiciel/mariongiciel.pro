QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_DEBUG += -Og
QMAKE_CXXFLAGS += -std=c++17

QT += core
QT += widgets
QT += network
QT -= gui


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


win32 | win64 {
    win64 {
        INCLUDEPATH += $$(QT_TOOLS)/OpenSSL/Win_x64/include/
        LIBS += -L$$(QT_TOOLS)/OpenSSL/bin -llibssl-1_1-x64
        LIBS += -L$$(QT_TOOLS)/OpenSSL/Win_x64/bin -llibcrypto-1_1-x64
    }
    win32 {
        INCLUDEPATH += $$(QT_TOOLS)/OpenSSL/Win_x86/include/
        LIBS += -L$$(QT_TOOLS)/Win_x86/bin -llibssl-1_1
        LIBS += -L$$(QT_TOOLS)/Win_x86/bin -llibcrypto-1_1
    }
    #mingw32-make install
    #your lib path
    #add env QT_DLL QT_PATH\{VERSION}\mingw{VERSION_ARCH}
    #add env QT_TOOLS QT_PATH\Tools\OpenSSL

    # RELEASE CONFIG
    CONFIG(release, debug|release) {
        TARGET = mariongiciel
        DESTDIR = runnable/release
        Release:OBJECTS_DIR = release/.obj
        Release:MOC_DIR = release/.moc
        Release:RCC_DIR = release/.rcc
        Release:UI_DIR = release/.ui

        DESTDIR = $${OUT_PWD}\runnable\release
        DLL.path    = $${DESTDIR}
        DLL.files   += $$(QT_DLL)\bin\Qt5Gui.dll
        DLL.files   += $$(QT_DLL)\bin\Qt5Network.dll
        DLL.files   += $$(QT_DLL)\bin\Qt5Core.dll
        DLL.files   += $$(QT_DLL)\bin\Qt5Widgets.dll
        DLL.files   += $$(QT_DLL)\bin\libstdc++-6.dll
        DLL.files   += $$(QT_DLL)\bin\libgcc_s_seh-1.dll
        DLL.files   += $$(QT_DLL)\bin\libwinpthread-1.dll

        win64 {
            OPENSSL.path    = $${DESTDIR}
            OPENSSL.files   += $$(QT_TOOLS)\OpenSSL\Win_64\bin\libcrypto-1_1-x64.dll
            OPENSSL.files   += $$QT_TOOLS)\OpenSSL\Win_64\bin\libssl-1_1-x64.dll
        }
        win32 {
            OPENSSL.path    = $${DESTDIR}
            OPENSSL.files   += $$(QT_OPENSSL)\OpenSSL\Win_86\bin\libcrypto-1_1.dll
            OPENSSL.files   += $$QT_OPENSSL)\OpenSSL\Win_86\bin\libssl-1_1.dll
        }

        PLATFORMS_EXTENSION.path    = $${DESTDIR}\platforms
        PLATFORMS_EXTENSION.files   += $$(QT_DLL)\plugins\platforms\*
        IMAGE_FORMATS.path    = $${DESTDIR}\imageformats
        IMAGE_FORMATS.files   += $$(QT_DLL)\plugins\imageformats\*

        RCS.path    = $${DESTDIR}\rcs
        RCS.files   += $${OUT_PWD}\..\rcs\config
        RCS.files   += $${OUT_PWD}\..\rcs\css
        RCS.files   += $${OUT_PWD}\..\rcs\icon

        SRC.path    = $${DESTDIR}\src
        SRC.files   += $${OUT_PWD}\..\mariongiciel\*

        INSTALLS += DLL OPENSSL PLATFORMS_EXTENSION IMAGE_FORMATS RCS SRC
    }
}

RC_ICONS = api.ico

SOURCES += \
    core/account.cpp \
    core/filter.cpp \
    core/format/csv.cpp \
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
    gui/filterdialog.cpp \
    gui/listview/customitem.cpp \
    gui/mainwindow.cpp \
    gui/menutoolbar.cpp \
    gui/querydialog.cpp \
    gui/referencialdialog.cpp \
    gui/referencialwidget.cpp \
    gui/searchparammanager.cpp \
    gui/searchwidget.cpp \
    main.cpp

HEADERS += \
    core/account.h \
    core/crypto.h \
    core/filter.h \
    core/format/csv.h \
    core/iomanagement.h \
    core/network/authentication.h \
    core/network/global.h \
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
    gui/filterdialog.h \
    gui/listview/customitem.h \
    gui/mainwindow.h \
    gui/menutoolbar.h \
    gui/querydialog.h \
    gui/referencialdialog.h \
    gui/referencialwidget.h \
    gui/searchparammanager.h \
    gui/searchwidget.h

