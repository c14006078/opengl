#include <GL/glx.h>
#include <GL/gl.h>
#include <X11/Xlib.h>
#include <stdio.h>

void main() {
    Display *display = XOpenDisplay(0);
    printf("glx extensions: %s \n", glXQueryExtensionsString(display, 0));
}
