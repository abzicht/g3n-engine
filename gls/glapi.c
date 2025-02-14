
// This file was generated automatically by "glapi2go" and contains functions to
// open the platform's OpenGL dll/shared library and to load all OpenGL function
// pointers for an specified OpenGL version described by the header file "glcorearb.h",
// from "https://www.khronos.org/registry/OpenGL/api/GL/glcorearb.h".
//
// As Go cgo cannot call directly to C pointers it also creates C function wrappers
// for all loaded OpenGL pointers.
// The code was heavily based on "https://github.com/skaslev/gl3w"

#include <stdlib.h>
#include <stdio.h>
#include "glapi.h"

//
// OpenGL function loader for Windows
//
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#undef near
#undef far

static HMODULE libgl;

// open_libgl opens the OpenGL dll for Windows
static int open_libgl(void) {

	libgl = LoadLibraryA("opengl32.dll");
	if (libgl == NULL) {
		return -1;
	}
	return 0;
}

// close_libgl closes the OpenGL dll object for Windows
static void close_libgl(void) {

	FreeLibrary(libgl);
}

// get_proc gets the pointer for an OpenGL function for Windows
static void* get_proc(const char *proc) {

	void* res;
	res = (void*)wglGetProcAddress(proc);
	if (!res) {
		res = (void*)GetProcAddress(libgl, proc);
	}
	return res;
}

//
// OpenGL function loader for Mac OS
//
#elif defined(__APPLE__)
#include <dlfcn.h>

static void *libgl;

static int open_libgl(void) {

	libgl = dlopen("/System/Library/Frameworks/OpenGL.framework/OpenGL", RTLD_LAZY | RTLD_GLOBAL);
	if (!libgl) {
		return -1;
	}
	return 0;
}

static void close_libgl(void) {

	dlclose(libgl);
}

static void* get_proc(const char *proc) {

	void* res;
	*(void **)(&res) = dlsym(libgl, proc);
	return res;
}

//
// OpenGL function loader for Linux, Unix*
//
#else
#include <dlfcn.h>
#include <GL/glx.h>

static void *libgl;
static PFNGLXGETPROCADDRESSPROC glx_get_proc_address;

// open_libgl opens the OpenGL shared object for Linux/Freebsd
static int open_libgl(void) {

	libgl = dlopen("libGL.so.1", RTLD_LAZY | RTLD_GLOBAL);
	if (libgl == NULL) {
		return -1;
	}
	*(void **)(&glx_get_proc_address) = dlsym(libgl, "glXGetProcAddressARB");
	if (glx_get_proc_address == NULL) {
		return -1;
	}
	return 0;
}

// close_libgl closes the OpenGL shared object for Linux/Freebsd
static void close_libgl(void) {

	dlclose(libgl);
}

// get_proc gets the pointer for an OpenGL function for Linux/Freebsd
static void* get_proc(const char *proc) {

	void* res;
	res = glx_get_proc_address((const GLubyte *)proc);
	if (!res) {
		*(void **)(&res) = dlsym(libgl, proc);
	}
	return res;
}
#endif

// Internal global flag to check error from OpenGL functions
static int checkError = 1;

// Declaration of internal function for loading OpenGL function pointers
static void load_procs();

//
// glapiLoad() tries to load functions addresses from the OpenGL library
//
int glapiLoad(void) {

	int res = open_libgl();
	if (res != 0) {
		return res;
	}
	load_procs();
	close_libgl();
	return 0;
}

//
// glapiCheckError sets the state of the internal flag which determines
// if error checking must be done for OpenGL calls
//
void glapiCheckError(int check) {

	checkError = check;
}

// Internal function to abort process when error
static void panic(GLenum err, const char* fname) {

		const char *msg;
		switch(err) {
    	case GL_NO_ERROR:
    		msg = "No error";
    		break;
    	case GL_INVALID_ENUM:
    		msg = "An unacceptable value is specified for an enumerated argument";
    		break;
    	case GL_INVALID_VALUE:
    		msg = "A numeric argument is out of range";
    		break;
    	case GL_INVALID_OPERATION:
    		msg = "The specified operation is not allowed in the current state";
    		break;
    	case GL_INVALID_FRAMEBUFFER_OPERATION:
    		msg = "The framebuffer object is not complete";
    		break;
    	case GL_OUT_OF_MEMORY:
    		msg = "There is not enough memory left to execute the command";
    		break;
    	case GL_STACK_UNDERFLOW:
    		msg = "An attempt has been made to perform an operation that would cause an internal stack to underflow";
    		break;
    	case GL_STACK_OVERFLOW:
    		msg = "An attempt has been made to perform an operation that would cause an internal stack to overflow";
    		break;
    	default:
    		msg = "Unexpected error";
    		break;
    }
    printf("\nGLAPI Error: %s (%d) calling: %s\n", msg, err, fname);
    exit(1);
}


