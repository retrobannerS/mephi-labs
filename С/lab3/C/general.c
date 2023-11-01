#include "general.h"

long double* init_arr(unsigned int *top, unsigned int *mem)                             //функция инициализации массива в цикле
{
    printf("\nWrite size of array (old array will be deleted):");

    unsigned int size = input_int();
    *top = size, *mem = size;                                                           //заполненность массива будет такой же, сколько ввел пользователь, памяти потребуется столько же
    long double *arr = allocating(NULL, top, mem);                                      //выделяем память под новый массив

    printf("\n\n");
    for (unsigned int i = 0; i < size; i++)                                             //заполняем в цикле
    {
        printf("Index %u:\n", i);
        arr[i] = input_elem();
        printf("\n");
    }

    return arr;
}

long double* input_arr(long double *arr, unsigned int *top, unsigned int *mem)          //функция ввода элемента по индексу
{
    printf("\nWrite integer index:");
    unsigned int index = input_int();
    long double value = input_elem();

    if (index >= *top)                                                                  //Вставка в конец массива
    {
        arr = allocating(arr, top, mem);                                                //выделяем память в соответствии с индивидуальным заданием
        arr[*top] = value;                                                              //просто вставляем в конец массива
    }

    else if(index < *top)                                                               //Вставка по индексу со сдвигом
    {
        arr = allocating(arr, top, mem);                                                //выделяем память в соответствии с индивидуальным заданием
        for (unsigned int i = *top; i > index; i--)                                     //сдвигаем некоторые элементы вправо
            arr[i] = arr[i - 1];
        arr[index] = value;                                                             //просто вставляем в освободившуюся ячейку
    }
    (*top)++;                                                                           //заполненность массива прибавилось на 1 элемент

    return arr;
}

long double* del_elem(long double *arr, unsigned int *top, unsigned int *mem)           //функция удаления элемента по индексу
{
    printf("\nWrite integer index:");

    unsigned int index = input_int();

    if (index > *top - 1 or *top == 0)                                                  //если указан пытаемся удалить то, что еще не существует
        printf("\nYou haven`t deleted anything!\n");

    else                                                                               //сдвигаем элементы влево и освобождаем одну ячейку памяти
    {
        for (unsigned int i = index; i < *top - 1; i++)
            arr[i] = arr[i + 1];
        arr = allocating(arr, top, mem);                                                //выделяем память в соответствии с индивидуальным заданием
        (*top)--;                                                                       //заполненность массива уменьшилось
        printf("\nDeleted!\n");
    }

    return arr;
}

void print_arr(long double *arr, unsigned int top)                                      //функция вывода массива
{
  if (top == 0)                                                                         //вывод пустого массива
       printf("Array is empty!");

  printf("\n");
  for (unsigned int i = 0; i < top; i++)                                                //массив непрерывен, поэтому можем выводить просто в цикле, перебирая индексы
      printf("a[%u] = %Lf\n", i, arr[i]);
}

void del_dup(long double **arr, unsigned int *top, unsigned int *mem, long double **arr2, unsigned int *top2, unsigned int *mem2)
{                                                                                       //функция из для индивидуального задания
    unsigned int top_tmp = *top, mem_tmp = *top;                                        //создаем новый массив, куда будем копировать последовательность
    unsigned int j = 0;                                                                 //без подряд стоящих равных элементов
    long double *tmp = allocating(NULL, &top_tmp, &mem_tmp);                            //выделяем памяти прозапасом столько, насколько заполнен основной массив,
                                                                                        //потому что элементы могут не повторяться

    unsigned int new_top = *top, new_mem = *top;                                        //так же создаем второй новый массив, куда будет копироваться последовательность
    unsigned int k = 0;                                                                 //только из подряд стоящих повторяющихся элементов
    long double *new_arr = allocating(NULL, &new_top, &new_mem);

    bool flag = false;                                                                  //флажок нужен, чтобы во второй новый массив копировалось корректное количество элементов

    unsigned int i = 0;                                                                 //i не в цикле, потому что нам нужно будет корректно скопировать последний элемент главного массива

    for(; i < *top - 1; i++)                                                            //последовательно в главном массиве проверяем по парам, равны ли элементы,
        if((*arr)[i] != (*arr)[i+1])                                                    //в зависимости от этого копируем элементы в соотвествующий новый массив
        {
            if(flag)                                                                    //если на предыдущей итерации пара элементов совпала,
            {                                                                           //а на текущей нет, нужно во второй новый массив добавить еще один элемент для корректного их количества
                new_arr[k++] = (*arr)[i];
                flag = false;
            }
            tmp[j++] = (*arr)[i];
        }
        else
        {
            new_arr[k++] = (*arr)[i];
            flag = true;
        }

    if ((*arr)[i - 1] == (*arr)[i])                                                     //проверяем, корректно ли будет вставить во второй новый массив последний элемент главного массива
        new_arr[k++] = (*arr)[i];
    tmp[j++] = (*arr)[i];                                                               //в первый новый массив всегда вставляем последний элемент главного массива

    free(*arr);                                                                  //освобождаем далее не нужный arr

    top_tmp = j, mem_tmp = j;                                                           //присваиваем параметрам первого нового массива его "характеристики"
    tmp = allocating(tmp, &top_tmp, &mem_tmp);                                          //освобождаем ненужную память

    *top = top_tmp, *mem = mem_tmp;                                                     //делаем главный массив равным первому новому, старый главный нам больше не нужен
    *arr = tmp;

    *top2 = k, *mem2 = k;                                                               //присваиваем параметрам второго нового массива его "характеристики"
    new_arr = allocating(new_arr, top2, mem2);                                          //освобождаем ненужную память
    *arr2 = new_arr;                                                                    //делаем второй массив равным второму новому в соответствии с индивидуальным заданием
}