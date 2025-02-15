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
# Minishell Project Tasks 🐚

## Current Development Tasks

### 1. Signal Handling
- [X] Fix SIGINT (Ctrl+C) exit status to return 130
- [X] Review and fix signal handling in heredoc context

### 2. Variable Expansion & Word Splitting
- [ ] Fix word splitting for variables
  ```bash
  # Issue example:
  export name="ninja          turtle"
  echo $name     # Should output: ninja turtle
  echo "$name"   # Should preserve original spacing
  ```
- [ ] Preserve spaces in quoted variable expansions

### 3. File Operations & Permissions
- [ ] Implement proper handling for non-executable files
- [ ] Add validation for `.` and `..` directory execution attempts (in token phase?)

### 4. Redirections & Pipes
- [ ] Fix pipe closing issues in redirect operations:
  ```bash
  # Test cases:
  > test
  >> test
  ```
- [ ] Implement correct behavior for multiple heredocs
- [ ] Fix heredoc behavior in pipe sequences
- [ ] Handle multiple redirections:
  ```bash
  # Test case:
  cat < makefile < asd
  ```
- [ ] Ensure pipe sequence continues with invalid commands:
  ```bash
  # Should continue execution despite 'blah' failing
  sleep 5 | blah | ls
  ```

### 5. Memory Management
- [ ] Implement cleanup() functions for all components

### 6. Additional Tasks
- [ ] Add/check error messages for failure cases

## Testing Requirements

### Signal Tests
```bash
# Test cases
ctrl+C during command execution
ctrl+C during heredoc
ctrl+C in empty prompt
```

### Variable Expansion Tests
```bash
# Test cases
export var="a   b   c"
echo $var
echo "$var"
echo '$var'
```

### Redirection Tests
```bash
# Test cases
cmd > file1 > file2
cmd >> file1 >> file2
cat < file1 < file2
```

### Pipe Tests
```bash
# Test cases
cmd1 | cmd2 | invalid_cmd | cmd3
cmd1 | cmd2 > file | cmd3
```

## Progress Tracking
- Keep this README updated as tasks are completed
- Mark completed tasks with [x]
- Add new edge cases as discovered

## Guidelines
1. Test before marking tasks as complete
2. Update behavior changes
3. Add anything missing to this doc.

