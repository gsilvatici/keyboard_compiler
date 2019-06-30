
#Simple keyboard language

Compilar :

	$make

-----------------------------
Test :
	$ ./tla < tests.skl

obtiene archivo ./out.java

correrlo en java:

	$javac out.java
	$java out

-------------------------------
palabras reservadas

skl, for, if, whi, fun, int, str, go, con, .., eq, put, get, to, cmp, add, sub, mul, div, mod, gre, les, and, or, not

caracteres especiales
'.', ','

-----------------------------
hello_world.skl:

skl
fun main ..
		put .hello world,
..


