#include <unistd.h>

int main(void)
{
	extern char **environ;
	char *env[3];

	env[2] = NULL;
	env[1] = "this=ha ha ha";
	env[0] = "export";
	execve("export",&env[0],environ);
}