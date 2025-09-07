#ifndef PARSER_H
#define PARSER_H

void expr();
void term();
void factor();
void parser();
void operations();
void conditional_expression();
void stmt();
void expr_prime();
void term_prime();
void stmt_prime();
void var();
void num();

extern int line_number;
extern char lexeme [100];
extern char strings[27][50];
extern int nextToken;
#endif

