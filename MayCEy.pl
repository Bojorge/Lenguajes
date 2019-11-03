
inicio:-
espacio,
write('Hola soy MayCEy'),
nl,
write('*  Si necesita ayuda  *  >>>  IDENTIFIQUESE : '),
read(X),
identidadAvion(X).

continuar:-
espacio,
write('¿algo mas? >>> s/n'),
read(X),
( (X == s)
->
ayuda ;
finalizar).

ayuda:-
espacio,
write('¿que necesita?'),
read(X),
X.

finalizar:-
espacio,
write('fue un gusto ayudarle, adios. '),
espacio,
write(' * * *  ...  * * *  ...  * * * '),
inicio.

/*identidad del avion para asignarle una pista*/
identidadAvion(beechcraft) :-  beechcraft, !.
identidadAvion(boing717) :- boing717, !.
identidadAvion(a340) :-  a340, !.
identidadAvion(emergencia) :- emergencia, !.



beechcraft:-
espacio,
write('le corresponde la pista 1'),
nl,
p1.

boing717:-
espacio,
write('le corresponde una de las pistas 2A o 2B '),
nl,
nl,
write('Necesita  ???  >>>  aterrizar/despegar : '),
read(X),
X,
p2_1.

a340:-
espacio,
write('le corresponde la pista 3'),
nl,
p3.


p1:-
espacio,
write('Tiene disponible un kilometro de pista '),
nl.


p2_1:-
espacio,
write('Tiene disponibles 2 kilometros de pista '),
nl,
write('Esta pista tiene una direccion de Este a Oeste'),
continuar.

p2_2:-
espacio,
write('Tiene disponible 2 kilometros de pista '),
nl,
write('Esta pista tiene una direccion de Oeste a Este').



p3:-
espacio,
write('Tiene disponibles 3 kilometros de pista ').


emergencia :-
espacio,
write('¿Cual es su emergencia? '),
read(X),
X.



secuestro:-
espacio,
write('llamare a la policia para que se encargue del secuestro'),
nl,
continuar.


nocombustible:-
espacio,
write('buscaremos una pista para que aterrice lo mas pronto posible'),
nl,
continuar.


aterrizar:-
espacio,
write('Tiene permiso para aterrizar en la pista indicada al inicio '),
continuar.

despegar:-
espacio,
write('Tiene permiso para despegar en la pista indicada al inicio '),
continuar.



/* how to ask questions */
preguntar(Question) :-
write('Usted quiere '),
write(Question),
nl,
read(Response),
nl,
( (Response == y)
->
assert(yes(Question)) ;
assert(no(Question)), fail).

:- dynamic yes/1,no/1.

/*How to verify something */
verificar(S) :-
(yes(S)
->
true ;
(no(S)
->
fail ;
preguntar(S))).
/* undo all yes/no assertions*/
undo :- retract(yes(_)),fail.
undo :- retract(no(_)),fail.
undo.


espacio:-
nl,nl,nl,nl,nl,nl.

