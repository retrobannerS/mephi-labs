#include <stdio.h>
#include <stdlib.h>

int* array_copy_with_new(int* old_array, int* old_len, int new_index, int value);
int* array_copy_with_shift(int* old_array, int* old_len, int index, int value);
void print_array(int* array, int len);

int main()
{
    int len = 1;
    int* array = calloc(len, sizeof (int));
    int index, value = -1;
    while(value != 0)
    {
        printf("Write index, space button and number (write number = 0, if you want to exit):");
        scanf("%d %d", &index, &value);
        if (index > (len - 1))
            array = array_copy_with_new(array, &len, index, value);

        else if (array[index] != 0)
            array = array_copy_with_shift(array, &len, index, value);

        else
            array[index] = value;

        print_array(array, len);
    }
    return 0;
}

int* array_copy_with_new(int* old_array, int* old_len, int new_index, int value)
{
    int* new_array = calloc(new_index + 1, sizeof (int));
    new_array[new_index] = value;
    for (int i = 0; i < *old_len; i++)
        new_array[i] = old_array[i];
    (*old_len) = new_index + 1;
    free(old_array);
    return new_array;
}

int* array_copy_with_shift(int* old_array, int* old_len, int index, int value)
{
    (*old_len) += 1;
    int *new_array = calloc(*old_len, sizeof(int));
    for (int i = 0; i < index; i++)
        new_array[i] = old_array[i];
    new_array[index] = value;
    for (int i = index + 1; i < *old_len; ++i)
        new_array[i] = old_array[i - 1];
    free(old_array);
    return new_array;
}

void print_array(int *array, int  len)
{
    printf("Indexes: ");
    for (int i = 0; i < len; i++)
        printf("%3d", i);
    printf("\n");
    printf("Elements:");
    for (int i = 0; i < len; i++)
        printf("%3d", array[i]);
    printf("\n");
}