//
// Definitions of function pointers variables
//
static PFNGLCULLFACEPROC                                      pglCullFace;
static PFNGLFRONTFACEPROC                                     pglFrontFace;
static PFNGLHINTPROC                                          pglHint;
static PFNGLLINEWIDTHPROC                                     pglLineWidth;
static PFNGLPOINTSIZEPROC                                     pglPointSize;
static PFNGLPOLYGONMODEPROC                                   pglPolygonMode;
static PFNGLSCISSORPROC                                       pglScissor;
static PFNGLTEXPARAMETERFPROC                                 pglTexParameterf;
static PFNGLTEXPARAMETERFVPROC                                pglTexParameterfv;
static PFNGLTEXPARAMETERIPROC                                 pglTexParameteri;
static PFNGLTEXPARAMETERIVPROC                                pglTexParameteriv;
static PFNGLTEXIMAGE1DPROC                                    pglTexImage1D;
static PFNGLTEXIMAGE2DPROC                                    pglTexImage2D;
static PFNGLDRAWBUFFERPROC                                    pglDrawBuffer;
static PFNGLCLEARPROC                                         pglClear;
static PFNGLCLEARCOLORPROC                                    pglClearColor;
static PFNGLCLEARSTENCILPROC                                  pglClearStencil;
static PFNGLCLEARDEPTHPROC                                    pglClearDepth;
static PFNGLSTENCILMASKPROC                                   pglStencilMask;
static PFNGLCOLORMASKPROC                                     pglColorMask;
static PFNGLDEPTHMASKPROC                                     pglDepthMask;
static PFNGLDISABLEPROC                                       pglDisable;
static PFNGLENABLEPROC                                        pglEnable;
static PFNGLFINISHPROC                                        pglFinish;
static PFNGLFLUSHPROC                                         pglFlush;
static PFNGLBLENDFUNCPROC                                     pglBlendFunc;
static PFNGLLOGICOPPROC                                       pglLogicOp;
static PFNGLSTENCILFUNCPROC                                   pglStencilFunc;
static PFNGLSTENCILOPPROC                                     pglStencilOp;
static PFNGLDEPTHFUNCPROC                                     pglDepthFunc;
static PFNGLPIXELSTOREFPROC                                   pglPixelStoref;
static PFNGLPIXELSTOREIPROC                                   pglPixelStorei;
static PFNGLREADBUFFERPROC                                    pglReadBuffer;
static PFNGLREADPIXELSPROC                                    pglReadPixels;
static PFNGLGETBOOLEANVPROC                                   pglGetBooleanv;
static PFNGLGETDOUBLEVPROC                                    pglGetDoublev;
static PFNGLGETERRORPROC                                      pglGetError;
static PFNGLGETFLOATVPROC                                     pglGetFloatv;
static PFNGLGETINTEGERVPROC                                   pglGetIntegerv;
static PFNGLGETSTRINGPROC                                     pglGetString;
static PFNGLGETTEXIMAGEPROC                                   pglGetTexImage;
static PFNGLGETTEXPARAMETERFVPROC                             pglGetTexParameterfv;
static PFNGLGETTEXPARAMETERIVPROC                             pglGetTexParameteriv;
static PFNGLGETTEXLEVELPARAMETERFVPROC                        pglGetTexLevelParameterfv;
static PFNGLGETTEXLEVELPARAMETERIVPROC                        pglGetTexLevelParameteriv;
static PFNGLISENABLEDPROC                                     pglIsEnabled;
static PFNGLDEPTHRANGEPROC                                    pglDepthRange;
static PFNGLVIEWPORTPROC                                      pglViewport;
static PFNGLDRAWARRAYSPROC                                    pglDrawArrays;
static PFNGLDRAWELEMENTSPROC                                  pglDrawElements;
static PFNGLGETPOINTERVPROC                                   pglGetPointerv;
static PFNGLPOLYGONOFFSETPROC                                 pglPolygonOffset;
static PFNGLCOPYTEXIMAGE1DPROC                                pglCopyTexImage1D;
static PFNGLCOPYTEXIMAGE2DPROC                                pglCopyTexImage2D;
static PFNGLCOPYTEXSUBIMAGE1DPROC                             pglCopyTexSubImage1D;
static PFNGLCOPYTEXSUBIMAGE2DPROC                             pglCopyTexSubImage2D;
static PFNGLTEXSUBIMAGE1DPROC                                 pglTexSubImage1D;
static PFNGLTEXSUBIMAGE2DPROC                                 pglTexSubImage2D;
static PFNGLBINDTEXTUREPROC                                   pglBindTexture;
static PFNGLDELETETEXTURESPROC                                pglDeleteTextures;
static PFNGLGENTEXTURESPROC                                   pglGenTextures;
static PFNGLISTEXTUREPROC                                     pglIsTexture;
static PFNGLDRAWRANGEELEMENTSPROC                             pglDrawRangeElements;
static PFNGLTEXIMAGE3DPROC                                    pglTexImage3D;
static PFNGLTEXSUBIMAGE3DPROC                                 pglTexSubImage3D;
static PFNGLCOPYTEXSUBIMAGE3DPROC                             pglCopyTexSubImage3D;
static PFNGLACTIVETEXTUREPROC                                 pglActiveTexture;
static PFNGLSAMPLECOVERAGEPROC                                pglSampleCoverage;
static PFNGLCOMPRESSEDTEXIMAGE3DPROC                          pglCompressedTexImage3D;
static PFNGLCOMPRESSEDTEXIMAGE2DPROC                          pglCompressedTexImage2D;
static PFNGLCOMPRESSEDTEXIMAGE1DPROC                          pglCompressedTexImage1D;
static PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC                       pglCompressedTexSubImage3D;
static PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC                       pglCompressedTexSubImage2D;
static PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC                       pglCompressedTexSubImage1D;
static PFNGLGETCOMPRESSEDTEXIMAGEPROC                         pglGetCompressedTexImage;
static PFNGLBLENDFUNCSEPARATEPROC                             pglBlendFuncSeparate;
static PFNGLMULTIDRAWARRAYSPROC                               pglMultiDrawArrays;
static PFNGLMULTIDRAWELEMENTSPROC                             pglMultiDrawElements;
static PFNGLPOINTPARAMETERFPROC                               pglPointParameterf;
static PFNGLPOINTPARAMETERFVPROC                              pglPointParameterfv;
static PFNGLPOINTPARAMETERIPROC                               pglPointParameteri;
static PFNGLPOINTPARAMETERIVPROC                              pglPointParameteriv;
static PFNGLBLENDCOLORPROC                                    pglBlendColor;
static PFNGLBLENDEQUATIONPROC                                 pglBlendEquation;
static PFNGLGENQUERIESPROC                                    pglGenQueries;
static PFNGLDELETEQUERIESPROC                                 pglDeleteQueries;
static PFNGLISQUERYPROC                                       pglIsQuery;
static PFNGLBEGINQUERYPROC                                    pglBeginQuery;
static PFNGLENDQUERYPROC                                      pglEndQuery;
static PFNGLGETQUERYIVPROC                                    pglGetQueryiv;
static PFNGLGETQUERYOBJECTIVPROC                              pglGetQueryObjectiv;
static PFNGLGETQUERYOBJECTUIVPROC                             pglGetQueryObjectuiv;
static PFNGLBINDBUFFERPROC                                    pglBindBuffer;
static PFNGLDELETEBUFFERSPROC                                 pglDeleteBuffers;
static PFNGLGENBUFFERSPROC                                    pglGenBuffers;
static PFNGLISBUFFERPROC                                      pglIsBuffer;
static PFNGLBUFFERDATAPROC                                    pglBufferData;
static PFNGLBUFFERSUBDATAPROC                                 pglBufferSubData;
static PFNGLGETBUFFERSUBDATAPROC                              pglGetBufferSubData;
static PFNGLMAPBUFFERPROC                                     pglMapBuffer;
static PFNGLUNMAPBUFFERPROC                                   pglUnmapBuffer;
static PFNGLGETBUFFERPARAMETERIVPROC                          pglGetBufferParameteriv;
static PFNGLGETBUFFERPOINTERVPROC                             pglGetBufferPointerv;
static PFNGLBLENDEQUATIONSEPARATEPROC                         pglBlendEquationSeparate;
static PFNGLDRAWBUFFERSPROC                                   pglDrawBuffers;
static PFNGLSTENCILOPSEPARATEPROC                             pglStencilOpSeparate;
static PFNGLSTENCILFUNCSEPARATEPROC                           pglStencilFuncSeparate;
static PFNGLSTENCILMASKSEPARATEPROC                           pglStencilMaskSeparate;
static PFNGLATTACHSHADERPROC                                  pglAttachShader;
static PFNGLBINDATTRIBLOCATIONPROC                            pglBindAttribLocation;
static PFNGLCOMPILESHADERPROC                                 pglCompileShader;
static PFNGLCREATEPROGRAMPROC                                 pglCreateProgram;
static PFNGLCREATESHADERPROC                                  pglCreateShader;
static PFNGLDELETEPROGRAMPROC                                 pglDeleteProgram;
static PFNGLDELETESHADERPROC                                  pglDeleteShader;
static PFNGLDETACHSHADERPROC                                  pglDetachShader;
static PFNGLDISABLEVERTEXATTRIBARRAYPROC                      pglDisableVertexAttribArray;
static PFNGLENABLEVERTEXATTRIBARRAYPROC                       pglEnableVertexAttribArray;
static PFNGLGETACTIVEATTRIBPROC                               pglGetActiveAttrib;
static PFNGLGETACTIVEUNIFORMPROC                              pglGetActiveUniform;
static PFNGLGETATTACHEDSHADERSPROC                            pglGetAttachedShaders;
static PFNGLGETATTRIBLOCATIONPROC                             pglGetAttribLocation;
static PFNGLGETPROGRAMIVPROC                                  pglGetProgramiv;
static PFNGLGETPROGRAMINFOLOGPROC                             pglGetProgramInfoLog;
static PFNGLGETSHADERIVPROC                                   pglGetShaderiv;
static PFNGLGETSHADERINFOLOGPROC                              pglGetShaderInfoLog;
static PFNGLGETSHADERSOURCEPROC                               pglGetShaderSource;
static PFNGLGETUNIFORMLOCATIONPROC                            pglGetUniformLocation;
static PFNGLGETUNIFORMFVPROC                                  pglGetUniformfv;
static PFNGLGETUNIFORMIVPROC                                  pglGetUniformiv;
static PFNGLGETVERTEXATTRIBDVPROC                             pglGetVertexAttribdv;
static PFNGLGETVERTEXATTRIBFVPROC                             pglGetVertexAttribfv;
static PFNGLGETVERTEXATTRIBIVPROC                             pglGetVertexAttribiv;
static PFNGLGETVERTEXATTRIBPOINTERVPROC                       pglGetVertexAttribPointerv;
static PFNGLISPROGRAMPROC                                     pglIsProgram;
static PFNGLISSHADERPROC                                      pglIsShader;
static PFNGLLINKPROGRAMPROC                                   pglLinkProgram;
static PFNGLSHADERSOURCEPROC                                  pglShaderSource;
static PFNGLUSEPROGRAMPROC                                    pglUseProgram;
static PFNGLUNIFORM1FPROC                                     pglUniform1f;
static PFNGLUNIFORM2FPROC                                     pglUniform2f;
static PFNGLUNIFORM3FPROC                                     pglUniform3f;
static PFNGLUNIFORM4FPROC                                     pglUniform4f;
static PFNGLUNIFORM1IPROC                                     pglUniform1i;
static PFNGLUNIFORM2IPROC                                     pglUniform2i;
static PFNGLUNIFORM3IPROC                                     pglUniform3i;
static PFNGLUNIFORM4IPROC                                     pglUniform4i;
static PFNGLUNIFORM1FVPROC                                    pglUniform1fv;
static PFNGLUNIFORM2FVPROC                                    pglUniform2fv;
static PFNGLUNIFORM3FVPROC                                    pglUniform3fv;
static PFNGLUNIFORM4FVPROC                                    pglUniform4fv;
static PFNGLUNIFORM1IVPROC                                    pglUniform1iv;
static PFNGLUNIFORM2IVPROC                                    pglUniform2iv;
static PFNGLUNIFORM3IVPROC                                    pglUniform3iv;
static PFNGLUNIFORM4IVPROC                                    pglUniform4iv;
static PFNGLUNIFORMMATRIX2FVPROC                              pglUniformMatrix2fv;
static PFNGLUNIFORMMATRIX3FVPROC                              pglUniformMatrix3fv;
static PFNGLUNIFORMMATRIX4FVPROC                              pglUniformMatrix4fv;
static PFNGLVALIDATEPROGRAMPROC                               pglValidateProgram;
static PFNGLVERTEXATTRIB1DPROC                                pglVertexAttrib1d;
static PFNGLVERTEXATTRIB1DVPROC                               pglVertexAttrib1dv;
static PFNGLVERTEXATTRIB1FPROC                                pglVertexAttrib1f;
static PFNGLVERTEXATTRIB1FVPROC                               pglVertexAttrib1fv;
static PFNGLVERTEXATTRIB1SPROC                                pglVertexAttrib1s;
static PFNGLVERTEXATTRIB1SVPROC                               pglVertexAttrib1sv;
static PFNGLVERTEXATTRIB2DPROC                                pglVertexAttrib2d;
static PFNGLVERTEXATTRIB2DVPROC                               pglVertexAttrib2dv;
static PFNGLVERTEXATTRIB2FPROC                                pglVertexAttrib2f;
static PFNGLVERTEXATTRIB2FVPROC                               pglVertexAttrib2fv;
static PFNGLVERTEXATTRIB2SPROC                                pglVertexAttrib2s;
static PFNGLVERTEXATTRIB2SVPROC                               pglVertexAttrib2sv;
static PFNGLVERTEXATTRIB3DPROC                                pglVertexAttrib3d;
static PFNGLVERTEXATTRIB3DVPROC                               pglVertexAttrib3dv;
static PFNGLVERTEXATTRIB3FPROC                                pglVertexAttrib3f;
static PFNGLVERTEXATTRIB3FVPROC                               pglVertexAttrib3fv;
static PFNGLVERTEXATTRIB3SPROC                                pglVertexAttrib3s;
static PFNGLVERTEXATTRIB3SVPROC                               pglVertexAttrib3sv;
static PFNGLVERTEXATTRIB4NBVPROC                              pglVertexAttrib4Nbv;
static PFNGLVERTEXATTRIB4NIVPROC                              pglVertexAttrib4Niv;
static PFNGLVERTEXATTRIB4NSVPROC                              pglVertexAttrib4Nsv;
static PFNGLVERTEXATTRIB4NUBPROC                              pglVertexAttrib4Nub;
static PFNGLVERTEXATTRIB4NUBVPROC                             pglVertexAttrib4Nubv;
static PFNGLVERTEXATTRIB4NUIVPROC                             pglVertexAttrib4Nuiv;
static PFNGLVERTEXATTRIB4NUSVPROC                             pglVertexAttrib4Nusv;
static PFNGLVERTEXATTRIB4BVPROC                               pglVertexAttrib4bv;
static PFNGLVERTEXATTRIB4DPROC                                pglVertexAttrib4d;
static PFNGLVERTEXATTRIB4DVPROC                               pglVertexAttrib4dv;
static PFNGLVERTEXATTRIB4FPROC                                pglVertexAttrib4f;
static PFNGLVERTEXATTRIB4FVPROC                               pglVertexAttrib4fv;
static PFNGLVERTEXATTRIB4IVPROC                               pglVertexAttrib4iv;
static PFNGLVERTEXATTRIB4SPROC                                pglVertexAttrib4s;
static PFNGLVERTEXATTRIB4SVPROC                               pglVertexAttrib4sv;
static PFNGLVERTEXATTRIB4UBVPROC                              pglVertexAttrib4ubv;
static PFNGLVERTEXATTRIB4UIVPROC                              pglVertexAttrib4uiv;
static PFNGLVERTEXATTRIB4USVPROC                              pglVertexAttrib4usv;
static PFNGLVERTEXATTRIBPOINTERPROC                           pglVertexAttribPointer;
static PFNGLUNIFORMMATRIX2X3FVPROC                            pglUniformMatrix2x3fv;
static PFNGLUNIFORMMATRIX3X2FVPROC                            pglUniformMatrix3x2fv;
static PFNGLUNIFORMMATRIX2X4FVPROC                            pglUniformMatrix2x4fv;
static PFNGLUNIFORMMATRIX4X2FVPROC                            pglUniformMatrix4x2fv;
static PFNGLUNIFORMMATRIX3X4FVPROC                            pglUniformMatrix3x4fv;
static PFNGLUNIFORMMATRIX4X3FVPROC                            pglUniformMatrix4x3fv;
static PFNGLCOLORMASKIPROC                                    pglColorMaski;
static PFNGLGETBOOLEANI_VPROC                                 pglGetBooleani_v;
static PFNGLGETINTEGERI_VPROC                                 pglGetIntegeri_v;
static PFNGLENABLEIPROC                                       pglEnablei;
static PFNGLDISABLEIPROC                                      pglDisablei;
static PFNGLISENABLEDIPROC                                    pglIsEnabledi;
static PFNGLBEGINTRANSFORMFEEDBACKPROC                        pglBeginTransformFeedback;
static PFNGLENDTRANSFORMFEEDBACKPROC                          pglEndTransformFeedback;
static PFNGLBINDBUFFERRANGEPROC                               pglBindBufferRange;
static PFNGLBINDBUFFERBASEPROC                                pglBindBufferBase;
static PFNGLTRANSFORMFEEDBACKVARYINGSPROC                     pglTransformFeedbackVaryings;
static PFNGLGETTRANSFORMFEEDBACKVARYINGPROC                   pglGetTransformFeedbackVarying;
static PFNGLCLAMPCOLORPROC                                    pglClampColor;
static PFNGLBEGINCONDITIONALRENDERPROC                        pglBeginConditionalRender;
static PFNGLENDCONDITIONALRENDERPROC                          pglEndConditionalRender;
static PFNGLVERTEXATTRIBIPOINTERPROC                          pglVertexAttribIPointer;
static PFNGLGETVERTEXATTRIBIIVPROC                            pglGetVertexAttribIiv;
static PFNGLGETVERTEXATTRIBIUIVPROC                           pglGetVertexAttribIuiv;
static PFNGLVERTEXATTRIBI1IPROC                               pglVertexAttribI1i;
static PFNGLVERTEXATTRIBI2IPROC                               pglVertexAttribI2i;
static PFNGLVERTEXATTRIBI3IPROC                               pglVertexAttribI3i;
static PFNGLVERTEXATTRIBI4IPROC                               pglVertexAttribI4i;
static PFNGLVERTEXATTRIBI1UIPROC                              pglVertexAttribI1ui;
static PFNGLVERTEXATTRIBI2UIPROC                              pglVertexAttribI2ui;
static PFNGLVERTEXATTRIBI3UIPROC                              pglVertexAttribI3ui;
static PFNGLVERTEXATTRIBI4UIPROC                              pglVertexAttribI4ui;
static PFNGLVERTEXATTRIBI1IVPROC                              pglVertexAttribI1iv;
static PFNGLVERTEXATTRIBI2IVPROC                              pglVertexAttribI2iv;
static PFNGLVERTEXATTRIBI3IVPROC                              pglVertexAttribI3iv;
static PFNGLVERTEXATTRIBI4IVPROC                              pglVertexAttribI4iv;
static PFNGLVERTEXATTRIBI1UIVPROC                             pglVertexAttribI1uiv;
static PFNGLVERTEXATTRIBI2UIVPROC                             pglVertexAttribI2uiv;
static PFNGLVERTEXATTRIBI3UIVPROC                             pglVertexAttribI3uiv;
static PFNGLVERTEXATTRIBI4UIVPROC                             pglVertexAttribI4uiv;
static PFNGLVERTEXATTRIBI4BVPROC                              pglVertexAttribI4bv;
static PFNGLVERTEXATTRIBI4SVPROC                              pglVertexAttribI4sv;
static PFNGLVERTEXATTRIBI4UBVPROC                             pglVertexAttribI4ubv;
static PFNGLVERTEXATTRIBI4USVPROC                             pglVertexAttribI4usv;
static PFNGLGETUNIFORMUIVPROC                                 pglGetUniformuiv;
static PFNGLBINDFRAGDATALOCATIONPROC                          pglBindFragDataLocation;
static PFNGLGETFRAGDATALOCATIONPROC                           pglGetFragDataLocation;
static PFNGLUNIFORM1UIPROC                                    pglUniform1ui;
static PFNGLUNIFORM2UIPROC                                    pglUniform2ui;
static PFNGLUNIFORM3UIPROC                                    pglUniform3ui;
static PFNGLUNIFORM4UIPROC                                    pglUniform4ui;
static PFNGLUNIFORM1UIVPROC                                   pglUniform1uiv;
static PFNGLUNIFORM2UIVPROC                                   pglUniform2uiv;
static PFNGLUNIFORM3UIVPROC                                   pglUniform3uiv;
static PFNGLUNIFORM4UIVPROC                                   pglUniform4uiv;
static PFNGLTEXPARAMETERIIVPROC                               pglTexParameterIiv;
static PFNGLTEXPARAMETERIUIVPROC                              pglTexParameterIuiv;
static PFNGLGETTEXPARAMETERIIVPROC                            pglGetTexParameterIiv;
static PFNGLGETTEXPARAMETERIUIVPROC                           pglGetTexParameterIuiv;
static PFNGLCLEARBUFFERIVPROC                                 pglClearBufferiv;
static PFNGLCLEARBUFFERUIVPROC                                pglClearBufferuiv;
static PFNGLCLEARBUFFERFVPROC                                 pglClearBufferfv;
static PFNGLCLEARBUFFERFIPROC                                 pglClearBufferfi;
static PFNGLGETSTRINGIPROC                                    pglGetStringi;
static PFNGLISRENDERBUFFERPROC                                pglIsRenderbuffer;
static PFNGLBINDRENDERBUFFERPROC                              pglBindRenderbuffer;
static PFNGLDELETERENDERBUFFERSPROC                           pglDeleteRenderbuffers;
static PFNGLGENRENDERBUFFERSPROC                              pglGenRenderbuffers;
static PFNGLRENDERBUFFERSTORAGEPROC                           pglRenderbufferStorage;
static PFNGLGETRENDERBUFFERPARAMETERIVPROC                    pglGetRenderbufferParameteriv;
static PFNGLISFRAMEBUFFERPROC                                 pglIsFramebuffer;
static PFNGLBINDFRAMEBUFFERPROC                               pglBindFramebuffer;
static PFNGLDELETEFRAMEBUFFERSPROC                            pglDeleteFramebuffers;
static PFNGLGENFRAMEBUFFERSPROC                               pglGenFramebuffers;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC                        pglCheckFramebufferStatus;
static PFNGLFRAMEBUFFERTEXTURE1DPROC                          pglFramebufferTexture1D;
static PFNGLFRAMEBUFFERTEXTURE2DPROC                          pglFramebufferTexture2D;
static PFNGLFRAMEBUFFERTEXTURE3DPROC                          pglFramebufferTexture3D;
static PFNGLFRAMEBUFFERRENDERBUFFERPROC                       pglFramebufferRenderbuffer;
static PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC           pglGetFramebufferAttachmentParameteriv;
static PFNGLGENERATEMIPMAPPROC                                pglGenerateMipmap;
static PFNGLBLITFRAMEBUFFERPROC                               pglBlitFramebuffer;
static PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC                pglRenderbufferStorageMultisample;
static PFNGLFRAMEBUFFERTEXTURELAYERPROC                       pglFramebufferTextureLayer;
static PFNGLMAPBUFFERRANGEPROC                                pglMapBufferRange;
static PFNGLFLUSHMAPPEDBUFFERRANGEPROC                        pglFlushMappedBufferRange;
static PFNGLBINDVERTEXARRAYPROC                               pglBindVertexArray;
static PFNGLDELETEVERTEXARRAYSPROC                            pglDeleteVertexArrays;
static PFNGLGENVERTEXARRAYSPROC                               pglGenVertexArrays;
static PFNGLISVERTEXARRAYPROC                                 pglIsVertexArray;
static PFNGLDRAWARRAYSINSTANCEDPROC                           pglDrawArraysInstanced;
static PFNGLDRAWELEMENTSINSTANCEDPROC                         pglDrawElementsInstanced;
static PFNGLTEXBUFFERPROC                                     pglTexBuffer;
static PFNGLPRIMITIVERESTARTINDEXPROC                         pglPrimitiveRestartIndex;
static PFNGLCOPYBUFFERSUBDATAPROC                             pglCopyBufferSubData;
static PFNGLGETUNIFORMINDICESPROC                             pglGetUniformIndices;
static PFNGLGETACTIVEUNIFORMSIVPROC                           pglGetActiveUniformsiv;
static PFNGLGETACTIVEUNIFORMNAMEPROC                          pglGetActiveUniformName;
static PFNGLGETUNIFORMBLOCKINDEXPROC                          pglGetUniformBlockIndex;
static PFNGLGETACTIVEUNIFORMBLOCKIVPROC                       pglGetActiveUniformBlockiv;
static PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC                     pglGetActiveUniformBlockName;
static PFNGLUNIFORMBLOCKBINDINGPROC                           pglUniformBlockBinding;
static PFNGLDRAWELEMENTSBASEVERTEXPROC                        pglDrawElementsBaseVertex;
static PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC                   pglDrawRangeElementsBaseVertex;
static PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC               pglDrawElementsInstancedBaseVertex;
static PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC                   pglMultiDrawElementsBaseVertex;
static PFNGLPROVOKINGVERTEXPROC                               pglProvokingVertex;
static PFNGLFENCESYNCPROC                                     pglFenceSync;
static PFNGLISSYNCPROC                                        pglIsSync;
static PFNGLDELETESYNCPROC                                    pglDeleteSync;
static PFNGLCLIENTWAITSYNCPROC                                pglClientWaitSync;
static PFNGLWAITSYNCPROC                                      pglWaitSync;
static PFNGLGETINTEGER64VPROC                                 pglGetInteger64v;
static PFNGLGETSYNCIVPROC                                     pglGetSynciv;
static PFNGLGETINTEGER64I_VPROC                               pglGetInteger64i_v;
static PFNGLGETBUFFERPARAMETERI64VPROC                        pglGetBufferParameteri64v;
static PFNGLFRAMEBUFFERTEXTUREPROC                            pglFramebufferTexture;
static PFNGLTEXIMAGE2DMULTISAMPLEPROC                         pglTexImage2DMultisample;
static PFNGLTEXIMAGE3DMULTISAMPLEPROC                         pglTexImage3DMultisample;
static PFNGLGETMULTISAMPLEFVPROC                              pglGetMultisamplefv;
static PFNGLSAMPLEMASKIPROC                                   pglSampleMaski;
static PFNGLBINDFRAGDATALOCATIONINDEXEDPROC                   pglBindFragDataLocationIndexed;
static PFNGLGETFRAGDATAINDEXPROC                              pglGetFragDataIndex;
static PFNGLGENSAMPLERSPROC                                   pglGenSamplers;
static PFNGLDELETESAMPLERSPROC                                pglDeleteSamplers;
static PFNGLISSAMPLERPROC                                     pglIsSampler;
static PFNGLBINDSAMPLERPROC                                   pglBindSampler;
static PFNGLSAMPLERPARAMETERIPROC                             pglSamplerParameteri;
static PFNGLSAMPLERPARAMETERIVPROC                            pglSamplerParameteriv;
static PFNGLSAMPLERPARAMETERFPROC                             pglSamplerParameterf;
static PFNGLSAMPLERPARAMETERFVPROC                            pglSamplerParameterfv;
static PFNGLSAMPLERPARAMETERIIVPROC                           pglSamplerParameterIiv;
static PFNGLSAMPLERPARAMETERIUIVPROC                          pglSamplerParameterIuiv;
static PFNGLGETSAMPLERPARAMETERIVPROC                         pglGetSamplerParameteriv;
static PFNGLGETSAMPLERPARAMETERIIVPROC                        pglGetSamplerParameterIiv;
static PFNGLGETSAMPLERPARAMETERFVPROC                         pglGetSamplerParameterfv;
static PFNGLGETSAMPLERPARAMETERIUIVPROC                       pglGetSamplerParameterIuiv;
static PFNGLQUERYCOUNTERPROC                                  pglQueryCounter;
static PFNGLGETQUERYOBJECTI64VPROC                            pglGetQueryObjecti64v;
static PFNGLGETQUERYOBJECTUI64VPROC                           pglGetQueryObjectui64v;
static PFNGLVERTEXATTRIBDIVISORPROC                           pglVertexAttribDivisor;
static PFNGLVERTEXATTRIBP1UIPROC                              pglVertexAttribP1ui;
static PFNGLVERTEXATTRIBP1UIVPROC                             pglVertexAttribP1uiv;
static PFNGLVERTEXATTRIBP2UIPROC                              pglVertexAttribP2ui;
static PFNGLVERTEXATTRIBP2UIVPROC                             pglVertexAttribP2uiv;
static PFNGLVERTEXATTRIBP3UIPROC                              pglVertexAttribP3ui;
static PFNGLVERTEXATTRIBP3UIVPROC                             pglVertexAttribP3uiv;
static PFNGLVERTEXATTRIBP4UIPROC                              pglVertexAttribP4ui;
static PFNGLVERTEXATTRIBP4UIVPROC                             pglVertexAttribP4uiv;
static PFNGLMINSAMPLESHADINGPROC                              pglMinSampleShading;
static PFNGLBLENDEQUATIONIPROC                                pglBlendEquationi;
static PFNGLBLENDEQUATIONSEPARATEIPROC                        pglBlendEquationSeparatei;
static PFNGLBLENDFUNCIPROC                                    pglBlendFunci;
static PFNGLBLENDFUNCSEPARATEIPROC                            pglBlendFuncSeparatei;
static PFNGLDRAWARRAYSINDIRECTPROC                            pglDrawArraysIndirect;
static PFNGLDRAWELEMENTSINDIRECTPROC                          pglDrawElementsIndirect;
static PFNGLUNIFORM1DPROC                                     pglUniform1d;
static PFNGLUNIFORM2DPROC                                     pglUniform2d;
static PFNGLUNIFORM3DPROC                                     pglUniform3d;
static PFNGLUNIFORM4DPROC                                     pglUniform4d;
static PFNGLUNIFORM1DVPROC                                    pglUniform1dv;
static PFNGLUNIFORM2DVPROC                                    pglUniform2dv;
static PFNGLUNIFORM3DVPROC                                    pglUniform3dv;
static PFNGLUNIFORM4DVPROC                                    pglUniform4dv;
static PFNGLUNIFORMMATRIX2DVPROC                              pglUniformMatrix2dv;
static PFNGLUNIFORMMATRIX3DVPROC                              pglUniformMatrix3dv;
static PFNGLUNIFORMMATRIX4DVPROC                              pglUniformMatrix4dv;
static PFNGLUNIFORMMATRIX2X3DVPROC                            pglUniformMatrix2x3dv;
static PFNGLUNIFORMMATRIX2X4DVPROC                            pglUniformMatrix2x4dv;
static PFNGLUNIFORMMATRIX3X2DVPROC                            pglUniformMatrix3x2dv;
static PFNGLUNIFORMMATRIX3X4DVPROC                            pglUniformMatrix3x4dv;
static PFNGLUNIFORMMATRIX4X2DVPROC                            pglUniformMatrix4x2dv;
static PFNGLUNIFORMMATRIX4X3DVPROC                            pglUniformMatrix4x3dv;
static PFNGLGETUNIFORMDVPROC                                  pglGetUniformdv;
static PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC                  pglGetSubroutineUniformLocation;
static PFNGLGETSUBROUTINEINDEXPROC                            pglGetSubroutineIndex;
static PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC                  pglGetActiveSubroutineUniformiv;
static PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC                pglGetActiveSubroutineUniformName;
static PFNGLGETACTIVESUBROUTINENAMEPROC                       pglGetActiveSubroutineName;
static PFNGLUNIFORMSUBROUTINESUIVPROC                         pglUniformSubroutinesuiv;
static PFNGLGETUNIFORMSUBROUTINEUIVPROC                       pglGetUniformSubroutineuiv;
static PFNGLGETPROGRAMSTAGEIVPROC                             pglGetProgramStageiv;
static PFNGLPATCHPARAMETERIPROC                               pglPatchParameteri;
static PFNGLPATCHPARAMETERFVPROC                              pglPatchParameterfv;
static PFNGLBINDTRANSFORMFEEDBACKPROC                         pglBindTransformFeedback;
static PFNGLDELETETRANSFORMFEEDBACKSPROC                      pglDeleteTransformFeedbacks;
static PFNGLGENTRANSFORMFEEDBACKSPROC                         pglGenTransformFeedbacks;
static PFNGLISTRANSFORMFEEDBACKPROC                           pglIsTransformFeedback;
static PFNGLPAUSETRANSFORMFEEDBACKPROC                        pglPauseTransformFeedback;
static PFNGLRESUMETRANSFORMFEEDBACKPROC                       pglResumeTransformFeedback;
static PFNGLDRAWTRANSFORMFEEDBACKPROC                         pglDrawTransformFeedback;
static PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC                   pglDrawTransformFeedbackStream;
static PFNGLBEGINQUERYINDEXEDPROC                             pglBeginQueryIndexed;
static PFNGLENDQUERYINDEXEDPROC                               pglEndQueryIndexed;
static PFNGLGETQUERYINDEXEDIVPROC                             pglGetQueryIndexediv;
static PFNGLRELEASESHADERCOMPILERPROC                         pglReleaseShaderCompiler;
static PFNGLSHADERBINARYPROC                                  pglShaderBinary;
static PFNGLGETSHADERPRECISIONFORMATPROC                      pglGetShaderPrecisionFormat;
static PFNGLDEPTHRANGEFPROC                                   pglDepthRangef;
static PFNGLCLEARDEPTHFPROC                                   pglClearDepthf;
static PFNGLGETPROGRAMBINARYPROC                              pglGetProgramBinary;
static PFNGLPROGRAMBINARYPROC                                 pglProgramBinary;
static PFNGLPROGRAMPARAMETERIPROC                             pglProgramParameteri;
static PFNGLUSEPROGRAMSTAGESPROC                              pglUseProgramStages;
static PFNGLACTIVESHADERPROGRAMPROC                           pglActiveShaderProgram;
static PFNGLCREATESHADERPROGRAMVPROC                          pglCreateShaderProgramv;
static PFNGLBINDPROGRAMPIPELINEPROC                           pglBindProgramPipeline;
static PFNGLDELETEPROGRAMPIPELINESPROC                        pglDeleteProgramPipelines;
static PFNGLGENPROGRAMPIPELINESPROC                           pglGenProgramPipelines;
static PFNGLISPROGRAMPIPELINEPROC                             pglIsProgramPipeline;
static PFNGLGETPROGRAMPIPELINEIVPROC                          pglGetProgramPipelineiv;
static PFNGLPROGRAMUNIFORM1IPROC                              pglProgramUniform1i;
static PFNGLPROGRAMUNIFORM1IVPROC                             pglProgramUniform1iv;
static PFNGLPROGRAMUNIFORM1FPROC                              pglProgramUniform1f;
static PFNGLPROGRAMUNIFORM1FVPROC                             pglProgramUniform1fv;
static PFNGLPROGRAMUNIFORM1DPROC                              pglProgramUniform1d;
static PFNGLPROGRAMUNIFORM1DVPROC                             pglProgramUniform1dv;
static PFNGLPROGRAMUNIFORM1UIPROC                             pglProgramUniform1ui;
static PFNGLPROGRAMUNIFORM1UIVPROC                            pglProgramUniform1uiv;
static PFNGLPROGRAMUNIFORM2IPROC                              pglProgramUniform2i;
static PFNGLPROGRAMUNIFORM2IVPROC                             pglProgramUniform2iv;
static PFNGLPROGRAMUNIFORM2FPROC                              pglProgramUniform2f;
static PFNGLPROGRAMUNIFORM2FVPROC                             pglProgramUniform2fv;
static PFNGLPROGRAMUNIFORM2DPROC                              pglProgramUniform2d;
static PFNGLPROGRAMUNIFORM2DVPROC                             pglProgramUniform2dv;
static PFNGLPROGRAMUNIFORM2UIPROC                             pglProgramUniform2ui;
static PFNGLPROGRAMUNIFORM2UIVPROC                            pglProgramUniform2uiv;
static PFNGLPROGRAMUNIFORM3IPROC                              pglProgramUniform3i;
static PFNGLPROGRAMUNIFORM3IVPROC                             pglProgramUniform3iv;
static PFNGLPROGRAMUNIFORM3FPROC                              pglProgramUniform3f;
static PFNGLPROGRAMUNIFORM3FVPROC                             pglProgramUniform3fv;
static PFNGLPROGRAMUNIFORM3DPROC                              pglProgramUniform3d;
static PFNGLPROGRAMUNIFORM3DVPROC                             pglProgramUniform3dv;
static PFNGLPROGRAMUNIFORM3UIPROC                             pglProgramUniform3ui;
static PFNGLPROGRAMUNIFORM3UIVPROC                            pglProgramUniform3uiv;
static PFNGLPROGRAMUNIFORM4IPROC                              pglProgramUniform4i;
static PFNGLPROGRAMUNIFORM4IVPROC                             pglProgramUniform4iv;
static PFNGLPROGRAMUNIFORM4FPROC                              pglProgramUniform4f;
static PFNGLPROGRAMUNIFORM4FVPROC                             pglProgramUniform4fv;
static PFNGLPROGRAMUNIFORM4DPROC                              pglProgramUniform4d;
static PFNGLPROGRAMUNIFORM4DVPROC                             pglProgramUniform4dv;
static PFNGLPROGRAMUNIFORM4UIPROC                             pglProgramUniform4ui;
static PFNGLPROGRAMUNIFORM4UIVPROC                            pglProgramUniform4uiv;
static PFNGLPROGRAMUNIFORMMATRIX2FVPROC                       pglProgramUniformMatrix2fv;
static PFNGLPROGRAMUNIFORMMATRIX3FVPROC                       pglProgramUniformMatrix3fv;
static PFNGLPROGRAMUNIFORMMATRIX4FVPROC                       pglProgramUniformMatrix4fv;
static PFNGLPROGRAMUNIFORMMATRIX2DVPROC                       pglProgramUniformMatrix2dv;
static PFNGLPROGRAMUNIFORMMATRIX3DVPROC                       pglProgramUniformMatrix3dv;
static PFNGLPROGRAMUNIFORMMATRIX4DVPROC                       pglProgramUniformMatrix4dv;
static PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC                     pglProgramUniformMatrix2x3fv;
static PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC                     pglProgramUniformMatrix3x2fv;
static PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC                     pglProgramUniformMatrix2x4fv;
static PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC                     pglProgramUniformMatrix4x2fv;
static PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC                     pglProgramUniformMatrix3x4fv;
static PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC                     pglProgramUniformMatrix4x3fv;
static PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC                     pglProgramUniformMatrix2x3dv;
static PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC                     pglProgramUniformMatrix3x2dv;
static PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC                     pglProgramUniformMatrix2x4dv;
static PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC                     pglProgramUniformMatrix4x2dv;
static PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC                     pglProgramUniformMatrix3x4dv;
static PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC                     pglProgramUniformMatrix4x3dv;
static PFNGLVALIDATEPROGRAMPIPELINEPROC                       pglValidateProgramPipeline;
static PFNGLGETPROGRAMPIPELINEINFOLOGPROC                     pglGetProgramPipelineInfoLog;
static PFNGLVERTEXATTRIBL1DPROC                               pglVertexAttribL1d;
static PFNGLVERTEXATTRIBL2DPROC                               pglVertexAttribL2d;
static PFNGLVERTEXATTRIBL3DPROC                               pglVertexAttribL3d;
static PFNGLVERTEXATTRIBL4DPROC                               pglVertexAttribL4d;
static PFNGLVERTEXATTRIBL1DVPROC                              pglVertexAttribL1dv;
static PFNGLVERTEXATTRIBL2DVPROC                              pglVertexAttribL2dv;
static PFNGLVERTEXATTRIBL3DVPROC                              pglVertexAttribL3dv;
static PFNGLVERTEXATTRIBL4DVPROC                              pglVertexAttribL4dv;
static PFNGLVERTEXATTRIBLPOINTERPROC                          pglVertexAttribLPointer;
static PFNGLGETVERTEXATTRIBLDVPROC                            pglGetVertexAttribLdv;
static PFNGLVIEWPORTARRAYVPROC                                pglViewportArrayv;
static PFNGLVIEWPORTINDEXEDFPROC                              pglViewportIndexedf;
static PFNGLVIEWPORTINDEXEDFVPROC                             pglViewportIndexedfv;
static PFNGLSCISSORARRAYVPROC                                 pglScissorArrayv;
static PFNGLSCISSORINDEXEDPROC                                pglScissorIndexed;
static PFNGLSCISSORINDEXEDVPROC                               pglScissorIndexedv;
static PFNGLDEPTHRANGEARRAYVPROC                              pglDepthRangeArrayv;
static PFNGLDEPTHRANGEINDEXEDPROC                             pglDepthRangeIndexed;
static PFNGLGETFLOATI_VPROC                                   pglGetFloati_v;
static PFNGLGETDOUBLEI_VPROC                                  pglGetDoublei_v;
static PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC               pglDrawArraysInstancedBaseInstance;
static PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC             pglDrawElementsInstancedBaseInstance;
static PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC   pglDrawElementsInstancedBaseVertexBaseInstance;
static PFNGLGETINTERNALFORMATIVPROC                           pglGetInternalformativ;
static PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC                pglGetActiveAtomicCounterBufferiv;
static PFNGLBINDIMAGETEXTUREPROC                              pglBindImageTexture;
static PFNGLMEMORYBARRIERPROC                                 pglMemoryBarrier;
static PFNGLTEXSTORAGE1DPROC                                  pglTexStorage1D;
static PFNGLTEXSTORAGE2DPROC                                  pglTexStorage2D;
static PFNGLTEXSTORAGE3DPROC                                  pglTexStorage3D;
static PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC                pglDrawTransformFeedbackInstanced;
static PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC          pglDrawTransformFeedbackStreamInstanced;
static PFNGLCLEARBUFFERDATAPROC                               pglClearBufferData;
static PFNGLCLEARBUFFERSUBDATAPROC                            pglClearBufferSubData;
static PFNGLDISPATCHCOMPUTEPROC                               pglDispatchCompute;
static PFNGLDISPATCHCOMPUTEINDIRECTPROC                       pglDispatchComputeIndirect;
static PFNGLCOPYIMAGESUBDATAPROC                              pglCopyImageSubData;
static PFNGLFRAMEBUFFERPARAMETERIPROC                         pglFramebufferParameteri;
static PFNGLGETFRAMEBUFFERPARAMETERIVPROC                     pglGetFramebufferParameteriv;
static PFNGLGETINTERNALFORMATI64VPROC                         pglGetInternalformati64v;
static PFNGLINVALIDATETEXSUBIMAGEPROC                         pglInvalidateTexSubImage;
static PFNGLINVALIDATETEXIMAGEPROC                            pglInvalidateTexImage;
static PFNGLINVALIDATEBUFFERSUBDATAPROC                       pglInvalidateBufferSubData;
static PFNGLINVALIDATEBUFFERDATAPROC                          pglInvalidateBufferData;
static PFNGLINVALIDATEFRAMEBUFFERPROC                         pglInvalidateFramebuffer;
static PFNGLINVALIDATESUBFRAMEBUFFERPROC                      pglInvalidateSubFramebuffer;
static PFNGLMULTIDRAWARRAYSINDIRECTPROC                       pglMultiDrawArraysIndirect;
static PFNGLMULTIDRAWELEMENTSINDIRECTPROC                     pglMultiDrawElementsIndirect;
static PFNGLGETPROGRAMINTERFACEIVPROC                         pglGetProgramInterfaceiv;
static PFNGLGETPROGRAMRESOURCEINDEXPROC                       pglGetProgramResourceIndex;
static PFNGLGETPROGRAMRESOURCENAMEPROC                        pglGetProgramResourceName;
static PFNGLGETPROGRAMRESOURCEIVPROC                          pglGetProgramResourceiv;
static PFNGLGETPROGRAMRESOURCELOCATIONPROC                    pglGetProgramResourceLocation;
static PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC               pglGetProgramResourceLocationIndex;
static PFNGLSHADERSTORAGEBLOCKBINDINGPROC                     pglShaderStorageBlockBinding;
static PFNGLTEXBUFFERRANGEPROC                                pglTexBufferRange;
static PFNGLTEXSTORAGE2DMULTISAMPLEPROC                       pglTexStorage2DMultisample;
static PFNGLTEXSTORAGE3DMULTISAMPLEPROC                       pglTexStorage3DMultisample;
static PFNGLTEXTUREVIEWPROC                                   pglTextureView;
static PFNGLBINDVERTEXBUFFERPROC                              pglBindVertexBuffer;
static PFNGLVERTEXATTRIBFORMATPROC                            pglVertexAttribFormat;
static PFNGLVERTEXATTRIBIFORMATPROC                           pglVertexAttribIFormat;
static PFNGLVERTEXATTRIBLFORMATPROC                           pglVertexAttribLFormat;
static PFNGLVERTEXATTRIBBINDINGPROC                           pglVertexAttribBinding;
static PFNGLVERTEXBINDINGDIVISORPROC                          pglVertexBindingDivisor;
static PFNGLDEBUGMESSAGECONTROLPROC                           pglDebugMessageControl;
static PFNGLDEBUGMESSAGEINSERTPROC                            pglDebugMessageInsert;
static PFNGLDEBUGMESSAGECALLBACKPROC                          pglDebugMessageCallback;
static PFNGLGETDEBUGMESSAGELOGPROC                            pglGetDebugMessageLog;
static PFNGLPUSHDEBUGGROUPPROC                                pglPushDebugGroup;
static PFNGLPOPDEBUGGROUPPROC                                 pglPopDebugGroup;
static PFNGLOBJECTLABELPROC                                   pglObjectLabel;
static PFNGLGETOBJECTLABELPROC                                pglGetObjectLabel;
static PFNGLOBJECTPTRLABELPROC                                pglObjectPtrLabel;
static PFNGLGETOBJECTPTRLABELPROC                             pglGetObjectPtrLabel;

