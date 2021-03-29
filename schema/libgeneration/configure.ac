AC_INIT(librandgeneration, 0.0.1, Y.L.Rusinov@rubin-spb.ru)

AC_CONFIG_SRCDIR(src/rand.cpp)
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([include/config.h])
AM_INIT_AUTOMAKE([foreign dist-bzip2])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([m],[cos])
AC_CHECK_LIB([gslcblas],[cblas_dgemm])
AC_CHECK_LIB([gsl],[gsl_blas_dgemm])
PKG_CHECK_MODULES([gsl], [gsl], [HAVE_GSL=yes], [HAVE_GSL=no])

PKG_CHECK_MODULES([libpq], [libpq >= 9.6], [HAVE_PG=yes], [HAVE_PG=no])
if test "${HAVE_PG}" = "yes" ; then
    LIBS="`pkg-config --libs libpq` $LIBS"
    PG_LIB="`pkg-config --libs libpq`"
    PG_INC="`pkg-config --cflags --libs libpq`"
    PG_INC_SERVER="-I`pg_config --includedir-server`"
fi
AC_SUBST(PG_INC,$PG_INC)
AC_SUBST(PG_INC_SERVER, $PG_INC_SERVER)
AC_SUBST(PG_LIB,$PG_LIB)

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h malloc.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_STAT
AC_CHECK_FUNCS([mkdir pow sqrt strerror])

AC_CONFIG_FILES([
         Makefile

         src/Makefile
         include/Makefile
])    

AC_OUTPUT
