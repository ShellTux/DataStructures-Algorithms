all: binTree

INCLUDE_DIR = include
SRC_DIR     = src

CC     = g++
CFLAGS = -Wall -Wextra -g -std=c++11 -I$(PWD)/$(INCLUDE_DIR)

debug: CFLAGS += -DDEBUG=1
debug: all

binTree: $(SRC_DIR)/binTree.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f binTree

relatorio.pdf: docs/report.md
	pandoc --standalone --resource-path=assets --output $@ $<

archive: AED-LuísGóis.zip

.PHONY: AED-LuísGóis.zip
AED-LuísGóis.zip: relatorio.pdf
	git archive --output=$@ --add-file=$< HEAD

.PHONY: .clangd
.clangd:
	rm --force $@

	@echo Diagnostics: | tee --append $@
	@echo '  UnusedIncludes: Strict' | tee --append $@
	@echo '  MissingIncludes: Strict' | tee --append $@
	@echo CompileFlags: | tee --append $@
	@echo '  Add:' | tee --append $@

	@for flag in $(CFLAGS) ; do echo "    - $$flag" | tee --append $@ ; done
