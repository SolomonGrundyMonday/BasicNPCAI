# NPCAI Project, Jeff Colgan
# Created makefile January 10, 2022.
EXE=chase

# Main target
all: $(EXE)

# Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
# OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=2
LIBS=-framework GLUT -framework OpenGL
# Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
# OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
ChaseMain.o: ChaseMain.cpp Ground.h Player.h GameObject.h Camera.h
Ground.o: Ground.cpp Ground.h GameObject.h 
Camera.o: Camera.cpp Camera.h
Player.o: Player.cpp Player.h GameObject.h
GameObject.o: GameObject.cpp GameObject.h

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

# Link
chase: ChaseMain.o   GameObject.o   Ground.o   Player.o   Camera.o
	g++ $(CFLG) -o $@ $^ $(LIBS)

# Clean
clean:
	$(CLEAN)