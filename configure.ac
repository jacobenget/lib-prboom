dnl Process this file with autoconf to produce a configure script.
AC_INIT([prboom],[2.5.0])
AC_CONFIG_AUX_DIR(autotools)
AC_CONFIG_MACRO_DIR(autotools)

dnl --- Check for target system type - before initialising Automake
AC_CANONICAL_TARGET

dnl --- Fire up automake
AM_INIT_AUTOMAKE([check-news foreign -Woverride -Wobsolete -Wportability -Wsyntax -Wunsupported subdir-objects])
AM_CONFIG_HEADER(config.h)

AC_MSG_CHECKING([checking whether to use x86 asm versions of some functions])
AC_ARG_ENABLE(i386-asm,AC_HELP_STRING([--disable-i386-asm],[Do not use i386 assembly]),,[
enable_i386_asm="no"
case "$target" in
        i?86-*) enable_i386_asm="yes" ;;
esac])
if test "$enable_i386_asm" = yes; then
    AC_DEFINE(I386_ASM,1,[Define on targets supporting 386 assembly])
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi

AC_ARG_WITH(waddir,AC_HELP_STRING([--with-waddir],[Path to install prboom.wad and look for other WAD files]),
DOOMWADDIR="$withval",
if test "x$prefix" != xNONE; then
  DOOMWADDIR="$prefix/share/games/doom"
else
  DOOMWADDIR="$ac_default_prefix/share/games/doom"
fi
)
AC_DEFINE_UNQUOTED(DOOMWADDIR,"$DOOMWADDIR",[Define to be the path where Doom WADs are stored])

dnl --- Check for programs
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LN_S
LT_INIT

if test "x$GCC" = "xyes"; then
  AC_DEFINE(PACKEDATTR,[__attribute__((packed))],[Set to the attribute to apply to struct definitions to make them packed])
else
  AC_DEFINE(PACKEDATTR,[])
  echo "-!- Your compiler is not gcc. We probably don't know how to force"
  echo '    structures to be packed with your compiler. You may have to edit'
  echo '    the source to insert the relevant pragmas so structures are packed.'
fi

dnl --- cph: work out flags to pass to compiler
CFLAGS_OPT="-O2 -fomit-frame-pointer"
AC_C_COMPILE_FLAGS(-Wall)
dnl --- Option to enable debugging
AC_ARG_ENABLE(debug,AC_HELP_STRING([--enable-debug],[turns on various debugging features, like range checking and internal heap diagnostics]),,enable_debug="no")
if test "$enable_debug" = "no"
then
    AC_C_COMPILE_FLAGS(-Wno-unused -Wno-switch)
else
    CFLAGS_OPT="-g"
    AC_C_COMPILE_FLAGS(-Wmissing-noreturn -Wredundant-decls -Wnested-externs -Wold-style-definition -Wmissing-declarations -Wmissing-format-attribute -Wvariadic-macros -Wdisabled-optimization -Wlarger-than-128000 -Waggregate-return -Wvolatile-register-var)
    AC_DEFINE(RANGECHECK,1,[Define to enable internal range checking])
    AC_DEFINE(INSTRUMENTED,1,[Define this to see real-time memory allocation statistics, and enable extra debugging features])
    AC_DEFINE(TIMEDIAG,1,[Defining this causes time stamps to be created each time a lump is locked, and lumps locked for long periods of time are reported])
fi
AC_ARG_ENABLE(profile,AC_HELP_STRING([--enable-profile],[turns on profiling]),,enable_profile="no")
if test "$enable_profile" = "yes"
then
    CFLAGS_OPT="-pg"
fi
AM_WITH_DMALLOC

dnl --- Try for processor optimisations
AC_CPU_OPTIMISATIONS

dnl --- some defaults for CFLAGS
AC_C_COMPILE_FLAGS(-Wextra -Wno-missing-field-initializers -Winline -Wwrite-strings -Wundef -Wbad-function-cast -Wcast-align -Wcast-qual -Wdeclaration-after-statement -ffast-math $CFLAGS_OPT)
dnl -Wmissing-prototypes -Wmissing-declarations
CFLAGS="$CFLAGS -I\$(top_srcdir)/src"

