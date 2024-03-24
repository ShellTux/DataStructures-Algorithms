all: binTree

VENV       := venv
PYTHON     := ./$(VENV)/bin/python3
PIP        := ./$(VENV)/bin/pip
PYTEST     := ./$(VENV)/bin/pytest
PRE_COMMIT := ./$(VENV)/bin/pre-commit

INCLUDE_DIR = include
SRC_DIR     = src

CC     = g++
CFLAGS = -Wall -Wextra -g -std=c++11 -I$(PWD)/$(INCLUDE_DIR)

debug: CFLAGS += -DDEBUG=1
debug: all

binTree: $(SRC_DIR)/binTree.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(VENV)
	rm -f binTree

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

$(VENV)/bin/activate: requirements.txt
	python3 -m venv $(VENV)
	$(PIP) install --requirement requirements.txt

venv: $(VENV)/bin/activate
