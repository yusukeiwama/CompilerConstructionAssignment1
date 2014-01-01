//
//  readExpr.c
//  CompilerConstructionAssignment1
//
//  Created by Yusuke Iwama on 12/24/13.
//  Copyright (c) 2013 University of Tsukuba. All rights reserved.
//

/*
 Top-Down Parser of Four Arithmetic Operations
 based on the following BNF.
 
 BNF =======================================================
 <expression> := <term> <expression1>
 <expression1> := <expr_op> <term> <expression1> | e
 <term> := <factor> <term1>
 <term1> := <term_op> <factor> <term1> | e
 <factor> := number | '-' number | '(' <expression> ')'
 <expr_op> := '+' | '-'
 <term_op> := '*' | '/'
 ===========================================================
 
 TEST CASE =================================================
 0
 1
 -0
 -1
 2+3
 -1+-0*4/2-3
 12*3 + 3*4 - 10
 12*(3+13)-10
 -10 / (-5) *3+3-(-1)  
 ===========================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "exprParser.h"

AST *readTerm(void);
AST *readFactor(void);


AST *readExpr(void)
{
    AST *e, *ee;
	
	e = readTerm();
	
    while (currentToken == PLUS_OP
		   || currentToken == MINUS_OP) {
		
		ee = (AST *)malloc(sizeof(AST)); // look-ahead
		ee->op = currentToken;
		getToken();
		ee->left = e;
		ee->right = readTerm();
		e = ee;
    }
    
	return e;
}


AST *readTerm(void)
{
	AST *e, *ee;
	
	e = readFactor();
	
	while (currentToken == TIMES_OP
		   || currentToken == OVER_OP) {
		
		ee = (AST *)malloc(sizeof(AST));
		ee->op = currentToken;
		getToken();
		ee->left = e;
		ee->right = readFactor();
		e = ee;
	}
	
	return e;
}


AST *readFactor(void)
{
	AST *e;
	
	switch (currentToken) {
		case NUM:
			e = (AST *)malloc(sizeof(AST));
			e->op = NUM;
			e->val = tokenVal;
			getToken();
			return e;
		case MINUS_OP:
			getToken();
			if (currentToken == NUM) {
				e = (AST *)malloc(sizeof(AST));
				e->op = NUM;
				e->val = -tokenVal; // negative value
				getToken();
				return e;
			} else {
				fprintf(stderr, "bad expression: NUM is expected\n"); // Top-down parsing
				exit(1);
			}
		case LEFT_PAR:
			getToken();
			e = readExpr();
			if (currentToken == RIGHT_PAR) {
				getToken();
				return e;
			} else {
				fprintf(stderr, "bad expression: RIGHT_PAR is expected\n"); // Top-down parsing
				exit(1);
			}
		default:
			fprintf(stderr, "bad expression: NUM, MINUS_OP or LEFT_PAR is expected\n"); // Top-down parsing
			exit(1);
	}
}
