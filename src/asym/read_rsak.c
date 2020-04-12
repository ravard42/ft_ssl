#include "ft_ssl.h"

static const char			*g_beg_end_str[] = {
	"-----BEGIN RSA PRIVATE KEY-----\n",
	"-----BEGIN PUBLIC KEY-----\n",
	"-----END RSA PRIVATE KEY-----\n",
	"-----END PUBLIC KEY-----\n"
};

/*
** handle_header
**
**	read encryption header if one and set p->a.iv_salt,
** offset[0] must point on b64 data at the end of this function
**	
**	return 1 if ok, 0 if error
*/

static int		check_enc_header(int64_t *offset, t_parse *p)
{
	char		*str;

	str = PEM_ENC_HEADER;
	if ((offset[1] = ft_grep_line(str, &p->r, offset[0])) == offset[0])
	{
		offset[0] += ft_strlen(str);
		if (p->r.len - offset[0] <= 16
			&& ft_dprintf(2, "%sincomplete header%s\n", KRED, KNRM))
			return (0);
		if (!hstr_to_64_t(p->s.arg[2].x, 1, p->r.msg + offset[0], false)
			&& ft_dprintf(2, "%serror reading initial vector%s\n", KRED, KNRM))
			return (0);
		p->s.arg[2].set = true;
		if ((offset[0] = ft_nxt_line(&p->r, offset[0])) <= 0)
			return (0);
	}
	offset[0] += p->r.msg[offset[0]] == '\n' ? 1 : 0;
	return (1); 
}

/*
** grep_pem
**
** scan t_read *r to find a pem valid sequence.
**
*/

int		grep_pem(t_parse *p)
{
	int64_t	offset[2];
//	char		*str;

	offset[0] = 0;
//	str = (p->a.o[7]) ? PEM_PUB_BEG : PEM_PRI_BEG;
	if ((offset[0] = ft_grep_line(g_beg_end_str[p->a.o[7]], &p->r, offset[0])) < 0)
		return (0);
	if ((offset[0] = ft_nxt_line(&p->r, offset[0])) <= 0)
		return (0);
	if (!p->a.o[7] && check_enc_header(offset, p) == -1)
		return (0);
//	str = (p->a.o[7]) ? PEM_PUB_END : PEM_PRI_END;
	if ((offset[1] = ft_grep_line(g_beg_end_str[2 + p->a.o[7]], &p->r, offset[0])) < 0)
		return (0);
	ft_memcpy(p->r.msg, p->r.msg + offset[0], offset[1] - offset[0]);
	p->r.msg[offset[1] - offset[0]] = 0;
	p->r.len = offset[1] - offset[0];
	return (1);
}

static int	pem_des_dec(t_parse *p)
{
	t_parse		tmp;

	if (!p->s.arg[0].p && !(p->s.arg[0].p = set_pass(false)))
		return (0);
	p->s.arg[3].p = p->s.arg[0].p;
	if (!md5_pbkdf(&tmp, p))
		return (0);
	p->s.arg[3].p = NULL;
	ft_memcpy(p->s.arg[0].x, &tmp.h.h, 8);
	p->s.arg[0].set = true;
	format_key(&p->s, 1);
	p->s.arg[1].x[0] = p->s.arg[2].x[0];
	p->s.arg[1].set = true;
	if (!opt_a_d(p))
		return (0);
	if (!des_dec(p))
		return (0);
	free(p->r.msg);
	p->r.msg = p->w.msg;
	p->w.msg = NULL;
	p->r.len = p->w.len;
	return (1);

}

static int64_t	der_pub_offset(char *data, int64_t len)
{
	int64_t i;

	i = -1;
	while (++i < len - 1)
		if (data[i] == 0x00 && data[i + 1] == 0x30)
			return (i + 1);
	ft_dprintf(2, "%sder_pub_offset error%s\n", KRED, KNRM);
	return (-1);
}

int		pem_2_der(t_parse *p)
{
	int64_t	der_offset;

	if (!grep_pem(p)
		&& ft_dprintf(2, "%sInvalid PEM file%s\n", KRED, KNRM))
		return (0);
	if (!p->s.arg[2].set)
	{
		if (run_b64_d(p) == -2)
			return (0);
		der_offset = (p->a.o[7]) ? der_pub_offset(p->w.msg, p->w.len) : 0;
		if (der_offset == -1)
			return (0);
		ft_memcpy(p->r.msg, p->w.msg + der_offset, p->w.len - der_offset);
		p->r.len = (p->a.o[7]) ? p->w.len - der_offset : p->w.len;
		return (1);
	}
	return (pem_des_dec(p));
}


/*
**	About read_rsak
**
**	ASN1 DER DECODING prototype: t_varint	*v_asn1_int_seq_der_d(int *nb_varint, t_read *r)
**
**	t_read *r must contain a valid DER interger sequence
** nb_varint could be:
**	9 for private keys: version, n, e, d, p, q, dp, dq, qinv
**	2 for public keys : n, e
**
** o[2] : -inform (0 for PEM, 2 for DER)
** o[4] : 1 for -passin, else 0
** o[7] : 1 for -pubin, else 0	
**
*/

int						read_rsak(t_parse *p)
{
	int64_t	offset;
	int		nb_v;

	if (!p->a.o[2] && !pem_2_der(p))
		return (0);
	else if (p->a.o[2] && p->a.o[7])
	{
		offset = der_pub_offset(p->r.msg, p->r.len);
		ft_memcpy(p->r.msg, p->r.msg + offset, p->r.len - offset);
		p->r.len -= offset;
	}
	p->a.rsak = v_asn1_int_seq_der_d(&nb_v, &p->r);
	if ((!p->a.rsak || (nb_v != 2 && nb_v != 9))
		&& ft_dprintf(2, "%srsa key loading error%s\n", KRED, KNRM))
		return (0);
	free_if((void **)&p->r.msg);
	free_if((void **)&p->w.msg);
	return (nb_v);
}