dnl --- Compiler characteristics
AC_C_CONST
AC_C_INLINE
if test "$cross_compiling" != "yes"; then
        AC_C_BIGENDIAN
fi

dnl --- Header files, typedefs, structures
AC_TYPE_UID_T
AC_TYPE_SIZE_T
AC_DECL_SYS_SIGLIST
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS(unistd.h asm/byteorder.h sched.h)

dnl --- Library functions
AC_CHECK_FUNC(stricmp,,AC_DEFINE(stricmp,strcasecmp,[Define to strcasecmp, if we have it]))
AC_CHECK_FUNC(strnicmp,,AC_DEFINE(strnicmp,strncasecmp,[Define to strncasecmp, if we have it]))
AC_CHECK_FUNC(min,AC_DEFINE(MIN,min,[If your platform has a fast version of min, define MIN to it]),)
AC_CHECK_FUNC(max,AC_DEFINE(MAX,max,[If your platform has a fast version of max, define MAX to it]),)
AC_CHECK_FUNCS(getopt inet_aton inet_pton inet_ntop snprintf vsnprintf mmap usleep sched_setaffinity)

dnl --- Check for libraries
dnl --- cph: we need pow(3) in SDL/i_sound.c; on some systems it gets pulled
dnl ---  in by other libraries, but we can't rely on that.
AC_CHECK_LIB(m,pow)
dnl - system specific stuff
case "$target" in
    *-*-cygwin* | *-*-mingw32*)
        SYS_GL_LIBS="-lopengl32"
        ;;
    *-*-beos*)
        SYS_GL_LIBS="-lGL -lGLU"
        ;;
    *-*-aix*)
        if test x$ac_cv_prog_gcc = xyes; then
            CFLAGS="$CFLAGS -mthreads"
        fi
        ;;
    *)
	SYS_GL_LIBS="-lGL -lGLU"
	;;
esac

dnl - GL
AC_ARG_ENABLE(gl,AC_HELP_STRING([--disable-gl],[disable OpenGL rendering code]),,enable_gl="yes")
if test "$enable_gl" = "yes"
then
    AC_MSG_CHECKING(for OpenGL support)
    have_opengl=no
    AC_TRY_COMPILE([
     #include <GL/gl.h>
    ],[
    ],[
    have_opengl=yes
    ])
    AC_MSG_RESULT($have_opengl)
    if test x$have_opengl = xyes; then
        AC_DEFINE(GL_DOOM,1,[Define if you are building with OpenGL support])
        AC_DEFINE(USE_GLU_IMAGESCALE,1,[Define if you want to use gluImageScale])
        AC_DEFINE(USE_GLU_MIPMAP,1,[Define if you want to use gluBuild2DMipmaps])
        GL_LIBS="$SYS_GL_LIBS"
    else
        AC_MSG_ERROR([You must have the relevant OpenGL development libraries & headers installed to compile with OpenGL support])
    fi
fi
AM_CONDITIONAL(BUILD_GL,test "$enable_gl" = "yes")

dnl - SDL
AM_PATH_SDL(1.1.3, sdl_main="yes")
if test "$sdl_main" != "yes"
then
 AC_MSG_ERROR([*** You must have the SDL libraries installed before you can compile prboom
 *** See http://prboom.sourceforge.net/linux.html
 ])
fi

savelibs="$LIBS"
LIBS="$LIBS $SDL_LIBS"
AC_CHECK_FUNCS(SDL_JoystickGetAxis)
LIBS="$savelibs"
AC_ARG_WITH([mixer],
  AC_HELP_STRING([--without-mixer],[Do not use SDL_mixer even if available]),
  [], AC_CHECK_LIB(SDL_mixer,Mix_OpenAudio,[],[],[$SDL_LIBS $MIXER_LIBS]))

