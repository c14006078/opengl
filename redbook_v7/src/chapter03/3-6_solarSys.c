#include <GL/glut.h>
#include<math.h>
#define PI 3.14159265

static float earthYear = 0, earthDay = 0;
static float moonYear = 0, moonDay = 0;
static float marYear = 90, marDay =0;
static GLfloat distance = 5.0;
int fromTop = 0;

static void draw_orbit(int edge_num, float radius) {
    glBegin(GL_LINE_LOOP);
	int i;
	for (i = 0; i < edge_num; i++) {
	    GLfloat angle = 2 * PI * i / edge_num;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
	}
    glEnd();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the star. For example, the sun.
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(0.3, 20, 16);

    // Draw the orbits for planets. They are 2 circles in fact.
    // Need to revolve round (rotate on) the x axis before draw orbits, making it rendered on the xz-plane.
    // Otherwise, it will be on the xy-plane and get the wrong result.
    glPushMatrix();
        glRotatef((GLfloat)90, 1.0, 0.0, 0.0);
        draw_orbit(100, 1.5);
        draw_orbit(100, 2.0);
    glPopMatrix();

    // Draw the planet. For example, the earth.
    glPushMatrix();
        glRotatef((GLfloat)earthYear, 0.0, 1.0, 0.0);  // planet revolves round the star, this affect its satellites.
        glTranslatef(1.5, 0.0, 0.0);
       
        // Planet rotates on its axis. This behavior should not affect its satellites. We should push and pop matrix.
        // However, planet also revolves round the star, this actually affects its satellites. Don't push and pop this transformation.
        glPushMatrix();
            glRotatef((GLfloat)earthDay, 0.0, 1.0, 0.0); // planet rotates on its own axis, this should not affect its satellites.
            glColor3f(0.0, 0.0, 1.0);
            glutSolidSphere(0.06, 10, 8);
        glPopMatrix();

        // Draw the satellite. For example, the moon.
        glPushMatrix();
            glRotatef((GLfloat)moonYear, 0.0, 1.0, 0.0);          // 月亮的公转取决于地球的自转参数，not moonYear, why? 
            glTranslatef(0.3, 0.0, 0.0);
            glRotatef((GLfloat)moonDay, 0.0, 1.0, 0.0);
            glColor3f(1.0, 1.0, 1.0);
            glutSolidSphere(0.02, 10, 8);
        glPopMatrix();
    glPopMatrix();

    // Draw another planet. For example, the mars.
    glPushMatrix();
        glRotatef((GLfloat)marYear, 0.0, 1.0, 0.0);
        glTranslatef(2.0, 0.0, 0.0);
        glRotatef((GLfloat)marDay, 0.0, 1.0, 0.0);
        glColor3f(1.0, 1.0, 0.0);
        glutSolidSphere(0.04, 10, 8);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, distance, 0.0,
              0.0, 0.0, 0.0,
              0.0, 0.0, 1.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 't':
        case 'T':
            fromTop = 1;
            break;
        case 'r':
        case 'R':
            fromTop = 0;
            break;
        case 's':
        case 'S':
            distance *= 1.2;
            break;
        case 'f':
        case 'F':
            distance /= 1.2;
            break;
        default:
            break;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (fromTop == 1) {
        gluLookAt(0.0, distance, 0.0,
                  0.0, 0.0, 0.0,
                  0.0, 0.0, 1.0);
    } else {
        gluLookAt(0.0, 3.0, distance,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);
    }
    glutPostRedisplay();
}

void rotate() {
    earthDay += 3;
    if (earthDay >= 360)
        earthDay -= 360;

    earthYear += 0.05;
    if (earthYear >= 360)
        earthYear -= 360;

    moonDay += 10;
    if (earthDay >= 360)
        earthDay -= 360;

    moonYear += 0.6;
    if (earthYear >= 360)
        earthYear -= 360;

    marDay += 5;
    if (marDay >= 360)
        marDay -= 360;

    marYear += 0.2;
    if (marYear >= 360)
        marYear -= 360;
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1200);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(rotate);
    glutMainLoop();
    return 0;
}
