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

1. [Extracting Information](#1-extracting-information)
2. [Parsing - Abstract Synthax Tree](2-parsing---abstract-synthax-tree)
3. [Environment Variables](#3-environment-variables)
4. [Termcaps](#5-termcaps)
5. Remaking the builtins
6. Running other executables from our terminal
   - Library executables (e.g. cat, ls)
   - Assynchronous Vs Synchronous (Pros, cons and our hybrid approach)
7. [Signals](#7-signals)
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


I recommend that you check our [parse](src/parse/parse.c) and [structs](src/structs.h) to better understand the processes that were conducted to convert the raw input into the aforementioned categories.

___

### 3. Environment Variables

> **Sources**
> 
>https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c
>https://man7.org/linux/man-pages/man7/environ.7.html
>https://stackoverflow.com/questions/23608202/can-i-setenv-using-a-envp

These work very similarly to Makefile Variables. They are associated to specific functions and tasks and get replaced in the moment of execution.

Some examples of environment variables:
- `USER=gleal42` used by our 42 header
- `PATH` used everytime we write a command (shell will look for executables in different directories specified in the variable)
- `PWD` and `OLDPWD`updated everytime we change directories. OLDPWD is used for `cd -` to go back to previous directory.
- `HOME`used for `cd` (with no arguments)
- `SHLVL` used in case we call `./minishell`

Environment variables will be important in our Minishell in the following ways:

> If the user types:
> 
> `echo $PWD$USER`

> The standard output should print something like:
> 
> `/Users/gleal42/Desktop/42_Minishellgleal42`

This list of variables can be acessed in two ways:

1. By adding a third argument to main `(int main (int argc, char **argv, char **envp))`
2. By calling the environ global varialbe `extern char **environ`

If we were allowed to use functions that can actually alter environment variables such as `putenv` `setenv` and `unsetenv`, the second option (using the extern global variable *environ*) would be great. But, the only function we're allowed to use related to environment variables is `getenv`, and we also have a limit on the global variables that we can use (just one), which is why we chose to duplicate this array of strings (in a linked list for easier setting and unsetting of variables).

___

### 5. Termcaps

> **Sources**
> 
> https://man7.org/linux/man-pages/man3/isatty.3.html
> https://www.mkssoftware.com/docs/man5/struct_termios.5.asp
> https://stackoverflow.com/questions/36258224/what-is-isatty-in-c-for/36258471
> https://linux.die.net/man/3/tcgetattr
> ibm.com/docs/en/aix/7.2?topic=library-understanding-terminals-curses
> https://man7.org/linux/man-pages/man5/termcap.5.html
> https://pubs.opengroup.org/onlinepubs/7990989799/xcurses/terminfo.html
> https://www.gnu.org/software/libc/manual/html_node/Canonical-or-Not.html
> https://pubs.opengroup.org/onlinepubs/7908799/xbd/termios.html
> https://smnd.sk/anino/programming/c/glibc-manual-0.02/library_16.html
> https://www.gnu.org/software/libc/manual/html_node/Noncanonical-Input.html
> https://www.ibm.com/docs/en/aix/7.2?topic=files-termiosh-file
> https://unix.stackexchange.com/questions/137842/what-is-the-point-of-ctrl-s


Termcaps stands for terminal capabilities. This 1992 Library is not easy to understand! Shout out to **[Dimitri](https://github.com/DimitriDaSilva)** for taming this monster. In this chapter I will summarize Dimitri's code comments and the main concepts. To better understand each function please read the comments in the code. 

As an old library, it has many and very complicated steps in order to work:

1. Protect the standard input file descriptor:

`if (!isatty(STDIN_FILENO))`

isatty is a function that checks if the standard input is pointing to our terminal (which is usually the case for 0, 1 and 2 file descriptors). This is important because we will use the STDIN fd in many termcaps functions. If it is not valid it is important to identify this error as soon as possible to display the correct error message (using the appropriate errno).

2. Save terminal settings before we change them using tcgetattr.
The settings are saved in a struct termios

```
struct termios {
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t c_cc[NCCS];
	speed_t c_ispeed;
	speed_t c_ospeed;
};
```
3. Using the tgetent function we check if there is a terminfo database (database with all terminal capabilities) for the TERM environment variable in our envp array and load the functions internally, so that the tgetstr function works.

4. We use tgetstr to check and save in a struct and tputs to activate the following capabilities:

	 1. We save ks -> keys_on (Transmit numpad/arrows). We we imediately use tputs to activate this functionality to output an ANSI code when these keys are pressed.
   2. We check and save ke -> keys_off capability that is the opposite of the previous capability so that we can activate it with (tputs) in order to quit the program correctly. Nothing happens when we turn it off but this way the terminal has exactly the same settings as when it started.
   3. The arrows and backspace ANSII code might also change from terminal to terminal so we need to check and save the key up (ku) key down (kd) key backspace (kb) characters in order to be compared with the ones read from the standard input.
   4. In order to reset the line we are also using the capabilities to delete the standard output (delete line "dl"). And, in case the cursor doesn't reset we use the "cr" capability to place it in the beginning of the current line. VSCode's and linux's terminals automatically reset the cursors but on the 42 MAC's it has to be done manually (we found out the hard way).

5. We change the terminal settings to change the way our read loop interprets the standard input and signals:

I think a great way to illustrate why we need to do this is if you use the command `cat` with no commands.
You can write as much as you want but it will only print a copy to the standard output once you press enter.
This is how our terminal is working in the beginning. Input is only interpreted if the read function finds a new_line.
However, when we press arrow up and down we want our terminal to interpret those characters, in order to navigate through our double linkedlist with the previously saved input.

The way that settings are changed is through bitwise operations:

| Initial settings(illustrative example) | 1 | 1 | 1 | 0 |
| ---------------- | - | - | - | - |
| ICANON (canonycal mode mask)| 0 | 1 | 0 | 0 |
| ~ICANON (inverted mask)| 1 | 0 | 1 | 1 |
| Init. Set &= ~ICANON | 1 | 0 | 1 | 0 |

Summing up:

~ is the BITWISE NOT operator inverts all bits
&= works exactly like a Mask in [Digital Art](https://www.youtube.com/watch?v=sbS5oUuGbGY):
- If mask is 0 then original value becomes 0.
- If mask is 1 then the original value doesn't change.

Okay, applying this logic we change several settings:

- Turn off canonycal processing ICANON
- Turn off local echo (we will have to write to standard output manually in order to see which characters were typed). ECHO
- Turn off specific signals (ctrl-c (SIGINT) and ctrl-z (SIGSTOP)) ISIG
- Turn off ^V chracter (otherwise an invisible character would be written (double enter needed). IEXTEN
- Turn off ctrl-s and ctrl-q, which were created in the time of teleprinters to make sure that the printers had time to physically print (in a paper) the code sent by the terminal. Obviously we won't need this feature because we don't print our code. We just post it on Github. IXON
- Read returns after single byte `termcaps->new_term.c_cc[VMIN] = 1;`
- Input waits 0 decisseconds before processing the read. `termcaps->new_term.c_cc[VTIME] = 0;` 

We then use `tcsetattr` to apply the new settings to our terminal.

6. We can now extract the input using the new settings and terminal capabilities:
	 1. We create a `char *buf[8192]` buffer to use in the read and write functions
	 2. We use ft_bzero to fill it with `0` to make sure that the string read is always null terminated.
	 3. We read 1-2 bytes at time because some extended ASCII characters, which can take up more than 1 byte.
	 4. We create different functions for each possible character:
			- `delete_single_char` will replace the last character with a `\0` and write it in the STDIO.
			- `parse_input_history` will clean current standard output and buffer, re-write the prompt and go through the double linkedlist, copy all characters of each command table to the buffer and write it in the STDIO.
			- `reset_cmd_line` - Replicate the ctrl-c behaviour
			- `exit_program` - Replicate the ctrl-d behaviour
			- Protect against printing invisible characters
			- Write all the other ASCII characters
	 5. If we find a line break we duplicate the buffer (allocating heap memory) and return it so it can be saved in the double linked list.
7. We reset the terminal setting to the original ones using `tcsetattr` with the termios struct we saved previously in `termcaps->old_term` in case we execute a different function that requires input (e.g. cat) in order for these to work normally.
8. We continue with parsing and execution (parsing described before).
___

### 7. Signals

> **Sources**
> 
> https://man7.org/linux/man-pages/man2/signal.2.html
> https://man7.org/linux/man-pages/man7/signal.7.html

We were asked to handle the following:

- CTRL-C
- CTRL-D (which is not a signal)
- CTRL-BACKSLASH

Now that we've talked about builtins, executables and about our termcaps it will be easier to understand how these work which.

The main issues that we must solve are that:
- Ctrl-D since it's not a signal, but a character (EOF) we don't need to do anything else. We've already dealt with it on our [Termcaps](#5-termcaps) section.
- Our minishell is an executable. So if we send a SIGINT(CTRL-C) signal or SIGQUIT (CTRL-\) it will self-quit the program. In our termcaps, while we're reading in non-canonycal mode, we already stop signals from doing this and print the correct messages in this case:
	- Ctrl-C it will print ^C and a linebreak
	- Ctrl-\ it will do nothing 

-  But if we were to start a cat or sleep and pressed ctrl-c/ or ctrl-\ we would exit both the cat /sleep executable as well as the minishell itself (not what we want).
- So we have to create signal catchers that will replace the "quitting" behaviour from this signals.
These catchers are made with the `signal` function, which redirects the signals to a specific function that we can define.
After some testing it appears that if we use an executable like `cat` then the signals SIGINT and SIGQUIT will continue to quit all the executables.

It will also print the `^C` character for Ctrl-C and not print anything for Ctrl-\) despite the different signal_catchers in our program.

So the messages we will need to print are:
- Ctrl-C just a linebreak `\n`
- Ctrl-\ the standard message: `Quit: 3\n`

**Warning**

If you're using a waitpid synchronously (meaning that if you write `sleep 4 | sleep 5`, then the process for the second sleep will only fork once the first sleep is finished. Then the signals will not work as expected. What I suggest is that you either change it to asynchronous (how we have it) or:

```
	else if (pid == 0)
	{
		if (g_msh.exit_status == 3 && process_index != 0)
		{
			if (process_index == nb_cmds - 1)
				printf("Quit: 3\n");
			signal(SIGQUIT, SIG_DFL);
			kill(0, SIGQUIT);
		}
```
So basically our signal will quit or interrupt the first process. But for the remaining we will have to do it manually.
We count the number of commands in the command table and we use a index to send the `SIGQUIT` signal the right amount of times. To send the sigquit signal without having to click the ctrl-\ we use the function `kill`. Kill is not just used to kill processes but to send all signals.


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
