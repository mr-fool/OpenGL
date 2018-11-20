# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = tracey

HEADERS = \
   $$PWD/imagebuffer.h \
   $$PWD/Program.h \
   $$PWD/ray.h \
    parseFile.h

SOURCES = \
   $$PWD/imagebuffer.cpp \
   $$PWD/main.cpp \
   $$PWD/Program.cpp \
   $$PWD/ray.cpp \
   $$PWD/Sphere.cpp

INCLUDEPATH = \
    $$PWD/.

#DEFINES = 

LIBS += -lGL -lglfw -lglad
