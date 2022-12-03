# Énoncé
⚠️ DISCLAIMER : ( Pas de moi, repris à partir de ce dépot gitlab : https://gitlab.com/vietdamien/training )

**Essayez d'éviter un maximum les copies.**

## Architecture
Le `CMakeLists.txt` fourni permet de compiler les fichiers correspondant à l'architecture suivante :
```
/
|__ include
    |__ model
        |__ // fichiers d'en-tête
    |__ tests (à ne pas toucher)
        |__ catch.hpp
|__ inline (facultatif)
    |__ model
        |__ // fichiers source séparés pour les templates 
|__ src
    |__ model
        |__ // fichiers d'implémentation
    |__ tests
        |__ catch.cpp
        |__ main_tests.cpp (les tests unitaires)
```
Pas besoin d'ajouter manuellement les fichiers `.cpp` dans le `CMakeLists.txt`, tant que les `.hpp` sont dans `include` et que les `.cpp` sont dans `src`, tout est fait automatiquement.

Les sous-dossiers `model` et `tests` sont facultatifs, mais dans le cas contraire, les inclusions de fichiers se font donc comme ceci : `#include "model/source.hpp"`.


## Test case 1 - Constructions et affectactions
### Contexte
Créer une classe `Product` avec les attributs suivants :

 - une chaîne de caractères pour le nom (`name`) ;
 - un prix en précision double (`price`) ;
 - des compteurs pour les constructions, les copies et les mouvements (`constructs`, `copies`, `transfers`) ;

Écrire les getters (qui reprennent les noms des attributs pour être iso avec la bibliothèque standard dans les tests unitaires mais rien ne vous empêche de faire du refactoring si ça vous amuse).

Implémenter les constructeurs et opérateurs d'affectation de copie et de mouvement, qui incrémentent les compteurs `constructs`, `copies` et `transfers`.

Ajouter une méthode virtuelle pure ayant la signature suivante : `std::ostream& display(std::ostream&)`.

### Implémentation de la classe abstraite
Créer une classe `Book` qui hérite de `Product` et qui contient un attribut chaîne de caractères `author`, implémenter la méthode `display()` et adapter la classe pour construire, copier et déplacer correctement les objets qui seront créés.

## Test case 2 - Polymorphisme
Par flemme, on va rajouter une classe `Item` qui représente tous les autres objets et qui hérite de `Product`, et normalement, le polymorphisme doit être en place.

## Test case 3 - Opérateurs de comparaison
Créer une classe `PriceRange` contenant deux entiers pour les bornes inférieure et supérieure de l'intervalle (`inf` et `sup`).

Implémenter les opérateurs de comparaison qui se basent en priorité sur la borne inférieure, et sur la borne supérieure en cas d'égalité.

## Test case 4 - Foncteur
Écrire le foncteur `PriceRangeGenerator` qui permet de générer un `std::vector<PriceRange>` et qui prend en arguments template :

- `Step` : le pas entre la borne inférieure actuelle et la borne inférieure suivante ;
- `Start` : la borne inférieure du premier intervalle initialisé par défaut à 0 ;
- `Count` : le nombre d'intervalles à générer initialisé par défaut à 1.

`PriceRangeGenerator<5, 0, 2>` doit renvoyer un vecteur avec les intervalles `[0, 4]` et `[5, 9]`.

## Test case 5 - Gestion des exceptions
Créer une classe `Store` template qui contient une `std::multimap<PriceRange, std::vector<ItemPtr>` où `ItemPtr` est :

 - soit un `T*`, mais vous devrez gérer la mémoire vous-même ;
 - soit un `std::unique_ptr<T>`, même si ce n'est pas forcément à l'examen.

Implémenter une méthode qui compte les éléments du vecteur pour une clé donnée et qui renvoie une exception si la clé n'existe pas.

## Test case 6 - Ajouts dans une multimap
Implémenter :

- une méthode qui prend un `PriceRange` en paramètre et qui permet d'insérer une paire (le vecteur est inintialisé à vide) ;
- une méthode qui prend un `std::unique_ptr<T>` et qui permet d'insérer l'élément de type `T` dans le vecteur correspondant au bon `PriceRange`.

## Test case 7 - Suppressions dans une multimap
Implémenter :

- une méthode dont le prototype est `void remove_key(int inf, int sup)` et qui permet de supprimer toutes les clés (et donc toutes les paires) dont le `PriceRange` correspond aux bornes passées en paramètres (voir `std::equal_range`) ;
- une méthode `remove_item` qui prend un nom de produit en paramètre et qui permet de supprimer toutes les occurrences des produits correspondants dans les vecteurs de toutes les paires (voir utilisation de `std::vector<T>::erase` et `std::vector<T>::remove_if`).

## Test case 8 - Opérateur d'affichage sur un flux de sortie
Écrire l'opérateur `operator<<(...)` pour qu'il corresponde à la sortie donnée dans les tests unitaires.
