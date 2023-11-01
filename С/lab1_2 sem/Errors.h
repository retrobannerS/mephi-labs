#ifndef LAB1_ERRORS_H
#define LAB1_ERRORS_H

enum Error{
    ok,
    failed_to_allocate_memory,
    bad_matrix_in_function,
    bad_size_of_matrix_in_function,
    rings_are_not_equal_in_function,
    row_adress_is_larger_than_size_of_matrix,
    col_adress_is_larger_than_size_of_matrix,
    sizes_of_matrix_are_not_equal_in_function,
    bad_coefs_in_function,
    bad_arguments_in_operation,
    can_not_inverse,
    eof,
    division_by_zero
};
extern enum Error err;

#endif //LAB1_ERRORS_H
