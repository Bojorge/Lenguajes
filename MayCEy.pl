
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
identidadAvion(cessna):- avionPequeno,pista(p1).
identidadAvion(beechcraft) :- avionPequeno,pista(p1).
identidadAvion(embraerPhenom) :- avionPequeno,pista(p1).

identidadAvion(boing717):- avionMediano,pista(p2_1).
identidadAvion(embraer190) :- avionMediano,pista(p2_2).
identidadAvion(airBusA220) :- avionMediano,pista(p2_1).

identidadAvion(boing747) :- avionGrande,pista(p3).
identidadAvion(airBusA340) :- avionGrande,pista(p3).
identidadAvion(airBusA380) :- avionGrande,pista(p3).

identidadAvion(emergencia) :- emergencia.



avionPequeno:-
espacio,
write('Avion pequeño'),
nl,
write('le corresponde la pista 1'),
nl.

avionMediano:-
espacio,
write('Avion mediano'),
nl,
write('le corresponde una de las pistas p2_1 o p2_2 '),
nl.




avionGrande:-
espacio,
write('Avion grande'),
nl,
write('le corresponde la pista 3'),
nl.


pista(p1):-
espacio,
write('Tiene disponible un kilometro de pista '),
nl,
write('Necesita  ???  >>>  aterrizar/despegar -> '),
read(X),
X.

pista(p2_1):-
espacio,
write('Pista p2_1. Esta pista mide 2km y tiene una direccion de Este a Oeste'),
nl,
write('Necesita  ???  >>>  aterrizar/despegar -> '),
read(X),
X.

pista(p2_2):-
espacio,
write('Pista p2_2. Esta pista mide 2 km y tiene una direccion de Oeste a Este'),
nl,
write('Necesita  ???  >>>  aterrizar/despegar -> '),
read(X),
X.

pista(p3):-
espacio,
write('Tiene disponibles 3 kilometros de pista '),
nl,
write('Necesita  ???  >>>  aterrizar/despegar -> '),
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
write('espere por el permiso para ATERRIZAR '),
nl,
write('Puede aterrizar'),
continuar.

despegar:-
espacio,
write('espere por el permiso para DESPEGAR '),
nl,
write('Puede despegar'),
continuar.



espacio:-
nl,nl,nl,nl,nl,nl.

