/// ***************************************************************************
/// Copyright (c) 2009, Industrial Logic, Inc., All Rights Reserved.
///
/// This code is the exclusive property of Industrial Logic, Inc. It may ONLY be
/// used by students during Industrial Logic's workshops or by individuals
/// who are being coached by Industrial Logic on a project.
///
/// This code may NOT be copied or used for any other purpose without the prior
/// written consent of Industrial Logic, Inc.
/// ****************************************************************************

/*
 * @(#) dirent.h 2.0 17 Jun 91   Public Domain.
 *
 *  A public domain implementation of BSD directory routines for
 *  MS-DOS.  Written by Michael Rendell ({uunet,utai}michael@garfield),
 *  August 1987
 *
 *  Enhanced and ported to OS/2 by Kai Uwe Rommel; added scandir() prototype
 *  December 1989, February 1990
 *  Change of MAXPATHLEN for HPFS, October 1990
 *
 *  Unenhanced and ported to Windows NT by Bill Gallagher
 *  17 Jun 91
 *  changed d_name to char * instead of array, removed non-std extensions
 *
 *  Cleanup, other hackery, Summer '92, Brian Moran , brianmo@microsoft.com
 */

#if defined(_WIN32) && !defined(__MINGW32__)

#ifndef WIN32_DIRENT
#define WIN32_DIRENT

#include <direct.h>

struct dirent
{
	ino_t d_ino; /* a bit of a farce */
	long d_reclen; /* more farce */
	long d_namlen; /* length of d_name */
	char *d_name;
};

struct _dircontents
{
	char *_d_entry;
	struct _dircontents *_d_next;
};

typedef struct _dirdesc
{
	int dd_id; /* uniquely identify each open directory*/
	long dd_loc; /* where we are in directory entry */
	struct _dircontents *dd_contents; /* pointer to contents of dir */
	struct _dircontents *dd_cp; /* pointer to current position */
}
DIR;

#ifdef __cplusplus
	extern "C" {
#endif

extern DIR *opendir(const char *);
extern struct dirent *readdir(DIR *);
extern void seekdir(DIR *, long);
extern long telldir(DIR *);
extern void closedir(DIR *);
#define rewinddir(dirp) seekdir(dirp, 0L)

#ifdef __cplusplus
	}  // extern "C"
#endif

#endif /* _DIRENT */

#endif /* defined(_WIN32) && !defined(__MINGW32__) */
