# Projet OCR - Résolution de Mots Croisés

**Équipe :** PA2_G1 — **Promotion :** 2030

---

## 1. Compilation

Pour compiler l'ensemble des modules du projet, exécutez à la racine :

```bash
make
```

Pour nettoyer les fichiers objets et binaires :

```bash
make clean
```

---

## 2. Utilisation des Modules

### A. Solveur de grille (Solver)
Recherche un mot dans une grille fournie sous forme de fichier texte.

* **Syntaxe :**
  ```bash
  ./solver <fichier_grille> <mot>
  ```
* **Exemple :**
  ```bash
  ./solver tests/grid.txt HELLO
  ```

---

### B. Réseau de neurones (OCR / MLP)
Lance l'entraînement et le test du réseau sur la porte non-linéaire XNOR, puis sauvegarde et charge le modèle entraîné.

* **Syntaxe :**
  ```bash
  ./nn
  ```

---

### C. Traitement d'image (Image Processing)
Exécute le prétraitement visuel complet sur une image (niveaux de gris, binarisation par Otsu et suppression des bruits parasites).

* **Syntaxe :**
  ```bash
  ./test_binarization <chemin_image>
  ```
* **Exemple :**
  ```bash
  ./test_binarization tests/image.png
  ```