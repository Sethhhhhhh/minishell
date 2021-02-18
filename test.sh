#! /bin/sh

#########Cmd and Args#########
echo bonjour
        echo echo hey
echo bonjourheybonjour salut
ls -l -R -a
echo -n bonjour coucou
pwd
cd ..
cd..
ls -l
#########Protections#########
'echo' "bonjour" "wesh"
e"ch"o bonjour
       'ech'o bonjour
#echappement tout seul
echo \hey
ech\o bonjour
echo b\onjour
ech\o bonjour
echo \$PATH
echo \\\\coucou
echo \\coucou
echo \"bonjour""
echo \'\'\''' bonjour "" | cat -e
e\c\h\o b\on\njour
#doubles quotes
"" "" echo minishell
""echo minishell
"ec''ho" bonjour
"ec'''ho" bonjour
echo "\\"
echo "" coucou | cat -e ## on dirait que y a un espace en trop
echo bon""jour
echo """""mdrr"
echo ''""
echo ''""''
echo """"bonjour"" "" | cat -e
"echo bonjou"""r
"echo""" ''bonjour # y a un espace après echo dans arg[0]
ls "-lR""-a"
echo bonjour 1>"hey" pas normal
echo bonjour 1> "wesh alors" hey
echo bonjour 1>'' pas normal
echo "" mdr "" | cat -e
echo bonjour 1>'"' pas normal
echo bonjour 1> "hey""" pas normal
echo bonjour 1> "hey"'' pas normal
echo bon"jo\"u"r
echo bon"jo\\"u"r"
echo bon"jo\"\"\"\$u"r
echo bon"jo\"\"\"\$u\\\$"r
echo bon"jo\"''\"\"\'$u\\'\$"r
echo b"\ \ \ onjour"
echo "b\on\j\our"
echo "b\\onjour\\"
"$'PATH'"
"echo '\$HOME'"
"echo ' \"\$HOME\" '"
"echo \"'\$HOME'\""
"echo \" '\$PWD' \\\"\$PWD\\\" '\$PWD' \"" "echo \"\\\$HOME\""
"echo \"'\$'\""
"echo \\\\\n"
echo\" bonjour\"
echo "mdrrr >coucou >> ceci n'est pas une redirection"
#simples quotes
'$PATH'
'$\PATH'
'' echo minishell
'echo "$HOME"'
echo co'c"o"u'
'echo" bonjour"'
echo 'cou""c""ou"'
echo bo'njou\r'
echo 'cou\"\"\\c""ou"'
echo '      cou    "cou"'
echo bo'njou\$r'
e'ch\\o' 'bonj'\o\u'r'
echo '' '' 'bonjour' | cat -e
echo '''''' | cat -e #j'envoie un espace mais géré par yohann
##########Redirections#########
#stdin
cat < test.txt
cat <test.txt >>hello<bonjour
cat "<test.txt"
#stdout stderr
echo bonjour1>test1
echo bonjour 1>test2
echo bonjour > "     test1"
echo bonjour 2>hey test2
#double redirection
echo bonjour >> test3
echo bonjour>>test3>>test4
1>test1 2>test2 echo bonjour
1>test12>test2 echo bonjour
2>>test1 #command not found alors que ca doit pas
>test1 2>test2 echo bonjour
1>test233 "" echo bonjour ## yohann va s'en occuper
>> e
#multi redirections
echo >mdr>hey>>sarace\sal"hehe"    #segfault quand echo tout seul sans arguments
echo bonjour 2>\wes\\hh
echo bonjour <\weshh
echo <hey1<h'ey2'
echo >hey1>h'ey2'
>coucou >hey >lol>mdr haha
echo bonjour >hey >>hey2 >>hey3
echo mdr <hello >>wesh>alors2>error
echo mdr >>wesh>alors2>error


#########Environnement#########
echo "$'PATH'"
echo $"coucou"
echo $PATH
$PWD$PATH$COLORTERM    # mauvais retour erreur command not found au lieu de No such file or directory
$COLORTERMcoucou      # mauvais retour
ls $HOME/Desktop
echo "$PATH""" coucou
"$PATH" #retour d'erreur doit etre no such file or directory
echo $PATH"coucou"
echo "hello"$PWD"coucou"
coucou$PWD test$COLORTERMlol lol$HOME
echo "bonjour$PATH$PWD"
echo "bonjour\$PATH$PWD"
echo $PATH"coucou"
echo $\PATH
echo $\c
$\PATH
echo $cou\cou
$cou\cou
echo $coucou"hey"
$coucou"hey"
echo bonjour 1>$"COLORTERM"
echo $PATH >$COLORTERM
echo bonjour 1>$hey"lol"
echo hey > coucou$COLORTERM
echo "$LOL" 2>"$COLORTERM" #segfault quand echo tout seul sans arguments

#########Pipes et Séparations#########
echo "bonjou\"r" ; echo coucou
echo "ceci n'est pas | un pipe"
echo \"  "< ceci | n\'est pas un pipe"
echo \"  " lol n\' ; coucou \"  "
echo \'   "< ceci | n\'est pas un pipe et ceci" ; echo "ceci est bien une séparation >\'"
echo \' "coucou" ; echo coucou
echo \" "coucou\"\"\" ; hey" ; "ech"o \" hey

#--------------------------------Jusqu'ici tout est OK
#--------------------------------probleme chez yohann
echo "$PAT\H" 2>"$COLORTERM"
"$P'ATH'" 
echo $$
$
$$PWD
#---------------------------à gérer ?
echo mdrr <>coucou


#########Cmds#########
echo


#########Tout ensemble#########
echo testing multi ; echo "test 1 ; | and 2" ; cat test.sh | grep echo
cat test.sh | grep arcu | cat -e
echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e
cat /dev/random | head -c 100 | wc -c
echo testing multi ; echo "test 1 ; | and 2" ; cat test.sh | grep echo
>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test
echo > < #segfault

#########Export#########
export
export test2=
export test2
export test1 test2 test3
export test=hello hello="poulette"
export test= o
export test=o
export test=$test"coucou"
export test=$COLORTERM=coucou
export ?=42
export $
export zz zzz= zzzz=asd

#Erreurs Quotes
echo co'c'o'u' #enlever une simple quote
echo c'o\'u'cou' #enlever une simple quote
echo "bon"jour"" #enlever une double quote
echo bonjour <\weshh #no such file or directory si weshh existe pas
;
|
b
a|||bxx
> > a
< < a
< >> a
>>> a
<<<< a
a<<<<
pwd >;
;pwd
pwd ;;
echo bonjour ;;;;;;;; echo coucou

#erreurs
$PWD$PATH$COLORTERM #No such file or directory
./srcs #./srcs: is a directory