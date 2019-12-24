make -C ../../
cp ../../ft_ssl ./

KNRM="\x1B[0m"
KRED="\x1B[31;1m"
KGRN="\x1B[32;1m"
KYEL="\x1B[33;1m"
KBLU="\x1B[34;1m"
KMAG="\x1B[35;1m"
KCYN="\x1B[36;1m"
KWHT="\x1B[37;1m"


args=($@)
#args=($@) nous renvoi un tableau (1st index = 0) avec tous les parametres du script 
#${args[$var]} permet de se référer à l'index $var du tableau

script=$1

#<------concernant les differentes variables à activer en fonction 
# 				du script selectionné ----------------------------->

#0 <---base64.sh--->
#id_arg=0

#1 <---des-ecb.sh, des-ecb_a.sh, des3-ecb.sh, des3-ecb_a.sh --->
#key=$2
#id_arg=1

#2 <---des_s.sh, des3-ebc_a_s.sh, des3_a_s.sh, des3-ofb_a_s.sh, des3-cfb_a_s.sh,--->
salt=$2
id_arg=1

#3 <---des.sh, des_a.sh, des3.sh, des3_a.sh, des-ofb.sh, des3-ofb.sh, des-cfb.sh, des3-cfb.sh --->
#key=$2
#iv=$3
#id_arg=2

#<------------------------------------------------------------->

echo "number of args = $#"

while ((id_arg++ != $# - 1));do
	echo -e $KYEL
	echo "id_arg = $id_arg"
	echo "arg = ${args[$id_arg]}"
	echo -e $KNRM

#0	sh $script ${args[$id_arg]}
#1	sh $script ${args[$id_arg]} $key
	sh $script ${args[$id_arg]} $salt
#3	sh $script ${args[$id_arg]} $key $iv
done;
