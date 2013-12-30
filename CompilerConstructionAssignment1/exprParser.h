//
//  exprParser.h
//  CompilerConstructionAssignment1
//
//  Created by Yusuke Iwama on 12/24/13.
//  Copyright (c) 2013 University of Tsukuba. All rights reserved.
//

#ifndef CompilerConstructionAssignment1_exprParser_h
#define CompilerConstructionAssignment1_exprParser_h

typedef enum _TokenType {
	EOL = 0,	// End of Line ... '\n'
	NUM,		// Number ... '0-9'
	PLUS_OP,	// Plus operator ... '+'
	MINUS_OP,	// Minus operator ... '-'
	TIMES_OP,	// Times operator ... '*'
	OVER_OP,	// Over operatior ... '/'
	LEFT_PAR,	// Left parenthesis ... '('
	RIGHT_PAR	// Right parenthesis ... ')'
} TokenType;

typedef struct _AST { // Abstruct Syntax Tree (binary tree)
    int op;		// Operator type
    int val;	// Operand value
    struct _AST *left;
    struct _AST *right;
} AST;

extern int tokenVal;		// Token value (if currentToken isn't a number, tokenVal won't be used.)
extern TokenType currentToken;	// Current token

/*
 Used for Lexical Analysis. It sets value and type of the next token into tokenVal and currentToken, by reading one or more characters from stdin.
 */
void getToken(void);

/*
 Used for Syntactic Analysis. It returns an abstruct syntax tree by reading tokens.
 */
AST *readExpr(void);

/**
 Used for Semantics Analysis. It returns the result value by evaluating the AST.
 @param e The AST to be evaluated.
 @return Evaluated value.
 */
int evalExpr(AST *e);

#endif
