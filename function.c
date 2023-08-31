#include "monty.h"

/**
* pint - print the element at the top of the stack.
* @stack: pointer to pointer to the first element on the stack.
* @line_number: number of the current line.
*Return: 0 if the first element is printed.
*/
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
/**
* pop - function to remove the top element from the stack.
* @stack: pointer to the first element of the stack.
* @line_number: number of the current line.
* Return: 0 if the element is successfully removed.
*/
int pop(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
		 fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	stack_t *temp = *stack;
	*stack = (*stack)->next;

	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(temp);
	return (0);
}
/**
 * swap - swap the first two elements of the stack
 * @stack: pointer to the first element of the stack
 * @line_number: number of the current line
 * Returns: 0 if both elements are swapped
*/
void swap(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	int temp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}
/**
 * add - add the top two elements
 * @stack: pointer to pointer to the first element on the stack
 * @line_number: number of the current line
 * Return: 0 if add the top two elements
*/
int add(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	int sum = (*stack)->n + (*stack)->next->n;
	(*stack)->next->n = sum;
	pop(stack, line_number);
	return (0);
}
/**
 * nop - does nothing
 * @stack: pointer to pointer to the first element on the stack
*/
void nop(stack_t **stack)
{
	(void)stack;
}
