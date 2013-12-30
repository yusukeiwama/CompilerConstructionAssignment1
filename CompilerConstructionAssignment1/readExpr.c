//
//  readExpr.c
//  CompilerConstructionAssignment1
//
//  Created by Yusuke Iwama on 12/24/13.
//  Copyright (c) 2013 University of Tsukuba. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "exprParser.h"

AST *readNum(void);

AST *readExpr()
{
//    int t;
    AST *e, *ee;
	
    e = readNum();
	
    while (currentToken == PLUS_OP
		   || currentToken == MINUS_OP
		   || currentToken == TIMES_OP
		   || currentToken == OVER_OP) {
		
		ee = (AST *)malloc(sizeof(AST)); // look-ahead
		ee->op = currentToken;
		
		switch (ee->op) {
			case PLUS_OP:
			case MINUS_OP:
				getToken();
				ee->left = e;
				ee->right = readNum();
				e = ee;
				break;
			case TIMES_OP:
			case OVER_OP:
				getToken();
				ee->left = e->right;
				e->right = ee;
				ee->right = readNum();
				break;
			default:
				break;
		}
    }
    
	return e;
}

AST *readNum()
{
    AST *e;
    
	if (currentToken == NUM) { // Top-down parsing

		e = (AST *)malloc(sizeof(AST));
		e->op = NUM;
		e->val = tokenVal;
		getToken();
		
		return e;

	} else {
		
		fprintf(stderr, "bad expression: NUM expected\n"); // Top-down parsing
		
		exit(1);
    }
}