/*
** my_strcat.c for my_strcat in /home/alkoleek/CPool_Day07
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Wed Oct 12 09:22:44 2016 Maxime DROUIN
** Last update Sat Jan 21 13:49:33 2017 Maxime DROUIN
*/

char	*my_strcat(char *dest, char *src)
{
  int	count;
  int	count_2;

  count = 0;
  count_2 = 0;
  while (dest[count] != '\0')
    count = count + 1;
  while (src[count_2] != '\0')
    {
      dest[count] = src[count_2];
      count = count + 1;
      count_2 = count_2 + 1;
    }
  dest[count] = '\0';
  return (dest);
}
