#ifndef GAMECORE_H_INCLUDED
#define GAMECORE_H_INCLUDED

enum gameState {
    INIT,
    MENU,
    preGame,
    preMenu,
    GAME

};
gameState state;
//display functions of each type
static void displayInit(const int &);
static void displayMenu(const int &);
static void displayPreGame(const int &);
static void displayPreMenu(const int &);
static void displayGame(const int &);
//initors
static void onInit();
static void onMenu();
static void onResume();
static void onPause();
static void onGame();

static void mouseInit();
static void mouseMenu();
static void mouseResume();
static void mousePause();
static void mouseGame();

static void idleInit(const int);
static void idleMenu(const int);
static void idleResume(const int);
static void idlePause(const int);
static void idleGame(const int);

gameState lastState = GAME;
static bool isNewGame = true;
static void gameFlowCycleHandler()
{

      if (lastState!=state)
    {
        lastState = state;

        switch (state){
            case INIT:
                onInit();
                break;
            case MENU:
                onMenu();
                break;
            case preGame:
                onResume();
                break;
            case GAME:
                onGame();
                break;
            case preMenu:
                onPause();
                break;

        }
    }
   /*else
    switch (state){
            case INIT:
                idleInit();
                break;
            case MENU:
                idleMenu();
                break;
            case preGame:
                idleResume();
                break;
            case GAME:
                idleGame();
                break;
            case preMenu:
                idlePause();
                break;

    }*/
}
static void mouse_handler()
{
    switch (state){
        case INIT:
            mouseInit();
            break;
        case MENU:
            mouseMenu();
            break;
        case preGame:
            mouseResume();
            break;
        case GAME:
            mouseGame();
            break;
        case preMenu:
            mousePause();
            break;

    }

}


#endif // GAMECORE_H_INCLUDED
