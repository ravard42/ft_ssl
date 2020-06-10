/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ssl_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 23:08:30 by ravard            #+#    #+#             */
/*   Updated: 2020/05/15 20:44:35 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const char		*g_ssl_str[] = {
	"%sb64 err_0 : bad char\n%s",
	"%sb64 err_1 : bad use of '='%s\n",
	"%sb64 err_2 : bad use of '='%s\n",
	"%sk and/or v undefined and salt missing %s\n",
	"%sV_MAX_LEN must be >= %d for this key size%s\n",
	"%sCan't parse %s as a decimal number%s\n",
	"%smodulus numbits must be >= 64%s\n",
	"%smodulus numbits must be <= 4096%s\n",
	"Generating RSA private key, %hd bit long modulus (2 primes)\n",
	"%spriv key is expected on input when -des opt is on, "\
	"des enc not computed%s\n",
	"%sOnly private keys can be checked%s\n",
	"%sV_MAX_LEN must be >= %d for checking this key size%s\n",
	"%sRSA key error: p not prime%s\n",
	"%sRSA key error: q not prime%s\n",
	"%sRSA key error: d e not congruent to 1%s\n",
	"%sRSA key error: dmp1 not congruent to d%s\n",
	"%sRSA key error: dmq1 not congruent to d%s\n",
	"%sRSA key error: iqmp not inverse of q%s\n",
	"%sRSA key ok%s\n",
	"RSA Public-Key: (%hd bit)\n",
	"RSA Private-Key: (%hd bit, 2 primes)\n",
	"%sNo key file specified%s\n",
	"%s-encrypt|-decrypt missing%s\n",
	"%sdata too large, V_MAX_LEN must be >= %d%s\n",
	"%sdata too small for key size%s\n",
	"%sdata too large for key size%s\n",
	"%sdata too large for modulus%s\n",
	"%sonly private key can decrypt%s\n",
	"%sunpadding error 0%s\n",
	"%sunpadding error 1%s\n",
	"%sout_file opening error%s\n",
	"%serror in opening /dev/urandom as csprng seed%s\n",
	"%scsprng (re)seeding failed: lack of random input data on rng->fd%s\n",
	"%splaintext and ciphertext samples must be at least %d bits in length%s\n",
	"%splaintext and ciphertext must both be set "\
	"for attempting cryptanalysis%s\n",
	"\nwrong (plaintext, ciphertext) des_ecb couple\n",
	"Attempting DES-ECB decryption\n--> Saving logs to %scrypta.log\n[...]%s\n",
	"NOTE: variable _le suffix stands for little endian "\
	"and _be for big endian.\n\n",
	"(dec_try_le, key_be, plaintext_le) = (%#018lx, %#018lx, %#018lx)\n"
};
