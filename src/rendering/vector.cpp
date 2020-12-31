#include<math.h>
#include "rendering\vector.h"

vect3d_t& vect3d_t::operator =(vect3d_t& v)
{
    x=v.x;
    y=v.y;
    z=v.z;
    return(*this);
}

vect3d_t vect3d_t::operator +(vect3d_t& v)
{
    vect3d_t temp(*this);
    temp.x+=v.x;
    temp.y+=v.y;
    temp.z+=v.z;
    return temp;
}

vect3d_t vect3d_t::operator -(vect3d_t& v)
{
    vect3d_t temp(*this);
    temp.x-=v.x;
    temp.y-=v.y;
    temp.z-=v.z;
    return temp;
}

vect3d_t::vect3d_t()
{
    x=y=z=0;
}

vect3d_t::vect3d_t(float x,float y,float z)
{
    vect3d_t::x=x;
    vect3d_t::y=y;
    vect3d_t::z=z;
}

vect3d_t::vect3d_t(vect3d_t& v)
{
    vect3d_t::x=v.x;
    vect3d_t::y=v.y;
    vect3d_t::z=v.z;
}

void normalize(vect3d_t& v)
{    
   float d = (float)sqrt(v.x*v.x+v.y*v.y+v.z*v.z); 
   if (d == 0.0) return;
   v.x /= d; v.y /= d; v.z /= d; 
}

void normcrossprod(vect3d_t v1,vect3d_t v2,vect3d_t& out) 
{ 
   out.x = v1.y*v2.z - v1.z*v2.y; 
   out.y = v1.z*v2.x - v1.x*v2.z; 
   out.z = v1.x*v2.y - v1.y*v2.x; 
   normalize(out); 
}

void calcnormal(vect3d_t a,vect3d_t b,vect3d_t c,vect3d_t& out)
{
    vect3d_t v1,v2;
    v1=a-b;
    v2=b-c;
	normcrossprod(v1,v2,out);
}

float dotprod(vect3d_t v1,vect3d_t v2)
{
    return (v1.x*v2.x+v1.y*v2.y+v1.z*v2.z);
}

float vectangle(vect3d_t v1,vect3d_t v2)
{ 
    return (float)dotprod(v1,v2)/
        (float)(sqrt(v1.x*v1.x+v1.y*v1.y+v1.z*v1.z)*
        sqrt(v2.x*v2.x+v2.y*v2.y+v2.z*v2.z));
}

int IsPointInTriangle(vect3d_t a,vect3d_t b,
					  vect3d_t c,vect3d_t point)
{
    float angle1,angle2,angle3;
    angle1=angle2=angle3=0.0;
    angle1=vectangle(vect3d_t(a-point),vect3d_t(b-point));
    angle2=vectangle(vect3d_t(a-point),vect3d_t(c-point));
    angle3=vectangle(vect3d_t(b-point),vect3d_t(c-point));
    if(angle1+angle2+angle3-360.0<=0.000001) return 1;
    else return 0;
}
