;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname |taller 1|) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (miembro x lista)
  (cond ((null? lista)
         #f)
        ((equal? x (car lista))
         #t)
        (else
         (miembro x (cdr lista)))))

;;(miembro '4 '(4 2 7))

(define (eliminar x lista)
  (cond ((null? lista)
         '())
        ((equal? x (car lista))
         (cdr lista))
        (else
         (cons (car lista)
          (eliminar x (cdr lista))))))

;;(eliminar '8 '(4 2 7))

(define (menor lista)
  (cond ((null? lista)
        #f)
        (else
         (menorAux (car lista)(cdr lista)))))

(define (menorAux x lista)
  (cond ((null? lista)
         x)
        ((< (car lista) x)
         (menorAux (car lista) (cdr list)))
        (else
         (menorAux x (cdr lista)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (mayor lista)
  (cond ((null? lista)
         #f)
        (else
         (mayor-aux (car lista) (cdr lista)))))

(define (mayor-aux x lista)
  (cond ((null? lista)
         x)
        ((< x (car lista))
         (mayor-aux (car lista) (cdr lista)))
        (else
         (mayor-aux x (cdr lista)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define(pivot lista)
  (cond ((null? lista)
         #f)
        (else
         (pivot-aux (car lista)(cdr lista) '() '() ))))

(define(pivot-aux punto lista menores mayores)
  (cond((null? lista)
        (list menores mayores))
       ((<= (car lista) punto)
        (pivot-aux punto
                   (cdr lista)
                   (cons (car lista) menores)
                   mayores))
       (else
        (pivot-aux punto
                   (cdr lista)
                   menores
                   (cons (car lista) mayores)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (quick-sort lista)
  (cond ((null? lista)
         '())
        (else
         (let*
             ((punto (car lista))
              (menores-mayores (pivot lista))
              (menores (car menores-mayores))
              (mayores (cadr menores-mayores)))
           (append (quick-sort menores)
                   (list punto)
                   (quick-sort mayores))))))

;;(quick-sort '(5 4 2 7 3 1 2 2 9 6))