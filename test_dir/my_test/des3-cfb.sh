echo "ft_ssl des3-cfb enc"
time ./ft_ssl des3-cfb -e -i $1 -o test.enc -k $2 -v $3
echo -e "\nopenssl des3-cfb enc"
time openssl des-ede3-cfb -in $1 -out test.openssl.enc -K $2 -iv $3
echo -e "\ndiff:\n"
diff test.enc test.openssl.enc

echo "ft_ssl des3-cfb dec"
time ./ft_ssl des3-cfb -d -i test.enc -o test.dec -k $2 -v $3
echo -e "\nopenssl des3-cfb dec"
time openssl des-ede3-cfb -in test.openssl.enc -d -out test.openssl.dec -K $2 -iv $3 
echo -e "\ndiff:\n"
diff test.dec test.openssl.dec
