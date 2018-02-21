/*
** my_str_isalpha.c for my_str_isalpha in /home/alkoleek/CPool_Day06
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Tue Oct 11 14:25:25 2016 Maxime DROUIN
** Last update Sun Jan 22 13:32:38 2017 Maxime DROUIN
*/

int	my_str_isalpha(char *str)
{
  int	count;

  count = 0;
  while (str[count] != '\0')
    {
      if ((str[count] > 64 && str[count] < 91)
	  || (str[count] > 96 && str[count] < 123)
	  || (str[count] == 95)
	  || (str[count] > 47 && str[count] < 58))
	count = count + 1;
      else
	return (0);
    }
  return (1);
}
