
conversation:-write('* Identifiquese '),read(X),saludo(X,[]).

nombre([boing717|X],X).
nombre([embraer190|X],X).


saludo([hola|X],X).
controlador([maycey|X],X).
alerta([secuestro|X],X).

verbo([vuela|X],X).
verbo([despega|X],X).
verbo([aterriza|X],X).
determinante(singular,[el|X],X).
determinante(plural,[los|X],X).

usersay(X,Y):-saludo(X,Z),controlador(Z,Y).
usersay(X,Y):-alerta(X,Y).


max(X,Y,Z):-X>Y->Z is X;Z is Y.

result(X,Y):-X>70->Y =pass;Y =fail.
