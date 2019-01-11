/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trmonich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:05:00 by trmonich          #+#    #+#             */
/*   Updated: 2019/01/11 15:46:11 by trmonich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void 			handle_length(const char **format, t_extra *extra)
{
	extra->length = none;
	if (**format == 'h' || **format == 'l')
	{
		if ((**format == 'h') && (**(format + 1) == 'h'))
		{
			extra->length == hh;
			*format++;
		}
		else if ((**format == 'l') && (**(format + 1) == 'l'))
		{
			extra->length = ll;
			*format++;
		}
		else if (**format == 'h')
			extra->length = h;
		else if (**format == 'l')
			extra->length = l;
		*format++;
	}
}

void			handle_flags(const char **format, t_extra *extra)
{
	while (**format == '#' || **format = '0' || **format = '-' || **format = '+' || **format = ' ')
	{
		if (**format == '#')
			extra->flag_hash = 1;
		if (**format == '0')
			extra->flag_zero = 1;
		if (**format == '-')
			extra->flag_minus = 1;
		if (**format == '+')
			extra->flag_plus = 1;
		if (**format == ' ')
			extra->flag_space = 1;
		*format++;
	}
	if (extra->flag_minus)
		flag_zero = 0;
}

t_extra			handle_extra(const char **format)
{
	t_extra		extra;

	*format++;
	handle_length(format, &extra);

}

int		inner(const char *format, va_list *args, size_t len)
{
	t_extra		extra;
	char		*next_arg;

	if (!*format)
		return (len);
	next_arg = ft_strchr(format, '%');
	if (!next_arg)
		ft_putstr(format);
	if (next_arg > format)
	{
		ft_putnstr(format, next_arg - format); //fonction a ajouter
		return (inner(next_arg, args, len + (next_arg - format)));
	}
	extra = handle_extra();
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	int			res;

	va_start(args, format);
	res = inner(format, &args, 0);
	va_end(args);
	return (res);
}
