#include<GL/glut.h>
#include<math.h>
#define PI 3.14159265
GLint POINTS = 100;
GLint radius = 40;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

void lineCircle(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
   
    glTranslatef(50.0, 50.0, 0.0); 
    //glBegin(GL_LINE_LOOP);
    glBegin(GL_POLYGON);
	int i;
	for (i = 0; i < POINTS; i++) {
	    GLfloat angle = 2 * PI * i / POINTS;
            glVertex2f(cos(angle) * radius, sin(angle) * radius);
	}
	/*glVertex2i(100, 100);
	glVertex2i(100, 200);
	glVertex2i(200, 200);*/
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
