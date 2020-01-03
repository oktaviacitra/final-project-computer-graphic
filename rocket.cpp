//
//  main.cpp
//  Prisma
//
//  Created by Oktavia Citra on 01/12/19.
//  Copyright © 2019 Oktavia Citra. All rights reserved.
//

#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>
void stars();
int p;
void rocket_to_cam_pos();
float i,j,count=0,count1=0,count3=0,flag=0,flag1=0,t=0,f=0,flag3=0;

void control()
{
    count1++;
    rocket_to_cam_pos();
}

void stars()
{
    glColor3f(0.965, 0.788, 0.055);
    glPointSize(1.37);
    glBegin(GL_POINTS);
    glVertex2i(10,20);
    glVertex2i(20,100);
    glVertex2i(30,10);
    glVertex2i(15,150);
    glVertex2i(17,80);
    glVertex2i(200,200);
    glVertex2i(55,33);
    glVertex2i(400,300);
    glVertex2i(330,110);
    glVertex2i(125,63);
    glVertex2i(63,125);
    glVertex2i(20,10);
    glVertex2i(110,330);
    glVertex2i(440,430);
    glVertex2i(32,65);
    glVertex2i(110,440);
    glVertex2i(210,230);
    glVertex2i(390,490);
    glVertex2i(12,90);
    glVertex2i(400,322);
    glVertex2i(420,366);
    glVertex2i(455,400);
    glVertex2i(20,20);
    glVertex2i(111,120);
    glVertex2i(401,200);
    glVertex2i(230,30);
    glVertex2i(220,20);
    glVertex2i(122,378);
    glVertex2i(133,340);
    glVertex2i(345,420);
    glVertex2i(130,360);
    glVertex2i(333,120);
    glVertex2i(250,22);
    glVertex2i(242,11);
    glVertex2i(280,332);
    glVertex2i(233,40);
    glVertex2i(210,418);
    glVertex2i(256,12);
    glVertex2i(288,232);
    glVertex2i(247,36);
    glVertex2i(229,342);
    glVertex2i(257,47);
    glVertex2i(290,63);
    glVertex2i(232,72);
    glVertex2i(243,143);
    glVertex2i(100,200);
    glVertex2i(90,250);
    glVertex2i(80,225);
    glVertex2i(50,333);
    glVertex2i(60,350);
    glVertex2i(243,143);
    glVertex2i(243,143);
    glEnd();
}


void rocket_to_cam_pos()
{
    count++;
    count3++;
    for(i=0;i<=500;i++)
    {
        glClearColor(0.169, 0.169, 0.157, 1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        stars();
        glColor3f(0.231, 0.035, 0.267);
        glBegin(GL_POLYGON);
        glVertex2f(237.5,20.0+i);
        glVertex2f(262.5,20.0+i);
        glVertex2f(262.5,120.0+i);
        glVertex2f(237.5,120.0+i);
        glEnd();
        glColor3f(0.631, 0.145, 0.349);
        glBegin(GL_POLYGON);
        glVertex2f(237.5,120.0+i);
        glVertex2f(262.5,120.0+i);
        glVertex2f(250,170.0+i);
        glEnd();
        glColor3f(0.373, 0.094, 0.329);
        glBegin(GL_POLYGON);
        glVertex2f(237.5,120.0+i);
        glVertex2f(217.5,95.0+i);
        glVertex2f(237.5,95.0+i);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(237.5,20.0+i);
        glVertex2f(217.5,20.0+i);
        glVertex2f(237.5,70.0+i);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(262.5,20.0+i);
        glVertex2f(282.5,20.0+i);
        glVertex2f(262.5,70.0+i);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(262.5,120.0+i);
        glVertex2f(262.5,95.0+i);
        glVertex2f(282.5,95.0+i);
        glEnd();
        glColor3f(0.945, 0.733, 0.835);
        glBegin(GL_POLYGON);
        glVertex2f(237.5,20.0+i);
        glVertex2f(244.5,20.0+i);
        glVertex2f(241,0.0+i);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(246.5,20.0+i);
        glVertex2f(253.5,20.0+i);
        glVertex2f(249.5,0.0+i);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(262.5,20.0+i);
        glVertex2f(255.5,20.0+i);
        glVertex2f(258.5,0.0+i);
        glEnd();
        p=p+1;
        for(j=0;j<=1000000;j++);
        glutSwapBuffers();
        glutPostRedisplay();
        glFlush();
    }
}

void display()
{
    control();
    glFlush();
}

void myinit()
{
    glClearColor(0.196078  ,0.6 ,0.8,1.0);
    glPointSize(1.0);
    gluOrtho2D(0.0,499.0,0.0,499.0);
}

int main(int argc,char*argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("rocket");
    myinit();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
