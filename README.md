# README Projet informatique SEI SICOM, assembleur Python

## Rappel sur les rendus
Les rendus de chaque incrément et le rendu final sont attendus sur Git.

C'est l'état du dépôt sur le serveur à la date du rendu qui fait foi.

Aucun rendu par mail !

Pour l'examen, il est nécessaire que votre code compile et fonctionne sur les machines Phelma sous Linux.


## Contenu attendu pour votre dépot Git

Votre dépôt Git devra contenir a minima :
* Un fichier `README.md` à la racine (ce fichier, à mettre à jour en ajoutant une section à chaque incrément), qui explique brièvement l'état du code, comment le compiler, comment l'exécuter, comment tester vos programmes ;
* Un fichier `Makefile` qui permet de compiler avec la commande make (conserver et utiliser celui fourni) ;
* Votre code source, organisé en sous-répertoires. Les fichiers `.c` contenant les programmes principaux attendus (livrables) seront plaçés dans le un sous-répertoire nommé `progs` ;
* Tous vos programmes principaux de test et les informations indiquant tous les tests que vous avez réalisés, dans le répertoire `tests` (voir les exemples fournis) ;
* Les autres fichiers nécessaires au fonctionnement de votre projet - typiquement le fichier de description des lexèmes, etc.

A l'inverse, un dépôt `git` ne doit PAS contenir :
* les fichiers binaires objet `.o` et les binaires exécutables : ils sont régénérés à chaque fois !

Le fichier `.gitignore` fourni à la racine du dépôt permet déjà que tous les fichiers objet `.o` ou et tous les fichiers d'extension `.exe` soient ignorés par `git`. Vous pouvez modifier / étendre ce fichier si besoin.

## Structure typique du dépôt

Nous conseillons de vous inspirer de l'arborescence suivante pour votre dépot git :

```bash
Racine du dépôt git
  |_ .gitignore : le fichier <gitignore>
  |_ README.md : ce README (à mettre à jour !)
  |_ Makefile : le fichier qui permet de tout compiler facilement (exécutable final, tests...)
  |_ include/pyas
     |_ tous les fichiers header .h de votre projet
  |_ src    
     |_ tous les fichiers source .c - sauf les programmes principaux et les tests
  |_ progs
     |_ les programmes principaux à livrer, i.e. les fichiers .c contenant les divers main()
  |_ tests
     |_ les fichiers source .c de tous les main de test
            et les éventuelles données  nécessaires à ces tests
      |_ howto
          |_ la documentation de l\'outil unitest.c fourni pour les tests
  |_ test-data
     |_ les fichiers éventuels nécessaires à vos test
         (typiquement les fichiers de données et oracles)
```

Notez que les éléments de code fournis ("*bootstrap*", voir site WWW du projet) respectent cette structure attendue pour votre dépot `git`. Comme vous avez décidément tout intérêt à vous y conformer (en plus de gagner instantément en efficacité et en précision), les sections ci-dessous expliquent donc comment utiliser le code fourni.


## Comment travailler

Tout de passe dans le répertoire du bootstrap fourni :
```bash
$ cd bootstrap
bootstrap$
```

Si vous avez une machine (virtuelle ou pas) sous *Ubuntu*, assurez-vous d'avoir tous les paquets installés (nécessite le droit d'administrer cette machine, vous n'avez pas à exécuter cette commande sur les machines de l'école) :

```bash
bootstrap$ make my-box-stylish
```

Ensuite il faut paramétrer les logiciels, là tout le monde doit le faire une fois sur chaque machine utilisée pour le projet :

```bash
bootstrap$ make pimp-my-ride && source ~/.bashrc
```

L'installation des logiciels est alors terminée.

Sauf pour créer les programmes du rendu, vous êtes censé mettre au point votre code à travers des tests. Un module `foo` est réputé être constitué des fichiers :
* `src/foo.c` (son code source),
* `include/pyas/foo.h` (son interface) et
* `tests/test-foo.c` (son test).

