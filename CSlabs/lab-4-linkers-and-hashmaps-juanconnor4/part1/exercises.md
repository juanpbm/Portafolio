(In a brief sentence or two)

1. What do you notice that is different about the functions(*Hint* search for foo)? 

the 'foo' function is listed as '_Z3fooii'

2. Do we have some information that could be useful for LD_PRELOAD if we were writing a function to override that function? That is, what information do we need to use to name a function?

You need the name and location of a library to name a function.

3. How many add_generic functions are there? What is your best guess for what the compiler is doing behind the scenes to implement the 'templating' feature?

In the symbol table, there 8 add_generic function definitions. Our best guess for what the compiler is doing is labeling the 4 function calls as seperate symbols as they are 4 different calls with different parameters. The compiler then stores 4 different definitions of the functions corresponding to the different calls with different parameters.
