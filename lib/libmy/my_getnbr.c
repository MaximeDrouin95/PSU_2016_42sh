/*
** my_getnbr.c for my_getnbr in /home/alkoleek/delivery
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Thu Oct  6 23:33:38 2016 Maxime DROUIN
** Last update Tue Oct 11 19:57:53 2016 Maxime DROUIN
*/

#include "libmy.h"

long long	get_sign(char *str)
{
  long long	sign;

  str = str - 1;
  if (*str == '-')
    sign = -1;
  else
    sign = 1;
  str = str + 1;
  return (sign);
}

int	verify_number(long long output_number)
{
  if (output_number > 2147483647)
    return (0);
  else if (output_number < -2147483648)
    return (0);
  else
    return (output_number);
}

int	verify_array(int count_array)
{
  if (count_array > 10 || count_array == 0)
    return (0);
  else
    return (1);
}

long long	calculate_number(char *str, int count, int output_number)
{
  long long	multiplier;
  long long	temp_array[100];

  multiplier = 1 * get_sign(str);
  while (*str >= 48 && *str <= 57)
    {
      temp_array[count] = *str - 48;
      str = str + 1;
      count = count + 1;
    }
  if (verify_array(count))
    {
      count = count - 1;
      while (count >= 0)
	{
	  output_number = output_number + (temp_array[count] * multiplier);
	  count = count - 1;
	  multiplier = multiplier * 10;
	}
    }
  else
    output_number = 0;
  return (output_number);
}

int		my_getnbr(char *str)
{
  int		count;
  long long	output_number;
  count = 0;
  output_number = 0;
  while (*str < 48 || *str > 57)
    str = str + 1;
  output_number = calculate_number(str, count, output_number);
  return (verify_number(output_number));
}
