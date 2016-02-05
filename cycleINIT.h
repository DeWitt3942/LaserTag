#ifndef CYCLEINIT_H_INCLUDED
#define CYCLEINIT_H_INCLUDED
static void mouseInit()
{

}
static void displayInit(const int &dt)
{
  //  cout<<"i'm in";
    const double a = lastT*90.0/1000;
    glColor3d(1,0,0);
    glLoadIdentity();
    glTranslatef(0,0,2);
    glPushMatrix();

        glTranslated(-2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.4,-1.2,-6);
        glRotated(60,1,0,0);
        glRotated(a,0,0,1);
        glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();


}

static void onInit()
{



    cout<<"onInit()";
    srand(time(0));
    glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	//glDepthFunc(GL_LEQUAL);
    //glEnable ( GL_COLOR_MATERIAL );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	/*hero.setHead(triple(0.f,1.f,0.f));
	used[0] = false; used[1] = false; used[2] = false; used[3] = false;*/
    glViewport(0,0,width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,width/height,0.1,1000);
    //reshape();
    //glutFullScreen();
    state = MENU;
    cout<<state;

}

static void idleInit(const int dt)
{

}
#endif // CYCLEINIT_H_INCLUDED
