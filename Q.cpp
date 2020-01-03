//
//  main.cpp
//  Character
//
//  Created by Oktavia Citra on 08/12/19.
//  Copyright © 2019 Oktavia Citra. All rights reserved.
//

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

typedef struct {
    float x,y,z;
} Point3D_t;
 
typedef struct {
    float x,y,z,r,g,b;
}Point3D_color_t;
 
typedef struct {
    float x,y;
} Point2D_t;
 
typedef struct {
    int NumberofVertices;
    short int pnt[32];
} face_t;
 
typedef struct {
    int NumberofVertices;
    Point3D_color_t pnt[100];
    int NumberofFaces;
    face_t fc[85];
} object3D_t;
 
typedef struct {
    float v[6];
} Vector3D_t;
 
typedef struct {
    float m[3][3];
} Matrix3D_t;
 
typedef struct {
    float r;
    float g;
    float b;
} Color_t;
 
int nmax=250;
int n=0;
int i,j;
float sudut =1;
Vector3D_t vec[100],vec3D;
Point2D_t titik2D[100];
Matrix3D_t matrix3DX,matrix3DY,matrix3DZ,matrix3DS;
object3D_t huruf1,huruf2,huruf3,huruf4;
 
Matrix3D_t createIdentity(){
    Matrix3D_t rotate;
    rotate.m[0][0]=0.0; rotate.m[0][1]=0.0; rotate.m[0][2]=0.0;
    rotate.m[1][0]=0.0; rotate.m[1][1]=0.0; rotate.m[1][2]=0.0;
    rotate.m[2][0]=0.0; rotate.m[2][1]=0.0; rotate.m[2][1]=0.0;
    return rotate;
}
 
Matrix3D_t rotationX(float teta){
    Matrix3D_t rotate=createIdentity();
    rotate.m[0][0]=1.0; rotate.m[0][1]=0.0; rotate.m[0][2]=0.0;
    rotate.m[1][0]=0.0; rotate.m[1][1]=cos(teta/57.3); rotate.m[1][2]=-sin(teta/57.3);
    rotate.m[2][0]=0.0; rotate.m[2][1]=sin(teta/57.3); rotate.m[2][2]=cos(teta/57.3);
    return rotate;
}
 
Matrix3D_t rotationY(float teta){
    Matrix3D_t rotate=createIdentity();
    rotate.m[0][0]=cos(teta/57.3); rotate.m[0][1]=0.0; rotate.m[0][2]=sin(teta/57.3);
    rotate.m[1][0]=0.0; rotate.m[1][1]=1.0; rotate.m[1][2]=0.0;
    rotate.m[2][0]=-sin(teta/57.3); rotate.m[2][1]=0.0; rotate.m[2][2]=cos(teta/57.3);
    return rotate;
}
 
Matrix3D_t rotationZ(float teta){
    Matrix3D_t rotate=createIdentity();
    rotate.m[0][0]=cos(teta/57.3); rotate.m[0][1]=-sin(teta/57.3); rotate.m[0][2]=0.0;
    rotate.m[1][0]=sin(teta/57.3); rotate.m[1][1]=cos(teta/57.3); rotate.m[1][2]=0.0;
    rotate.m[2][0]=0.0; rotate.m[2][1]=0.0; rotate.m[2][2]=1.0;
    return rotate;
}
 
Matrix3D_t scale2D(float kx, float ky,float kz){
    Matrix3D_t rotate;
    rotate.m[0][0]=kx; rotate.m[0][1]=0; rotate.m[0][2]=0.0;
    rotate.m[1][0]=0.0; rotate.m[1][1]=ky; rotate.m[1][2]=0.0;
    rotate.m[2][0]=0.0; rotate.m[2][1]=0.0; rotate.m[2][2]=kz;
return rotate;
}
 
void setColor(Color_t col){
    glColor3f(col.r, col.g, col.b);
}
 
Vector3D_t Point2Vector3D(Point3D_color_t pnt){
    Vector3D_t vecb;
    vecb.v[0]=pnt.x;
    vecb.v[1]=pnt.y;
    vecb.v[2]=pnt.z;
    vecb.v[3]=pnt.r;
    vecb.v[4]=pnt.g;
    vecb.v[5]=pnt.b;
    return vecb;
}
 
Point2D_t Vector2Point2D(Vector3D_t vec){
    Point2D_t pnt;
    pnt.x=vec.v[0];
    pnt.y=vec.v[1];
    return pnt;
}
 
