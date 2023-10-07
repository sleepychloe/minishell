# minishell

Mandatory part without any bonus

Success 100/100

## Installation

```bash
  git clone https://github.com/sleepychloe/minishell.git
  cd minishell
  make
```

if comfile fails because of "readline/readline.h" header,
install it via

```bash
  sudo apt-get install libreadline-dev
```
    
## Usage

```bash
  ./minishell
```
to check memory leak
```bash
  valgrind --suppressions=./ignore_leak.supp --leak-check=full --show-leak-kinds=all ./minishell
```

## Handling invironment variable with quote, double quote, and dollar sign
```
- single quotes with $ENV: env variable will not change to the its value
    ex) command: echo '$HOME'
         output: $HOME
- double quotes with $ENV: env variable will change to the its value
    ex) command: echo "$HOME"
         output: /home/chloe
- signle or double quotes with dollar sign: dollar sign will be removed
    ex) command: echo $'cmd'
         output: cmd

- checklist
╔══════════════════╦══════════════════╗
║     command      ║      output      ║
╠══════════════════╬══════════════════╣
║  echo $HOME      ║  /home/chloe     ║
║  echo '$HOME'    ║  $HOME           ║
║  echo "$HOME"    ║  /home/chloe     ║
║  echo "'$HOME'"  ║  '/home/chloe'   ║
║  echo '"$HOME"'  ║  "$HOME"         ║
║  echo "$'HOME'"  ║  $'HOME'         ║
║  echo '$"HOME"'  ║  $"HOME"         ║
║  echo $"HOME"    ║  HOME            ║
║  echo $'HOME'    ║  HOME            ║
╠══════════════════╬══════════════════╣
║  echo $          ║  $               ║
║  echo $"cmd"     ║  cmd             ║
║  echo $'cmd'     ║  cmd             ║
╠══════════════════╬══════════════════║
║  echo '$?'       ║  $?              ║
║  echo "$?"       ║  0(exit code)    ║
║  echo $?         ║  0(exit code)    ║
║  echo "'$?'"     ║  '0'(exit code)  ║
║  echo '"$?"'     ║  "$?"            ║
║  echo $"?"       ║  ?               ║
╚══════════════════╩══════════════════╝
```
