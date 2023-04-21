# Ezo - Code Golf: Calculatrice par chaîne de caractères

Cette exercice m'a été fourni par EZO comme test technique en vue d'une entrevue technique.

# Réglements

Vous devez créer une application qui évalue une chaîne de caractères, comme si elle avait été entrée dans une calculatrice. Votre programme doit accepter une entrée et produire une réponse juste en sortie.

Le programme doit:
* Être écrit dans le langage orienté-objet de votre choix
* Authoriser les nombres à virgule flotante et les nombres négatifs
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
* La démarche des opérations est affiché

On peut inscrire 
* HELP : Inscrit les informations d'utilisation
* QUIT ou EXIT : Pour quitter


# Défis personnels

## Strategie de parsing : 
* Au départ elle était différente mais apportait beaucoup de problème de parsing. J’ai changé de strategie ce qui m’a aussi permi d’ajouter la démarche

## Les sqrt
* Les racines carrée ne sont pas des nombres mais se comporte comme tel dans la situation des nombres négatifs. 
* Lors des opérations, elle considéré comme des opérations mais différente
* Lors du tokenparsing, elles ne sont pas des nombres et ne sont pas des opérations
* Problème restant non traité: Lorsque deux sqrt() sont mise côte a côte, elles une multiplication est ajouté. Pourrait être réglé mais je trouvais l’idée bonne aussi. (bug → feature)

## Les doubles opérations ayant des opérations OP_SUB et OP_SQR  
* Au départ, tokenParsing traitait les nombres négatifs en exception. C’est devenu très compliqué à gérer. La fonction parseNegativeNumber a simplifié le processus.

## Makefile
* Je n’avais jamais vraiment utiliser les wildcards jusqu’à présent. Je me suis inspirer du makefile de notre projet en cours à l’école pour l’implanter dans celui-ci.

## Test unitaire
* Premier projet seul ou j’implante les tests unitaires.

## Ne pas m’emballer
* J’aurais pu faire plus mais je me suis mis une limite dès le départ et outre la démarche et un petit easter egg, j’ai respecté les objectifs que je trouvais réaliste de produire au départ.


# Architecture, fonctionnement et démonstration

https://whimsical.com/ezo-calculator-AyLnjBewy9n3qKgAehcmjW
