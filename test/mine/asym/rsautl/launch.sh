#!/bin/bash

KNRM="\x1B[0m"
KRED="\x1B[31;1m"
KGRN="\x1B[32;1m"
KYEL="\x1B[33;1m"
KBLU="\x1B[34;1m"
KMAG="\x1B[35;1m"
KCYN="\x1B[36;1m"
KWHT="\x1B[37;1m"

#>>>> MAKING ./FT_SSL >>>>>
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
#<<<< MAKING ./FT_SSL <<<<<<

#>>>>> INPUT PARSER >>>>>
# available tests
test_type[0]='raw_enc'
test_nbarg[0]=4
test_usage[0]='sh launch.sh raw_enc key_len file_len nb_tests'

nb_type=1
# $1 : type of the test
for ((id = 0; id < nb_type; ++id)); do
if [[ $1 == ${test_type[$id]} ]]; then break; fi
done

if (( id == nb_type )); then
echo -ne "${KYEL}usage: sh launch.sh "
for ((i = 0; i < nb_type - 1; i++ )); do echo -n "${test_type[$i]}|"; done
echo -e "${test_type[$i]}$KRNM"
ls | grep -v launch.sh | xargs rm
exit
fi

if (( test_nbarg[id] != $# )); then
echo -e "${KYEL}${test_usage[$id]}$KRNM"
ls | grep -v launch.sh | xargs rm
exit
fi

#<<<<< INPUT PARSER <<<<<<

#>>>>> TEST FUNCTIONS >>>>>>

raw_enc() {
#cf function_args.sh in ~/language/scriptShell/learning-bash
key_len=$2
file_len=$3

./ft_ssl genrsa -out key.pem $key_len 2>/dev/null
head -c $file_len /dev/urandom > file

./ft_ssl rsa -in key.pem -modulus -noout
hexdump -ve '1/1 "%0.2x"' file
echo ""
openssl rsautl -in file -inkey key.pem -encrypt -raw -hexdump #> /dev/null

}

#<<<<< TESTS FUNCTIONS <<<<<<

#>>>>>> MAIN >>>>>>
i=0
ok=0
col=$KYEL
nb_tests=${@: -1}

while ((i < nb_tests)); do
	${test_type[$id]} "$@" #2>/dev/null

if (($? == 0)); then ((ok += 1)); fi
((i += 1))
if ((i != ok)); then col=$KRED; fi
echo -ne "									${col}${test_type[$id]}:	${ok}/${nb_tests}${KNRM}"
echo -ne "\r"
done

if ((i == ok)); then col=$KGRN; fi
echo -e "									${col}${test_type[$id]}:	${ok}/${nb_tests}${KNRM}"
#<<<<<< MAIN <<<<<<

ls | grep -v launch.sh | xargs rm

