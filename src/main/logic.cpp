/*
 *  R : A Computer Language for Statistical Data Analysis
 *  Copyright (C) 1995, 1996  Robert Gentleman and Ross Ihaka
 *  Copyright (C) 1999--2014  The R Core Team.
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <Defn.h>
#include <Internal.h>

#include "CXXR/BinaryFunction.hpp"
#include "CXXR/GCStackRoot.hpp"
#include "CXXR/RawVector.h"
#include "CXXR/UnaryFunction.hpp"

using namespace CXXR;
using namespace VectorOps;

// Functionality to support do_logic() :
namespace {

    LogicalVector* binaryLogic(int opcode, const LogicalVector* l,
			       const LogicalVector* r)
    {
	switch (opcode) {
	case 1:
	    {
		return applyBinaryOperator(
		    [](Logical l, Logical r) { return l && r; },
		    GeneralBinaryAttributeCopier(),
		    l, r);
	    }
	case 2:
	    {
		return applyBinaryOperator(
		    [](Logical l, Logical r) { return l || r; },
		    GeneralBinaryAttributeCopier(),
		    l, r);
	    }
	}
	return nullptr;  // -Wall
    }

    RawVector* bitwiseBinary(int opcode, const RawVector* l, const RawVector* r)
    {
	switch (opcode) {
	case 1:
	    {
		return applyBinaryOperator(
		    [](Rbyte l, Rbyte r) -> Rbyte { return l & r; },
		    GeneralBinaryAttributeCopier(),
		    l, r);
	    }
	case 2:
	    {
		return applyBinaryOperator(
		    [](Rbyte l, Rbyte r) -> Rbyte { return l | r; },
		    GeneralBinaryAttributeCopier(),
		    l, r);
	    }
	}
	return nullptr;  // -Wall
    }

    RObject* lbinary(const BuiltInFunction* op, RObject* x, RObject* y)
    {
	/* logical binary : "&" or "|" */
	if (x && x->sexptype() == RAWSXP
	    && y && y->sexptype() == RAWSXP) {
	    // Bitwise operations:
	    RawVector* vl = static_cast<RawVector*>(x);
	    RawVector* vr = static_cast<RawVector*>(y);
	    return bitwiseBinary(op->variant(), vl, vr);
	}
	if (!isNumber(x) || !isNumber(y))
	    Rf_error(_("operations are possible only for"
		       " numeric, logical or complex types"));
	GCStackRoot<LogicalVector>
	    vl(static_cast<LogicalVector*>(coerceVector(x, LGLSXP)));
	GCStackRoot<LogicalVector>
	    vr(static_cast<LogicalVector*>(coerceVector(y, LGLSXP)));
	return binaryLogic(op->variant(), vl, vr);
    }

    RObject* lnot(RObject* arg)
    {
	if (arg && arg->sexptype() == RAWSXP) {
	    // Bit inversion:
	    return applyUnaryOperator([](Rbyte x) { return Rbyte(~x); },
				      CopyAllAttributes(),
				      SEXP_downcast<RawVector*>(arg));
	} else if (arg && arg->sexptype() == LGLSXP) {
	    // Logical negation:
	    return applyUnaryOperator(
		[](Logical x) { return !x; },
		CopyAllAttributes(),
		SEXP_downcast<LogicalVector*>(arg));
	} else if (!isNumber(arg)) {
	    if (Rf_length(arg) == 0U)  // For back-compatibility
		return LogicalVector::create(0);
	    Rf_error(_("invalid argument type"));
	} else {
	    // Logical negation:
	    GCStackRoot<LogicalVector>
		lv(static_cast<LogicalVector*>(coerceVector(arg, LGLSXP)));
	    return applyUnaryOperator(
		[](Logical x) { return !x; },
                // Note: in other cases all attributes are copied.
		CopyLayoutAttributes(),
		lv.get());
	}
    }
}  // anonymous namespace

/* & | ! */
SEXP attribute_hidden do_logic(/*const*/ CXXR::Expression* call, const CXXR::BuiltInFunction* op, CXXR::Environment* env, CXXR::RObject* const* args, int num_args, const CXXR::PairList* tags)
{
    SEXP ans;

    // It would be logical to test the arity before calling
    // DispatchGroup, but tests/primitives.R assumes otherwise.
    auto dispatched = op->InternalOpsGroupDispatch("Ops", call, env, num_args,
						   args, tags);
    if (dispatched.first)
	return dispatched.second;
    op->checkNumArgs(num_args, call);
    switch (op->variant()) {
    case 1:
    case 2:
	return lbinary(op, args[0], args[1]);
    case 3:
	return lnot(args[0]);
    default:
	error(_("internal error in do_logic"));
    }
    return nullptr;  // -Wall
}

SEXP attribute_hidden do_logic_slow(SEXP call, SEXP op, SEXP args, SEXP env)
{
    SEXP ans;

    // It would be logical to test the arity before calling
    // DispatchGroup, but tests/primitives.R assumes otherwise.
    if (DispatchGroup("Ops",call, op, args, env, &ans))
	return ans;
    checkArity(op, args);
    switch (PRIMVAL(op)) {


    case 1:
    case 2:
	return lbinary(SEXP_downcast<BuiltInFunction*>(op),
		       CAR(args), CADR(args));
    case 3:
	return lnot(CAR(args));
    default:
	error(_("internal error in do_logic"));
    }
    return nullptr;  // -Wall
}

