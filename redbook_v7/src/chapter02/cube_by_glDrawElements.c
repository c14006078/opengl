#include<GL/glut.h>
    GLfloat rCube = 0.0;

    /*static GLint vertices[] = {
                100, 200, 100,
				200, 200, 100,		//index: 1
                200, 200, 300,
				100, 200, 300,
				100, 100, 100,		//index: 4
				200, 100, 100,		//index: 5
				200, 100, 300,
				100, 100, 300		//index: 7
				};
    */
    static GLfloat vertices[] = {
                1.0, 2.0, 1.0,		//index: 0
				2.0, 2.0, 1.0,
                2.0, 2.0, 3.0,		//index: 2
				1.0, 2.0, 3.0,
				1.0, 1.0, 1.0,		//index: 4
				2.0, 1.0, 1.0,		//index: 5
				2.0, 1.0, 3.0,
				1.0, 1.0, 3.0		//index: 7
				};


    static GLfloat colors[] = {
                0.8, 0.0, 0.0,		// index: 0
				0.6, 0.0, 0.0,
				0.0, 0.4, 0.0,		// index: 2
				0.0, 0.2, 0.0,
				0.2, 0.0, 0.0,		// index: 4
				0.4, 0.0, 0.0,
				0.0, 0.6, 0.0,	// index: 6
				0.0, 0.8, 0.0
				};

    static GLubyte front[] = {4, 5, 6, 7};
    static GLubyte right[] = {5, 1, 2, 6};
    static GLubyte back[] = {1, 0, 3, 2};
    static GLubyte left[] = {0, 4, 7, 3};
    static GLubyte bottom[] = {4, 0, 1, 5};
    static GLubyte top[] = {7, 6, 2, 3};

    static GLubyte allIndices[] = {4, 5, 6, 7,
                                   5, 1, 2, 6,
                                   1, 0, 3, 2,
                                   0, 4, 7, 3,
                                   4, 0, 1, 5,
                                   7, 6, 2, 3};

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0.0, 800.0, 0.0, 600.0, 0.0, 1000.0);
     gluPerspective ( 90, ( float ) 1.0, 1.0, 5000.0 );
    //gluPerspective(90.0, 800.0/600.0, 100.0, 5000.0);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
}

void drawCube(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0f);
    glRotatef(rCube, 0.0f, 1.0f, 0.0f); 

#if 0
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, front); 
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, right);   
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, back);   
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, left);   
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottom);   
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, top);  
#endif

    glDrawElements(GL_QUADS, sizeof(allIndices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, allIndices); 
    glPopMatrix();

    rCube += 0.1;

    glFlush();  // The animation will behave abnormally if glFlush() is not called.
}

void reshape(int w, int h)   // Create The Reshape Function (the viewport)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);  // Select The Projection Matrix
    glLoadIdentity();                // Reset The Projection Matrix
    if (h == 0) {  // Calculate The Aspect Ratio Of The Window
        gluPerspective ( 90, ( float ) w, 1.0, 5000.0 );
    } else {
        gluPerspective ( 90, ( float ) w / ( float ) h, 1.0, 5000.0 );
    }
    glMatrixMode(GL_MODELVIEW);  // Select The Model View Matrix
    glLoadIdentity();    // Reset The Model View Matrix
}

void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("A sample opengl app.");

    init();
    glutDisplayFunc(drawCube);
    glutIdleFunc(drawCube);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
