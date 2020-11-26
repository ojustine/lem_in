#include <unistd.h>

void	ft_putnbr(int n)
{
	static const char	*digits = "0123456789";
	long long			nb;

	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb <= 9)
	{
		write(1, &digits[nb], 1);
		return ;
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}
