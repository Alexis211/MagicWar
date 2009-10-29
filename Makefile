installdir = /opt/magicwar
.PHONY: clean, mrproper, po, mo

languages = fr

all: $(Objects)
	make -C game
	make -C server

updatepo:
	xgettext -f po/POTFILES.in -k_ -kU_ -o po/en.pot -C
	for lang in $(languages); do \
		msgmerge po/$$lang.po po/en.pot -o po/$$lang.po; \
	done

updatemo:
	for lang in $(languages); do  \
		mkdir -p data/locale/$$lang/LC_MESSAGES; \
		msgfmt po/$$lang.po -o data/locale/$$lang/LC_MESSAGES/magicwar.mo; \
	done

commit: mrproper
	git add .
	git commit -a
	git push origin

rebuild: mrproper all

clean:
	make -C game clean
	make -C server clean

mrproper: clean
	make -C game mrproper
	make -C server mrproper

install:
	mkdir $(installdir) -p
	cp game/magicwar $(installdir)
	cp server/magicwar-server $(installdir)
	cp -r data $(installdir)
	cp -r docs $(installdir)

uninstall:
	rm -rf $(installdir)
