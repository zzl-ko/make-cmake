###############################################################################
# Declaration: 特别鸣谢以下三位作者，本文的完成主要参考和引用他（她）们的作品
#              whyglinux (https://sourceforge.net/projects/gcmakefile/)
#              mbcrawfo  (https://github.com/mbcrawfo/GenericMakefile)
#              胡彦      (http://blog.csdn.net/huyansoft/article/details/8924624)
# Copyright  : GPL (General Public License)
# Author     : Kevin Zhou <zzl.ko@outlook.com>
# Date       : 2015-01-27 (version 0.1)
# Description: 这是一个Unix/Linux下基于GNU Make环境编写的一个C/C++通用Makefile。
#              本Makefile支持C和C++的混合编译，因而为了能够在C++程序里调用C函数，
#              必须把每一个要调用的C函数，其声明都包括在extern "C"{}块里面。
#              如果使用g++编译C和C++的混合源码，不应将C源码包含在extern "C"{}块中！
# Usages     : 1.拷贝本Makefile文件到程序工程目录下；
#              2.对“定制段”，“适配段”中各参数做适当的配置；
#              3.直接执行make开始编译创建目标程序；
#              4.复制本文件到子模块目录再配置“定制段”即可嵌套调用；
#              5.对本Makefile可用的目标及相关帮助信息可通过make help得到。
# History    : 参见文件末尾
#==============================================================================
MK_VERSION  := 0.8

# 定制段，工程配置选项 START
###############################################################################
# 编译类型，0: 可执行程序，1: 动态链接库，2: 静态链接库
COM_TYPE     = 1

# 编译链接库时，（通常需要）去除的包含main函数的源文件，在此指明文件，不含后缀
MAIN_FILE    = main

# 最终目标，即可执行程序（或不含后缀的链接库）的名字
BIN_NAME     = calc

# 存放工程源文件的目录路径（相对于本Makefile文件）。现仅支持当前路径不建议修改！
SRC_PATH     = .

# 在工程的顶层目录下创建的用于存放最终编译目录的的文件夹（为.或空则不创建）
BIN_PATH     = bin

# 在工程的顶层目录下创建的用于存放编译临时文件的目录（为.或空则不创建）
BUILD_PATH   = build

# true: 查找当前路径下所有文件夹中的源文件, false: 仅当前文件夹
INC_SUB_DIRS = true

# true: 嵌套调用子目录下的Makefile, false: 仅执行当前Makefile
INC_SUB_MAKE = false

# make的默认编译工作的模式（debug或release）
MAKE_MODE    = release

# 程序安装的相关设置
INSTALL_CMD  = install
INSTALL_BIN  = /usr/local/bin
INSTALL_DATA = /etc/$(BIN_NAME)
INSTALL_MODE = $(INSTALL) -m 644
#==============================================================================
# 定制段 END

# 适配段，编译链接等选项 START
###############################################################################
# 指定C或C++的编译器
CC        = gcc
CXX       = g++
# 去掉下行注释，可用C++编译器编译C程序
# CC        = $(CXX)

# 额外的头文件路径（形式为：-I路径；以空格分割），指定寻找头文件的目录
INCLUDES  = -I$(SRC_PATH) -I./calc -I./utility

# 额外的链接库路径（形式为：-L路径；以空格分割），指定寻找链接库文件的目录
LIBPATHS  = -L./calc/bin -L./utility/bin

# 需要连接的库文件（形式为：-l具体某个链接库的名称，不带后缀；以空格分割）
# 注：库需要以lib作为开头，而在指定链接命令行参数时，却无需包含开头和扩展名
# 动态库（以.so为后缀），注意如果A依赖B，则B应当在A的右边
DLIBRARIES= -pthread -lcalc

# 静态库（以.a为后缀），同上
SLIBRARIES= -lutility

# 编译预处理选项（cpp: compile pre-processor），使用man cpp获取相关信息
CPPFLAGS  = -Wall

# 编译选项（通过命令行可覆写这些选项），使用man gcc或man g++获取相关信息
CFLAGS    = -O1
CXXFLAGS  = -O2

# 其它额外的预处理和编译选项
OCFLAGS   = -D _LINUX_

# 链接选项，使用man ld获取相关信息
LDFLAGS   =

