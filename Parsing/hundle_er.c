
int	hundle_error(char *str)
{
	int i = 0;
	
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (0);
		if (str[i] == '>' && (str[i + 1] == '|' || str[i + 1] == '<'))
			return (0);
		if (str[i] == '>' && (str[i + 1] == '|' || str[i + 1] == '<'))
			return (0);
		i++;
	}
	
}