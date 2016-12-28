// Draw an Icosahedron
// ECE4893/8893 Project 4
// Ibrahim Khan

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

#define NFACE 20
#define NVERTEX 12

#define X .525731112119133606 
#define Z .850650808352039932

static float updaterate = 10.0;
int depth;

// These are the 12 vertices for the icosahedron
static GLfloat vdata[NVERTEX][3] = {
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};

// These are the 20 faces.  Each of the three entries for each 
// vertex gives the 3 vertices that make the face.
static GLint tindices[NFACE][3] = {
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

int testNumber; // Global variable indicating which test number is desired
void DrawTriangle(GLfloat* v1, GLfloat* v2, GLfloat* v3)
{
  // Drawing triangles with each face having a different color
  glBegin(GL_TRIANGLES);
    glColor3f(0.0,0.0,1.0); // Diffrent color for each face
    glVertex3fv(v1); glVertex3fv(v2); glVertex3fv(v3);
  glEnd();

  glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 1.0, 1.0); // White lines
    glVertex3fv(v1); glVertex3fv(v2); glVertex3fv(v3);
  glEnd();

}
void normalize(GLfloat v[3])
{
  GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  v[0] /= d; v[1] /= d; v[2] /= d;
}

void subdivide(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth)
{
  GLfloat v12[3], v23[3], v31[3];

  if (depth == 0) {
      DrawTriangle(v1, v2, v3);
    return;
  }

  for (int i = 0; i < 3; i++) {
    v12[i] = (v1[i]+v2[i])/2.0; v23[i] = (v2[i]+v3[i])/2.0; v31[i] = (v3[i]+v1[i])/2.0;
  }
  
  normalize(v12); normalize(v23); normalize(v31);

  subdivide(v1, v12, v31, depth-1); subdivide(v2, v23, v12, depth-1); subdivide(v3, v31, v23, depth-1); subdivide(v12, v23, v31, depth-1);
}

// Test cases.  Fill in your code for each test case
void Test1()
{
 
  for (int i = 0; i < NFACE; i++)
  {
    DrawTriangle(vdata[tindices[i][0]], 
    	vdata[tindices[i][1]], 
    	vdata[tindices[i][2]]);
  }

}

void Test2()
{
  static GLfloat rot = 0.0;
  glRotatef(rot, 1.0, 1.0, 0.0); // Rotate about X-axis  //can we do 1,1?
  //glRotatef(rotY, 0.0, 1.0, 0.0); // Rotate about Y-axis
  rot+= 1.0;

    //if(rot == (GLfloat)360.0) rot = (GLfloat)0.0;

    //if(rotY == (GLfloat)360.0) rotY = (GLfloat)0.0;

    Test1();
}

void Test3()
{
  for (int i = 0; i < NFACE; i++) {
    subdivide(vdata[tindices[i][0]],
              vdata[tindices[i][1]],
        vdata[tindices[i][2]],1);
  }
}

void Test4()
{

  static GLfloat rot = 0.0;
  glRotatef(rot, 1.0, 1.0, 0.0); // Rotate about X-axis  //can we do 1,1?
  //glRotatef(rotY, 0.0, 1.0, 0.0); // Rotate about Y-axis
  rot+= 1.0;

  Test3();

}

void Test5(int depth)
{
	if (depth > 5)
    {
      cout << "depth > 5 not valid" << endl;
      exit(1);
    }
	  for (int i = 0; i < NFACE; i++) {
    subdivide(vdata[tindices[i][0]],
              vdata[tindices[i][1]],
        vdata[tindices[i][2]],depth);
  }
}

void Test6(int depth)
{
  static GLfloat rot = 0.0;
  glRotatef(rot, 1.0, 1.0, 0.0);
  rot+= 1.0;
  Test5(depth);
}
void timer(int)
{
  glutPostRedisplay();
  glutTimerFunc(1000.0/updaterate, timer, 0);
}

void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  //glEnable(GL_LINE_SMOOTH);
  glShadeModel(GL_SMOOTH);
  glLineWidth(2.0);
  
}
void display(void)
{

//DICKS!!!!!!

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);				//clear buffers to preset values
  glEnable(GL_DEPTH_TEST|GL_LINE_SMOOTH);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0,2.00 , 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glTranslatef(250, 250, 0);
  glScalef(200.0, 200.0, 200);

  if (testNumber == 1) Test1();
  if (testNumber == 2) Test2();
  if (testNumber == 3) Test3();
  if (testNumber == 4) Test4();
  if (testNumber == 5) Test5(depth);
  if (testNumber == 6) Test6(depth); 
  if (testNumber > 6 || testNumber < 1 ) cout << "invalid test" << endl;
  glutSwapBuffers(); 
}
void reshape(int w, int h)
{
/*
  GLfloat aspect = (GLfloat) w / (GLfloat) h;
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    glOrtho(-1, 1, -1 * aspect, 1 * aspect, -2.0, 2.0);
  else
    glOrtho(-1 * aspect, 1 * aspect, -1, 1, -2.0, 2.0);
  glMatrixMode(GL_MODELVIEW);

  glutPostRedisplay();*/
  glViewport(0,0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, (GLdouble)w, (GLdouble)0.0, h, (GLdouble)w, (GLdouble)-w);
  //glFrustum(0.0, (GLdouble)w, (GLdouble)0.0, h, (GLdouble)1, (GLdouble)40);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      std::cout << "Usage: icosahedron testnumber" << endl;
      exit(1);
    }
  // Set the global test number
  testNumber = atol(argv[1]);
  if (argc > 2) depth = atoi(argv[2]);
  // Initialize glut  and create your window here
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize (500,500);
  glutInitWindowPosition (100, 100);
  glutCreateWindow("Icosahedron");
  init();
  // Set your glut callbacks here
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(1000.0/updaterate , timer, 0);
  // Enter the glut main loop here
  glutMainLoop();
  return 0;
}
