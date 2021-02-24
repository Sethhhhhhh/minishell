#! /bin/sh

######################################## YOHANN ########################################


#########Echo#########
echo bonjour
        echo echo hey
echo bonjourheybonjour salut
echo lalalala                lalalalal      alalalalal alalalala
echo -n lalalala                lalalalal      alalalalal alalalala
                        echo       -n            bonjour
echo -n bonjour coucou
echo -n
echo -n-n
echo "-n     mdr"
echo -\n hey
echo \-n hey
echo - n
echo '-     n'
echo  Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem...
echo a '' b '' c '' d
echo a "" b "" c "" d
echo -n -n lol -n
echo -n -n -n test tout
echo
echo -n -n 
echo -n a '' b '' c '' d
echo -n a "" b "" c "" d
echo '' '' ''
echo ''
echo a; echo b; echo c; echo d; echo e; echo f; echo g; echo h; echo i;echo j;
echo;
echo ;
echo -nnnnnnnnnnnnnnnnnnnnn bonjour
echo -nnnnnnnnnnnnnnnnnnnnn -n -n -n bonjour -n -n
Echo bonjour
eCho bonjour
ecHo bonjour
echO bonjour
EchO bonjour
eCHo bonjour
EcHo bonjour
eChO bonjour
[SETUP mkdir d] echo $PWD; echo $OLDPWD
[EXPORTS HOME='/Users/emmabourdit'] echo $PWD; echo $OLDPWD
echo "$wfjwefielwhfhlwefkhwefwe" a
echo '$wfjwefielwhfhlwefkhwefwe' a
'$wfjwefielwhfhlwefkhwefwe' a
"$wfjwefielwhfhlwefkhwefwe" a
#/bin/echo fonctionne pas
/bin/echo " \  "
/bin/echo " \" "
/bin/echo " \' "
/bin/echo " \a "
/bin/echo " \b "
/bin/echo " \| "
/bin/echo " \! "
/bin/echo " \@ "
/bin/echo " \$ "
/bin/echo " \$LESS "
/bin/echo " \$? "
/bin/echo " \\ "
/bin/echo " \\\ "
/bin/echo " \\\\ "
/bin/echo " \\\\\ "
/bin/echo " \\\\\\ "
/bin/echo " \\\\\\\ "
/bin/echo " \\\\\\\\ "
/bin/echo ' \  '
/bin/echo ' \" '
/bin/echo ' \a '
/bin/echo ' \b '
/bin/echo ' \! '
/bin/echo ' \@ '
/bin/echo ' \$ ' 
/bin/echo ' $LESS '
/bin/echo ' \$? '
/bin/echo ' \\ '
/bin/echo ' \\\ '

#########Cd#########
cd ..
cd..
cd ./srcs
cd .
cd ../
cd ../../../
cd /
cd
cd -
cd /Users
Cd .
cD .
cd /.
cd /./
cd /././././
cd //
cd ///
cd ////
cd //////////////////////////////////////////////////////
cd $HOME
cd ' // '; pwd
#retour a la ligne tout seul donne un command not found
#il faut pas renvoyer command not found quand y a un fichier qui a été créé et que arg[0] = \0
./minishell -c "echo bonjour > file ; <file" | cat -e
touch test ; < test
# permission denied alors que c'est pas censé renvoyer de msg d'erreur
cd '' 
cd '' ''
cd '' '' ''
cd ' '
#permission denied en trop
cd ' // '
cd ' /'
cd '                  /'
cd d ''
cd d d
mkdir -m 000 d ; echo $PWD; echo $OLDPWD; cd d; echo $OLDPWD 
# il me dit no such file or directory alors que doit pas
cd ~ 
# renvoie chez nous /home et //home dans bash
cd //home ; pwd 