# 指定调试(Debug)或发布(Release)时的编译和链接选项
DCFLAGS   = -g -D DEBUG
DLDFLAGS  =

RCFLAGS   = -D NDEBUG
RLDFLAGS  =

# 为Emacs编辑器创建tags文件
ETAGS     = etags
ETAGSFLAGS=
# 为Vim编辑器创建tags文件
CTAGS     = ctags
CTAGSFLAGS=
#==============================================================================
# 适配段 END

# 固定段，make工作的主体描述（通常不需更改，但可自行扩展） START
###############################################################################
#==============================================================================
# Shell used in this makefile(bash is used for 'echo -en')
SHELL   = /bin/bash
EMPTY   =
SPACE   = $(EMPTY) $(EMPTY)

# Default compiler if they are no define.
CC     ?= gcc
CXX    ?= g++

# Obtains the OS type, either 'Darwin' (OS X) or 'Linux'
UNAME_S:= $(shell uname -s)

# Macros for timing compilation
ifeq ($(UNAME_S),Darwin)
  CUR_TIME = awk 'BEGIN{srand(); print srand()}'
  TIME_FILE = $(dir $@).$(notdir $@)_time
  START_TIME = $(CUR_TIME) > $(TIME_FILE)
  END_TIME = read st < $(TIME_FILE) ; \
    $(RM) $(TIME_FILE) ; \
    st=$$((`$(CUR_TIME)` - $$st)) ; \
    echo $$st
else
  TIME_FILE = $(dir $@).$(notdir $@)_time
  START_TIME = date '+%s' > $(TIME_FILE)
  END_TIME = read st < $(TIME_FILE) ; \
    $(RM) $(TIME_FILE) ; \
    st=$$((`date '+%s'` - $$st - 86400)) ; \
    echo `date -u -d @$$st '+%H:%M:%S'`
endif

# Version macros(Comment/remove this section to remove versioning).
USE_VERSION := false
ifeq ($(shell git describe > /dev/null 2>&1 ; echo $$?), 0)
  USE_VERSION := true
  VERSION := $(shell git describe --tags --long --dirty --always | \
    sed 's/v\([0-9]*\)\.\([0-9]*\)\.\([0-9]*\)-\?.*-\([0-9]*\)-\(.*\)/\1 \2 \3 \4 \5/g')
  VERSION_MAJOR := $(word 1, $(VERSION))
  VERSION_MINOR := $(word 2, $(VERSION))
  VERSION_PATCH := $(word 3, $(VERSION))
  VERSION_REVISION := $(word 4, $(VERSION))
  VERSION_HASH := $(word 5, $(VERSION))
  VERSION_STRING := \
    "$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH).$(VERSION_REVISION)-$(VERSION_HASH)"
  override CFLAGS := $(CFLAGS) \
    -D VERSION_MAJOR=$(VERSION_MAJOR) \
    -D VERSION_MINOR=$(VERSION_MINOR) \
    -D VERSION_PATCH=$(VERSION_PATCH) \
    -D VERSION_REVISION=$(VERSION_REVISION) \
    -D VERSION_HASH=\"$(VERSION_HASH)\"
endif

# Named a default name for target if BIN_NAME is no define.
ifeq ($(BIN_NAME),)
  CUR_PATH = $(subst /,$(SPACE),$(subst $(SPACE),_,$(CURDIR)))
  BIN_NAME = $(word $(words $(CUR_PATH)),$(CUR_PATH))
  ifeq ($(BIN_NAME),)
    BIN_NAME = demo
  endif
endif

ifeq ($(BIN_PATH),)
  BIN_PATH   := .
endif
ifeq ($(BUILD_PATH),)
  BUILD_PATH := .
endif

TARGET = $(shell if [ "$(BIN_PATH)" != "." ];then echo "$(BIN_PATH)/"; fi)$(BIN_NAME)

LIBRARIES = $(EMPTY)
ifneq ($(SLIBRARIES),)
  LIBRARIES += -Wl,-Bstatic  $(SLIBRARIES)
endif
ifneq ($(DLIBRARIES),)
  LIBRARIES += -Wl,-Bdynamic $(DLIBRARIES)
endif

# Append pkg-config specific libraries if need be.
ifneq ($(LIBRARIES),)
#   OCFLAGS += $(shell pkg-config --cflags $(LIBRARIES))
#   LDFLAGS += $(shell pkg-config --libs   $(LIBRARIES))
endif

