/*
 *  R : A Computer Language for Statistical Data Analysis
 *  Copyright (C) 2008-2014  Andrew R. Runnalls.
 *  Copyright (C) 2014 and onwards the CXXR Project Authors.
 *
 *  CXXR is not part of the R project, and bugs and other issues should
 *  not be reported via r-bugs or other R project channels; instead refer
 *  to the CXXR website.
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
 */

/** @file DotInternal.cpp
 *
 * @brief Table of functions invoked \e via <tt>.Internal()</tt>.
 */

#include "CXXR/DotInternal.h"

#include "Internal.h"

#include "CXXR/BuiltInFunction.h"
#include "CXXR/Expression.h"
#include "CXXR/errors.h"

using namespace std;
using namespace CXXR;

namespace CXXR {
    namespace ForceNonInline {
	SEXP (*INTERNALp)(SEXP x) = INTERNAL;
    }
}

// ***** C interface *****

// void SET_INTERNAL(SEXP x, SEXP v)
// {
//     const Symbol* sym = SEXP_downcast<Symbol*>(x);
//     BuiltInFunction* fun = SEXP_downcast<BuiltInFunction*>(v);
//     DotInternalTable::set(sym, fun);
// }

SEXP do_internal(SEXP call, SEXP op, SEXP args, SEXP env)
{
    Expression* callx = SEXP_downcast<Expression*>(call);
    BuiltInFunction* opfun = SEXP_downcast<BuiltInFunction*>(op);
    PairList* argspl = SEXP_downcast<PairList*>(args);
    Environment* envir = SEXP_downcast<Environment*>(env);
    opfun->checkNumArgs(argspl, callx);
    Expression* innercall = dynamic_cast<Expression*>(argspl->car());
    if (!innercall)
	Rf_errorcall(call, _("invalid .Internal() argument"));
    Symbol* funsym = dynamic_cast<Symbol*>(innercall->car());
    if (!funsym)
	Rf_errorcall(call, _("invalid .Internal() argument"));
    BuiltInFunction* func = BuiltInFunction::obtainInternal(funsym);
    if (!func)
	Rf_errorcall(call, _("there is no .Internal function \"%s\""),
		     funsym->name()->c_str());
    ArgList al(innercall->tail(), ArgList::RAW);
    return func->apply(&al, envir, innercall);
}
