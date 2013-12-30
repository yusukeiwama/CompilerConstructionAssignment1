//
//  getToken.c
//  CompilerConstructionAssignment1
//
//  Created by Yusuke Iwama on 12/24/13.
//  Copyright (c) 2013 University of Tsukuba. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "exprParser.h"

int tokenVal;
TokenType currentToken;

void getToken()
{
    int c, n;

again:
    c = getc(stdin);
	
    switch (c) {
		case '+':
			currentToken = PLUS_OP;
			return;
		case '-':
			currentToken = MINUS_OP;
			return;
		case '*':
			currentToken = TIMES_OP;
			return;
		case '/':
			currentToken = OVER_OP;
			return;
		case '(':
			currentToken = LEFT_PAR;
			return;
		case ')':
			currentToken = RIGHT_PAR;
			return;
		case '\n':
			currentToken = EOL;
			return;
    }
	
    if (isspace(c)) goto again;

    if (isdigit(c)) {
		n = 0;
		
		do {
			n = n * 10 + (c - '0');
			c = getc(stdin);
		} while (isdigit(c));

		ungetc(c, stdin); // If c isn't digit, put it back to stdin.

		tokenVal = n; // Set token value.
		currentToken = NUM;

		return;
    }
	
    fprintf(stderr,"bad char '%c'\n",c);

    exit(1);
}
