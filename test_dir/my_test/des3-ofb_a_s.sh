echo "ft_ssl des3-ofb -a -s enc"
time ./ft_ssl des3-ofb -e -i $1 -o test.enc -s $2 -a
echo -e "\nopenssl des3-ofb -a -s enc"
time openssl des-ede3-ofb -in $1 -out test.openssl.enc -S $2 -a
echo -e "\ndiff:\n"
diff test.enc test.openssl.enc

echo "ft_ssl des3-ofb -a -s dec"
time ./ft_ssl des3-ofb -d -i test.enc -o test.dec -s $2 -a
echo -e "\nopenssl des3-ofb -a -s dec"
time openssl des-ede3-ofb -in test.openssl.enc -d -out test.openssl.dec -S $2 -a
echo -e "\ndiff:\n"
diff test.dec test.openssl.dec
