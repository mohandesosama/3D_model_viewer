// Mesh3DViewr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<GL/glut.h>
#include "Mesh.h"
#pragma comment (lib, "opengl32.lib") /* link with Microsoft OpenGL lib */
#pragma comment (lib, "glu32.lib") /* link with OpenGL Utility lib */
#pragma comment (lib, "glut32.lib") /* link with Win32 GLUT lib */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
//#include <fstream>
//#include <cmath

float cam_theta = 45.0; // camera rotation angle - theta
float cam_phi = 45.0; // camera rotation angle - phi
int model_num=3;
int color_counter=3; //don't start with 0 as it will be black.
int trans_mode=1; //this value 1 for rotation 2 translation 3 scaling
int x_rot=0,y_rot=0,z_rot=0; //rotation angle for the model
float x_trans=0,y_trans=0,z_trans=0; //translation value for the model
float scale=1.0; // scale value for the model
int obj_mode=2;

Mesh my3VNMesh; //the 3vn file used which was wineglass.3vn file
Mesh arbit3VNMesh;
//<<<<<<<<<<<<<<<<<<< axis >>>>>>>>>>>>>>
void axis(double length)
{ // draw a z-axis, with cone at end
	glPushMatrix();
	glBegin(GL_LINES);
	   glVertex3d(0, 0, 0); glVertex3d(0, 0, length); // along the z-axis
	glEnd();
	glTranslated(0, 0,length -0.2); 
	//glutWireCone(0.04, 0.2, 12, 9);
	glutSolidCone(0.04, 0.2, 12, 9);
	glPopMatrix();
}	

void Init()
{
	//read the mesh file
	my3VNMesh.readFile("WINEGLASS.3VN");
	arbit3VNMesh.readFile("PAWN.3VN");
	// set properties of the surface material
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 }; // gray
	GLfloat mat_diffuse[] = { 0.6, 0.0, 0.0, 1.0 }; 
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; 
	GLfloat mat_shininess[] = { 50.0 }; 
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// Set the lights
	GLfloat light_intensity[] = {0.8, 0.8, 0.8, 1.0};
	GLfloat light_position[] = {0, 10, 10, 1}; 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
	//float local_view[] = {0.0};
	//glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glClearColor(0.97, 0.78, 0.64, 0.0);  // background color
    //glColor3f(1.0, 1.0, 1.0);
	
	// set the camera
	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	
	// Parallel projection
	//int factor = 2;
	//glOrtho(-factor * 64/48.0, factor * 64/48.0, -factor, factor, 0.1, 1000);
	// Pespective projection
	//gluPerspective(10, 64/48.0, 0.1, 1000);
	gluPerspective(20, 64/48., 0.1, 1000);

	glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_MORE);
	
    //glFrontFace(GL_CW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
}

static void Reshape(int w, int h)
{

    glViewport(0, 0, (GLint)w, (GLint)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-6.0, 6.0, -6.0, 6.0, -1.0, 10.0);
	gluPerspective(20, w/(double)h, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void jackPart()
{ // draw one axis of the unit jack - a stretched sphere
	glPushMatrix();
	glScaled(0.2,0.2,1.0);
	glutSolidSphere(1,15,15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0,1.2); // ball on one end
	glutSolidSphere(0.2,15,15);
	glTranslated(0,0, -2.4);
	glutSolidSphere(0.2,15,15); // ball on the other end
	glPopMatrix();
}
//<<<<<<<<<<<<<<<<<<< jack >>>>>>>>>>>>>>>>>>>>
void jack()
{ // draw a unit jack out of spheroids
	glPushMatrix();
	jackPart();
	glRotated(90.0, 0, 1, 0);
	jackPart();
	glRotated(90.0, 1,0,0);
	jackPart();
	glPopMatrix();
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< display >>>>>>>>>>>>>>>>>>>>>>
void display()
{
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-6.0, 6.0, -6.0, 6.0, -1.0, 10.0);
	//gluPerspective(60, w/(double)h, 0.1, 1000);
	gluPerspective(20, 64/48., 0.1, 1000);
	// set the View matrix
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0); // Camera initially points to -z direction

	glTranslatef(0.0, 0.0, -10);
	glRotated(cam_phi, 1, 0, 0); // Camera rotation (phi)
	glRotated(-cam_theta, 0, 1, 0); // Camera rotation (theta)

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen
	{
		GLfloat mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

		glColor3d(0,0,1); // blue lines for wireframe
		axis(2);		 // z-axis
	}
	glPushMatrix(); 
	{
		GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 }; 	
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	
		glRotated(90, 0, 1.0, 0);
		glColor3d(1,0,0); // red lines for wireframe
		axis(2);		// x-axis
	}
	glPopMatrix();	
	glPushMatrix();	
	{
		GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	
		glRotated(-90.0, 1, 0, 0);
		glColor3d(0,1,0); // green lines for wireframe
		axis(2);		// y-axis
	}
	glPopMatrix();	
	{

		//rotate the model
		glRotated(x_rot, 1.0,0.0,0.0);
		glRotated(y_rot, 0.0,1.0,0.0);
		glRotated(z_rot, 0.0,0.0,1.0);
		//translate the model
		glTranslatef(x_trans, y_trans, z_trans);
		//scale the model
		glScalef(scale,scale,scale);
		if(obj_mode==0)
		{
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		}
		else
		{
			glEnable(GL_LIGHTING);
		    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		}
		//Get the current color counter and convert it to binary
		//That will give different diffusion color related to the 
		//value of the color_counter;
		int cc=color_counter;
		int c=0;
		int bin[4];
		int rem=0;
		while(c<4)
		{
			rem=cc%2;
			cc /= 2;
			bin[c++]=rem;
		}
		//put the corresponding binary value into the diffusion matrix
		GLfloat mat_diffuse[] = { bin[0], bin[1], bin[2], bin[3] }; 
		//GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	
		//glColor3d(0,1,1);
		switch(model_num)
		{
		case 1:
			glutSolidCube(1.0);
			break;
		case 2:
			glutSolidTeapot(1.0);
			break;
		case 3:
			my3VNMesh.Draw();
			break;
		case 4:
			jack();
			break;
		case 5:
			arbit3VNMesh.Draw();
			break;
		}
		//glColor3d(0,0,0); // black lines for wireframe
		//glutSolidSphere(1.0, 20, 20);
		
		//
	}

	glFlush();
	//glutSwapBuffers();
}

