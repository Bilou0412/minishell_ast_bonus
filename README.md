
# Mini-Shell

Le but du projet est de créer un mini-shell simplifié sans toutes ses fonctionnalités complètes.

## Objectif du Projet

Le but est d'exécuter les fonctions dans un ordre précis. Pour cela, nous devons créer un arbre binaire. La création de cet arbre binaire requiert une étape préliminaire de tokenization, qui consiste à découper la chaîne de commandes en tokens distincts. Afin de réaliser cette tokenization, nous devons d'abord procéder au processus de lexicographie, qui consiste à attribuer un type à chaque token identifié (tout simplement définir quels pourraient être ces tokens).

Nous suivrons ensuite la grammaire établie, sans aller plus loin que les commandes. Tout ce qui reste fera partie intégrante des commandes et sera utilisé pour les exécuter ultérieurement.

## Fonctionnalités à Implémenter

- `>>` : append file
  - Lorsque vous utilisez `ps aux >> file`, la sortie de `ps aux` sera ajoutée à "file". Si "file" existe déjà, son contenu précédent sera conservé et la sortie de `ps aux` sera ajoutée après son contenu existant.

- `>` : clobber file
  - Lorsque vous utilisez `ps aux > file`, la sortie de `ps aux` écrasera "file". Si "file" existe déjà, son contenu sera remplacé par la sortie de `ps aux`.

- `<<` : here_doc
  - Lancez le programme spécifié à gauche de l'opérateur, par exemple `cat` (comme `cat << EOF`).
  - Récupérez les entrées de l'utilisateur, y compris les sauts de ligne, jusqu'à ce que la condition spécifiée à droite de l'opérateur soit rencontrée sur une seule ligne, par exemple `EOF`.
  - Envoyez tout ce qui a été lu, à l'exception de la valeur `EOF`, à l'entrée standard du programme à gauche.

- `<` : redirection d'entrée
  - Dans un shell, le symbole `<` est utilisé pour la redirection d'entrée, permettant le contenu d'un fichier d'être utilisé comme entrée pour un programme.

- `|` : pipe
  - Chaque commande nécessite une entrée standard et renvoie une sortie.
  - Le `|` permet à la sortie d'une commande de servir d'entrée à une autre commande.

- `&&` : et logique
  - Utilisé pour exécuter une commande uniquement si la commande précédente a réussi.

- `||` : ou logique
  - Utilisé pour exécuter une commande si la commande précédente a échoué.



## Grammaire

```
<minishell> ::= <pipeline>
    | <pipeline> ('&&' | '||') <minishell>
<pipeline> ::= <command>
   | <command> '|' <pipeline>
<command> ::= <simple_command>
  | <redirection_command>
<simple_command> ::= <cmd_word>
         | <cmd_word> <arguments>
<redirection_command> ::= <cmd_word> <redirection> <filename>
<redirection> ::= '>' | '<'
<cmd_word> ::= <string>
<arguments> ::= <string> | <string> <arguments>
<string> ::= <char> | <char> <string>
<char> ::= any valid character
```

## Parsing

En utilisant la grammaire fournie, vous pouvez construire un arbre syntaxique abstrait (AST) en suivant cette logique de parcours récursif :

1. Définissez une structure d'arbre pour les nœuds de commande, en tenant compte des détails de chaque commande, y compris les redirections et les arguments.
2. Implémentez une fonction principale pour analyser l'entrée de l'utilisateur, par exemple `parseMinishell`.
3. Identifiez les pipelines et les opérateurs logiques, en créant des nœuds pour chaque opérateur et en appelant récursivement la fonction d'analyse pour les parties gauche et droite de l'opérateur.
4. Gérez les commandes simples et les tuyaux en conséquence, en créant des nœuds pour chaque opérateur et en descendant dans l'arbre en appelant les fonctions d'analyse appropriées.

En suivant ces étapes, vous pourrez construire un AST respectant la grammaire définie, ce qui vous permettra de gérer les commandes et les opérations de manière efficace dans votre mini-shell.


## Exécution

Si vous souhaitez implémenter une logique pour cette grammaire sans créer un AST qui descend jusqu'au niveau le plus bas des commandes, vous pouvez suivre une approche de parcours récursif des règles de la grammaire pour évaluer et exécuter la commande donnée. Voici une approche générale que vous pouvez suivre :

1. Définissez des fonctions pour chaque règle de la grammaire. Par exemple, vous pouvez avoir des fonctions comme `executeMinishell`, `executePipeline`, `executeCommand`, etc.

2. Commencez par la fonction `executeMinishell` qui sera votre point d'entrée. Cette fonction appellera d'autres fonctions en fonction de la structure de la grammaire.

3. Implémentez des fonctions pour chaque règle de la grammaire. Par exemple, dans la fonction `executePipeline`, évaluez les commandes et les opérateurs logiques `|` en parcourant les jetons. Exécutez les commandes en fonction de la structure identifiée.

4. Utilisez la récursivité pour parcourir les sous

-commandes et évaluer les expressions en fonction de la grammaire.

5. Gérez les opérateurs logiques `&&` et `||` pour exécuter les commandes en fonction de la logique des opérateurs logiques définie par la grammaire.

En utilisant cette approche, vous pouvez évaluer et exécuter les commandes en parcourant les jetons de la liste chaînée et en identifiant la structure de la commande en fonction des règles de la grammaire. Assurez-vous de gérer les cas d'erreur et de validation pour garantir que la logique d'exécution reflète correctement la structure syntaxique de la commande.