#include "Errors.h"
#include "types/INT.h"
#include "types/REAL.h"
#include "types/COMPLEX.h"
#include "ringinfo.h"
#include "Square_Matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void printerr()
{
    printf("Error 1 - не удалось аллоцировать память\n");
    printf("Error 2 - в функцию передана плохая матрица\n");
    printf("Error 3 - в функцию передана матрица с плохим размером\n");
    printf("Error 4 - кольца аргументов в функции не совпадают\n");
    printf("Error 5 - номер введенной строки больше, чем размер матрицы\n");
    printf("Error 6 - номер введенного столбца больше, чем размер матрицы\n");
    printf("Error 7 - размеры матриц не совпадают\n");
    printf("Error 8 - плохие коэффициенты в линейной комбинации\n");
    printf("Error 9 - плохой аргумент в операции кольца\n");
    printf("Error 10 - у этого кольца нельзя найти обратный элемент относительно умножения\n");
    printf("Error 11 - ошибка ввода или EOF\n");
    printf("Error 12 - деление на ноль\n");
}

void input(int* a, int max)
{
    char check1 = scanf("%d[^\n]", a);
    int check2 = getchar();

    while(check1 != 1 || check2 != '\n' || *a < 1 || *a > max)
    {
        if (check2 == -1)                                             //если произошли ошибка ввода или конец ввода
        {
            err = eof;
            return;
        }

        else
            printf("Введено некорректное целое число. Попробуйте заново:");

        scanf("%*[^\n]%*c");
        check1 = scanf("%d", a);
        check2 = getchar();
    }
}

void menu()
{
    printf("1. Ввести матрицу\n");
    printf("2. Заменить матрицу нулевой\n");
    printf("3. Заменить матрицу единичной\n");
    printf("4. Поменять элемент в матрице\n");
    printf("5. Достать элемент из матрицы\n");
    printf("6. Поменять матрицы местами\n");
    printf("7. Скопировать матрицу А в матрицу B\n");
    printf("8. Скопировать матрицу B в матрицу A\n");
    printf("9. Сложить матрицы\n");
    printf("10. Перемножить матрицы\n");
    printf("11. Скалярно умножить матрицу на число\n");
    printf("12. Вычислить алгебраическое дополнение матрицы\n");
    printf("13. Вычислить определитель матрицы\n");
    printf("14. Транспонировать матрицу\n");
    printf("15. Найти обратную матрицу\n");
    printf("16. Линейная комбинация строк\n");
    printf("17. Линейная комбинация столбцов\n");
    printf("18. Вывести список ошибок\n");
    printf("19. Обнулить ошибки\n");
    printf("20. Запустить тестовую функцию\n");
    printf("21. Завершить программу\n");
}

void choose(int* a)
{
    printf("1. Матрица А\n2. Матрица B\n");
    input(a, 2);
}

