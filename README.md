# Ezo - Code Golf: Calculatrice par chaîne de caractères

Cet exercice m'a été fourni par EZO comme test en prévision d'une entrevue technique.

# Réglements fournis par Ezo

Vous devez créer une application qui évalue une chaîne de caractères, comme si elle avait été entrée dans une calculatrice. Votre programme doit accepter une entrée et produire une réponse juste en sortie.

Le programme doit:
* Être écrit dans le langage orienté-objet de votre choix
* Autoriser les nombres à virgule flottante et les nombres négatifs
* Supporter **au moins** les opérateurs de base (+, -, * et /)
* Supporter un ou plusieurs espaces entre les opérateurs et les nombres
* Respecter la priorité des opérateurs
* Avoir un code propre qui respecte les principes de programmation OO

Vous ne pouvez pas:
* Copier du code sur Internet
* Utiliser du code produit par quelqu'un d'autre

Limitation
* L'architecture doit être belle et propre
* Le code doit être beau et propre

#### Nos cas de test
| Test     | Résultat attendu |
|----------|-----------------:|
| "1+1"    | "2"              |
| "1 + 2"  | "3"              |
|"1 + -1"  | "0"              |
|"-1 - -1" | "0"              |
| "5-4"    | "1"              |
| "5\*2"   | "10"             |
|"(2+5)\*3"| "21"             |
| "10/2"   | "5"              |
|"2+2\*5+5"| "17"             |
|"2.8\*3-1"| "7.4"            |
|"2^8"     | "256"            |
|"2^8\*5-1"| "1279"           |
|"sqrt(4)" | "2"              |
|"1/0"     | Erreur\*         |

Note: D'autres cas de test peuvent être utilisés. Vous ne devez pas implémenter tous les opérations du tableau ci-dessus. Vous pouvez simplement expliquer comment vous auriez implémenté les opérateurs manquants.

# Couvert dans ce projet

La ezoCalc couvre les fonctionnalités suivantes:
* Les opérations < +, -, *, /, ^, sqrt() >
* La priorité des parenthèses et opérations est respectées
* Si vous ne mettez pas d'opérateur devant ou après une parenthèse, l'opération sera considéré une multiplication
* Vous pouvez utiliser < ans > pour récupérer le dernier résultat valide
* La démarche des opérations est affichée
* Des exceptions sont lancés en cas d'erreurs de syntax, de division par zéro, de nombre non réel (racine carrée nombre négatif) et de nombre trop grand pour un float.


On peut inscrire 
* HELP : Inscrit les informations d'utilisation
* QUIT ou EXIT : Pour quitter

## Makefile

* make run		-> Compile et lance le programme
* make goal		-> Vulgarisation du but de l'exercice
* make rules 		-> Ouvre le github des consignes de Ezo
* make test		-> Lance les tests unitaires
* make leak		-> Execute le programme avec "leaks -- atExit -- " en premice
* make valgrind		-> Execute le programme avec "valgrind --leak-check=full " en premice
* make tools		-> Affiche les outils disponibles (ceci)

# Défis personnels

## Strategie de parsing : 
* Au départ elle était différente mais apportait beaucoup de problème de parsing. J’ai changé de stratégie ce qui m’a aussi permis d’ajouter la démarche

## L'implantation de la racine carrée -> sqrt()
* Les racines carrée ne sont pas des nombres mais se comporte comme tel dans la situation des nombres négatifs. 
* Lors des opérations, elle considéré comme des opérations mais traitée de façon différente
* Lors du parsing des tokens, elles n'est pas considérée comme un nombre ou commen une opération

## Les doubles opérations ayant des opérations OP_SUB et OP_SQR  
* Au départ, tokenParsing traitait les nombres négatifs en exception. C’est devenu très compliqué à gérer. La fonction parseNegativeNumber a simplifié le processus.

## Test unitaire
* Premier projet personnel où j’implante les tests unitaires.

## Ne pas m’emballer
* J’aurais pu m'emballer et en faire plus mais je me suis fixé une limite dès le départ et outre la démarche et un petit easter-egg, j’ai respecté les objectifs que je trouvais réaliste de produire au départ.

# Architecture, fonctionnement et démonstration

https://whimsical.com/ezo-calculator-AyLnjBewy9n3qKgAehcmjW



## Démonstration

Entrée:  2(3 + -sqrt(4 + 6) ^ 3)

   2 * ( 3 + -sqrt( 10 ) ^ 3 )

  2 * ( 3 + -3.16228 ^ 3 )

  2 * ( 3 + -31.6228 )

  2 * ( -28.6228 )

-57.2456

La reponse est: -57.2456


