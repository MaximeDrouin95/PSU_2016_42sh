/*
** my_strncmp.c for strncmp in /home/alkoleek/CPool_Day06
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Mon Oct 10 23:17:24 2016 Maxime DROUIN
** Last update Tue Oct 11 20:03:11 2016 Maxime DROUIN
*/

int     my_strncmp(char *s1, char *s2, int n)
{
  int   count;

  count = 0;
  while (count < n)
    {
      if (s1[count] != s2[count])
	{
	  if (s1[count] == '\0' && s2[count] != '\0')
	    return (-1);
	  if (s2[count] == '\0' && s1[count] != '\0')
	    return (1);
	  if (s1[count] < s2[count])
	    return (-1);
	  if (s1[count] > s2[count])
	    return (1);
	}
      count = count + 1;
    }
  return (0);
}
