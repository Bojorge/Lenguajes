
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
identidadAvion(cessna) :- cessna, !.
identidadAvion(beechcraft) :-  beechcraft, !.
identidadAvion(embraerPhenom) :- embraerPhenom, !.

identidadAvion(boing717) :- boing717, !.
identidadAvion(embraer190) :- embraer190, !.
identidadAvion(airBusA220) :- airBusA220, !.

identidadAvion(boing747) :- boing747, !.
identidadAvion(airBusA340) :-  airBusA340, !.
identidadAvion(airBusA380) :- airBusA380, !.

identidadAvion(emergencia) :- emergencia, !.

avionPequeno:-
espacio,
write('Avion pequeño'),
nl,
write('le corresponde la pista 1'),
p1.

avionMediano:-
espacio,
write('Avion mediano'),
nl,
write('le corresponde una de las pistas p2_1 o p2_2 '),
nl,
(yes(p2_1)
->
p2_1 ;
(nl,
nl,
p2_2)).




avionGrande:-
espacio,
write('Avion grande'),
nl,
write('le corresponde la pista 3'),
nl,
p3.


cessna:-
avionPequeno.

beechcraft:-
avionPequeno.

embraerPhenom:-
avionPequeno.

boing717:-
avionMediano.

embraer190:-
avionMediano.

airBusA220:-
avionMediano.

boing747:-
avionGrande.

airBusA340:-
avionGrande.

airBusA380:-
avionGrande.


p1:-
espacio,
write('Tiene disponible un kilometro de pista '),
nl,
write('Necesita  ???  >>>  aterrizar/despegar : '),
read(X),
X.


p2_1:-
espacio,
%assertz(p2_1),
write('Pista p2_1. Esta pista mide 2km y tiene una direccion de Este a Oeste'),
nl,
write('Necesita  ???  >>>  aterrizar/despegar : '),
nl,
read(X),
( X==aterrizar
->
aterrizar(p2_1);
despegar(p2_1)).


p2_2:-
espacio,
%assertz(p2_2),
write('Pista p2_2. Esta pista mide 2 km y tiene una direccion de Oeste a Este'),
nl,
write('Necesita  ???  >>>  aterrizar/despegar : '),
nl,
read(X),
( X==aterrizar
->
aterrizar(p2_2);
despegar(p2_2)).

p3:-
espacio,
write('Tiene disponibles 3 kilometros de pista '),
nl,
write('Necesita  ???  >>>  aterrizar/despegar : '),
read(X),
X.


emergencia :-
espacio,
write('¿Cual es su emergencia? '),
read(X),
X.



secuestro:-
espacio,
write('llamare a la policia para que se encargue del secuestro'),
continuar.


nocombustible:-
espacio,
write('buscaremos una pista para que aterrice lo mas pronto posible'),
continuar.


aterrizar(Pista):-
espacio,
write('espere por el permiso para ATERRIZAR '),
espacio,
verificar(Pista).

despegar(Pista):-
espacio,
write('espere por el permiso para DESPEGAR '),
espacio,
verificar(Pista).


/* how to ask questions */
confirmar(Pista) :-
write('  ¿ok?  >>>  '),
read(Response),
nl,
( (Response == ok)
->
assert(no(Pista)),
continuar;
assert(yes(Pista)),
write('NO se usara la pista '),
write(Pista),
continuar).

:- dynamic no/1,yes/1.

/*How to verify something */
verificar(Pista) :-
(yes(Pista)
->
write('Puede utilizar la pista '),
write(Pista),
confirmar(Pista);
(no(Pista)
->
(espacio,
write('la pista '),
write(Pista),
write(' esta ocupada '),
nl,
write(' * Se le asignara otra * '),
asignar(Pista)))).


asignar(Pista):-
(Pista==p2_1
->
(yes(p3)
->
write(' puede usar p3 '),
verificar(p3);
write(' todas las pistas estan ocupadas '));
write(' estan ocupadas las pistas '),
inicio).



/* undo all yes/no assertions*/
undo :- retract(yes(_)),fail.
undo :- retract(no(_)),fail.
undo.


espacio:-
nl,nl,nl,nl,nl,nl.

%:- dynamic p1/0,p2_1/0,p2_2/0,p3/0.
