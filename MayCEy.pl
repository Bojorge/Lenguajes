
inicio:-
write('identifiquese '),
read(X),
identidadAvion(X),
write('en que le puedo ayudar '),
read(Y),
emergencia(Y),
undo.


/*identidad del avion para asignarle una pista*/
identidadAvion(beechcraft) :-  beechcraft, !.
identidadAvion(boing717) :- boing717, !.
identidadAvion(a340) :-  a340, !.



beechcraft:-
write('le corresponde la pista 1'),
p1.

boing717:-
write('le corresponde la pista 2 '),
p2.

a340:-
write('le corresponde la pista 3'),
p3.


p1:-
verificar(aterrizar),
verificar(despegar).


p2:-
verificar(aterrizar),
verificar(despegar).


p3:-
verificar(aterrizar),
verificar(despegar).

emergencia(secuestro):- secuestro.


secuestro:-
write('llamare a la policia para que se encargue del secuestro').



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




