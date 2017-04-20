#define GLUT_DISABLE_ATEXIT_HACK
#define _WIN32_WINNT 0x0500
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <sys/time.h>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "sound.h"
#include "bmp_read.h"
#include "read_shader.h"
#include "font_reader.h"
#include "elementary_drawing.h"
#include "playfield.h"
#include "animation.h"
#include "attacks.h"
#include "hero.h"
#include "mob.h"
#include "animations.h"
#include "events.h"
#include "controls.h"
#include "gui.h"
#include "slideshow.h"


int main(int argc, char** argv)
{
	//std::cout.precision(17);
	load_font("font/slider.ttf"); 
	srand(time(0));
	glutInit(&argc,argv);
	InitGL(1024,768);                              
                  
}
