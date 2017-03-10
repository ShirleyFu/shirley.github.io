
/*
 * CS252: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include "command.h"

SimpleCommand::SimpleCommand()
{
	// Create available space for 5 arguments
	_numOfAvailableArguments = 5;
	_numOfArguments = 0;
	_arguments = (char **) malloc( _numOfAvailableArguments * sizeof( char * ) );
}

void
SimpleCommand::insertArgument( char * argument )
{
	if ( _numOfAvailableArguments == _numOfArguments  + 1 ) {
		// Double the available space
		_numOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				  _numOfAvailableArguments * sizeof( char * ) );
	}
	
	_arguments[ _numOfArguments ] = argument;

	// Add NULL argument at the end
	_arguments[ _numOfArguments + 1] = NULL;
	
	_numOfArguments++;
}

Command::Command()
{
	// Create available space for one simple command
	_numOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numOfSimpleCommands = 0;
	_outFile = 0;
	_inFile = 0;
	_errFile = 0;
	_background = 0;
}

void
Command::insertSimpleCommand( SimpleCommand * simpleCommand )
{
	if ( _numOfAvailableSimpleCommands == _numOfSimpleCommands ) {
		_numOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numOfSimpleCommands ] = simpleCommand;
	_numOfSimpleCommands++;
}

void
Command:: clear()
{
	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	if ( _outFile ) {
		free( _outFile );
	}

	if ( _inFile ) {
		free( _inFile );
	}

	if ( _errFile ) {
	     // free( _errFile );
	}

	_numOfSimpleCommands = 0;
	_outFile = 0;
	_inFile = 0;
	_errFile = 0;
	_background = 0;
	
}

void
Command::print()
{
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	
	fflush(stdout);
	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inFile?_inFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );
	
}

void
Command::execute()
{
	// Don't do anything if there are no simple commands
	if ( _numOfSimpleCommands == 0 ) {
		prompt();
		return;
	}
	if(!strcmp(_simpleCommands[0]->_arguments[0] ,"exit")){
	    printf("  Good bye!!\n");
	    exit(1);
	}

	// Print contents of Command data structure
	//print();

	// Add execution here
	// For every simple command fork a new process
	// Setup i/o redirection
	// and call exec
	
	int tempin=dup(0);
	int tempout=dup(1);
	int status;
	//set the initial inout 
	int fdin;
	if(_inFile ) {
               fdin = open(_inFile,O_RDWR);
        }
	else	fdin = dup(tempin);
	int temperr = dup(2);
        if(_errFile && _append == 1) 
	       temperr = open(_errFile,O_CREAT|O_WRONLY|O_APPEND,0600);
        if(_errFile && _append == 0) 
	       temperr = open(_errFile,O_CREAT|O_WRONLY,0600);
	       
	       
	dup2(temperr,2);
	close(temperr);
	 
        int fdout;
	int ret;
	for(int i=0; i<_numOfSimpleCommands;i++) {
          
          dup2(fdin,0);
          close(fdin);

          if (i == _numOfSimpleCommands-1) {
	        if(_outFile && _append == 1) {
                  fdout = open(_outFile,O_CREAT|O_WRONLY|O_APPEND,0600);
                }
		else if(_outFile){
		fdout = open(_outFile,O_CREAT|O_WRONLY,0600);
		}
	        else    fdout = dup(tempout);
          }
          else {
                int fdpipe[2];
                pipe(fdpipe);
                fdout = fdpipe[1];
                fdin = fdpipe[0];
          }
          dup2(fdout,1);
          close(fdout);
	  ret = fork();
	  if (ret == 0) {
	        execvp(_simpleCommands[i]->_arguments[0],_simpleCommands[i]->_arguments);
	        perror("execvp");
	        _exit(1);
	  }
	  else 
	  {
	       wait(&status);
	  }
	    dup2(fdin,0);
	}

        dup2(tempin,0);
        dup2(tempout,1);;
        close(tempin);
        close(tempout);

        if(!_background) {
           waitpid(ret,NULL, WNOHANG|WUNTRACED);
        }
	//printf("finished");
	// Clear to prepare for next command
	//printf("%d",_directT);
	if(_directT > 1) 
	   printf("Ambiguous output redirect\n");
	clear();
	
	// Print new prompt
	prompt();
}

// Shell implementation

extern "C" void disp(int sig){
	fprintf(stderr,"\nmyshell>");
}
void
Command::prompt()
{    
	if(isatty(0))
	printf("myshell>");
	fflush(stdout);
	
	
}
Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;

int yyparse(void);
main()
{
	struct sigaction sa;
	sa.sa_handler = disp;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if(sigaction(SIGINT, &sa ,NULL)){
   	  perror("sigaction");	  
	  exit(2);
	}
	Command::_currentCommand.prompt();
	yyparse();
	
}

