#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "RTv1.h"

int strlen_while_dig(char *str)
{
	int len;
	char stop;

	len = 0;
	while (str)
	{
		if (!ft_isdigit(*str))
			break ;
		str++;
		len++;
	}
	return len;
}

double ft_atof(char *str)
{
	double ret;
	double mod;
	int	neg;

	while ((*str == '\n') || (*str == '\t') || (*str == '\v') ||
			(*str == ' ') || (*str == '\f') || (*str == '\r'))
		str++;
	neg = (*str == '-' ? 1 : 0);
	ret = 0.0;
	ret = (double)ft_atoi(str);
	
	if (!ft_strchr(str, '.'))
		return (ret);
	str = ft_strchr(str, '.') + 1;
	if (ft_isdigit(*str))
	{
		mod = (double)ft_atoi(str);
		mod /= pow(10, strlen_while_dig(str));
		
		ret += (neg ? -mod : mod);
	}
	//printf("ret\t%f\n", ret);
	return (ret);
}
