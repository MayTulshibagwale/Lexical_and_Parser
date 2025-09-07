#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "front.h"
/* ---------------------------------------------------------------------------------------------------------------*/

static void error();

/* i removed the left recursion from the grammar and thus used the new grammar.
 * change in <function> after removing recursion
*/
/* ---------------------------------------------------------------------------------------------------------------*/
void parser() {
  stmt();
}

/* ---------------------------------------------------------------------------------------------------------------*/
/* expr left recursion
 * E  ::= T E'
E' ::= + T E'
     | - T E'
     | ε
*/

void expr() {
  term();
  expr_prime();
}

void expr_prime() {
  while (nextToken == ADD_OP || nextToken == SUB_OP) {
    lex();
    term();
  }
}

/* ---------------------------------------------------------------------------------------------------------------*/
/* left recursion:
 * T  ::= F T'
T' ::= * F T'
     | / F T'
     | ** F T'
     | ε

*/

void term() {
  factor();
  term_prime();
}

void term_prime() {
  while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == POW_OP) {
    lex();
    factor();
  }
}

/* ---------------------------------------------------------------------------------------------------------------*/
void factor() {
  if (nextToken == IDENT) {
    var();
  } else if (nextToken == INT_LIT) {
    num();
  } else if (nextToken == LEFT_PAREN) {
    lex();
    expr();
    if (nextToken == RIGHT_PAREN) {
      lex();
    } else {
      error();
    }
  } else {
    error();
  }
}

/* ---------------------------------------------------------------------------------------------------------------*/
void operations() {
  if (nextToken == INC_OP || nextToken == DEC_OP) {
    lex();
    var();
  } else {
    error();
  }
}

/* ---------------------------------------------------------------------------------------------------------------*/
void conditional_expression() {
  expr();
  if (nextToken == LESSER_OP || nextToken == GREATER_OP || nextToken == EQUAL_OP || nextToken == NEQUAL_OP || nextToken == LEQUAL_OP || nextToken == GEQUAL_OP){
    lex();
    expr();
  } else {
    error();
  }
}

/* ---------------------------------------------------------------------------------------------------------------*/
/* stmt recursion:
 * S  ::= S1 S'
S1 ::= V := E
     | O
     | read(V)
     | print(E)
     | if C: begin S end
     | if C: begin S else: S end
S' ::= ; S S' | ε
*/

void stmt() {
  if (nextToken == IDENT) {
    var();
    if (nextToken == ASSIGN_OP) {
      lex();
      expr();
    } else {
      error();
      }
  } else if (nextToken == INC_OP || nextToken == DEC_OP) {
    operations();
    } else if (nextToken == KEY_READ) {
      lex();
      if (nextToken == LEFT_PAREN) {
        lex();
        var();
        if (nextToken == RIGHT_PAREN) {
          lex();
          } else {
            error();
            }
      } else {
        error();
        }
      } else if (nextToken == KEY_PRINT){
        lex();
        if (nextToken == LEFT_PAREN) {
          lex();
          expr();
          if (nextToken == RIGHT_PAREN) {
            lex();
          } else {
            error();
            }
        } else {
          error();
          }
      } else if (nextToken == KEY_IF) {
        lex();
        conditional_expression();
        if (nextToken == COLON) {
          lex();
          if (nextToken == KEY_BEGIN) {
            lex();
            stmt();
            if (nextToken == KEY_END) {
              lex();
            } else if (nextToken == KEY_ELSE) {
              lex();
              if (nextToken == COLON) {
                lex();
                stmt();
                if (nextToken == KEY_END) {
                  lex();
                } else {
                  error();
                  }
                } else {
                error();
                }
              } else {
                error();
                }
          } else {
            error();
            }
        } else {
          error();
          }
      } else {
        error();
        }
    stmt_prime();
}

void stmt_prime() {
  if (nextToken == SEMICOLON) {
    lex();
    stmt();
    stmt_prime();
  }
  printf("Exit <s_prime>\n");
}

/* ---------------------------------------------------------------------------------------------------------------*/
void var() {
  lex();
  while (nextToken == IDENT){
    lex();
  }
}

/* ---------------------------------------------------------------------------------------------------------------*/
void num() {
  lex();
  while (nextToken == INT_LIT) {
    lex();
  }
}


/* ---------------------------------------------------------------------------------------------------------------*/
static void error() {
  if (nextToken != EOF) {
    printf("Error encounter on line %d: The next lexeme was %s and the next token was %s\n",line_number, lexeme, strings[nextToken]);
    exit(1);
  } else {
    exit(0);
  }
}
/* ---------------------------------------------------------------------------------------------------------------*/
