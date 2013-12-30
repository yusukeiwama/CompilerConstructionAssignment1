//
//  interpreter.c
//  CompilerConstructionAssignment1
//
//  Created by Yusuke Iwama on 12/24/13.
//  Copyright (c) 2013 University of Tsukuba. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "exprParser.h"

int main()
{
	AST *e;
	
    getToken(); // Lexical Analysis (look-forward)
	
    e = readExpr(); // Syntax Analysis (build AST)
	
    if (currentToken != EOL) { // Error check
		printf("error: EOL expected\n");
		exit(1);
    }
	
    printf("= %d\n", evalExpr(e)); // Semantics Analysis (evaluate AST)

    exit(0);
}
