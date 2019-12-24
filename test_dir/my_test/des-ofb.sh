echo "ft_ssl des-ofb enc"
time ./ft_ssl des-ofb -e -i $1 -o test.enc -k $2 -v $3
echo -e "\nopenssl des-ofb enc"
time openssl des-ofb -in $1 -out test.openssl.enc -K $2 -iv $3
echo -e "\ndiff:\n"
diff test.enc test.openssl.enc

echo "ft_ssl des-ofb dec"
time ./ft_ssl des-ofb -d -i test.enc -o test.dec -k $2 -v $3
echo -e "\nopenssl des-ofb dec"
time openssl des-ofb -in test.openssl.enc -d -out test.openssl.dec -K $2 -iv $3 
echo -e "\ndiff:\n"
diff test.dec test.openssl.dec
