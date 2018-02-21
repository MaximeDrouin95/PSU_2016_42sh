/*
** my_strcpy.c for my_strcpy in /home/alkoleek/CPool_Day06
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Mon Oct 10 12:01:12 2016 Maxime DROUIN
** Last update Fri Jan 20 15:10:34 2017 Maxime DROUIN
*/

char	*my_strcpy(char *dest, const char *src)
{
  int	i;

  i = 0;
  while (src[i] != 0)
    {
      dest[i] = src[i];
      i = i + 1;
    }
  dest[i] = 0;
  return (dest);
}
