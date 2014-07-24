#include <GL/glut.h>
#include <stdio.h>

#define XStart            -0.8
#define XEnd               0.8
#define YStart            -0.8
#define YEnd               0.8

#define NumXPoints         11
#define NumYPoints         11
#define NumPoints          (NumXPoints * NumYPoints)
#define NumPointsPerStrip  (2 * NumXPoints)
#define NumStrips          (NumYPoints - 1)
#define RestartIndex       0xffff

GLfloat *vertices;
GLushort *indices;

void init() {

    // set up vertex data
    // glBufferData(GL_ARRAY_BUFFER, 2 * NumPoints * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    vertices = (GLfloat *)malloc(2 * NumPoints * sizeof(GLfloat));

    if (NULL == vertices) {
        fprintf(stderr, "Failed to allocate memory for vertex\n");
        exit(EXIT_FAILURE);
    } else {
        int i, j;
        GLfloat dx = (XEnd - XStart) / (NumXPoints - 1);
        GLfloat dy = (YEnd - YStart) / (NumYPoints - 1);
        GLfloat *tmp = vertices;

        int n = 0;
        for (j = 0; j < NumYPoints; ++j) {
            GLfloat y = YStart + j * dy;
            for (i = 0; i < NumXPoints; ++i) {
                GLfloat x = XStart + i * dx;
                *tmp++ = x;
                *tmp++ = y;
            }
        }

        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glEnableClientState(GL_VERTEX_ARRAY);
    }

    // set up index data

    // allocate an extra restart index because it simplifies the element-array loop logic
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumStrips * (NumPointsPerStrip + 1) * sizeof(GLushort), NULL, GL_STATIC_DRAW);
    indices = (GLushort *)malloc(NumStrips * (NumPointsPerStrip + 1) * sizeof(GLushort));

    if (NULL == indices) {
        fprintf(stderr, "Failed to allocate memory for index\n");
        exit(EXIT_FAILURE);
    } else {
        int i, j;
        GLushort *index = indices;
        for (j = 0; j < NumStrips; ++j) {
            GLushort bottomRow = j * NumYPoints;
            GLushort topRow = bottomRow + NumYPoints;

            for (i = 0; i < NumXPoints; ++i) {
                *index++ = topRow + i;
                *index++ = bottomRow + i;
            }
            *index++ = RestartIndex;
        }
    }
    glPrimitiveRestartIndex(RestartIndex);
    glEnable(GL_PRIMITIVE_RESTART);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void display() {
    int i, start;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    // glPolygonMode(GL_FRONT, GL_LINE);
    // glDrawElements(GL_TRIANGLE_STRIP, NumStrips * (NumPointsPerStrip + 1), GL_UNSIGNED_SHORT, indices);
    glDrawElements(GL_LINE_STRIP, NumStrips * (NumPointsPerStrip + 1), GL_UNSIGNED_SHORT, indices);
    glutSwapBuffers();
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("opengl sample: rectangle.");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
