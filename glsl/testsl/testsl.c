#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
//#include <io.h>
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
 
//窗口句柄
static GLint window;
 
GLuint ProgramObject = 0;                            //程序对象
GLuint VertexShaderObject = 0;                   //顶点着色器对象
GLuint FragmentShaderObject = 0;    //片段着色器对象
 
//Shader类型
typedef enum {
    EVertexShader,
         EFragmentShader,
} EShaderType;
 
//用来检查OpenGL版本，需要GLSL 2.0支持
void getGlVersion( int *major, int *minor )
{
    const char* verstr = (const char*)glGetString( GL_VERSION );
    if( (verstr == NULL) || (sscanf( verstr, "%d.%d", major, minor ) != 2) )
    {
        *major = *minor = 0;
        fprintf( stderr, "Invalid GL_VERSION format!!!\n" );
    }
}
 
static void display(void)
{
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
         //查询vertex shader属性变量VertexTemp，并对它进行设置，每个vertex需要指定一个属性
         GLint tempLoc = glGetAttribLocationARB(ProgramObject, "VertexTemp");
         glBegin(GL_TRIANGLES);
                   glVertexAttrib1f(tempLoc, 0.0f);        
                   glVertex3f(1.0f,0.0f,0.0f);
                   glVertexAttrib1f(tempLoc, 0.5f);
                   glVertex3f(-1.0f,0.0f,0.0f);
                   glVertexAttrib1f(tempLoc, 1.0f);
                   glVertex3f(0.0f,1.0f,0.0f);
         glEnd();
    glFlush();
    glutSwapBuffers();
}
 
