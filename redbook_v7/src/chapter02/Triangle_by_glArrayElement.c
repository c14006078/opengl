#include<GL/glut.h>
#include<math.h>
#define PI 3.14159265
GLint POINTS = 100;
GLint radius = 40;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

void lineCircle(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    static GLint vertices[] = { 25, 25,
				100, 325,
				175, 25,
				250, 25,
				325, 325};

    static GLfloat colors[] = { 1.0, 0.2, 0.2,
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
        glArrayElement(2);
        glArrayElement(3);
        glArrayElement(4);
    glEnd();

    glFlush();
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("A sample opengl app.");

    init();
    glutDisplayFunc(lineCircle);
    glutMainLoop();
}
