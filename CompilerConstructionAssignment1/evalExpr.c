//
//  evalExpr.c
//  CompilerConstructionAssignment1
//
//  Created by Yusuke Iwama on 12/24/13.
//  Copyright (c) 2013 University of Tsukuba. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "exprParser.h"

int evalExpr(AST *e)
{
    switch(e->op){
		case NUM:
			return e->val;
		case PLUS_OP:
			return evalExpr(e->left) + evalExpr(e->right);
		case MINUS_OP:
			return evalExpr(e->left) - evalExpr(e->right);
		case TIMES_OP:
			return evalExpr(e->left) * evalExpr(e->right);
		case OVER_OP:
			return evalExpr(e->left) / evalExpr(e->right);
		default:
			fprintf(stderr,"evalExpr: bad expression\n");
			exit(1);
    }
}
