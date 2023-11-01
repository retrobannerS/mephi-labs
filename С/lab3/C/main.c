#include "general.h"

void menu(bool);

int main()
{
    char *str = (char*) calloc(7, sizeof(char));  //создаём строку, куда будут вводиться команды
    unsigned int top = 0, top2 = 0;                                       //длина массивов в любой момент времени. Сначала массивы пустые и значение 0.
    unsigned int mem = 0, mem2 = 0;                                       //количество ячеек памяти, выделенных для массива в любой момент времени
    long double *arr = NULL, *arr2 = NULL;                                //указатели на главный и второй массив

    unsigned int mem_main = mem;                                          //количество ячеек памяти,
    unsigned int top_main = top;                                          //указатель и длина массива,
    long double *arr_main = arr;                                          //который выбрал пользователь (функция choose). Всегда начинаем с главного массива.

    bool flag = false;                                                    //флажок выбранного массива, для первого и второго немного разные правила использования

    menu(flag);                                                           //начинаем диалог с пользователем

    while(1) {
        printf("$");
        scanf("%6[^\n]", str);                             //ввод команды, она заведомо не может быть более 6 символов.
        if (str_check(str, flag) == true)                   //если заранее прошла проверка на неверность команды -
            continue;                                            // - следующая итерация(еще раз просим команду)
        if (strcmp(str, "exit") == 0)                            //штатный способ завершения программы
        {
            printf("\nBye!");
            break;
        }
        //дальше идет сравнение введенной пользователем команды с одной из предусмотренных команд, если совпало - выполняем для выбранного массива(строка 12)
        else if (strcmp(str, "init") == 0)
        {
            free(arr_main);
            arr_main = init_arr(&top_main, &mem_main);
        }
        else if (strcmp(str, "input") == 0)
            arr_main = input_arr(arr_main, &top_main, &mem_main);
        else if (strcmp(str, "delete") == 0)
            arr_main = del_elem(arr_main, &top_main, &mem_main);
        else if (strcmp(str, "print") == 0)
            print_arr(arr_main, top_main);
        else if (strcmp(str, "dup") == 0)
            if (flag)                                                               //мы не можем создавать 2ой массив из 2го, 2 массив создается только из главного
                printf("\nYou can`t use \"dup\" with array N2!\n");
            else if(top_main == 0 or top_main == 1)                                 //главный массив может быть слишком короткий для такой команды
                printf("Array is empty or it has too few elements.\n");
            else
            {
                if (!flag)
                    free(arr2);
                del_dup(&arr_main, &top_main, &mem_main, &arr2, &top2, &mem2);
            }
        else if (strcmp(str, "choose") == 0)
            flag = choosing_arr(&arr_main, &top_main, &mem_main, &arr, &top, &mem, &arr2, &top2, &mem2);
        else if(strcmp(str, "help") == 0)
            menu(flag);
        else                                                                        //если ничего не подошло - значит неверная команда
            printf("\nYou`ve wrote wrong command. Try again:");
        if (!flag)
        {
            arr = arr_main;                                                         //после каждой итерации запоминаем параметры выбранного массива
            top = top_main;
            mem = mem_main;
            printf("\nYou are using array N1");                               //поддерживаемые команды для выбранного массива и строка, показывающая текущий массив
            printf("\nMENU: init   input   delete   print   dup   choose   help   exit\n");
        }
        else                                                                        //аналогично для второго массива
        {
            arr2 = arr_main;
            top2 = top_main;
            mem2 = mem_main;
            printf("\nYou are using array N2");
            printf("\nMENU: init   input   delete   print   choose   help   exit\n");
        }
    }
    free(arr);                                                                //прибираемся за собой
    free(arr2);
    free(str);

    return 0;
}

void menu(bool flag)                                                                  //меню с поддерживаемыми для выбранного массива командами
{
    printf("\nWrite   \"init\"    if you want to initialize array.\n");
    printf("Write   \"input\"   if you want to input element into array by index.\n");
    printf("Write   \"delete\"  if you want to delete the element from array by index.\n");
    printf("Write   \"print\"   if you want to see your array.\n");
    if(!flag)
        printf("Write   \"dup\"     if you want to process equal elements, which are nearby in array.\n");
    printf("Write   \"choose\"  if you want to choose array.\n");
    printf("Write   \"help\"    if you want to read this message again.\n");
    printf("Write   \"exit\"    if you want to exit the program.\n\n");
}