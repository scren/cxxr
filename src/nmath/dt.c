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
 *  AUTHOR
 *    Catherine Loader, catherine@research.bell-labs.com.
 *    October 23, 2000.
 *
 *  Merge in to R:
 *	Copyright (C) 2000, The R Core Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, a copy is available at
 *  http://www.r-project.org/Licenses/
 *
 *
 * DESCRIPTION
 *
 *    The t density is evaluated as
 *         sqrt(n/2) / ((n+1)/2) * Gamma((n+3)/2) / Gamma((n+2)/2).
 *             * (1+x^2/n)^(-n/2)
 *             / sqrt( 2 pi (1+x^2/n) )
 *
 *    This form leads to a stable computation for all
 *    values of n, including n -> 0 and n -> infinity.
 */

#include "nmath.h"
#include "dpq.h"

double dt(double x, double n, int give_log)
{
    double t, u;
#ifdef IEEE_754
    if (ISNAN(x) || ISNAN(n))
	return x + n;
#endif

    if (n <= 0) ML_ERR_return_NAN;
    if(!R_FINITE(x))
	return R_D__0;
    if(!R_FINITE(n))
	return dnorm(x, 0., 1., give_log);

    t = -bd0(n/2.,(n+1)/2.) + stirlerr((n+1)/2.) - stirlerr(n/2.);
    if ( x*x > 0.2*n )
	u = log( 1+ x*x/n ) * n/2;
    else
	u = -bd0(n/2.,(n+x*x)/2.) + x*x/2.;

    return R_D_fexp(M_2PI*(1+x*x/n), t-u);
}