#########Export#########
export test=coucou ; echo $test
export emma="bourdit" yohann="viavant"
export "mdr"=hey
export "ceci"="cela"
export lol=""
export lol=" "
export lol2=''
export lol2=' '
export lol2="\'"
export lol2="'"
export lol2="'"
export lol2="\\"
export lol2='$'
export lol2='\t'
export test=hello hello="poulette"
export test2=
export test1
export test= o
export test=$test"coucou"
export zz zzz= zzzz=asd
export A=a B=b C=c D=d E=e F=f G=g H=h I=i J=j K=k L=l M=m N=n O=o P=p Q=q R=r
Export B=bonjour
exporT B=bonjour
[EXPORTS PATH='/bin:/usr/bin'] Export B=bonjour
[EXPORTS PATH='/bin:/usr/bin'] exporT B=bonjour
export A=\B\O\N\ \ \ \ \ \ \ JOURJESUIS
export test=$COLORTERM=coucou
#à faire
export 
#maximum 1 espace entre les élements
export test="   a   "
echo $test$test$test$test$test$test$test$test$test$test
echo $test$test$test$test
#quand y a le début d'une autre variable ca l'appelle
echo $PA
echo "$PAT\H" 2>"$COLORTERM"
"$P'ATH'" 
echo $$
$
$$PWD
export A=\B\O\N\ \ \ \ \ \ \ JOURJESUIS ; echo $A
#une deuxième assignation doit écraser la première
export mdr=hey; env ; export mdr=lol ; env
#error a renvoyer not a valid identifier si y a des caractères autres que ??:
export ?=42
export $
export 1=a
export BONJOURJESUIS =a
export BONJOUR\\JESUIS=a
export BONJOUR\'JESUIS=a
export BONJOUR\&JESUIS=a 
export BONJOUR\|JESUIS=a
export BONJOUR\;JESUIS=a
export 'AH\'=nop
export 'AH@'=nop
export 'AH"'=nop
export 'AH!'=nop
export A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C
export "  a"=coucou

#########Unset#########
unset emma yohann
export test1 test2= test3="coucou" ; unset test1 test2
export A='a' ; unset 'A'; echo $A
Unset TERM
unseT TERM
#a faire
unset
#erreur doit renvoyer "unset `... ': not a valid identifier"
export A='a' ; unset 'A '; echo $A
export A='a' B='b' C='c' ; unset 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C
export A='a' B='b' C='c' ; unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf '; echo $A$B$C
export A='a' B='b' C='c' ; unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C 
unset 'AH@'=nop
unset "AH'"=nop
unset 'AH"'=nop
unset 'AH$'=nop
unset 'AH!'=nop
unset 'AH|'=nop
unset 'AH;'=nop
unset 'AH&'=nop
unset 'AH\'=nop  
#renvoie pas l'erreur + renvoie pas le resultat de echo $A
export A='a' ; unset 'A='; echo $A
#renvoie une variable d'environnement wtf?
export A='a' B='b' C='c' ; unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C
#Term n'est pas unset ici
export PATH='/bin:/usr/bin' ; unset TERM ; echo $TERM
unset TERM ; echo $TERM

#########Env#########
env
Env
enV
export PATH='/bin:/usr/bin' ; Env
export PATH='/bin:/usr/bin' ; enV  
# la variable A n'apparaît pas
export A=a ; env
# y a que la variable B qui s'est exportée
export A=a B=b C=c ; env
export A=a B=b C=c ; env | cat -e 

#########Pwd#########
pwd
pwd mdr
pwd coucou ne rien imprimer
[SETUP cd ..] pwd
[SETUP cd ../..] pwd
[SETUP cd ../../..] pwd
[SETUP cd /] pwd
[SETUP cd $HOME] pwd
pwd | cat -e
unset PWD; pwd; echo $PWD
Pwd
pwD
#erreur : pas le meme retour chez nous renvoie /etc dans bash renvoie le bon pwd
export PWD='/etc' ; pwd
export PWD=foo; pwd; echo $PWD

#########Pipes#########
echo testing multi ; echo "test 1 ; | and 2" ; cat test.sh | grep echo
cat test.sh | grep arcu | cat -e
echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e
cat /dev/random | head -c 100 | wc -c
echo testing multi ; echo "test 1 ; | and 2" ; cat test.sh | grep echo
>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test
touch a b c d; mkdir m1 m2 m3; echo bonjour > a ; ls -l | cat -e < a
ls asdfasdf | echo a
echo a | ls asdfasdf
#Boucle infinie :
cat -e /dev/random | head -c 10
cat -e /dev/random | cat -e | head -c 10 
cat -e /dev/random | cat -e | cat -e | head -c 10


#########Erreurs A renvoyer#########
#il manque un retour erreur ici :
asdf | echo bonjour
#Mauvais retour d'erreur : Bad file descriptor au lieu de No such file or directory
cat < doesnotexist
#Mauvais retour d'erreur : command not found au lieu de No such file or directory
$PWD$PATH$COLORTERM
"$PATH"
#Mauvais retour d'erreur : command not found au lieu de is a directory
./srcs
# y a command not found qui se met dans test
> test
>> test
#command not found alors que ca doit pas
2>>test1
$COLORTERMcoucou
#l'inverse, c'est sencé renvoyer command not found mais c'est pas le cas
1>test233 "" echo bonjour


######################################## EMMA ########################################

