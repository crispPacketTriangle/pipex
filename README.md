# pipex

Pipex is a 42 project that uses process ids and file descriptors in order to recreate the behaviour of the unix | command.

There are two parts to the project.  

1. Taking and parsing input from the user, as well as parsing the paths to the relevant commands from environment variables. 
2. Forking processes and setting up pipes using the file descriptor table.

A set of commands are given as arguments to the programme, representing, "input", "command", "command", "output".

The input which could be a file, or stdin is passed to the first command and the output of this is passed into the second command, the output of which is passed to another file or stdout.

These processes, the use of file descriptors and process ids, and the way data is passed between them underlies the common refrain that everything in Linux is a file.
