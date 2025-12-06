/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 10:08:57 by homura            #+#    #+#             */
/*   Updated: 2025/12/06 10:13:29 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft/includes/libft.h"

void	print_error_exit(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}
