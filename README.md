# Expression Interpreter

This is a simple expression interpreter.


![](https://github.com/zhaoyw1999/arithmetic-interpreter/blob/master/example.png)


## Build

Use the command `make` to build and `make clean` to delete object files.

## Usage

Use `make run` to run the interpreter (must be built before).

You can input any arithmetic expression such as:

```
(3 + 5) / 6 - 7 * 8 / 99
(((587)))
(1 + 2) * (3 + 4)
```

Note that this interpreter can only support arithmetic expression of this Backus-Naur Form：

```
e: expression
t: term
f: factor

e => e + t | e - t | t
t => t * f | t / f | f
f => x | (e)
x => number | id
```

Of course, you can also use variables and assignment statements like this:

```
a = 114
b = 514
c = a * b - a / b
```

Finally, you can input `$` to exit.