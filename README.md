# Objectif

Projet réalisé en groupe à l'école 42. Le but du projet : Apprendre le fonctionnement interne d'un shell et plus généralement des systèmes Unix. Le sujet demande pour cela de créer un shell similaire à Bash, permettant à un utilisateur d'interargir avec la machine par écrit.

# Fonctionnalités

Notre shell supporte les fonctionnalités suivantes :
* Opérateurs &&, || et |
* Redirection des entrées/sorties
* Edition de ligne (via l'archaïque bibliothèque Termcaps)
* Autocomplétion
* Builtins: cd, echo, help, ...
* Alias
* Historique persistant

# Dépendances

* Compilateur C (gcc, clang, ...)
* Bibliothèque `termcaps`. 
* /!\ Le shell est initialement prévu pour fonctionner sur MAC OS et avec claviers QWERTY. Des défauts de fonctionnement sont donc possibles dans d'autres conditions.

# Utilisation

```
> git clone https://github.com/ArthurCauchy/42sh.git
> cd 42sh
> make
> ./42sh
```

