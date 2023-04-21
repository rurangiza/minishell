# Bugs
- ls | export <argument> : should not print anything

## To-do
- export : verifier si le premier element de l'argument est un nombre, il ne peut y avoir que des lettres (minuscules et maj), des chiffres ou des _.
	- verifier aussi pourles += ' ' & " " : 
- gerer les "|pipe" , marche quand il y a deja un caractere avant le |. 
- pipe : verifier quand les commandes snt collees (sans espaces)

## Done
- unset : verifier si la commande est valide avant de voir si il est deja dans l'env 
- cd ~ , il doit faire plus que revenir au HOME, il doit pouvoir naviguer egalement. 






[x] ls | echo hello | cat
	-> output   : ls
	-> expected : "hello"
[x] echo hello | echo miss
	-> output   : nothing
	-> expected : "miss"
	= first built-in changed stdout, and last enherited that than printed on the changed stdout
		-> initialized stdout to original in all built-in cmd except first cmd in pipeline