void test()
{
    RingInfo* INT = malloc(sizeof (RingInfo));
    RingInfo* REAL = malloc(sizeof(RingInfo));
    RingInfo* COMPLEX = malloc(sizeof (RingInfo));
    NewRing(INT, INTsize, &Intsum, &Intmult,
            &int0, &int1, &Intminus, &Intinverse,
            &Intprint, &Intinput);
    NewRing(REAL, REALsize, &Realsum, &Realmult,
            &real0, &real1, &Realminus, &Realinverse,
            &Realprint, &Realinput);
    NewRing(COMPLEX, COMPLEXsize, &Complexsum, &Complexmult,
            &complex0, &complex1, &Complexminus, &Complexinverse,
            &Complexprint, &Complexinput);
    printf("Сначала с матрицей целых чисел.\n");
    printf("Нулевая матрица произвольного размера:\n");
    sqmatr* A = Newsqmatrix(INT, rand()%10);
    Zerosqmatrix(A);
    Sqmatrixprint(A);
    printf("Преобразуем её в единичную:\n");
    E_matrix(A);
    Sqmatrixprint(A);
    Sqmatrixdelete(A);
    printf("Можем заполнять матрицу:\n");
    A = Newsqmatrix(INT, 3);
    Inputsqmatrix(A);
    Sqmatrixprint(A);
    printf("Можем поменять в ней какой то элемент:\n");
    sqmatr* tmp = Newsqmatrix(INT, 1);
    int row = 0, col = 0;
    printf("Номер строки:");
    input(&row, 3);
    printf("Номер столбца:");
    input(&col, 3);
    printf("Значение:");
    Inputsqmatrix(tmp);
    row--, col--;
    Putvalue(A, row, col, tmp);
    Sqmatrixprint(A);
    Sqmatrixdelete(tmp);
    printf("Можем скопировать матрицу в другую:\n");
    tmp = Newsqmatrix(INT, 3);
    Sqmatrixcopy(A, tmp);
    Sqmatrixprint(tmp);
    Sqmatrixprint(A);
    Sqmatrixdelete(tmp);
    Sqmatrixdelete(A);
    printf("Давайте сложим две матрицы:\n");
    A = Newsqmatrix(INT, 5);
    E_matrix(A);
    sqmatr* B = Newsqmatrix(INT, 5);
    E_matrix(B);
    sqmatr* C = Newsqmatrix(INT, 5);
    Sqmatrixsum(A, B, C);
    printf("A:\n");
    Sqmatrixprint(A);
    printf("B:\n");
    Sqmatrixprint(B);
    printf("result:\n");
    Sqmatrixprint(C);
    Sqmatrixdelete(A);
    Sqmatrixdelete(B);
    Sqmatrixdelete(C);
    printf("Перемножим две введенные матрицы:\n");
    A = Newsqmatrix(INT, 2);
    B = Newsqmatrix(INT, 2);
    C = Newsqmatrix(INT, 2);
    Inputsqmatrix(A);
    Inputsqmatrix(B);
    Sqmatrixmult(A, B, C);
    printf("A:\n");
    Sqmatrixprint(A);
    printf("B:\n");
    Sqmatrixprint(B);
    printf("result:\n");
    Sqmatrixprint(C);
    Sqmatrixdelete(A);
    Sqmatrixdelete(B);
    Sqmatrixdelete(C);
    printf("Перемножим единичную матрицу на скаляр:\n");
    printf("Введите скаляр:\n");
    tmp = Newsqmatrix(INT, 1);
    Inputsqmatrix(tmp);
    A = Newsqmatrix(INT, 4);
    E_matrix(A);
    Sqmatrixscalarmult(tmp, A, A);
    Sqmatrixprint(A);
    Sqmatrixdelete(A);
    Sqmatrixdelete(tmp);
    printf("Введём матрицу 3 на 3:\n");
    A = Newsqmatrix(INT, 3);
    Inputsqmatrix(A);
    Sqmatrixprint(A);
    printf("Посчитаем алгебраическое дополнение:\n");
    printf("Номер строки:");
    input(&row, 3);
    printf("Номер столбца:");
    input(&col, 3);
    row--, col--;
    tmp = Newsqmatrix(INT, 1);
    Sqmatrixalgcompl(A, row, col, tmp);
    printf("Результат:\n");
    Sqmatrixprint(tmp);
    printf("Посчитаем определитель:\n");
    Sqmatrixdet(A, tmp);
    Sqmatrixprint(tmp);
    Sqmatrixdelete(tmp);
    printf("Транспонируем матрицу:\n");
    printf("Было:\n");
    Sqmatrixprint(A);
    Sqmatrixtranspose(A, A);
    printf("Стало:\n");
    Sqmatrixprint(A);
    printf("Найдем для нее обратную(для INT нельзя так сделать, должна вылезти ошибка):\n");
    B = Newsqmatrix(INT, 3);
    Sqmatrixinverse(A, B);
    Sqmatrixprint(B);
    Sqmatrixdelete(B);
    printf("Выведем номер ошибки\n");
    printf("Error ");
    printf("%d\n", err);
    printf("Это ошибка отсутствия обратного элемента по умножению для целых чисел\n");
    printf("Прибавим ко 2 строке линейную комбинацию остальных строк\n");
    Sqmatrixprint(A);
    void *coefs = malloc(INT->size * A->sizeofmatr);
    for (int i = 0; i < A->sizeofmatr; ++i)
    {
        printf("Коэффициент %d:", i + 1);
        INT->input(coefs + i * INT->size);
    }
    Sqmatrixlincombofrows(A, 1, coefs);
    Sqmatrixprint(A);
    Sqmatrixdelete(A);
    free(coefs);
    printf("Теперь перейдем к комплексным матрицам\n");
    A = Newsqmatrix(COMPLEX, 3);
    B = Newsqmatrix(COMPLEX, 3);
    Inputsqmatrix(A);
    Inputsqmatrix(B);
    Sqmatrixprint(A);
    Sqmatrixprint(B);
    printf("Найдем оба определителя\n");
    tmp = Newsqmatrix(COMPLEX, 1);
    Sqmatrixdet(A, tmp);
    Sqmatrixprint(tmp);
    Sqmatrixdet(B, tmp);
    Sqmatrixprint(tmp);
    Sqmatrixdelete(tmp);
    printf("Сложим обе матрицы\n");
    C = Newsqmatrix(COMPLEX, 3);
    Sqmatrixprint(A);
    Sqmatrixprint(B);
    Sqmatrixsum(A, B, C);
    printf("Результат:\n");
    Sqmatrixprint(C);
    printf("Перемножим матрицы\n");
    Sqmatrixmult(A, B, C);
    Sqmatrixprint(C);
    printf("Найдем обратную для первой матрицы\n");
    Sqmatrixinverse(A, C);
    Sqmatrixprint(A);
    Sqmatrixprint(C);
    printf("Перемножим их\n");
    Sqmatrixmult(A, C, C);
    Sqmatrixprint(C);
    printf("Попробуем найти обратную матрицу для нулевой\n");
    Zerosqmatrix(C);
    Sqmatrixprint(C);
    Sqmatrixinverse(C, C);
    Sqmatrixprint(C);
    printf("Определитель равен нулю, смотрим лог ошибок\n");
    printf("Error ");
    printf("%d\n", err);
    Sqmatrixdelete(A);
    Sqmatrixdelete(B);
    Sqmatrixdelete(C);
    free(INT);
    free(REAL);
    free(COMPLEX);
}

