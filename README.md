================================================================================
                             PROJET OCR
                    Equipe PA2_G1 - Promotion 2030
================================================================================

1. COMPILATION
--------------
Pour compiler l'ensemble des modules du projet, executez a la racine :

    make

Pour nettoyer les fichiers objets et binaires :

    make clean


2. UTILISATION DES MODULES
--------------------------

A. Solveur de grille (Solver)
   Recherche un mot dans une grille fournie sous forme de fichier texte.
   
   Syntaxe :
       ./solver <fichier_grille> <mot>

   Exemple :
       ./solver tests/grid.txt HELLO


B. Reseau de neurones (OCR / MLP)
   Lance l'entrainement et le test du reseau sur la porte non-lineaire XNOR,
   puis sauvegarde et charge le modele entraine.

   Syntaxe :
       ./nn


C. Traitement d'image (Image Processing)
   Execute le pretraitement visuel complet sur une image (niveaux de gris,
   binarisation par Otsu et suppression des bruits parasites).

   Syntaxe :
       ./test_binarization <chemin_image>

   Exemple :
       ./test_binarization tests/image.png
================================================================================