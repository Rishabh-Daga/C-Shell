# C-shell
A bash-like shell created using syscalls in C to implement various shell commands.

All the commands implemented are uploaded in a PDF with sample given in it
## How to start the shell
- Run `make` in terminal.
- Run `./a.out` to run the shell.


## How to exit the shell
- Enter `quit` to exit the shell.




### Functionalities of individual files

- ass2.c -> main file and bg fg processes 
- input.h -> contains function to scan input
- ls.h -> contains fucntion to execute ls command
- cd.h ->  contains function to execute cd command
- pinfo.h -> function to execute pinfo command
- pwd.h  -> a function for pwd and echo
- bgcheck.h  ->  handler for background processes
- cron.h -> bonus for cronjob
- global.h   ->   contains all global variables
- jobs.h ->  contains kjob, jobs, bg, fg, overkill  
- pipes.h  ->  contains all stuff for piping commands
- env.h    ->    contains setenv and unsetnev
- redirection.h  ->  all redirection stuff
