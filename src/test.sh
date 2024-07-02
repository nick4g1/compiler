gcc -o test main.c lexer.c parser.c -g
gdb --args ./test input.txt output.txt
