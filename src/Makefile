##
# Botanic L-system Modelisation
#
# @file
# @version 0.1


CC = g++

CORE_CPP_FILES = core/l_system.cpp core/rule.cpp
OBJ_FILES = $(CORE_CPP_FILES:.cpp=.o)

CXX_FLAGS += -Wall -Wextra -O3 -g -std=c++17
CXX_FLAGS += -lm
CXX_FLAGS += -m64 -march=native
CXX_FLAGS += -fopt-info-vec-optimized #-fopt-info-vec-missed -ftree-vectorize

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

toto:
	$(CC) opencv_test.cpp -o test $(LIBS)

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


all: main-build

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

main-build: pre-build build post-build

build: $(OBJ_FILES)
	$(CC) main.cpp -o lsys $(OBJ_FILES) $(CXX_FLAGS)

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

.PHONY: all clean pre-build post-build main-build build



clean:
	rm -f lsys
	rm -f $(OBJ_FILES) main.o

# end
