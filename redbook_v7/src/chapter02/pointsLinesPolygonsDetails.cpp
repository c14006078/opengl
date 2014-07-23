#include <GL/glut.h>
#include <stdio.h>

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("A sample opengl app.");

	GLfloat aliasedPointSizeRange[2];
	glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, aliasedPointSizeRange);
	printf("aliased point size range: %f, %f\n", aliasedPointSizeRange[0], aliasedPointSizeRange[1]);

	GLfloat smoothPointSizeRange[2];
	glGetFloatv(GL_SMOOTH_POINT_SIZE_RANGE, smoothPointSizeRange);
	printf("smooth point size range: %f, %f\n", smoothPointSizeRange[0], smoothPointSizeRange[1]);

	GLfloat smoothPointSizeGranularity;
	glGetFloatv(GL_SMOOTH_POINT_SIZE_GRANULARITY, &smoothPointSizeGranularity);
	printf("smooth point granularity: %f\n", smoothPointSizeGranularity);

	GLfloat aliasedLineWidthRange[2];
	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, aliasedLineWidthRange);
	printf("aliased line width range: %f, %f\n", aliasedLineWidthRange[0], aliasedLineWidthRange[1]);

	GLfloat smoothLineWidthRange[2];
	glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, smoothLineWidthRange);
	printf("smooth line width range: %f, %f\n", smoothLineWidthRange[0], smoothLineWidthRange[1]);

	GLfloat smoothLineWidthGranularity;
	glGetFloatv(GL_SMOOTH_LINE_WIDTH_GRANULARITY, &smoothLineWidthGranularity);
	printf("smooth line width granularity: %f\n", smoothLineWidthGranularity);

	return 0;
}
