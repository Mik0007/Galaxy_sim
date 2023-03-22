/*
 * OGL02Animation.cpp: 3D Shapes with animation
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include "Custom_data_IO.h"
 
/* Global variables */
char title[] = "3D Shapes with animation";
int refreshMills = 50;        // refresh interval in milliseconds [NEW]
int T = 1;
 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
 
void cube(float x, float y, float z)
{
	// Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef((GLfloat) x, (GLfloat) y, (GLfloat) z);  // Move right and into the screen
    GLfloat size = 0.3f;
 
   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
//      // Top face (y = 1.0f)
//      // Define vertices in counter-clockwise (CCW) order with normal pointing out
//      glColor3f(0.0f, 1.0f, 0.0f);     // Green
////      glVertex3f( 1.0f, 1.0f, -1.0f);
////      glVertex3f(-1.0f, 1.0f, -1.0f);
////      glVertex3f(-1.0f, 1.0f,  1.0f);
////      glVertex3f( 1.0f, 1.0f,  1.0f);
//	  glVertex3f( size,  size, -size);
//      glVertex3f(-size,  size, -size);
//      glVertex3f(-size,  size, size);
//      glVertex3f( size,  size, size);
//// 
////      // Bottom face (y = -1.0f)
//      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
////      glVertex3f( 1.0f, -1.0f,  1.0f);
////      glVertex3f(-1.0f, -1.0f,  1.0f);
////      glVertex3f(-1.0f, -1.0f, -1.0f);
////      glVertex3f( 1.0f, -1.0f, -1.0f);
//	  glVertex3f( size, -size, size);
//      glVertex3f(-size, -size, size);
//      glVertex3f(-size, -size,-size);
//      glVertex3f( size, -size,-size);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( size,  size, size);
      glVertex3f(-size,  size, size);
      glVertex3f(-size, -size, size);
      glVertex3f( size, -size, size);
 
////      // Back face (z = -1.0f)
//      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
////      glVertex3f( 1.0f, -1.0f, -1.0f);
////      glVertex3f(-1.0f, -1.0f, -1.0f);
////      glVertex3f(-1.0f,  1.0f, -1.0f);
////      glVertex3f( 1.0f,  1.0f, -1.0f);
//	  glVertex3f( size, -size,-size);
//      glVertex3f(-size, -size,-size);
//      glVertex3f(-size,  size,-size);
//      glVertex3f( size,  size,-size);
//// 
////      // Left face (x = -1.0f)
//      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
////      glVertex3f(-1.0f,  1.0f,  1.0f);
////      glVertex3f(-1.0f,  1.0f, -1.0f);
////      glVertex3f(-1.0f, -1.0f, -1.0f);
////      glVertex3f(-1.0f, -1.0f,  1.0f);
//	  glVertex3f(-size,  size, size);
//      glVertex3f(-size,  size,-size);
//      glVertex3f(-size, -size,-size);
//      glVertex3f(-size, -size, size);
//// 
////      // Right face (x = 1.0f)
//      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
////      glVertex3f(1.0f,  1.0f, -1.0f);
////      glVertex3f(1.0f,  1.0f,  1.0f);
////      glVertex3f(1.0f, -1.0f,  1.0f);
////      glVertex3f(1.0f, -1.0f, -1.0f);
//	  glVertex3f( size,  size,-size);
//      glVertex3f( size,  size, size);
//      glVertex3f( size, -size, size);
//      glVertex3f( size, -size,-size);
      
   glEnd();  // End of drawing color-cube
}
 
 
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
 	//limite alto dx
// 	cube( 75, 40, -100);
 	
 	
 	double n = 4*pow(10, 12);
	double m = n * 9 / 16;
	double bounds[6] = {-n, n, -m, m, -m, m};
 	
 	int totbodies = 600;
	vec3D* vec = binary_import2("Data/Binary_Data/orbiting_data" + to_string(T) + ".dat",
								totbodies);
	
	float x,y,z;
	
	for (int i = 0; i < totbodies; i++)
	{
		double scale_x = (bounds[1] - bounds[0])/(2* 75);
		double scale_y = (bounds[3] - bounds[2])/(2* 40);
//		double scale_z = (bounds[5] - bounds[4])/(height / 2);

		x = (vec[i].x / scale_x);
		y = (vec[i].y / scale_y);
// 		z = (vec[i].z / scale_z) - (bounds[4] / scale_z);
		
 		cube( x, y, -100);
	}
	T++;
	
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
 
/* Called back when timer expired [NEW] */
void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(600, 600);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
