help:
	@echo 'Available make targets:'
	@echo '    build-examples  - build examples'
	@echo '    headers-deb     - build a deb package with headers'
	@echo '    clean           - remove produced files'

build-examples:
	$(MAKE) -C examples

VERSION = $(shell cat VERSION)
PREFIX = /usr/include
debtree =  DEBIAN
debDEBIAN = $(debtree)/DEBIAN
CONTROL = $(debDEBIAN)/control

headers-deb: $(debtree) $(CONTROL)
	mkdir -p $(debtree)$(PREFIX)
	cp -r PhysUnits $(debtree)$(PREFIX)
	dpkg-deb -b $(debtree) libphysunits-$(VERSION)_all.deb
	rm -rf $(debtree)

$(debtree):
	mkdir -p $(debtree)

$(debDEBIAN):
	mkdir -p $(debDEBIAN)

$(CONTROL): $(debDEBIAN)
	$(shell echo "Package: libphysunits-dev" > $(CONTROL))
	$(shell echo "Version: $(VERSION)" >> $(CONTROL))
	$(shell echo "Maintainer: Adam Rudzinski <adam.rudzinski@rdlabs.pl>" >> $(CONTROL))
	$(shell echo "Architecture: all" >> $(CONTROL))
	$(shell echo "Priority: optional" >> $(CONTROL))
	$(shell echo "Description:" >> $(CONTROL))
	$(shell echo " PhysUnits is a library for handling physical magnitudes with defined units." >> $(CONTROL))
	$(shell echo " It focuses on conversions between various units of the same magnitude" >> $(CONTROL))
	$(shell echo " (like cm and mils)." >> $(CONTROL))

clean:
	$(MAKE) -C examples clean
	rm -rf *.deb
