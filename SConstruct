#*******************************************************************************
env_0 = { 'EXE': 'notepad', 'PKGS': 'gtk+-3.0 gmodule-no-export-2.0 gdk-3.0', 'INCLUDES': 'stdint.h stdlib.h string.h errno.h gtk/gtk.h gdk/gdk.h', 'DEFINES': [ ( 'FALSE', 'false' ), ( 'TRUE', 'true' ) ] }
#==============================================================================
if len( COMMAND_LINE_TARGETS ) == 0 or 'build' in COMMAND_LINE_TARGETS:
	env = Environment( variant_dir='.build', EXE=env_0[ 'EXE' ], PKGS=env_0[ 'PKGS' ], INCLUDES=env_0[ 'INCLUDES' ], obfuscation=False, CPPDEFINES=env_0[ 'DEFINES' ], CC='/usr/lib/llvm/13/bin/clang', CCFLAGS='-pipe -fwrapv -flto -emit-llvm -Ofast -march=native'.split() )
	env.SConscript( 'SConscript', exports='env', variant_dir=env[ 'variant_dir' ], duplicate=0 )
if len( COMMAND_LINE_TARGETS ) == 0 or '.build-dist/0.tar.xz' in COMMAND_LINE_TARGETS:
	env = Environment( variant_dir='.build-dist', EXE=env_0[ 'EXE' ], PKGS=env_0[ 'PKGS' ], INCLUDES=env_0[ 'INCLUDES' ], obfuscation=True, CPPDEFINES=env_0[ 'DEFINES' ], CC='/usr/lib/llvm/13/bin/clang', CCFLAGS='-pipe -fwrapv -flto -emit-llvm -Ofast -mtune=generic'.split(), LINKFLAGS='-s' )
	env.SConscript( 'SConscript', exports='env', variant_dir=env[ 'variant_dir' ], duplicate=0 )
#*******************************************************************************