#########Protections#########
'echo' "bonjour" "wesh"
e"ch"o bonjour
       'ech'o bonjour
#echappement tout seul
echo\ bonjour
\ echo bonjour
 \ echo bonjour
                 \ echo bonjour
 \                 echo bonjour
                 \                    echo bonjour
echo lol\ \ \ \coucou
\ \ \ \ \ \ mdr
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
echo \ \ jesuis \|\| \ charles
#doubles quotes
"" "" echo minishell
""echo minishell
"ec''ho" bonjour
"ec'''ho" bonjour
echo "\\"
echo "" coucou | cat -e
echo bon""jour
echo """""mdrr"
echo ''""
echo ''""''
echo """"bonjour"" "" | cat -e
"echo bonjou"""r
"echo""" ''bonjour
echo "$wfjwefielwhfhlwefkhwefwe" a
ls "-lR""-a"
echo bonjour 1>"hey" pas normal
echo bonjour 1> "wesh alors" hey
echo "" mdr "" | cat -e
echo bonjour 1>'"' pas normal
echo bonjour 1> "hey""" pas normal
echo bonjour 1> "hey"'' pas normal
echo bon"jo\"u"r
echo bon"jo\\"u"r"
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
echo '''''' | cat -e
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
>test1 2>test2 echo bonjour
>> e
#multi redirections
echo >mdr>hey>>sarace\sal"hehe"
echo bonjour 2>\wes\\hh
echo bonjour <\weshh
echo <hey1<h'ey2'
echo >hey1>h'ey2'
>coucou >hey >lol>mdr haha
echo bonjour >hey >>hey2 >>hey3
echo mdr <hello >>wesh>alors2>error
echo mdr >>wesh>alors2>error
echo "\"" >>a"b""c"
echo b > foo ; echo a | cat -e < foo
echo > test'sticked' bonjour
> test'sticked' echo bonjour
echo >> test'sticked' bonjour
>> test'sticked' echo bonjour
echo bonjour > test; echo salut > je ; cat<test<je

#########Environnement#########
echo "$'PATH'"
echo $"coucou"
echo $PATH
ls $HOME/Desktop
echo "$PATH""" coucou
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
echo "$LOL" 2>"$COLORTERM"

#########Pipes et Séparations#########
echo "bonjou\"r" ; echo coucou
echo "ceci n'est pas | un pipe"
echo \"  "< ceci | n\'est pas un pipe"
echo \"  " lol n\' ; coucou \"  "
echo \'   "< ceci | n\'est pas un pipe et ceci" ; echo "ceci est bien une séparation >\'"
echo \' "coucou" ; echo coucou
echo \" "coucou\"\"\" ; hey" ; "ech"o \" hey
echo bonjour | asdf
echo bonjour; ls doesnotexists
echo \ \ jesuis\; \ charles


#########Erreurs A renvoyer#########
#erreurs dans les fichiers des redirections :
echo bonjour 1>'' pas normal # No such file or directory
#syntax error near unexpected token `|'
echo|
| ; a
| < a
< | a
> | a
>> | a 
echo |
echo |
|echo
|cat
| cat
    | cat 
 echo bonjour | | cat -e
echo a ||| echo b
#syntax error near unexpected token `;'
echo a ; ;
< ; a
> ; a
>> ; a
; | a
; < a
; > a
; >> a
;
; ;
; ; ; 
echo a ; ; echo b
; echo 
;echo 
#syntax error near unexpected token `;;'
;;;
echo a ;;;;; echo b 
echo a ;; echo b
#syntax error near unexpected token `newline'
echo <
> 
>>
<
#syntax error near unexpected token `>'
echo foo >>> bar
#syntax error near unexpected token `>>'
echo foo >>>> bar 
echo foo >>>>> bar
#syntax error near unexpected token `<'
echo bonjour > bar ; cat << < bar 
#syntax error near unexpected token `<<'
#echo bonjour > bar ; cat << << bar
echo bonjour > bar ; cat <<<<< bar 
#Erreurs Quotes
echo ''#enlever une simple quote
echo '\'''#enlever une simple quote
echo ""#enlever une double quote
echo ''''''''''''''''''''''''''''''''''''''''''''#enlever une simple quote
echo "\\"""#enlever une double quote
echo "AH\""#enlever une double quote
echo """" #enlever une double quote : boucle infinie
echo co'c'o'u' #enlever une simple quote
echo c'o\'u'cou' #enlever une simple quote
echo "bon"jour"" #enlever une double quote
echo bonjour <\weshh #no such file or directory si weshh existe pas



#---------------------------à gérer ?
echo mdrr <>coucou
echo > < #segfault