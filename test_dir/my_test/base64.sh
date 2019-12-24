echo "ft_ssl base64 enc"
time ./ft_ssl base64 -e -i $1 -o test.enc 
echo -e "\nopenssl base64 enc"
time openssl base64 -in $1 -out test.openssl.enc
echo -e "\ndiff:\n"
diff test.enc test.openssl.enc

echo "ft_ssl base64 dec"
time ./ft_ssl base64 -d -i test.enc -o test.dec
echo -e "\nopenssl base64 dec"
time openssl base64 -in test.openssl.enc -d -out test.openssl.dec
echo -e "\ndiff:\n"
diff test.dec test.openssl.dec
