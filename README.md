# pipex
### Recréer le méchanisme "pipe" (tube)


<img src="documentation/Unix_pipeline_exemple.gif" width="100%" alt="animation of how pipeline work in UNIX"/>

> Animation by [Computerphile](https://www.youtube.com/watch?v=bKzonnwoR2I)

Dans ce projet, j'ai du créer un programme “pipex” qui reproduit le fonctionnement des tubes UNIX comme dans l'exemple suivant:

```bash
$> < fichier1 cmd1 | cmd2 > fichier2
```
N.B: "cmd" = une commande linux au choix: ls, grep, cat,...

Traduit en francais, voilà ce que cette suite de commandes fait:
1. on applique `cmd1` sur le contenu du **fichier1**
2. ensuite on envoie le résultat a `cmd2`
3. puis on applique `cmd2` sur le contenu reçu
4. et finalement, on écrit le résultat dans **fichier2**

parsing pour verifier que la commande existe (envp, acces())

## Ce que j'ai appris
Ce projet m'a permis d'apprendre a créer des processus, utiliser les pipes pour permettre à ces processus de communiquer entre eux, utiliser les redirections d'entrée/sortie standard et aussi comment executer des commandes shell a partir d'un programme.

## Liens utiles
Articles
- [Creating and Killing Child Processes in C](https://www.codequoi.com/en/creating-and-killing-child-processes-in-c/)
- [Pipe: an Inter-Process Communication Method](https://www.codequoi.com/en/pipe-an-inter-process-communication-method/)
- [Handling a File by its Descriptor in C](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
- [Errno and Error Management in C](https://www.codequoi.com/en/errno-and-error-management-in-c/)
- [Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)

Vidéos
- [Unix Processes in C](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY) (Playlist)
- [fork()](https://www.youtube.com/watch?v=xVSPv-9x3gk), [dup()](https://www.youtube.com/watch?v=EqndHT606Tw) et [pipe()](https://www.youtube.com/watch?v=uHH7nHkgZ4w) expliqué simplement

Testeur
- [PIPEX EXAMINATOR](https://github.com/mariadaan/PIPEXaminator)
