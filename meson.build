project('sound', 'c')
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)
sound_dep = dependency('alsa')

executable('sound', 
'main.c', 
'sound.c',
'timing.c',
dependencies: [m_dep, sound_dep])


