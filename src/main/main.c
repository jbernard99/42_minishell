/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/03 15:48:24 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ctrlc_handle(){
	ft_putchar_fd('\n', 1); 							// Jump on a clean line
	rl_on_new_line();									// Tell readline we are on a new line
	rl_replace_line("", 0);								// Replace readline buffer with empty
	rl_redisplay();										// Rewrite prompt with empty str
}

void sigquit_handle(int sig){
	//It's not because a function does nothing that it's useless
	(void)sig;
}

void	ez_divide(t_cmdlst *cmdlst)
{
	char	*token;
	size_t	old_size;

	old_size = 0;
	token = ft_strtok(cmdlst->cmd, " ", &cmdlst->flags);
	write(1, "ok\n", 2);
	// if (!cmd_is_builtin(token)){
	// 	token = ft_strjoin("/bin/", token);
	// 	printf("Result");
	// }
	while (token != NULL)
	{
		cmdlst->token = realloc(cmdlst->token, old_size + 1);
		cmdlst->token[old_size] = token;
		token = ft_strtok(NULL, " ", &cmdlst->flags);
		old_size++;
	}
}

void	prompt_loop(t_cmdlst *cmdlst){
	while (1){
		char* input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		add_history(input);								// Add current input to the history list
		ez_divide(cmdlst);
		free(input);
	}
}

void set_new_termios(struct termios old_termios){
	struct termios new_termios;
	
	new_termios = old_termios;
	new_termios.c_cc[VQUIT] = _POSIX_VDISABLE;			// Disable printing of ^\ when doing ctrl-\ --
	new_termios.c_lflag &= ~ECHOCTL;					// Disable printing of ^c when doing ctrl-c
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);		// Set new settings to current terminal
}

int main(int argc, char **argv, char **envp) {
	struct termios old_termios;
	t_cmdlst *cmdlst;

	cmdlst = get_lst();
	tcgetattr(STDIN_FILENO, &old_termios);				// Get parent terminal settings
	set_new_termios(old_termios);
	
	signal(SIGINT, ctrlc_handle);
	signal(SIGQUIT, sigquit_handle);
	
	(void)argc;
	(void)argv;
	(void)envp;
	
	prompt_loop(cmdlst);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);		// Go back to old terminal settings.
	
	return 0;
}