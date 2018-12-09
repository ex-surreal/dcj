def Settings( **kwargs ):
    return {
        'flags': [ '-x', 'c++', '-Wall', '-Wextra', '-Werror', '-I', './includes', '-I', './playground/input', '-DDEBUG' ],
    }