Idéalement, pour éviter d'être juge et partie et ainsi gagner en robustesse de développement, deux personnes participent à la mise au point d'un même module :
1. Elles (re)définissent ensemble l'interface `include/pyas/foo.h`, puis, séparément :
2. L'une d'elles définit et écrit le test `tests/test-foo.c` ;
3. L'autre écrit le code du module `src/foo.c` ;
4. Et elles rebouclent tant que les tests ne passent pas.

Voir par exemple les ébauches des modules `list` et `regexp` fournies, et notamment la construction de leurs tests.

Le système de test lui-même est documenté par l'exemple dans les `tests/howto/*.c*`, par fonctionnalités allant graduellement des plus basiques (au moins `01_test-examples-pass.c` et `02_test-examples-fail.c` sont à comprendre et à utiliser dans ce projet) aux plus ésotériques (`ZZ_test-implementation-*.c`, qui nécessitent déjà un certain entraînement avant d'en tirer pleinement profit).

Pour (re)compiler et déboguer un test (99.99% de votre activité) :
* Dans VSCode, cliquez sur le code source de `tests/test-foo.c` et appuyez sur F5 ;
* Ou, dans un terminal, entrez la commande :

```bash
bootstrap$ make tests/test-foo.exe@debug
```

Vous ne devriez pas tarder à vous rendre compte qu'il est beaucoup plus facile, efficace et précis d'utiliser `make` dans un terminal, plutôt que passer son temps à cliquer sur le bon fichier à tester et appuyer sur F5... Les lignes ci-dessous tentent de vous en convaincre en listant les quelques autres commandes dont vous aurez besoin (en plus de celles de `git`).

Pour (re)compiler *un* test et l'exécuter dans `valgrind` :

```bash
bootstrap$ make tests/test-foo.exe@runtest
```

Pour (re)compiler et exécuter tous les tests à la suite (sans `valgrind` ni le débogueur) :

```bash
bootstrap$ make runtests
````

Pour (re)compiler et exécuter tous les tests à la suite dans `valgrind` :

```bash
bootstrap$ make checks
````

Pour compiler les tests et les programmes à rendre :

```bash
bootstrap$ make
```

Pour faire le ménage (typiquement avant un `git push`, après un `git pull`, et aussi souvent que vous le voulez en fait) :

```bash
bootstrap$ make clean
```

Note : Si vous préférez `AddressSanitizer` à `valgrind`, vous ne pourrez travailler que depuis un terminal car il faut ajouter la définition `with=asan` aux invocations de `make` ci-dessus. Par exemple :

```bash
bootstrap$ make tests/test-foo.exe@debug with=asan
```

# Et pour les utilisateurs de MacOS ?

Quelques efforts ont été fournis dans le bootrap pour que les utilisateurs de MacOS puissent se passer de la machine virtuelle pour les tâches les plus courantes. 

Ainsi, sous MacOS, dès lors que vous avez installé les *Command Line Tools* (voir la documentation Apple ou [ici](https://osxdaily.com/2024/09/30/how-install-command-line-tools-macos-sonoma/)) ainsi que VSCode (*cf.* les nombreuses documentations en ligne ou [ici](https://code.visualstudio.com/docs/setup/mac)), vous devriez pouvoir : 
* compiler / exécuter votre code depuis VSCode ;
* compiler et exécuter votre code depuis le terminal grâce au `Makefile` fourni ;
* et donc notamment exécuter les tests écrits avec l'outil `UniTest`. 

Attention toutefois : 
* Ces fonctionnalités sont expérimentales sous MacOS. Elles ne sont *pas* garanties ! 
* Il n'existe pas de distribution de `valgrind` pour MacOS. Donc, par exemple, pas de `make tests@check`. Sous MacOS tentez plutôt d'utiliser `AddressSanitizer` (*cf.* la fin de la section précédente). 
* Si votre version de MacOS est récente, vous ne pourrez pas installer `python2` (plus disponible sur les versions récentes de MacOS), générez vos fichiers de test Python sur les machines de l'école.

Compte tenu de ces limitations, il est fortement conseillé aux utilisateurs de MacOS d'avoir une machine Linux Phelma ou une machine virtuelle Linux à portée de main : Ubuntu demeure l'environnement de travail de référence.

