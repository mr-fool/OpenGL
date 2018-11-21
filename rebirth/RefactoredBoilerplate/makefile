OS_NAME:=$(shell uname -s)

ifeq ($(OS_NAME),Linux)
	LIBS += \
		-lGLEW \
		-lglfw \
		-lpthread \
		-lm \
		-lXi \
		-lXrandr \
		-lX11 \
		-lXxf86vm \
		-lXinerama \
		-lXcursor \
		-lGLU \
		-ldl \
		-lOpenGL
endif

target a.out:
	c++ -std=c++11 -I./include src/glad.c imagebuffer.cpp Program.cpp main.cpp -Wall -Wpragmas $(LIBS) -o a.out
clean:
	rm *.o a.out
