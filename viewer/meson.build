project('viewer', 'cpp',
  version : '0.1',
  default_options: ['buildtype=release'])
add_global_arguments('-std=c++23', language: 'cpp')

globber = run_command('find', './src', '-name', '*.cpp', check: true)
src = globber.stdout().strip().split('\n')

# gtkmm_dep = dependency('gtkmm-4.0', version: '>= 4.6.0')
glib = dependency('gobject-2.0')
gtk4 = dependency('gtk4')
libadwaita = dependency('libadwaita-1', version: '>= 1.5')
sqlitecpp = dependency('sqlitecpp', version: '3.3.2')
# peel = dependency('peel')
peel = subproject('peel').get_variable('peel_dep')

peel_gen = find_program('peel-gen')
peel_gtk = custom_target('peel-codegen',
  command: [
    peel_gen,
    '--recursive',
    '--out-dir', '@OUTDIR@',
    'Gtk', '4.0',
    'Adw', '1'
  ],
  output: 'peel',
)

executable(meson.project_name(), src, peel_gtk,
  dependencies: [sqlitecpp, glib, libadwaita, gtk4, peel],
)
