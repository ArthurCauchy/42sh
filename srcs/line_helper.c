#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "line_edit.h"

int			dslash_before(char *line, int index)
{
	int		i;
	int		j;

	i = 0;
	j = index - 1;
	while (j >= 0 && line[j] == '\\')
	{
		i++;
		j--;
	}
	if (!(i % 2))
		return (1);
	return (0);
}

unsigned long	get_key(void)
{
	unsigned char	buff[6];

	ft_bzero(buff, 6);
	read(0, buff, 6);
	return (buff[0] + (buff[1] << 8) + (buff[2] << 16) + (buff[3] << 24) + \
			((unsigned long)buff[4] << 32) + ((unsigned long)buff[5] << 40));
}

char		**path(char **env)
{
	while (env && *env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			return (ft_split(*env + 5, ":"));
		env++;
	}
	return (NULL);
}