/* && || */
SEXP attribute_hidden do_logic2(SEXP call, SEXP op, SEXP args, SEXP env)
{
/*  &&	and  ||	 */
    SEXP s1, s2;
    int x1, x2;
    int ans;

    if (length(args) != 2)
	error(_("'%s' operator requires 2 arguments"),
	      PRIMVAL(op) == 1 ? "&&" : "||");

    s1 = CAR(args);
    s2 = CADR(args);
    s1 = eval(s1, env);
    if (!isNumber(s1))
	errorcall(call, _("invalid 'x' type in 'x %s y'"),
		  PRIMVAL(op) == 1 ? "&&" : "||");
    x1 = asLogical(s1);

#define get_2nd							\
	s2 = eval(s2, env);					\
	if (!isNumber(s2))					\
	    errorcall(call, _("invalid 'y' type in 'x %s y'"),	\
		      PRIMVAL(op) == 1 ? "&&" : "||");		\
	x2 = asLogical(s2);

    switch (PRIMVAL(op)) {
    case 1: /* && */
	if (x1 == FALSE)
	    ans = FALSE;
	else {
	    get_2nd;
	    if (x1 == NA_LOGICAL)
	        ans = (x2 == NA_LOGICAL || x2) ? NA_LOGICAL : x2;
	    else /* x1 == TRUE */
		ans = x2;
	}
	break;
    case 2: /* || */
	if (x1 == TRUE)
	    ans = TRUE;
	else {
	    get_2nd;
	    if (x1 == NA_LOGICAL)
		ans = (x2 == NA_LOGICAL || !x2) ? NA_LOGICAL : x2;
	    else /* x1 == FALSE */
		ans = x2;
	}
    }
    return ScalarLogical(ans);
}


#define _OP_ALL 1
#define _OP_ANY 2

static int checkValues(int op, int na_rm, int *x, R_xlen_t n)
{
    R_xlen_t i;
    int has_na = 0;
    for (i = 0; i < n; i++) {
//	if ((i+1) % NINTERRUPT == 0) R_CheckUserInterrupt();
        if (!na_rm && x[i] == NA_LOGICAL) has_na = 1;
        else {
            if (x[i] == TRUE && op == _OP_ANY) return TRUE;
            if (x[i] == FALSE && op == _OP_ALL) return FALSE;
	}
    }
    switch (op) {
    case _OP_ANY:
        return has_na ? NA_LOGICAL : FALSE;
    case _OP_ALL:
        return has_na ? NA_LOGICAL : TRUE;
    default:
        error("bad op value for do_logic3");
    }
    return NA_LOGICAL; /* -Wall */
}

/* all, any */
SEXP attribute_hidden do_logic3(SEXP call, SEXP op, SEXP args, SEXP env)
{
    SEXP ans, s, t, call2;
    int narm, has_na = 0;
    /* initialize for behavior on empty vector
       all(logical(0)) -> TRUE
       any(logical(0)) -> FALSE
     */
    Rboolean val = PRIMVAL(op) == _OP_ALL ? TRUE : FALSE;

    PROTECT(args = fixup_NaRm(args));
    PROTECT(call2 = shallow_duplicate(call));
    SETCDR(call2, args);

    if (DispatchGroup("Summary", call2, op, args, env, &ans)) {
	UNPROTECT(2);
	return(ans);
    }

    ans = matchArgExact(R_NaRmSymbol, &args);
    narm = asLogical(ans);

    for (s = args; s != R_NilValue; s = CDR(s)) {
	t = CAR(s);
	/* Avoid memory waste from coercing empty inputs, and also
	   avoid warnings with empty lists coming from sapply */
	if(xlength(t) == 0) continue;
	/* coerceVector protects its argument so this actually works
	   just fine */
	if (TYPEOF(t) != LGLSXP) {
	    /* Coercion of integers seems reasonably safe, but for
	       other types it is more often than not an error.
	       One exception is perhaps the result of lapply, but
	       then sapply was often what was intended. */
	    if(TYPEOF(t) != INTSXP)
		warningcall(call,
			    _("coercing argument of type '%s' to logical"),
			    type2char(TYPEOF(t)));
	    t = coerceVector(t, LGLSXP);
	}
	val = CXXRCONSTRUCT(Rboolean, checkValues(PRIMVAL(op), narm, LOGICAL(t), XLENGTH(t)));
        if (val != NA_LOGICAL) {
            if ((PRIMVAL(op) == _OP_ANY && val)
                || (PRIMVAL(op) == _OP_ALL && !val)) {
                has_na = 0;
                break;
            }
        } else has_na = 1;
    }
    UNPROTECT(2);
    return has_na ? ScalarLogical(NA_LOGICAL) : ScalarLogical(val);
}
#undef _OP_ALL
#undef _OP_ANY

namespace CXXR {
    namespace VectorOps {
	void checkOperandsConformable(const VectorBase* vl, const VectorBase* vr)
	{
	    // Temporary kludge:
	    VectorBase* vlnc = const_cast<VectorBase*>(vl);
	    VectorBase* vrnc = const_cast<VectorBase*>(vr);
	    if (Rf_isArray(vlnc) && Rf_isArray(vrnc)
		&& !Rf_conformable(vlnc, vrnc))
		Rf_error(_("non-conformable arrays"));
	    if (isTs(vlnc)) {
		if (isTs(vrnc) && !Rf_tsConform(vlnc, vrnc))
		    Rf_error(_("non-conformable time-series"));
		if (vr->size() > vl->size())
		    Rf_error(_("time-series/vector length mismatch"));
	    } else if (isTs(vrnc) && vl->size() > vr->size())
		Rf_error(_("time-series/vector length mismatch"));
	}
    } // namespace VectorOps
} // namespace CXXR  
