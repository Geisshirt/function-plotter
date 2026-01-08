# function-plotter
A simple function plotter implemented in C using [TinyExpr](https://github.com/codeplea/tinyexpr) to
parse the function and SDL2 to create graphs. 

## Usage
One can generate a graph by `./plot "exp" xrange yrange` i.e.:
```
$ ./plot "x * sin(x)" -10..10 -10..10
```
will generate this graph:<br> 
![quadratic](/Graphs/xsinx.png)
