# Cpp-bf-interpreter
THIS PROJECT IS A WORK-IN-PROGRESS

I want to make an interpreter for the BrainF*** Programming language

I will just say "bf" to be more family-friendly

Bf is a very simple language, so it is the only one I have a chance of making an interpreter for
# Usage
## Important to know
I use g++ to compile it. When compiled, run the program in a terminal. I use I/O to get the program from the user and the input to the program from the user.

## Inputting the program
Will ignore all characters exept the eight that are used in bf: <>,.[]-+

Uses newline as the mark that you are done inputting the program, so don't use newlines when inputting

## Input to the BF program.
(Not yet implemented)

Since the newline character is used to declare end of getline() in C++, instead do this:

\n

If you want to input the backslash character (\) you must enter two like this: \\

# TODO
Ensure the program has valid square bracket loops, so a program like these would NOT be OK:

][]

[]][

I also need to make it actually interpret BF code, but obviously this is just an aesthetic choice 

(Obviously joking)
