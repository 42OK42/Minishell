# Minishell

A simple shell interpreter that replicates basic Bash functionalities. This project is part of the 42 School curriculum.

## Overview

Minishell implements a basic command-line interpreter with:
- Command execution
- Pipes (`|`)
- Redirections (`<`, `>`, `>>`)
- Environment variables (`$`)
- Here-Documents (`<<`)
- Signal handling (ctrl-C, ctrl-D, ctrl-\\)
- Built-in shell commands

### Built-in Commands

- `echo` (with -n option)
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

## Installation

```bash
git clone git@github.com:42OK42/Minishell.git
cd Minishell
make
```

## Usage

```bash
./minishell
```

### Examples

```bash
# Simple commands
> ls -la

# Pipes
> ls | grep .c

# Redirections
> ls > output.txt
> cat < input.txt

# Environment variables
> echo $PATH

# Here-Document
> cat << EOF
> This is the text
> Multiple lines possible
> EOF
```

## Key Learnings

- **Process Management**: Deep understanding of fork, exec, and pipes
- **Signal Handling**: Implementation of signal handlers for various terminal events
- **Parsing**: Development of a robust parser for shell syntax
- **Memory Management**: Careful memory management to avoid leaks
- **Error Handling**: Comprehensive error handling for various edge cases

## Technical Details

- Written in C
- Uses readline library for input handling
- Implements custom parsing logic
- Handles complex command chaining

## Project Structure

```
.
├── src/
│   ├── execution/       # Command execution
│   ├── parsing/         # Input parsing
│   ├── built_ins/       # Built-in commands
│   └── utils/          # Helper functions
├── incl/               # Header files
└── libft/              # Custom C library
```

## Known Limitations

- No support for complex Bash features like wildcards or functions
- Limited error handling compared to original Bash
- No job control

## Contributors

- [bschmidt](https://github.com/Bendix-Schmidt)

## License

This project is part of the 42 School curriculum.

