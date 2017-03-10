
/*
 * CS-252
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */

%token	<string_val> WORD

%token 	NOTOKEN GREAT NEWLINE GREATGREAT PIPE AMPERSAND LESS GREATGREATAMPERSAND GREATAMPERSAND 

%union	{
		char   *string_val;
	}

%{
//#define yylex yylex
#include <stdio.h>
#include "command.h"
void yyerror(const char * s);
int yylex();

%}

%%

goal:	
	command_list
	;

	
pipe_list:
 	pipe_list PIPE command_and_args {
	 // printf("pipe_list: pipe_list PIPE command_and_args\n");
	  
	}
	| command_and_args {
	  
	 // printf("pipe_list : command_and args\n");
       }
       |
	;

argument_list:
	argument_list argument{
	}
	| /* can be empty */
	;

command_and_args:
	command_word argument_list {
	 	//printf(" comman_and_args: command_word argument_list\n");
	        /*Command::_currentSimpleCommand = new SimpleCommand();
	        Command::_currentSimpleCommand->insertArgument( $1 );*/
		Command::_currentCommand.
			insertSimpleCommand( Command::_currentSimpleCommand );
	}
	;


argument:
	WORD {
              // printf("   Yacc: insert argument \"%s\"\n", $1);

	       Command::_currentSimpleCommand->insertArgument( $1 );\
	}	
	;

command_word:
	WORD {
               //printf("   Yacc: insert command \"%s\"\n", $1);
	       Command::_currentSimpleCommand = new SimpleCommand();
	       Command::_currentSimpleCommand->insertArgument( $1 );
	}
	;


io_modifier_opt:
	GREAT WORD {
	//	printf("   Yacc: insert output \"%s\"\n", $2);
		//printf("%d",Command::_currentCommand._directT);
		Command::_currentCommand._outFile = $2;
	        Command::_currentCommand._directT++;
	}
	| GREATGREATAMPERSAND WORD{
		Command::_currentCommand._append = 1;
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._errFile = $2;
	        Command::_currentCommand._directT++;

	}
	| GREATAMPERSAND WORD{
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._errFile = $2;
	        Command::_currentCommand._directT++;
	}
	| GREATGREAT WORD{
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._append = 1;
	        Command::_currentCommand._directT++;
	}
	| LESS WORD{
		Command::_currentCommand._inFile = $2;
	}
	;

io_modifier_list:
	io_modifier_list io_modifier_opt{
	 //	printf("io_list:list op\n");
	}
        |io_modifier_opt
	|
	;
	
background_opt:
	AMPERSAND{
	//	printf(" background_opt:amoersand");
		Command::_currentCommand._background=1;
	}
	|	
	;

command_line:
	pipe_list io_modifier_list background_opt NEWLINE{
	 // printf("  comman_line:Excute command\n");
          Command::_currentCommand.execute();	
	}
	|NEWLINE
	|error NEWLINE{yyerrok;}
	;

command_list:
	|command_list command_line
	;
%%

void
yyerror(const char * s)
{
	
	fprintf(stderr,"%s", s);
}
#if 0
main()
{
	yyparse();
}
#endif
