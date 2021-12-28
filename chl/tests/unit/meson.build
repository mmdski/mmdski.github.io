glib_dep = dependency('glib-2.0', required : true)
test_env = environment()
test_env.set('G_TEST_SRCDIR', meson.current_source_dir())
test_env.set('G_TEST_BUILDDIR', meson.current_build_dir())

# matrix tests
testmatrix = executable('testmatrix', ['matrix.c'],
                        include_directories : [inc],
                        dependencies : [glib_dep],
                        link_with : [chlib])
test('testmatrix',
    testmatrix,
    env: test_env
    )
