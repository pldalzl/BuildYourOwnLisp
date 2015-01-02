#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#include <editline/readline.h>
#include <editline/history.h>

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];
/* Create some parsers */ 
mpc_parser_t* Number 	= mpc_new("number");
mpc_parser_t* Operator 	= mpc_new("operator");
mpc_parser_t* Expr 		= mpc_new("expr");
mpc_parser_t* Lispy 	= mpc_new("lispy");

/* Define them with the following Language */
mpca_lang(MPCA_LANG_DEFAULT,
	"														\
	number 		: /-?[0-9]+/;								\
	operator 	: '+' | '-' | '*' | '/';					\
	expr 		: <number> | '(' <operator> <expr>+ ')' ;	\
	lispy 		: /^/ <operator> <expr>+ /$/				\
	",
	Number, Operator, Expr, Lispy);


/* Fake readline function */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add_history function */
void add_history(char* unused) {}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

/* Undefine and delete the parsers */
mpc_cleanup(4, Number, Operator, Expr, Lispy);

int main(int argc, char** argv){
	/* Print Version and Exit information */
	puts("Lispy Version 0.0.0.0.1");
	puts("Press Ctrl-c to Exit\n");

	/* loop forever */
	while(1){
		
		/* Output prompt and get input*/
		char* input = readline("lispy> ");

		/*Add input to history */
		add_history(input);

		/* Echo input */
		printf("You said %s\n", input);

		/* Free retrieved input */
		free(input);
	}
	return 0;
}