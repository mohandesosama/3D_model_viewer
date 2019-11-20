#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
//#include <fstream>
//#include <cmath>

float cam_theta = 45.0; // camera rotation angle - theta
float cam_phi = 45.0; // camera rotation angle - phi

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
    glColor3f(1.0, 1.0, 1.0);
	
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


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< display >>>>>>>>>>>>>>>>>>>>>>
void display(void)
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

	glTranslatef(0.0, 0.0, -10.0);
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
		GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; 
		//GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 }; 
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	

		//glColor3d(0,0,0); // black lines for wireframe
		//glutSolidSphere(1.0, 20, 20);
		//glutSolidCube(1.0);
		glutSolidTeapot(1.0);
	}

	glFlush();
	//glutSwapBuffers();
}

void myKeyboard(unsigned char Key, int mouseX, int mouseY)
// Deals with normal keys
{
	switch (Key)	{
		case 't': 
			display();
			glFlush();
			//glutSwapBuffers();
			break;
		case 'k': 
			cam_theta += 2;
			display();
			glFlush();
			//glutSwapBuffers();
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

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
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
}