//
// load_procs loads all gl functions addresses into the pointers
//
static void load_procs() {

	pglCullFace = (PFNGLCULLFACEPROC)get_proc("glCullFace"); 
	pglFrontFace = (PFNGLFRONTFACEPROC)get_proc("glFrontFace"); 
	pglHint = (PFNGLHINTPROC)get_proc("glHint"); 
	pglLineWidth = (PFNGLLINEWIDTHPROC)get_proc("glLineWidth"); 
	pglPointSize = (PFNGLPOINTSIZEPROC)get_proc("glPointSize"); 
	pglPolygonMode = (PFNGLPOLYGONMODEPROC)get_proc("glPolygonMode"); 
	pglScissor = (PFNGLSCISSORPROC)get_proc("glScissor"); 
	pglTexParameterf = (PFNGLTEXPARAMETERFPROC)get_proc("glTexParameterf"); 
	pglTexParameterfv = (PFNGLTEXPARAMETERFVPROC)get_proc("glTexParameterfv"); 
	pglTexParameteri = (PFNGLTEXPARAMETERIPROC)get_proc("glTexParameteri"); 
	pglTexParameteriv = (PFNGLTEXPARAMETERIVPROC)get_proc("glTexParameteriv"); 
	pglTexImage1D = (PFNGLTEXIMAGE1DPROC)get_proc("glTexImage1D"); 
	pglTexImage2D = (PFNGLTEXIMAGE2DPROC)get_proc("glTexImage2D"); 
	pglDrawBuffer = (PFNGLDRAWBUFFERPROC)get_proc("glDrawBuffer"); 
	pglClear = (PFNGLCLEARPROC)get_proc("glClear"); 
	pglClearColor = (PFNGLCLEARCOLORPROC)get_proc("glClearColor"); 
	pglClearStencil = (PFNGLCLEARSTENCILPROC)get_proc("glClearStencil"); 
	pglClearDepth = (PFNGLCLEARDEPTHPROC)get_proc("glClearDepth"); 
	pglStencilMask = (PFNGLSTENCILMASKPROC)get_proc("glStencilMask"); 
	pglColorMask = (PFNGLCOLORMASKPROC)get_proc("glColorMask"); 
	pglDepthMask = (PFNGLDEPTHMASKPROC)get_proc("glDepthMask"); 
	pglDisable = (PFNGLDISABLEPROC)get_proc("glDisable"); 
	pglEnable = (PFNGLENABLEPROC)get_proc("glEnable"); 
	pglFinish = (PFNGLFINISHPROC)get_proc("glFinish"); 
	pglFlush = (PFNGLFLUSHPROC)get_proc("glFlush"); 
	pglBlendFunc = (PFNGLBLENDFUNCPROC)get_proc("glBlendFunc"); 
	pglLogicOp = (PFNGLLOGICOPPROC)get_proc("glLogicOp"); 
	pglStencilFunc = (PFNGLSTENCILFUNCPROC)get_proc("glStencilFunc"); 
	pglStencilOp = (PFNGLSTENCILOPPROC)get_proc("glStencilOp"); 
	pglDepthFunc = (PFNGLDEPTHFUNCPROC)get_proc("glDepthFunc"); 
	pglPixelStoref = (PFNGLPIXELSTOREFPROC)get_proc("glPixelStoref"); 
	pglPixelStorei = (PFNGLPIXELSTOREIPROC)get_proc("glPixelStorei"); 
	pglReadBuffer = (PFNGLREADBUFFERPROC)get_proc("glReadBuffer"); 
	pglReadPixels = (PFNGLREADPIXELSPROC)get_proc("glReadPixels"); 
	pglGetBooleanv = (PFNGLGETBOOLEANVPROC)get_proc("glGetBooleanv"); 
	pglGetDoublev = (PFNGLGETDOUBLEVPROC)get_proc("glGetDoublev"); 
	pglGetError = (PFNGLGETERRORPROC)get_proc("glGetError"); 
	pglGetFloatv = (PFNGLGETFLOATVPROC)get_proc("glGetFloatv"); 
	pglGetIntegerv = (PFNGLGETINTEGERVPROC)get_proc("glGetIntegerv"); 
	pglGetString = (PFNGLGETSTRINGPROC)get_proc("glGetString"); 
	pglGetTexImage = (PFNGLGETTEXIMAGEPROC)get_proc("glGetTexImage"); 
	pglGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)get_proc("glGetTexParameterfv"); 
	pglGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)get_proc("glGetTexParameteriv"); 
	pglGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)get_proc("glGetTexLevelParameterfv"); 
	pglGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)get_proc("glGetTexLevelParameteriv"); 
	pglIsEnabled = (PFNGLISENABLEDPROC)get_proc("glIsEnabled"); 
	pglDepthRange = (PFNGLDEPTHRANGEPROC)get_proc("glDepthRange"); 
	pglViewport = (PFNGLVIEWPORTPROC)get_proc("glViewport"); 
	pglDrawArrays = (PFNGLDRAWARRAYSPROC)get_proc("glDrawArrays"); 
	pglDrawElements = (PFNGLDRAWELEMENTSPROC)get_proc("glDrawElements"); 
	pglGetPointerv = (PFNGLGETPOINTERVPROC)get_proc("glGetPointerv"); 
	pglPolygonOffset = (PFNGLPOLYGONOFFSETPROC)get_proc("glPolygonOffset"); 
	pglCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)get_proc("glCopyTexImage1D"); 
	pglCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)get_proc("glCopyTexImage2D"); 
	pglCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)get_proc("glCopyTexSubImage1D"); 
	pglCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)get_proc("glCopyTexSubImage2D"); 
	pglTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)get_proc("glTexSubImage1D"); 
	pglTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)get_proc("glTexSubImage2D"); 
	pglBindTexture = (PFNGLBINDTEXTUREPROC)get_proc("glBindTexture"); 
	pglDeleteTextures = (PFNGLDELETETEXTURESPROC)get_proc("glDeleteTextures"); 
	pglGenTextures = (PFNGLGENTEXTURESPROC)get_proc("glGenTextures"); 
	pglIsTexture = (PFNGLISTEXTUREPROC)get_proc("glIsTexture"); 
	pglDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)get_proc("glDrawRangeElements"); 
	pglTexImage3D = (PFNGLTEXIMAGE3DPROC)get_proc("glTexImage3D"); 
	pglTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)get_proc("glTexSubImage3D"); 
	pglCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)get_proc("glCopyTexSubImage3D"); 
	pglActiveTexture = (PFNGLACTIVETEXTUREPROC)get_proc("glActiveTexture"); 
	pglSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)get_proc("glSampleCoverage"); 
	pglCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)get_proc("glCompressedTexImage3D"); 
	pglCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)get_proc("glCompressedTexImage2D"); 
	pglCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)get_proc("glCompressedTexImage1D"); 
	pglCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)get_proc("glCompressedTexSubImage3D"); 
	pglCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)get_proc("glCompressedTexSubImage2D"); 
	pglCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)get_proc("glCompressedTexSubImage1D"); 
	pglGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)get_proc("glGetCompressedTexImage"); 
	pglBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)get_proc("glBlendFuncSeparate"); 
	pglMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)get_proc("glMultiDrawArrays"); 
	pglMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)get_proc("glMultiDrawElements"); 
	pglPointParameterf = (PFNGLPOINTPARAMETERFPROC)get_proc("glPointParameterf"); 
	pglPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)get_proc("glPointParameterfv"); 
	pglPointParameteri = (PFNGLPOINTPARAMETERIPROC)get_proc("glPointParameteri"); 
	pglPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)get_proc("glPointParameteriv"); 
	pglBlendColor = (PFNGLBLENDCOLORPROC)get_proc("glBlendColor"); 
	pglBlendEquation = (PFNGLBLENDEQUATIONPROC)get_proc("glBlendEquation"); 
	pglGenQueries = (PFNGLGENQUERIESPROC)get_proc("glGenQueries"); 
	pglDeleteQueries = (PFNGLDELETEQUERIESPROC)get_proc("glDeleteQueries"); 
	pglIsQuery = (PFNGLISQUERYPROC)get_proc("glIsQuery"); 
	pglBeginQuery = (PFNGLBEGINQUERYPROC)get_proc("glBeginQuery"); 
	pglEndQuery = (PFNGLENDQUERYPROC)get_proc("glEndQuery"); 
	pglGetQueryiv = (PFNGLGETQUERYIVPROC)get_proc("glGetQueryiv"); 
	pglGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)get_proc("glGetQueryObjectiv"); 
	pglGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)get_proc("glGetQueryObjectuiv"); 
	pglBindBuffer = (PFNGLBINDBUFFERPROC)get_proc("glBindBuffer"); 
	pglDeleteBuffers = (PFNGLDELETEBUFFERSPROC)get_proc("glDeleteBuffers"); 
	pglGenBuffers = (PFNGLGENBUFFERSPROC)get_proc("glGenBuffers"); 
	pglIsBuffer = (PFNGLISBUFFERPROC)get_proc("glIsBuffer"); 
	pglBufferData = (PFNGLBUFFERDATAPROC)get_proc("glBufferData"); 
	pglBufferSubData = (PFNGLBUFFERSUBDATAPROC)get_proc("glBufferSubData"); 
	pglGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)get_proc("glGetBufferSubData"); 
	pglMapBuffer = (PFNGLMAPBUFFERPROC)get_proc("glMapBuffer"); 
	pglUnmapBuffer = (PFNGLUNMAPBUFFERPROC)get_proc("glUnmapBuffer"); 
	pglGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)get_proc("glGetBufferParameteriv"); 
	pglGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)get_proc("glGetBufferPointerv"); 
	pglBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)get_proc("glBlendEquationSeparate"); 
	pglDrawBuffers = (PFNGLDRAWBUFFERSPROC)get_proc("glDrawBuffers"); 
	pglStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)get_proc("glStencilOpSeparate"); 
	pglStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)get_proc("glStencilFuncSeparate"); 
	pglStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)get_proc("glStencilMaskSeparate"); 
	pglAttachShader = (PFNGLATTACHSHADERPROC)get_proc("glAttachShader"); 
	pglBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)get_proc("glBindAttribLocation"); 
	pglCompileShader = (PFNGLCOMPILESHADERPROC)get_proc("glCompileShader"); 
	pglCreateProgram = (PFNGLCREATEPROGRAMPROC)get_proc("glCreateProgram"); 
	pglCreateShader = (PFNGLCREATESHADERPROC)get_proc("glCreateShader"); 
	pglDeleteProgram = (PFNGLDELETEPROGRAMPROC)get_proc("glDeleteProgram"); 
	pglDeleteShader = (PFNGLDELETESHADERPROC)get_proc("glDeleteShader"); 
	pglDetachShader = (PFNGLDETACHSHADERPROC)get_proc("glDetachShader"); 
	pglDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)get_proc("glDisableVertexAttribArray"); 
	pglEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)get_proc("glEnableVertexAttribArray"); 
	pglGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)get_proc("glGetActiveAttrib"); 
	pglGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)get_proc("glGetActiveUniform"); 
	pglGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)get_proc("glGetAttachedShaders"); 
	pglGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)get_proc("glGetAttribLocation"); 
	pglGetProgramiv = (PFNGLGETPROGRAMIVPROC)get_proc("glGetProgramiv"); 
	pglGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)get_proc("glGetProgramInfoLog"); 
	pglGetShaderiv = (PFNGLGETSHADERIVPROC)get_proc("glGetShaderiv"); 
	pglGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)get_proc("glGetShaderInfoLog"); 
	pglGetShaderSource = (PFNGLGETSHADERSOURCEPROC)get_proc("glGetShaderSource"); 
	pglGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)get_proc("glGetUniformLocation"); 
	pglGetUniformfv = (PFNGLGETUNIFORMFVPROC)get_proc("glGetUniformfv"); 
	pglGetUniformiv = (PFNGLGETUNIFORMIVPROC)get_proc("glGetUniformiv"); 
	pglGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)get_proc("glGetVertexAttribdv"); 
	pglGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)get_proc("glGetVertexAttribfv"); 
	pglGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)get_proc("glGetVertexAttribiv"); 
	pglGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)get_proc("glGetVertexAttribPointerv"); 
	pglIsProgram = (PFNGLISPROGRAMPROC)get_proc("glIsProgram"); 
	pglIsShader = (PFNGLISSHADERPROC)get_proc("glIsShader"); 
	pglLinkProgram = (PFNGLLINKPROGRAMPROC)get_proc("glLinkProgram"); 
	pglShaderSource = (PFNGLSHADERSOURCEPROC)get_proc("glShaderSource"); 
	pglUseProgram = (PFNGLUSEPROGRAMPROC)get_proc("glUseProgram"); 
	pglUniform1f = (PFNGLUNIFORM1FPROC)get_proc("glUniform1f"); 
	pglUniform2f = (PFNGLUNIFORM2FPROC)get_proc("glUniform2f"); 
	pglUniform3f = (PFNGLUNIFORM3FPROC)get_proc("glUniform3f"); 
	pglUniform4f = (PFNGLUNIFORM4FPROC)get_proc("glUniform4f"); 
	pglUniform1i = (PFNGLUNIFORM1IPROC)get_proc("glUniform1i"); 
	pglUniform2i = (PFNGLUNIFORM2IPROC)get_proc("glUniform2i"); 
	pglUniform3i = (PFNGLUNIFORM3IPROC)get_proc("glUniform3i"); 
	pglUniform4i = (PFNGLUNIFORM4IPROC)get_proc("glUniform4i"); 
	pglUniform1fv = (PFNGLUNIFORM1FVPROC)get_proc("glUniform1fv"); 
	pglUniform2fv = (PFNGLUNIFORM2FVPROC)get_proc("glUniform2fv"); 
	pglUniform3fv = (PFNGLUNIFORM3FVPROC)get_proc("glUniform3fv"); 
	pglUniform4fv = (PFNGLUNIFORM4FVPROC)get_proc("glUniform4fv"); 
	pglUniform1iv = (PFNGLUNIFORM1IVPROC)get_proc("glUniform1iv"); 
	pglUniform2iv = (PFNGLUNIFORM2IVPROC)get_proc("glUniform2iv"); 
	pglUniform3iv = (PFNGLUNIFORM3IVPROC)get_proc("glUniform3iv"); 
	pglUniform4iv = (PFNGLUNIFORM4IVPROC)get_proc("glUniform4iv"); 
	pglUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)get_proc("glUniformMatrix2fv"); 
	pglUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)get_proc("glUniformMatrix3fv"); 
	pglUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)get_proc("glUniformMatrix4fv"); 
	pglValidateProgram = (PFNGLVALIDATEPROGRAMPROC)get_proc("glValidateProgram"); 
	pglVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)get_proc("glVertexAttrib1d"); 
	pglVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)get_proc("glVertexAttrib1dv"); 
	pglVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)get_proc("glVertexAttrib1f"); 
	pglVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)get_proc("glVertexAttrib1fv"); 
	pglVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)get_proc("glVertexAttrib1s"); 
	pglVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)get_proc("glVertexAttrib1sv"); 
	pglVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)get_proc("glVertexAttrib2d"); 
	pglVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)get_proc("glVertexAttrib2dv"); 
	pglVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)get_proc("glVertexAttrib2f"); 
	pglVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)get_proc("glVertexAttrib2fv"); 
	pglVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)get_proc("glVertexAttrib2s"); 
	pglVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)get_proc("glVertexAttrib2sv"); 
	pglVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)get_proc("glVertexAttrib3d"); 
	pglVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)get_proc("glVertexAttrib3dv"); 
	pglVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)get_proc("glVertexAttrib3f"); 
	pglVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)get_proc("glVertexAttrib3fv"); 
	pglVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)get_proc("glVertexAttrib3s"); 
	pglVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)get_proc("glVertexAttrib3sv"); 
	pglVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)get_proc("glVertexAttrib4Nbv"); 
	pglVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)get_proc("glVertexAttrib4Niv"); 
	pglVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)get_proc("glVertexAttrib4Nsv"); 
	pglVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)get_proc("glVertexAttrib4Nub"); 
	pglVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)get_proc("glVertexAttrib4Nubv"); 
	pglVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)get_proc("glVertexAttrib4Nuiv"); 
	pglVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)get_proc("glVertexAttrib4Nusv"); 
	pglVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)get_proc("glVertexAttrib4bv"); 
	pglVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)get_proc("glVertexAttrib4d"); 
	pglVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)get_proc("glVertexAttrib4dv"); 
	pglVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)get_proc("glVertexAttrib4f"); 
	pglVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)get_proc("glVertexAttrib4fv"); 
	pglVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)get_proc("glVertexAttrib4iv"); 
	pglVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)get_proc("glVertexAttrib4s"); 
	pglVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)get_proc("glVertexAttrib4sv"); 
	pglVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)get_proc("glVertexAttrib4ubv"); 
	pglVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)get_proc("glVertexAttrib4uiv"); 
	pglVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)get_proc("glVertexAttrib4usv"); 
	pglVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)get_proc("glVertexAttribPointer"); 
	pglUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)get_proc("glUniformMatrix2x3fv"); 
	pglUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)get_proc("glUniformMatrix3x2fv"); 
	pglUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)get_proc("glUniformMatrix2x4fv"); 
	pglUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)get_proc("glUniformMatrix4x2fv"); 
	pglUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)get_proc("glUniformMatrix3x4fv"); 
	pglUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)get_proc("glUniformMatrix4x3fv"); 
	pglColorMaski = (PFNGLCOLORMASKIPROC)get_proc("glColorMaski"); 
	pglGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)get_proc("glGetBooleani_v"); 
	pglGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)get_proc("glGetIntegeri_v"); 
	pglEnablei = (PFNGLENABLEIPROC)get_proc("glEnablei"); 
	pglDisablei = (PFNGLDISABLEIPROC)get_proc("glDisablei"); 
	pglIsEnabledi = (PFNGLISENABLEDIPROC)get_proc("glIsEnabledi"); 
	pglBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)get_proc("glBeginTransformFeedback"); 
	pglEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)get_proc("glEndTransformFeedback"); 
	pglBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)get_proc("glBindBufferRange"); 
	pglBindBufferBase = (PFNGLBINDBUFFERBASEPROC)get_proc("glBindBufferBase"); 
	pglTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)get_proc("glTransformFeedbackVaryings"); 
	pglGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)get_proc("glGetTransformFeedbackVarying"); 
	pglClampColor = (PFNGLCLAMPCOLORPROC)get_proc("glClampColor"); 
	pglBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)get_proc("glBeginConditionalRender"); 
	pglEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)get_proc("glEndConditionalRender"); 
	pglVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)get_proc("glVertexAttribIPointer"); 
	pglGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)get_proc("glGetVertexAttribIiv"); 
	pglGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)get_proc("glGetVertexAttribIuiv"); 
	pglVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)get_proc("glVertexAttribI1i"); 
	pglVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)get_proc("glVertexAttribI2i"); 
	pglVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)get_proc("glVertexAttribI3i"); 
	pglVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)get_proc("glVertexAttribI4i"); 
	pglVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)get_proc("glVertexAttribI1ui"); 
	pglVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)get_proc("glVertexAttribI2ui"); 
	pglVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)get_proc("glVertexAttribI3ui"); 
	pglVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)get_proc("glVertexAttribI4ui"); 
	pglVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)get_proc("glVertexAttribI1iv"); 
	pglVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)get_proc("glVertexAttribI2iv"); 
	pglVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)get_proc("glVertexAttribI3iv"); 
	pglVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)get_proc("glVertexAttribI4iv"); 
	pglVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)get_proc("glVertexAttribI1uiv"); 
	pglVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)get_proc("glVertexAttribI2uiv"); 
	pglVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)get_proc("glVertexAttribI3uiv"); 
	pglVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)get_proc("glVertexAttribI4uiv"); 
	pglVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)get_proc("glVertexAttribI4bv"); 
	pglVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)get_proc("glVertexAttribI4sv"); 
	pglVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)get_proc("glVertexAttribI4ubv"); 
	pglVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)get_proc("glVertexAttribI4usv"); 
	pglGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)get_proc("glGetUniformuiv"); 
	pglBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)get_proc("glBindFragDataLocation"); 
	pglGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)get_proc("glGetFragDataLocation"); 
	pglUniform1ui = (PFNGLUNIFORM1UIPROC)get_proc("glUniform1ui"); 
	pglUniform2ui = (PFNGLUNIFORM2UIPROC)get_proc("glUniform2ui"); 
	pglUniform3ui = (PFNGLUNIFORM3UIPROC)get_proc("glUniform3ui"); 
	pglUniform4ui = (PFNGLUNIFORM4UIPROC)get_proc("glUniform4ui"); 
	pglUniform1uiv = (PFNGLUNIFORM1UIVPROC)get_proc("glUniform1uiv"); 
	pglUniform2uiv = (PFNGLUNIFORM2UIVPROC)get_proc("glUniform2uiv"); 
	pglUniform3uiv = (PFNGLUNIFORM3UIVPROC)get_proc("glUniform3uiv"); 
	pglUniform4uiv = (PFNGLUNIFORM4UIVPROC)get_proc("glUniform4uiv"); 
	pglTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)get_proc("glTexParameterIiv"); 
	pglTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)get_proc("glTexParameterIuiv"); 
	pglGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)get_proc("glGetTexParameterIiv"); 
	pglGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)get_proc("glGetTexParameterIuiv"); 
	pglClearBufferiv = (PFNGLCLEARBUFFERIVPROC)get_proc("glClearBufferiv"); 
	pglClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)get_proc("glClearBufferuiv"); 
	pglClearBufferfv = (PFNGLCLEARBUFFERFVPROC)get_proc("glClearBufferfv"); 
	pglClearBufferfi = (PFNGLCLEARBUFFERFIPROC)get_proc("glClearBufferfi"); 
	pglGetStringi = (PFNGLGETSTRINGIPROC)get_proc("glGetStringi"); 
	pglIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)get_proc("glIsRenderbuffer"); 
	pglBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)get_proc("glBindRenderbuffer"); 
	pglDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)get_proc("glDeleteRenderbuffers"); 
	pglGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)get_proc("glGenRenderbuffers"); 
	pglRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)get_proc("glRenderbufferStorage"); 
	pglGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)get_proc("glGetRenderbufferParameteriv"); 
	pglIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)get_proc("glIsFramebuffer"); 
	pglBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)get_proc("glBindFramebuffer"); 
	pglDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)get_proc("glDeleteFramebuffers"); 
	pglGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)get_proc("glGenFramebuffers"); 
	pglCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)get_proc("glCheckFramebufferStatus"); 
	pglFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)get_proc("glFramebufferTexture1D"); 
	pglFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)get_proc("glFramebufferTexture2D"); 
	pglFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)get_proc("glFramebufferTexture3D"); 
	pglFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)get_proc("glFramebufferRenderbuffer"); 
	pglGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)get_proc("glGetFramebufferAttachmentParameteriv"); 
	pglGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)get_proc("glGenerateMipmap"); 
	pglBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)get_proc("glBlitFramebuffer"); 
	pglRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)get_proc("glRenderbufferStorageMultisample"); 
	pglFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)get_proc("glFramebufferTextureLayer"); 
	pglMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)get_proc("glMapBufferRange"); 
	pglFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)get_proc("glFlushMappedBufferRange"); 
	pglBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)get_proc("glBindVertexArray"); 
	pglDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)get_proc("glDeleteVertexArrays"); 
	pglGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)get_proc("glGenVertexArrays"); 
	pglIsVertexArray = (PFNGLISVERTEXARRAYPROC)get_proc("glIsVertexArray"); 
	pglDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)get_proc("glDrawArraysInstanced"); 
	pglDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)get_proc("glDrawElementsInstanced"); 
	pglTexBuffer = (PFNGLTEXBUFFERPROC)get_proc("glTexBuffer"); 
	pglPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)get_proc("glPrimitiveRestartIndex"); 
	pglCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)get_proc("glCopyBufferSubData"); 
	pglGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)get_proc("glGetUniformIndices"); 
	pglGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)get_proc("glGetActiveUniformsiv"); 
	pglGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)get_proc("glGetActiveUniformName"); 
	pglGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)get_proc("glGetUniformBlockIndex"); 
	pglGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)get_proc("glGetActiveUniformBlockiv"); 
	pglGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)get_proc("glGetActiveUniformBlockName"); 
	pglUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)get_proc("glUniformBlockBinding"); 
	pglDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)get_proc("glDrawElementsBaseVertex"); 
	pglDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)get_proc("glDrawRangeElementsBaseVertex"); 
	pglDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)get_proc("glDrawElementsInstancedBaseVertex"); 
	pglMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)get_proc("glMultiDrawElementsBaseVertex"); 
	pglProvokingVertex = (PFNGLPROVOKINGVERTEXPROC)get_proc("glProvokingVertex"); 
	pglFenceSync = (PFNGLFENCESYNCPROC)get_proc("glFenceSync"); 
	pglIsSync = (PFNGLISSYNCPROC)get_proc("glIsSync"); 
	pglDeleteSync = (PFNGLDELETESYNCPROC)get_proc("glDeleteSync"); 
	pglClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)get_proc("glClientWaitSync"); 
	pglWaitSync = (PFNGLWAITSYNCPROC)get_proc("glWaitSync"); 
	pglGetInteger64v = (PFNGLGETINTEGER64VPROC)get_proc("glGetInteger64v"); 
	pglGetSynciv = (PFNGLGETSYNCIVPROC)get_proc("glGetSynciv"); 
	pglGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC)get_proc("glGetInteger64i_v"); 
	pglGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)get_proc("glGetBufferParameteri64v"); 
	pglFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)get_proc("glFramebufferTexture"); 
	pglTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)get_proc("glTexImage2DMultisample"); 
	pglTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)get_proc("glTexImage3DMultisample"); 
	pglGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)get_proc("glGetMultisamplefv"); 
	pglSampleMaski = (PFNGLSAMPLEMASKIPROC)get_proc("glSampleMaski"); 
	pglBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)get_proc("glBindFragDataLocationIndexed"); 
	pglGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)get_proc("glGetFragDataIndex"); 
	pglGenSamplers = (PFNGLGENSAMPLERSPROC)get_proc("glGenSamplers"); 
	pglDeleteSamplers = (PFNGLDELETESAMPLERSPROC)get_proc("glDeleteSamplers"); 
	pglIsSampler = (PFNGLISSAMPLERPROC)get_proc("glIsSampler"); 
	pglBindSampler = (PFNGLBINDSAMPLERPROC)get_proc("glBindSampler"); 
	pglSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)get_proc("glSamplerParameteri"); 
	pglSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)get_proc("glSamplerParameteriv"); 
	pglSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)get_proc("glSamplerParameterf"); 
	pglSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)get_proc("glSamplerParameterfv"); 
	pglSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)get_proc("glSamplerParameterIiv"); 
	pglSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)get_proc("glSamplerParameterIuiv"); 
	pglGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)get_proc("glGetSamplerParameteriv"); 
	pglGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)get_proc("glGetSamplerParameterIiv"); 
	pglGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)get_proc("glGetSamplerParameterfv"); 
	pglGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)get_proc("glGetSamplerParameterIuiv"); 
	pglQueryCounter = (PFNGLQUERYCOUNTERPROC)get_proc("glQueryCounter"); 
	pglGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)get_proc("glGetQueryObjecti64v"); 
	pglGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)get_proc("glGetQueryObjectui64v"); 
	pglVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)get_proc("glVertexAttribDivisor"); 
	pglVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)get_proc("glVertexAttribP1ui"); 
	pglVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)get_proc("glVertexAttribP1uiv"); 
	pglVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)get_proc("glVertexAttribP2ui"); 
	pglVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)get_proc("glVertexAttribP2uiv"); 
	pglVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)get_proc("glVertexAttribP3ui"); 
	pglVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)get_proc("glVertexAttribP3uiv"); 
	pglVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)get_proc("glVertexAttribP4ui"); 
	pglVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)get_proc("glVertexAttribP4uiv"); 
	pglMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)get_proc("glMinSampleShading"); 
	pglBlendEquationi = (PFNGLBLENDEQUATIONIPROC)get_proc("glBlendEquationi"); 
	pglBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)get_proc("glBlendEquationSeparatei"); 
	pglBlendFunci = (PFNGLBLENDFUNCIPROC)get_proc("glBlendFunci"); 
	pglBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)get_proc("glBlendFuncSeparatei"); 
	pglDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)get_proc("glDrawArraysIndirect"); 
	pglDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)get_proc("glDrawElementsIndirect"); 
	pglUniform1d = (PFNGLUNIFORM1DPROC)get_proc("glUniform1d"); 
	pglUniform2d = (PFNGLUNIFORM2DPROC)get_proc("glUniform2d"); 
	pglUniform3d = (PFNGLUNIFORM3DPROC)get_proc("glUniform3d"); 
	pglUniform4d = (PFNGLUNIFORM4DPROC)get_proc("glUniform4d"); 
	pglUniform1dv = (PFNGLUNIFORM1DVPROC)get_proc("glUniform1dv"); 
	pglUniform2dv = (PFNGLUNIFORM2DVPROC)get_proc("glUniform2dv"); 
	pglUniform3dv = (PFNGLUNIFORM3DVPROC)get_proc("glUniform3dv"); 
	pglUniform4dv = (PFNGLUNIFORM4DVPROC)get_proc("glUniform4dv"); 
	pglUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)get_proc("glUniformMatrix2dv"); 
	pglUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)get_proc("glUniformMatrix3dv"); 
	pglUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)get_proc("glUniformMatrix4dv"); 
	pglUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)get_proc("glUniformMatrix2x3dv"); 
	pglUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)get_proc("glUniformMatrix2x4dv"); 
	pglUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)get_proc("glUniformMatrix3x2dv"); 
	pglUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)get_proc("glUniformMatrix3x4dv"); 
	pglUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)get_proc("glUniformMatrix4x2dv"); 
	pglUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)get_proc("glUniformMatrix4x3dv"); 
	pglGetUniformdv = (PFNGLGETUNIFORMDVPROC)get_proc("glGetUniformdv"); 
	pglGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)get_proc("glGetSubroutineUniformLocation"); 
	pglGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)get_proc("glGetSubroutineIndex"); 
	pglGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)get_proc("glGetActiveSubroutineUniformiv"); 
	pglGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)get_proc("glGetActiveSubroutineUniformName"); 
	pglGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)get_proc("glGetActiveSubroutineName"); 
	pglUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)get_proc("glUniformSubroutinesuiv"); 
	pglGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)get_proc("glGetUniformSubroutineuiv"); 
	pglGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)get_proc("glGetProgramStageiv"); 
	pglPatchParameteri = (PFNGLPATCHPARAMETERIPROC)get_proc("glPatchParameteri"); 
	pglPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)get_proc("glPatchParameterfv"); 
	pglBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)get_proc("glBindTransformFeedback"); 
	pglDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)get_proc("glDeleteTransformFeedbacks"); 
	pglGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)get_proc("glGenTransformFeedbacks"); 
	pglIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)get_proc("glIsTransformFeedback"); 
	pglPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)get_proc("glPauseTransformFeedback"); 
	pglResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)get_proc("glResumeTransformFeedback"); 
	pglDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)get_proc("glDrawTransformFeedback"); 
	pglDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)get_proc("glDrawTransformFeedbackStream"); 
	pglBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)get_proc("glBeginQueryIndexed"); 
	pglEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)get_proc("glEndQueryIndexed"); 
	pglGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)get_proc("glGetQueryIndexediv"); 
	pglReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)get_proc("glReleaseShaderCompiler"); 
	pglShaderBinary = (PFNGLSHADERBINARYPROC)get_proc("glShaderBinary"); 
	pglGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)get_proc("glGetShaderPrecisionFormat"); 
	pglDepthRangef = (PFNGLDEPTHRANGEFPROC)get_proc("glDepthRangef"); 
	pglClearDepthf = (PFNGLCLEARDEPTHFPROC)get_proc("glClearDepthf"); 
	pglGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC)get_proc("glGetProgramBinary"); 
	pglProgramBinary = (PFNGLPROGRAMBINARYPROC)get_proc("glProgramBinary"); 
	pglProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC)get_proc("glProgramParameteri"); 
	pglUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC)get_proc("glUseProgramStages"); 
	pglActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC)get_proc("glActiveShaderProgram"); 
	pglCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)get_proc("glCreateShaderProgramv"); 
	pglBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC)get_proc("glBindProgramPipeline"); 
	pglDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)get_proc("glDeleteProgramPipelines"); 
	pglGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC)get_proc("glGenProgramPipelines"); 
	pglIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC)get_proc("glIsProgramPipeline"); 
	pglGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)get_proc("glGetProgramPipelineiv"); 
	pglProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC)get_proc("glProgramUniform1i"); 
	pglProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)get_proc("glProgramUniform1iv"); 
	pglProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC)get_proc("glProgramUniform1f"); 
	pglProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)get_proc("glProgramUniform1fv"); 
	pglProgramUniform1d = (PFNGLPROGRAMUNIFORM1DPROC)get_proc("glProgramUniform1d"); 
	pglProgramUniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)get_proc("glProgramUniform1dv"); 
	pglProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)get_proc("glProgramUniform1ui"); 
	pglProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)get_proc("glProgramUniform1uiv"); 
	pglProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC)get_proc("glProgramUniform2i"); 
	pglProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)get_proc("glProgramUniform2iv"); 
	pglProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC)get_proc("glProgramUniform2f"); 
	pglProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)get_proc("glProgramUniform2fv"); 
	pglProgramUniform2d = (PFNGLPROGRAMUNIFORM2DPROC)get_proc("glProgramUniform2d"); 
	pglProgramUniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)get_proc("glProgramUniform2dv"); 
	pglProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)get_proc("glProgramUniform2ui"); 
	pglProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)get_proc("glProgramUniform2uiv"); 
	pglProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC)get_proc("glProgramUniform3i"); 
	pglProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)get_proc("glProgramUniform3iv"); 
	pglProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC)get_proc("glProgramUniform3f"); 
	pglProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)get_proc("glProgramUniform3fv"); 
	pglProgramUniform3d = (PFNGLPROGRAMUNIFORM3DPROC)get_proc("glProgramUniform3d"); 
	pglProgramUniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)get_proc("glProgramUniform3dv"); 
	pglProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)get_proc("glProgramUniform3ui"); 
	pglProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)get_proc("glProgramUniform3uiv"); 
	pglProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC)get_proc("glProgramUniform4i"); 
	pglProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)get_proc("glProgramUniform4iv"); 
	pglProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC)get_proc("glProgramUniform4f"); 
	pglProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)get_proc("glProgramUniform4fv"); 
	pglProgramUniform4d = (PFNGLPROGRAMUNIFORM4DPROC)get_proc("glProgramUniform4d"); 
	pglProgramUniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)get_proc("glProgramUniform4dv"); 
	pglProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)get_proc("glProgramUniform4ui"); 
	pglProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)get_proc("glProgramUniform4uiv"); 
	pglProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)get_proc("glProgramUniformMatrix2fv"); 
	pglProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)get_proc("glProgramUniformMatrix3fv"); 
	pglProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)get_proc("glProgramUniformMatrix4fv"); 
	pglProgramUniformMatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)get_proc("glProgramUniformMatrix2dv"); 
	pglProgramUniformMatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)get_proc("glProgramUniformMatrix3dv"); 
	pglProgramUniformMatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)get_proc("glProgramUniformMatrix4dv"); 
	pglProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)get_proc("glProgramUniformMatrix2x3fv"); 
	pglProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)get_proc("glProgramUniformMatrix3x2fv"); 
	pglProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)get_proc("glProgramUniformMatrix2x4fv"); 
	pglProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)get_proc("glProgramUniformMatrix4x2fv"); 
	pglProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)get_proc("glProgramUniformMatrix3x4fv"); 
	pglProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)get_proc("glProgramUniformMatrix4x3fv"); 
	pglProgramUniformMatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)get_proc("glProgramUniformMatrix2x3dv"); 
	pglProgramUniformMatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)get_proc("glProgramUniformMatrix3x2dv"); 
	pglProgramUniformMatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)get_proc("glProgramUniformMatrix2x4dv"); 
	pglProgramUniformMatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)get_proc("glProgramUniformMatrix4x2dv"); 
	pglProgramUniformMatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)get_proc("glProgramUniformMatrix3x4dv"); 
	pglProgramUniformMatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)get_proc("glProgramUniformMatrix4x3dv"); 
	pglValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)get_proc("glValidateProgramPipeline"); 
	pglGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)get_proc("glGetProgramPipelineInfoLog"); 
	pglVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC)get_proc("glVertexAttribL1d"); 
	pglVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC)get_proc("glVertexAttribL2d"); 
	pglVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC)get_proc("glVertexAttribL3d"); 
	pglVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC)get_proc("glVertexAttribL4d"); 
	pglVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC)get_proc("glVertexAttribL1dv"); 
	pglVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC)get_proc("glVertexAttribL2dv"); 
	pglVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC)get_proc("glVertexAttribL3dv"); 
	pglVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC)get_proc("glVertexAttribL4dv"); 
	pglVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)get_proc("glVertexAttribLPointer"); 
	pglGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC)get_proc("glGetVertexAttribLdv"); 
	pglViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)get_proc("glViewportArrayv"); 
	pglViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)get_proc("glViewportIndexedf"); 
	pglViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)get_proc("glViewportIndexedfv"); 
	pglScissorArrayv = (PFNGLSCISSORARRAYVPROC)get_proc("glScissorArrayv"); 
	pglScissorIndexed = (PFNGLSCISSORINDEXEDPROC)get_proc("glScissorIndexed"); 
	pglScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)get_proc("glScissorIndexedv"); 
	pglDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)get_proc("glDepthRangeArrayv"); 
	pglDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)get_proc("glDepthRangeIndexed"); 
	pglGetFloati_v = (PFNGLGETFLOATI_VPROC)get_proc("glGetFloati_v"); 
	pglGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)get_proc("glGetDoublei_v"); 
	pglDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)get_proc("glDrawArraysInstancedBaseInstance"); 
	pglDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)get_proc("glDrawElementsInstancedBaseInstance"); 
	pglDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)get_proc("glDrawElementsInstancedBaseVertexBaseInstance"); 
	pglGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC)get_proc("glGetInternalformativ"); 
	pglGetActiveAtomicCounterBufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)get_proc("glGetActiveAtomicCounterBufferiv"); 
	pglBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC)get_proc("glBindImageTexture"); 
	pglMemoryBarrier = (PFNGLMEMORYBARRIERPROC)get_proc("glMemoryBarrier"); 
	pglTexStorage1D = (PFNGLTEXSTORAGE1DPROC)get_proc("glTexStorage1D"); 
	pglTexStorage2D = (PFNGLTEXSTORAGE2DPROC)get_proc("glTexStorage2D"); 
	pglTexStorage3D = (PFNGLTEXSTORAGE3DPROC)get_proc("glTexStorage3D"); 
	pglDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)get_proc("glDrawTransformFeedbackInstanced"); 
	pglDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)get_proc("glDrawTransformFeedbackStreamInstanced"); 
	pglClearBufferData = (PFNGLCLEARBUFFERDATAPROC)get_proc("glClearBufferData"); 
	pglClearBufferSubData = (PFNGLCLEARBUFFERSUBDATAPROC)get_proc("glClearBufferSubData"); 
	pglDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)get_proc("glDispatchCompute"); 
	pglDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)get_proc("glDispatchComputeIndirect"); 
	pglCopyImageSubData = (PFNGLCOPYIMAGESUBDATAPROC)get_proc("glCopyImageSubData"); 
	pglFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC)get_proc("glFramebufferParameteri"); 
	pglGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC)get_proc("glGetFramebufferParameteriv"); 
	pglGetInternalformati64v = (PFNGLGETINTERNALFORMATI64VPROC)get_proc("glGetInternalformati64v"); 
	pglInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC)get_proc("glInvalidateTexSubImage"); 
	pglInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC)get_proc("glInvalidateTexImage"); 
	pglInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC)get_proc("glInvalidateBufferSubData"); 
	pglInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC)get_proc("glInvalidateBufferData"); 
	pglInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)get_proc("glInvalidateFramebuffer"); 
	pglInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)get_proc("glInvalidateSubFramebuffer"); 
	pglMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)get_proc("glMultiDrawArraysIndirect"); 
	pglMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)get_proc("glMultiDrawElementsIndirect"); 
	pglGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC)get_proc("glGetProgramInterfaceiv"); 
	pglGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC)get_proc("glGetProgramResourceIndex"); 
	pglGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC)get_proc("glGetProgramResourceName"); 
	pglGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC)get_proc("glGetProgramResourceiv"); 
	pglGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC)get_proc("glGetProgramResourceLocation"); 
	pglGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)get_proc("glGetProgramResourceLocationIndex"); 
	pglShaderStorageBlockBinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC)get_proc("glShaderStorageBlockBinding"); 
	pglTexBufferRange = (PFNGLTEXBUFFERRANGEPROC)get_proc("glTexBufferRange"); 
	pglTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)get_proc("glTexStorage2DMultisample"); 
	pglTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC)get_proc("glTexStorage3DMultisample"); 
	pglTextureView = (PFNGLTEXTUREVIEWPROC)get_proc("glTextureView"); 
	pglBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)get_proc("glBindVertexBuffer"); 
	pglVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)get_proc("glVertexAttribFormat"); 
	pglVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC)get_proc("glVertexAttribIFormat"); 
	pglVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC)get_proc("glVertexAttribLFormat"); 
	pglVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)get_proc("glVertexAttribBinding"); 
	pglVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC)get_proc("glVertexBindingDivisor"); 
	pglDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)get_proc("glDebugMessageControl"); 
	pglDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)get_proc("glDebugMessageInsert"); 
	pglDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)get_proc("glDebugMessageCallback"); 
	pglGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)get_proc("glGetDebugMessageLog"); 
	pglPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)get_proc("glPushDebugGroup"); 
	pglPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)get_proc("glPopDebugGroup"); 
	pglObjectLabel = (PFNGLOBJECTLABELPROC)get_proc("glObjectLabel"); 
	pglGetObjectLabel = (PFNGLGETOBJECTLABELPROC)get_proc("glGetObjectLabel"); 
	pglObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)get_proc("glObjectPtrLabel"); 
	pglGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)get_proc("glGetObjectPtrLabel"); 
	
}