int main ()
{
    printf("1. Использовать целые числа\n");
    printf("2. Использовать вещественные числа\n");
    printf("3. Использовать комплексные числа\n");
    int a = 0;
    input(&a, 3);
    RingInfo* RING = malloc(sizeof(RingInfo));
    switch(a)
    {
        case 1:
            NewRing(RING, INTsize, &Intsum, &Intmult,
                    &int0, &int1, &Intminus, &Intinverse,
                    &Intprint, &Intinput);
            break;
        case 2:
            NewRing(RING, REALsize, &Realsum, &Realmult,
                    &real0, &real1, &Realminus, &Realinverse,
                    &Realprint, &Realinput);
            break;
        case 3:
            NewRing(RING, COMPLEXsize, &Complexsum, &Complexmult,
                    &complex0, &complex1, &Complexminus, &Complexinverse,
                    &Complexprint, &Complexinput);
            break;
    }

    sqmatr* A = NULL;
    sqmatr* B = NULL;

    while(1)
    {
        a = 0;
        int b = 0;
        menu();
        input(&a, 21);
        switch(a)
        {
            case 1:
            {
                int size = 0;
                choose(&b);
                printf("Введите размер матрицы:");
                input(&size, 4000000);
                if(b == 1)
                {
                    if(A)
                        Sqmatrixdelete(A);
                    A = Newsqmatrix(RING, size);
                    Inputsqmatrix(A);
                }
                else
                {
                    if(B)
                        Sqmatrixdelete(B);
                    B = Newsqmatrix(RING, size);
                    Inputsqmatrix(B);
                }
                break;
            }
            case 2:
            {
                choose(&b);
                if(b == 1)
                    Zerosqmatrix(A);
                else
                    Zerosqmatrix(B);
                break;
            }
            case 3:
            {
                choose(&b);
                if (b == 1)
                    E_matrix(A);
                else
                    E_matrix(B);
                break;
            }
            case 4:
            {
                int row = 0, col = 0;
                sqmatr* tmp = Newsqmatrix(RING, 1);
                choose(&b);
                printf("Введите номер строки:");
                input(&row, 4000000);
                printf("Введите номер столбца:");
                input(&col, 4000000);
                row--, col--;
                printf("Введите новое значение:");
                Inputsqmatrix(tmp);
                if(b == 1)
                    Putvalue(A, row, col, tmp);
                else
                    Putvalue(B, row, col, tmp);
                Sqmatrixdelete(tmp);
                break;
            }
            case 5:
            {
                int row, col;
                void* data;
                choose(&b);
                printf("Введите номер строки:");
                input(&row, 4000000);
                printf("Введите номер столбца:");
                input(&col, 4000000);
                row--, col--;
                if(b == 1)
                    data = Getvalue(A, row, col);
                else
                    data = Getvalue(B, row, col);
                RING->print(data);
                printf("\n");
                break;
            }
            case 6:
            {
                sqmatr* swap = A;
                A = B;
                B = swap;
                break;
            }
            case 7:
            {
                Sqmatrixcopy(A, B);
                break;
            }
            case 8:
            {
                Sqmatrixcopy(B, A);
                break;
            }
            case 9:
            {
                sqmatr* C = Newsqmatrix(RING, A->sizeofmatr);
                Sqmatrixsum(A, B, C);
                printf("Результат:\n");
                Sqmatrixprint(C);
                Sqmatrixdelete(C);
                break;
            }
            case 10:
            {
                sqmatr* C = Newsqmatrix(RING, A->sizeofmatr);
                Sqmatrixmult(A, B, C);
                printf("Результат:\n");
                Sqmatrixprint(C);
                Sqmatrixdelete(C);
                break;
            }
            case 11:
            {
                choose(&b);
                printf("Введите скаляр:");
                sqmatr* scalar = Newsqmatrix(RING, 1);
                Inputsqmatrix(scalar);
                printf("Результат:\n");
                if (b == 1)
                {
                    sqmatr* C = Newsqmatrix(RING, A->sizeofmatr);
                    Sqmatrixscalarmult(scalar, A, C);
                    Sqmatrixprint(C);
                    Sqmatrixdelete(C);
                }
                else
                {
                    sqmatr* C = Newsqmatrix(RING, B->sizeofmatr);
                    Sqmatrixscalarmult(scalar, B, C);
                    Sqmatrixprint(C);
                    Sqmatrixdelete(C);
                }
                Sqmatrixdelete(scalar);
                break;
            }
            case 12:
            {
                int row = 0, col = 0;
                sqmatr* tmp = Newsqmatrix(RING, 1);
                choose(&b);
                printf("Введите номер строки:");
                input(&row, 4000000);
                printf("Введите номер столбца:");
                input(&col, 4000000);
                row--, col--;
                if(b == 1)
                    Sqmatrixalgcompl(A, row, col, tmp);
                else
                    Sqmatrixalgcompl(B, row, col, tmp);
                printf("Результат:\n");
                Sqmatrixprint(tmp);
                Sqmatrixdelete(tmp);
                break;
            }
            case 13:
            {
                choose(&b);
                sqmatr* tmp = Newsqmatrix(RING, 1);
                if(b == 1)
                    Sqmatrixdet(A, tmp);
                else
                    Sqmatrixdet(B, tmp);
                printf("Результат:\n");
                Sqmatrixprint(tmp);
                Sqmatrixdelete(tmp);
                break;
            }
            case 14:
            {
                choose(&b);
                if(b == 1)
                    Sqmatrixtranspose(A, A);
                else
                    Sqmatrixtranspose(B, B);
                break;
            }
            case 15:
            {
                choose(&b);
                if(b == 1)
                {
                    sqmatr *tmp = Newsqmatrix(RING, A->sizeofmatr);
                    Sqmatrixinverse(A, tmp);
                    printf("Результат:\n");
                    Sqmatrixprint(tmp);
                    Sqmatrixdelete(tmp);
                }
                else
                {
                    sqmatr *tmp = Newsqmatrix(RING, B->sizeofmatr);
                    Sqmatrixinverse(B, tmp);
                    printf("Результат:\n");
                    Sqmatrixprint(tmp);
                    Sqmatrixdelete(tmp);
                }
                break;
            }
            case 16:
            {
                choose(&b);
                int row;
                printf("Номер строки, к которой нужно прибавить комбинацию:");
                if (b == 1)
                {
                    input(&row, (int)A->sizeofmatr);
                    row--;
                    void *coefs = malloc(RING->size * A->sizeofmatr);
                    for (int i = 0; i < A->sizeofmatr; ++i)
                    {
                        printf("Коэффициент %d:", i);
                        RING->input(coefs + i * RING->size);
                    }
                    Sqmatrixlincombofrows(A, row,coefs);
                }
                else
                {
                    input(&row, (int)B->sizeofmatr);
                    row--;
                    void *coefs = malloc(RING->size * B->sizeofmatr);
                    for (int i = 0; i < B->sizeofmatr; ++i)
                    {
                        printf("Коэффициент %d:", i);
                        RING->input(coefs + i * RING->size);
                    }
                    Sqmatrixlincombofrows(B, row,coefs);
                }
                break;
            }
            case 17:
            {
                choose(&b);
                int col;
                printf("Номер строки, к которой нужно прибавить комбинацию:");
                if (b == 1)
                {
                    input(&col, (int) A->sizeofmatr);
                    col--;
                    void *coefs = malloc(RING->size * A->sizeofmatr);
                    for (int i = 0; i < A->sizeofmatr; ++i)
                    {
                        printf("Коэффициент %d:", i);
                        RING->input(coefs + i * RING->size);
                    }
                    Sqmatrixlincombofcols(A, col, coefs);
                }
                else
                {
                    input(&col, (int) B->sizeofmatr);
                    col--;
                    void *coefs = malloc(RING->size * B->sizeofmatr);
                    for (int i = 0; i < B->sizeofmatr; ++i)
                    {
                        printf("Коэффициент %d:", i);
                        RING->input(coefs + i * RING->size);
                    }
                    Sqmatrixlincombofrows(B, col, coefs);
                }
                break;
            }
            case 18:
            {
                printerr();
                break;
            }
            case 19:
                err = ok;
                break;
            case 20:
                test();
                pause();
                return err;
            case 21:
                goto A;

        }
        if(A)
        {
            printf("Матрица А:\n");
            Sqmatrixprint(A);
        }
        else
            printf("Матрица А еще не определена\n");

        if(B)
        {
            printf("Матрица B\n");
            Sqmatrixprint(B);
        }
        else
            printf("Матрица B еще не определена\n");
        if(err)
            printf("Error %d\n", err);

    }
    A:
    Sqmatrixdelete(A);
    Sqmatrixdelete(B);
    return err;
}
