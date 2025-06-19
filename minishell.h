/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorun <etorun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:02:07 by etorun            #+#    #+#             */
/*   Updated: 2025/06/19 18:55:03 by etorun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>

enum e_enlist
{
	EMPTY,
	FIRST,
	ARGUMENT,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
};

typedef struct s_token
{
	char			*con;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_dt
{
	char	*line;
	t_token	**head;
	char	**c_arr;
	char	**temp;
	char	**argv;
	char	**envp;
	char	*p_command;
	char	*sta;
	char	*dol;
	char	*finish;
	char	*var;
	char	*e_val;
	int		sq;
	int		dq;
	int		w;
	int		std_in;
	int		std_out;
	int		cur_read;
	int		cur_write;
	size_t	flag;
	int		pf;
	char	*oldpwd;
	char	*home;
}	t_dt;

size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int sta, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strpathjoin(char const *s1, char const *s2, int i, int j);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	**ft_split(char const *s, char c);
void	work_again(t_dt *dt);
int		ex_code(int new);
void	use_err(char *s, int fd);
void	e_err(char *s, int fd, int code, char *special);
void	e_ex(char *s, char *special);
void	free_command(t_dt *dt);
void	free_all(t_dt *dt);
void	dt_init(t_dt *dt, char **argv, char **envp);
int		cntlline(t_dt *dt, char *cntl);
void	tab_replacer(t_dt *dt);
int		first_pipe(char *c);
int		pipecntl(char *c);
int		parser(t_dt *dt, char *cur);
void	env_check(t_dt *dt);
t_token	*ntok(int type, void *con);
void	token_add(t_dt *dt, t_token *new);
void	def_q(char *cur, t_dt *dt);
void	reset_q(t_dt *dt);
char	*concat(t_token *tok, char *counter, t_dt *dt, int i);
char	*ex_code_add(char *whole, char *raw, char *sta, t_dt *dt);
char	*q_remover(char *sta, char *cur, char *new, t_dt *dt);
int		ft_pwd(void);
int		ft_env(t_dt *dt);
int		ft_echo(t_dt *dt, int flag, int i);
int		ft_cd(t_dt *dt, char **c_arr, int flag, char *curpwd);
int		ft_export(t_dt *dt);
int		ft_unset(t_dt *dt);
int		ft_exit(t_dt *dt);
int		exe(t_dt *dt, t_token *cur);
t_token	*counttoken(int *counts, t_token *tok);
t_token	*c_maker(t_dt *dt, int x, int start, t_token *tok);
char	*c_exist(t_dt *dt, char *cmd, char **envp);
void	freeandleave(t_dt *dt);
void	handle_redir(t_token *tok);

#endif