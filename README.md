<h1 align="center">Minishell</h1>

- Display a prompt when waiting for a new command.
- Have a working history
- Search and launch the right executable (bases on the PATH variable or using a relative or an absolute path).
- Avoid using more than one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access your main data structures.

## redirections:

- < should redirect input
- > should redirect output
- << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn't have to update the history!
- >> should redirect output in append mode.

- Implement pipes the output of each command in the pipeline is connected to the input of the next command via a pipe.
- Handle environment variables ($ followed by a sequence of characters) wich should expand to their values.
- Handle $? wich should expand to the exit status of  the most recently executed foreground pipeline.
- Handle ctrl -C, ctrl -D and ctr -\ which should behave like in bash.

## In interactive mode:

- ctrl -C displays a new prompt on a new line.
- ctrl -D exits the shell.
- ctrl -\ does nothing.

## builtins:

- echo with option  -n
- cd with only a relative or absolute path
- pwd with no options
- export with no options
- unset with no options
- env with no options or arguments
- exit with no options

## TO_DO

- Parsing: Analyse et découpe la ligne de commande en tokens.
- Exécution: gestion des processus, des commandes intégrées (cd, echo, etc).
- Redirections & Pipres: gestions des >, <, |.
- Gestions des signaux: intercepter ctrl -C, ctrl -D, ctrl -\.
- Gestion de l'environnement: mise a jour des variables (env, export, etc.).

### Structure:

- Une liste chainée pour stocker les commandes et arguments.
- Un tableau de tokens pour le parsing.
- Une structure pour l'environnement (variables d'env modifiables).

### Parsing;

1) Lecture d'entrée:

	- Gestion du prompt et récupération des commandes saisies.

2) Analyse lexicale (lexer):

	- Découpage de la ligne de commande en tokens (mot, opérateurs, redirections).
	- Gestion des quotes (simple ou double).
	- Détections des opérateurs spéciaux (|, <, >, <<, >>).

3) Analyse syntaxique (parser):

	- Construction de structures de données représentant les commandes.
	- Vérification de la syntaxe (par exemple, détection d'erreurs comme "ls | |").

4) Expansion:

	- Remplacement des variables d'environnement ($USER, $PATH, etc.).
	- Gestion du code de retour ($?).

5) Préparation des données pour l'éxecution:

	- Organisation des commandes et des pipes
	- Identification des redirections.

### Exec:

1) gestion des commandes internes (builtins):

	- Implémentation de cd, echo, export, unset, env, exit.

2) Exécution des commandes externes:

	- Recherche du chemin d'exécution.
	- Création des processus fils (fork).
	- Exécution avec execve.

3) Gestion des redirections:

	- Redirections d'entré (<)
	- Redirections de sortie (>, >>)
	- Here-doc (<<)

4) Gestion des pipes:

	- Créations des tubes
	- Connexion entre les processus

5) Gestion des signaux:

	- SIGINT (CTRL + C)
	- SIGQUIT (CTRL + D)
	- CTRL + \

6) Gestion des variables d'environnement:

	- Stockage et mise a jour
	- Passage aux commandes exécutées
	- Stockage et mise a jour
	- Passage aux commandes exécutées
