#ifndef CYCLEMENU_H_INCLUDED
#define CYCLEMENU_H_INCLUDED

static void mouseMenu(){}

static void displayMenu(const int &dt)
{
    displayInit(dt);
}
static void onMenu()
{
    cout<<"onMenu()\n";
}
int time_menu = 0;
static void idleMenu(const int dt){

time_menu += dt;
if (time_menu >=1000)
    state = preGame;
}
#endif // CYCLEMENU_H_INCLUDED
