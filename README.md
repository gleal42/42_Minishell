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

- Extracting Information
- Parsing - Abstract Synthax Tree
- Environment Variables
- Signals
- Termcaps
- Remaking the builtins
- Running other executables from our terminal
  - Library executables (e.g. cat, ls)
  - Assynchronous Vs Synchronous (Pros, cons and our hybrid approach)
- Pipes and Redirections
  - Pipes
  - Redirection
  - Combining our executables with builtin functions
- Using Github Branches.
___

### Extracting Information

A minishell (in it's simplest form) will extract a full line (breaks when it reaches \n) and analyze it. (Use get next line).

### Parsing - Abstract Synthax Tree

- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

https://github.com/tokenrove/build-your-own-shell

### Other Resources

1. https://hackernoon.com/lets-build-a-linux-shell-part-i-bz3n3vg1
2. https://hackernoon.com/building-a-linux-shell-part-ii-a-step-by-step-guide-pk203ywg
3. https://hackernoon.com/building-a-linux-shell-part-iii-wzo3uoi
4. https://hackernoon.com/building-a-linux-shell-part-iv-h21o3uwl
5. https://hackernoon.com/building-a-linux-shell-part-v-k61a3uai

Check which is more complete:

1. https://medium.com/dev-genius/lets-build-a-linux-shell-part-i-954c95911501
2. https://medium.com/swlh/lets-build-a-linux-shell-part-ii-340ecf471028
3. https://medium.com/swlh/lets-build-a-linux-shell-part-iii-a472c0102849
4. https://medium.com/dev-genius/lets-build-a-linux-shell-part-iv-cefdd8f58138
5. https://medium.com/dev-genius/building-a-linux-shell-part-v-9cf3c0e31269

https://nickolasteixeira.medium.com/want-to-build-a-simple-shell-heres-how-you-do-it-75890647bae8

1. https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/
2. https://indradhanush.github.io/blog/writing-a-unix-shell-part-2/
3. https://indradhanush.github.io/blog/writing-a-unix-shell-part-3/
(Unfinished)

- https://github.com/brenns10/lsh
- https://brennan.io/2015/01/16/write-a-shell-in-c/

- https://www.geeksforgeeks.org/making-linux-shell-c/
- https://medium.com/swlh/tutorial-to-code-a-simple-shell-in-c-9405b2d3533e
- https://danishpraka.sh/2018/01/15/write-a-shell.html


### Githubs
- https://github.com/R4meau/minishell/blob/master/src/main.c (very commented)
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
- https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form (maybe not very useful in the case of minishell but this is the format used to describe how a parser should work)

If you want to go further in language theory:
- https://en.wikipedia.org/wiki/Formal_language
- https://en.wikipedia.org/wiki/Turing_machine
- https://en.wikipedia.org/wiki/Chomsky_hierarchy

- http://www.cems.uwe.ac.uk/~irjohnso/coursenotes/lrc/system/shell/index.html

See what implement AST means

Bash overview

https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation

Environmental Variables
https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c

chdir
https://stackoverflow.com/questions/4998530/can-chdir-accept-relative-paths
https://stackoverflow.com/questions/3642050/chdir-not-affecting-environment-variable-pwd

Pipes
https://swcarpentry.github.io/shell-novice/04-pipefilter/index.html
https://askubuntu.com/questions/404141/why-cant-i-pipe-into-cd
