chl_sources = ['chlmem.c', 'chlmatrix.c']
chlib_c_args = ['-DCHL_COMPILATION']

# emscripten build
if target_machine.cpu() == 'wasm32'
    chlsin_name = 'chlsin'
    chlsin_sources = ['chlsin.c']

    executable(chlsin_name, chlsin_sources, name_suffix: 'js',
        install : true, install_dir : js_install_dir)
endif

if target_machine.cpu() == 'x86_64'
    chlib = static_library('chlib',
        chl_sources,
        include_directories: inc,
        c_args: chlib_c_args)
endif