//
// Definitions of C wrapper functions for all OpenGL loaded pointers
// which call the pointer and optionally cals glGetError() to check
// for OpenGL errors.
//

void glCullFace(GLenum mode) {

	pglCullFace(mode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCullFace");
		}
	}
}

void glFrontFace(GLenum mode) {

	pglFrontFace(mode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFrontFace");
		}
	}
}

void glHint(GLenum target, GLenum mode) {

	pglHint(target, mode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glHint");
		}
	}
}

void glLineWidth(GLfloat width) {

	pglLineWidth(width);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glLineWidth");
		}
	}
}

void glPointSize(GLfloat size) {

	pglPointSize(size);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPointSize");
		}
	}
}

void glPolygonMode(GLenum face, GLenum mode) {

	pglPolygonMode(face, mode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPolygonMode");
		}
	}
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {

	pglScissor(x, y, width, height);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glScissor");
		}
	}
}

void glTexParameterf(GLenum target, GLenum pname, GLfloat param) {

	pglTexParameterf(target, pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexParameterf");
		}
	}
}

void glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params) {

	pglTexParameterfv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexParameterfv");
		}
	}
}

void glTexParameteri(GLenum target, GLenum pname, GLint param) {

	pglTexParameteri(target, pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexParameteri");
		}
	}
}

