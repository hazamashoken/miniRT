/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nta.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:25:48 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/30 11:27:12 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NTA_H
# define NTA_H

int		nta_size(void **array);
void	nta_free(void **array);
void	**nta_new(void *p);
void	**nta_add_back(void **array, void *p);
void	**nta_add_front(void **array, void *p);

#endif
