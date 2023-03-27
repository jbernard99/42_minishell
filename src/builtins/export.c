/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:43:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/24 13:44:10 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Export : 
	Working Export cases:
		"export test" 	: Var test will be created without any value -> MUST NOT SHOW IN "env" AFTER, ONLY IN "export"
		"export"		: print envp in order
		"export x =123" : OR "export x= 123"		ERROR '=' must follow var name (No spaces)
		"export x="		: No value, x will equal ""
		"export x=2"	: 2 will become string "2"
		"export x='Bonjour''Allo'123" : Var x will be 'BonjourAllo123'
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *) s1 - *(unsigned char *) s2);
}

char	**get_alpha_envp(char **envp)
{
	char 	**n_envp;
	char	*temp;
	int		i;
	int		j;
	
	n_envp = tabstrdup(envp);
	while (n_envp[i])
	{
		j = i + 1;
		while (n_envp[j])
		{
			if (ft_strcmp(n_envp[i], n_envp[j]) > 0)
			{
				temp = ft_strdup(n_envp[i]);
				n_envp[i] = ft_strdup(n_envp[j]);
				n_envp[j] = ft_strdup(temp);
			}
			j++;
		}
		i++;
	}
	return envp;
}

void	ft_export(char **args, char **envp, int fd_out)
{
	char	**new_envp;
	int		argc;
	int		i;
	
	new_envp = get_alpha_envp(envp);
	argc = ft_strtablen(args);
	i = 1;
	if (argc > 1)
	{
		while (args[i])
		{	
			envp_set_line(envp, get_name(args[i]), get_value(args[i]));
			i++;
		}	
	}
	else
		put_envp(new_envp);
	ft_freetabstr(&new_envp);
}