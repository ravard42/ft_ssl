#!/bin/bash

KNRM="\x1B[0m"
KRED="\x1B[31;1m"
KGRN="\x1B[32;1m"
KYEL="\x1B[33;1m"
KBLU="\x1B[34;1m"
KMAG="\x1B[35;1m"
KCYN="\x1B[36;1m"
KWHT="\x1B[37;1m"


#MAKING FT_SSL EXEC
make_dir="/home/ravard/projets/42/ft_ssl"

echo -ne "${KYEL}ft_ssl makefile is running [...]$KNRM"
echo -ne "\r"
#make -C $make_dir  re > /dev/null 2>&1
#make -C $make_dir  re
make -C $make_dir  
if (($? == 0));then
echo -e "${KGRN}ft_ssl successfully built and ready to be tested$KNRM\n"
else
echo -e "${KRED}error in ft_ssl compilation      $KNRM\n"
fi
cp $make_dir/ft_ssl ./ 

# $1 : type of the test
# "genrsa" | ? [...]

#-----GENRSA TEST-----

if [[ $1 == genrsa ]];then
# $2 : size of modulus in bits
# $3 : numb of tests
if (($# != 3));then
echo -e "${KYEL}usage: sh launch.sh genrsa numbits numberOfTests\n$KRNM"
else

i=0
OK=0
COL=$KYEL

while ((i < $3));do

#DER
#./ft_ssl genrsa $2 > rsak.der
#openssl rsa -check -inform DER -in rsak.der | grep ok

#PEM
./ft_ssl genrsa $2 > rsak.pem
openssl rsa -check -in rsak.pem | grep ok

if (($? == 0));then
((OK += 1))
fi
((i += 1))

if ((i != OK));then
COL=$KRED
fi
echo -ne "									${COL}${OK}/$3${KNRM}"
echo -ne "\r"
done

if ((i == OK));then
COL=$KGRN
fi
echo -e "									${COL}${OK}/$3${KNRM}"
rm rsak.pem rsak.der

fi
elif [[ $1 == rsa ]];then
echo "not done yet"
elif [[ $1 == rsautl ]];then
echo "not done yet"
else
echo -e "${KYEL}sh launch.sh genrsa|rsa|rsautl\n$KRNM"
fi
