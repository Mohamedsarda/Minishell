# Minishell

Minishell is a project from the 42 curriculum that involves creating a minimal shell. This shell replicates some of the functionality of real-world shells like `bash` or `zsh`, allowing users to interact with the system through commands. The goal of this project is to deepen understanding of processes, file descriptors, and the basics of shell scripting.

---

## Features

- **Command Execution**: Executes commands using `execve`.
- **Built-in Commands**:
  - `echo`: Print text to the terminal.
  - `cd`: Change the current working directory.
  - `pwd`: Print the current working directory.
  - `export`: Set environment variables.
  - `unset`: Remove environment variables.
  - `env`: Display environment variables.
  - `exit`: Exit the shell.
- **Environment Variables**: Supports exporting, accessing, and modifying environment variables.
- **Input/Output Redirection**: Handles `>` (output redirection) and `<` (input redirection).
- **Pipes (`|`)**: Allows piping the output of one command into another.
- **Error Handling**: Provides meaningful error messages for invalid commands or syntax.
- **Signal Handling**: Handles signals such as `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` gracefully.

---

## Installation

1. Clone the repository:
   ```bash
   git clone git@github.com:Mohamedsarda/Minishell.git
   cd minishell
   ```
2. Compile the program:
   ```bash
   make
   ```
3. Run the shell:
   ```bash
   ./minishell
   ```

---

## Usage

- Start the shell by running `./minishell`.
- Type commands as you would in a regular shell, e.g.:
  ```bash
  ls -l | grep minishell > output.txt
  ```
- Use `exit` to quit the shell.

---

## Project Requirements

- Must be implemented in **C**.
- Must follow the **42 Norm**.
- Can only use allowed standard library functions.
- Handles edge cases and invalid input gracefully.
- Must support:
  - Multiple built-in commands.
  - Pipes and redirections.
  - Execution of external programs.


---

## Example Session

```bash
$ pwd
/home/user/minishell
$ ls -l | grep minishell > output.txt
$ cat output.txt
-rwxr-xr-x  1 user group 12345 Dec 24 2024 minishell
$ export PATH=/custom/path:$PATH
$ echo $PATH
/custom/path:/usr/local/bin:/usr/bin:/bin
$ exit
```

---

## Authors

- Mohamed Sarda
- [El Hossein El Ghalbzouri](https://github.com/El-Hossein)

---

## Acknowledgments

- 42 Network for the project.
- Peers and collaborators for guidance and support.



