# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/21 18:19:49 by jafaghpo          #+#    #+#              #
#    Updated: 2018/03/01 16:58:55 by rbalbous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vm=resources/filler_vm
maps=resources/maps/map0
players=resources/players
ext=.filler

#======COLORS======#

EOC="\033[0m";
RED="\033[31m";
GREEN="\033[32m";
YELLOW="\033[33m"
BLUE="\033[34m";
MAGENTA="\033[35m";
CYAN="\033[36m";
HIGH="\033[1m";
BG_RED="\033[41m";
BG_BLUE="\033[44m";


# dont touch after this line --------------------------------------------------

p1=0;
p2=0;

echo "$HIGH$GREEN--- Welcome to Filler tester v1.0 ---\n$EOC"
read -p 'Enter the login of your champions: ' plr1 plr2
read -p 'Enter the arena: ' map
if  (( map < 0 || map > 2)); then
	echo "$RED\nError: wrong arena name"
	exit 1
fi
read -p 'Enter the number of rounds: ' rounds
if (( rounds <= 0)); then
	echo "$RED\nError: wrong number of rounds"
	exit ;
fi
echo "\n$EOC-----$HIGH$BLUE $plr1$EOC vs $HIGH$RED$plr2$EOC -----"
echo "\nOn arena $map in $rounds round(s)...\n"
echo "$HIGH$BLUE----------->$EOC FIGHT $HIGH$RED<-----------$EOC\n"

while [ $rounds != 0 ]
do
	$vm -f $maps$map -p1 $players/$plr1$ext -p2 $players/$plr2$ext 1>/dev/null
	result=$(cat filler.trace | grep won)
	if echo "\e;30[40m$result" | grep -q "$plr1"
	then
		((p1++))
		printf "$HIGH$BLUE>"
	else
		((p2++))
		printf "$HIGH$RED>"
	fi
	((rounds--))
done

echo "$EOC$HIGH$BLUE\n\n$plr1: $EOC$p1$HIGH$RED  $plr2: $EOC$p2"

if [ $p1 -gt $p2 ]
then
	echo " $HIGH$BLUE\nAnd the winner is...$plr1! Congratulations."
else
	echo "$HIGH$RED\nAnd the winner is... $plr2! Congratulations."
fi
