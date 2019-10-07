;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |taller 1|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #t #t none #f () #f)))



;;funcion que recibe un numero y devuelve su factorial
(define (factorial x)
  (cond ((equal? 0 x)
        1)
        (else
         (* x (factorial (- x 1))))))
  

;;(factorial 5)

;;funcion que recibe un numero y devuelve el elemento de la sucesion de fibonacci
;;en la posicion indicada por numero ingresado como parametro
(define (fibonacci x)
  (cond ((or(equal? x 0) (equal? x 1))
         1)
        (else
         (+ (fibonacci (- x 2)) (fibonacci (- x 1))))))

;;(fibonacci 0)

;;funcion que recibe un simbolo y una lista
;;se busca el elemento en la lista y si esta retorna #t sino #f
(define (miembro x lista)
  (cond ((null? lista)
         #f)
        ((equal? x (car lista))
         #t)
        (else
         (miembro x (cdr lista)))))

;;(miembro 8 '(1 2 3 4 5))

;;funcion que recibe un numero y una lista
;;si el elemento esta, lo elimina si no retorna #f
(define (eliminar x lista)
  (cond ((null? lista)
         '())
        ((equal? x (car lista))
         (cdr lista))
        (else
         (cons (car lista) (eliminar x (cdr lista))))))

;;(eliminar 0 '(1 2 3 4 5 6 7 8 9))

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

;;funcion que recibe la lista a ordenar
(define (quickSort lista)
  (cond ((null? lista)
         '())
        (else
         (ordenar (cdr lista) (car lista) '() '()))))

(quickSort '(1 6 8 0 2 4 3 9 5 7)) 
        