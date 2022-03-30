##
# Botanic L-system Modelisation
#
# @file
# @version 0.1


CC = g++

CORE_CPP_FILES = core/l_system.cpp core/rule.cpp core/module.cpp core/state.cpp
CORE_OBJ_FILES = $(CORE_CPP_FILES:.cpp=.o)

UTILS_CPP_FILES = utils/turtle.cpp utils/drawer2D.cpp
# UTILS_OBJ_FILES = $(UTILS_CPP_FILES:.cpp=.o)

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


all: fractals brackets context_sensitive stochastic

pre-build:
	@$(call color,4)
	@echo "******** Starting Compilation ************"
	@mkdir -p build
	@$(call default_color)

post-build:
	@sta=$$?
	@$(call color,4)
	@echo "*********** End Compilation **************"
	@$(call default_color)
	@exit $$sta

# main: pre-build build-main post-build

# build-main: $(CORE_OBJ_FILES)
# 	$(CC) main.cpp -o lsys $(CORE_OBJ_FILES) $(CXX_FLAGS)

fractals: pre-build build-fractals post-build

build-fractals: $(CORE_OBJ_FILES)
	@mkdir -p output/fractals
	$(CC) fractals.cpp $(UTILS_CPP_FILES) -o build/fractals $(CORE_OBJ_FILES) $(CXX_FLAGS) $(LIBS) 

brackets: pre-build build-brackets post-build

build-brackets: $(CORE_OBJ_FILES)
	@mkdir -p output/brackets
	$(CC) brackets.cpp $(UTILS_CPP_FILES) -o build/brackets $(CORE_OBJ_FILES) $(CXX_FLAGS) $(LIBS)

stochastic: pre-build build-stochastic post-build

build-stochastic: $(CORE_OBJ_FILES)
	@mkdir -p output/stochastic
	$(CC) stochastic.cpp $(UTILS_CPP_FILES) -o build/stochastic $(CORE_OBJ_FILES) $(CXX_FLAGS) $(LIBS)

context_sensitive: pre-build build-context_sensitive post-build

build-context_sensitive: $(CORE_OBJ_FILES)
	@mkdir -p output/context_sensitive
	$(CC) context_sensitive.cpp $(UTILS_CPP_FILES) -o build/context_sensitive $(CORE_OBJ_FILES) $(CXX_FLAGS) $(LIBS)

parametric: pre-build build-parametric post-build

build-parametric: $(CORE_OBJ_FILES)
	@mkdir -p output/parametric
	$(CC) parametric.cpp $(UTILS_CPP_FILES) -o build/parametric $(CORE_OBJ_FILES) $(CXX_FLAGS) $(LIBS)

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

.PHONY: all clean pre-build post-build build-main main fractals build-fractals #tree2D build-tree2D

clean:
	rm -f lsys bin_tree2D
	rm -f build/*
	rm -f $(CORE_OBJ_FILES) main.o tree2D.o drawer2D.o
	rm -f $(CORE_OBJ_FILES) $(UTILS_OBJ_FILES) main.o

# end
