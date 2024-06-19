#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define size_str 200
#define gramar(symbol) (('a' <= symbol) && (symbol <= 'z'))
#define number(symbol) (('0' <= symbol) && (symbol <= '9'))
#define operation(symbol) ((symbol == '+') || (symbol == '-') || (symbol == '*') || (symbol == '/'))


struct nodelist
{
    char inf;
    struct nodelist *next;
};

struct Steklist
{
    struct nodelist *top;
    int size;
};

typedef struct nodelist node;
typedef struct Steklist stek;


bool push(stek *st, char val)
{
    if(st)
    {
        node *new_el = (node*) malloc(sizeof(node));
        if(new_el)
        {
            new_el -> inf = val;
            new_el -> next = NULL;
            if(st -> top == NULL)
            {
                st -> top = new_el;
            }
            else
            {
                new_el -> next = st -> top;
                st -> top = new_el;
            }
            st -> size++;
            return true;
        }
    }
    return false;
}

char pop(stek *st)
{
    if(st)
    {
        if(st -> top)
        {
            char elem = st -> top -> inf;
            node *ptrIx = st -> top;
            st -> top = st -> top -> next;
            st -> size--;
            free(ptrIx);
            return elem;
        }
    }
    return 0;
}

bool ShowTop(stek *st, char *val)
{
    bool ans = false;
    if(st && val)
    {
        if(st -> top)
        {
            *val = st -> top -> inf;
            ans = true;
        }
    }
    return ans;
}

void print_stack(stek st)
{
    if(st.top == NULL)
        printf("Stack is empty!\n");
    node *current = st.top;
    while(current)
    {
        printf("%c\n", current -> inf);
        current = current -> next;
    }
}

bool isEmpty(stek st)
{
    if(st.top == NULL)
        return true;
    return false;
}

void delStek(stek *st)
{
    if(st)
    {
        if(st -> top)
        {
            node *ptr = st -> top;
            node *ptrIx = NULL;
            while(ptr)
            {
                ptrIx = ptr;
                ptr = ptr -> next;
                st -> size--;
                free(ptrIx);
            }
            st -> top = NULL;
        }
    }
}

bool chek_triple(stek *st)
{
    if(st == NULL)
        return false;
    int pos = 0;
    while(isEmpty(*st) == false)
    {
        char tmp = pop(st);
        if(gramar(tmp) || number(tmp))
            if(pos % 2 == 1)
                return false;
        else
            if(tmp == '(' && pos != 0)
                return false;
            else
                if(tmp == ')' && pos != 2)
                    return false;
                    
        if(operation(tmp))
            if(pos % 2 == 0)
                return false;
        pos++;
    }
    return true;
}

bool check_expression(char *str)
{
    if(str == NULL)
        return false;
    if(strlen(str) == 0)
        return false;

    stek st = {NULL, 0};
    int count = 0;
    for(int i = 0; str[i]; i++)
    {
        if(str[i] == '(')
        {
            count++;
            if(str[i + 1] && str[i + 1] == ')')
                return false;
        }
        else if(str[i] == ')')
        {
            count--;
            if(str[i + 1] && str[i + 1] == '(')
                return false;
        }
        else if(str[i] != ' ')
        {
            if(str[i - 1] && str[i - 1] == '(' && (str[i] == '+' || str[i] == '-'))
                push(&st, '0');
            push(&st, str[i]);
        }
        
        
    }
    if(count != 0)
        return false;
    
    bool flag = true;
    while(flag)
    {
        stek triple = {NULL, 0};
        for(int i = 0; i < 3; i++)
        {
            char tmp = pop(&st);
            push(&triple, tmp);
        }
        if(chek_triple(&triple))
            push(&st, 'v');
        else
            return false;
            
        if(st.size == 2)
            return false;
        if(st.size == 1)
            flag = false;
    }
    return true;
    
}

int main()
{
    //char str[size_str] = "";//uncorrect
    char str[size_str] = "(()";//uncorrect
    //char str[size_str] = " (+ h)";// correct
    //char str[size_str] = " (2)";
    //char str[size_str] = "(2 + (8 * a))";
    //char str[size_str] = "  (2 - ((-1) / h ) + (a /  (-1)))";//correct
    //char str[size_str] = "((c-d)*h+1)*(a+b)";//correct
    //char str[size_str] = "(-d)";//correct
    //char str[size_str] = "f * a * 8 + 1 + a";
    //char str[size_str] = "(-2)";//correct
    //char str[size_str] = "(+2)";//correct
    //char str[size_str] = "((c + d) * h + 1) * (a + b))))))))))))";//uncorrect
    //char str[size_str] = "(a+(b**h) - 8)";//uncorrect
    //char str[size_str] = "(-1) * (-2)";//correct
    //char str[size_str] = "(-1) * ()";//uuncorrect
    //char str[size_str] = "(-1) (-2)";//uncorrect
    //char str[size_str] = "(-1) * ()";//uncorrect
    //char str[size_str] = "(-1) * (+)";//uncorrect
    if(check_expression(str))
        printf("correct\n");
    else
        printf("uncorrect\n");


    return 0;
}
