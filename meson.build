project('l-systems', 'cpp', default_options : ['cpp_std=c++20'])

sources = []
includes = [include_directories('includes')]

arguments = meson.get_compiler('cpp').get_supported_arguments('-w')
add_project_arguments(arguments,  language : 'cpp')

subdir('src')
executable('fractals', dependencies: opencvdep, link_with: [libcore, libutils],sources: sources + fractals, include_directories: includes)
executable('brackets', dependencies: opencvdep, link_with: [libcore, libutils],sources: sources + brackets, include_directories: includes)
executable('stochastic', dependencies: opencvdep, link_with: [libcore, libutils],sources: sources + stochastic, include_directories: includes)
executable('context_sensitive', dependencies: opencvdep, link_with: [libcore, libutils],sources: sources + context_sensitive, include_directories: includes)
executable('parametric', dependencies: opencvdep, link_with: [libcore, libutils],sources: sources + parametric, include_directories: includes)
executable('tree3d', dependencies: opencvdep, link_with: [libcore, libutils],sources: sources + tree3d, include_directories: includes)

# if get_option('buildtype') == 'debugoptimized'
#   add_project_arguments('-O3',  language : 'cpp')
# endif
