#include <unistd.h>     // getpid(), getcwd()
#include <sys/types.h>  // type definitions, e.g., pid_t
#include <sys/wait.h> 
#include <sys/stat.h> // wait()
#include <signal.h>     // signal name constants and kill()
#include <iostream>
#include <vector>
#include <string>
#include<stdlib.h> 
#include<unistd.h> 
#include<stdio.h> 
#include<fcntl.h>
using namespace std;

bool IsPathExist(const std::string &s)
{
  struct stat buffer;
   stat (s.c_str(), &buffer);
   return S_ISREG(buffer.st_mode);
}

void execute(char command[], vector<char*> args){
  //char** argv = new char*[args.size()+1];
  char* argv[args.size()+1];

  for(unsigned i,k = 0; i < args.size(); i++, k++){
    
  }
   

    argv[args.size()] = NULL;

    if ( strcmp( command, "exit" ) == 0 )
    {
      //return 0;
      return;
    }
    else
    {
      pid_t kidpid = fork();
      if ( kidpid < 0 )
      {
        perror( "Internal error: cannot fork." );
        //return -1;
        return;
      }
      else if ( kidpid == 0 )
      {
        // I am the child.
        execvp( argv[0], argv );
        // The following lines should not happen (normally).
        perror( command );
       // return -1;
        return;
      }
      else
      {
        // I am the parent.  Wait for the child.
        if ( waitpid( kidpid, 0, 0 ) < 0 )
        {
          perror( "Internal error: cannot wait for child." );
          //return -1;
          return;
        }
      }
    }
    args.clear();
}


int main(){

	int pipefd[4];
	if(pipe(pipefd) == -1){
		return 0;
	}

	int normal = dup(1);


 int file_desc = open("test.txt",O_WRONLY | O_TRUNC /*| O_APPEND*/); 
      
    // here the newfd is the file descriptor of stdout (i.e. 1) 
    int temp = dup2(file_desc, 1) ;  
          
    // All the printf statements will be written in the file 
    // "tricky.txt" 
    cout << "test2" << endl;
 close(temp);

    int x = dup2(normal, STDOUT_FILENO);


    cout << "should appear in terminal\n";

return 0;
}
































 