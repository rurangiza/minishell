char *expand_variable(char *buffer)
{
	int start;
	int end;
	int index;
	
	// Find start
	start = ft_strchr_mod(buffer, '$') + 1;
	// Find end
	end = start;
	while (buffer[end] && !ft_isspace(buffer[end]))
		end++;
	// Isolate the variable
	char *variable = ft_substr(buffer, start, end - start);
	// Check if variable exists in envp

	//getenv(variable);
	
	index = 0;
	while (envp[index])
	{
		if (ft_strnstr(envp[index], variable, ft_strlen(variable)) && envp[index][ft_strlen(variable)] == '=') // hello [HOME] nothing
		{
			// if so, join its content to start of buffer
			char *s1 = ft_substr(buffer, 0, start - 1);					
			char *s2 = envp[index] + ft_strlen(variable) + 1;
			char *s3 = buffer + end;
			char *tmp = ft_strjoin_trio(s1, s2, s3);
			free(variable);
			stash = ft_strjoin_mod(stash, tmp);
			index = -1;
			break ;
		}
		index++;
	}
	if (index != -1)
	{
		// else, join start of buffer with rest ignoring the variable part
		char *s1 = ft_substr(buffer, 0, start - 1);
		char *s2 = buffer + end;
		char *tmp = ft_strjoin_mod(s1, s2); // to free
		stash = ft_strjoin_mod(stash, tmp);
	}
}