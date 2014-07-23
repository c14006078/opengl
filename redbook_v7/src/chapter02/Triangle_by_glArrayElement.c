#include<GL/glut.h>
#include<math.h>

#define PI 3.14159265
GLint POINTS = 100;
GLint radius = 40;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);

/*	glShadeModel(GL_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);					// seems that openGL will draw gradient by default if vertices' colors are different.
*/  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

void lineCircle(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    static GLint vertices[] = { 
				25, 25,
				100, 325,
				175, 25,
				250, 25,
				325, 325};

    static GLfloat colors[] = {
				1.0, 0.2, 0.2,
				0.2, 0.2, 1.0,
				0.8, 1.0, 0.2,
				0.75, 0.75, 0.75,
				0.35, 0.35, 0.35,
				0.5, 0.5, 0.5};

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(2, GL_INT, 0, vertices);
   
    glBegin(GL_POLYGON);
        glArrayElement(0);
        glArrayElement(1);
        glArrayElement(2);
        glArrayElement(3);
        glArrayElement(4);
        glArrayElement(5);
    glEnd();

    // glutSwapBuffers();	// Will not show the geometries if double buffer is created, but glutSwapBuffers() is not called.
    glFlush();				// Will not show the geometries if glFlush() is not called.
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);		// must swap buffer in this case.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("A sample opengl app.");

    init();
    glutDisplayFunc(lineCircle);
    glutMainLoop();
}
