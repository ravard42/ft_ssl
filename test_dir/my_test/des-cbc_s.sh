echo "ft_ssl des-cbc enc"
time ./ft_ssl des-cbc -e -i $1 -o test.enc -s $2 -a
echo -e "\nopenssl des-cbc enc"
time openssl des-cbc -in $1 -out test.openssl.enc -S $2 -a
echo -e "\ndiff:\n"
diff test.enc test.openssl.enc

echo "ft_ssl des-cbc dec"
time ./ft_ssl des-cbc -d -i test.enc -o test.dec -s $2 -a
echo -e "\nopenssl des-cbc dec"
time openssl des-cbc -in test.openssl.enc -d -out test.openssl.dec -S $2 -a
echo -e "\ndiff:\n"
diff test.dec test.openssl.dec
