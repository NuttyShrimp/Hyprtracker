project('hyprtracker', 'cpp',
  version : '0.1',
  default_options: ['buildtype=release'])
add_global_arguments('-std=c++23', language: 'cpp')

sqlitecpp = dependency('sqlitecpp', version: '3.3.2')

globber = run_command('find', './src', '-name', '*.cpp', check: true)
src = globber.stdout().strip().split('\n')

shared_module(meson.project_name(), src,
  dependencies: [
    dependency('hyprland'),
    dependency('pixman-1'),
    dependency('libdrm'),
    dependency('pangocairo'),
    dependency('libinput'),
    dependency('libudev'),
    dependency('wayland-server'),
    dependency('xkbcommon'),
    sqlitecpp,
  ],
)
