/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mhaan <mhaan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 16:09:56 by mhaan         #+#    #+#                 */
/*   Updated: 2023/08/18 15:47:29 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// includes
# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

// prototypes
int	ft_printf(const char *fmt, ...);
int	put_uns_base(unsigned long long n, int base, char fmt);
int	put_sign_dec(int n, char fmt);
int	put_str_printf(char *str);
int	put_chr_printf(char c);
int	put_ptr(uintptr_t n);

#endif
