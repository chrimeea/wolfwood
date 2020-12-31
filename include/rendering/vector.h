#if !defined( VECTOR_H )
#define VECTOR_H

class vect3d_t {
public:
    float x,y,z;
public:
    vect3d_t();
    vect3d_t(float x,float y,float z);
    vect3d_t(vect3d_t& v);
    vect3d_t& operator=(vect3d_t& v);
    vect3d_t operator+(vect3d_t& v);
    vect3d_t operator-(vect3d_t& v);
};

void normalize(vect3d_t&);
void normcrossprod(vect3d_t,vect3d_t,vect3d_t&);
void calcnormal(vect3d_t,vect3d_t,vect3d_t,vect3d_t&);
float vectangle(vect3d_t,vect3d_t);
int IsPointInTriangle(vect3d_t,vect3d_t,vect3d_t,vect3d_t);

#endif