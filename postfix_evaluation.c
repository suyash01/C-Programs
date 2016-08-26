#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct st
{
    int *a;
    int tos,size;
}stack;

void init(stack *s, int n)
{
    s->a = (int *)malloc(sizeof(int)*n);
    s->tos = -1;
    s->size = n;
}

int isempty(const stack *s)
{
    if(s->tos == -1)
        return 1;
    else
        return 0;
}

int isfull(const stack *s)
{
    if(s->tos == s->size)
        return 1;
    else
        return 0;
}

void push(stack *s, int z)
{
    if(!isfull(s))
        s->a[++s->tos] = z;
}

int pop(stack *s)
{
    if(!isempty(s))
        return s->a[s->tos--];
}

int peek(stack *s)
{
    if(!isempty(s))
        return s->a[s->tos];
}

int evaluate(char a[])
{
    int i,r,a1,a2;
    stack s;
    init(&s, (strlen(a)+1)/2);
    for(i=0;a[i]!='\0';i++)
    {
        if(isdigit(a[i]))
            push(&s, a[i]-'0');
        else
        {
            a2 = pop(&s);
            a1 = pop(&s);
            switch(a[i])
            {
                case '+':
                    r = a1+a2;
                    break;
                case '-':
                    r = a1-a2;
                    break;
                case '*':
                    r = a1*a2;
                    break;
                case '/':
                    r = a1/a2;
                    break;
            }
            push(&s, r);
        }
    }
    return pop(&s);
}

int main()
{
    char a[100];
    int res;
    printf("Enter the postfix expression.\n");
    gets(a);
    res = evaluate(a);
    printf("The result is: %d",res);
    return 0;
}
