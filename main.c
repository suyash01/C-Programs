#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct st
{
    char *a;
    int tos,size;
}stack;

void init(stack *s, int n)
{
    s->a = (char *)malloc(n);
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

void push(stack *s, char z)
{
    if(!isfull(s))
        s->a[++s->tos] = z;
}

char pop(stack *s)
{
    if(!isempty(s))
        return s->a[s->tos--];
}

char peek(stack *s)
{
    if(!isempty(s))
        return s->a[s->tos];
}

int prcd(char ch)
{
    if(ch == '*' || ch == '/' || ch == '%')
        return 3;
    else if(ch == '+' || ch == '-')
        return 2;
    else
        return 1;
}

char * convert(char a[])
{
    static char b[100];
    stack s;
    int j,i;
    char z;
    init(&s, strlen(a));
    for(i=0,j=0;a[i]!='\0';i++)
    {
        if(isalnum(a[i]))
            b[j++] = a[i];
        else
        {
            switch(a[i])
            {
                case '(':
                    push(&s, a[i]);
                    break;
                case ')':
                    do{
                        z = pop(&s);
                        if(z!='(')
                            b[j++] = z;
                    }while(z!='(');
                    break;
                default :
                    while(!isempty(&s) && prcd(peek(&s))>=prcd(a[i]))
                        b[j++] = pop(&s);
                    push(&s, a[i]);
            }
        }
    }
    while(!isempty(&s))
        b[j++] = pop(&s);
    b[j] = '\0';
    return b;
}

int main()
{
    char a[100];
    char *b;
    printf("Enter an infix expression.\n");
    gets(a);
    b = convert(a);
    printf("The postfix expression is.\n%s",b);
    return 0;
}