AC_ARG_WITH(net,
  AS_HELP_STRING([--without-net],[Do not use SDL_net even if available]),
  [
    dnl -- Networking was disabled by the user.
    NET_LIBS=
  ],[
    dnl -- Check for networking support
    AC_CHECK_LIB(SDL_net,SDLNet_UDP_Bind,[
      AC_DEFINE(HAVE_NET,1,[Define if you want network game support])
      AC_DEFINE(HAVE_LIBSDL_NET,1,
        [Define if you have the SDL net library -lSDL_net])
      AC_DEFINE(USE_SDL_NET,1,[Define if you want to use the SDL net lib])
      NET_LIBS=-lSDL_net
      sdl_net=yes
      save_CFLAGS="$CFLAGS"
      CFLAGS="$CFLAGS $SDL_CFLAGS"
      AC_TRY_COMPILE([
          #include "SDL_net.h"
          ],[
          UDPpacket *p;
          int n = sizeof(p->src);
          ],
          AC_DEFINE(SDL_NET_UDP_PACKET_SRC,1,[Define if you have an old SDL_net, such that the UDPpacket structure has a src member instead of an address member]))
      CFLAGS="$save_CFLAGS"
    ],[
      dnl -- Warn if networking support was not disabled but sdlnet is missing
      AC_MSG_WARN([*** SDL networking library not found. The game will not be compiled with network game support.])
    ],$SDL_LIBS)
  ])

dnl - Turn all warnings into errors (this needs to be done AFTER the above check for SDL which uses $CFLAGS, probably because the AC_TRY_COMPILE there produces a warning)
AC_C_COMPILE_FLAGS(-Werror)

dnl - Other libs
AC_CHECK_LIB(png,png_create_info_struct)
AC_EGREP_HEADER(sockaddr_in6,netinet/in.h,AC_DEFINE(HAVE_IPv6,1,[Define if you have struct sockaddr_in6]))

dnl --- Options
dnl - Always use highres mode and basic checks - anyone that wants these off can edit the config.h
AC_DEFINE(HIGHRES,1,[Define for high resolution support])
AC_DEFINE(SIMPLECHECKS,1,[When defined this causes quick checks which only impose significant overhead if a posible error is detected.])
AC_DEFINE(ZONEIDCHECK,1,[Define this to perform id checks on zone blocks, to detect corrupted and illegally freed blocks])

AC_ARG_ENABLE(dogs,AC_HELP_STRING([--disable-dogs],[disables support for helper dogs]),,enable_dogs="yes")
if test x"$enable_dogs" = xyes
then
	AC_DEFINE(DOGS,1,[Define for support for MBF helper dogs])
fi

AC_ARG_ENABLE(heapcheck,AC_HELP_STRING([--enable-heapcheck],[turns on continuous heap checking (very slow)]),,enable_heapcheck="no")
AC_ARG_ENABLE(heapdump,AC_HELP_STRING([--enable-heapdump],[turns on dumping the heap state for debugging]),,enable_heapdump="no")
if test "$enable_heapcheck" = "yes"
then
    AC_DEFINE(CHECKHEAP,1,[Uncomment this to exhaustively run memory checks while the game is running (this is EXTREMELY slow).])
fi
if test "$enable_heapdump" = "yes"
then
    AC_DEFINE(HEAPDUMP,1,[Uncomment this to cause heap dumps to be generated. Only useful if INSTRUMENTED is also defined.])
fi

AM_CONDITIONAL(WAD_MMAP,test "$ac_cv_func_mmap" = yes)
AC_SUBST(MIXER_CFLAGS)
AC_SUBST(MIXER_LIBS)
AC_SUBST(NET_CFLAGS)
AC_SUBST(NET_LIBS)
AC_SUBST(MATH_LIB)
AC_SUBST(GL_LIBS)
AC_SUBST(CFLAGS)
AC_SUBST(DOOMWADDIR)

dnl --- Require Python 3.8 for some related script usage during development.
dnl --- Version 3.8 was only choosen because it was the version that I (Jake) locally had installed by default,
dnl --- and there may be an earlier version of Python that also satisfies the need but I'm not doing the work of figuring that out,
dnl --- since I do not expect the autotools portion of this project to live on long enough for this detail to matter.
AM_PATH_PYTHON([3.8])

dnl --- output
AC_OUTPUT(Makefile src/Makefile src/POSIX/Makefile src/SDL/Makefile src/MAC/Makefile doc/Makefile data/Makefile ICONS/Makefile VisualC6/Makefile VisualC8/Makefile tests/Makefile prboom.spec)
