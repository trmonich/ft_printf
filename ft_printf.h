/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trmonich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:05:36 by trmonich          #+#    #+#             */
/*   Updated: 2019/01/11 15:46:13 by trmonich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF

typedef struct		s_extra
{
	unsigned int	width;
	unsigned int	precision;
	enum			length
	{
		none,
		hh,
		h,
		l,
		ll
	};
	unsigned int	flag_hash : 1;
	unsigned int	flag_zero : 1;
	unsigned int	flag_minus : 1;
	unsigned int	flag_plus : 1;
	unsigned int	flag_space : 1;
}					t_extra;

#endif
