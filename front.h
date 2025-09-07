#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 100
#define DIGIT 200
#define OTHER 300

/* Token codes */
#define ASSIGN_OP       0 // :=
#define LESSER_OP       1 // <
#define GREATER_OP      2 // >
#define EQUAL_OP        3 // =
#define NEQUAL_OP       4 // <>
#define LEQUAL_OP       5 // <=
#define GEQUAL_OP       6 // >=
#define LEFT_PAREN      7 // (
#define RIGHT_PAREN     8 // )
#define ADD_OP		9 // +
#define SUB_OP		10 // -
#define MULT_OP		11 // *
#define DIV_OP 		12 // /
#define POW_OP 		13 // **
#define INC_OP 		14 // ++
#define DEC_OP		15 // --
#define SEMICOLON	16 // ;
#define COLON		17 // :
#define KEY_READ	18 // read
#define KEY_PRINT	19 // print
#define KEY_IF		20 // if
#define KEY_ELSE 	21 // else
#define KEY_BEGIN	22 // begin
#define KEY_END		23 // end
#define INT_LIT         24 // N
#define IDENT           25 // V
#define UNKNOWN 	26 // UNKNOWN


int lex();

#endif

