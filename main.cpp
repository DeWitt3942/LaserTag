#include <gl/gl.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <stdlib.h>
#include<iostream>
#include<bits/stdc++.h>
#define Dict(x) map<int, x >

using namespace std;
static bool obstacling = false;
template<class T>
Dict(T) dictCreator()
{
    Dict(T) r;
    return r;
}
const string assets_path = "F:\\codeblocksproj\\unoGluto\\assets\\";
#include <windows.h>
#include "utils.h"

#include "Entities.h"
#include "Models.h"
#include "GLroutins.h"
#include "cycleINIT.h"
#include "cycleMENU.h"
#include "cycleResume.h"
#include "cycleGame.h"
#include "cyclePause.h"
#define ttl(a) (a).x, (a).y, (a).z
#define mp(a,b) make_pair(a,b)



//TODO: Display functions


//TODO: initializers




int main(int argc, char *argv[])
{

    freopen("game.log","w",stdout);

    state = INIT;
    glutInit(&argc, argv);
    gameFlowCycleHandler();
    DevILInit();
	initTexture();
    glutInitWindowSize(width,height);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("LaserTag");
    //glutFullScreen      ( );
    initLight();
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyHandle);
    glutKeyboardUpFunc(keyUphandle);
    glutIdleFunc(idle);

    //glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glEnable(GL_LIGHT0);
  //  glEnable(GL_NORMALIZE);
    //glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_LIGHTING);


    glutMainLoop();

    return EXIT_SUCCESS;

}
