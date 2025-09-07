/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "front.h"
#include "parser.h"
#include <sys/stat.h>
#include <stdlib.h>



/* Global Variable */
int nextToken;
int line_number = 1;

/* Local Variables */
static int charClass;
char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();

char strings[27][50] = { 

	 "ASSIGN_OP",
         "LESSER_OP",       
	 "GREATER_OP", 
	 "EQUAL_OP",
         "NEQUAL_OP",  
	 "LEQUAL_OP",       
	 "GEQUAL_OP",       
	 "LEFT_PAREN",     
	 "RIGHT_PAREN",    
	 "ADD_OP",          
	 "SUB_OP",          
	 "MULT_OP",         
	 "DIV_OP",         
	 "POW_OP",        
	 "INC_OP",          
	 "DEC_OP",          
	 "SEMICOLON",       
	 "COLON",           
	 "KEY_READ",        
	 "KEY_PRINT",       
	 "KEY_IF",          
	 "KEY_ELSE",        
	 "KEY_BEGIN",       
	 "KEY_END",         
	 "INT_LIT",        
	 "IDENT",           
	 "UNKNOWN"         
    };


/******************************************************/
/* main driver */
int main(int argc, char *argv[]) 
{
    /* R number */
    printf("Cooke Analyzer::R#11815197\n");
    
    /* declaring variables for checking if file exist*/
    struct stat file_info;
    int return_value_of_stat;

    /* Checks if the file name is passed as Command - line Argument -- exit code 2*/
    if (argc != 2) 
    {
    
        printf("Please provide the Test file as the first Command-Line Argument \n");
	exit(2);
    }

    /* Checks if the file exist -- exit code 3*/
    return_value_of_stat = stat(argv[1], &file_info);
    if (return_value_of_stat == -1){
    	printf("%s file does not exist.\n", argv[1]);
	exit(3);
    }

    /* Now that we know that file exist let us check if we can open it for reading */
    
    in_fp = fopen(argv[1], "r");
    if (in_fp == NULL) 
    {
        printf("ERROR - cannot open %s\n",argv[1]);
	return 4;
    }
    /* Now that we can open the file for reading lets start processing it*/
    else 
    {
	getChar();
        lex();
	parser();

        /* Syntax Validated*/
        printf("Syntax Validated\n");
        exit(0);
    }	
}


/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the 
 * token */
static int lookup(char ch) 
{
    switch (ch) {
        case '(':
            addChar();
	    getChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
	    getChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
	    getChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
	    getChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
	    getChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
	    getChar();
            nextToken = DIV_OP;
            break;
        case ';':
            addChar();
	    getChar();
            nextToken = SEMICOLON;
            break;
        case ':':
            addChar();
	    getChar();
            nextToken = COLON;
            break;
        case '=':
            addChar();
	    getChar();
            nextToken = EQUAL_OP;
            break;
        case '<':
            addChar();
	    getChar();
            nextToken = LESSER_OP;
            break;
        case '>':
            addChar();
	    getChar();
            nextToken = GREATER_OP;
            break;
        default:
            addChar();
	    getChar();
            nextToken = UNKNOWN;
            break;
	    
    }
    return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() 
{
    if (lexLen <= 98) 
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else 
    {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its 
 * character class */
static void getChar() 
{
    if ((nextChar = getc(in_fp)) != EOF) 
    {
	if (nextChar =='\n'){
	    line_number++;
	}
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = OTHER;
    } 
    else 
    {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace 
 * character */
static void getNonBlank() 
{
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() 
{
    lexLen = 0;
    getNonBlank();
    memset(lexeme, 0, sizeof(lexeme));
    
    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) 
	    {
                addChar();
                getChar();
            }
	    if (strcmp(lexeme,"read") == 0)
		    nextToken = KEY_READ;
	    else if (strcmp (lexeme, "print") == 0)
		    nextToken = KEY_PRINT;
	    else if (strcmp (lexeme, "if") == 0)
		    nextToken = KEY_IF;
	    else if (strcmp (lexeme, "else") == 0)
		    nextToken = KEY_ELSE;
	    else if (strcmp (lexeme, "begin") == 0)
		    nextToken = KEY_BEGIN;
	    else if (strcmp (lexeme, "end") == 0)
		    nextToken = KEY_END;
	    else
            	    nextToken = IDENT;
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) 
	    {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case OTHER:
            lookup(nextChar);
	    if (nextToken == COLON) // Checks for := 
	    {
	    	//getChar();
		if (nextChar == '=') 
		{
		   addChar();
		   getChar();
		   nextToken = ASSIGN_OP;
		}
	    }
	    
	    else if (nextToken == LESSER_OP) 
	    {
		//getChar();
		if (nextChar == '=') // Checks for <=
		{
		   addChar();
		   getChar();
		   nextToken = LEQUAL_OP;
		}
		else if (nextChar == '>') // Checks for <>
		{
		   addChar();
		   getChar();
		   nextToken = NEQUAL_OP;
		
		}

	    }
	    
	    else if (nextToken == GREATER_OP) // Checks for >=
	    {
   	    	//getChar();
		if (nextChar == '=')
		{
		   addChar();
		   getChar();
	       	   nextToken = GEQUAL_OP;	   
		}
	    }
	     
	    else if (nextToken == MULT_OP) // Checks for **
   	    {
		//getChar();
		if (nextChar == '*')
		{
		   addChar ();
		   getChar();
		   nextToken = POW_OP;
		}
	    }

	    else if (nextToken == ADD_OP) // Checks for ++	
	    {
		//getChar();
		if (nextChar == '+')  //changed to nextChar
		{
		   addChar();
		   getChar();
		   nextToken = INC_OP;
		}
	    }	
	
	    else if (nextToken == SUB_OP) // Checks for --
	    {
		//getChar();
		if (nextChar == '-')
		{
		   addChar();
		   getChar();
		   nextToken = DEC_OP;
		}
	    }

	    //getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */
   if (nextToken != EOF) 
   {
	    printf("%s\t%s\n", lexeme,strings[nextToken]);
   }

   return nextToken;
} /* End of function lex */