Point3D_color_t Vector2Point3D(Vector3D_t veci){
    Point3D_color_t pnt;
    pnt.x=veci.v[0];
    pnt.y=veci.v[1];
    pnt.z=veci.v[2];
    return pnt;
}
 
Vector3D_t operator*(Matrix3D_t a,Vector3D_t b){
    Vector3D_t c;
    int i,j;
    for(i=0;i<3;i++){
        c.v[i]=0;
        for(j=0;j<3;j++)
            c.v[i]+=a.m[i][j]*b.v[j];
    }
    return c;
}
 
Vector3D_t operator +(Vector3D_t a, Vector3D_t b){
    Vector3D_t c;
    for(int i=0; i<3; i++){
        c.v[i]=a.v[i]+b.v[i];
    }
    return c;
}
 
Vector3D_t operator -(Vector3D_t a, Vector3D_t b){
    Vector3D_t c;
 
    for(int i=0; i<3; i++){
        c.v[i]=a.v[i]-b.v[i];
    }
    return c;
}
 
Vector3D_t operator ^(Vector3D_t a,Vector3D_t b){
    Vector3D_t c;
    c.v[0]=a.v[1]*b.v[2]-a.v[2]*b.v[1];
    c.v[1]=a.v[2]*b.v[0]-a.v[0]*b.v[2];
    c.v[2]=a.v[0]*b.v[1]-a.v[1]*b.v[0];
    return c;
}
 
