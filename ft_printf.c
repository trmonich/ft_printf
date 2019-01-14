/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trmonich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:05:00 by trmonich          #+#    #+#             */
/*   Updated: 2019/01/14 15:31:11 by trmonich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdio.h> //test

void	show_extra(t_extra extra)
{
	printf("flags :\n hash: %i\n 0: %i\n -: %i\n space: %i\n +: %i\n width: %i\n precision: %i\n length: %i\n",
			extra.flag_hash, extra.flag_zero, extra.flag_minus, extra.flag_space, extra.flag_plus, extra.width, extra.precision, extra.length);
}

void 			handle_length(const char **format, t_extra *extra)
{
	extra->length = none;
	if (**format == 'h' || **format == 'l')
	{
		printf("\non a bien %c et %c\n", **format, *(*format + 1));
		if ((**format == 'h') && (*(*format + 1) == 'h'))
		{
			extra->length = hh;
			(*format)++;
		}
		else if ((**format == 'l') && (*(*format + 1) == 'l'))
		{
			extra->length = ll;
			(*format)++;
		}
		else if (**format == 'h')
			extra->length = h;
		else if (**format == 'l')
		{
			printf("on passe la");
			extra->length = l;
		}
		(*format)++;
	}
}

void			handle_flags(const char **format, t_extra *extra)
{
	while (**format == '#' || **format == '0' || **format == '-' || **format == '+' || **format == ' ')
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
		(*format)++;
	}
	if (extra->flag_minus)
		extra->flag_zero = 0;
}

void			handle_width(const char **format, t_extra *extra)
{
	extra->width = 0;
	while (ft_isdigit(**format))
	{
		extra->width = extra->width * 10 + (**format - '0');
		(*format)++;
	}
}

void			handle_precision(const char **format, t_extra *extra)
{
	extra->precision = 0;
	if (**format == '.')
	{
		(*format)++;
		while (ft_isdigit(**format))
		{
			extra->precision = extra->precision * 10 + (**format - '0');
			(*format)++;
		}
	}
}

t_extra			handle_extra(const char **format)
{
	t_extra		extra;

	(*format)++;
	handle_flags(format, &extra);
	handle_width(format, &extra);
	handle_precision(format, &extra);
	handle_length(format, &extra);
	return (extra);
}

int		inner(const char *format, va_list *args, size_t len)
{
	t_extra		extra;
	char		*next_arg;

//	printf("-----------on rentre dans inner avec format %s\n", format);
	if (!*format)
		return (len);
	next_arg = ft_strchr(format, '%');
//	printf("next arg : %s", next_arg);
	if (!next_arg)
	{
		ft_putstr(format);
		return (len + ft_strlen(format));
	}
	if (next_arg > format)
	{
		ft_putnstr(format, next_arg - format); //fonction a ajouter
		return (inner(next_arg, args, len + (next_arg - format)));
	}
	extra = handle_extra(&format);
	show_extra(extra);
	ft_putchar(*format);
	format++;
	return (inner(format, args, len)); //il faut changer la len en fonction du type, temporaire
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


int		main()
{
	ft_printf("test %+05.3lls test2\n");
	return (0);
}
