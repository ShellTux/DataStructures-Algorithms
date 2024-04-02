MAKEFLAGS += --jobs=4 --output-sync=target

ARCHIVE     = AED-LuísGóis.zip
INCLUDE_DIR = $(PWD)/include
OBJ_DIR     = obj
SRC_DIR     = src
TARGETS     = binTree sorting
VENV       := venv
PYTHON     := ./$(VENV)/bin/python3
PIP        := ./$(VENV)/bin/pip
PYTEST     := ./$(VENV)/bin/pytest
PRE_COMMIT := ./$(VENV)/bin/pre-commit

HEADERS  = $(shell find $(INCLUDE_DIR) \
	   -name "*.h" -o \
	   -name "*.hpp" \
	   2>/dev/null | tr '\n' ' ')

CC      = g++
CFLAGS  = -Wall -Wextra -std=c++11
CFLAGS  = -Wall -Wextra -Werror
CFLAGS += -Wno-error=unused-parameter
CFLAGS += -Wno-error=unused-variable
CFLAGS += -Wno-error=unused-but-set-variable
CFLAGS += -fdiagnostics-color=always
CFLAGS += -I$(INCLUDE_DIR)
LINKS   =

all: $(TARGETS)

debug: CFLAGS += -g -DDEBUG=1
debug: clean all

$(OBJ_DIR)/%.cpp.o: %.cpp $(HEADERS)
	@printf "\n\033[31m"
	@printf "########################\n"
	@printf "Building %s\n" $@
	@printf "########################\n"
	@printf "\033[0m\n"
	mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -c -o $@ $<

SOURCES = binTree
binTree: $(SOURCES:%=$(OBJ_DIR)/$(SRC_DIR)/%.cpp.o)

SOURCES = Sort/main
sorting: $(SOURCES:%=$(OBJ_DIR)/$(SRC_DIR)/%.cpp.o)

$(TARGETS): %:
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.md: %.md
	mkdir --parents `dirname $@`
	cp $< $@
	sed -i 's|/assets|assets|g' $@
	sed -i 's|date: date|date: '$(shell date +'%d/%m/%Y')'|' $@

archive: $(ARCHIVE)

.PHONY: $(ARCHIVE)
$(ARCHIVE): relatorio.pdf
	git archive --output=$@ --add-file=$< HEAD

setup: .clangd

.PHONY: .clangd
.clangd:
	rm --force $@

	@echo Diagnostics: | tee --append $@
	@echo '  UnusedIncludes: Strict' | tee --append $@
	@echo '  MissingIncludes: Strict' | tee --append $@
	@echo CompileFlags: | tee --append $@
	@echo '  Add:' | tee --append $@

	@for flag in $(CFLAGS) ; do echo "    - $$flag" | tee --append $@ ; done

.PHONY: clean
clean:
	@printf "Cleaning\n"
	rm -f $(TARGETS)
	rm -rf $(OBJ_DIR)

.PHONY: watch
watch:
	@while true ;\
	do \
		clear ; \
		$(MAKE) --no-print-directory; \
		inotifywait --quiet --event modify --recursive $(INCLUDE_DIR) --recursive $(SRC_DIR); \
	done

.PHONY: PRINT-MACROS
PRINT-MACROS:
	@make -p MAKE-MACROS| grep -A1 "^# makefile" | grep -v "^#\|^--" | sort

$(VENV)/bin/activate: requirements.txt
	python3 -m venv $(VENV)
	$(PIP) install --requirement requirements.txt

venv: $(VENV)/bin/activate
