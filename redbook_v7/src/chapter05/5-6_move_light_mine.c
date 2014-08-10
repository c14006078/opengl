#include <GL/glut.h>

static int spin = 0;
static int window_width = 0, window_height = 0;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

// here is where the light position is reset after the modeling transformation (glRotated) is called.
// This places the light at a new position in world coordinates. The cube represents the position of
// the light.
void display() {
    GLfloat position[] = {0.0, 0.0, 1.5, 1.0};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        // glTranslatef(0.0, 0.0, -5.0);  // It is not necessary once we move the view point of camera
	    glRotated((GLdouble)-60, 1.0, 1.0, 0.0);

        glPushMatrix();
	        glRotated((GLdouble)spin, 1.0, 0.0, 0.0);
    	    glLightfv(GL_LIGHT0, GL_POSITION, position);

        	glTranslated(0.0, 0.0, 1.5);
	        glDisable(GL_LIGHTING);
    	    glColor3f(0.0, 1.0, 1.0);
        	glutWireCube(0.1);
        	glEnable(GL_LIGHTING);
        glPopMatrix();

        glutSolidTorus(0.275, 0.85, 8, 15);
    glPopMatrix();

    glFlush();
}

void reshape(int w, int h) {
    window_width = w, window_height = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // The default view point is from (0, 0, 0) to (0, 0, -100), and positive y-axis is up direction.
    // We move the view point to (0, 0, 5). So glTranslate on line:26 is not necessary.
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        spin = (spin + 5) % 360;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (button) {
        case GLUT_LEFT_BUTTON:
            gluLookAt(0.0, 0.0, 5.0,
                      0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0);
            break;
        case GLUT_RIGHT_BUTTON:
            gluLookAt(5.0, 0.0, 0.0,
                      0.0, 0.0, 0.0,
                      0.0, 0.0, 1.0);
            break;
        default:
            gluLookAt(0.0, 1.0, 5.0,
                      0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}   
