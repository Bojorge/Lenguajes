;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |taller 1|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #t #t none #f () #f)))

;; 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;funcion que recibe un numero y devuelve su factorial
(define (factorial x)
  (cond ((equal? 0 x)
        1)
        (else
         (* x (factorial (- x 1))))))
  

;; 2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;funcion que recibe un numero y devuelve el elemento de la sucesion de fibonacci
;;en la posicion indicada por numero ingresado como parametro
(define (fibonacci x)
  (cond ((or(equal? x 0) (equal? x 1))
         1)
        (else
         (+ (fibonacci (- x 2)) (fibonacci (- x 1))))))


;; 3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;funcion que recibe un simbolo y una lista
;;se busca el elemento en la lista y si esta retorna #t sino #f
(define (miembro x lista)
  (cond ((null? lista)
         #f)
        ((equal? x (car lista))
         #t)
        (else
         (miembro x (cdr lista)))))


;; 4
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;funcion que recibe un numero y una lista
;;si el elemento esta, lo elimina si no retorna #f
(define (eliminar x lista)
  (cond ((null? lista)
         '())
        ((equal? x (car lista))
         (cdr lista))
        (else
         (cons (car lista) (eliminar x (cdr lista))))))


;; 5
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;funcion que se encarga de ordenar los elementos de una lista usando el algoritmo quicksort
(define (ordenar lista pivote menores mayores)
  (cond ((and (null? lista) (and (null? menores) (null? mayores)))
         (append menores (cons pivote mayores)))
        
        ((and (null? lista) (null? menores))
         (append menores
                 (cons pivote (ordenar (cdr mayores)
                  (car mayores)
                  '()
                  '()))))

         ((and (null? lista) (null? mayores))
         (append (ordenar (cdr menores) 
                  (car menores)
                  '()
                  '())
                 (cons pivote mayores)))

         ((null? lista)
          (append (ordenar (cdr menores)
                  (car menores)
                  '()
                  '())
                 (cons pivote (ordenar (cdr mayores)
                  (car mayores)
                  '()
                  '()))))
        
         ((<= (car lista) pivote)
         (ordenar (cdr lista)
                  pivote
                  (cons (car lista) menores)
                  mayores))
        (else
         (ordenar (cdr lista)
                  pivote
                  menores
                  (cons (car lista) mayores)))))

;;funcion que recibe la lista a ordenar por quicksort
(define (quickSort lista)
  (cond ((null? lista)
         '())
        (else
         (ordenar (cdr lista) (car lista) '() '()))))



;; 6
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;funcion que recube dos listas y devuelve otra lista con pares (atributo, valor)
(define  (wrapper lista1 lista2)
  (cond ((or (null? lista1) (null? lista2))
         '())
        (else
         (cons (list (car lista1) (car lista2)) (wrapper (cdr lista1) (cdr lista2))))))



;; 7
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;funcion para eliminar un elemento de un arbol binario
(define (eliminarNodo x arb)
  (cond ((null? arb)
         '())
        ;;se inicia la busqueda del nodo
        ((< x (raiz arb))
         (arbol (raiz arb)
                (eliminarNodo x (hijo-izq arb))
                (hijo-der arb)))
        ((> x (raiz arb))
         (arbol (raiz arb)
                (hijo-izq arb)
                (eliminar x (hijo-der arb))))
        ;;el nodo no tiene hijos
        ((and (null? (hijo-izq arb))
              (null? (hijo-der arb)))
         '())
        ;;el nodo no tiene hijo-izq
        ((null? (hijo-izq arb))
         (hijo-der arb))
        ;;el nodo no tiene hijo-der
        ((null? (hijo-der arb))
         (hijo-izq arb))
        ;;el nodo tiene dos hijos
        (else
         (arbol ((raiz (mayorNodo (hijo-izq arb)))
                ((eliminarNodo (mayorNodo (hijo-izq arb))
                              (hijo-izq arb)))
                (hijo-der arb))))))

;;funciones auxiliares para eliminar trabajar con arboles
(define (arbol centro izq der)
  (cond ((and (null? izq)
              (null? der))
         centro)
        (else
         (list centro izq der))))
;;;;;;;;;;;;;;;
(define (mayorNodo arb)
  (cond ((null? arb)
         #f)
        ((null? (hijo-der arb))
         (raiz arb))
        (else
         ((mayorNodo (hijo-der arb))))))
;;;;;;;;;;;;;;;;
(define (atom? x)
  (not (list? x)))
;;;;;;;;;;;;;;;;
(define (raiz arb)
  (cond ((atom? arb)
         arb)
        (else
         (car arb))))
;;;;;;;;;;;;;;;
(define (hijo-izq arb)
  (cond ((atom? arb)
         '())
        (else
         (cadr arb))))
;;;;;;;;;;;;;;;
(define (hijo-der arb)
  (cond ((atom? arb)
         '())
        (else
         (caddr arb))))



;; 8
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;funcion para rutas "anchura primero" de un grafo
(define (anchuraPrimero ini fin grafo)
  (anchuraPrimeroAux (list (list ini)) fin grafo '()))


(define (anchuraPrimeroAux rutas fin grafo total)
  (cond ((null? rutas)
         (map reverse total))
        ((solucion? fin (car rutas))
         (anchuraPrimeroAux (cdr rutas)
                            fin
                            grafo
                            (cons (car rutas) total)))
        (else
         (anchuraPrimeroAux (append
                             (cdr rutas)
                             (extender (car rutas) grafo))
                            fin
                            grafo
                            total))))

;;crea nuevas trayectorias si no lo puede hacer devuelve #f
(define (extender ruta grafo)
  (apply append
         (map (lambda(x)
                (cond ((miembro x ruta) '())
                      (else (list (cons x ruta)))))
              (vecinos (car ruta) grafo))))

;;se obtiene una solucion cuando se ha llegado al nodo destino
(define (solucion? fin ruta)
  (equal? fin (car ruta)))
  
;;retorna los vecinos inmediatos
(define (vecinos x grafo)
    (cond ((equal? (assoc x grafo) #f)
           '())
          (else
           (cadr (assoc x grafo)))))
         
;;grafo de prueba
(define graph '((i(a b))
                (a (i c d))
                (c (a b x))
                (d (a b f))
                (x (c))
                (f(d))))


;; PRUEBAS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;(factorial 5)

;;(fibonacci 9)

;;(miembro 8 '(1 2 3 4 5))

;;(eliminar 0 '(1 2 3 4 5 6 7 8 9))

;;(quickSort '(1 6 8 0 2 4 3 9 5 7))

;;(wrapper '(tipo marca modelo color AC transmision) '(hatchback suzuki forza rojo si manual))

;;(eliminarNodo 14 '(10 (5 3 8) (15 14 18)))

(anchuraPrimero 'i 'f graph)