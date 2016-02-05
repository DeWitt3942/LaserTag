#ifndef MODELS_H_INCLUDED
#define MODELS_H_INCLUDED

//#include "Entities.h"
struct Drawable{
    void draw();
    bool contains(triple);


};
struct Box : Drawable{
    triple p1, p2;
    void draw()
    {
        glColor3f(1.f,1.f,1.f);
        glPushMatrix();
            glScalef(ttl(p2-p1));
            glutWireCube(1);
        glPopMatrix();
    }
    bool contains(triple point)
    {
        //cout<< ((!(point<p1) && !(point>p2))?"C":"N")<<point<<" "<<p1<<" "<<p2<<endl;
        return (point.x >=p1.x && point.x <= p2.x && point.y >=p1.y && point.y <= p2.y && point.z >=p1.z && point.z <= p2.z );

    }
    Box(){}
};
struct Shape : Drawable{
    triple boxL, boxR;
    int type;
    Box* border;
    vector<double> params;
    bool selected = false;
    Shape( int type, vector<double> params): type(type), params(params) {
        border = new Box();
    }
    void setSizes(double A, double B, double C = 0.1)
    {
        border->p1 = triple(-A/2, -B/2, -C/2);
        border->p2 = triple(A/2, B/2, C/2);


    }

    bool contains(triple point)
    {
        return border->contains(point);
    }
    virtual void draw(){};

};



struct Sphere: public Shape{
    double R;
    Sphere(double r) : R(r) , Shape(1,{r}) {

        Shape::setSizes(r,r);
    }
    void draw()
    {
        glutSolidSphere(R, 30,30);
    }
};
struct Rect: public Shape{
    double H, W, D;
    Rect(double w, double h, double d = 0.1) : H(h), W(w), D(d), Shape(2, {W, H, D}) {
        setSizes(w,h,d);
    }

    void draw()
    {
        glPushMatrix();
            glScalef(W,H, D);
            glutSolidCube(1);
        glPopMatrix();
    }


};
struct Teapot: public Shape{
    double sz;
    Teapot(double sz) : sz(sz), Shape(3, vector<double>()){}
    void draw()
    {

        glutSolidTeapot(sz);
    }

};
struct Cone: public Shape{
    double r, H;
    Cone(double r, double H) : r(r), H(H), Shape(3, vector<double>()){}
    void draw()
    {

        glutSolidCone(r, H,30,30);
    }

};
struct Lego: public Shape{
    double width,height,depth;
    triple color;

    GLUquadricObj* sciffs;
    Lego(double w,  double h, double depth = 1) : width(w), height(h), depth(depth), Shape(4, {width,  height, depth}){

            sciffs =gluNewQuadric();
            color = triple(1.0,0.5,0.5);
            setSizes(width,height,depth);
    }
    void draw()
    {
        double D = depth/4, H = 3*height/4, W = width/6, sz = min(W, D);
        glColor3f(ttl(color));
        glPushMatrix();
        glTranslatef(-width/2, -height/2+(height-H), - depth/2);
        glPushMatrix();
            glTranslatef(W, H, D);
            glPushMatrix();
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                gluCylinder(sciffs, sz, sz, height-H, 30,30);

            glPopMatrix();
            glTranslatef(2*W, 0, 0);

            glPushMatrix();
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                gluCylinder(sciffs, sz, sz, height-H, 30,30);
            glPopMatrix();
            glTranslatef(2*W, 0, 0);

            glPushMatrix();
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                gluCylinder(sciffs, sz, sz, height-H, 30,30);
            glPopMatrix();

            glTranslatef(-4*W, 0, 2*D);
                        glPushMatrix();
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                gluCylinder(sciffs, sz, sz, height-H, 30,30);
            glPopMatrix();
            glTranslatef(2*W, 0, 0);

            glPushMatrix();
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                gluCylinder(sciffs, sz, sz, height-H, 30,30);
            glPopMatrix();
            glTranslatef(2*W, 0, 0);

            glPushMatrix();
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                gluCylinder(sciffs, sz, sz, height-H, 30,30);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(width/2,(height - H)/2, depth/2);
            glScalef(width, height*0.75, depth);
            glutSolidCube(1);
        glPopMatrix();



        glPopMatrix();
    }


};

static bool intersects(triple sphere_center, double radius,  triple a1, triple a2)
{
    cout<<"( "<<sphere_center<<", radius = "<<radius<<" "<<" "<<a1<<", "<<a2<<" )"<< "result = "<<(sphere_center.toSegment(a1,a2)<=radius)<<"\n";
    obstacling = (sphere_center.toSegment(a1,a2)<=radius);
    return (sphere_center.toSegment(a1,a2)<=radius);

}
static bool intersects(Box* box,  triple pos, ptt segment, triple segment_pos)
{
    return false;
}

static bool intersects(Shape* shape, triple pos, ptt segment, triple segment_pos)
{
    cout<<"CHECK";
    if (shape->type==1)
            return intersects(pos, shape->params[0], segment.first + segment_pos, segment_pos + segment.second);
    //test Box
    if (!intersects(shape->border, pos, segment, segment_pos))
        return false;

    return false;
}


#endif // MODELS_H_INCLUDED
