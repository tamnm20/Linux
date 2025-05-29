# Makefile tutorial

## Variable

There are two flavors of variables:

recursive (use =) - only looks for the variables when the command is used, not when it's defined.
simply expanded (use :=) - like normal imperative programming -- only those defined so far get expanded

~~~make
# Recursive variable. This will print "later" below
one = one ${later_variable}
# Simply expanded variable. This will not print "later" below
two := two ${later_variable}

later_variable = later

all: 
	echo $(one)
	echo $(two)
~~~

.phony