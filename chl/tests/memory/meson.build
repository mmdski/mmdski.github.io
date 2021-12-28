vlgnd = find_program('valgrind', required : true)

matrix_mem_test = executable('matrix_mem_test',
    'matrix_mem_test.c',
    include_directories: [inc],
    link_with: [chlib])

test('test_matrix_mem', vlgnd,
    args : [
        '--leak-check=full',
        '--error-exitcode=33',
        matrix_mem_test.full_path()
        ],
    suite: 'memory'
    )
