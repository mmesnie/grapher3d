/*
 * Please see README for copying information.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int child(char *cmd, FILE **input, FILE **output) {
  int childpid, pipe1[2], pipe2[2];
  
  /*
   * Create two pipes.
   */ 

  if ((pipe(pipe1) < 0) || (pipe(pipe2) < 0)) {
    perror("pipe"); 
    exit(-1);
  }

  /*
   * Fork into two processes
   */

  if ((childpid = fork()) <0) {
    perror("fork");
    exit(-1);
  } else if (childpid > 0) {

    /*
     * This is the parent. It will only be able
     * to write to pipe1 and read from pipe2. 
     */
 
    close(pipe1[0]);
    close(pipe2[1]); 
    *input  = fdopen(pipe2[0], "r");
    *output = fdopen(pipe1[1], "w");
    return childpid;
  } else {

    /*
     * This is the child. It will only be able
     * to read from pipe1 and write to pipe2.
     */

    close(pipe1[1]);
    close(pipe2[0]); 

    /*
     * The commands "standard in" while now
     * come from pipe1[0], and the "standard
     * out" will go to pipe2[1].
     */

    dup2(pipe1[0], 0);
    dup2(pipe2[1], 1);
    if (execlp(cmd, cmd, NULL) <0) {
      perror(cmd);
      exit(-1);
    }
  }    
  return 0;
}
