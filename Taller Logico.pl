% Manuel Bojorge Araya : Taller funcional



% 1
madre(clara,jose).
madre(patricia,jaime).
padre(tomas,jose).
padre(tomas,isabel).
padre(jose,ana).
padre(jose,patricia).




% 2
abuelo(X,Y):-padre(X,Z),padre(Z,Y);padre(X,Z),madre(Z,Y).
abuela(X,Y):-madre(X,Z),madre(Z,Y);madre(X,Z),padre(Z,Y).

bisabuelo(X,Y):-padre(X,Z),abuelo(Z,Y);padre(X,Z),abuela(Z,Y).
bisabuela(X,Y):-madre(X,Z),abuela(Z,Y);madre(X,Z),abuelo(Z,Y).




% 3
valioso(oro).
femina(ana).
tiene(juan,oro).
papa(juan,maria).
presta(juan,libro,maria).
presta(juan,lapiz,pedro).
presta(pedro,borrador,juan).




% 4
varon(albert).
varon(edward).
mujer(alice).
mujer(victoria).
padres(edward,victoria,albert).
padres(alice,victoria,albert).

hermana(X,Y):-mujer(X),padres(X,victoria,albert),padres(Y,victoria,albert).




% 5
miembro(X,[X|_]).
miembro(X,[_|Y]):-miembro(X,Y).




% 6
inversa(L1,L2):-inversa(L1,[],L2).
inversa([],L,L).
inversa([X|L1],L2,L3):-inversa(L1,[X|L2],L3).




% 7
longitud([],0).
longitud([_|Cola],X):-longitud(Cola,Y), X is Y+1.



%8
acontecimiento(2018,fise).
acontecimiento(2019,xgames).
acontecimiento(2020,juegosolimpicos).

evento :- write('Digite la fecha: '), read(X), acontecimiento(X,Y), write(Y).



