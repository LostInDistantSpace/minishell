/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:24:31 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/17 16:25:43 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_in_out(t_data *data)
{
	close(data->save_in);
	close(data->save_out);
}

void	restore_in_out(t_data *data)
{
	dup2(data->save_in, STDIN_FILENO);
	dup2(data->save_out, STDOUT_FILENO);
}