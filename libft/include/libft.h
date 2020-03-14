/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 02:11:26 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 02:12:59 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <inttypes.h>
# include <wchar.h>
# include <stdbool.h>
# include "varint.h"

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31;1m"
# define KGRN  "\x1B[32;1m"
# define KYEL  "\x1B[33;1m"
# define KBLU  "\x1B[34;1m"
# define KMAG  "\x1B[35;1m"
# define KCYN  "\x1B[36;1m"
# define KWHT  "\x1B[37;1m"

# define READ_BUFF_SIZE 4096
# define MAX_FD 2048
# define BUFF_SIZE 7
# define MARGE 5

typedef struct		s_read
{
	char			*msg;
	int64_t			len;
	struct s_read	*next;
	struct s_read	*prev;
}					t_read;

typedef struct		s_flags
{
	char			hash;
	char			min;
	char			plu;
	char			sp;
	char			ze;
}					t_flags;

typedef struct		s_buff
{
	char			*b;
	int				ret;
}					t_buff;

typedef struct		s_spe
{
	t_flags			fl;
	int				w;
	int				pre;
	char			size;
	char			type;
	t_buff			buff;
	char			*out;
	int				fd;
	int				c_null_conv;
}					t_spe;

typedef struct		s_conv
{
	char			*s;
	void			(*f)(va_list *va, t_spe *e);
}					t_conv;

/*
** basic functions
*/

void				*ft_memalloc(size_t size);
void				ft_memset(char *b, char c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memrcpy(void *dst, const void *src, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_putchar(char c);
void				ft_putnchar(char *ptr, size_t len);
void				ft_puthex(void *p, int64_t len, bool capitalize,  bool newline);
void				ft_putrhex(void *p, int64_t len, bool capitalize, bool newline);
void				ft_putstr(char *str);
size_t				ft_strlen(const char *s);
size_t				ft_wstrlen(wchar_t *wc);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_revstr(char *str);
char				*ft_strdup(const char *str);
char				**ft_strsplit(const char *s, char c);
char				*polarity(char *str, int *sign);
int					ft_len(char *buf, char mode);
int					ft_power(int x, int n);
int					ft_atoi(const char *str);
int					ft_hexatoi(const char *str);
bool				ft_is_decimal(char *str);
char				ft_toupper(char c);
uint64_t			*hstr_to_64_t(uint64_t *x, int64_t len_64, char *str, bool yel_msg);
char				**malloc_empty_str_tab(void);
int					free_ok(void *ptr);
int					free_split(char **tab);
char				*rm_begin_whitespace(char *str);
char				*rm_multi_whitespace(char *str);
int					get_next_line(int fd, char **line);
void				*ft_rand(void *dest, size_t len);
uint64_t			ft_range(uint64_t src, uint64_t min, uint64_t max);
int				ft_read(t_read *r, char *file);
int64_t			ft_nxt_line(t_read *r, int64_t offset);
int64_t			ft_grep_line(char *str, t_read *r, int64_t offset);

/*
**	ft_printf
*/
int					ft_sprintf(char *str, const char *format, ...);
int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					conv(t_spe *sp, const char *s, va_list *va,
						t_conv const *tab);
void				c_conv(va_list *va, t_spe *sp);
void				s_conv(va_list *va, t_spe *sp);
void				d_conv(va_list *va, t_spe *sp);
void				oux_conv(va_list *va, t_spe *sp);
void				bin_conv(va_list *va, t_spe *sp);
void				undefined_conv(va_list *va, t_spe *sp);
int					extract_specifier(char const *s, t_spe *spe);
void				putchar_buffer(char c, char *buff);
void				putstr_buffer(char *str, char *buff);
void				putnbr_buffer(intmax_t n, char *buff);
void				putbnbr_buffer(uintmax_t n, char *param, char *buff);
void				ft_exit(char *error);
int					catch_pos_numb(char *s);
void				init_spe(t_spe *sp);
char				*add_nose(int n, char c, char *buff);
char				*add_tail(int n, char c, char *buff);
int					write_no_spe(char const *s, t_spe *sp);
void				write_spe(t_spe *sp);
char				*buff_malloc(int *offset, char const *s, t_spe *sp);
void				d_malloc(intmax_t i, t_spe *sp);
void				oux_malloc(uintmax_t i, char b, t_spe *sp);
void				c_malloc(char nb_char, t_spe *sp);
void				s_malloc(char *str, t_spe *sp);
int					utf_32_to_8(wchar_t utf_32, char *utf_8);
/*
** switch endianness
*/
uint32_t			bswap32(uint32_t x);
uint32_t			*multi_bswap32(uint32_t *h, int64_t size);
uint64_t			bswap64(uint64_t x);
uint64_t			*multi_bswap64(uint64_t *h, int64_t size);

#endif
