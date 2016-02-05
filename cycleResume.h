#ifndef CYCLERESUME_H_INCLUDED
#define CYCLERESUME_H_INCLUDED


static void mouseResume(){}
static void displayPreGame(const int &){}

static void idleResume(const int dt){}
static void onResume()
{
    cout<<"onResume()\n";
    if (isNewGame)
    {
        loadLevel();//from file
        cout<<"loaded level!\n";
        /*hero.pos = triple(0,0,1);
        hero.look = triple(0,1,0);*/
        hero.head = triple(0,0,1);
        hero.shape = new Sphere(HERO_RADIUS);
        isNewGame = false;
    }
    //prepare object's to show
    state = GAME;


}

#endif // CYCLERESUME_H_INCLUDED
