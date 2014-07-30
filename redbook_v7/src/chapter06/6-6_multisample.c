#include <GL/glut.h>
#include <stdio.h>

static int bgtoggle = 1;

// Print out state values related to multisampling. Create display list with
// "pinwheel" of lines and triangles.
static init() {
    GLint buffers, samples;
    int i, j;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glGetIntegerv(GL_SAMPLE_BUFFERS, &buffers);
    printf("number of sample buffers is %d\n", buffers);

    glGetIntegerv(GL_SAMPLES, &samples);
    printf("number of samples is %d\n", samples);

    glNewList(1, GL_COMPILE);
    for (i = 0; i < 19; i++) {
        glPushMatrix();

        glRotatef(360.0 * (float)i / 19.0, 0.0, 0.0, 1.0);
        glColor3f(1.0, 1.0, 1.0);
        glLineWidth((i % 3) + 1.0);

        glBegin(GL_LINES);
            glVertex2f(0.25, 0.05);
            glVertex2f(0.9, 0.2);
        glEnd();

        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES);
            glVertex2f(0.25, 0.0);
            glVertex2f(0.9, 0.0);
            glVertex2f(0.875, 0.10);
        glEnd();

        glPopMatrix();
    }
    glEndList();

    glNewList(2, GL_COMPILE);
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (((i + j) % 2) == 0) {
                glVertex2f(-1.0 + i * 0.25, -1.0 + j * 0.25);
                glVertex2f(-1.0 + i * 0.25, -0.75 + j * 0.25);
                glVertex2f(-0.75 + i * 0.25, -0.75 + j * 0.25);
                glVertex2f(-0.75 + i * 0.25, -1.0 + j * 0.25);
            }
        }
    }
    glEnd();
    glEndList();
}

// Draw two sets of primitives so that you can compare the user of multisampling against its absense.
// This code enables AA and draws one display list, and then it disable and draws the other display list.
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (bgtoggle) {
        glCallList(2);
    }

    glEnable(GL_MULTISAMPLE);
    glPushMatrix();
    glTranslatef(-1.0, 0.0, 0.0);
    glCallList(1);
    glPopMatrix();

    glDisable(GL_MULTISAMPLE);
    glPushMatrix();
    glTranslatef(1.0, 0.0, 0.0);
    glCallList(1);
    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
    case 'b':
    case 'B':
        bgtoggle = !bgtoggle;
        glutPostRedisplay();
        break;
    case 27:   // Escape key
        exit(0);
    default:
        break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
