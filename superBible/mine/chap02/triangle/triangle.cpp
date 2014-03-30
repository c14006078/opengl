/***********************************************************
 * Simple Demo for GLSL 2.0
 *
 * www.lighthouse3d.com
 **********************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glut.h>
#include "textfile.h"

GLuint v, f, p;
// float lpos[4] = {1,0.5,1,0};

void changeSize(int w, int h) {
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
}


void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glLoadIdentity();
    /* gluLookAt(0.0, 0.0, 5.0, 
              0.0, 0.0, -1.0,
              0.0f, 1.0f, 0.0f);

    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glutSolidTeapot(1);
*/
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
}

void setShaders() {
    char *vs = NULL, *fs = NULL;

    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);

    vs = textFileRead("tri.vert");
    fs = textFileRead("tri.frag");

    const char * ff = fs;
    const char * vv = vs;

    glShaderSource(v, 1, &vv, NULL);
    glShaderSource(f, 1, &ff, NULL);

    free(vs);
    free(fs);

    glCompileShader(v);
    glCompileShader(f);

    p = glCreateProgram();
    glAttachShader(p, f);
    glAttachShader(p, v);

    glLinkProgram(p);
    glUseProgram(p);
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Teapot -- MM 2004-05");

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(processNormalKeys);

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0,1.0);
    // glEnable(GL_CULL_FACE);

    glewInit();
    if (glewIsSupported("GL_VERSION_2_0")) {
        printf("Ready for OpenGL 2.0\n");
    } else {
        printf("OpenGL 2.0 not supported\n");
        exit(1);
    }

    setShaders();

    glutMainLoop();

    // just for compatibiliy purposes
    return 0;
}
