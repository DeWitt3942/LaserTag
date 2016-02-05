#ifndef GLROUTINS_H_INCLUDED
#define GLROUTINS_H_INCLUDED
//#include "Gamecore.h"

#include "Camera.h"
#include "LevelManager.h"
//#include "Entities.h"
static int slices = 16;
static int stacks = 16;
//const int width = 1366, height = 768;
int width = 1000, height = 580;
int midx = width/2, midy = height/2;
static POINT mousexy;
/*
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
*/
bool keys[256];
bool used[66], usedm[3], paused = false;
void light_and_material()
{
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_LIGHTING);
//            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LIGHT0);

            GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
            GLfloat light0_diffuse[] = {1.0, 1.0, 1.0};
            GLfloat light0_ambient[] = {0.f, 1.f, 0.f, 0.5};

            GLfloat light0_position[] = {0.0, 100.0, 0.0, 1.0};
            GLfloat light0_spot_direction[] = {0.0, -2.0, 0.0};
            GLfloat light0_light_model[] = {0,0,1,0};
            glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
            glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0_light_model);


}
static void idle(void)
{
    gameFlowCycleHandler();
    glutPostRedisplay();
}

static void resize(int width_, int height_)
{
    const float ar = (float) width_ / (float) height_;

    glViewport(0, 0, width_, height_);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void reshape ( int width_, int height_ )
{

			if(height_==0){height_=1;}
            width = width_; height = height_;
            midx = width/2; midy = height_/2;
			glViewport(0,0,width_,height_);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();


			gluPerspective(45.0f,(GLfloat)width_/(GLfloat)height_,0.1f,1000.0f);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
}
void reshape()
{
    reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
void keyUphandle(unsigned char key, int x, int y)
{
    keys[key] = false;
    switch (key){

    case 'w':
        used[0] = false;
        break;
    case 's':
        used[1] = false;
        break;
    case 'a':
        used[2] = false;
        break;
    case 'd':
        used[3] = false;
        break;


    case ' ':
        used[4] = false;
        break;
    case 'c':
        used[5] = false;
        break;

    case '+':
        used[7] = false;
        break;
    case '-':
        used[8] = false;
        break;

    default:
        break;
    }

}
void keyHandle(unsigned char key, int x, int y)
{
    keys[key] = true;
        switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
        case '/':
            state = INIT;
            break;
        case '*':
            state = preGame;
            break;
        case 'p':
            if (state==GAME)
                state = preMenu;
            else
                state = preGame;
            break;
    }
    switch (key){
    case 'w':
        used[0] = true;
        break;
    case 's':
        used[1] = true;
        break;
    case 'a':
        used[2] = true;
        break;
    case 'd':
        used[3] = true;
        break;
    case ' ':
        used[4] = true;
        break;
    case 'c':
        used[5] = true;
        break;

    case '+':
        used[7] = true;
        break;
    case '-':
        used[8] = true;
        break;
    case 27:
        exit(0);
        break;
    case 'm':
        hero.switchGameMode();
    default:
        break;
    }
}

void initTexture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

//	moonTex = ilutGLLoadImage((char*)moon);
  //  backgroundTex = ilutGLLoadImage((char*)background);
}
void initLight()
{
    glEnable(GL_LIGHTING);
	GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[]={50.0};
	GLfloat light_position[]={0.0,5.0,0.0,0.0};
	GLfloat white_light[]={1.0,1.0,1.0,1.0};

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	//glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	//glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
	//glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);
    glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 90);
    glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 0.f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT6);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_COLOR_MATERIAL);

}

int DevILInit()
{
   if ( ilGetInteger ( IL_VERSION_NUM ) < IL_VERSION )
   {
       fprintf ( stderr, "Incorrect devil.dll version\n" );
       return 0;
   }
   if ( iluGetInteger ( ILU_VERSION_NUM ) < ILU_VERSION )
   {
       fprintf ( stderr, "Incorrect ilu.dll version\n" );
       return 0;
   }
   if ( ilutGetInteger ( ILUT_VERSION_NUM ) < ILUT_VERSION )
   {
       fprintf ( stderr, "Incorrect ilut.dll version\n" );
       return 0;
   }
   ilInit();
   iluInit();
   ilutInit();
   ilutRenderer(ILUT_OPENGL);
}

static int lastT = 0;
static int frame = 0;
static int timebase = 0;
static char title[50];
static void display(void)
{
    frame++;

    const int dt = glutGet(GLUT_ELAPSED_TIME) - lastT;
        if (glutGet(GLUT_ELAPSED_TIME)- timebase > 0)
        {
              sprintf(title, "LaaerTag   FPS: %4.2f", 	frame*1000.0/(glutGet(GLUT_ELAPSED_TIME)-timebase+0.001));
              glutSetWindowTitle(title);
            timebase = glutGet(GLUT_ELAPSED_TIME);
            frame = 0;
        }

     switch (state){
            case INIT:
                idleInit(dt);
                break;
            case MENU:
                idleMenu(dt);
                break;
            case preGame:
                idleResume(dt);
                break;
            case GAME:
                idleGame(dt);
                break;
            case preMenu:
                idlePause(dt);
                break;
     }
    lastT += dt;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearColor(0.f,0.f,0.f,0.f);



    switch (state){
        case INIT:
            displayInit(dt);
            break;
        case MENU:
            displayMenu(dt);
            break;
        case preGame:
            displayPreGame(dt);
            break;
        case preMenu:
            displayPreMenu(dt);
            break;
        case GAME:
            displayGame(dt);
            break;
        default:
            break;
    }
    glutSwapBuffers();
    mouse_handler();
}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
        case '/':
            state = INIT;
            break;
        case '*':
            state = preGame;
            break;
        case 'p':
            if (state==GAME)
                state = preMenu;
            else
                state = preGame;
            break;

    }

    glutPostRedisplay();
}




#endif // GLROUTINS_H_INCLUDED