void glTexParameteriv(GLenum target, GLenum pname, const GLint *params) {

	pglTexParameteriv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexParameteriv");
		}
	}
}

void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels) {

	pglTexImage1D(target, level, internalformat, width, border, format, type, pixels);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexImage1D");
		}
	}
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels) {

	pglTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexImage2D");
		}
	}
}

void glDrawBuffer(GLenum buf) {

	pglDrawBuffer(buf);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawBuffer");
		}
	}
}

void glClear(GLbitfield mask) {

	pglClear(mask);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClear");
		}
	}
}

void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {

	pglClearColor(red, green, blue, alpha);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClearColor");
		}
	}
}

void glClearStencil(GLint s) {

	pglClearStencil(s);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClearStencil");
		}
	}
}

void glClearDepth(GLdouble depth) {

	pglClearDepth(depth);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClearDepth");
		}
	}
}

void glStencilMask(GLuint mask) {

	pglStencilMask(mask);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glStencilMask");
		}
	}
}

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {

	pglColorMask(red, green, blue, alpha);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glColorMask");
		}
	}
}

void glDepthMask(GLboolean flag) {

	pglDepthMask(flag);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDepthMask");
		}
	}
}

void glDisable(GLenum cap) {

	pglDisable(cap);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDisable");
		}
	}
}

void glEnable(GLenum cap) {

	pglEnable(cap);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glEnable");
		}
	}
}

void glFinish(void) {

	pglFinish();
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFinish");
		}
	}
}

void glFlush(void) {

	pglFlush();
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFlush");
		}
	}
}

void glBlendFunc(GLenum sfactor, GLenum dfactor) {

	pglBlendFunc(sfactor, dfactor);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBlendFunc");
		}
	}
}

void glLogicOp(GLenum opcode) {

	pglLogicOp(opcode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glLogicOp");
		}
	}
}

void glStencilFunc(GLenum func, GLint ref, GLuint mask) {

	pglStencilFunc(func, ref, mask);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glStencilFunc");
		}
	}
}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {

	pglStencilOp(fail, zfail, zpass);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glStencilOp");
		}
	}
}

void glDepthFunc(GLenum func) {

	pglDepthFunc(func);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDepthFunc");
		}
	}
}

void glPixelStoref(GLenum pname, GLfloat param) {

	pglPixelStoref(pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPixelStoref");
		}
	}
}

void glPixelStorei(GLenum pname, GLint param) {

	pglPixelStorei(pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPixelStorei");
		}
	}
}

void glReadBuffer(GLenum src) {

	pglReadBuffer(src);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glReadBuffer");
		}
	}
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels) {

	pglReadPixels(x, y, width, height, format, type, pixels);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glReadPixels");
		}
	}
}

void glGetBooleanv(GLenum pname, GLboolean *data) {

	pglGetBooleanv(pname, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetBooleanv");
		}
	}
}

void glGetDoublev(GLenum pname, GLdouble *data) {

	pglGetDoublev(pname, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetDoublev");
		}
	}
}

GLenum glGetError(void) {

	GLenum res = pglGetError();
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetError");
		}
	}
	return res;
}

void glGetFloatv(GLenum pname, GLfloat *data) {

	pglGetFloatv(pname, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetFloatv");
		}
	}
}

void glGetIntegerv(GLenum pname, GLint *data) {

	pglGetIntegerv(pname, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetIntegerv");
		}
	}
}

const GLubyte * glGetString(GLenum name) {

	const GLubyte * res = pglGetString(name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetString");
		}
	}
	return res;
}

void glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void *pixels) {

	pglGetTexImage(target, level, format, type, pixels);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetTexImage");
		}
	}
}

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params) {

	pglGetTexParameterfv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetTexParameterfv");
		}
	}
}

void glGetTexParameteriv(GLenum target, GLenum pname, GLint *params) {

	pglGetTexParameteriv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetTexParameteriv");
		}
	}
}

void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params) {

	pglGetTexLevelParameterfv(target, level, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetTexLevelParameterfv");
		}
	}
}

void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params) {

	pglGetTexLevelParameteriv(target, level, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetTexLevelParameteriv");
		}
	}
}

GLboolean glIsEnabled(GLenum cap) {

	GLboolean res = pglIsEnabled(cap);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsEnabled");
		}
	}
	return res;
}

void glDepthRange(GLdouble near, GLdouble far) {

	pglDepthRange(near, far);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDepthRange");
		}
	}
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {

	pglViewport(x, y, width, height);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glViewport");
		}
	}
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count) {

	pglDrawArrays(mode, first, count);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawArrays");
		}
	}
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) {

	pglDrawElements(mode, count, type, indices);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawElements");
		}
	}
}

