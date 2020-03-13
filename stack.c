#include <stdlib.h>
#include "stack.h"

int stack_Pop (struct stack **this, int *v)
{
	if (!*this)
		return 1;
	int value = (*this)->value;
	struct stack *next = (*this)->next;
	stack_Destroy(*this);
	*this = next;
	if (v)
		*v = value;
	return 0;
}

struct stack *stack_New (int v)
{
	struct stack *this;
	this = malloc(sizeof(struct stack));
	this->value = v;
	this->next = NULL;
	return this;
}

void stack_Destroy (struct stack *this)
{
	free(this);
}

void stack_Push (struct stack **this, int v)
{
	struct stack *new = stack_New(v);
	new->next = *this;
	*this = new;
}
