
; Conta os nos de uma arvore
(defun tree_node_count (tree)
   (if (null tree) 0
       (+ 1 (tree_node_count (first (rest tree))) (tree_node_count (first (rest (rest tree)))))
   )
)

(print (tree_node_count '(5 () (8 (6 () (7 () ())) (9 () ())))))

; Infixa
(defun infix (tree)
    (if (null tree) '()
        (append (infix (first (rest tree))) (list (first tree)) (infix (first (rest (rest tree)))))
    )
)

(print (infix '(5 () (8 (6 () (7 () ())) (9 () ())))))

; Posfixa
(defun posfix (tree)
    (if (null tree) '()
        (append (list (first tree)) (posfix (first (rest tree))) (posfix (first (rest (rest tree)))))
    )
)

(print (posfix '(5 () (8 (6 () (7 () ())) (9 () ())))))

; Descobrir se eh arvore binaria de busca
(defun is_binary_tree (tree)
    (if (null tree) T
        (let* ((node (first tree))
               (esq (first (rest tree)))
               (dir (first (rest (rest tree))))
               (esq_node (first esq))
               (dir_node (first dir))
               (esq_binary (is_binary_tree esq))
               (dir_binary (is_binary_tree dir))  )

               (if esq_binary
                   (if dir_binary
                       (if (null esq_node) (if (null dir_node) T (< node dir_node))
                           (if (null dir_node) (< esq_node node) (and (< esq_node node) (< node dir_node)) )
                       )
                    NIL
                   )
                NIL
               )
         )
     )
)

(print (is_binary_tree '(5 () (8 (4 () (7 () ())) (9 () ())))))

; Achar elemento arvore de busca binaria
(defun find_tree (tree item)
    (if (null tree) NIL
        (let ((node (first tree))
              (esq (first (rest tree)))
              (dir (first (rest (rest tree))))
             )
             (if (= node item) T
                 (if (< node item) (find_tree dir item) (find_tree esq item))
             )
        )
    )
)

; Inserir na arvore
(defun insert_tree (tree item)
    (if (null tree) (list item '() '())
        (let ((node (first tree))
              (esq (first (rest tree)))
              (dir (first (rest (rest tree))))
             )
             (if (> node item) (list node (insert_tree esq item) dir) (list node esq (insert_tree dir item)))
        )
    )
)

; Metodo extrema direita
(defun extreme_right (tree)
    (let ((dir (first (rest (rest tree)))))
         (if (null dir) (first tree) (extreme_right dir))
    )
)

(print (extreme_right '(3 () (8 (6 () (7 () ())) (11 () ())))))

; Metodo extrema esquerda
(defun extreme_left (tree)
    (let ((esq (first (rest tree))))
         (if (null esq) (first tree) (extreme_left esq))
    )
)

; Metodo auxiliar para corrigir arvore esquerda de onde foi retirado item para rotacionar
(defun fix_tree_left (tree item)
     (if (null tree) '()
         (if (= (first tree) item) (first (rest tree))
             (list (first tree) (first (rest tree)) (fix_tree_left (first (rest (rest tree))) item))
         )
     )
)

; Metodo auxiliar para corrigir arvore direita de onde foi retirado item para rotacionar
(defun fix_tree_right (tree item)
     (if (null tree) '()
         (if (= (first tree) item) (first (rest (rest tree)))
             ; (fix_tree_right (first (rest tree)) item)
             (list (first tree) (fix_tree_right (first (rest tree)) item) (first (rest (rest tree))))
         )
     )
)

; Metodo principal deletar arvore
(defun delete_tree (tree item)
    (if (null tree) '()
        (let ((node (first tree))
              (esq (first (rest tree)))
              (dir (first (rest (rest tree))))
             )
             (if (eq node item)
                 (let ((ex_dir (extreme_right esq)) (ex_esq (extreme_left dir)))
                      (if (null ex_dir)
                          (list ex_esq esq (fix_tree_right dir ex_esq))
                          (list ex_dir (fix_tree_left esq ex_esq) dir)
                      )
                 )

                 (if (null esq) (list node esq (delete_tree dir item) )
                     (if (null dir) (list node (delete_tree esq item) dir)
                         (if (> node item) (list node (delete_tree esq item) dir) (list node esq (delete_tree dir item)) )
                     )
                 )
             )
        )
    )
)
