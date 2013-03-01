/*CXXR $Id$
 *CXXR
 *CXXR This file is part of CXXR, a project to refactor the R interpreter
 *CXXR into C++.  It may consist in whole or in part of program code and
 *CXXR documentation taken from the R project itself, incorporated into
 *CXXR CXXR (and possibly MODIFIED) under the terms of the GNU General Public
 *CXXR Licence.
 *CXXR 
 *CXXR CXXR is Copyright (C) 2008-13 Andrew R. Runnalls, subject to such other
 *CXXR copyrights and copyright restrictions as may be stated below.
 *CXXR 
 *CXXR CXXR is not part of the R project, and bugs and other issues should
 *CXXR not be reported via r-bugs or other R project channels; instead refer
 *CXXR to the CXXR website.
 *CXXR */

/*
  R : A Computer Language for Statistical Data Analysis
  Copyright (C) 1995-1996   Robert Gentleman and Ross Ihaka
  Copyright (C) 1997-2012   The R Core Team

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at
  your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, a copy is available at
  http://www.r-project.org/Licenses/
*/

/*
  See ../unix/system.txt for a description of some of these functions
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Defn.h"
#include "Fileio.h" /* for R_fopen */
#include "Startup.h"

/* These are used in ../gnuwin32/system.c, ../unix/sys-std.c */
SA_TYPE SaveAction = SA_SAVEASK;
SA_TYPE	RestoreAction = SA_RESTORE;
static Rboolean LoadSiteFile = TRUE;
attribute_hidden Rboolean LoadInitFile = TRUE;  /* Used in R_OpenInitFile */
static Rboolean DebugInitFile = FALSE;

/*
 *  INITIALIZATION AND TERMINATION ACTIONS
 */

void attribute_hidden R_InitialData(void)
{
    R_RestoreGlobalEnv();
}


attribute_hidden
FILE *R_OpenLibraryFile(const char *file)
{
    char buf[PATH_MAX];
    FILE *fp;

    snprintf(buf, PATH_MAX, "%s/library/base/R/%s", R_Home, file);
    fp = R_fopen(buf, "r");
    return fp;
}

attribute_hidden
char *R_LibraryFileName(const char *file, char *buf, size_t bsize)
{
    if (snprintf(buf, bsize, "%s/library/base/R/%s", R_Home, file) < 0)
	error(_("R_LibraryFileName: buffer too small"));
    return buf;
}

attribute_hidden
FILE *R_OpenSysInitFile(void)
{
    char buf[PATH_MAX];
    FILE *fp;

    snprintf(buf, PATH_MAX, "%s/library/base/R/Rprofile", R_Home);
    fp = R_fopen(buf, "r");
    return fp;
}

attribute_hidden
FILE *R_OpenSiteFile(void)
{
    char buf[PATH_MAX];
    FILE *fp;

    fp = NULL;
    if (LoadSiteFile) {
	char *p = getenv("R_PROFILE");
	if (p) {
	    if (*p) return R_fopen(R_ExpandFileName(p), "r");
	    else return NULL;
	}
#ifdef R_ARCH
	snprintf(buf, PATH_MAX, "%s/etc/%s/Rprofile.site", R_Home, R_ARCH);
	if ((fp = R_fopen(buf, "r"))) return fp;
#endif
	snprintf(buf, PATH_MAX, "%s/etc/Rprofile.site", R_Home);
	if ((fp = R_fopen(buf, "r"))) return fp;
    }
    return fp;
}

	/* Saving and Restoring the Global Environment */

#ifndef Win32
static char workspace_name[1000] = ".RData";

/*
  set_workspace_name is in src/gnuwin32/system.c and used to implement
  drag-and-drop on Windows.
 */
#else
static char workspace_name[PATH_MAX] = ".RData";

void set_workspace_name(const char *fn)
{
    strncpy(workspace_name, fn, PATH_MAX);
}
#endif

const char* get_workspace_name()
{
    return workspace_name;
}

void R_RestoreGlobalEnv(void)
{
    if(RestoreAction == SA_RESTORE) {
	R_RestoreGlobalEnvFromFile(workspace_name, R_Quiet);
    }
}

void R_SaveGlobalEnv(void)
{
    R_SaveGlobalEnvToFile(".RData");
}


/*
 *  INITIALIZATION HELPER CODE
 */

void R_DefParams(Rstart Rp)
{
    Rp->R_Quiet = FALSE;
    Rp->R_Slave = FALSE;
    Rp->R_Interactive = TRUE;
    Rp->R_Verbose = FALSE;
    Rp->RestoreAction = SA_RESTORE;
    Rp->SaveAction = SA_SAVEASK;
    Rp->LoadSiteFile = TRUE;
    Rp->LoadInitFile = TRUE;
    Rp->DebugInitFile = FALSE;
    Rp->vsize = R_VSIZE;
    Rp->max_vsize = R_SIZE_T_MAX;
    Rp->ppsize = R_PPSSIZE;
    Rp->NoRenviron = FALSE;
}

#define Max_Nsize 50000000	/* about 1.4Gb 32-bit, 2.8Gb 64-bit */
#define Max_Vsize R_SIZE_T_MAX	/* unlimited */

#define Min_Nsize 220000
#define Min_Vsize (1*Mega)

void R_SizeFromEnv(Rstart Rp)
{
    int ierr;
    R_size_t value;
    char *p;

    if((p = getenv("R_VSIZE"))) {
	value = R_Decode2Long(p, &ierr);
	if(ierr != 0 || value > Max_Vsize || value < Min_Vsize)
	    R_ShowMessage("WARNING: invalid R_VSIZE ignored\n");
	else
	    Rp->vsize = value;
    }
}

static void SetSize(R_size_t vsize)
{
    char msg[1024];

    /* vsize >0 to catch long->int overflow */
    if (vsize < 1000 && vsize > 0) {
	R_ShowMessage("WARNING: vsize ridiculously low, Megabytes assumed\n");
	vsize *= CXXRCONSTRUCT(R_size_t, Mega);
    }
    if(vsize < Min_Vsize || vsize > Max_Vsize) {
	sprintf(msg, "WARNING: invalid v(ector heap)size `%lu' ignored\n"
		 "using default = %gM\n", static_cast<unsigned long>( vsize),
		R_VSIZE / Mega);
	R_ShowMessage(msg);
	R_VSize = R_VSIZE;
    } else
	R_VSize = vsize;
}


void R_SetParams(Rstart Rp)
{
    R_Quiet = Rp->R_Quiet;
    R_Slave = Rp->R_Slave;
    R_Interactive = Rp->R_Interactive;
    R_Verbose = Rp->R_Verbose;
    RestoreAction = Rp->RestoreAction;
    SaveAction = Rp->SaveAction;
    LoadSiteFile = Rp->LoadSiteFile;
    LoadInitFile = Rp->LoadInitFile;
    DebugInitFile = Rp->DebugInitFile;
    SetSize(Rp->vsize);
#ifdef Win32
    R_SetWin32(Rp);
#endif
}
