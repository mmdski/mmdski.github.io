# emscripten build
if target_machine.cpu() == 'wasm32'
    chlsin_name = 'chlsin'
    chlsin_sources = ['chlsin.c']

    executable(chlsin_name, chlsin_sources, name_suffix: 'js',
        install : true, install_dir : js_install_dir)
endif
