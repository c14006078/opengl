#include<GL/glut.h>
#include<math.h>
#define PI 3.14159265
GLint POINTS = 20;
GLint radius = 10;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -1.0, 1.0);
}

void rectangle(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    
    //glBegin(GL_POLYGON);
    glBegin(GL_LINE_LOOP);
	int i;
	for (i = 0; i < POINTS; i++) {
	    GLfloat angle = 2 * PI * i / POINTS;
            glVertex2f(cos(angle) * radius, sin(angle) * radius);
	}
    glEnd();

    glFlush();
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("opengl sample: rectangle.");

    init();
    glutDisplayFunc(rectangle);
    glutMainLoop();
}
