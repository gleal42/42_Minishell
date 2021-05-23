# Minishell
<br>

![screenshot minishell](media/minishell_pic.png)

In this project we are asked to mimic the behaviour of a bash shell.
We don't need to create a new window/ tabs our vertical splits like our iTerm (this is what I imagined the assignment would be).
Our assignment consists in creating a ./minishell executable that when opened, will show a prompt (`>msh`) and wait for user input.
The user can then type any shell commands like echo, ls, env export, pwd and we will show the exact same information / error messages as bash.
Fun fact: We can call other executables inside our minishell, including minishell itself.
So we can type `./minishell` to enter our minishell then `./minishell` again. We will then have to exit twice to finish all our programs.

### **DREAM TEAM**
This project was done in pairs, which was an amazing opportunity to learn how to better use github (I'll also add a few commands to showcase our workflow in this document):
I really want to thank Dimitri for everything he taught me about commenting code, for his amazing VSCode Snippets, his patience and dedication!
I couldn't have asked for a better team mate!

#### Our work was generally split in the following way:
<br>

> **[Dimitri](https://github.com/DimitriDaSilva)** 
> 
> Extracting Information, Parsing, Termcaps, Executables, Pipes and Redirections

> **[Goncalo](https://github.com/gleal42)**
> 
> Environment Variables, Builtin Functions and Signal Handling

___

### Main challenges

1. Extracting Information
2. Parsing - Abstract Synthax Tree
3. Environment Variables
4. Signals
5. Termcaps
6. Remaking the builtins
7. Running other executables from our terminal
   - Library executables (e.g. cat, ls)
   - Assynchronous Vs Synchronous (Pros, cons and our hybrid approach)
8. Pipes and Redirections
   - Pipes
   - Redirection
   - Combining our executables with builtin functions
9. Using Github Branches.
___

### 1. Extracting Information

A minishell (in it's simplest form) will extract a full line (breaking the while loop when it reaches `\n`) and analyzing it.
To follow the initial logic, just imagine we're using get_next_line, saving each line. We will see later that, in order to use the arrows to navigate history we will have to modify the get_next_line function to allow us to deploy different functions when the arrows characters are pressed. These, modifications will be described in the Termcaps section.

**Output**

Full line exactly as user typed it:
Example that we will use throughout this tutorial:

`echo helllo > test; echo testiiing > a if it works | echo hmmm | cat > b > c < test`
___

### 2. Parsing - Abstract Synthax Tree

> **Sources**
> 
> https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf


The best way to explain this concept is to say that instead of creating functions for every case that user writes we interpret what is being written in categories and subcategories:

Instead of trying to guess what the user is going to write:

```
if (strncmp(input, "echo helllo", 7) == 0 && ft_strchr(input, '>')) == 0 && ft_strchr(input, '|') == 0)
	ft_echo_25_no_redirection_no_pipes();
else if (strncmp(input, "echo helllo", 7) == 0 && ft_strchr(input, '>')) != 0 && ft_strchr(input, '|') == 0)
	ft_echo_25_with_redirection_no_pipes();
...
```

We create the following categories to help us interpret the input:


#### Command tables
Independent groups of commands and redirections which can be separated by `;` `&&` `||`, depending on the exit status of the commands inside it (exit status will be explained in the environment variables section).

#### Commands
Default interpretation
- `[command identifier` (e.g. echo)] 
- `[command arguments]` starting with flags(-n in the case of echo) in case they exist)
- Separated by pipes `|`

#### Redirections
Interpreted as such if redirection signs (`>` `<` or `>>`) are found
- `[name of file to be created, updated or read (single word)]`
	 - Once the output from a command is redirected, following commands (separated by pipes)
 	 	 - e.g. `echo okay baby > a sure| cat` will have standard output empty 
 	 	 	 - file `a` will have `okay sure` written inside (okay before redirection and sure after redirection)
 	 	 	 - cat will receive nothing as input and it will print nothing as output

We will dwelve further into redirections in pipes in their sections.

#### Tokens
Finally, white spaces will be ignored used as split delimiters for our command tables input (except when they are inbetween single or double quotes). 

I recommend that you check our [parse]src/parse/parse.c and [structs](src/structs.h) to better understand the processes that were conducted to convert the raw input into the aforementioned categories.

___

### 3. Environment Variables

> **Sources**
> 
>https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c
>https://man7.org/linux/man-pages/man7/environ.7.html

These work very similarly to Makefile Variables. They are associated to specific functions and tasks and get replaced in the moment of execution.

Some examples of environment variables:
- `USER=gleal42` used by our 42 header
- `PATH` used everytime we write a command (shell will look for executables in different directories specified in the variable)
- `PWD` and `OLDPWD`updated everytime we change directories. OLDPWD is used for `cd -` to go back to previous directory.
- `HOME`used for `cd` (with no arguments)
- `SHLVL` used in case we call `./minishell`

### Other Resources

Good overview
- https://github.com/tokenrove/build-your-own-shell

- https://github.com/brenns10/lsh
	- https://brennan.io/2015/01/16/write-a-shell-in-c/

1. https://hackernoon.com/lets-build-a-linux-shell-part-i-bz3n3vg1
2. https://hackernoon.com/building-a-linux-shell-part-ii-a-step-by-step-guide-pk203ywg
3. https://hackernoon.com/building-a-linux-shell-part-iii-wzo3uoi
4. https://hackernoon.com/building-a-linux-shell-part-iv-h21o3uwl
5. https://hackernoon.com/building-a-linux-shell-part-v-k61a3uai

https://nickolasteixeira.medium.com/want-to-build-a-simple-shell-heres-how-you-do-it-75890647bae8

1. https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/
2. https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/
3. https://indradhanush.github.io/blog/writing-a-unix-shell-part-3/
(Unfinished)


- https://medium.com/swlh/tutorial-to-code-a-simple-shell-in-c-9405b2d3533e
- https://danishpraka.sh/2018/01/15/write-a-shell.html

___

### Other Githubs
- https://github.com/R4meau/minishell/blob/master/src/main.c
- https://github.com/cclaude42/minishell
- https://github.com/pankratdodo/minishell-42
- https://adrienblanc.com/projects/42/minishell
- https://github.com/jraleman/42.Minishell
- https://git.42l.fr/Fabien/minishell

### Example of exercise from CS course
http://cs.brown.edu/courses/csci0330/shell1/

#### Parsing technique

- https://github.com/Swoorup/mysh

#### Suggested in Discord:

Recommended readings for parsing in minishell:
- https://en.wikipedia.org/wiki/LL_parser
- https://en.wikipedia.org/wiki/LR_parser
- https://en.wikipedia.org/wiki/Abstract_syntax_tree

If you want to go further in language theory:
- https://en.wikipedia.org/wiki/Formal_language
- https://en.wikipedia.org/wiki/Turing_machine
- https://en.wikipedia.org/wiki/Chomsky_hierarchy

- http://www.cems.uwe.ac.uk/~irjohnso/coursenotes/lrc/system/shell/index.html

Bash overview

https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation

Environmental Variables

chdir
https://stackoverflow.com/questions/4998530/can-chdir-accept-relative-paths
https://stackoverflow.com/questions/3642050/chdir-not-affecting-environment-variable-pwd

Pipes
https://swcarpentry.github.io/shell-novice/04-pipefilter/index.html
https://askubuntu.com/questions/404141/why-cant-i-pipe-into-cd