void glGetPointerv(GLenum pname, void **params) {

	pglGetPointerv(pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetPointerv");
		}
	}
}

void glPolygonOffset(GLfloat factor, GLfloat units) {

	pglPolygonOffset(factor, units);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPolygonOffset");
		}
	}
}

void glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {

	pglCopyTexImage1D(target, level, internalformat, x, y, width, border);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCopyTexImage1D");
		}
	}
}

void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {

	pglCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCopyTexImage2D");
		}
	}
}

void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {

	pglCopyTexSubImage1D(target, level, xoffset, x, y, width);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCopyTexSubImage1D");
		}
	}
}

void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {

	pglCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCopyTexSubImage2D");
		}
	}
}

void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels) {

	pglTexSubImage1D(target, level, xoffset, width, format, type, pixels);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexSubImage1D");
		}
	}
}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels) {

	pglTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexSubImage2D");
		}
	}
}

void glBindTexture(GLenum target, GLuint texture) {

	pglBindTexture(target, texture);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindTexture");
		}
	}
}

void glDeleteTextures(GLsizei n, const GLuint *textures) {

	pglDeleteTextures(n, textures);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteTextures");
		}
	}
}

void glGenTextures(GLsizei n, GLuint *textures) {

	pglGenTextures(n, textures);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGenTextures");
		}
	}
}

GLboolean glIsTexture(GLuint texture) {

	GLboolean res = pglIsTexture(texture);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsTexture");
		}
	}
	return res;
}

void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices) {

	pglDrawRangeElements(mode, start, end, count, type, indices);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawRangeElements");
		}
	}
}

void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels) {

	pglTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexImage3D");
		}
	}
}

void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels) {

	pglTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexSubImage3D");
		}
	}
}

void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {

	pglCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCopyTexSubImage3D");
		}
	}
}

void glActiveTexture(GLenum texture) {

	pglActiveTexture(texture);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glActiveTexture");
		}
	}
}

void glSampleCoverage(GLfloat value, GLboolean invert) {

	pglSampleCoverage(value, invert);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glSampleCoverage");
		}
	}
}

void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data) {

	pglCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCompressedTexImage3D");
		}
	}
}

void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data) {

	pglCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCompressedTexImage2D");
		}
	}
}

void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data) {

	pglCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCompressedTexImage1D");
		}
	}
}

void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data) {

	pglCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCompressedTexSubImage3D");
		}
	}
}

void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data) {

	pglCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCompressedTexSubImage2D");
		}
	}
}

void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data) {

	pglCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCompressedTexSubImage1D");
		}
	}
}

void glGetCompressedTexImage(GLenum target, GLint level, void *img) {

	pglGetCompressedTexImage(target, level, img);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetCompressedTexImage");
		}
	}
}

void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {

	pglBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBlendFuncSeparate");
		}
	}
}

void glMultiDrawArrays(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount) {

	pglMultiDrawArrays(mode, first, count, drawcount);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glMultiDrawArrays");
		}
	}
}

void glMultiDrawElements(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount) {

	pglMultiDrawElements(mode, count, type, indices, drawcount);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glMultiDrawElements");
		}
	}
}

void glPointParameterf(GLenum pname, GLfloat param) {

	pglPointParameterf(pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPointParameterf");
		}
	}
}

void glPointParameterfv(GLenum pname, const GLfloat *params) {

	pglPointParameterfv(pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPointParameterfv");
		}
	}
}

void glPointParameteri(GLenum pname, GLint param) {

	pglPointParameteri(pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPointParameteri");
		}
	}
}

void glPointParameteriv(GLenum pname, const GLint *params) {

	pglPointParameteriv(pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPointParameteriv");
		}
	}
}

void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {

	pglBlendColor(red, green, blue, alpha);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBlendColor");
		}
	}
}

void glBlendEquation(GLenum mode) {

	pglBlendEquation(mode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBlendEquation");
		}
	}
}

void glGenQueries(GLsizei n, GLuint *ids) {

	pglGenQueries(n, ids);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGenQueries");
		}
	}
}

void glDeleteQueries(GLsizei n, const GLuint *ids) {

	pglDeleteQueries(n, ids);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteQueries");
		}
	}
}

GLboolean glIsQuery(GLuint id) {

	GLboolean res = pglIsQuery(id);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsQuery");
		}
	}
	return res;
}

void glBeginQuery(GLenum target, GLuint id) {

	pglBeginQuery(target, id);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBeginQuery");
		}
	}
}

void glEndQuery(GLenum target) {

	pglEndQuery(target);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glEndQuery");
		}
	}
}

void glGetQueryiv(GLenum target, GLenum pname, GLint *params) {

	pglGetQueryiv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetQueryiv");
		}
	}
}

void glGetQueryObjectiv(GLuint id, GLenum pname, GLint *params) {

	pglGetQueryObjectiv(id, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetQueryObjectiv");
		}
	}
}

void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params) {

	pglGetQueryObjectuiv(id, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetQueryObjectuiv");
		}
	}
}

void glBindBuffer(GLenum target, GLuint buffer) {

	pglBindBuffer(target, buffer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindBuffer");
		}
	}
}

void glDeleteBuffers(GLsizei n, const GLuint *buffers) {

	pglDeleteBuffers(n, buffers);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteBuffers");
		}
	}
}

void glGenBuffers(GLsizei n, GLuint *buffers) {

	pglGenBuffers(n, buffers);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGenBuffers");
		}
	}
}

GLboolean glIsBuffer(GLuint buffer) {

	GLboolean res = pglIsBuffer(buffer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsBuffer");
		}
	}
	return res;
}

void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {

	pglBufferData(target, size, data, usage);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBufferData");
		}
	}
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data) {

	pglBufferSubData(target, offset, size, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBufferSubData");
		}
	}
}

void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void *data) {

	pglGetBufferSubData(target, offset, size, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetBufferSubData");
		}
	}
}

void * glMapBuffer(GLenum target, GLenum access) {

	void * res = pglMapBuffer(target, access);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glMapBuffer");
		}
	}
	return res;
}

GLboolean glUnmapBuffer(GLenum target) {

	GLboolean res = pglUnmapBuffer(target);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUnmapBuffer");
		}
	}
	return res;
}

void glGetBufferParameteriv(GLenum target, GLenum pname, GLint *params) {

	pglGetBufferParameteriv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetBufferParameteriv");
		}
	}
}

void glGetBufferPointerv(GLenum target, GLenum pname, void **params) {

	pglGetBufferPointerv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetBufferPointerv");
		}
	}
}

void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {

	pglBlendEquationSeparate(modeRGB, modeAlpha);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBlendEquationSeparate");
		}
	}
}

void glDrawBuffers(GLsizei n, const GLenum *bufs) {

	pglDrawBuffers(n, bufs);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawBuffers");
		}
	}
}

void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {

	pglStencilOpSeparate(face, sfail, dpfail, dppass);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glStencilOpSeparate");
		}
	}
}

void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {

	pglStencilFuncSeparate(face, func, ref, mask);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glStencilFuncSeparate");
		}
	}
}

void glStencilMaskSeparate(GLenum face, GLuint mask) {

	pglStencilMaskSeparate(face, mask);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glStencilMaskSeparate");
		}
	}
}

void glAttachShader(GLuint program, GLuint shader) {

	pglAttachShader(program, shader);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glAttachShader");
		}
	}
}

void glBindAttribLocation(GLuint program, GLuint index, const GLchar *name) {

	pglBindAttribLocation(program, index, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindAttribLocation");
		}
	}
}

void glCompileShader(GLuint shader) {

	pglCompileShader(shader);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCompileShader");
		}
	}
}

GLuint glCreateProgram(void) {

	GLuint res = pglCreateProgram();
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCreateProgram");
		}
	}
	return res;
}

GLuint glCreateShader(GLenum type) {

	GLuint res = pglCreateShader(type);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCreateShader");
		}
	}
	return res;
}

void glDeleteProgram(GLuint program) {

	pglDeleteProgram(program);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteProgram");
		}
	}
}

void glDeleteShader(GLuint shader) {

	pglDeleteShader(shader);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteShader");
		}
	}
}

void glDetachShader(GLuint program, GLuint shader) {

	pglDetachShader(program, shader);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDetachShader");
		}
	}
}

void glDisableVertexAttribArray(GLuint index) {

	pglDisableVertexAttribArray(index);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDisableVertexAttribArray");
		}
	}
}

void glEnableVertexAttribArray(GLuint index) {

	pglEnableVertexAttribArray(index);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glEnableVertexAttribArray");
		}
	}
}

void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) {

	pglGetActiveAttrib(program, index, bufSize, length, size, type, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetActiveAttrib");
		}
	}
}

void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) {

	pglGetActiveUniform(program, index, bufSize, length, size, type, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetActiveUniform");
		}
	}
}

void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders) {

	pglGetAttachedShaders(program, maxCount, count, shaders);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetAttachedShaders");
		}
	}
}

GLint glGetAttribLocation(GLuint program, const GLchar *name) {

	GLint res = pglGetAttribLocation(program, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetAttribLocation");
		}
	}
	return res;
}

void glGetProgramiv(GLuint program, GLenum pname, GLint *params) {

	pglGetProgramiv(program, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramiv");
		}
	}
}

void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {

	pglGetProgramInfoLog(program, bufSize, length, infoLog);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramInfoLog");
		}
	}
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint *params) {

	pglGetShaderiv(shader, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetShaderiv");
		}
	}
}

void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {

	pglGetShaderInfoLog(shader, bufSize, length, infoLog);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetShaderInfoLog");
		}
	}
}

void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source) {

	pglGetShaderSource(shader, bufSize, length, source);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetShaderSource");
		}
	}
}

GLint glGetUniformLocation(GLuint program, const GLchar *name) {

	GLint res = pglGetUniformLocation(program, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetUniformLocation");
		}
	}
	return res;
}

void glGetUniformfv(GLuint program, GLint location, GLfloat *params) {

	pglGetUniformfv(program, location, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetUniformfv");
		}
	}
}

void glGetUniformiv(GLuint program, GLint location, GLint *params) {

	pglGetUniformiv(program, location, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetUniformiv");
		}
	}
}

void glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble *params) {

	pglGetVertexAttribdv(index, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetVertexAttribdv");
		}
	}
}

void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params) {

	pglGetVertexAttribfv(index, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetVertexAttribfv");
		}
	}
}

void glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params) {

	pglGetVertexAttribiv(index, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetVertexAttribiv");
		}
	}
}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer) {

	pglGetVertexAttribPointerv(index, pname, pointer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetVertexAttribPointerv");
		}
	}
}

GLboolean glIsProgram(GLuint program) {

	GLboolean res = pglIsProgram(program);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsProgram");
		}
	}
	return res;
}

GLboolean glIsShader(GLuint shader) {

	GLboolean res = pglIsShader(shader);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsShader");
		}
	}
	return res;
}

void glLinkProgram(GLuint program) {

	pglLinkProgram(program);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glLinkProgram");
		}
	}
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length) {

	pglShaderSource(shader, count, string, length);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glShaderSource");
		}
	}
}

void glUseProgram(GLuint program) {

	pglUseProgram(program);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUseProgram");
		}
	}
}

void glUniform1f(GLint location, GLfloat v0) {

	pglUniform1f(location, v0);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform1f");
		}
	}
}

void glUniform2f(GLint location, GLfloat v0, GLfloat v1) {

	pglUniform2f(location, v0, v1);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform2f");
		}
	}
}

void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {

	pglUniform3f(location, v0, v1, v2);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform3f");
		}
	}
}

void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {

	pglUniform4f(location, v0, v1, v2, v3);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform4f");
		}
	}
}

void glUniform1i(GLint location, GLint v0) {

	pglUniform1i(location, v0);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform1i");
		}
	}
}

void glUniform2i(GLint location, GLint v0, GLint v1) {

	pglUniform2i(location, v0, v1);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform2i");
		}
	}
}

void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2) {

	pglUniform3i(location, v0, v1, v2);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform3i");
		}
	}
}

void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {

	pglUniform4i(location, v0, v1, v2, v3);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform4i");
		}
	}
}

void glUniform1fv(GLint location, GLsizei count, const GLfloat *value) {

	pglUniform1fv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform1fv");
		}
	}
}

void glUniform2fv(GLint location, GLsizei count, const GLfloat *value) {

	pglUniform2fv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform2fv");
		}
	}
}

void glUniform3fv(GLint location, GLsizei count, const GLfloat *value) {

	pglUniform3fv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform3fv");
		}
	}
}

void glUniform4fv(GLint location, GLsizei count, const GLfloat *value) {

	pglUniform4fv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform4fv");
		}
	}
}

void glUniform1iv(GLint location, GLsizei count, const GLint *value) {

	pglUniform1iv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform1iv");
		}
	}
}

void glUniform2iv(GLint location, GLsizei count, const GLint *value) {

	pglUniform2iv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform2iv");
		}
	}
}

void glUniform3iv(GLint location, GLsizei count, const GLint *value) {

	pglUniform3iv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform3iv");
		}
	}
}

void glUniform4iv(GLint location, GLsizei count, const GLint *value) {

	pglUniform4iv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform4iv");
		}
	}
}

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglUniformMatrix2fv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix2fv");
		}
	}
}

void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglUniformMatrix3fv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix3fv");
		}
	}
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglUniformMatrix4fv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix4fv");
		}
	}
}

void glValidateProgram(GLuint program) {

	pglValidateProgram(program);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glValidateProgram");
		}
	}
}

void glVertexAttrib1d(GLuint index, GLdouble x) {

	pglVertexAttrib1d(index, x);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib1d");
		}
	}
}

void glVertexAttrib1dv(GLuint index, const GLdouble *v) {

	pglVertexAttrib1dv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib1dv");
		}
	}
}

void glVertexAttrib1f(GLuint index, GLfloat x) {

	pglVertexAttrib1f(index, x);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib1f");
		}
	}
}

void glVertexAttrib1fv(GLuint index, const GLfloat *v) {

	pglVertexAttrib1fv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib1fv");
		}
	}
}

void glVertexAttrib1s(GLuint index, GLshort x) {

	pglVertexAttrib1s(index, x);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib1s");
		}
	}
}

void glVertexAttrib1sv(GLuint index, const GLshort *v) {

	pglVertexAttrib1sv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib1sv");
		}
	}
}

void glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y) {

	pglVertexAttrib2d(index, x, y);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib2d");
		}
	}
}

void glVertexAttrib2dv(GLuint index, const GLdouble *v) {

	pglVertexAttrib2dv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib2dv");
		}
	}
}

void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {

	pglVertexAttrib2f(index, x, y);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib2f");
		}
	}
}

void glVertexAttrib2fv(GLuint index, const GLfloat *v) {

	pglVertexAttrib2fv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib2fv");
		}
	}
}

void glVertexAttrib2s(GLuint index, GLshort x, GLshort y) {

	pglVertexAttrib2s(index, x, y);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib2s");
		}
	}
}

void glVertexAttrib2sv(GLuint index, const GLshort *v) {

	pglVertexAttrib2sv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib2sv");
		}
	}
}

void glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) {

	pglVertexAttrib3d(index, x, y, z);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib3d");
		}
	}
}

void glVertexAttrib3dv(GLuint index, const GLdouble *v) {

	pglVertexAttrib3dv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib3dv");
		}
	}
}

void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {

	pglVertexAttrib3f(index, x, y, z);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib3f");
		}
	}
}

void glVertexAttrib3fv(GLuint index, const GLfloat *v) {

	pglVertexAttrib3fv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib3fv");
		}
	}
}

void glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) {

	pglVertexAttrib3s(index, x, y, z);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib3s");
		}
	}
}

void glVertexAttrib3sv(GLuint index, const GLshort *v) {

	pglVertexAttrib3sv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib3sv");
		}
	}
}

void glVertexAttrib4Nbv(GLuint index, const GLbyte *v) {

	pglVertexAttrib4Nbv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4Nbv");
		}
	}
}

void glVertexAttrib4Niv(GLuint index, const GLint *v) {

	pglVertexAttrib4Niv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4Niv");
		}
	}
}

void glVertexAttrib4Nsv(GLuint index, const GLshort *v) {

	pglVertexAttrib4Nsv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4Nsv");
		}
	}
}

void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) {

	pglVertexAttrib4Nub(index, x, y, z, w);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4Nub");
		}
	}
}

void glVertexAttrib4Nubv(GLuint index, const GLubyte *v) {

	pglVertexAttrib4Nubv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4Nubv");
		}
	}
}

void glVertexAttrib4Nuiv(GLuint index, const GLuint *v) {

	pglVertexAttrib4Nuiv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4Nuiv");
		}
	}
}

void glVertexAttrib4Nusv(GLuint index, const GLushort *v) {

	pglVertexAttrib4Nusv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4Nusv");
		}
	}
}

void glVertexAttrib4bv(GLuint index, const GLbyte *v) {

	pglVertexAttrib4bv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4bv");
		}
	}
}

void glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {

	pglVertexAttrib4d(index, x, y, z, w);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4d");
		}
	}
}

void glVertexAttrib4dv(GLuint index, const GLdouble *v) {

	pglVertexAttrib4dv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4dv");
		}
	}
}

void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {

	pglVertexAttrib4f(index, x, y, z, w);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4f");
		}
	}
}

void glVertexAttrib4fv(GLuint index, const GLfloat *v) {

	pglVertexAttrib4fv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4fv");
		}
	}
}

void glVertexAttrib4iv(GLuint index, const GLint *v) {

	pglVertexAttrib4iv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4iv");
		}
	}
}

void glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) {

	pglVertexAttrib4s(index, x, y, z, w);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4s");
		}
	}
}

void glVertexAttrib4sv(GLuint index, const GLshort *v) {

	pglVertexAttrib4sv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4sv");
		}
	}
}

void glVertexAttrib4ubv(GLuint index, const GLubyte *v) {

	pglVertexAttrib4ubv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4ubv");
		}
	}
}

void glVertexAttrib4uiv(GLuint index, const GLuint *v) {

	pglVertexAttrib4uiv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4uiv");
		}
	}
}

void glVertexAttrib4usv(GLuint index, const GLushort *v) {

	pglVertexAttrib4usv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttrib4usv");
		}
	}
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizeiptr pointer) {

	pglVertexAttribPointer(index, size, type, normalized, stride, (void *) pointer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribPointer");
		}
	}
}

void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglUniformMatrix2x3fv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix2x3fv");
		}
	}
}

void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglUniformMatrix3x2fv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix3x2fv");
		}
	}
}

void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglUniformMatrix2x4fv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix2x4fv");
		}
	}
}

void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglUniformMatrix4x2fv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix4x2fv");
		}
	}
}

void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglUniformMatrix3x4fv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix3x4fv");
		}
	}
}

void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglUniformMatrix4x3fv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix4x3fv");
		}
	}
}

void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) {

	pglColorMaski(index, r, g, b, a);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glColorMaski");
		}
	}
}

void glGetBooleani_v(GLenum target, GLuint index, GLboolean *data) {

	pglGetBooleani_v(target, index, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetBooleani_v");
		}
	}
}

void glGetIntegeri_v(GLenum target, GLuint index, GLint *data) {

	pglGetIntegeri_v(target, index, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetIntegeri_v");
		}
	}
}

void glEnablei(GLenum target, GLuint index) {

	pglEnablei(target, index);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glEnablei");
		}
	}
}

void glDisablei(GLenum target, GLuint index) {

	pglDisablei(target, index);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDisablei");
		}
	}
}

GLboolean glIsEnabledi(GLenum target, GLuint index) {

	GLboolean res = pglIsEnabledi(target, index);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsEnabledi");
		}
	}
	return res;
}

void glBeginTransformFeedback(GLenum primitiveMode) {

	pglBeginTransformFeedback(primitiveMode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBeginTransformFeedback");
		}
	}
}

void glEndTransformFeedback(void) {

	pglEndTransformFeedback();
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glEndTransformFeedback");
		}
	}
}

