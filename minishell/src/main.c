/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:24:46 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 19:35:39 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_main(int argc, char *argv[])
{
	printf("\n\e[100m\e[96m       Minishell       \e[0m\n");
	printf("\e[36m _____           _____ \n");
	printf("/  ___|         /  ___|\n");
	printf("\\ `--.   \e[32m_ __\e[36m   \\ `--. \n");
	printf(" `--. \\ \e[32m| '_ \\\e[36m   `--. \\\n");
	printf("/\\__/ / \e[32m| | | |\e[36m /\\__/ /\n");
	printf("\\____/  \e[32m|_| |_|\e[36m \\____/ \e[0m\n\n");
	(void)argc;
	(void)argv;
}

// 명령어 1개이고, export, unset, cd, exit 중 하나일 때 메인에서 처리하기 위한 함수
int	check_export_unset_exit(char **cmd, int size, t_env *env)
{
	// 명령어가 1개이고, 아래 명령어에 해당하면 메인 프로세스에서 처리
	if (size == 1)
	{
		if (!ft_strncmp("export", cmd[0], 7))
			g_err = ft_export(env, cmd);
		else if (!ft_strncmp("unset", cmd[0], 6))
			g_err = ft_unset(env, cmd);
		else if (!ft_strncmp("cd", cmd[0], 3))
			g_err = ft_cd(env, cmd[1]);
		else if (!ft_strncmp("exit", cmd[0], 5))
			ft_exit(cmd);
		else
			return (-1);
		return (g_err);
	}
	return (-1);
}

// Minishell 실행 전 초기 세팅을 위한 함수
static t_env	*init(int argc, char **argv, char **envp)
{
	t_env	*env;

	// Minishell 시작 문구
	print_main(argc, argv);

	// stdin, stdout 백업해두기
	dup2(STDIN_FILENO, BACKUP_STDIN);
	dup2(STDOUT_FILENO, BACKUP_STDOUT);

	// 환경변수와 시그널 세팅
	env = NULL;
	set_signal();
	env_parsing(envp, &env);

	return (env);
}

// 파싱 결과를 사용해 명령어를 실행하기 위한 함수
static void	go_to_exec(char *str, t_list *cmd, t_list *redi, t_env *env)
{
	int	idx;

	idx = -1;
	// 빈 명령줄이면 패스
	if (!ft_strlen(str))
		return ;
	
	// 공백 넘기기 + 공백으로만 이루어진 명령줄이면 패스
	while (str[++idx] == ' ')
		;
	if (str[idx] == '\0')
		return ;

	// 명령줄 parsing해서 cmd와 redirect 리스트 만들기
	if (!parsing(str, env, cmd, redi))
	{
		// 명령어가 하나고, export, unset, cd, exit면 메인 프로세스에서 실행
		if (check_export_unset_exit((char **)cmd->next->content,
				ft_lstsize(cmd) - 1, env) != -1)
		{
			free_cmd_list(cmd);
			free_redirect_list(redi);
		}
		else
			// 아니면 명령어 수행 프로세스에서 실행
			cmd_redirect_exec(cmd, redi, env);
	}
	else
		g_err = 258;	// parsing 에러시 종료 코드 258로 변경

	// 명령줄 히스토리에 추가 및 free
	add_history(str);
	free(str);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_env	*env;
	t_list	*cmd;
	t_list	*redirect;

	// 초기 세팅 및 환경변수 세팅
	env = init(argc, argv, envp);
	while (1)
	{
		// cmd, redirect 리스트 초기화
		cmd = ft_lstnew(0);
		redirect = ft_lstnew(0);

		// 명령줄 입력받기
		str = readline("\e[94mprompt > \e[0m");

		// 명령이 있으면 실행
		if (str)
			go_to_exec(str, cmd, redirect, env);
		else
		{
			printf("exit\n");
			break ;
		}
	}
	return (0);
}
