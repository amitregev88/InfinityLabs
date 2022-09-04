
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(wildcard *.c)
PROJ_SRCS = watchdog.c watchdog_exec.c #watchdog_test.c 

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/ds/include

# the executable file
PROJ_OUT = watchdog_exec.out #watchdog_test.out

# list of ADDITIONAL compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS = -pthread
PROJ_CPPFLAGS =

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS = scheduler_heap.o uid.o pqueue_heap.o heap.o dynamic_vector.o task.o

# additional libraries
PROJ_LIBS = pthread

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/ds/scheduler_heap/Makefile

include $(ROOT_DIR)/make/Project.mak
