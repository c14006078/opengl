#include <GL/glut.h>

float location = 4.0;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, location + 1.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 1.0);
    glScalef(1.0, 2.0, 1.0);
    glutWireCube(1.0);
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
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
