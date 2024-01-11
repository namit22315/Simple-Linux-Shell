# Simple-Linux-Shell

## Overview

SimpleShell is a basic command-line shell program written in C. It provides a simple interactive shell environment that allows users to enter commands, execute them, and manage a command history. The shell can also run commands in the background and execute script files. This README describes the key features and functionality of the SimpleShell code.

## Key Features

### Command Execution

- *Interactive Shell*: SimpleShell provides an interactive command-line interface where users can enter commands.

- *Command Execution*: The shell executes user-provided commands and displays the output. It supports a variety of commands, including Unix-like commands, script execution, and more.

- *Command History*: SimpleShell maintains a command history, allowing users to view previously executed commands.

### Script Execution

- *Script Execution*: Users can execute script files by entering the script filename. The shell opens the script, reads its contents, and executes the commands within the script.

- *Script Error Handling*: SimpleShell provides error messages for cases where it cannot open a specified script file.

### Background Execution

- *Background Processes*: SimpleShell supports running commands in the background using the "&" operator. It displays the process ID (PID) of background processes.

### Exiting the Shell

- *Graceful Exit*: Users can exit the shell by entering the "exit" command.

### Error Handling

- *Error Reporting*: The shell handles errors gracefully and provides informative error messages when necessary, such as when a script file cannot be opened or when a system call fails.

## Code Structure

The code for SimpleShell is organized as follows:

- *Main Function*: The `main` function contains the main logic of the shell. It initializes the command history and enters an infinite loop to accept and process user input.

- *`execute_command` Function*: This function is responsible for executing individual commands. It handles command history, background execution, and error reporting.

- *Command History*: SimpleShell uses a custom data structure called `CommandHistory` to store and manage the command history.

## Contribution

### Person 1: Namit Jain (Roll No. 2022315)

- Implemented the `execute_command` function, responsible for executing commands and managing background processes.
- Created the data structure for the command history and implemented the history management logic.
- Handled the execution of commands, including error reporting.
- Managed background execution of commands using the "&" operator.
- Assisted in debugging and optimizing the code.
- Handling the execution of .sh files.
- Implemented the main function of the shell, including the interactive command input loop.
- Added support for running script files, opening and executing them line by line.
- Handled user input, command parsing, and the "exit" command.
- Collaborated in debugging and optimizing the code.
- Assisted in reviewing and ensuring code clarity and readability.
- handled the PID and process termination status..


## Requirements

- *Compilation*: Compile the source code using a C compiler, e.g., `gcc -o myshell myshell.c`.

- *Usage*: Run the compiled executable, e.g., `./myshell`, to start the shell.

- *Commands*: Enter commands interactively, execute script files, and use background execution features.

- *Exit*: To exit the shell, enter the "exit" command.

## Limitations

- SimpleShell does not implement the actual functionality of Unix commands but relies on system calls to execute them.

- Some complex or specialized Unix commands may not be fully supported.

- User commands should not include backslashes or quotes, and arguments are separated by whitespace.

- Detailed information about the execution of past commands is displayed only for the current session's history.

Feel free to explore and use SimpleShell for your basic command execution needs. If you have any questions or encounter issues, please reach out for assistance.

## Github link
https://github.com/namit22315/SimpleShell