ifneq ($(MAKE_MODE),release)
  OCFLAGS += $(DCFLAGS)
  LDFLAGS += $(LIBPATHS) $(DLDFLAGS) -Wl,-Map,$(TARGET).map
else
  OCFLAGS += $(RCFLAGS)
  LDFLAGS += $(LIBPATHS) $(RLDFLAGS) -Wl,-Map,$(TARGET).map
endif

# Get the dirs that store source files.
ifeq ($(INC_SUB_DIRS),true)
  SRCDIRS = $(shell find . -type d)
else
  SRCDIRS = .
endif

ifeq ($(INC_SUB_MAKE),true)
  SUBDIRS = $(shell ls -l | grep ^d | grep -v $(BUILD_PATH) | grep -v $(BIN_PATH) | awk '{print $$9}')
  BLDDIRS = $(foreach d,$(SUBDIRS),$(addprefix $(d)/*,$(BUILD_PATH)))
  BINDIRS = $(foreach d,$(SUBDIRS),$(addprefix $(d)/*,$(BIN_PATH)))
endif

# Get the root path of current project.
ifndef ROOT_PATH
  ROOT_PATH = $(shell pwd)
endif

# Auto assign headers abspath of curr project for compiler.
ifdef INCLUDES
  CURR_PATH = $(shell pwd)
  CURR_DIRS = $(shell find . \( -path ./$(BIN_PATH) -o -path ./$(BUILD_PATH) \) \
                            -prune -o -type d ! -name "." -print )
  INCLUDES += $(subst ./, -I$(CURR_PATH)/, $(CURR_DIRS))
endif

# The source and header file types.
# .c indicates C source files, and others C++ ones.
SRCEXTS = .c .C .cc .cpp .CPP .c++ .cxx .cp
HDREXTS = .h .H .hh .hpp .HPP .h++ .hxx .hp
# Delete the default suffixes rules.
.SUFFIXES:

HEADERS = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(HDREXTS))))
SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
SRC_CXX = $(filter-out %.c,$(SOURCES))
OBJECTS = $(addprefix $(BUILD_PATH),$(patsubst ./%,/%,$(addsuffix .o,$(basename $(SOURCES)))))
DEPENDS = $(OBJECTS:.o=.d)

DEP_OPT = $(shell if `$(CC) --version | grep $(CC) >/dev/null`; then \
                  echo "-MG -MM -MP"; else echo "-M"; fi )
DEPEND      = $(CC)  $(CPPFLAGS) $(CFLAGS)   $(OCFLAGS) $(INCLUDES) $(DEP_OPT)
DEPEND.d    = $(subst -g ,,$(DEPEND))
COMPILE.c   = $(CC)  $(CPPFLAGS) $(CFLAGS)   $(OCFLAGS) $(INCLUDES)
COMPILE.cxx = $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OCFLAGS) $(INCLUDES)
LINK.c      = $(CC)  $(CPPFLAGS) $(CFLAGS)   $(OCFLAGS) $(INCLUDES) $(LDFLAGS)
LINK.cxx    = $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OCFLAGS) $(INCLUDES) $(LDFLAGS)

ifneq ($(COM_TYPE),0)
  ifneq ($(MAIN_FILE),)
    # filter out the file contain main function.
    OBJECTS := $(filter-out %/$(MAIN_FILE).o,$(OBJECTS))
    DEPENDS := $(OBJECTS:.o=.d)
  endif
endif

# Verbose option, to output compile and link commands
export Verbose := false
ifeq ($(Verbose),true)
  export CPREFIX :=
else
  export CPREFIX := @
endif

# Build and output paths
export BIN_PATH BUILD_PATH ROOT_PATH

# Combine compiler and linker flags and variables
export CFLAGS CXXFLAGS CPPFLAGS LDFLAGS OCFLAGS

# compiler and linker flags when debug or release.
staticlib: export TARGET      := $(BIN_PATH)/lib$(BIN_NAME).a
sharedlib: export TARGET      := $(BIN_PATH)/lib$(BIN_NAME).so
sharedlib: export COMPILE.c   += -fPIC
sharedlib: export COMPILE.cxx += -fPIC
release:   export COMPILE.c   := $(COMPILE.c)
release:   export COMPILE.cxx := $(COMPILE.cxx)
release:   export LINK.c      := $(LINK.c)
release:   export LINK.cxx    := $(LINK.cxx)
debug:     export COMPILE.c   := $(COMPILE.c)
debug:     export COMPILE.cxx := $(COMPILE.cxx)
debug:     export LINK.c      := $(LINK.c)
debug:     export LINK.cxx    := $(LINK.cxx)

# Create the directories used in the build.
ifeq ($(shell if [ -d $(BUILD_PATH) ] && [ "."!=$(BUILD_PATH) ];then echo "true"; else echo "false"; fi),false)
  MKBUILDDIRS = mkdir -p $(dir $(OBJECTS))
endif

# Define commands for creating dependency files
define gen_deps
  @$(MKBUILDDIRS)
  @echo -n $(dir $@) > $@
  @$(DEPEND.d)   $< >> $@
endef

define gen_cxx_objs
  @echo "Compiling: $< -> $@"
  @$(START_TIME)
  $(CPREFIX)$(COMPILE.cxx) -c $< -o $@
  @echo -en "\t Compile time: "
  @$(END_TIME)
endef

define gen_sub_target
  @$(START_TIME)
  @$(MAKE) submake --no-print-directory
  @echo -n "SubMake total build time: "
  @$(END_TIME)
endef

define gen_all_target
  @$(START_TIME)
  @$(MAKE) all --no-print-directory
  @echo -n "All Total build time: "
  @$(END_TIME)
endef

define after_target_func
  @if [ $(CURR_PATH) != $(ROOT_PATH) ]; then \
   mkdir -p $(dir $(ROOT_PATH)/$(TARGET));   \
   cp $(CURR_PATH)/$(TARGET) $(ROOT_PATH)/$(TARGET); fi
endef

# Standard, non-optimized release build.
#---------------------------------------
.PHONY: release
release:
	@echo "Beginning debug build "$(shell if [ "$(USE_VERSION)" = "true" ];then echo "v$(VERSION_STRING)"; fi)
ifeq ($(INC_SUB_MAKE),true)
	$(CPREFIX)$(gen_sub_target)
endif
ifneq  ($(COM_TYPE),0)
  ifeq ($(COM_TYPE),1)
	@$(MAKE) sharedlib --no-print-directory
  else
	@$(MAKE) staticlib --no-print-directory
  endif
else
	$(CPREFIX)$(gen_all_target)
endif

# Debug build for gdb debugging.
#-------------------------------
.PHONY: debug
debug:
	@echo "Beginning debug build "$(shell if [ "$(USE_VERSION)" = "true" ];then echo "v$(VERSION_STRING)"; fi)
ifeq ($(INC_SUB_MAKE),true)
	$(CPREFIX)$(gen_sub_target)
endif
ifneq  ($(COM_TYPE),0)
  ifeq ($(COM_TYPE),1)
	@$(MAKE) sharedlib --no-print-directory
  else
	@$(MAKE) staticlib --no-print-directory
  endif
else
	$(CPREFIX)$(gen_all_target)
endif

# call sub dir's makefile.
#-------------------------
.PHONY: submake
submake: $(SUBDIRS)
$(SUBDIRS): FORCE
ifeq ($(INC_SUB_MAKE),true)
	@echo "Entering directory: ---> $@"
  ifneq ($(MAKECMDGOALS),submake)
	@$(MAKE) -C $@ $(MAKECMDGOALS)
  else
	@$(MAKE) -C $@
  endif
	@echo "Exiting  directory: <--- $@"
endif

# Main rule, checks the executable and symlinks to the output.
#-------------------------------------------------------------
.PHONY: all
all: $(TARGET)
ifneq ($(BIN_PATH),.)
	@echo "Making symlink: $(BIN_NAME) -> $(TARGET)"
	@$(RM) $(BIN_NAME)
	@ln -s $(TARGET) $(BIN_NAME)
endif
	$(CPREFIX)$(after_target_func)

# Rules for link and generating the executable.
#----------------------------------------------
$(TARGET): objs
	@echo "Linking: $@"
	@$(START_TIME)
ifeq ($(SRC_CXX),)              # C program
	$(CPREFIX)$(LINK.c)   $(OBJECTS) $(LIBRARIES) -o $@
else                            # C++ program
	$(CPREFIX)$(LINK.cxx) $(OBJECTS) $(LIBRARIES) -o $@
endif
	@echo -en "\t Link time: "
	@$(END_TIME)

# make shared library.
#---------------------
.PHONY: sharedlib
sharedlib: objs
	@echo "Make shared library: $(TARGET)"
	@$(START_TIME)
ifeq ($(SRC_CXX),)              # C program
	$(CPREFIX)$(COMPILE.c)   $(OBJECTS) -shared -o $(TARGET)
else                            # C++ program
	$(CPREFIX)$(COMPILE.cxx) $(OBJECTS) -shared -o $(TARGET)
endif
	@echo -en "\t Total time: "
	@$(END_TIME)
	$(CPREFIX)$(after_target_func)

# make static library.
#---------------------
.PHONY: staticlib
staticlib: objs
	@echo "Make static library: $(TARGET)"
	@$(START_TIME)
	@echo "C and C++ static library" > /dev/null
	$(CPREFIX)ar cr $(TARGET) $(OBJECTS)
	@echo -en "\t Total time: "
	@$(END_TIME)
	$(CPREFIX)$(after_target_func)

# Create the directories used in the build.
#------------------------------------------
.PHONY: dirs
dirs:
ifeq ($(shell if [ -d $(BUILD_PATH) ] && [ -d $(BIN_PATH) ];then echo "true"; else echo "false"; fi),false)
	@echo "Creating directories"
endif
ifneq ($(BUILD_PATH),.)
	@mkdir -p $(dir $(OBJECTS))
endif
ifneq ($(BIN_PATH),.)
	@mkdir -p $(BIN_PATH)
endif

# Rules for generating object files (.o).
#----------------------------------------
.PHONY: objs
objs: dirs deps $(OBJECTS)

$(BUILD_PATH)/%.o:$(SRC_PATH)/%.c
	@echo "Compiling: $< -> $@"
	@$(START_TIME)
	$(CPREFIX)$(COMPILE.c) -c $< -o $@
	@echo -en "\t Compile time: "
	@$(END_TIME)
	
$(BUILD_PATH)/%.o:$(SRC_PATH)/%.C
	$(CPREFIX)$(gen_cxx_objs)
	
$(BUILD_PATH)/%.o:$(SRC_PATH)/%.cc
	$(CPREFIX)$(gen_cxx_objs)
	
$(BUILD_PATH)/%.o:$(SRC_PATH)/%.cp
	$(CPREFIX)$(gen_cxx_objs)
	
$(BUILD_PATH)/%.o:$(SRC_PATH)/%.cpp
	$(CPREFIX)$(gen_cxx_objs)
	
$(BUILD_PATH)/%.o:$(SRC_PATH)/%.CPP
	$(CPREFIX)$(gen_cxx_objs)
	
$(BUILD_PATH)/%.o:$(SRC_PATH)/%.c++
	$(CPREFIX)$(gen_cxx_objs)
	
$(BUILD_PATH)/%.o:$(SRC_PATH)/%.cxx
	$(CPREFIX)$(gen_cxx_objs)
	
# Rules for creating dependency files (.d).
#------------------------------------------
.PHONY: deps
deps: $(DEPENDS)

$(BUILD_PATH)/%.d:$(SRC_PATH)/%.c
	$(CPREFIX)$(gen_deps)
	
$(BUILD_PATH)/%.d:$(SRC_PATH)/%.C
	$(CPREFIX)$(gen_deps)

$(BUILD_PATH)/%.d:$(SRC_PATH)/%.cc
	$(CPREFIX)$(gen_deps)
	
$(BUILD_PATH)/%.d:$(SRC_PATH)/%.cp
	$(CPREFIX)$(gen_deps)

$(BUILD_PATH)/%.d:$(SRC_PATH)/%.cpp
	$(CPREFIX)$(gen_deps)

$(BUILD_PATH)/%.d:$(SRC_PATH)/%.CPP
	$(CPREFIX)$(gen_deps)

$(BUILD_PATH)/%.d:$(SRC_PATH)/%.c++
	$(CPREFIX)$(gen_deps)

$(BUILD_PATH)/%.d:$(SRC_PATH)/%.cxx
	$(CPREFIX)$(gen_deps)
	
# other useful phony targets
.PHONY: clean distclean install uninstall show help

# Installs the program
install:
	@echo "Installing program to $(INSTALL_BIN)"
	@$(INSTALL_CMD) $(TARGET) $(INSTALL_BIN)
ifneq ($(INSTALL_DATA),)
	@echo "Installing data to $(INSTALL_DATA)"
	@$(INSTALL_CMD) -t $(INSTALL_DATA) $(TARGET)
endif

# Uninstalls the program
uninstall:
	@echo "Removing $(INSTALL_BIN)/$(BIN_NAME)"
	@$(RM) $(INSTALL_BIN)/$(BIN_NAME)
ifneq ($(INSTALL_DATA),)
	@echo "Removing data $(INSTALL_DATA)"
	@$(RM) -r $(INSTALL_DATA)
endif

check: ; @echo "check: do nothing"

test: ; @echo "test: do nothing"

# Rules for generating the tags
etags: $(HEADERS) $(SOURCES)
	$(ETAGS) $(ETAGSFLAGS) $(HEADERS) $(SOURCES)

ctags: $(HEADERS) $(SOURCES)
	$(CTAGS) $(CTAGSFLAGS) $(HEADERS) $(SOURCES)

# Removes all temp files
clean: $(SUBDIRS)
	@echo "Deleting temporary files"
	$(CPREFIX)$(RM) $(TIME_FILE) .*_time
	$(CPREFIX)$(RM) $(OBJECTS) $(DEPENDS)
	$(CPREFIX)find . -type f -name "*.o" -o -name "*.d" | xargs rm -f

# Removes all build files
distclean: clean $(SUBDIRS)
	@echo "Deleting tags files"
	@$(RM) tags TAGS
	@echo "Deleting $(BIN_NAME) or it's symlink"
	@$(RM) $(BIN_NAME)
	@echo "Deleting build directories, if exist"
ifneq ($(BUILD_PATH),.)
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BLDDIRS)
endif
ifneq ($(BIN_PATH),.)
	@$(RM) -r $(BIN_PATH)
	@$(RM) -r $(BINDIRS)
endif

# Function used to check variables, Use on the command line: make print-VARNAME
print-%: ; @echo $*=$($*)

# Function used to debug Makefile or test feautures
dbgMake:
	@echo -e "TARGET: $@ Do nothing!\n"
	@echo -e $(notdir $@) "\n"
	@echo -e $(dir $@) "\n"
	@echo -e "\$$(MAKECMDGOALS): $(MAKECMDGOALS)\n"
	@echo -e "\$$(MAKEFILE_LIST): $(MAKEFILE_LIST)\n"
	@echo -e "\$$(.DEFAULT_GOAL): $(.DEFAULT_GOAL)\n"
	@echo -e "\$$(.LIBPATTERNS): $(.LIBPATTERNS)\n"
	@echo -e "\$$(.VARIABLES): $(.VARIABLES)\n"

# Show variables (for debug use only.)
show:
	@echo 'BIN_NAME    :' $(BIN_NAME)
	@echo 'BIN_PATH    :' $(BIN_PATH)
	@echo 'BUILD_PATH  :' $(BUILD_PATH)
	@echo 'INCLUDES    :' $(INCLUDES)
	@echo 'LIBPATHS    :' $(LIBPATHS)
	@echo 'LIBRARIES   :' $(LIBRARIES)
	@echo 'SRCDIRS     :' $(SRCDIRS)
	@echo 'HEADERS     :' $(HEADERS)
	@echo 'SOURCES     :' $(SOURCES)
	@echo 'SRC_CXX     :' $(SRC_CXX)
	@echo 'OBJECTS     :' $(OBJECTS)
	@echo 'DEPENDS     :' $(DEPENDS)
	@echo 'DEPEND      :' $(DEPEND)
	@echo 'DEPEND.d    :' $(DEPEND.d)
	@echo 'COMPILE.c   :' $(COMPILE.c)
	@echo 'COMPILE.cxx :' $(COMPILE.cxx)
	@echo 'LINK.c      :' $(LINK.c)
	@echo 'LINK.cxx    :' $(LINK.cxx)
	
# Show help.
help:
	@echo 'Generic Makefile for C/C++ Programs (GnuMakefile) version '$(MK_VERSION)
	@echo 'Copyright (C)2015 Kevin Oscar <zrzxlfe@gmail.com>'
	@echo
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  release   :(=make) compile and link for release.'
	@echo '  debug     :compile and link for debug.'
	@echo '  all       :compile and link.'
	@echo '  objs      :compile only (no linking).'
	@echo '  deps      :generate dependency files (do nothing).'
	@echo '  clean     :clean objects and dependencies.'
	@echo '  distclean :clean objects, dependencies and executable etc.'
	@echo '  sharedlib :compile and generate shared library (*.so).'
	@echo '  staticlib :compile and generate static library (*.a).'
	@echo '  NODEPENDS :make without generating dependencies.'
	@echo '  install   :install executable program.'
	@echo '  uninstall :uninstall executable program.'
	@echo '  check     :check executable program(do nothing).'
	@echo '  test      :test executable program(do nothing).'
	@echo '  etags     :create etags for Emacs editor.'
	@echo '  ctags     :create ctags for VI editor.'
	@echo '  print-Var :print a specific variable (for debug use only).'
	@echo '  show      :show variables (for debug use only).'
	@echo '  help      :print this message.'
	@echo
	@echo 'Report bugs to <zko221986 AT hotmail DOT com>.'

.PHONY: FORCE
FORCE:

# Include dependency files, if they exist.
ifndef NODEPENDS
 ifneq ($(DEPENDS),)
  -include $(DEPENDS)
 endif
endif
#==============================================================================
# 固定段 END
## End of the Makefile ###  Suggestions are welcome  ### All rights reserved ##
###############################################################################

###############################################################################
# Author       Date        Version    Abstact
#------------------------------------------------------------------------------
# Kevin Zhou   2015-01-27  v0.1       初始文件创建（满足基本编译需求，支持临时编译目录）
# Kevin Zhou   2016-04-21  v0.2       格式调整对齐，错误修正，完善注释等
# Kevin Zhou   2017-09-12  v0.3       修正include生成头文件依赖出错无法clean
# Kevin Zhou   2018-02-19  v0.4       修正当BUILD_PATH非.时无法跟踪头文件变化
# Kevin Zhou   2018-05-20  v0.5       增加链接可执行程序时的MAP文件生成
# Kevin Zhou   2018-07-15  v0.6       优化头文件包含时的路径问题
# Kevin Zhou   2018-10-19  v0.7       增加编译动态或静态库，并支持同时链接动态库和静态库
# Kevin Zhou   2018-11-22  v0.8       增加嵌套调用子目录下的Makefile
###############################################################################
# 其它引用参考：
# 1.Linux下Makefile生成*.d依赖文件及gcc -M -MF -MP -MG等相关选项说明
# http://blog.csdn.net/qq1452008/article/details/50855810
# 2.make&&gcc/g++ 生成 map file
# https://blog.csdn.net/dj0379/article/details/17011237
# 3.解决C文件包含的头文件修改了，但C文件不重新编译的问题
# https://blog.csdn.net/szullc/article/details/85038875
# 4.Linux下Makefile中动态链接库和静态链接库的生成与调用
# http://blog.csdn.net/u011964923/article/details/73297443
# https://blog.csdn.net/andylauren/article/details/70146701
# https://www.cnblogs.com/jiqingwu/p/linux_dynamic_lib_create.html
# 5.gcc编译选项fpic/fPIC, fpie/fPIE的说明
# https://blog.csdn.net/baidu_31504167/article/details/99825999
# 6.关于LIBRARY_PATH和LD_LIBRARY_PATH环境变量
# http://blog.csdn.net/yasi_xi/article/details/8196011
# http://blog.csdn.net/wishfly/article/details/52174901
# 7.GCC中同时链接动态库和静态库(https://www.cnblogs.com/lidabo/p/6206504.html)
# 8.折腾gcc/g++链接时.o文件及库的顺序问题
# https://www.cnblogs.com/little-ant/p/3398885.html
# 9.pkg-config详解(http://blog.csdn.net/newchenxf/article/details/51750239)
# 10.多文件目录下Makefile文件嵌套调用递归执行
# https://www.cnblogs.com/Shirlies/p/4282182.html
# 11.makefile专题：预定义变量的使用
# https://blog.csdn.net/jacob__lei/article/details/79274145
###############################################################################
