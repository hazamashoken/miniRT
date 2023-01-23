/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:29:10 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/23 15:35:51 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMS_H
# define PARAMS_H

# include "libft.h"

int		isnum(char *str);
int		count_bits(int n);
int		ft_strarrlen(char **arr);
int		check_params(char **params, int type, int flag);
void	set_material(t_obj *new, char **params, int i, int flag);

#endif
