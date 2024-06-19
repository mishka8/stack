# ОТЧЁТ
## Постановка задачи - Разбор алгебраического выражения с помощью стека
> [!NOTE]
> Множества
> 1. символов 'a'  - 'z', '0' - '9';
> 2. операций '+','-','*','/'  '(',')';

### РЕШЕНИЕ И АЛГОРИТМ
Так как наша задача проверить правильное ли выражение или нет, 
мы не учитываем приоритет операций.
Первым делом мы проверяем скобки правильно ли они раставлены или нет.
После мы опускаем скобки 
выражение без скобок мы проверяем с помощью "троек"


## СТЕК
> [!NOTE]
> Стек (от англ. stack — стопка) — структура данных, представляющая собой упорядоченный набор элементов, в которой добавление новых элементов и удаление существующих производится с одного конца, называемого вершиной стека.
```C
struct nodelist
{
    char inf;//данные 
    struct nodelist *next;//указатель на следующий элемент 
};
```

```C
struct Steklist
{
    struct nodelist *top;//верхушка
    int size;// количество элементов 
};
```
```C
typedef struct nodelist node;
typedef struct Steklist stek;
```
данные две строчки позволяют нам сделать новый тип данных в программе чтобы удобнее было писать код

### ФУНКЦИИ ДЛЯ РАБОТЫ СО СТЕКОМ

> [!NOTE]
> 1. push или положить в вершину
> 2. pop или вытащить из верщины
> 3. show top или показать вершину стека
> 4. print stek вывод стека
> 5. is empty проверка на пустоту
> 6. del stek удаление стека полностью

1. push или положить в вершину
```C
bool push(stek *st, char val)//входные данные стек и данные которые надо положить в стек
{
    if(st)//проверка что данные коректны
    {
        node *new_el = (node*) malloc(sizeof(node));// создаём элемент 
        if(new_el)// проверка что элемент создан
        {
            new_el -> inf = val;
            new_el -> next = NULL;
            if(st -> top == NULL) // если стек пуст 
            {
                st -> top = new_el; // новый элемент теперь вершина 
            }
            else
            {
                new_el -> next = st -> top; // проводим связи
                st -> top = new_el; // и объявляем неовый элемент вершиной стека
            }
            st -> size++; // увеличиваем количество значчений
            return true; // возвращаем true если функция отработала правильно 
        }
    }
    return false; //иначе возвращаем false
}
```
2. pop или вытащить из верщины
```C
char pop(stek *st)//входные данные стек 
{
    if(st)//проверка данных
    {
        if(st -> top)// проверка пуст ли стек или нет  
        {
            char elem = st -> top -> inf;// запоминаем элемент 
            node *ptrIx = st -> top;// делаем указатель на вершину стека 
            st -> top = st -> top -> next;// сдвигаем вершину стека 
            st -> size--;// уменьшаем размер 
            free(ptrIx);// удалем элемент 
            return elem;// возвращем элемент котрый запомнили 
        }
    }
    return 0;// иначе возвращаем ноль
}
```
3. show top или показать вершину стека
```C
bool ShowTop(stek *st, char *val)// входные данные стек и адрес куда положить данные из верха стека
{
    bool ans = false;// 
    if(st && val)// проверка данных 
    {
        if(st -> top)// если есть вершина стека
        {
            *val = st -> top -> inf;// кладём значение по адресу
            ans = true;// меняем ans на true
        }
    }
    return ans;// возвращаем ans
}
```
4. print stek вывод стека
```C
void print_stack(stek st)//входные данные стек
{
    if(st.top == NULL)// проверка если стека нет то стек пустой
        printf("Stack is empty!\n");
    node *current = st.top;// указатель для навигации по элементам 
    while(current)// 
    {
        printf("%c\n", current -> inf);  //вывод 
        current = current -> next;// указываем на следующий элемент 
    }
}
```
5. is empty проверка на пустоту
```C
bool isEmpty(stek st)//входные данные стек
{
    if(st.top == NULL)// если стек пустой 
        return true;// возвращаем true
    return false;// иначе возвращаем false
}
```

6. del stek удаление стека полностью
```C
void delStek(stek *st)//входные данные стек
{
    if(st)// проверка данных
    {
        if(st -> top)// проверка что есть вершина стека
        {
            node *ptr = st -> top;// указатель на вершину
            node *ptrIx = NULL;// указатель для удаления данных
            while(ptr)// 
            {
                ptrIx = ptr;// 
                ptr = ptr -> next;// уставнавливаем указатель на следующий элемент
                st -> size--;// уменьшаем размер
                free(ptrIx);// очищаем элемент
            }
            st -> top = NULL;//вершина теперь NULL
        }
    }
}
```
## ГЛАВНАЯ ФУНКЦИЯ ПРОВЕРКИ ВЫРАЖЕНИЯ

>[!IMPORTANT]
> 1. Проверка скобок так, как нам не важене приоритет операций, то нам достаточно проверять количество скобок 
> 2. Полностью помещаем выражение в стек
> 3. проверка тройками и замена тройки на один символ
```C
push(&st, 'v');
```

функйция проверки "тройки"
```C
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
```



Сама функция: 
```C
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
```
## ТЕСТИРОВКА ПРОГРАММЫ 
конечно же нам надо придумать тестировки для данной программы. Я придумал следующие тестировки 
```C
    char str[size_str] = "";//uncorrect
    char str[size_str] = "(()";//uncorrect
    char str[size_str] = " + h";// correct
    char str[size_str] = "  (+2 - ((-1) / h ) + (a /  (-1)))";//correct
    char str[size_str] = "((c - d) * h + 1) * (a + b)";//correct
    char str[size_str] = "-d";//correct
    char str[size_str] = "+h";//correct
    char str[size_str] = "(-2)";//ccorrect
    char str[size_str] = "(+2)";//correct
    char str[size_str] = "((c + d) * h + 1) * (a + b))))))))))))";//uncorrect
    char str[size_str] = "(a+(b**h) - 8)";//uncorrect
    char str[size_str] = "(-1) * (-2)";//correct
    char str[size_str] = "(-1) * ()";//uuncorrect
    char str[size_str] = "(-1) (-2)";//uncorrect
    char str[size_str] = "(-1) * ()";//uncorrect
    char str[size_str] = "(-1) * (+)";//uncorrect
```
Смотря на функцию проверки выражения, мы понимаем, что надо  проверить когда спрока пустая, когда строка состоит только из скобок, только из цифр, только буквы, где слишком много или слишком мало скобок, так же где символы стоят не на своих позициях,
где повторяющиеся символы, так же унарный плюс или унарный минус (Унарным называется оператор, который применяется к одному операнду), так же где совсем не мат операций.











