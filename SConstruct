#==============================================================================
env_0 = { 'EXE': 'notepad', 'PKGS': 'gtk+-3.0 gmodule-no-export-2.0 gdk-3.0', 'INCLUDES': 'stdint.h stdlib.h string.h errno.h gtk/gtk.h gdk/gdk.h', 'DEFINES': [ ( 'FALSE', 'false' ), ( 'TRUE', 'true' ) ] }
#==============================================================================
if len( COMMAND_LINE_TARGETS ) == 0 or 'build' in COMMAND_LINE_TARGETS:
	env = Environment( variant_dir='.build', EXE=env_0[ 'EXE' ], PKGS=env_0[ 'PKGS' ], INCLUDES=env_0[ 'INCLUDES' ], obfuscation=False, CPPDEFINES=env_0[ 'DEFINES' ], CC='~/bin/clang', CCFLAGS='-march=native' )
	env.SConscript( 'SConscript', exports='env', variant_dir=env[ 'variant_dir' ], duplicate=0 )
if len( COMMAND_LINE_TARGETS ) == 0 or '.build_dist/0.tar.xz' in COMMAND_LINE_TARGETS:
	env = Environment( variant_dir='.build_dist', EXE=env_0[ 'EXE' ], PKGS=env_0[ 'PKGS' ], INCLUDES=env_0[ 'INCLUDES' ], obfuscation=True, CPPDEFINES=env_0[ 'DEFINES' ], CC='~/bin/clang', CCFLAGS='-mtune=generic', LINKFLAGS='-s' )
	env.SConscript( 'SConscript', exports='env', variant_dir=env[ 'variant_dir' ], duplicate=0 )
#==============================================================================