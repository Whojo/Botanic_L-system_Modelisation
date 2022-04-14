opencvdep = dependency('opencv4')

core = files (
  'core/l_system.cpp',
  'core/module.cpp',
  'core/rule.cpp',
  'core/state.cpp',
  )

libcore = static_library('core', core, include_directories: includes)

utils = files (
  'utils/drawer2D.cpp',
  'utils/turtle.cpp',
  'utils/material.cpp'
  )

libutils = static_library('utils', utils, dependencies: opencvdep, include_directories: includes)

sources = core + utils
fractals = files ('fractals.cpp')
brackets = files ('brackets.cpp')
stochastic = files ('stochastic.cpp')
context_sensitive = files ('context_sensitive.cpp')
parametric = files ('parametric.cpp')
tree3d = files ('tree3d.cpp')

