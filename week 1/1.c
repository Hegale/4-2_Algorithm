#include <stdio.h>
#include <stdlib.h>

/*
순위 r은 head = 0부터 1씩 증가한다고 가정.
*/

typedef struct	s_node{
    char	elem;
    struct s_node *prev;
    struct s_node *next;
}	t_node ;

int	list_size(t_node **list)
{
	t_node	*p = *list;
	int		r = 0;

	while (p)
	{
		p = p->next;
		r++;
	}
	return (r - 2);
}

// 크기보다 크거나 작은 r에 대한 예외처리 X
int	add(t_node **list, int r, char e)
{
	t_node	*p = *list;
	t_node	*new;
	int		size;

	size = list_size(list);
	if (r < 1 || r > size + 1)
		return (-1);
	// rank의 직전 노드로 p를 설정
	for (int i = 0; i < r - 1; ++i)
		p = p->next;
	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->elem = e;
	p->next->prev = new;
	new->next = p->next;
	p->next = new;
	new->prev = p;
	return (0);
}

int	delete(t_node **list, int r)
{
	t_node	*p = *list;
	int		size;

	size = list_size(list);
	if (r < 1 || r > size)
		return (-1);
	for (int i = 0; i < r; ++i)
		p = p->next;
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
	return (0);
}

char	get_entry(t_node **list, int r)
{
	t_node	*p = *list;
	int		size;

	size = list_size(list);
	if (r < 1 || r > size)
		return (-1);
	for (int i = 0; i < r; ++i){
		p = p->next;
	}
	return (p->elem);
}

void	print(t_node **list)
{
	t_node	*p = *list;

	while (p)
	{
		printf("%c", p->elem);
		p = p->next;
	}
	printf("\n");
}



int	main()
{
	t_node	*head;
	t_node	*tail;
	int		n;
	int		r;
	char	calc;
	char	elem;
	int		out;

	// 초기화5
	head = (t_node *)malloc(sizeof(t_node));
	tail = (t_node *)malloc(sizeof(t_node));
	head->next = tail;
	head->prev = NULL;
	tail->prev = head;
	tail->next = NULL;

	// 입력
	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; ++i)
	{
		scanf("%c", &calc);
		getchar();
		if (calc == 'P'){
			print(&head);
			continue ;
		}
		scanf("%d", &r);
		getchar();
		if (calc == 'G')
		{
			out = get_entry(&head, r);
			if (out == -1)
				printf("invalid position\n");
			else
				printf("%c\n", out);
			continue ;
		}
		else if (calc == 'D')
		{
			out = delete(&head, r);
			if (out == -1)
				printf("invalid position\n");
			continue ;
		}
		scanf("%c", &elem);
		getchar();
		if (calc == 'A'){
			out = add(&head, r, elem);
			if (out == -1)
				printf("invalid position\n");
		}
	}
	printf("\n");
	return (0);
}
