
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>


pid_t pid;



void sigint_handler(int signum) {
    
    write(STDERR_FILENO, "\n", 1);
    
    write(STDERR_FILENO, PROMPT, strlen(PROMPT));
}


int is_all_whitespace(const char *str) {
    
    while (*str) {
        
        if (*str!= '\t' ||*str != ' ') {
            return 0;
        }
        str++;
    }
    
    return 1;
}


int main(int argc, char *argv[]) {
   
    int timeout = -1;

    if (argc > 2) {
        
        fprintf(stderr, "Error: Too many arguments provided.\n");
        exit(EXIT_FAILURE);
    }
    
    if (argc == 2) {
        
        timeout = atoi(argv[1]);
       
        if (timeout < 0) {
            fprintf(stderr, "Error: Timeout value cannot be negative.\n");
            exit(EXIT_FAILURE);
        }
    }

    
    const int maxLineLength = 4096;
    char cmd[maxLineLength];

    
    signal(SIGINT, sigint_handler);

    
    while (1) {
        
        write(STDERR_FILENO, PROMPT, strlen(PROMPT));
       
        int numBytes = read(STDIN_FILENO, cmd, maxLineLength - 1);
        
      
        
     if (numBytes == 0) {
    write(STDERR_FILENO, "\n", 1);
    exit(EXIT_SUCCESS);
} else if (numBytes < 0) {
    perror("read");
    exit(EXIT_FAILURE);
} else {
    
    if(cmd[numBytes-1] == '\n') {
       cmd[numBytes-1] = '\0';
    } else {
        cmd[numBytes] = '\0';
         write(STDERR_FILENO, "\n", 1);
    }
       

    if (is_all_whitespace(cmd)) {
       
        continue;
    }
}


 int arg_count = 0;
        char **args = NULL;
        char *token = strtok(cmd, " \t");

        while (token != NULL) {
            
            char **new_args = malloc(sizeof(char*) * (arg_count + 1));
            for (int i = 0; i < arg_count; i++) {
                new_args[i] = args[i];
            }
            free(args);
            args = new_args;

            args[arg_count++] = token;
            token = strtok(NULL, " \t");
        }

       
        char **new_args = malloc(sizeof(char*) * (arg_count + 1));
        for (int i = 0; i < arg_count; i++) {
            new_args[i] = args[i];
        }
        free(args);
        args = new_args;
        args[arg_count] = NULL;

      
       
    
        pid = fork();

       
        if (pid == 0) {
            if(timeout>=0) {
                alarm(timeout);
            }


           int output=  execve(args[0], args, NULL);
           if(output== -1){
            perror("execve");
            exit(EXIT_FAILURE);
           }

           exit(EXIT_SUCCESS);
        }
        
        else if (pid > 0) {
          
           
           int status;
            wait(&status);
            
             if (WIFSIGNALED(status)) {
                write(STDERR_FILENO, CATCHPHRASE, strlen(CATCHPHRASE));
            }
             if (timeout >= 0) {
                alarm(0);
            }
            
        }
       
        else {
           
            perror("fork");
            exit(EXIT_FAILURE);
        }

        
        free(args);
    }

   
    return 0;
}
