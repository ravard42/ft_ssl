echo "ft_ssl des3-ecb -a enc"
time ./ft_ssl des3-ecb -e -i $1 -o test.enc -k $2 -a
echo -e "\nopenssl des3-ecb -a enc"
time openssl des-ede3 -in $1 -out test.openssl.enc -K $2 -a
echo -e "\ndiff:\n"
diff test.enc test.openssl.enc

echo "ft_ssl des3-ecb -a dec"
time ./ft_ssl des3-ecb -d -i test.enc -o test.dec -k $2 -a
echo -e "\nopenssl des3-ecb -a dec"
time openssl des-ede3 -in test.openssl.enc -d -out test.openssl.dec -K $2 -a
echo -e "\ndiff:\n"
diff test.dec test.openssl.dec
