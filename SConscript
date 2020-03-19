#*******************************************************************************
import binascii
import os
import random
import re
import subprocess
#==============================================================================
Import( 'env' )
env.Append( CROSS_COMP_SRC_ARCH='0.tar.xz' )
obfuscate = {}
Q_random_I_id_S_begin_source = list( map( chr, random.sample( list( range( 97, 122 )) + [ 95 ] + list( range( 65, 90 )), 4 )))
Q_random_I_id_S_trail_source = list( range( 97, 122 )) + list( range( 48, 57 )) + list( range( 65, 90 )) + [ 95 ]
Q_random_I_id_S_chosen = [ '' ]
#==============================================================================
env.Alias( 'build', env[ 'EXE' ] )
env.Default( 'build' )
#==============================================================================
def Q_list_I_filename_I_map(s):
	return s.rpartition( '/' )[2]
#==============================================================================
def Q_random_I_id():
	a = []
	s = ''
	while s in Q_random_I_id_S_chosen:
		a = []
		i = 0
		while i < 3:
			a.append( chr( random.choice( Q_random_I_id_S_trail_source )))
			i = i + 1
		s = ''.join(a)
	Q_random_I_id_S_chosen.append(s)
	return ''.join( [ random.choice( Q_random_I_id_S_begin_source ) ] + a )
#------------------------------------------------------------------------------
def Q_h_builder_I_action( target, source, env ):
	global obfuscate
	d = '_'+ str( binascii.b2a_base64( bytes( str( source[0] ), 'UTF-8' ), newline = False ), 'ASCII' ).rstrip( '=' ) +'_H'
	s_new = '#ifndef '+ d +"\n#define "+ d +"\n"
	proc = subprocess.Popen( [ 'makeheaders', '-h', '--', str( source[0] ) ], stdin = subprocess.PIPE, stdout = subprocess.PIPE )
	for l in proc.stdout:
		l = str( l, 'UTF-8' )
		if env[ 'obfuscation' ]:
			if l.startswith( '_EXPORT_OBFUSCATE ' ):
				name = l.partition( '(' )[0].rpartition( ' ' )[2]
				if name not in obfuscate:
					obfuscate[name] = Q_random_I_id()
				s_new += '#define '+ name +' '+ obfuscate[name] +"\n"
				s_new += l
			elif l.startswith( 'OBFUSCATE' ):
				name = l.partition( '(' )[2].rpartition( ')' )[0].strip()
				if name not in obfuscate:
					obfuscate[name] = Q_random_I_id()
				s_new += '#define '+ name +' "'+ obfuscate[name] +"\"\n"
			else:
				s_new += l
		elif l.startswith( 'OBFUSCATE' ):
				name = l.partition( '(' )[2].rpartition( ')' )[0].strip()
				s_new += '#define '+ name +' "'+ name +"\"\n"
		else:
			s_new += l
	s_new += '#endif'
	try:
		with open( str( target[0] )) as r:
			s_old = r.read()
	except IOError:
		s_old = ''
	if s_new != s_old:
		with open( str( target[0] ), 'w' ) as w:
			w.write( s_new )
	return None
h_builder = env.Builder( action=Q_h_builder_I_action
, suffix='.h'
, src_suffix='.c'
)
env[ 'BUILDERS' ][ 'HFile' ] = h_builder
#------------------------------------------------------------------------------
def Q_ui_builder_I_action( target, source, env ):
	global obfuscate
	if env[ 'obfuscation' ]:
		regex = dict()
		regex[ 'object' ] = r'.*?\s(id|constructor)(?:=(?:"([^"]+)?")?)?'
		regex[ 'signal' ] = r'.*?\s(handler)(?:=(?:"([^"]+)?")?)?'
		regex[ 'menu' ] = r'.*?\s(id)(?:=(?:"([^"]+)?")?)?'
	else:
		regex = re.compile( r'\sid(?:=(?:"([^"]+)?")?)?' )
	with open( str( target[0] ), 'w' ) as w:
		for f in source:
			with open( str(f) ) as r:
				for l in r:
					i = 0
					if env[ 'obfuscation' ]:
						for m in re.finditer( r'.*?<('+ '|'.join( regex.keys() ) +r')(\s[^>]*?)(/?>)', l ):
							w.write( m.string[ m.start() : m.start(2) ] )
							found_id = False
							i = 0
							for m_1 in re.finditer( regex[ m.group(1) ], m.group(2) ):
								if m_1.group(2): #znacznik ma wartość.
									if m_1.group(1) == 'id':
										found_id = True
									if m_1.group(2) not in obfuscate:
										obfuscate[ m_1.group(2) ] = Q_random_I_id()
									w.write( m_1.string[ m_1.start() : m_1.end(1) ] +'="'+ obfuscate[ m_1.group(2) ] +'"' )
								elif m.group(1) == 'object' and m_1.group(1) == 'id': #znacznik nie miał wartości, lecz jest wymagany.
									found_id = True
									w.write( m_1.string[ m_1.start() : m_1.end(1) ] +'="'+ Q_random_I_id() +'"' )
								else: #znacznik nie miał wartości i nie jest wymagany.
									w.write( m_1.group() )
								i = m_1.end()
							w.write( m.string[ m.start(2) + i : m.end(2) ] )
							if m.group(1) == 'object' and not found_id:
								w.write( ' id="'+ Q_random_I_id() +'"' )
							w.write( m.group(3) )
							i = m.end()
					else:
						for m in re.finditer( r'.*?<object(\s[^>]*?)(/?>)', l ):
							w.write( m.string[ m.start() : m.start(1) ] )
							m_1 = regex.search( m.group(1) )
							if m_1: #znacznik jest.
								if m_1.group(1): #znacznik ma wartość.
									w.write( m_1.string )
								else:
									w.write( m_1.string[: m_1.start() ] +' id="'+ Q_random_I_id() +'"'+ m_1.string[ m_1.end() :] )
							else:
								w.write( m.group(1) +' id="'+ Q_random_I_id() +'"' )
							w.write( m.group(2) )
							i = m.end()
					w.write( l[ i :] )
