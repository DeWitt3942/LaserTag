#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#define ttl(t) (t).x, (t).y, (t).z
using namespace std;



struct triple
{
    double x,y,z;
    triple(double x, double y, double z = 0):x(x),y(y),z(z) {}
    triple():x(0),y(0),z(0) {}
    bool operator < (triple B)
    {
        if (x<B.x)return true;
        if (x>B.x)return false;
        if (y<B.y)return true;
        if (y>B.y)return true;
        if (z<B.z)return true;
        if (z>B.z)return false;
    }
    bool operator ==(triple B)
    {
        return (x==B.x && y==B.y && z==B.z);
    }
    bool operator >(triple B)
    {
        return (!(*this<B || *this==B));
    }
    triple operator + (triple B)
    {
        return triple(x+B.x, y+B.y, z + B.z);
    }
    triple operator - (triple B)
    {
        return triple(x-B.x, y-B.y, z - B.z);
    }
    double norm()
    {
        return sqrt(x*x+y*y+z*z);
    }
    void transponise()
    {
        double d = (*this).norm();
        x/=d;
        y/=d;
        z/=d;
    }
    triple ort()
    {
        return triple(x/norm(), y/norm(), z/norm());

    }
    triple operator * (triple b)
    {
        return triple( y * b.z - z * b.y, z*b.x - x*b.z, x*b.y - y*b.x);
    }
    triple scalar (triple b)
    {
        return triple(x*b.x,y*b.y,z*b.z);
    }
    triple mult(double d)
    {
        return triple(x*d, y*d, z*d);
    }
    void print()
    {
        cout<<x<<" "<<y<<" "<<z<<endl;
    }
    triple inverse()
    {
        return triple(sqrt(1/(1+x/y)), sqrt(1 - 1/(1+x/y)));
    }
    static double pov(triple A, triple B, triple C)
    {
        return (B.x - A.x)*(C.y-A.y) - (B.y-A.y)*(C.x-A.x);
    }
    double toSegment(triple A, triple B, bool debug = false)
    {
        double f1 = triple::pov(*this, A, B);
        double a = (A-B).norm();
        double b = (*this-A).norm();
        double c = (*this-B).norm();
        if (debug)
            cout<<f1<<" "<<a<<" "<<b<<" "<<c<<endl;
        if (a*a+b*b< c*c || a*a+c*c<b*b)
            return min(b,c);
        //cout<<"["<<abs(f1)*1.0/a<<"]";

        return std::abs(f1*1.0/a);
    }
    triple nearToSegment(triple A, triple B)
    {
      /* double r = toSegment(A,B);
         double f1 = triple::pov(*this, A, B);
         double a = (A-B).norm(); double b = (*this-A).norm();  double c = (*this-B).norm();
        if (f1/a==r)
        {
            double h = f1/a,d1,d2;
            d1 = sqrt(b*b - h*h);
            d2 = a - d1;
            return A + (B-A).mult(d1/a);
        }


        if (r==b)
            return A;

        if (r==c)
            return B;*/

        triple* mm = this;
        mm->y = A.y;
        if (mm->x<A.x || mm->x > B.x)
            return  ((*mm - A).norm() > (*mm-B).norm())? B:A;

        return *mm;
    }
    triple abs()
    {
        return triple(std::abs(x), std::abs(y), std::abs(z));
    }
    double max()
    {
        return std::max(x,std::max(y,z));
    }
    triple project(int mask)
    {
        return triple( x * (mask&1), y * (mask & 2 ) /2, z * (mask&4)/4 );
    }
    static triple ZERO;
};
triple triple::ZERO = triple();
ostream &operator <<(ostream &os, triple t)
{
    return os<<"( "<<t.x<<", "<<t.y<<", "<<t.z<<")";
}
template<class T, class Q>
ostream &operator <<(ostream &os, pair<T,Q> t)
{
    return os<<"( "<<t.first<<", "<<t.second<<")";
}
typedef pair<triple, triple> ptt;

const triple toLeft = triple(-1,0);
const triple toRight = triple(1,0);
triple UP = triple(0,1), DOWN = triple(0,-1), LEFT = triple(-1,0), RIGHT = triple(1,0), delta;

const triple zeroTriple = zeroTriple;
int cv(int x)
{
    return x?1:-1;
}



struct poly
{
    vector<triple> pts;
    triple centre;
    vector<triple> colors;
    //poly(vector<triple> p =) :pts(p) {}
    poly(vector<triple> p, vector<triple> c = vector<triple>(0)) : pts(p), colors(c)  {}
    poly()
    {
        pts.assign(0,zeroTriple);
        colors.assign(0,zeroTriple);
    }
    void draw(bool thick = false)
    {
        glBegin(thick?GL_LINE_LOOP:GL_POLYGON);
        for (int i=0;i<pts.size();i++)
        {

            if (i<colors.size())                glColor3f(ttl(colors[i]));
        glVertex3f(ttl(pts[i] + centre));
        }
        glEnd();

    }
    static poly rectangle(double A, double B)
    {
        return poly({triple(-A/2, -B/2), triple(-A/2, B/2), triple(A/2, B/2), triple(A/2,-B/2)});
    }
    static poly circle(double R, double pr = 20)
    {
        vector<triple> vc;
        for (int i=0;i< 360;i+=pr)
        {
            vc.push_back(triple(R* cos(i), R*sin(i)));
        }
        return poly(vc);
    }
};
double dmod(double x, int a)
{
    return (x - (int(x/a))*a);
}

struct Object
{
    vector<poly> polys;
    Object(vector<poly> p = vector<poly>(0)) : polys(p) {}
    void draw(bool thick = false)
    {
        for (int i=0;i<polys.size();i++)
            polys[i].draw(thick);
    }

};


bool segmentIntersection(double a, double a1, double b, double b1)
{
    if (a>a1)
        swap(a,a1);
    if (b>b1)
        swap(b,b1);
    return !(a>b1 || a1<b);
}

bool rectangleIntersection(triple a, triple a1, triple b, triple b1)
{
    double X[] = {a.x , a1.x, b.x, b1.x};
    double Y[] = {a.z , a1.z, b.z, b1.z};
    sort(X, X + 4);
    sort(Y, Y + 4);
    return (X[2]-X[1]>0.2 && Y[2]-Y[1]>0.2);
}



void outtext(float x, float y, float z, char *string, triple color = zeroTriple)
{
    glColor3f(ttl(color));
glRasterPos3f(x, y, z);
for (char *c=string; *c!='\0'; c++)
{
glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, *c);
}
}



bool in(double a, double b, double c)
{
    return (a>=b && a<=c);
}



#endif // UTILS_H_INCLUDED
