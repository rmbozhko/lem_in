/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_visual_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 13:18:47 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/13 12:45:28 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static	void		fifth_line(void)
{
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\t");
	printf(ERROR_SIGN);
	printf("    ");
	printf(ERROR_SIGN);
	printf("\t");
	printf(ERROR_SIGN);
	printf("    ");
	printf(ERROR_SIGN);
	printf("\t");
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf("    ");
	printf(ERROR_SIGN);
}

static	void		forth_line(void)
{
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf("   ");
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf("   ");
	printf(ERROR_SIGN);
	printf("\t       ");
	printf(ERROR_SIGN);
	printf("   ");
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf("   ");
	printf(ERROR_SIGN);
	printf("\n");
	fifth_line();
}

static	void		third_line(void)
{
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\t       ");
	printf(ERROR_SIGN);
	printf("   ");
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\n");
	forth_line();
}

static	void		second_line(void)
{
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf("   ");
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf("   ");
	printf(ERROR_SIGN);
	printf("\t       ");
	printf(ERROR_SIGN);
	printf("   ");
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf("   ");
	printf(ERROR_SIGN);
	printf("\n");
	third_line();
}

void				ft_handle_error(void)
{
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\t");
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\t\t");
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf(ERROR_SIGN);
	printf("\n");
	second_line();
	printf("\n");
}
