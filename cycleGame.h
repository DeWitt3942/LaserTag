#ifndef CYCLEGAME_H_INCLUDED
#define CYCLEGAME_H_INCLUDED

static void mouseGame(){

    GetCursorPos(&mousexy);
    int x = mousexy.x - glutGet((GLenum)GLUT_WINDOW_X);
    int y = mousexy.y - glutGet((GLenum)GLUT_WINDOW_Y);
    if (x<0 || x>width || y<0 || y>height)
        return;
     int dx = x - midx, dy = y - midy;
     if (dx==0 && dy==0)
        return;
    hero.look = hero.look - (hero.head.mult(dy)).mult(prima) + (hero.look*hero.head.mult(dx)).mult(prima);
    SetCursorPos(glutGet((GLenum)GLUT_WINDOW_X) +midx, glutGet((GLenum)GLUT_WINDOW_Y)+midy);

}
static void onGame()
{
    cout<<"onGame()\n";
    reshape();
    hero.gamemode = SURVIVAL;

}
static void showAxies()
{
    glPushMatrix();
    glTranslatef(0,0,5);
    glutSolidSphere(0.5,50,50);

    glColor3f(0,1,0);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(100,0,0);
    glEnd();
    glColor3f(0,0,1);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,100,0);
    glEnd();

    glPopMatrix();
}
void showMeTheNumberofWalls()
{
    cout<<"StATS\n";
        for (int y=LEVEL_WIDTH-1;y>=0;y--)
        {
                 for (int x=0;x<LEVEL_LENGTH;x++)
    {
        int c = 0;
        for (int q = 0;q<6;q++)
            if (tiles[x][y].type.walls[q]->health>0)
            c++;
        cout<<c<<" ";
    }
    cout<<endl;
    }
    cout<<"AAA\n";
}
vector<triple> colors = { triple(1,0,0), triple(0,1,0), triple(0,0,1) };
static void displayGame(const int &dt)
{

    //cout<<"OLOLO";
   // showMeTheNumberofWalls();
    glClearColor(1.f,1.f,1.f,1.f);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
   //  cout<<"So, hero is on "<< hero.pos<< ".. looking to "<< hero.pos + hero.look<<".. head is pointing to "<< hero.head<<endl;
     gluLookAt (ttl(hero.pos), ttl(hero.pos + hero.look.mult(prima)), ttl(hero.head));
     showAxies();
     glColor4f(0,1.f,1.f,1.f);
     glPushMatrix();
        glTranslatef(ttl(hero.pos));
       //glTranslatef(triple(1,1,3));
        glutSolidSphere(HERO_RADIUS, 50,50);
     glPopMatrix();
     glColor4f(1.f,1.f,1.f,1.f);
     glPushMatrix();
        glPushMatrix();

        for (int i=0;i<LEVEL_LENGTH;i++)
        {
            for (int j=0;j<LEVEL_WIDTH;j++)
            {
             //   glColor3f(ttl(colors[i+j]));
               // glutWireTorus(0.5,0.2,50,50);
                tiles[i][j].draw();
            //    cout<<"y++"<<j<<" ";
                glTranslatef(0,TILE_SIZE,0);
            }
          //  cout<<"x++\n";
            glTranslatef(0,- LEVEL_WIDTH*TILE_SIZE,0);
            glTranslatef(TILE_SIZE, 0, 0);

        }
        glPopMatrix();
        glTranslatef(0,5,0);
      //  glutWireSphere(1,50,50);
     glPopMatrix();



}

static void idleGame(const int dt){

    //it's exactly resumed
    //cout<<dt<<endl;
    hero.handleKeys(used, dt/10.0);
    hero.handleGravity();


}

#endif // CYCLEGAME_H_INCLUDED
