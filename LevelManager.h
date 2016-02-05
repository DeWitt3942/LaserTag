#ifndef LEVELMANAGER_H_INCLUDED
#define LEVELMANAGER_H_INCLUDED
#include "Gamecore.h"

const triple DIR_NORTH = triple(0,1), DIR_SOUTH = triple(0,-1), DIR_EAST = triple(1,0), DIR_WEST = triple(-1,0);


EntityLooking hero = EntityLooking(triple(0,0,1), triple(0,0,1));
struct LevelMap{




};
const double HERO_RADIUS = 1;
const double TILE_SIZE = 3;
const double TILE_HEIGHT = 1.5;
const double WALL_THICKNESS = 0.1;
const int MAX_LEVEL_SIZE = 20;
static Shape* defaultWallModel = new Rect(TILE_SIZE, WALL_THICKNESS, TILE_HEIGHT);
struct SingleWall{
    enum WallHealth{
        DEAD = 0,
        SINGLE_USE = 1,
        MILD = 3,
        STRONG = 10,
        IMMORTAL = 99999


    };
    enum WallOrientation {
        WALL_LEFT = 0,
        WALL_RIGHT = 1,
        WALL_TOP = 2,
        WALL_BOTTOM = 3,
        WALL_DIAGONAL = 4,
        WALL_ANTI_DIAGONAL = 5
    };
    int health;
    WallOrientation orientation;
    Shape* wallModel;

    SingleWall(Shape* wallModel,int health, int orientation): wallModel(wallModel)
    {
        this->orientation = static_cast<WallOrientation>(orientation);
        switch (health){
        case -1:
            this->health = SINGLE_USE;
            break;
        case -2:
            this->health = MILD;
            break;
        case -3:
            this->health = STRONG;
            break;
        case -4:
            this->health = IMMORTAL;
            break;
        default:
            this->health = health;
            break;
        }

    }

    void draw()
    {

        if (health==0)
            return;
        glPushMatrix();
     //   cout<<"+WALL";
        switch (orientation)
        {
            case WALL_LEFT:
                glTranslatef(0,TILE_SIZE/2,0);
                glRotatef(-90, 0,0,1.f);
                break;
            case WALL_RIGHT:
                glTranslatef(TILE_SIZE, TILE_SIZE/2,0);
                glRotatef(-90, 0,0,1.f);
                break;
            case WALL_TOP:
                glTranslatef(TILE_SIZE/2, TILE_SIZE,0);
                break;
            case WALL_BOTTOM:
                glTranslatef(TILE_SIZE/2,0,0);
                break;
            case WALL_DIAGONAL:

                glTranslatef(TILE_SIZE/2,TILE_SIZE/2,0);
                glRotatef(-45.0,0,0,1.f);

                break;
            case WALL_ANTI_DIAGONAL:
                glTranslatef(TILE_SIZE/2,TILE_SIZE/2,0);
                glRotatef(45.0,0,0,1.f);

                break;
            default:
                break;
        }
        wallModel->draw();
        glPopMatrix();
    }
    static Dict(triple) seatToTriple;
    static Dict(ptt ) seats;
    ptt getSeatPoints()
    {
       return seats[orientation];

    }

};
Dict(triple) SingleWall::seatToTriple = {{0, triple()},{1, triple(TILE_SIZE,0)}, {2, triple(TILE_SIZE, TILE_SIZE) }, {3, triple(0,TILE_SIZE)}};
Dict(ptt) SingleWall::seats = {
                                    {SingleWall::WallOrientation::WALL_LEFT,
                                        {SingleWall::seatToTriple[3], SingleWall::seatToTriple[0]}
                                        },
                                    {SingleWall::WallOrientation::WALL_RIGHT,
                                        {SingleWall::seatToTriple[1], SingleWall::seatToTriple[2]}
                                        },
                                    {SingleWall::WallOrientation::WALL_TOP,
                                        {SingleWall::seatToTriple[2], SingleWall::seatToTriple[3]}
                                        },
                                    {SingleWall::WallOrientation::WALL_BOTTOM,
                                        {SingleWall::seatToTriple[0], SingleWall::seatToTriple[1]}
                                        },
                                    {SingleWall::WallOrientation::WALL_DIAGONAL,
                                        {SingleWall::seatToTriple[3], SingleWall::seatToTriple[1]}
                                        },
                                    {SingleWall::WallOrientation::WALL_ANTI_DIAGONAL,
                                        {SingleWall::seatToTriple[0], SingleWall::seatToTriple[2]}
                                        }
                                    };

struct TileType{

