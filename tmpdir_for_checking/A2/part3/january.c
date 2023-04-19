#include <stdio.h>
#include <stdlib.h>

typedef struct	node {
	int			day;
	float		min;
	float		max;
	struct node	*next;
}	node_t;

void add_node(node_t **node, int day, float min, float max)
{
	node_t *new_node;

	if (*node == NULL)
	{
		*node = (node_t *)malloc(sizeof(node_t));
		(*node)->day = day;
		(*node)->min = min;
		(*node)->max = max;
		(*node)->next = NULL;
	}
	else if (day == (*node)->day)
	{
		(*node)->min = min;
		(*node)->max = max;
	}
	else if (day < (*node)->day)
	{
		new_node = (node_t *)malloc(sizeof(node_t));
		new_node->next = *node;
		*node = new_node;
		new_node->day = day;
		new_node->min = min;
		new_node->max = max;
	}
	else if (day > (*node)->day)
	{
		add_node(&(*node)->next, day, min, max);
	}
}

void print_table(node_t *node)
{
	if (node != NULL)
	{
		printf("%d	%f	%f \n", node->day, node->min, node->max);
		print_table(node->next);
	}
}

void delete_node(node_t **node, int day)
{
	node_t *temp;

	if (*node == NULL)
		return;
	else if ((*node)->day == day)
	{
		temp = *node;
		*node = (*node)->next;
		free(temp);
	}
	else
		delete_node(&(*node)->next, day);
}

void delete_all(node_t *node)
{
    if (node == NULL)
		return;
    delete_all(node->next);
    free(node);
}

void run_program()
{
	node_t	*head;
	char	command;
	int		day;
	float	min;
	float	max;

	head = NULL;
	printf("Enter command: ");
	scanf(" %c", &command);
	while (command)
	{
		if (command == 'A' || command == 'a')
		{
			scanf(" %d  %f  %f", &day, &min, &max);
			add_node(&head, day, min, max);
		}
		else if (command == 'P' || command == 'p')
		{
			printf("day	min		max\n");
			if (head != NULL)		
				print_table(head);
		}
		else if (command == 'D' || command == 'd')
		{
			scanf(" %d", &day);
			delete_node(&head, day);
		}
		else if (command == 'Q' || command == 'q')
		{
			delete_all(head);
			printf("Goodbye\n");
			break;
		}
		else
			printf("Command not found\n");
		printf("Enter command: ");
		scanf(" %c", &command);
	}
}

int	main(void)
{
	run_program();
	return (0);
}
