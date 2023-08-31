#include "monty.h"
/**
 * _isdigit - checks if a string is a number
 * @num: character to test
 * Returns: 1 if it is a number, 0 otherwise
*/
int _isdigit(int num)
{
    if (num >= '0' && num <= '9')
    {
        return (1);
    }
    else
    {
        return (0);
    }
}
/**
 * push - function to add a new element to the top of the stack
 * @stack - pointer to the first element on the stack
 * @line_number: current line number.
 * return: 0 if the element is successfully added to the stack.
*/
int push(stack_t **stack, unsigned int line_number)
{
    char *numchar = NULL;
    int num = 0;
    stack_t *new_node = NULL;

    numchar = strtok(NULL, "\t\n");

    if (numchar == NULL)
    {
        fprintf(stderr, "L%u: usage: push integer", line_number);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; numchar[i] != '\0'; i++)
    {
        if (!_isdigit(numchar[i]) && numchar[i] != '-')
        {
            fprintf(stderr, "L%u: usage: push integer", line_number);
            exit(EXIT_FAILURE);
        }
    }
    num = atoi(numchar);
    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->n = num;
    new_node->prev = NULL;
    new_node->next = *stack;
    if (*stack != NULL)
        (*stack)->prev = new_node;
    *stack = new_node;
    return (0);
}
/**
* pall - print all elements in the stack
* @stack: pointer to pointer to the first element on the stack
* Return: 0 if stack prints successfilly
*/
int pall(stack_t **stack)
{
    stack_t *current = *stack;

    if (current == NULL)
        return (0);
    
    while(current != NULL)
    {
        if (current->n)
            printf("%u\n", current->n);
        else
            printf("%u\n", 0);
        current = current->next;
    }
    return (0);
}
/**
 * free_all - frees everything left over
 * @stack: pointer to the first element of the stack
 * @buffer: is the imput
*/
void free_all(stack_t *stack, char *buffer)
{
    while (stack != NULL)
    {
        stack_t *next_node = stack->next;

        free(stack);
        stack = next_node;
    }
    free(buffer);
}
/**
 * main - program input
 * @argc: number of arguments passed on command line
 * @argv: index of strings containing arguments passed on command line
 * Return: 0 if the program is executed successfully
*/
int main(int argc, char **argv)
{
    stack_t *stack = NULL;
    char *buffer = NULL, *code = NULL;
    size_t buffsize = 0;
    unsigned int line_number = 0;
    FILE *file = NULL;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file");
        exit(EXIT_FAILURE); }
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        exit(EXIT_FAILURE); }
    while (getline(&buffer, &buffsize, file) != -1)
    {
        line_number++, code = strtok(buffer, "\t\n");
        if (code == NULL)
            continue;
        if (strcmp(code, "push") == 0)
            push(&stack, line_number);
        else if (strcmp(code, "pall") == 0)
            pall(&stack);
        else if (strcmp(code, "pint") == 0)
            pint(&stack, line_number);
        else if (strcmp(code, "pop") == 0)
            pop(&stack, line_number);
        else if (strcmp(code, "swap") == 0)
            swap(&stack, line_number);
        else if (strcmp(code, "add") == 0)
            add(&stack, line_number);
        else if (strcmp(code, "nop") == 0)
            nop(&stack);
        else
        {
            fprintf(stderr, "L%u: unknown instruction %s", line_number, code);
            exit(EXIT_FAILURE); } 
        }
    fclose(file), free_all(stack, buffer);
    return (0); 
}