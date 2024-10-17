/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 04:03:15 by shamzaou          #+#    #+#             */
/*   Updated: 2024/10/17 16:24:15 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		code;

	if (argc != 5 && argc != 6)
	{
		return (error_handler(1));
	}
	if (parse_and_initialise(argv, &rules))
	{
		return (error_handler(3));
	}
	if (simulation(&rules))
	{
		return (error_handler(2));
	}
	return (EXIT_SUCCESS);
}
