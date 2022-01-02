chl_sources = files(['chlmem.c', 'chlmatrix.c'])
chlib_c_args = ['-DCHL_COMPILATION']

if target_machine.cpu() == 'x86_64'
    chlib = static_library('chlib',
        chl_sources,
        include_directories: inc,
        c_args: chlib_c_args)
endif
