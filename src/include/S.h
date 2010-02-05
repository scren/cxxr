/*CXXR $Id$
 *CXXR
 *CXXR This file is part of CXXR, a project to refactor the R interpreter
 *CXXR into C++.  It may consist in whole or in part of program code and
 *CXXR documentation taken from the R project itself, incorporated into
 *CXXR CXXR (and possibly MODIFIED) under the terms of the GNU General Public
 *CXXR Licence.
 *CXXR 
 *CXXR CXXR is Copyright (C) 2008-10 Andrew R. Runnalls, subject to such other
 *CXXR copyrights and copyright restrictions as may be stated below.
 *CXXR 
 *CXXR CXXR is not part of the R project, and bugs and other issues should
 *CXXR not be reported via r-bugs or other R project channels; instead refer
 *CXXR to the CXXR website.
 *CXXR */

/*
 *  R : A Computer Language for Statistical Data Analysis
 *  Copyright (C) 1995, 1996  Robert Gentleman and Ross Ihaka
 *  Copyright (C) 1997--2003 The R Development Core Team.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, a copy is available at
 *  http://www.r-project.org/Licenses/
 *
 *  Much of this is from Doug Bates.
 */

#ifndef R_S_H
#define R_S_H

#ifndef USING_R
# define USING_R
/* is this a good idea? - conflicts with many versions of f2c.h */
# define longint int
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
# include <math.h>

#include <Rconfig.h>
#include <R_ext/Constants.h>
#include <R_ext/Memory.h>	/* S_alloc */

/* subset of those in Random.h */
extern void seed_in(long *);
extern void seed_out(long *);
extern double unif_rand(void);
extern double norm_rand(void);

/* Macros for S/R Compatibility */

#include <R_ext/RS.h>
/* for PROBLEM ... Calloc, Realloc, Free, Memcpy, F77_xxxx */

/* S4 uses macros equivalent to */
#define Salloc(n,t) (t*)S_alloc(n, sizeof(t))
#define Srealloc(p,n,old,t) (t*)S_realloc(p,n,old,sizeof(t))

/* S's complex is different, and is a define to S_complex now */
typedef struct {
	double re;
	double im;
} S_complex;

#ifdef S_OLD_COMPLEX
# define complex S_complex
#endif

/* Not quite full compatibility: beware! */
/* void	call_R(char*, long, void**, char**, long*, char**, long, char**);*/
#define call_S call_R


#ifdef __cplusplus
}
#endif

#endif /* !R_S_H */
