echo "ft_ssl des-cfb enc"
time ./ft_ssl des-cfb -e -i $1 -o test.enc -k $2 -v $3
echo -e "\nopenssl des-cfb enc"
time openssl des-cfb -in $1 -out test.openssl.enc -K $2 -iv $3
echo -e "\ndiff:\n"
diff test.enc test.openssl.enc

echo "ft_ssl des-cfb dec"
time ./ft_ssl des-cfb -d -i test.enc -o test.dec -k $2 -v $3
echo -e "\nopenssl des-cfb dec"
time openssl des-cfb -in test.openssl.enc -d -out test.openssl.dec -K $2 -iv $3 
echo -e "\ndiff:\n"
diff test.dec test.openssl.dec
