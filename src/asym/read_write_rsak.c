#include "ft_ssl.h"

/*
**	About read_rsak
**
**	ASN1 DER DECODING prototype: t_varint	*v_asn1_int_seq_der_d(int *nb_varint, t_read *r)
**
**	t_read *r must contain a valid DER interger sequence
** nb_varint could be 9
**
*/

//int						read_rsak(t_parse *p)
//{
//	
//}

/*
**	About write_rsak
**
**	ASN1 DER ENCODING prototype: int	v_asn1_int_seq_der_e(t_read *r, t_varint *v, int nb_varint)
**
**	
**
*/

int						write_rsak(t_parse *p)
{
	v_asn1_int_seq_der_e(&p->r, p->a.rsak, 9);
	if (p->out_file)
      p->w.fd = open(p->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
   else
      p->w.fd = 1;
   if (p->w.fd == -1
      && ft_dprintf(2, "%sout_file opening error\n%s", KRED, KNRM))
      return (0);
//	DER
//	write(p->w.fd, p->r.msg, p->r.len);
// PEM (need to initialize t_sym struct here!!!!)
	if (run_b64_e(p) != -2)
	{
		ft_dprintf(p->w.fd, "-----BEGIN RSA PRIVATE KEY-----\n");
		write(p->w.fd, p->w.msg, p->w.len);
		ft_dprintf(p->w.fd, "-----END RSA PRIVATE KEY-----\n");
	}
	// BURN IT
	ft_memset((char *)p->a.rsak, 0, sizeof(t_varint) * 9);
	free_p(p);
	return (0);
}
