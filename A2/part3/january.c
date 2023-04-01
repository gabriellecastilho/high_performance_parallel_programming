#include <stdio.h>
#include <stdlib.h>

typedef struct	node {
	int		index;
	float	max;
	float	min;
	struct	node	*next;
}	node_t;

void add_node(node_t **node, int index, float min, float max)
{
	if (*node == NULL) // add first node or at the end of table
	{
		*node = (node_t *)malloc(sizeof(node_t));
		(**node).index = index;
		(**node).min = min;
		(**node).max = max;
		(**node).next = NULL;
	}

	else if ((**node).index == index) // update node
	{
		(**node).min = min;
		(**node).max = max;
	}

	else if ((**node).next == NULL && (**node).index < index) //add node at the beginning of table or after root
		add_node(&(**node).next, index, min, max);

	else if ((**node).index > index) //add node before root
	{
		node_t *old_root = (node_t *)malloc(sizeof(node_t));
		(*old_root).index = (**node).index;
		(*old_root).min = (**node).min;
		(*old_root).max = (**node).max;
		(*old_root).next = (**node).next;
		(**node).index = index;
		(**node).min = min;
		(**node).max = max;
		(**node).next = old_root;
	}

	else if (((**node).next == NULL) || ((**node).next->index < index)) //move forward in the table
	{
		add_node(&(**node).next, index, min, max);
	}

	else //Add node in between two nodes
	{
		node_t *new_node = (node_t *)malloc(sizeof(node_t));
		(*new_node).index = index;
		(*new_node).min = min;
		(*new_node).max = max;
		(*new_node).next = (**node).next;
		(**node).next = new_node;
	}
}

void print_table(node_t *node)
{
	if (node != NULL)
	{
		printf("%d	%f	%f \n", node->index, node->min, node->max);
		print_table(node->next);
	}
}

void delete_node(node_t **node, int index)
{
	if ((**node).index == index)
	{
		node_t *old_node = *node;
		*node = (**node).next;
		free(old_node);
	}
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
	node_t *root = NULL;
	while (1)
	{
		char	command;
		int		index;
		float	min;
		float	max;

		printf("Enter command: ");
		scanf(" %c", &command);
		if (command == 'A' || command == 'a')
		{
			scanf(" %d", &index);
			scanf(" %f", &min);
			scanf(" %f", &max);
			add_node(&root, index, min, max);
		}
		else if (command == 'P' || command == 'p')
		{
			printf("day	min		max\n");
			if (root != NULL)		
				print_table(root);
		}
		else if (command == 'D' || command == 'd')
		{
			scanf(" %d", &index);
			delete_node(&root, index);
		}
		else if (command == 'Q' || command == 'q')
		{
			delete_all(root);
			break;
		}
		else
			printf("Command not found\n");
	}
}

int	main(void)
{
	run_program();
	return (0);
}