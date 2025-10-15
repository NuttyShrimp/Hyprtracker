project('hyprtracker', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3'])

sqlitecpp = dependency('sqlitecpp', version: '3.3.2')

library('hyprtracker', 'hyprtracker.cpp', dependencies: [sqlitecpp])
