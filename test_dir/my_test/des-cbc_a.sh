echo "ft_ssl des-cbc -a enc"
time ./ft_ssl des-cbc -e -i $1 -o test.enc -k $2 -v $3 -a
echo -e "\nopenssl des-cbc -a enc"
time openssl des-cbc -in $1 -out test.openssl.enc -K $2 -iv $3 -a
echo -e "\ndiff:\n"
diff test.enc test.openssl.enc

echo "ft_ssl des-cbc -a dec"
time ./ft_ssl des-cbc -d -i test.enc -o test.dec -k $2 -v $3 -a
echo -e "\nopenssl des-cbc -a dec"
time openssl des-cbc -in test.openssl.enc -d -out test.openssl.dec -K $2 -iv $3 -a
echo -e "\ndiff:\n"
diff test.dec test.openssl.dec