static void reshape(int w, int h)
{
    float vp = 0.8f;
    float aspect = (float) w / (float) h;
        
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
    glFrustum(-vp, vp, -vp / aspect, vp / aspect, 3, 10.0);
         glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
 
//Shader related functions
static int shaderSize(char *fileName, EShaderType shaderType)
{
         //返回顶点着色器或者片段着色器的大小
    char name[100];
    strcpy(name, fileName);
 
    switch (shaderType)
    {
        case EVertexShader:
            strcat(name, ".vert");
            break;
        case EFragmentShader:
            strcat(name, ".frag");
            break;
        default:
            printf("ERROR: unknown shader file type\n");
            exit(1);
            break;
    }
 
    int count = -1;
    // Open the file, seek to the end to find its length
    int fd = open(name, O_RDONLY);
    if (fd != -1)
    {
        count = lseek(fd, 0, SEEK_END) + 1;
        close(fd);
    }
    return count;
}
 
 
static int readShader(char *fileName, EShaderType shaderType, char *shaderText, int size)
{
    //
    // Reads a shader from the supplied file and returns the shader in the
    // arrays passed in. Returns 1 if successful, 0 if an error occurred.
    // The parameter size is an upper limit of the amount of bytes to read.
    // It is ok for it to be too big.
    //
    FILE *fh;
    char name[100];
    int count;
 
    strcpy(name, fileName);
 
    switch (shaderType)
    {
        case EVertexShader:
            strcat(name, ".vert");
            break;
        case EFragmentShader:
            strcat(name, ".frag");
            break;
        default:
            printf("ERROR: unknown shader file type\n");
            exit(1);
            break;
    }
 
    // Open the file
    fh = fopen(name, "r");
    if (!fh)
        return -1;
 
    // Get the shader from a file.
    fseek(fh, 0, SEEK_SET);
    count = (int) fread(shaderText, 1, size, fh);
    shaderText[count] = '\0';
 
    if (ferror(fh))
        count = 0;
 
    fclose(fh);
    return count;
}
 
 
/*public*/
int readShaderSource(char *fileName, GLchar **vertexShader, GLchar **fragmentShader)
{
    int vSize, fSize;
 
    //
    // Allocate memory to hold the source of our shaders.
    //
    vSize = shaderSize(fileName, EVertexShader);
    fSize = shaderSize(fileName, EFragmentShader);
 
    if ((vSize == -1) || (fSize == -1))
    {
        printf("Cannot determine size of the shader %s\n", fileName);
        return 0;
    }
 
    *vertexShader = (GLchar *) malloc(vSize);
    *fragmentShader = (GLchar *) malloc(fSize);
 
    //
    // Read the source code
    //
    if (!readShader(fileName, EVertexShader, *vertexShader, vSize))
    {
        printf("Cannot read the file %s.vert\n", fileName);
        return 0;
    }
 
    if (!readShader(fileName, EFragmentShader, *fragmentShader, fSize))
    {
        printf("Cannot read the file %s.frag\n", fileName);
        return 0;
    }
 
    return 1;
}
 
 
/*public*/
int installShaders(const GLchar *Vertex,
                        const GLchar *Fragment)
{
    GLint vertCompiled, fragCompiled;    // status values
    GLint linked;
 
    // Create a vertex shader object and a fragment shader object
 
    VertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    FragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
 
    // Load source code strings into shaders
 
    glShaderSource(VertexShaderObject, 1, &Vertex, NULL);
    glShaderSource(FragmentShaderObject, 1, &Fragment, NULL);
 
    // Compile the brick vertex shader, and print out
    // the compiler log file.
 
    glCompileShader(VertexShaderObject);
    glGetShaderiv(VertexShaderObject, GL_COMPILE_STATUS, &vertCompiled);
 
    // Compile the brick vertex shader, and print out
    // the compiler log file.
 
    glCompileShader(FragmentShaderObject);
    glGetShaderiv(FragmentShaderObject, GL_COMPILE_STATUS, &fragCompiled);
 
    if (!vertCompiled || !fragCompiled)
        return 0;
 
    // Create a program object and attach the two compiled shaders
 
    ProgramObject = glCreateProgram();
    glAttachShader(ProgramObject, VertexShaderObject);
    glAttachShader(ProgramObject, FragmentShaderObject);
 
    // Link the program object and print out the info log
 
    glLinkProgram(ProgramObject);
    glGetProgramiv(ProgramObject, GL_LINK_STATUS, &linked);
 
    if (!linked)
        return 0;
 
    // Install program object as part of current state
 
    glUseProgram(ProgramObject);
 
    // Set up initial uniform values
    glUniform1f(glGetUniformLocation(ProgramObject, "CoolestTemp"), 0.0f);
    glUniform1f(glGetUniformLocation(ProgramObject, "TempRange"), 1.0f);
    glUniform3f(glGetUniformLocation(ProgramObject, "CoolestColor"), 0.0, 0.0, 1.0);
    glUniform3f(glGetUniformLocation(ProgramObject, "HottestColor"), 1.0, 0.0, 0.0);
 
    return 1;
}
 
/******************************************************************************/
/*
 * Main
 *
 ******************************************************************************/
int main( int argc, char **argv )
{
    int success = 0;
    int gl_major, gl_minor;
    GLchar *VertexShaderSource, *FragmentShaderSource;
        
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    window = glutCreateWindow( "Temperature Shader");
        
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
        
    // Initialize the "OpenGL Extension Wrangler" library
    glewInit();
        
    // Make sure that OpenGL 2.0 is supported by the driver
    getGlVersion(&gl_major, &gl_minor);
    printf("GL_VERSION major=%d minor=%d\n", gl_major, gl_minor);
        
    if (gl_major < 2)
    {
        printf("GL_VERSION major=%d minor=%d\n", gl_major, gl_minor);
        printf("Support for OpenGL 2.0 is required for this demo...exiting\n");
        exit(1);
    }
        
    readShaderSource("temp", &VertexShaderSource, &FragmentShaderSource);
    success = installShaders(VertexShaderSource, FragmentShaderSource);
        
    if (success)
        glutMainLoop();
   
    return 0;

}
