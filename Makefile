#==============================================================================
PHONY_TARGETS := build rebuild run dist-1 dist-2 dist-3 dist-4 clean clean-dist
.PHONY: $(PHONY_TARGETS)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OTHER_TARGETS := $(filter-out $(PHONY_TARGETS),$(MAKECMDGOALS))
.DEFAULT: build
build:
	scons -j 4 $(OTHER_TARGETS)
rebuild: clean build
run:
	cd .build && ./notepad
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.build_dist/0.tar.xz: clean-dist
	scons $@
dist-1: .build_dist/0.tar.xz
dist-2:
	install -o ftp -g ftp -m 444 -t ~ftp/dload .build_dist/0.tar.xz
	systemctl start vsftpd
dist-3:
	systemctl stop vsftpd
	rm ~ftp/dload/0.tar.xz
	for d in li686 li386; do \
		chown inc:inc ~ftp/upload/notepad_$$d \
		&& chmod 600 ~ftp/upload/notepad_$$d \
		&& mv ~ftp/upload/notepad_$$d ~inc/moje/programy/narzędzia/notatnik/.dist/ ;\
	done
dist-4:
	{ [ -d .dist ] || mkdir .dist; } && cd .dist \
	&& ln -f ../.build_dist/notepad notepad_lx86_64 \
	&& for d in lx86_64 li686 li386; do \
		   { [ -d $$d ] || mkdir $$d; } && cd $$d \
		   && { [ -d external ] || mkdir external; } && chmod 755 external \
		   && install -m 644 -t external ../../external/* \
		   && install -m 644 -t . ../../.build_dist/*.ui \
		   && install -m 600 -t . ../../manual_open_from_notepad \
		   && install -m 755 -T ../notepad_$$d notepad \
		   && rm -f ../notepad_$$d.tar.xz.gpg \
		   && tar cJ * \
		     | gpg --batch -u 5E72C266 -s -o ../notepad_$$d.tar.xz.gpg \
		   && cd .. \
		   && rm -r $$d \
		   || break ;\
	done
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
clean-dist:
	rm -f .build_dist/0.tar.xz
clean:
	scons -c
#==============================================================================