void drawPolygon(Point2D_t pnt[],int n,Color_t c){
    int i;
    setColor(c);
    glBegin(GL_POLYGON);
    for (i=0;i<n;i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}
 
void drawLine(Point2D_t pnt[],int n,Color_t c){
    int i;
    setColor(c);
    glBegin(GL_LINE_LOOP);
    for (i=0;i<n;i++) {
        glVertex2f(pnt[i].x, pnt[i].y);
    }
    glEnd();
}
 
void timer (int value){
    glutPostRedisplay();
    glutTimerFunc(10,timer,0);
}
 
float dot(object3D_t obj, int faceKe){
    Vector3D_t a;
    Vector3D_t b;
    a = operator -(Point2Vector3D(obj.pnt[obj.fc[faceKe].pnt[1]]),
                   Point2Vector3D(obj.pnt[obj.fc[faceKe].pnt[0]]));
 
    b = operator -(Point2Vector3D(obj.pnt[obj.fc[faceKe].pnt[0]]),
                   Point2Vector3D(obj.pnt[obj.fc[faceKe].pnt[2]]));
 
    Vector3D_t k = operator ^(a,b);
    return k.v[2];
 
}
 
object3D_t draw(object3D_t obj,int x,int y,int z){
    n++;
 
    for(i=0;i<obj.NumberofVertices;i++){
        vec[i]=Point2Vector3D(obj.pnt[i]);
    }
    for(i=0;i<obj.NumberofFaces;i++){
 
        for(j=0;j<obj.fc[i].NumberofVertices;j++){
            titik2D[j]=Vector2Point2D(vec[obj.fc[i].pnt[j]]);
        }
        float k = dot(obj,i);
        float red = (obj.pnt[obj.fc[i].pnt[0]].r+
                        obj.pnt[obj.fc[i].pnt[1]].r+
                        obj.pnt[obj.fc[i].pnt[2]].r)/3;
        float green = (obj.pnt[obj.fc[i].pnt[0]].g+
                        obj.pnt[obj.fc[i].pnt[1]].g+
                        obj.pnt[obj.fc[i].pnt[2]].g)/3;
        float blue = (obj.pnt[obj.fc[i].pnt[0]].b+
                        obj.pnt[obj.fc[i].pnt[1]].b+
                        obj.pnt[obj.fc[i].pnt[2]].b)/3;
            Color_t rgb = {red,green,blue};
        if(k>0){
//            drawPolygon(titik2D,obj.fc[i].NumberofVertices,rgb);
            drawLine(titik2D,obj.fc[i].NumberofVertices,rgb);
        }
        //std::cout << "-> face ke" << i << " ==> " << k  <<"\n";
    }
    matrix3DX=rotationX(x);
    matrix3DY=rotationY(y);
    matrix3DZ=rotationZ(z);
    for ( int i=0; i<obj.NumberofVertices; i++){
        vec3D=Point2Vector3D(obj.pnt[i]);
        vec3D=operator *(matrix3DX,vec3D);
        vec3D=operator *(matrix3DY,vec3D);
        vec3D=operator *(matrix3DZ,vec3D);
        obj.pnt[i]=Vector2Point3D(vec3D);
    }
    return obj;
    std::cout << "memutar";
}
 
void userdraw(void) {
    //std::cout << n << " ,";
    huruf1 = draw(huruf1,0,1,0);
    huruf2 = draw(huruf2,1,0,0);
    huruf3 = draw(huruf3,0,1,0);
    huruf4 = draw(huruf4,0,0,1);
 
}
 
object3D_t buatHuruf(){
    object3D_t huruf={
            34, {
                {-200, 100, 50, 0.5,0.6,0.7},
                {-175, 100, 50, 0.5,0.6,0.7},
                {-200, -100, 50, 0.5,0.6,0.7},
                {-175, -100, 50, 0.5,0.6,0.7},
                {0, -200, 50, 0.5,0.6,0.7},
                {0, -175, 50, 0.5,0.6,0.7},
                {175, -200, 50, 0.5,0.6,0.7},
                {175, -175, 50, 0.5,0.6,0.7},
                {175, -450, 50, 0.5,0.6,0.7},
                {200, -450, 50, 0.5,0.6,0.7},
                {200, -425, 50, 0.5,0.6,0.7},
                {250, -425, 50, 0.5,0.6,0.7},
                {250, -450, 50, 0.5,0.6,0.7},
                {175, 100, 50, 0.5,0.6,0.7},
                {200, 100, 50, 0.5,0.6,0.7},
                {0, 175, 50, 0.5,0.6,0.7},
                {0, 200, 50, 0.5,0.6,0.7},
                {-200, 100, -50, 0.5,0.6,0.7},
                {-175, 100, -50, 0.5,0.6,0.7},
                {-200, -100, -50, 0.5,0.6,0.7},
                {-175, -100, -50, 0.5,0.6,0.7},
                {0, -200, -50, 0.5,0.6,0.7},
                {0, -175, -50, 0.5,0.6,0.7},
                {175, -200, -50, 0.5,0.6,0.7},
                {175, -175, -50, 0.5,0.6,0.7},
                {175, -450, -50, 0.5,0.6,0.7},
                {200, -450, -50, 0.5,0.6,0.7},
                {200, -425, -50, 0.5,0.6,0.7},
                {250, -425, -50, 0.5,0.6,0.7},
                {250, -450, -50, 0.5,0.6,0.7},
                {175, 100, -50, 0.5,0.6,0.7},
                {200, 100, -50, 0.5,0.6,0.7},
                {0, 175, -50, 0.5,0.6,0.7},
                {0, 200, -50, 0.5,0.6,0.7}
        }, 62, {
            {3,{1,3,18}},
            {3,{18,3,20}},
            {3,{3,5,20}},
            {3,{20,5,22}},
            {3,{5,7,22}},
            {3,{22,7,24}},
            {3,{30,24,13}},
            {3,{13,24,7}},
            {3,{32,30,15}},
            {3,{15,30,13}},
            {3,{15,1,32}},
            {3,{32,1,18}},
            
            {3,{0,19,2}},
            {3,{0,17,19}},
            {3,{2,21,4}},
            {3,{2,19,21}},
            {3,{4,23,6}},
            {3,{4,21,23}},
            {3,{6,25,8}},
            {3,{6,23,25}},
            {3,{8,25,9}},
            {3,{25,26,9}},
            {3,{9,26,12}},
            {3,{26,29,12}},
            {3,{11,12,28}},
            {3,{28,12,29}},
            {3,{27,10,28}},
            {3,{28,10,11}},
            {3,{14,10,31}},
            {3,{31,10,27}},
            {3,{16,14,33}},
            {3,{33,14,31}},
            {3,{33,17,16}},
            {3,{16,17,0}},
            
            {3,{0,2,1}},
            {3,{1,2,3}},
            {3,{2,4,3}},
            {3,{3,4,5}},
            {3,{4,6,5}},
            {3,{5,6,7}},
            {3,{13,8,14}},
            {3,{14,8,9}},
            {3,{9,11,10}},
            {3,{9,12,11}},
            {3,{15,13,16}},
            {3,{16,13,14}},
            {3,{16,0,15}},
            {3,{15,0,1}},
            {3,{17,18,19}},
            {3,{18,20,19}},
            {3,{19,20,21}},
            {3,{20,22,21}},
            {3,{21,22,23}},
            {3,{22,24,23}},
            {3,{30,31,25}},
            {3,{31,26,25}},
            {3,{26,27,28}},
            {3,{26,28,29}},
            {3,{32,31,30}},
            {3,{33,31,32}},
            {3,{33,32,17}},
            {3,{32,18,17}}
        }
    };
    return huruf;
}
 
object3D_t ubahHuruf(object3D_t obj,int rotx,int roty,int rotz,float skala){
    matrix3DX=rotationX(rotx);
    matrix3DY=rotationY(roty);
    matrix3DZ=rotationZ(rotz);
    matrix3DS=scale2D(skala,skala,skala);
    for ( int i=0; i<obj.NumberofVertices; i++){
        vec3D=Point2Vector3D(obj.pnt[i]);
        vec3D=operator *(matrix3DX,vec3D);
        vec3D=operator *(matrix3DY,vec3D);
        vec3D=operator *(matrix3DZ,vec3D);
        vec3D=operator *(matrix3DS,vec3D);
        obj.pnt[i]=Vector2Point3D(vec3D);
    }
    return obj;
}
 
void initHuruf(){
    huruf1 = buatHuruf();
    huruf1 = ubahHuruf(huruf1,0,0,0,1);
    huruf2 = buatHuruf();
    huruf2 = ubahHuruf(huruf2,90,0,0,0.5);
    huruf3 = buatHuruf();
    huruf3 = ubahHuruf(huruf3,0,90,0,0.25);
    huruf4 = buatHuruf();
    huruf4 = ubahHuruf(huruf4,0,0,90,0.1);
}
 
void tulisKeFile(object3D_t obj,string nama){
    ofstream simpan;
    //std::cout <<nama;
    string path = "/Users/oktaviacitra/characters/" + nama + ".off";
    simpan.open(path.c_str());
    simpan << "COFF" << endl;
    simpan << obj.NumberofVertices <<" "<<obj.NumberofFaces << " 0"<< endl;
    for(i=0;i<obj.NumberofVertices;i++){
        simpan << obj.pnt[i].x/250 <<" ";
        simpan << obj.pnt[i].y/250 <<" ";
        simpan << obj.pnt[i].z/250 <<" ";
 
        simpan << obj.pnt[i].r <<" ";
        simpan << obj.pnt[i].g <<" ";
        simpan << obj.pnt[i].b <<" ";
        simpan << "255";
        simpan << endl;
    }
    for(i=0;i<obj.NumberofFaces;i++){
        simpan << obj.fc[i].NumberofVertices <<" ";
        for(j=0;j<obj.fc[i].NumberofVertices;j++){
            simpan << obj.fc[i].pnt[j] <<" ";
        }
        simpan <<endl;
    }
    simpan.close();
}
 
object3D_t normalise(object3D_t obj){
    double objxmax;
    for(int i = 0; i<obj.NumberofVertices;i++){
        if(objxmax < abs(obj.pnt[i].x))
            objxmax = abs(obj.pnt[i].x);
        if(objxmax < abs(obj.pnt[i].y))
            objxmax = abs(obj.pnt[i].y);
        if(objxmax < abs(obj.pnt[i].z))
            objxmax = abs(obj.pnt[i].z);
    }
    //std::cout << ","<<objxmax ;
    for(int i = 0; i<obj.NumberofVertices;i++){
        obj.pnt[i].x = nmax * (obj.pnt[i].x/objxmax);
        obj.pnt[i].y = nmax * (obj.pnt[i].y/objxmax);
        obj.pnt[i].z = nmax * (obj.pnt[i].z/objxmax);
    }
    return obj;
}
 
double hitungJarak(Point3D_color_t titik1 , Point3D_color_t titik2){
    //printf("x1 %f, x2 %f y1 %f x2 %f z1 %f z2 %f",titik1.x,titik2.x,titik2.y,titik2.y,titik1.z,titik2.z);
    double x = pow(titik1.x-titik2.x,2);
    double y = pow(titik1.y-titik2.y,2);
    double z = pow(titik1.z-titik2.z,2);
    return sqrt(x+y+z);
}
 
double herosFormula(double a,double b, double c){
    return sqrt(  (a+b+c)/2
             * ( (a+b+c)/2 - a)
             * ( (a+b+c)/2 - b)
             * ( (a+b+c)/2 - c));
}
 
void calculateArea(object3D_t obj){
    double totalArea = 0 ;
    for(int i = 0; i<obj.NumberofFaces;i++){
        double sisi1 = hitungJarak(obj.pnt[obj.fc[i].pnt[0]],obj.pnt[obj.fc[i].pnt[1]]);
        double sisi2 = hitungJarak(obj.pnt[obj.fc[i].pnt[0]],obj.pnt[obj.fc[i].pnt[2]]);
        double sisi3 = hitungJarak(obj.pnt[obj.fc[i].pnt[2]],obj.pnt[obj.fc[i].pnt[1]]);
        //printf("\n sisi1 %d sisi2 %d sisi3 %d",sisi1,sisi2,sisi3);
        double area = herosFormula(sisi1,sisi2,sisi3);
        //printf("\n%d , -> %lf",i,area);
        totalArea = totalArea + area;
    }
    std::cout << "total area " << totalArea << "\n\n";
    return totalArea;
}
 
object3D_t ave(object3D_t obj){
    printf("\n------------------------------------");
    float x,y,z;
    for(int i = 0; i<obj.NumberofVertices;i++){
        x+= obj.pnt[i].x;
        y+= obj.pnt[i].y;
        z+= obj.pnt[i].z;
    }
    x=x/obj.NumberofVertices;
    y=y/obj.NumberofVertices;
    z=z/obj.NumberofVertices;
    std::cout << endl ;
    std::cout << "x rat : " << x << endl;
    std::cout << "y rat : " << y << endl;
    std::cout << "z rat : " << z << endl;
    obj = normalise(obj);
    calculateArea(obj);
    return obj;
}
 
object3D_t bacaKeObjek(object3D_t obj, string nama){
    std::cout <<"\n\n\n" <<nama;
    string temp;
    ifstream masuk;
    //string path = "C:/Users/M Aliffiansyah/Documents/Kuliah/sm5/Grafika Komputer/txtfile/"+nama+".txt";
    string path = "/Users/oktaviacitra/characters/" + nama + ".off";
    masuk.open(path.c_str());
    string tulisan;
    getline(masuk,tulisan);//coff
 
    masuk >> obj.NumberofVertices;
    masuk >> obj.NumberofFaces;
    masuk >> temp;
    for(int i = 0; i<obj.NumberofVertices;i++){
        masuk >> obj.pnt[i].x;
        obj.pnt[i].x*=250;
        masuk >> obj.pnt[i].y;
        obj.pnt[i].y*=250;
        masuk >> obj.pnt[i].z;
        obj.pnt[i].z*=250;
        masuk >> obj.pnt[i].r;
        masuk >> obj.pnt[i].g;
        masuk >> obj.pnt[i].b;
        masuk >> temp;
    }
    for(int i = 0; i<obj.NumberofFaces;i++){
        masuk >> obj.fc[i].NumberofVertices;
        for(int j = 0; j<obj.fc[i].NumberofVertices;j++){
            masuk >> obj.fc[i].pnt[j];
        }
    }
    obj = ave(obj);
    return obj;
}
 
void tulisHuruf(){
    tulisKeFile(huruf1,"huruf1");
    tulisKeFile(huruf2,"huruf2");
    tulisKeFile(huruf3,"huruf3");
    tulisKeFile(huruf4,"huruf4");
}
 
void bacaHuruf(){
//    string huruf = "";
    huruf1 = bacaKeObjek(huruf1,"Q");
//    huruf2 = bacaKeObjek(huruf2,"huruf2");
//    huruf3 = bacaKeObjek(huruf3,"huruf3");
//    huruf4 = bacaKeObjek(huruf4,"huruf4");
}
 
void display(void) {
    glClear( GL_COLOR_BUFFER_BIT);
    userdraw();
    glutSwapBuffers();
}
 
int main(int argc, char **argv){
    glutInit(&argc,argv);
//    initHuruf();
//    tulisHuruf();
    bacaHuruf();
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition(10,10);
    glutInitWindowSize(1000,1000);
    glutCreateWindow ("2110171018 Oktavia Citra");
    glClearColor(0.412, 0.518, 0.455, 1.0);
    gluOrtho2D(-500, 500, -500, 500);
    glutDisplayFunc(display);
    glutTimerFunc(1,timer,0);
    glutMainLoop();
    return 0;
}
