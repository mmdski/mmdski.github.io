# emscripten build
if meson.get_compiler('c').get_id() == 'emscripten'
    chlsin_name = 'chlsin'
    chlsin_sources = ['chlsin.c']

    executable(chlsin_name, chlsin_sources, name_suffix: 'js',
        install : true, install_dir : js_install_dir)
endif
