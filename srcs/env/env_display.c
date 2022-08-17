#include <structs.h>
#include <stdio.h>
/*Legacy code!*/
void env_display(t_env *head)
{
	t_env	*temp;

	if (!head)
		return ;
	temp = head;
	while (temp)
	{
		printf("%s\n", temp->var_together);
		temp = temp->next;
	}
	return ;
}