
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
write('le corresponde una de las pistas 2A o 2B '),
nl,
nl,
write('Necesita  ???  >>>  aterrizar/despegar : '),
read(X),
X,
p2_1.

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
write('Esta pista mide 2km y tiene una direccion de Este a Oeste'),
nl,
write('Necesita  ???  >>>  aterrizar/despegar : '),
read(X),
X.

p2_2:-
espacio,
write('Esta pista mide 2 km y tiene una direccion de Oeste a Este'),
nl,
write('Necesita  ???  >>>  aterrizar/despegar : '),
read(X),
X.



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


aterrizar:-
espacio,
write('Tiene permiso para aterrizar en la pista correspondiente '),
continuar.

despegar:-
espacio,
write('Tiene permiso para despegar en la pista correspondiente '),
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

