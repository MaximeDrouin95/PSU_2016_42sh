/*
** my_strncpy.c for my_strncpy in /home/alkoleek/CPool_Day06
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Mon Oct 10 12:52:50 2016 Maxime DROUIN
** Last update Tue Oct 11 20:03:45 2016 Maxime DROUIN
*/

char	*my_strncpy(char *dest, char *src, int n)
{
  int	count;

  count = 0;
  while (count < n)
    {
      if (*src != '\0')
	{
	  *dest = *src;
	  src = src + 1;
	}
      else
	*dest = '\0';
      dest = dest + 1;
      count = count + 1;
    }
  dest = dest - count;
  return (dest);
}