    SingleWall* walls[6];
  //  static Dict(TileType) was;

/*private:
    TileType(int x):coded(x)
    {

        for (int i=0;i<6;i++)
            walls[i] = new SingleWall(defaultWallModel, (x&(1<<i))>0, i);


    }
public:

    static TileType* encode(int x)
    {
        if (TileType::was.count(x)==0)
            was[x] = new TileType(x);
        return was[x];

    }*/
    TileType(int x)
    {
         for (int i=0;i<6;i++)
            walls[i] = new SingleWall(defaultWallModel, -((x&(1<<i))>0)*4, i);

    }
};
//Dict(TileType) TileType::was = dictCreator<TileType>();
struct Tile{
    int indexX, indexY;
    TileType type;
    Tile():Tile(0,0,TileType(0)){}
    Tile(int iX, int iY, TileType type):indexX(iX), indexY(iY), type(type){}
    void draw()
    {
       // cout<<"IM DRAWING, YYOU LITL BICH\n!!!!";
        glPushMatrix();
           //glTranslatef(indexX*TILE_SIZE, indexY*TILE_SIZE,0);
            for (int i=0;i<6;i++)
                 type.walls[i]->draw();
        glPopMatrix();
    }
    static triple midleOf(int ix, int iy)
    {
        return triple(ix*TILE_SIZE - TILE_SIZE*0.5, iy*TILE_SIZE - TILE_SIZE*0.5);
    }
    void putWall(int wallOr, int health)
    {
        if (type.walls[wallOr]->health>=health)
            return;
        type.walls[wallOr] = new SingleWall(defaultWallModel, health, wallOr);
    }
    static pair<int,int> getTile(triple t)
    {
        return make_pair((int)((t.x+1e-3)/TILE_SIZE), (int)((t.y+1e-3)/TILE_SIZE));
    }
};

//

static int LEVEL_WIDTH, LEVEL_LENGTH;

const char* level_file = "assets\\level.txt";
Tile tiles[MAX_LEVEL_SIZE][MAX_LEVEL_SIZE];

static bool occupied(Shape* shape, triple pos)
{
    if (pos.z>TILE_HEIGHT)
        return false;
    static pair<int,int> t1, t2;
    static triple p1,p2;
    t1 = Tile::getTile(shape->border->p1 + pos);
    t2 = Tile::getTile(shape->border->p2 + pos);
    t1.first--; t1.second--;
    t2.first++; t2.second++;
    t1.first = max(t1.first,0);
    t2.first = min(t2.first, LEVEL_LENGTH);

    t1.second = max(t1.second,0);
    t2.second = min(t2.second, LEVEL_WIDTH);
    for (int i=t1.first;i<=t2.first;i++)
        for (int j=t1.second;j<=t2.second;j++)
            for (int id=0;id<6;id++)
                if (tiles[i][j].type.walls[id]->health>0)
                    if (intersects(shape, pos, tiles[i][j].type.walls[id]->getSeatPoints(), {TILE_SIZE * i, TILE_SIZE * j}))
                    {
                        cout<<"It works!\n";

                        return true;
                    }
      return false;
}


static void makeBorder()
{

        for (int i=0;i<LEVEL_LENGTH;i++)
        for (int j=0;j<LEVEL_WIDTH;j++)
    {
        if (i==0)
        {
            tiles[i][j].putWall(0,SingleWall::WallHealth::IMMORTAL);
        }
        if (i==LEVEL_LENGTH-1)
        {
            tiles[i][j].putWall(1,SingleWall::WallHealth::IMMORTAL);
        }
        if (j==LEVEL_WIDTH-1)
        {
            tiles[i][j].putWall(2,SingleWall::WallHealth::IMMORTAL);
        }
        if (j==0)
        {
            tiles[i][j].putWall(3,SingleWall::WallHealth::IMMORTAL);
        }

    }
}
static void loadLevel()
{
    string s;
    freopen(level_file,"r",stdin);
    cin>>LEVEL_WIDTH>>LEVEL_LENGTH;
    int x,y;
    for (int i=0;i<LEVEL_WIDTH;i++)
        for (int j=0;j<LEVEL_LENGTH;j++)
    {
        cin>>x;
       tiles[j][LEVEL_WIDTH-i-1] =
                                    Tile(j, LEVEL_WIDTH-i-1, TileType(x));
    }
    cin>>s;
    if (s=="border")
        makeBorder();

    //list of spawn positions

    cin>>x>>y;
    hero.pos = Tile::midleOf(x,y) + triple(0,0,10);
                switch (-x){
                    case -1:
                        hero.look = DIR_EAST;
                        break;
                    case -2:
                        hero.look = DIR_NORTH;
                        break;
                    case -3:
                        hero.look = DIR_WEST;
                        break;
                    case -4:
                        hero.look = DIR_SOUTH;
                        break;
                }
    cout<<hero.pos;
    cout<<LEVEL_LENGTH<<" "<<LEVEL_WIDTH<<endl;
}


#endif // LEVELMANAGER_H_INCLUDED
