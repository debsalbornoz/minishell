<h1 align="center">Minishell</h1>

<div align="center">
<img alt="Static Badge" src="https://img.shields.io/badge/Status-Finished-green">
<img alt="Static Badge" src="https://img.shields.io/badge/42-Project-blue">
<img alt="Static Badge" src="https://img.shields.io/badge/Language-C-lightgrey">
</div>

## Demo

[minishell.webm](https://github.com/user-attachments/assets/1d2f7bdd-3ab1-4b3c-8155-7191f02d140b)

## About

**Minishell** is a simple shell developed in C, built to simulate a basic command-line environment similar to Bash. This project provides hands-on understanding of the fundamental principles behind how a shell works, including command execution, process management, environment variable handling, and interaction with the operating system.

Minishell lets users run system commands, change directories, and manage data input/output, offering an environment that mimics the experience of a real shell. Throughout development, a range of programming techniques were explored, including string manipulation, system calls for process management, and error handling — all aimed at ensuring robustness and reliability.

## Features

Minishell offers several features that make the experience interactive and practical:

- **Command execution** — run both simple commands and system binaries.
- **Builtins** — support for built-in commands such as `cd` (change directory) and `exit` (terminate the shell).
- **Environment variable handling** — allows viewing and setting environment variables, essential for configuring the execution environment.
- **Input/output redirection** — redirect command output to files, and read input from files.
- **Pipes** — chain commands together using pipes, so the output of one command becomes the input of another.
- **Error handling** — critical operations include error checking, providing a more stable and predictable experience.

## Table of Contents

- [Installation](#installation)

## Installation

To install Minishell, you'll need the GCC compiler and the Make utility installed on your system. Follow the steps below to set up the environment:

1. Clone the repository:

    ```bash
    git clone git@github.com:debsalbornoz/minishell.git
    ```

2. Navigate to the project directory:

    ```bash
    cd minishell
    ```

3. Build the project:

    ```bash
    make
    ```

4. Start Minishell by running the following command in your terminal:

    ```bash
    ./minishell
    ```

---

<p align="center">Built as part of the 42 curriculum 🖥️</p>
