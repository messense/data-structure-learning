default: build

.DEFAULT:
	@echo Entering directory src.
	cd src && $(MAKE) $@
	@echo Leaving directory src.
	@echo Entering directory test.
	cd test && $(MAKE) $@
	@echo Leaving directory test.
	@echo All done, have fun!