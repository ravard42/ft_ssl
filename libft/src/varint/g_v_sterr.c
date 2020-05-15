/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_v_sterr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 03:15:06 by ravard            #+#    #+#             */
/*   Updated: 2020/05/12 03:15:09 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const char		*g_v_sterr[] = {
	"%sg_v_r has been called%s\n",
	"%sV_MAX_LEN must be a multiple of 8 s.t 0 < V_MAX_LEN <= 4096\nexit ...\n",
	"%sv.len <= 0 or v.len > MAX_LEN%s\n",
	"%scorrupted varint : len and data doesn't match%s\n",
	"%sdivision by 0%s\n",
	"%sneg pow not handle%s\n",
	"%sexponent lim value overtaken in v_exp%s\n",
	"%selem not inversible for this modulo%s\n",
	"%sasn1 der header len must be <= 0xffff)%s\n",
	"%sder file corrupted or is'not a sequence of integers%s\n",
	"%scan't store asn1_der number, V_MAX_LEN must be >= %d%s\n",
	"%soverflow in v_left_shift, V_MAX_LEN must be >= %d%s\n",
	"%soverflow in v_add|v_sub, V_MAX_LEN must be >= %d%s\n",
	"%soverflow in v_mul, V_MAX_LEN must be >= %d%s\n",
	"%soverflow in v_exp, V_MAX_LEN must be >= %d%s\n",
	"%soverflow in v_expmod|cra, V_MAX_LEN must be >= %d%s\n",
	"%soverflow in v_eea or v_inv, V_MAX_LEN must be >= %d%s\n",
};
