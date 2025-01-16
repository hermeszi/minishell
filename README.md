# minishell 🐚
# 2024

#sigint(ctrl c) and sigquit(ctrl \) - ignore sigquit, sigint use readline function
#read, tokenize, ast nodes, parse, expansion, execute

### File Structure
```
                  ░█░░░█░█▀▀░█▀▀▄░█▀▀░█▀▀░█▀▄░▀█▀░█░░░░█▀▀░█▀▀▄░█▀▀▄░▄▀▀▄░█░░█
                  ░▀▄█▄▀░█▀▀░█░▒█░█▀▀░█▀▀░█░█░░█░░█▀▀█░█▀▀░█▄▄▀░█▄▄█░█▄▄█░█▄▄█
                  ░░▀░▀░░▀▀▀░▀░░▀░▀▀▀░▀▀▀░▀▀░░░▀░░▀░░▀░▀▀▀░▀░▀▀░▀░░▀░█░░░░▄▄▄▀
minishell
├── inc/
│   ├── minishell.h
│   ├── token.h
│   ├── parse.h
│   ├── exec.h
│   ├── pipe.h
│   ├── redirect.h
│   ├── builtins.h
│   ├── heredoc.h
│   ├── sig_control.h
│   └── error.h
│   └── env.h
│   └── expansion.h
├── libft/
├── token/
├── parse/
├── exec/
├── pipe/
├── redirect/
├── builtins/
├── heredoc/
├── signal/
├── error/
├── env/
├── expansion/
├── main.c
└── Makefile
```
###Main branch:
- [x] Write Makefile
- [x] Update headers
- [x] Clean up code to fit new headers and Makefile
- [x] clean memory leaks
- [x] norm

###Token:
- [] add expansion
- [x] norm

###Env:
- [x] dup env
- [x] norm

###Expansion
- []read from env
- []expand word
- []expand quote
- []norm