void myKeyboard(unsigned char Key, int mouseX, int mouseY)
// Deals with normal keys
{
	switch (Key)	{
		case 'k': 
			cam_theta += 2;
			display();
			glFlush();
			//glutSwapBuffers();
			break;
		case 'm':
			//kep number of colors to 5 colors
			//starting from 0 ends with 4 and then
			//returning back to 0 
			color_counter=color_counter++%5;
			display();
			glFlush();
			break;
		case '1':
			model_num=1;
			display();
			glFlush();
			break;
		case '2':
			model_num=2;
			display();
			glFlush();
			break;
		case '3':
			model_num=3;
			display();
			glFlush();
			break;
		case '4':
			model_num=4;
			display();
			glFlush();
			break;
		case '5':
			model_num=5;
			display();
			glFlush();
			break;
		case 'r':
			trans_mode=1; //Rotation
			break;
		case 't':
			trans_mode=2; //Translation
			break;
		case 's':
			trans_mode=3; //Scaling
			break;
		case 'x':
			if (trans_mode==1)
				x_rot=x_rot++%360;
			else if(trans_mode==2)
				x_trans++;
			else if(trans_mode==3)
			{
				scale+=0.1;
				if(scale > 1) scale = 1;
			}
			display();
			glFlush();
			break;
		case 'X':
			if (trans_mode==1)
				x_rot=x_rot--%360;
			else if(trans_mode==2)
				x_trans--;
			else if(trans_mode==3)
			{
				scale-=0.1;
				if(scale < 0) scale=0;
			}
			display();
			glFlush();
			break;
		case 'y':
			if (trans_mode==1)
				y_rot=y_rot++%360;
			else if(trans_mode==2)
				y_trans++;
			else if(trans_mode==3)
			{
				scale+=0.1;
				if(scale > 1) scale = 1;
			}
			display();
			glFlush();
			break;
		case 'Y':
			if (trans_mode==1)
				y_rot=y_rot--%360;
			else if(trans_mode==2)
				y_trans--;
			else if(trans_mode==3)
			{
				scale-=0.1;
				if(scale < 0) scale=0;
			}
			display();
			glFlush();
			break;
		case 'z':
			if (trans_mode==1)
				z_rot=z_rot++%360;
			else if(trans_mode==2)
				z_trans++;
			else if(trans_mode==3)
			{
				scale+=0.1;
				if(scale > 1) scale = 1;
			}
			display();
			glFlush();
			break;
		case 'Z':
			if (trans_mode==1)
				z_rot=z_rot--%360;
			else if(trans_mode==2)
				z_trans--;
			else if(trans_mode==3)
			{
				scale-=0.1;
				if(scale < 0) scale=0;
			}
			display();
			glFlush();
			break;
		case 'd':
			trans_mode=1; //this value 1 for rotation 2 translation 3 scaling
			x_rot=0;y_rot=0;z_rot=0; //rotation angle for the model
			x_trans=0;y_trans=0;z_trans=0; //translation value for the model
			scale=1.0;
			display();
			glFlush();
			break;
		case 'w':
			
			if(obj_mode==0)
				glShadeModel(GL_FLAT);
			else 
				glShadeModel(GL_SMOOTH);
			obj_mode++;if(obj_mode > 2) obj_mode=0;
			display();
			glFlush();
			break;
	}
}

void mySpecialKeyboard(int Key, int mouseX, int mouseY)
// Deals with special keys
{
	switch (Key)	{
		case GLUT_KEY_RIGHT: // increase theta
			cam_theta += 2;
			display();
			//glFlush();
			glutPostRedisplay();
			//glutSwapBuffers();
			break;
		case GLUT_KEY_LEFT: // increase theta
			cam_theta -= 2;
			display();
			//glFlush();
			glutPostRedisplay();
			//glutSwapBuffers();
			break;
		case GLUT_KEY_UP: // increase phi
			cam_phi += 2;
			display();
			//glFlush();
			glutPostRedisplay();
			//glutSwapBuffers();
			break;
		case GLUT_KEY_DOWN: // increase phi
			cam_phi -= 2;
			display();
			//glFlush();
			glutPostRedisplay();
			//glutSwapBuffers();
			break;
	}
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH ); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH ); 
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3D Mesh Viewer");
	Init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glEnable(GL_LIGHTING); // enable the light source
	glEnable(GL_LIGHT0); // use this specific light
	//glShadeModel(GL_FLAT); // shading method
	glShadeModel(GL_SMOOTH); // shading method
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0.97, 0.78, 0.64, 0.0);  // background color
	glViewport(0, 0, 640, 480);
	glutMainLoop();
	return 0;
}
