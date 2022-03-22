##
# Botanic L-system Modelisation
#
# @file
# @version 0.1


CC = g++

CORE_CPP_FILES = core/l_system.cpp core/rule.cpp
CORE_OBJ_FILES = $(CORE_CPP_FILES:.cpp=.o)

CXX_FLAGS += -Wall -Wextra -O3 -g -std=c++20
CXX_FLAGS += -lm
# CXX_FLAGS += -m64 -march=native
# CXX_FLAGS += -fopt-info-vec-optimized #-fopt-info-vec-missed -ftree-vectorize

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

#For gcc 4.9
#CXXFLAGS+=-fdiagnostics-color=auto
export GCC_COLORS=1

define color
    if test `tput colors` -gt 0 ; then \
	tput setaf $(1); \
    fi
endef

define default_color
 if test `tput colors` -gt 0 ; then  tput sgr0 ; fi
endef


all: main

pre-build:
	@$(call color,4)
	@echo "******** Starting Compilation ************"
	@$(call default_color)

post-build:
	@sta=$$?
	@$(call color,4)
	@echo "*********** End Compilation **************"
	@$(call default_color)
	@exit $$sta

main: pre-build build-main post-build

build-main: $(CORE_OBJ_FILES)
	$(CC) main.cpp -o lsys $(CORE_OBJ_FILES) $(CXX_FLAGS)

tree2D: pre-build build-tree2D post-build

build-tree2D: $(CORE_OBJ_FILES)
	$(CC) tree2D.cpp drawer2D.cpp -o bin_tree2D $(CORE_OBJ_FILES) $(CXX_FLAGS) $(LIBS)

%.o: %.cpp %.hpp
	@$(call color,2)
	@echo "[$@] $(CXX_FLAGS)"
	@$(call default_color)
	@$(CC) -c -o $@ $< $(CXX_FLAGS) ; \
	sta=$$?;	  \
	if [ $$sta -eq 0 ]; then  \
	  $(call color,2) ; \
	  echo "[$@ success]" ; \
	  $(call default_color) ; \
	else  \
	  $(call color,1) ; \
	  echo "[$@ failure]" ; \
	  $(call default_color) ; \
	fi ;\
	exit $$sta

.PHONY: all clean pre-build post-build build-main main tree2D build-tree2D

clean:
	rm -f lsys bin_tree2D
	rm -f $(CORE_OBJ_FILES) main.o

# end
