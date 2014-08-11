#include <GL/glut.h>

float location = 4.0;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

/*    float vertices[] = {-1.0, 0.0,		// Why this is wrong? 
                        1.0, 0.0,
                        0.0, 3.0};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
*/
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float vertices[] = {-2.0, 0.0,
                        2.0, 0.0,
                        0.0, 6.0};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);

    glColor3f(1.0, 0.0, 0.0);
    glLoadIdentity();				// can use glPushMatrix, glPopMatrix too.
    // glPushMatrix();
    glTranslatef(-10.0, 10.0, 0.0);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    // glPopMatrix();

    glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);
    glColor3f(0.0, 1.0, 0.0);
    glLoadIdentity();
    // glPushMatrix();
    glTranslatef(10.0, 10.0, 0.0);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    // glPopMatrix();

	glLineStipple(1, 0xF00F);
    glColor3f(0.0, 0.0, 1.0);
    glLoadIdentity();
    // glPushMatrix();
    glTranslatef(-10.0, -10.0, 0.0);
    glScalef(1.5, 0.5, 1.0);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    // glPopMatrix();

	glLineStipple(1, 0x8888);
    glColor3f(1.0, 0.0, 1.0);
    glLoadIdentity();
    // glPushMatrix();
    glTranslatef(10.0, -10.0, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    // glPopMatrix();

    glDisable(GL_LINE_STIPPLE);
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20.0, 20.0,
               -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    glLoadIdentity();
    switch(key) {
    case 's':
    case 'S':
        location *= 0.9;
    	gluLookAt(0.0, 0.0, location + 1.0,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 1.0);
        break;
    case 'f':
    case 'F':
        location *= 1.1;
    	gluLookAt(0.0, 0.0, location + 1.0,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 1.0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
