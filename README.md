# function-plotter
A simple function plotter implemented in C using [TinyExpr](https://github.com/codeplea/tinyexpr) to
parse the function and SDL2 to create graphs. 

## Usage
One can generate a graph by `./plot "exp" xrange yrange` i.e.:
```
$ ./plot "x^2" -2..2 -1..2
```
will generate this graph:
![quadratic](/Graphs/quadratic.png)
