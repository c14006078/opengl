#include<GL/glut.h>

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    // gluOrtho2D(0.0, 400.0, 0.0, 300.0);
    gluOrtho2D(0.0, 4.0, 0.0, 3.0);
}

void lineSegment(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

#if 0    
    glBegin(GL_TRIANGLES);
        glVertex2i(200, 200);
        glVertex2i(200, 100);
        glVertex2i(300, 100);
    glEnd();
#endif

    glTranslatef(0.5, 0.5, 0.0);
    // glutWireCube(1.0);
    // glutSolidCube(1.0);
    glutWireSphere(1.0, 10, 12);

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
