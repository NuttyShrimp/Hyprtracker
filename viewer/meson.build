project('viewer', 'cpp',
  version : '0.1',
  default_options: ['buildtype=release'])
add_global_arguments('-std=c++23', language: 'cpp')

globber = run_command('find', './src', '-name', '*.cpp', check: true)
src = globber.stdout().strip().split('\n')

gtkmm_dep = dependency('gtkmm-4.0', version: '>= 4.6.0')
sqlitecpp = dependency('sqlitecpp', version: '3.3.2')
adwaita = dependency('libadwaita-1')

executable(meson.project_name(), src,
  dependencies: [gtkmm_dep, sqlitecpp, adwaita],
#  win_subsystem: 'windows',
)
