/**
 * \file system.h
 *
 *  Some misc low-level API
 */

//#define fsync64 fsync

#define VERSION "12.34.56"
#define RPMCONFIGDIR "/usr/lib/rpm"

#define PACKAGE "rpm"
//AM_CPPFLAGS += -DLIBRPMALIAS_FILENAME="\"rpmpopt-${VERSION}\""
#define LIBRPMALIAS_FILENAME "rpmpopt-4.15.90"
//AM_CPPFLAGS += -DLIBRPMALIAS_EXECPATH="\"$(bindir)\""
#define LIBRPMALIAS_EXECPATH "/usr/bin"

#define UID_0_USER "root"
#define GID_0_GROUP "root"
#define SYSCONFDIR "/etc"
#define RPMCANONVENDOR "redhat"
#define LOCALSTATEDIR "/var/lib"
#define PACKAGE_BUGREPORT "https://bugzilla.example.com"

#define HAVE_EVP_MD_CTX_NEW
#define HAVE_RSA_SET0_KEY
#define HAVE_DSA_SET0_KEY
#define HAVE_DSA_SET0_PQG
#define HAVE_DSA_SIG_SET0
#define HAVE_BN2BINPAD

#define WITH_POSIX 1
#define __USE_GNU
//#define __USE_MISC
#undef __USE_FILE_OFFSET64
#define __USE_LARGEFILE64 1
//#define STATFS_IN_SYS_STATVFS 1
//#define STATFS_IN_SYS_VFS 1
#define STATFS_IN_SYS_STATFS 1
#define MAJOR_IN_SYSMACROS 1
#define WITH_CAP 0
#define WITH_ACL 0
#define HAVE_SYS_UTSNAME_H 1
#define HAVE_UNISTD_H 1
#define HAVE_LIMITS_H 1
#define HAVE_STPCPY 1
#define HAVE___PROGNAME 1
#undef WITH_IMAEVM

//#define HAVE_CONFIG_H 1
#define HAVE_SYS_PARAM_H 1
#define HAVE_STPCPY 1
#define HAVE_STPNCPY 0
#define HAVE_FCNTL_H 1
#define HAVE_DIRENT_H 1
#define HAVE_SYS_NDIR_H 1
#define HAVE_SYS_DIR_H 1
#define HAVE_NDIR_H 1
#define HAVE_MEMPCPY 1
//#if defined(HAVE_FDATASYNC) && !HAVE_DECL_FDATASYNC
//#if defined(HAVE_SETPROGNAME) /* BSD'ish systems */
//#elif defined(HAVE___PROGNAME) /* glibc and others */

#ifndef	H_SYSTEM
#define	H_SYSTEM

#define stat64 stat
extern char ** environ;

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif

/* <unistd.h> should be included before any preprocessor test
   of _POSIX_VERSION.  */
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#if !defined(__GLIBC__)
#ifdef __APPLE__
#include <crt_externs.h>
#define environ (*_NSGetEnviron())
#else
extern char ** environ;
#endif /* __APPLE__ */
#endif
#endif

#if !defined(HAVE_STPCPY)
char * stpcpy(char * dest, const char * src);
#endif

#if !defined(HAVE_STPNCPY)
char * stpncpy(char * dest, const char * src, size_t n);
#endif

#if HAVE_SECURE_GETENV
#define	getenv(_s)	secure_getenv(_s)
#elif HAVE___SECURE_GETENV
#define	getenv(_s)	__secure_getenv(_s)
#endif

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#else
#include <sys/file.h>
#endif

#ifdef HAVE_DIRENT_H
# include <dirent.h>
# define NLENGTH(direct) (strlen((direct)->d_name))
#else /* not HAVE_DIRENT_H */
# define dirent direct
# define NLENGTH(direct) ((direct)->d_namlen)
# ifdef HAVE_SYS_NDIR_H
#  include <sys/ndir.h>
# endif /* HAVE_SYS_NDIR_H */
# ifdef HAVE_SYS_DIR_H
#  include <sys/dir.h>
# endif /* HAVE_SYS_DIR_H */
# ifdef HAVE_NDIR_H
#  include <ndir.h>
# endif /* HAVE_NDIR_H */
#endif /* HAVE_DIRENT_H */

#if HAVE_LIMITS_H
#include <limits.h>
#endif

#ifndef PATH_MAX
#ifdef _POSIX_PATH_MAX
#define PATH_MAX _POSIX_PATH_MAX
#elif defined MAXPATHLEN
#define PATH_MAX MAXPATHLEN
#else
#define PATH_MAX 256
#endif
#endif

#if defined(HAVE_FDATASYNC) && !HAVE_DECL_FDATASYNC
extern int fdatasync(int fildes);
#endif

#include "rpmio/rpmutil.h"
/* compatibility macros to avoid a mass-renaming all over the codebase */
#define xmalloc(_size) rmalloc((_size))
#define xcalloc(_nmemb, _size) rcalloc((_nmemb), (_size))
#define xrealloc(_ptr, _size) rrealloc((_ptr), (_size))
#define xstrdup(_str) rstrdup((_str))
#define _free(_ptr) rfree((_ptr))

/* To extract program's name: use calls (reimplemented or shipped with system):
   - void setprogname(const char *pn)
   - const char *getprogname(void)

   setprogname(*pn) must be the first call in main() in order to set the name
   as soon as possible. */
#if defined(HAVE_SETPROGNAME) /* BSD'ish systems */
# include <stdlib.h> /* Make sure this header is included */
# define xsetprogname(pn) setprogname(pn)
# define xgetprogname(pn) getprogname(pn)
#elif defined(HAVE___PROGNAME) /* glibc and others */
# define xsetprogname(pn)
  extern const char *__progname;
# define xgetprogname(pn) __progname
#else
# error "Did not find any sutable implementation of xsetprogname/xgetprogname"
#endif

/* Take care of NLS matters.  */
#if ENABLE_NLS
# include <locale.h>
# include <libintl.h>
# define _(Text) dgettext (PACKAGE, Text)
#else
# define _(Text) Text
#endif

#define N_(Text) Text

/* ============== from misc/miscfn.h */

#include "misc/fnmatch.h"

#endif	/* H_SYSTEM */
