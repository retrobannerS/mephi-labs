#include "checking.h"

bool str_check(char* str, bool arr)                             //функция проверки ввода команды
{
    char check;                                                      //нужная переменная для проверки здорового ввода
    bool flag = false;                                               //флажок, который мы возвратим

    check = getchar();                                               //берем первый символ из stdin

    if (check == -1)                                                 //если произошли ошибка ввода или конец ввода
    {
        fprintf(stderr, "\nError or EOF...\nExit the program");
        free(str);
        exit(1);
    }

    else if(check != '\n' or strlen(str) < 3)                    //если заведомо больше 6 символов или меньше 3 - команда автоматически некорректная
    {
        printf("\nYou`ve wrote wrong command. Try again:");
        if (!arr)                                                    //выводим меню в соответствии с текущим выбором массива
        {
            printf("\nYou are using array N1");
            printf("\nMENU: init   input   delete   print   dup   choose   help   exit\n");
        }
        else
        {
            printf("\nYou are using array N2");
            printf("\nMENU: init   input   delete   print   choose   help   exit\n");
        }

        scanf("%*[^\n]%*c");
        flag = true;                                                  //команда введена некорректно - поднимаем флажок
    }

    return flag;
}

bool choosing_arr(long double **arr_main, unsigned int *top_main, unsigned int *mem_main, long double **arr, unsigned int *top, unsigned int *mem, long double **arr2, unsigned int *top2, unsigned int *mem2)
{
    bool flag = false;                                                                          //флажок выбора массива

    if (*arr2 != NULL)                                                                          //обязательно проверяем, существует ли второй массив
    {
        unsigned int x = 0;                                                                     //стандартные проверки на здоровый ввод числа

        printf("\nChoose array(1 or 2):");
        char check1 = scanf("%1u", &x), check2 = getchar();

        while(check1 != 1 or check2 != '\n' or (x != 1 and x != 2))
        {
            if (check2 == -1)
            {
                fprintf(stderr, "\nError or EOF...\nExit the program");
                exit(1);
            }
            else
                printf("You haven`t wrote 1 or 2. Try again:");

            scanf("%*[^\n]%*c");
            check1 = scanf("%1u", &x);
            check2 = getchar();
        }

        if(x == 2 and *arr_main == *arr and *top_main == *top and *mem_main == *mem)        //если после пользователь выбрал ДРУГОЙ массив, то
        {                                                                                   //запоминаем параметры старого и по аналогии
            *arr = *arr_main;                                                               //со строкой 12(main.c) меняем выбранный массив
            *top = *top_main;
            *mem = *mem_main;
            *arr_main = *arr2;
            *top_main = *top2;
            *mem_main = *mem2;
            flag = true;                                                                    //выбран массив 2 - поднимаем флажок
            printf("You can`t use \"dup\" with array N2!\n");                         //предупреждаем, что мы не можем использовать некоторые команды со вторым массивом
        }
        else if(x == 1 and *arr_main == *arr2 and *top_main == *top2 and *mem_main == *mem2)
        {
            *arr2 = *arr_main;
            *top2 = *top_main;
            *mem2 = *mem_main;
            *arr_main = *arr;
            *top_main = *top;
            *mem_main = *mem;
        }
    }
    else
        printf("Array 2 don`t exist yet. Initialize it by \"dup\".\n");

    return flag;
}

unsigned int input_int()                                             //стандартна функция проверки ввода целого беззнакового числа(в данном случае индекса)
{
    long long int index;                                             //создаём long long int, чтобы упростить жизнь, когда пользователь вводит отрицательные числа

    char check1 = scanf("%ld", &index), check2 = getchar();

    while(check1 != 1 or check2 != '\n' or index < 0)
    {
        if (check2 == -1)                                             //если произошли ошибка ввода или конец ввода
        {
            fprintf(stderr, "\nError or EOF...\nExit the program");
            exit(1);
        }

        else
            printf("You`ve written incorrect integer. Try again:");

        scanf("%*[^\n]%*c");
        check1 = scanf("%ld", &index);
        check2 = getchar();
    }

    return (unsigned int) index;                                     //явно приводим к беззнаковому
}

long double input_elem()                                             //стандартная функция проверки числа с плавающей запятой
{
    long double x;

    printf("Write value(float number) of element:");

    char check1 = scanf("%Lf", &x), check2 = getchar();

    while(check1 != 1 or check2 != '\n')
    {
        if (check2 == -1)                                              //если произошли ошибка ввода или конец ввода
        {
            fprintf(stderr, "\nError or EOF...\nExit the program");
            exit(1);
        }

        else
            printf("You`ve written incorrect value. \nTry again:");

        scanf("%*[^\n]%*c");
        check1 = scanf("%Lf", &x);
        check2 = getchar();
    }

    return x;
}

long double *allocating(long double *arr, const unsigned int *top, unsigned int *mem) //функция здорового выделения памяти
{
    unsigned int x = *(mem) - *(top);                                //разность текущих выделения памяти и заполненности массива
    long double *tmp = arr;

    if (x == 0)                                                      //выделение N памяти, если не хватает
    {
        tmp = (long double*)realloc(arr, (*mem + N) * sizeof(long double));
        *mem += N;
    }

    else if (x == N + 1)                                             //освобождение ячейки памяти, если много свободного места
        tmp = (long double*)realloc(arr, --(*mem) * sizeof(long double));

    if (NULL == tmp)                                                 //проверка выделения памяти
    {
        fprintf(stderr ,"\nFailed to allocate memory!\n");
        free(arr);
        exit(1);
    }

    return tmp;
}