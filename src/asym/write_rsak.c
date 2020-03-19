#include "ft_ssl.h"

static const char			*g_beg_end_str[] = {
	"-----BEGIN RSA PRIVATE KEY-----\n",
	"-----BEGIN PUBLIC KEY-----\n",
	"-----END RSA PRIVATE KEY-----\n",
	"-----END PUBLIC KEY-----\n"
};

/*
**	ASN1 PUBLIC KEY STRUCTURE:
**
** TOTAL_SEQ
** 	CONST_SEQ
**			OBJECT
**			NULL
** 	BIT STRING (BIT_STRING_HEADER 0x00 v_asn1_int_seq_der_e)
** 
**	about uint8_t h[2][5]:
**	index 0 for TOTAL_SEQ HEADER and h[1] for BIT_STRING_HEADER
**	h[x][0] = header len
**	h[x][1:4] = header
*/

static int			add_der_pub_offset(t_parse *p)
{
	static const uint8_t		const_seq[15] = {0x30, 0x0d, 0x06, 0x09, 0x2a,
		0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00};
	uint8_t						h[2][5];
	char							*tmp;
	int64_t						tmp_len;

	if (put_der_header(h[1], 0x03, 1 + p->r.len) == -1)
		return (0);
	if (put_der_header(h[0], 0x30, 15 + h[1][0] + 1 + p->r.len) == -1)
		return (0);
	tmp = (char *)ft_memalloc(sizeof(char) *
		(h[0][0] + 15 + h[1][0] + 1 + p->r.len));
	ft_memcpy(tmp, h[0] + 1, h[0][0]);
	tmp_len = h[0][0];
	ft_memcpy(tmp + tmp_len, const_seq, 15);
	tmp_len += 15;
	ft_memcpy(tmp + tmp_len, h[1] + 1, h[1][0]);
	tmp_len += h[1][0] + 1;
	ft_memcpy(tmp + tmp_len, p->r.msg, p->r.len);
	free(p->r.msg);
	p->r.msg = tmp;
	p->r.len += tmp_len;
	return (1);
}

static int			der_enc(t_parse *p, int nb_v)
{
	int		ret;

	p->a.o[8] = (nb_v == 2) ? 1 : p->a.o[8];
	if (p->a.o[8])
	{
		ret = (nb_v == 2) ? v_asn1_int_seq_der_e(&p->r, p->a.rsak, 2) :
			v_asn1_int_seq_der_e(&p->r, p->a.rsak + 1, 2);
		if (ret != 1 && ft_dprintf(2, "%spub der enc error%s\n", KRED, KNRM))
			return (0);
		if (!add_der_pub_offset(p))
			return (0);
	}
	else if (v_asn1_int_seq_der_e(&p->r, p->a.rsak, 9) != 1)
		return (0);
	return (1);
}


/*
**	About write_rsak
**
**	ASN1 DER ENCODING prototype: int	v_asn1_int_seq_der_e(t_read *r, t_varint *v, int nb_varint)
**	
**
**	o[3] : -outform (0 for PEM, 2 for DER)
**	o[5] : 1 for -passout, else 0
**	o[6] : 1 for -des, else 0
**	o[8] : 1 for -pubout, else 0
*/

int						write_rsak(t_parse *p, int nb_v)
{
	if (!der_enc(p, nb_v))
		return (0);
	if (p->out_file)
      p->w.fd = open(p->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
   else
      p->w.fd = 1;
   if (p->w.fd == -1
      && ft_dprintf(2, "%sout_file opening error\n%s", KRED, KNRM))
      return (0);
//	DER
	if (p->a.o[3] == 2 && ft_dprintf(2, "writing RSA key\n"))
		write(p->w.fd, p->r.msg, p->r.len);
	else if (run_b64_e(p) != -2 && ft_dprintf(2, "writing RSA key\n"))
	{
		ft_dprintf(p->w.fd, g_beg_end_str[p->a.o[8]]);
		write(p->w.fd, p->w.msg, p->w.len);
		ft_dprintf(p->w.fd, g_beg_end_str[2 + p->a.o[8]]);
	}
	// BURN IT
	ft_memset((char *)p->a.rsak, 0, sizeof(t_varint) * nb_v);
	free_p(p);
	return (0);
}
