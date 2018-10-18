// TODO header 42

#include <sys/types.h>
#include <unistd.h>
#include "env.h"
#include "utils.h"
#include "builtins.h"
#include "starter.h"
#include "global.h"

/*
** Starts a process and returns it's pid
** Params :
** - proc : process to start
** - forked : start command in new process ? 1:yes/0:no
** Return:
** - (n>0) the new process pid
** - (n<0) error code or builtin's exit status
*/
int	start_process(t_process *proc, int forked)
{
	pid_t		pid;
	t_builtin	*builtin;

	if (!forked && (builtin = search_builtin(proc->args[0])))
		return (-builtin->func(&g_env, proc->args)); // TODO change to command env
	if (!proc->path || !is_there_a_file(proc->path)
			|| !is_executable(proc->path)) // TODO print error msg based on error type
	{
		ft_putendl_fd("Command not found.", 2);
		return (0);
	}
	if ((pid = fork()) < 0)
		exit_error("fork() error");
	if (pid == 0)
	{
		execve(proc->path, proc->args, env_to_array(&g_env)); // TODO change to command env
		exit_error("execve() error");
	}
	return (pid);
}