#def Q_dynamic_list_builder_I_action( target, source, env ):
	#global obfuscate
	#with open( str( target[0] ), 'w' ) as w:
		#w.write( "{\n" )
		#for f in source:
			#with open( str(f) ) as r:
				#for l in r:
					#if l.startswith( '_EXPORT ' ) \
					#or l.startswith( '_EXPORT_OBFUSCATE ' ):
						#name = l.partition( '(' )[0].rpartition( ' ' )[2]
						#if env[ 'obfuscation' ] \
						#and l.startswith( '_EXPORT_OBFUSCATE ' ):
							#if name not in obfuscate:
								#obfuscate[name] = Q_random_I_id()
							#name = obfuscate[name]
						#w.write( name +";\n" )
		#w.write( "};" )
def Q_defines_I_gcc_string_I_map(a):
	return '-D'+ a[0] +'='+ a[1]
def Q_cross_comp_src_arch_builder_I_action( target, source, env ):
	files = map( Q_list_I_filename_I_map, map( str, source ))
	c = ''
	h = []
	for f in files:
		if f[-2:] == '.c':
			c += ' '+ f
		elif f[-2:] == '.h':
			h += [ f ]
	h = ' '.join( Q_flags_I_to_includes( env.Split( env[ 'INCLUDES' ] ) + h ))
	with open( env[ 'variant_dir' ] +'/Makefile', 'w' ) as w:
		w.write( env[ 'EXE' ] +'_l$(MARCH): '+ ' '.join(files) \
		  +"\n\t"+'clang -Qunused-arguments -pipe -fwrapv -march=$(MARCH) -flto -emit-llvm -Ofast -fvisibility=hidden -Wl,-E,--gc-sections -Wfatal-errors -Wall -Wno-parentheses '+ ' '.join( map( Q_defines_I_gcc_string_I_map, env[ 'CPPDEFINES' ] )) +' $$( pkg-config --cflags --libs '+ env[ 'PKGS' ] +' ) -iquote. '+ h +' -o $@'+ c \
		)
	subprocess.check_call( [ 'tar', 'caf', str( target[0] ), '--transform', 's`^.*/``', '--' ] + map( str, source ) + [ env[ 'variant_dir' ] +'/Makefile' ] )
#------------------------------------------------------------------------------
def Q_str_I_to_suffix( f, s ):
	return '%s.' % f.rpartition( '.' )[0] + s
def Q_str_I_to_h_suffix(f):
	return Q_str_I_to_suffix( f, 'h' )
def Q_list_I_to_headers(sources):
	a = []
	for f in map( Q_str_I_to_h_suffix, map( str, sources )):
		a += [ f ]
	return a
def Q_str_I_to_filename(f):
	return f.rpartition( '/' )[2]
def Q_flags_I_to_includes(headers):
	a = []
	for f in headers:
		a += [ '-include', str(f) ]
	print(a)
	return a
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uis = env.Glob( '*.ui0', True, True, True )
for f in uis:
	env.Command( Q_str_I_to_suffix( f, 'ui' ), f, Q_ui_builder_I_action )
uis = env.Glob( '*.ui', False, True, True )
env.Depends( 'build', uis )
sources = env.Glob( '*.c', True, True, True )
for f in sources:
	env.HFile(f)
	if env[ 'obfuscation' ]:
		env.Depends( Q_str_I_to_h_suffix(f), uis )
headers = [ '_0.h' ] + env.Glob( '*.h', False, False, True )
for f in sources:
	env.Depends( Q_str_I_to_suffix( f, 'o' ), headers )
env.Program( env[ 'EXE' ], sources )
#------------------------------------------------------------------------------
if str( Dir( '.' ).path ) == '.build_dist':
	env.Command( env[ 'CROSS_COMP_SRC_ARCH' ], sources + headers, Q_cross_comp_src_arch_builder_I_action )
	env.Depends( env[ 'CROSS_COMP_SRC_ARCH' ], env[ 'EXE' ] )
	env.Clean( env[ 'CROSS_COMP_SRC_ARCH' ], 'Makefile' )
#------------------------------------------------------------------------------
env.Append( CPPDEFINES=[ ( '_EXPORT', "'"'__attribute__((visibility("default")))'"'" ), ( '_EXPORT_OBFUSCATE', '_EXPORT' ), ( "'"'OBFUSCATE(a)'"'", '' ), ( 'FALSE', '0' ), ( 'TRUE', '1' ) ] )
headers = list( map( Q_str_I_to_filename, headers ))
env.Append( CPPFLAGS=Q_flags_I_to_includes( env.Split( env[ 'INCLUDES' ] ) + headers ))
env.Append( CCFLAGS=env.Split( '-flto -emit-llvm -fvisibility=hidden -iquote'+ str( Dir( '.' ).path ) +' -iquote.' ))
env.ParseFlags( '-I'+ os.environ[ 'HOME' ] +'/.local/include -L'+ os.environ[ 'HOME' ] +'/.local/lib' )
env.ParseConfig( 'pkg-config --cflags --libs '+ env[ 'PKGS' ] )
env.Append( LINKFLAGS=env.Split( '-flto -Wl,--as-needed,-E,--gc-sections,-X' ))
#*******************************************************************************
