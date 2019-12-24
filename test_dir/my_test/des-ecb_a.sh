echo "ft_ssl des-ecb -a enc"
time ./ft_ssl des-ecb -e -i $1 -o test.enc -k $2 -a
echo -e "\nopenssl des-ecb -a enc"
time openssl des-ecb -in $1 -out test.openssl.enc -K $2 -a
echo -e "\ndiff:\n"
diff test.enc test.openssl.enc

echo "ft_ssl des-ecb dec -a"
time ./ft_ssl des-ecb -d -i test.enc -o test.dec -k $2 -a
echo -e "\nopenssl des-ecb dec -a"
time openssl des-ecb -in test.openssl.enc -d -out test.openssl.dec -K $2 -a
echo -e "\ndiff:\n"
diff test.dec test.openssl.dec
