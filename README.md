Name: Aryan Roy
PennKey: aryanroy
List of Submitted Source Files
penn-shredder.c

In this assignment, a simple command-line program was implemented. This program reads commands from the user and executes them using system calls. Additionally, signal handling was implemented for SIGINT and SIGALRM to provide a more robust user experience.

Description of Code and Code Layout:
main: Orchestrates the overall program.
timeout_handler: Handles timeouts by sending a SIGKILL signal to the child process.
sigint_handler: Handles the interrupt signal SIGINT.
is_all_whitespace: Checks if a string contains only whitespace.


Code Layout
Signal Handlers: The program starts by defining signal handler functions.
Utility Functions: A utility function (is_all_whitespace) for string checking is defined.



Main Logic:
Reads command-line arguments and initializes variables.
Sets up signal handlers.
Enters an infinite loop that:
Prompts the user for input.
Reads and processes input.
Tokenizes the input into commands and arguments to ignore spaces/tabs using malloc.
Forks and executes commands in a child process.
Waits for the child process to complete in the parent process.
Handles timeout if specified(ends child process).



