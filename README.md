# Leo Lang
A programming language that can be run either with an interpreter or compiled.

## Basic Rules
- Each line separates a new operation to take place
- Only a-Z and \_ are used for user names
- Commands must be in UPPER case _(unless otherwise defined in the "lang info" file)_
- Code indentation uses tabs _(unless otherwise defined in the "lang info" file)_
- When using multiple parameters/arguments a comma is used to separate multiple.
- Variables must have type definition
- Parameters/Arguments must have data-type definition
- Indexes start from 0
- Defined variables cannot change data-type
- Variables have a global/local scope (when defined in a function or loop they are local)
- When passing values into a function they can either be passed by reference or value, however some data-types must be passed by reference for example arrays
- Dynamically allocated memory must be freed manually
    - The "IN" command produces dynamic allocated memory
- You cannot define a function inside of another function

### Lang Info
A "lang info" file can be included in each project which defines certain parameters for the compiler/interpreter.

## Usage
When the leo-lang compiler has been compiled. You can give it the following command `compile example.leo example.c`, this will compile into a C file.

Then when compiling the C file you will need to add the -I option to include the "library_c" directory so that the header files will be found.

> Program usage is very still a WIP, and will be better in the future.

### Example

```
$ make
$ ./build/leo-lang.out compile example.leo example.c
$ gcc example.c library_c/inbuilt.c -I library_c/ -o main.o
```

## Code Examples
Code examples can be found in the examples directory.

## Syntax

### Input
`IN <Input Source> <Variable Name>`

Inputs are given as a STRING data-type.

#### Inputs Sources
- STDIN

### Output
`OUT <Output Source> <Variable Name>`

Output to the terminal with either a single variable or multiple.

#### Output Sources
- STDOUT
- STDERR

### VAR
`VAR <Variable Name> <Data Type>`

`VAR <Variable Name> <Data Type> = <Default Value>`

Declare a variable, with or without a default.

### SET
`SET <Variable Name> = <New Value>`

Give a variable a new value

### CALC
`CALC <Variable C> = <Variable A> <Operation> <Variable B>`

Calculate an operation between A and B and store it result in a variable C.

### IF
```
IF (<expression>)
    ...
```

Used to add logic into a program.

### WHILE
```
WHILE (<expression>)
    ...
```

Used to add while loops.

### FORI
```
FORI <Index Variable Name> <Start i value> <End i value>
    ...
```

For loop with a index and range.

### FORV
```
FORV <Value Variable Name> <Iterable Variable Name>
    ...
```

A for each value loop.

### BREAK
Used to stop iterating through a loop.

### FN
```
FN <Name>
    ...
```

```
FN <Name>(<params>)
    ...
```

```
FN <Name> <return type>
    ...
```

```
FN <Name>(<params>) <return type>
    ...
```

Define a function, with or without parameters and with a return type.

### RETURN
`RETURN <Variable Name>`

Return a variable from a function.

### CALL

`CALL <Function Name>`

`CALL <Function Name>(<params>)`

`CALL <Function Name> INTO <Variable Name>`

`CALL <Function Name>(<params>) INTO <Variable Name>`

Call a defined function with or without parameters, also storing a functions returned value into a variable.

### Arguments/Parameters
When using functions with parameters there are certain "features" that have to be used.

#### Defining
Arguments must have a expected data-type to receive. As well as data-types you can decide whether to pass the values by reference or value, _some data-types however must be passed by reference_.

This example shows a function expected a string and a integer passed by value.

```
FN my_func(STRING name, INT age)
    ...
```

This example shows a function expecting a string passed by value and a integer passed by reference.

```
FN my_func_two(STRING name, REF INT age)
    ...
```

#### Calling
When we call functions we must first know what data-types they are expecting and whether they should be passed by value or reference.

This example shows passing a string and integer into a function by value.

```
VAR name STRING = "Leo"
VAR age INTEGER = 19
CALL my_func(name, age)
```

This example shows passing a string by value and a integer by reference.

```
VAR name STRING = "Leo"
VAR age INTEGER = 19
CALL my_func_two(name, REF age)
```

### FREE
`FREE <Variable Name>`

Remove a defined variable from memory when not it's not going to be used anymore.

### USE
`USE <Import Path>`

Use code from system. Each file that is imported must be used in a separate "USE" statement.

### EXIT
`EXIT <code>`

Exit program with a specific code 0-255.

### COMMENT
`COMMENT <the comment>`

```
COMMENT
    ...
```

Add a comment, language allows for single line comments and multi-line using indentation.

### Data-Types
There are several data-types that can be used.

#### Types
- STRING, STR
- BOOLEAN, BOOL
- INTEGER, INT
- FLOAT
- ARRAY

#### Indexed Types
- STRING
- ARRAY

## Examples

### Count From 0 To 10
```
FORI number 0 10
    OUT STDOUT number
```

### Use
```
USE std

CALL std::Print("Hello World!")
```

### Functions
```
FN add_together(INT a, INT b) INT
    VAR c INT
    CALC c = (a + b)
    RETURN c
```

## License
Copyright (C) 2021 Leo Spratt

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
