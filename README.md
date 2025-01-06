# Pipex

Pipex is a program that takes two files and two user-specified programs, redirecting the input and output to emulate the behavior of the following Bash command:  
```bash
< input_file program1 | program2 > output_file
```
**Note:** Some functions rely on `<unistd.h>`, making this program incompatible with Windows.

## How to Compile

1. Clone this repository:
   ```bash
   git clone https://github.com/lhenriqu42/pipex
   ```

2. Navigate to the repository folder:
   ```bash 
   cd pipex
   ```

3. Compile the code using Make:
   ```bash
   make
   ```

## How to Use

1. After compilation, the Makefile will generate the executable binary `pipex`. Run it as follows:
   ```bash
   ./pipex input_file program1 program2 output_file
   ```