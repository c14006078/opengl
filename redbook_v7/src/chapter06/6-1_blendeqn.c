#include <GL/glut.h>

/* the following keys change the selected blend equation mode
 * 
 * 'a' --> GL_FUNC_ADD
 * 's' --> GL_FUNC_SUBTRACT
 * 'r' --> GL_FUNC_REVERSE_SUBTRACT
 * 'm' --> GL_MIN
 * 'x' --> GL_MAX
 */

void init() {
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glBlendFunc(GL_ONE, GL_ONE);
    glEnable(GL_BLEND);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glRectf(-0.5, -0.5, 0.5, 0.5);
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
    case 'a': case 'A':
        glBlendEquation(GL_FUNC_ADD);
        break;
    case 's': case 'S':
        glBlendEquation(GL_FUNC_SUBTRACT);
        break;
    case 'r': case 'R':
        glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
        break;
    case 'm': case 'M':
        glBlendEquation(GL_MIN);
        break;
    case 'x': case 'X':
        glBlendEquation(GL_MAX);
        break;
    case 27:
        exit(0);
    default:
        break;
    }
    glutPostRedisplay();
}
        

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("opengl sample: blend");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
