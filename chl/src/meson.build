chl_sources = ['chlsin.c']

chl_name = 'chl'

install_dir = meson.source_root() / 'js'

executable(chl_name, chl_sources, name_suffix: 'js',
    c_args : ['-s', 'EXPORTED_FUNCTIONS=["_chl_sin"]'],
    install : true, install_dir : install_dir)