void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {

	pglBindBufferRange(target, index, buffer, offset, size);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindBufferRange");
		}
	}
}

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer) {

	pglBindBufferBase(target, index, buffer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindBufferBase");
		}
	}
}

void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode) {

	pglTransformFeedbackVaryings(program, count, varyings, bufferMode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTransformFeedbackVaryings");
		}
	}
}

void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name) {

	pglGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetTransformFeedbackVarying");
		}
	}
}

void glClampColor(GLenum target, GLenum clamp) {

	pglClampColor(target, clamp);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClampColor");
		}
	}
}

void glBeginConditionalRender(GLuint id, GLenum mode) {

	pglBeginConditionalRender(id, mode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBeginConditionalRender");
		}
	}
}

void glEndConditionalRender(void) {

	pglEndConditionalRender();
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glEndConditionalRender");
		}
	}
}

void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer) {

	pglVertexAttribIPointer(index, size, type, stride, pointer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribIPointer");
		}
	}
}

void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params) {

	pglGetVertexAttribIiv(index, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetVertexAttribIiv");
		}
	}
}

void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params) {

	pglGetVertexAttribIuiv(index, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetVertexAttribIuiv");
		}
	}
}

void glVertexAttribI1i(GLuint index, GLint x) {

	pglVertexAttribI1i(index, x);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI1i");
		}
	}
}

void glVertexAttribI2i(GLuint index, GLint x, GLint y) {

	pglVertexAttribI2i(index, x, y);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI2i");
		}
	}
}

void glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z) {

	pglVertexAttribI3i(index, x, y, z);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI3i");
		}
	}
}

void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) {

	pglVertexAttribI4i(index, x, y, z, w);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI4i");
		}
	}
}

void glVertexAttribI1ui(GLuint index, GLuint x) {

	pglVertexAttribI1ui(index, x);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI1ui");
		}
	}
}

void glVertexAttribI2ui(GLuint index, GLuint x, GLuint y) {

	pglVertexAttribI2ui(index, x, y);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI2ui");
		}
	}
}

void glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z) {

	pglVertexAttribI3ui(index, x, y, z);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI3ui");
		}
	}
}

void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {

	pglVertexAttribI4ui(index, x, y, z, w);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI4ui");
		}
	}
}

void glVertexAttribI1iv(GLuint index, const GLint *v) {

	pglVertexAttribI1iv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI1iv");
		}
	}
}

void glVertexAttribI2iv(GLuint index, const GLint *v) {

	pglVertexAttribI2iv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI2iv");
		}
	}
}

void glVertexAttribI3iv(GLuint index, const GLint *v) {

	pglVertexAttribI3iv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI3iv");
		}
	}
}

void glVertexAttribI4iv(GLuint index, const GLint *v) {

	pglVertexAttribI4iv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI4iv");
		}
	}
}

void glVertexAttribI1uiv(GLuint index, const GLuint *v) {

	pglVertexAttribI1uiv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI1uiv");
		}
	}
}

void glVertexAttribI2uiv(GLuint index, const GLuint *v) {

	pglVertexAttribI2uiv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI2uiv");
		}
	}
}

void glVertexAttribI3uiv(GLuint index, const GLuint *v) {

	pglVertexAttribI3uiv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI3uiv");
		}
	}
}

void glVertexAttribI4uiv(GLuint index, const GLuint *v) {

	pglVertexAttribI4uiv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI4uiv");
		}
	}
}

void glVertexAttribI4bv(GLuint index, const GLbyte *v) {

	pglVertexAttribI4bv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI4bv");
		}
	}
}

void glVertexAttribI4sv(GLuint index, const GLshort *v) {

	pglVertexAttribI4sv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI4sv");
		}
	}
}

void glVertexAttribI4ubv(GLuint index, const GLubyte *v) {

	pglVertexAttribI4ubv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI4ubv");
		}
	}
}

void glVertexAttribI4usv(GLuint index, const GLushort *v) {

	pglVertexAttribI4usv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribI4usv");
		}
	}
}

void glGetUniformuiv(GLuint program, GLint location, GLuint *params) {

	pglGetUniformuiv(program, location, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetUniformuiv");
		}
	}
}

void glBindFragDataLocation(GLuint program, GLuint color, const GLchar *name) {

	pglBindFragDataLocation(program, color, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindFragDataLocation");
		}
	}
}

GLint glGetFragDataLocation(GLuint program, const GLchar *name) {

	GLint res = pglGetFragDataLocation(program, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetFragDataLocation");
		}
	}
	return res;
}

void glUniform1ui(GLint location, GLuint v0) {

	pglUniform1ui(location, v0);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform1ui");
		}
	}
}

void glUniform2ui(GLint location, GLuint v0, GLuint v1) {

	pglUniform2ui(location, v0, v1);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform2ui");
		}
	}
}

void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) {

	pglUniform3ui(location, v0, v1, v2);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform3ui");
		}
	}
}

void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {

	pglUniform4ui(location, v0, v1, v2, v3);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform4ui");
		}
	}
}

void glUniform1uiv(GLint location, GLsizei count, const GLuint *value) {

	pglUniform1uiv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform1uiv");
		}
	}
}

void glUniform2uiv(GLint location, GLsizei count, const GLuint *value) {

	pglUniform2uiv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform2uiv");
		}
	}
}

void glUniform3uiv(GLint location, GLsizei count, const GLuint *value) {

	pglUniform3uiv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform3uiv");
		}
	}
}

void glUniform4uiv(GLint location, GLsizei count, const GLuint *value) {

	pglUniform4uiv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform4uiv");
		}
	}
}

void glTexParameterIiv(GLenum target, GLenum pname, const GLint *params) {

	pglTexParameterIiv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexParameterIiv");
		}
	}
}

void glTexParameterIuiv(GLenum target, GLenum pname, const GLuint *params) {

	pglTexParameterIuiv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexParameterIuiv");
		}
	}
}

void glGetTexParameterIiv(GLenum target, GLenum pname, GLint *params) {

	pglGetTexParameterIiv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetTexParameterIiv");
		}
	}
}

void glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params) {

	pglGetTexParameterIuiv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetTexParameterIuiv");
		}
	}
}

void glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value) {

	pglClearBufferiv(buffer, drawbuffer, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClearBufferiv");
		}
	}
}

void glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value) {

	pglClearBufferuiv(buffer, drawbuffer, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClearBufferuiv");
		}
	}
}

void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value) {

	pglClearBufferfv(buffer, drawbuffer, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClearBufferfv");
		}
	}
}

void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {

	pglClearBufferfi(buffer, drawbuffer, depth, stencil);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClearBufferfi");
		}
	}
}

const GLubyte * glGetStringi(GLenum name, GLuint index) {

	const GLubyte * res = pglGetStringi(name, index);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetStringi");
		}
	}
	return res;
}

GLboolean glIsRenderbuffer(GLuint renderbuffer) {

	GLboolean res = pglIsRenderbuffer(renderbuffer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsRenderbuffer");
		}
	}
	return res;
}

void glBindRenderbuffer(GLenum target, GLuint renderbuffer) {

	pglBindRenderbuffer(target, renderbuffer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindRenderbuffer");
		}
	}
}

void glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers) {

	pglDeleteRenderbuffers(n, renderbuffers);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteRenderbuffers");
		}
	}
}

void glGenRenderbuffers(GLsizei n, GLuint *renderbuffers) {

	pglGenRenderbuffers(n, renderbuffers);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGenRenderbuffers");
		}
	}
}

void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {

	pglRenderbufferStorage(target, internalformat, width, height);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glRenderbufferStorage");
		}
	}
}

void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params) {

	pglGetRenderbufferParameteriv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetRenderbufferParameteriv");
		}
	}
}

GLboolean glIsFramebuffer(GLuint framebuffer) {

	GLboolean res = pglIsFramebuffer(framebuffer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsFramebuffer");
		}
	}
	return res;
}

void glBindFramebuffer(GLenum target, GLuint framebuffer) {

	pglBindFramebuffer(target, framebuffer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindFramebuffer");
		}
	}
}

void glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers) {

	pglDeleteFramebuffers(n, framebuffers);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteFramebuffers");
		}
	}
}

void glGenFramebuffers(GLsizei n, GLuint *framebuffers) {

	pglGenFramebuffers(n, framebuffers);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGenFramebuffers");
		}
	}
}

GLenum glCheckFramebufferStatus(GLenum target) {

	GLenum res = pglCheckFramebufferStatus(target);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCheckFramebufferStatus");
		}
	}
	return res;
}

void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {

	pglFramebufferTexture1D(target, attachment, textarget, texture, level);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFramebufferTexture1D");
		}
	}
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {

	pglFramebufferTexture2D(target, attachment, textarget, texture, level);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFramebufferTexture2D");
		}
	}
}

void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) {

	pglFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFramebufferTexture3D");
		}
	}
}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {

	pglFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFramebufferRenderbuffer");
		}
	}
}

void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params) {

	pglGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetFramebufferAttachmentParameteriv");
		}
	}
}

void glGenerateMipmap(GLenum target) {

	pglGenerateMipmap(target);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGenerateMipmap");
		}
	}
}

void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {

	pglBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBlitFramebuffer");
		}
	}
}

void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {

	pglRenderbufferStorageMultisample(target, samples, internalformat, width, height);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glRenderbufferStorageMultisample");
		}
	}
}

void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {

	pglFramebufferTextureLayer(target, attachment, texture, level, layer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFramebufferTextureLayer");
		}
	}
}

void * glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) {

	void * res = pglMapBufferRange(target, offset, length, access);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glMapBufferRange");
		}
	}
	return res;
}

void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) {

	pglFlushMappedBufferRange(target, offset, length);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFlushMappedBufferRange");
		}
	}
}

void glBindVertexArray(GLuint array) {

	pglBindVertexArray(array);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindVertexArray");
		}
	}
}

void glDeleteVertexArrays(GLsizei n, const GLuint *arrays) {

	pglDeleteVertexArrays(n, arrays);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteVertexArrays");
		}
	}
}

void glGenVertexArrays(GLsizei n, GLuint *arrays) {

	pglGenVertexArrays(n, arrays);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGenVertexArrays");
		}
	}
}

GLboolean glIsVertexArray(GLuint array) {

	GLboolean res = pglIsVertexArray(array);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsVertexArray");
		}
	}
	return res;
}

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) {

	pglDrawArraysInstanced(mode, first, count, instancecount);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawArraysInstanced");
		}
	}
}

void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount) {

	pglDrawElementsInstanced(mode, count, type, indices, instancecount);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawElementsInstanced");
		}
	}
}

void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer) {

	pglTexBuffer(target, internalformat, buffer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexBuffer");
		}
	}
}

void glPrimitiveRestartIndex(GLuint index) {

	pglPrimitiveRestartIndex(index);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPrimitiveRestartIndex");
		}
	}
}

void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {

	pglCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCopyBufferSubData");
		}
	}
}

void glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices) {

	pglGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetUniformIndices");
		}
	}
}

void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params) {

	pglGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetActiveUniformsiv");
		}
	}
}

void glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName) {

	pglGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetActiveUniformName");
		}
	}
}

GLuint glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName) {

	GLuint res = pglGetUniformBlockIndex(program, uniformBlockName);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetUniformBlockIndex");
		}
	}
	return res;
}

void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params) {

	pglGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetActiveUniformBlockiv");
		}
	}
}

void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName) {

	pglGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetActiveUniformBlockName");
		}
	}
}

void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) {

	pglUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformBlockBinding");
		}
	}
}

void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex) {

	pglDrawElementsBaseVertex(mode, count, type, indices, basevertex);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawElementsBaseVertex");
		}
	}
}

void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex) {

	pglDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawRangeElementsBaseVertex");
		}
	}
}

void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex) {

	pglDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawElementsInstancedBaseVertex");
		}
	}
}

void glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex) {

	pglMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glMultiDrawElementsBaseVertex");
		}
	}
}

void glProvokingVertex(GLenum mode) {

	pglProvokingVertex(mode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProvokingVertex");
		}
	}
}

GLsync glFenceSync(GLenum condition, GLbitfield flags) {

	GLsync res = pglFenceSync(condition, flags);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFenceSync");
		}
	}
	return res;
}

GLboolean glIsSync(GLsync sync) {

	GLboolean res = pglIsSync(sync);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsSync");
		}
	}
	return res;
}

void glDeleteSync(GLsync sync) {

	pglDeleteSync(sync);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteSync");
		}
	}
}

GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {

	GLenum res = pglClientWaitSync(sync, flags, timeout);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClientWaitSync");
		}
	}
	return res;
}

void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {

	pglWaitSync(sync, flags, timeout);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glWaitSync");
		}
	}
}

void glGetInteger64v(GLenum pname, GLint64 *data) {

	pglGetInteger64v(pname, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetInteger64v");
		}
	}
}

void glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values) {

	pglGetSynciv(sync, pname, bufSize, length, values);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetSynciv");
		}
	}
}

void glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data) {

	pglGetInteger64i_v(target, index, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetInteger64i_v");
		}
	}
}

void glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params) {

	pglGetBufferParameteri64v(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetBufferParameteri64v");
		}
	}
}

void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) {

	pglFramebufferTexture(target, attachment, texture, level);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFramebufferTexture");
		}
	}
}

void glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {

	pglTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexImage2DMultisample");
		}
	}
}

void glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {

	pglTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexImage3DMultisample");
		}
	}
}

void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val) {

	pglGetMultisamplefv(pname, index, val);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetMultisamplefv");
		}
	}
}

void glSampleMaski(GLuint maskNumber, GLbitfield mask) {

	pglSampleMaski(maskNumber, mask);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glSampleMaski");
		}
	}
}

void glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name) {

	pglBindFragDataLocationIndexed(program, colorNumber, index, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindFragDataLocationIndexed");
		}
	}
}

GLint glGetFragDataIndex(GLuint program, const GLchar *name) {

	GLint res = pglGetFragDataIndex(program, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetFragDataIndex");
		}
	}
	return res;
}

void glGenSamplers(GLsizei count, GLuint *samplers) {

	pglGenSamplers(count, samplers);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGenSamplers");
		}
	}
}

void glDeleteSamplers(GLsizei count, const GLuint *samplers) {

	pglDeleteSamplers(count, samplers);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteSamplers");
		}
	}
}

GLboolean glIsSampler(GLuint sampler) {

	GLboolean res = pglIsSampler(sampler);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsSampler");
		}
	}
	return res;
}

void glBindSampler(GLuint unit, GLuint sampler) {

	pglBindSampler(unit, sampler);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindSampler");
		}
	}
}

void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param) {

	pglSamplerParameteri(sampler, pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glSamplerParameteri");
		}
	}
}

void glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint *param) {

	pglSamplerParameteriv(sampler, pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glSamplerParameteriv");
		}
	}
}

void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) {

	pglSamplerParameterf(sampler, pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glSamplerParameterf");
		}
	}
}

void glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat *param) {

	pglSamplerParameterfv(sampler, pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glSamplerParameterfv");
		}
	}
}

void glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint *param) {

	pglSamplerParameterIiv(sampler, pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glSamplerParameterIiv");
		}
	}
}

void glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint *param) {

	pglSamplerParameterIuiv(sampler, pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glSamplerParameterIuiv");
		}
	}
}

void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint *params) {

	pglGetSamplerParameteriv(sampler, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetSamplerParameteriv");
		}
	}
}

void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint *params) {

	pglGetSamplerParameterIiv(sampler, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetSamplerParameterIiv");
		}
	}
}

void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat *params) {

	pglGetSamplerParameterfv(sampler, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetSamplerParameterfv");
		}
	}
}

void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint *params) {

	pglGetSamplerParameterIuiv(sampler, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetSamplerParameterIuiv");
		}
	}
}

void glQueryCounter(GLuint id, GLenum target) {

	pglQueryCounter(id, target);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glQueryCounter");
		}
	}
}

void glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 *params) {

	pglGetQueryObjecti64v(id, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetQueryObjecti64v");
		}
	}
}

void glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 *params) {

	pglGetQueryObjectui64v(id, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetQueryObjectui64v");
		}
	}
}

void glVertexAttribDivisor(GLuint index, GLuint divisor) {

	pglVertexAttribDivisor(index, divisor);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribDivisor");
		}
	}
}

void glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {

	pglVertexAttribP1ui(index, type, normalized, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribP1ui");
		}
	}
}

void glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value) {

	pglVertexAttribP1uiv(index, type, normalized, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribP1uiv");
		}
	}
}

void glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {

	pglVertexAttribP2ui(index, type, normalized, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribP2ui");
		}
	}
}

void glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value) {

	pglVertexAttribP2uiv(index, type, normalized, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribP2uiv");
		}
	}
}

void glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {

	pglVertexAttribP3ui(index, type, normalized, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribP3ui");
		}
	}
}

void glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value) {

	pglVertexAttribP3uiv(index, type, normalized, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribP3uiv");
		}
	}
}

void glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {

	pglVertexAttribP4ui(index, type, normalized, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribP4ui");
		}
	}
}

void glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value) {

	pglVertexAttribP4uiv(index, type, normalized, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribP4uiv");
		}
	}
}

void glMinSampleShading(GLfloat value) {

	pglMinSampleShading(value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glMinSampleShading");
		}
	}
}

void glBlendEquationi(GLuint buf, GLenum mode) {

	pglBlendEquationi(buf, mode);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBlendEquationi");
		}
	}
}

void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha) {

	pglBlendEquationSeparatei(buf, modeRGB, modeAlpha);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBlendEquationSeparatei");
		}
	}
}

void glBlendFunci(GLuint buf, GLenum src, GLenum dst) {

	pglBlendFunci(buf, src, dst);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBlendFunci");
		}
	}
}

void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {

	pglBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBlendFuncSeparatei");
		}
	}
}

void glDrawArraysIndirect(GLenum mode, const void *indirect) {

	pglDrawArraysIndirect(mode, indirect);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawArraysIndirect");
		}
	}
}

void glDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect) {

	pglDrawElementsIndirect(mode, type, indirect);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawElementsIndirect");
		}
	}
}

void glUniform1d(GLint location, GLdouble x) {

	pglUniform1d(location, x);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform1d");
		}
	}
}

void glUniform2d(GLint location, GLdouble x, GLdouble y) {

	pglUniform2d(location, x, y);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform2d");
		}
	}
}

void glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z) {

	pglUniform3d(location, x, y, z);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform3d");
		}
	}
}

void glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {

	pglUniform4d(location, x, y, z, w);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform4d");
		}
	}
}

void glUniform1dv(GLint location, GLsizei count, const GLdouble *value) {

	pglUniform1dv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform1dv");
		}
	}
}

void glUniform2dv(GLint location, GLsizei count, const GLdouble *value) {

	pglUniform2dv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform2dv");
		}
	}
}

void glUniform3dv(GLint location, GLsizei count, const GLdouble *value) {

	pglUniform3dv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform3dv");
		}
	}
}

void glUniform4dv(GLint location, GLsizei count, const GLdouble *value) {

	pglUniform4dv(location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniform4dv");
		}
	}
}

void glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglUniformMatrix2dv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix2dv");
		}
	}
}

void glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglUniformMatrix3dv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix3dv");
		}
	}
}

void glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglUniformMatrix4dv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix4dv");
		}
	}
}

void glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglUniformMatrix2x3dv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix2x3dv");
		}
	}
}

void glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglUniformMatrix2x4dv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix2x4dv");
		}
	}
}

void glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglUniformMatrix3x2dv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix3x2dv");
		}
	}
}

void glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglUniformMatrix3x4dv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix3x4dv");
		}
	}
}

void glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglUniformMatrix4x2dv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix4x2dv");
		}
	}
}

void glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglUniformMatrix4x3dv(location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformMatrix4x3dv");
		}
	}
}

