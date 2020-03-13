#ifndef STACK_h
#define STACK_h 1
struct stack {
	int value;
	struct stack *next;
};

int stack_Pop (struct stack **this, int *v);
struct stack *stack_New (int v);
void stack_Destroy (struct stack *this);
void stack_Push (struct stack **this, int v);
#endif
