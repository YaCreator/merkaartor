# PREFIX              - base prefix for installation (default: /usr/local)
# LIBDIR              - base directory for plugins (default: $$PREFIX/lib)
# NODEBUG             - no debug target

MERKAARTOR_SRC_DIR = $$PWD/..

#Static config
include ($$MERKAARTOR_SRC_DIR/src/Config.pri)

DEFINES += VERSION=\"\\\"$$VERSION\\\"\"
DEFINES += REVISION=\"\\\"$$REVISION\\\"\"

!contains(NODEBUG,1) {
    CONFIG += debug
    OBJECTS_DIR += tmp/$$(QMAKESPEC)/obj_debug
}
contains(NODEBUG,1) {
    CONFIG += release
    DEFINES += NDEBUG
    DEFINES += QT_NO_DEBUG_OUTPUT
    OBJECTS_DIR += tmp/$$(QMAKESPEC)/obj_release
}

win32-msvc* {
    DEFINES += _USE_MATH_DEFINES
}


OUTPUT_DIR = $$MERKAARTOR_SRC_DIR/$$(QMAKESPEC)/binaries
UI_DIR += tmp/$$(QMAKESPEC)
MOC_DIR += tmp/$$(QMAKESPEC)
RCC_DIR += tmp/$$(QMAKESPEC)
win32 {
    DESTDIR = $$OUTPUT_DIR
} else {
    DESTDIR = $$OUTPUT_DIR
}

DEPENDPATH += $${MERKAARTOR_SRC_DIR}/interfaces
INCLUDEPATH += $${MERKAARTOR_SRC_DIR}/interfaces

win32 {
    INCLUDEPATH += $$OUTPUT_DIR/include
    LIBS += -L$$OUTPUT_DIR/lib
}

unix {
    # Prefix: base instalation directory
    isEmpty( PREFIX ) {
        PREFIX = /usr/local
    }
    isEmpty( LIBDIR ) {
        LIBDIR = $${PREFIX}/lib${LIB_SUFFIX}
    }

    target.path = $${LIBDIR}/merkaartor/plugins
    INSTALLS += target
}