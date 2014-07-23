#include<GL/glut.h>

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 20.0, 0.0, 15.0);
    // gluOrtho2D(0.0, 20.0, 0.0, 15.0);
}

void lineSegment(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glPointSize(4.0);
    glPushMatrix();						// Why the drawing will be wrong when without push and pop matrix: glTranslatef(3.0, 1.0, 0.0); then glTranslatef(0.0, 4.0, 0.0), glTranslatef(0.0, 4.0, 0.0);
    glTranslatef(3.0, 1.0, 0.0);
    glBegin(GL_POINTS);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 3.0);
        glVertex2f(4.0, 3.0);
        glVertex2f(6.0, 1.5);
        glVertex2f(4.0, 0.0);
    glEnd();
    glPopMatrix();

    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(3.0, 5.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 3.0);
        glVertex2f(4.0, 3.0);
        glVertex2f(6.0, 1.5);
        glVertex2f(4.0, 0.0);
    glEnd();
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(3.0, 9.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 3.0);
        glVertex2f(4.0, 3.0);
        glVertex2f(6.0, 1.5);
        glVertex2f(4.0, 0.0);
    glEnd();
    glPopMatrix();

    glFlush();
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("A sample opengl app.");

    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();
}
