
#include "libft.h"

int		ft_toupper(int c)
{
	if (c < 97)
		return (c);
	else if (c > 122)
		return (c);
	return (c - 32);
}
