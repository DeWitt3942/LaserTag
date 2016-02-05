#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include "Models.h"
//#include "Savable.h"
namespace Gravity{

    const double G = 5e-2;
    triple DOWN = triple(0,0,-1);
    triple UP = triple(0,0,1);

}

double prima = 1e-3;
static bool occupied(Shape*, triple);
enum Gamemode {SURVIVAL, CREATIVE};
struct Entity
{
    triple pos, velocity;
    Entity(triple pos, triple velocity = zeroTriple) : pos(pos), velocity(velocity) {}
    triple getNextPoint(double dt=1)
    {
        return pos + velocity.mult(prima);
    }
    void move(double dt = 1)
    {
        pos = getNextPoint(dt);
    }
};
struct PhysicalObject: Entity
{
    double mass;
    int health;
    Shape* shape;
    Box* box;
    bool isSelected = false;
    double scale = 1;
    bool isNeutrino = false;
    void move(double dt = 1)
    {
        if (velocity.norm()==0)
            return;
        triple point = getNextPoint();
        if (!isNeutrino)
        {
                //if (!occupiedPoint(point+box->p1) && !occupiedPoint(point+box->p2))
                if (!occupied(shape, pos))
                    this->pos = point;
                else
                    this->velocity = triple::ZERO;
                return;
        }

        Entity::move();
    }

    bool operator < (PhysicalObject b)
    {
        return mass < b.mass;
    }
    PhysicalObject(triple pos, triple velocity = zeroTriple) : Entity(pos, velocity) {
        mass = 0;
    }
    PhysicalObject(triple pos, triple velocity, Shape* shape, int health = 1) : Entity(pos, velocity), shape(shape), health(health) {
        mass = 0;
        box = shape->border;


    }
    void drawBorder()
    {
        glPushMatrix();
           glTranslatef(ttl(pos));
            glColor3f(1.f,1.f,1.f);
            box->draw();
            glColor3f(1.f,1.f,1.f);
        glPopMatrix();

    }

    void draw()
    {
        glTranslatef(ttl(pos));
        switch (health)
        {
        case 0:
            glColor4f(0.f,0.f,0.f,0.f);
            break;
        case 1:
            glColor3f(.8f,.8f,0.8f);
            break;
        case 2:
            glColor3f(1.f,0.f,0.f);
            break;
        case 3:
            glColor3f(0.f,0.f,1.f);
            break;
        case 7:
            glColor3f(0.f,1.f,0.8f);
            break;
        default:
            glColor3f(1.f,1.f,1.f);
            break;
        }
        glPushMatrix();
            glScalef(scale, scale, scale);
            shape->draw();

        glPopMatrix();
     glColor3f(.5f,.5f,.5f);
     glTranslatef(ttl(pos.mult(-1)));
     if (isSelected)
        drawBorder();

    }

    bool contains(triple point)
    {
        return box->contains(point - pos);
    }
    vector<string> getCoding()
    {
        vector<string> r;
//        r.push_back(Savable::getCoding(mass) + " " + getCoding(health) + " " + getCoding(pos)  );
        return r;
    }
};

struct PObjectSet
{
    vector<PhysicalObject*> objects;
    triple velocity, pos;
    int p[101], s[101];
    bool selection[101];

    int findset(int x)
    {
        if (p[x]==x)
            return x;
        else return findset(p[x]);
    }
    void unite(int x, int y)
    {
        int x0,y0;
        x0 = findset(x);
        y0 = findset(y);
        if (x0==y0)
            return;
        if (s[x0]<s[y0])
            p[x0] = y0;
        else
        {
            p[y0] = x0;
            if (s[x0]==s[y0])
                s[x0]++;

        }
    }


    void move()
    {
        pos = pos + velocity;
    }
    PObjectSet(vector<PhysicalObject*> obj, triple p)
    {
        objects = obj;
        pos = p;
        velocity = triple();
    }
    void addObject(PhysicalObject* obj)
    {
        objects.push_back(obj);
        p[objects.size()-1] = objects.size()-1;
        s[objects.size()-1] = 0;
        selection[objects.size()-1] = false;
    }
    void draw()
    {
        glPushMatrix();
            glTranslatef(ttl(pos));
            for (size_t i =0;i<objects.size();i++)
                objects[i]->draw();
        glPopMatrix();

    }
    void tryToMoveB(int h, triple v)
    {

        for (int i=0;i<objects.size();i++)
        {

        }

    }



};


bool legosCombine(PhysicalObject* A, PhysicalObject* B)
{
    if (A->pos.y<B->pos.y)
        swap(A,B);
    if (abs(A->pos.y - B->pos.y - 0.5) > 0.1)
        return false;
    triple a, a1, b, b1;
    a = A->box->p1 + A->pos;
    a1 = A->box->p2 + A->pos;
    b = B->box->p1 + B->pos;
    b1 = B->box->p2 + B->pos;
    //if (!(segmentIntersection(a.x, a1.x, b.x, b1.x) && segmentIntersection(a.z, a1.z, b.z, b1.z)))
        return false;
    //return (rectangleIntersection(a,a1,b,b1));


}


#endif // ENTITIES_H_INCLUDED
