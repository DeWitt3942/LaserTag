#ifndef CYCLEPAUSE_H_INCLUDED
#define CYCLEPAUSE_H_INCLUDED


static void onPause() {
    cout<<"onPause()\n";
    loadLevel();


    state = MENU;

}
static void mousePause() {}
static void displayPreMenu(const int &){

}

static void idlePause(const int dt){}

#endif // CYCLEPAUSE_H_INCLUDED