void glGetUniformdv(GLuint program, GLint location, GLdouble *params) {

	pglGetUniformdv(program, location, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetUniformdv");
		}
	}
}

GLint glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar *name) {

	GLint res = pglGetSubroutineUniformLocation(program, shadertype, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetSubroutineUniformLocation");
		}
	}
	return res;
}

GLuint glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar *name) {

	GLuint res = pglGetSubroutineIndex(program, shadertype, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetSubroutineIndex");
		}
	}
	return res;
}

void glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values) {

	pglGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetActiveSubroutineUniformiv");
		}
	}
}

void glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name) {

	pglGetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetActiveSubroutineUniformName");
		}
	}
}

void glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name) {

	pglGetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetActiveSubroutineName");
		}
	}
}

void glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint *indices) {

	pglUniformSubroutinesuiv(shadertype, count, indices);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUniformSubroutinesuiv");
		}
	}
}

void glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint *params) {

	pglGetUniformSubroutineuiv(shadertype, location, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetUniformSubroutineuiv");
		}
	}
}

void glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint *values) {

	pglGetProgramStageiv(program, shadertype, pname, values);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramStageiv");
		}
	}
}

void glPatchParameteri(GLenum pname, GLint value) {

	pglPatchParameteri(pname, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPatchParameteri");
		}
	}
}

void glPatchParameterfv(GLenum pname, const GLfloat *values) {

	pglPatchParameterfv(pname, values);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPatchParameterfv");
		}
	}
}

void glBindTransformFeedback(GLenum target, GLuint id) {

	pglBindTransformFeedback(target, id);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindTransformFeedback");
		}
	}
}

void glDeleteTransformFeedbacks(GLsizei n, const GLuint *ids) {

	pglDeleteTransformFeedbacks(n, ids);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteTransformFeedbacks");
		}
	}
}

void glGenTransformFeedbacks(GLsizei n, GLuint *ids) {

	pglGenTransformFeedbacks(n, ids);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGenTransformFeedbacks");
		}
	}
}

GLboolean glIsTransformFeedback(GLuint id) {

	GLboolean res = pglIsTransformFeedback(id);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsTransformFeedback");
		}
	}
	return res;
}

void glPauseTransformFeedback(void) {

	pglPauseTransformFeedback();
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPauseTransformFeedback");
		}
	}
}

void glResumeTransformFeedback(void) {

	pglResumeTransformFeedback();
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glResumeTransformFeedback");
		}
	}
}

void glDrawTransformFeedback(GLenum mode, GLuint id) {

	pglDrawTransformFeedback(mode, id);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawTransformFeedback");
		}
	}
}

void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream) {

	pglDrawTransformFeedbackStream(mode, id, stream);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawTransformFeedbackStream");
		}
	}
}

void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id) {

	pglBeginQueryIndexed(target, index, id);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBeginQueryIndexed");
		}
	}
}

void glEndQueryIndexed(GLenum target, GLuint index) {

	pglEndQueryIndexed(target, index);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glEndQueryIndexed");
		}
	}
}

void glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint *params) {

	pglGetQueryIndexediv(target, index, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetQueryIndexediv");
		}
	}
}

void glReleaseShaderCompiler(void) {

	pglReleaseShaderCompiler();
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glReleaseShaderCompiler");
		}
	}
}

void glShaderBinary(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length) {

	pglShaderBinary(count, shaders, binaryformat, binary, length);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glShaderBinary");
		}
	}
}

void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision) {

	pglGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetShaderPrecisionFormat");
		}
	}
}

void glDepthRangef(GLfloat n, GLfloat f) {

	pglDepthRangef(n, f);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDepthRangef");
		}
	}
}

void glClearDepthf(GLfloat d) {

	pglClearDepthf(d);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClearDepthf");
		}
	}
}

void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary) {

	pglGetProgramBinary(program, bufSize, length, binaryFormat, binary);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramBinary");
		}
	}
}

void glProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length) {

	pglProgramBinary(program, binaryFormat, binary, length);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramBinary");
		}
	}
}

void glProgramParameteri(GLuint program, GLenum pname, GLint value) {

	pglProgramParameteri(program, pname, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramParameteri");
		}
	}
}

void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program) {

	pglUseProgramStages(pipeline, stages, program);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glUseProgramStages");
		}
	}
}

void glActiveShaderProgram(GLuint pipeline, GLuint program) {

	pglActiveShaderProgram(pipeline, program);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glActiveShaderProgram");
		}
	}
}

GLuint glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const*strings) {

	GLuint res = pglCreateShaderProgramv(type, count, strings);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCreateShaderProgramv");
		}
	}
	return res;
}

void glBindProgramPipeline(GLuint pipeline) {

	pglBindProgramPipeline(pipeline);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindProgramPipeline");
		}
	}
}

void glDeleteProgramPipelines(GLsizei n, const GLuint *pipelines) {

	pglDeleteProgramPipelines(n, pipelines);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDeleteProgramPipelines");
		}
	}
}

void glGenProgramPipelines(GLsizei n, GLuint *pipelines) {

	pglGenProgramPipelines(n, pipelines);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGenProgramPipelines");
		}
	}
}

GLboolean glIsProgramPipeline(GLuint pipeline) {

	GLboolean res = pglIsProgramPipeline(pipeline);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glIsProgramPipeline");
		}
	}
	return res;
}

void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params) {

	pglGetProgramPipelineiv(pipeline, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramPipelineiv");
		}
	}
}

void glProgramUniform1i(GLuint program, GLint location, GLint v0) {

	pglProgramUniform1i(program, location, v0);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform1i");
		}
	}
}

void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value) {

	pglProgramUniform1iv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform1iv");
		}
	}
}

void glProgramUniform1f(GLuint program, GLint location, GLfloat v0) {

	pglProgramUniform1f(program, location, v0);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform1f");
		}
	}
}

void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) {

	pglProgramUniform1fv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform1fv");
		}
	}
}

void glProgramUniform1d(GLuint program, GLint location, GLdouble v0) {

	pglProgramUniform1d(program, location, v0);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform1d");
		}
	}
}

void glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble *value) {

	pglProgramUniform1dv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform1dv");
		}
	}
}

void glProgramUniform1ui(GLuint program, GLint location, GLuint v0) {

	pglProgramUniform1ui(program, location, v0);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform1ui");
		}
	}
}

void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) {

	pglProgramUniform1uiv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform1uiv");
		}
	}
}

void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1) {

	pglProgramUniform2i(program, location, v0, v1);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform2i");
		}
	}
}

void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value) {

	pglProgramUniform2iv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform2iv");
		}
	}
}

void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1) {

	pglProgramUniform2f(program, location, v0, v1);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform2f");
		}
	}
}

void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) {

	pglProgramUniform2fv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform2fv");
		}
	}
}

void glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1) {

	pglProgramUniform2d(program, location, v0, v1);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform2d");
		}
	}
}

void glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble *value) {

	pglProgramUniform2dv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform2dv");
		}
	}
}

void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1) {

	pglProgramUniform2ui(program, location, v0, v1);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform2ui");
		}
	}
}

void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) {

	pglProgramUniform2uiv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform2uiv");
		}
	}
}

void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) {

	pglProgramUniform3i(program, location, v0, v1, v2);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform3i");
		}
	}
}

void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value) {

	pglProgramUniform3iv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform3iv");
		}
	}
}

void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {

	pglProgramUniform3f(program, location, v0, v1, v2);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform3f");
		}
	}
}

void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) {

	pglProgramUniform3fv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform3fv");
		}
	}
}

void glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2) {

	pglProgramUniform3d(program, location, v0, v1, v2);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform3d");
		}
	}
}

void glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble *value) {

	pglProgramUniform3dv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform3dv");
		}
	}
}

void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) {

	pglProgramUniform3ui(program, location, v0, v1, v2);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform3ui");
		}
	}
}

void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) {

	pglProgramUniform3uiv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform3uiv");
		}
	}
}

void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {

	pglProgramUniform4i(program, location, v0, v1, v2, v3);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform4i");
		}
	}
}

void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value) {

	pglProgramUniform4iv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform4iv");
		}
	}
}

void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {

	pglProgramUniform4f(program, location, v0, v1, v2, v3);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform4f");
		}
	}
}

void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value) {

	pglProgramUniform4fv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform4fv");
		}
	}
}

void glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) {

	pglProgramUniform4d(program, location, v0, v1, v2, v3);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform4d");
		}
	}
}

void glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble *value) {

	pglProgramUniform4dv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform4dv");
		}
	}
}

void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {

	pglProgramUniform4ui(program, location, v0, v1, v2, v3);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform4ui");
		}
	}
}

void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value) {

	pglProgramUniform4uiv(program, location, count, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniform4uiv");
		}
	}
}

void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglProgramUniformMatrix2fv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix2fv");
		}
	}
}

void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglProgramUniformMatrix3fv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix3fv");
		}
	}
}

void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglProgramUniformMatrix4fv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix4fv");
		}
	}
}

void glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglProgramUniformMatrix2dv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix2dv");
		}
	}
}

void glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglProgramUniformMatrix3dv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix3dv");
		}
	}
}

void glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglProgramUniformMatrix4dv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix4dv");
		}
	}
}

void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglProgramUniformMatrix2x3fv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix2x3fv");
		}
	}
}

void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglProgramUniformMatrix3x2fv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix3x2fv");
		}
	}
}

void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglProgramUniformMatrix2x4fv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix2x4fv");
		}
	}
}

void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglProgramUniformMatrix4x2fv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix4x2fv");
		}
	}
}

void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglProgramUniformMatrix3x4fv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix3x4fv");
		}
	}
}

void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {

	pglProgramUniformMatrix4x3fv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix4x3fv");
		}
	}
}

void glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglProgramUniformMatrix2x3dv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix2x3dv");
		}
	}
}

void glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglProgramUniformMatrix3x2dv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix3x2dv");
		}
	}
}

void glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglProgramUniformMatrix2x4dv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix2x4dv");
		}
	}
}

void glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglProgramUniformMatrix4x2dv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix4x2dv");
		}
	}
}

void glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglProgramUniformMatrix3x4dv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix3x4dv");
		}
	}
}

void glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value) {

	pglProgramUniformMatrix4x3dv(program, location, count, transpose, value);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glProgramUniformMatrix4x3dv");
		}
	}
}

void glValidateProgramPipeline(GLuint pipeline) {

	pglValidateProgramPipeline(pipeline);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glValidateProgramPipeline");
		}
	}
}

void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {

	pglGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramPipelineInfoLog");
		}
	}
}

void glVertexAttribL1d(GLuint index, GLdouble x) {

	pglVertexAttribL1d(index, x);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribL1d");
		}
	}
}

void glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y) {

	pglVertexAttribL2d(index, x, y);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribL2d");
		}
	}
}

void glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) {

	pglVertexAttribL3d(index, x, y, z);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribL3d");
		}
	}
}

void glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {

	pglVertexAttribL4d(index, x, y, z, w);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribL4d");
		}
	}
}

void glVertexAttribL1dv(GLuint index, const GLdouble *v) {

	pglVertexAttribL1dv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribL1dv");
		}
	}
}

void glVertexAttribL2dv(GLuint index, const GLdouble *v) {

	pglVertexAttribL2dv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribL2dv");
		}
	}
}

void glVertexAttribL3dv(GLuint index, const GLdouble *v) {

	pglVertexAttribL3dv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribL3dv");
		}
	}
}

void glVertexAttribL4dv(GLuint index, const GLdouble *v) {

	pglVertexAttribL4dv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribL4dv");
		}
	}
}

void glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer) {

	pglVertexAttribLPointer(index, size, type, stride, pointer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribLPointer");
		}
	}
}

void glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble *params) {

	pglGetVertexAttribLdv(index, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetVertexAttribLdv");
		}
	}
}

void glViewportArrayv(GLuint first, GLsizei count, const GLfloat *v) {

	pglViewportArrayv(first, count, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glViewportArrayv");
		}
	}
}

void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) {

	pglViewportIndexedf(index, x, y, w, h);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glViewportIndexedf");
		}
	}
}

void glViewportIndexedfv(GLuint index, const GLfloat *v) {

	pglViewportIndexedfv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glViewportIndexedfv");
		}
	}
}

void glScissorArrayv(GLuint first, GLsizei count, const GLint *v) {

	pglScissorArrayv(first, count, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glScissorArrayv");
		}
	}
}

void glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) {

	pglScissorIndexed(index, left, bottom, width, height);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glScissorIndexed");
		}
	}
}

void glScissorIndexedv(GLuint index, const GLint *v) {

	pglScissorIndexedv(index, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glScissorIndexedv");
		}
	}
}

void glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble *v) {

	pglDepthRangeArrayv(first, count, v);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDepthRangeArrayv");
		}
	}
}

void glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f) {

	pglDepthRangeIndexed(index, n, f);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDepthRangeIndexed");
		}
	}
}

void glGetFloati_v(GLenum target, GLuint index, GLfloat *data) {

	pglGetFloati_v(target, index, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetFloati_v");
		}
	}
}

void glGetDoublei_v(GLenum target, GLuint index, GLdouble *data) {

	pglGetDoublei_v(target, index, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetDoublei_v");
		}
	}
}

void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) {

	pglDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawArraysInstancedBaseInstance");
		}
	}
}

void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance) {

	pglDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawElementsInstancedBaseInstance");
		}
	}
}

void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance) {

	pglDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawElementsInstancedBaseVertexBaseInstance");
		}
	}
}

void glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params) {

	pglGetInternalformativ(target, internalformat, pname, bufSize, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetInternalformativ");
		}
	}
}

void glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint *params) {

	pglGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetActiveAtomicCounterBufferiv");
		}
	}
}

void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) {

	pglBindImageTexture(unit, texture, level, layered, layer, access, format);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindImageTexture");
		}
	}
}

void glMemoryBarrier(GLbitfield barriers) {

	pglMemoryBarrier(barriers);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glMemoryBarrier");
		}
	}
}

void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) {

	pglTexStorage1D(target, levels, internalformat, width);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexStorage1D");
		}
	}
}

void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) {

	pglTexStorage2D(target, levels, internalformat, width, height);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexStorage2D");
		}
	}
}

void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) {

	pglTexStorage3D(target, levels, internalformat, width, height, depth);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexStorage3D");
		}
	}
}

void glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount) {

	pglDrawTransformFeedbackInstanced(mode, id, instancecount);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawTransformFeedbackInstanced");
		}
	}
}

void glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount) {

	pglDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDrawTransformFeedbackStreamInstanced");
		}
	}
}

void glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data) {

	pglClearBufferData(target, internalformat, format, type, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClearBufferData");
		}
	}
}

void glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data) {

	pglClearBufferSubData(target, internalformat, offset, size, format, type, data);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glClearBufferSubData");
		}
	}
}

void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) {

	pglDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDispatchCompute");
		}
	}
}

void glDispatchComputeIndirect(GLintptr indirect) {

	pglDispatchComputeIndirect(indirect);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDispatchComputeIndirect");
		}
	}
}

void glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) {

	pglCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glCopyImageSubData");
		}
	}
}

void glFramebufferParameteri(GLenum target, GLenum pname, GLint param) {

	pglFramebufferParameteri(target, pname, param);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glFramebufferParameteri");
		}
	}
}

void glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params) {

	pglGetFramebufferParameteriv(target, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetFramebufferParameteriv");
		}
	}
}

void glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params) {

	pglGetInternalformati64v(target, internalformat, pname, bufSize, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetInternalformati64v");
		}
	}
}

void glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth) {

	pglInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glInvalidateTexSubImage");
		}
	}
}

void glInvalidateTexImage(GLuint texture, GLint level) {

	pglInvalidateTexImage(texture, level);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glInvalidateTexImage");
		}
	}
}

void glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length) {

	pglInvalidateBufferSubData(buffer, offset, length);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glInvalidateBufferSubData");
		}
	}
}

void glInvalidateBufferData(GLuint buffer) {

	pglInvalidateBufferData(buffer);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glInvalidateBufferData");
		}
	}
}

void glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments) {

	pglInvalidateFramebuffer(target, numAttachments, attachments);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glInvalidateFramebuffer");
		}
	}
}

void glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height) {

	pglInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glInvalidateSubFramebuffer");
		}
	}
}

void glMultiDrawArraysIndirect(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride) {

	pglMultiDrawArraysIndirect(mode, indirect, drawcount, stride);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glMultiDrawArraysIndirect");
		}
	}
}

void glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride) {

	pglMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glMultiDrawElementsIndirect");
		}
	}
}

void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint *params) {

	pglGetProgramInterfaceiv(program, programInterface, pname, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramInterfaceiv");
		}
	}
}

GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name) {

	GLuint res = pglGetProgramResourceIndex(program, programInterface, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramResourceIndex");
		}
	}
	return res;
}

void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name) {

	pglGetProgramResourceName(program, programInterface, index, bufSize, length, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramResourceName");
		}
	}
}

void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params) {

	pglGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramResourceiv");
		}
	}
}

GLint glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name) {

	GLint res = pglGetProgramResourceLocation(program, programInterface, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramResourceLocation");
		}
	}
	return res;
}

GLint glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar *name) {

	GLint res = pglGetProgramResourceLocationIndex(program, programInterface, name);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetProgramResourceLocationIndex");
		}
	}
	return res;
}

void glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) {

	pglShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glShaderStorageBlockBinding");
		}
	}
}

void glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) {

	pglTexBufferRange(target, internalformat, buffer, offset, size);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexBufferRange");
		}
	}
}

void glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {

	pglTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexStorage2DMultisample");
		}
	}
}

void glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {

	pglTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTexStorage3DMultisample");
		}
	}
}

void glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) {

	pglTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glTextureView");
		}
	}
}

void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) {

	pglBindVertexBuffer(bindingindex, buffer, offset, stride);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glBindVertexBuffer");
		}
	}
}

void glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) {

	pglVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribFormat");
		}
	}
}

void glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {

	pglVertexAttribIFormat(attribindex, size, type, relativeoffset);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribIFormat");
		}
	}
}

void glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {

	pglVertexAttribLFormat(attribindex, size, type, relativeoffset);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribLFormat");
		}
	}
}

void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex) {

	pglVertexAttribBinding(attribindex, bindingindex);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexAttribBinding");
		}
	}
}

void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor) {

	pglVertexBindingDivisor(bindingindex, divisor);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glVertexBindingDivisor");
		}
	}
}

void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled) {

	pglDebugMessageControl(source, type, severity, count, ids, enabled);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDebugMessageControl");
		}
	}
}

void glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf) {

	pglDebugMessageInsert(source, type, id, severity, length, buf);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDebugMessageInsert");
		}
	}
}

void glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam) {

	pglDebugMessageCallback(callback, userParam);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glDebugMessageCallback");
		}
	}
}

GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog) {

	GLuint res = pglGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetDebugMessageLog");
		}
	}
	return res;
}

void glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar *message) {

	pglPushDebugGroup(source, id, length, message);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPushDebugGroup");
		}
	}
}

void glPopDebugGroup(void) {

	pglPopDebugGroup();
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glPopDebugGroup");
		}
	}
}

void glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar *label) {

	pglObjectLabel(identifier, name, length, label);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glObjectLabel");
		}
	}
}

void glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label) {

	pglGetObjectLabel(identifier, name, bufSize, length, label);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetObjectLabel");
		}
	}
}

void glObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label) {

	pglObjectPtrLabel(ptr, length, label);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glObjectPtrLabel");
		}
	}
}

void glGetObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label) {

	pglGetObjectPtrLabel(ptr, bufSize, length, label);
	if (checkError) {
		GLenum err = pglGetError();
		if (err != GL_NO_ERROR) {
			panic(err, "glGetObjectPtrLabel");
		}
	}
}
