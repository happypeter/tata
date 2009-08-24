#############################################################################
# Makefile for building: popup
# Generated by qmake (2.01a) (Qt 4.3.4) on: Mon Aug 24 17:09:28 2009
# Project:  popup.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile popup.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_SHARED -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -fpermissive -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Isplash -I. -I.
LINK          = g++
LFLAGS        = -Wl,--no-undefined
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		popup.cpp \
		splash/display.cpp \
		splash/screen.cpp moc_popup.cpp \
		moc_display.cpp \
		moc_screen.cpp
OBJECTS       = main.o \
		popup.o \
		display.o \
		screen.o \
		moc_popup.o \
		moc_display.o \
		moc_screen.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		popup.pro
QMAKE_TARGET  = popup
DESTDIR       = 
TARGET        = popup

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: popup.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf
	$(QMAKE) -unix -o Makefile popup.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile popup.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/popup1.0.0 || $(MKDIR) .tmp/popup1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/popup1.0.0/ && $(COPY_FILE) --parents popup.hpp splash/display.hpp splash/screen.hpp .tmp/popup1.0.0/ && $(COPY_FILE) --parents main.cpp popup.cpp splash/display.cpp splash/screen.cpp .tmp/popup1.0.0/ && (cd `dirname .tmp/popup1.0.0` && $(TAR) popup1.0.0.tar popup1.0.0 && $(COMPRESS) popup1.0.0.tar) && $(MOVE) `dirname .tmp/popup1.0.0`/popup1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/popup1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_popup.cpp moc_display.cpp moc_screen.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_popup.cpp moc_display.cpp moc_screen.cpp
moc_popup.cpp: splash/display.hpp \
		splash/screen.hpp \
		popup.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) popup.hpp -o moc_popup.cpp

moc_display.cpp: splash/screen.hpp \
		splash/display.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) splash/display.hpp -o moc_display.cpp

moc_screen.cpp: splash/screen.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) splash/screen.hpp -o moc_screen.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

main.o: main.cpp splash/screen.hpp \
		splash/display.hpp \
		popup.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

popup.o: popup.cpp popup.hpp \
		splash/display.hpp \
		splash/screen.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o popup.o popup.cpp

display.o: splash/display.cpp splash/display.hpp \
		splash/screen.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o display.o splash/display.cpp

screen.o: splash/screen.cpp splash/screen.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o screen.o splash/screen.cpp

moc_popup.o: moc_popup.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_popup.o moc_popup.cpp

moc_display.o: moc_display.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_display.o moc_display.cpp

moc_screen.o: moc_screen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_screen.o moc_screen.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
