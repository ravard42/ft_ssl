echo "ft_ssl des-ecb enc"
time ./ft_ssl des-ecb -e -i $1 -o test.enc -k $2
echo -e "\nopenssl des-ecb enc"
time openssl des-ecb -in $1 -out test.openssl.enc -K $2
echo -e "\ndiff:\n"
diff test.enc test.openssl.enc

echo "ft_ssl des-ecb dec"
time ./ft_ssl des-ecb -d -i test.enc -o test.dec -k $2
echo -e "\nopenssl des-ecb dec"
time openssl des-ecb -in test.openssl.enc -d -out test.openssl.dec -K $2
echo -e "\ndiff:\n"
diff test.dec test.openssl.dec
