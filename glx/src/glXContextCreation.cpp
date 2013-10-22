#include <GL/glx.h>
#include <X11/Xlib.h>
#include <GL/glu.h>
#include <stdio.h>
#include <iostream>
#include <vector>

//using namespace std;

#define GL_X_1_3 1

static bool ctxErrorOccurred = false;
Pixmap fPixmap;
GLXPixmap fGlxPixmap;
GLXContext fContext;

static int ctxErrorHandler(Display *dpy, XErrorEvent *ev) {
    ctxErrorOccurred = true;
    return 0;
}

int main(int argc, char** argv) {
    Display *fDisplay = XOpenDisplay(0);

    static int visual_attribs[] = {
        GLX_X_RENDERABLE    , True,
        GLX_DRAWABLE_TYPE   , GLX_PIXMAP_BIT,
        None
    };

    int fbcount;
    GLXFBConfig *fbc = glXChooseFBConfig(fDisplay, DefaultScreen(fDisplay),
                                          visual_attribs, &fbcount);
    int best_fbc = -1, best_num_samp = -1;
    int i;
    for (i = 0; i < fbcount; ++i) {
        XVisualInfo *vi = glXGetVisualFromFBConfig(fDisplay, fbc[i]);
        if (vi) {
            int samp_buf, samples;
            glXGetFBConfigAttrib(fDisplay, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
            glXGetFBConfigAttrib(fDisplay, fbc[i], GLX_SAMPLES, &samples);

            //SkDebugf("  Matching fbconfig %d, visual ID 0x%2x: SAMPLE_BUFFERS = %d,"
            //       " SAMPLES = %d\n",
            //        i, (unsigned int)vi->visualid, samp_buf, samples);

            if (best_fbc < 0 || (samp_buf && samples > best_num_samp))
                best_fbc = i, best_num_samp = samples;
        }
        XFree(vi);
    }

    GLXFBConfig bestFbc = fbc[best_fbc];

    // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
    XFree(fbc);

// Get a visual
    XVisualInfo *vi = glXGetVisualFromFBConfig(fDisplay, bestFbc);
    //SkDebugf("Chosen visual ID = 0x%x\n", (unsigned int)vi->visualid);

    fPixmap = XCreatePixmap(fDisplay, RootWindow(fDisplay, vi->screen), 10, 10, vi->depth);

    if (!fPixmap) {
    //    SkDebugf("Failed to create pixmap.\n");
    //    this->destroyGLContext();
    //    return NULL;
        printf("create pixmap failed.\n");
        return NULL;
        //exit(0);
    }

    fGlxPixmap = glXCreateGLXPixmap(fDisplay, vi, fPixmap);

    XFree(vi);

    ctxErrorOccurred = false;
    int (*oldHandler)(Display*, XErrorEvent*) =
        XSetErrorHandler(&ctxErrorHandler);

    // Get the default screen's GLX extension list
    const char *glxExts = glXQueryExtensionsString(
        fDisplay, DefaultScreen(fDisplay)
    );
    // Check for the GLX_ARB_create_context extension string and the function.
    // If either is not present, use GLX 1.3 context creation method.
    /*if ( 0 ) //!gluCheckExtension(
          //reinterpret_cast<const GLubyte*>("GLX_ARB_create_context")
          //"GLX_ARB_create_context"
          //, reinterpret_cast<const GLubyte*>(glxExts)))
          //, glxExts))
    {
#ifdef GLX_1_3
        fContext = glXCreateNewContext(fDisplay, bestFbc, GLX_RGBA_TYPE, 0, True);
#else
        fContext = glXCreateContext(fDisplay, vi, 0, True);
#endif

    }
#ifdef GLX_1_3
    else*/ {
        //SkDebugf("Creating context.\n");

        PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB =
            (PFNGLXCREATECONTEXTATTRIBSARBPROC) glXGetProcAddressARB((GLubyte*)"glXCreateContextAttribsARB");
        int context_attribs[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
            GLX_CONTEXT_MINOR_VERSION_ARB, 0,
            //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            None
        };
        fContext = glXCreateContextAttribsARB(
            fDisplay, bestFbc, 0, True, context_attribs
        );

        // Sync to ensure any errors generated are processed.
        XSync(fDisplay, False);
        if (!ctxErrorOccurred && fContext) {
           //SkDebugf( "Created GL 3.0 context.\n" );
           printf("create GL 3.0 context.\n");
        } else {
            // Couldn't create GL 3.0 context.
            // Fall back to old-style 2.x context.
            // When a context version below 3.0 is requested,
            // implementations will return the newest context version compatible
            // with OpenGL versions less than version 3.0.

            // GLX_CONTEXT_MAJOR_VERSION_ARB = 1
            context_attribs[1] = 1;
            // GLX_CONTEXT_MINOR_VERSION_ARB = 0
            context_attribs[3] = 0;

            ctxErrorOccurred = false;

            std::vector<int> attribs;
            attribs.push_back(0);

            //SkDebugf("Failed to create GL 3.0 context."
            //       " Using old-style GLX context.\n");
            fContext = glXCreateContextAttribsARB(
                //fDisplay, bestFbc, 0, True, context_attribs
                fDisplay, bestFbc, 0, True, &attribs.front()
            );
        }
    }
//#endif
    // Sync to ensure any errors generated are processed.
    XSync(fDisplay, False);

    // Restore the original error handler
    XSetErrorHandler(oldHandler);

    if (ctxErrorOccurred || !fContext) {
        //SkDebugf("Failed to create an OpenGL context.\n");
        //this->destroyGLContext();
        //return NULL;
        printf("ctxErrorOccurred.\n");
        return NULL;
        //exit(0);
    }

    // Verify that context is a direct context
    if (!glXIsDirect(fDisplay, fContext)) {
        //SkDebugf("Indirect GLX rendering context obtained.\n");
    } else {
        //SkDebugf("Direct GLX rendering context obtained.\n");
    }

    //SkDebugf("Making context current.\n");
    if (!glXMakeCurrent(fDisplay, fGlxPixmap, fContext)) {
      //SkDebugf("Could not set the context.\n");
      //  this->destroyGLContext();
      //  return NULL;
        printf("glXMakeCurrent failed.\n");
        return NULL;
        //exit(0);
    }



    printf("glx extensions: %s \n", glXQueryExtensionsString(fDisplay, 0));
}
