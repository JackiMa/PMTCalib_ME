#
# PMTCalib makefile
# author : Leonidas N. Kalousis
# e-mail : leonidas.kalousis@gmail.com
#

dict = PMTCalibDict
lib = lib/libPMTCalib.so
rootmap = $(lib:.so=.rootmap)

srcs = $(wildcard src/*.cc)
head = $(wildcard src/*.h)
objs = $(srcs:.cc=.o)
GSL = /usr/include/gsl
ROOTLIBS = -L/opt/root/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -Wl,-rpath,/opt/root/lib -lpthread -lm -ldl
# ROOTLIBS = -L/opt/root/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -Wl,-rpath,/opt/root/lib -stdlib=libc++ -lpthread -lm -ldl
PMTCALIB = /root/code

cxx = g++
cxxflags = -g -W -O -Wall -Wno-deprecated -Werror -fPIC -std=c++17

incflags = -I.
incflags += -I$(ROOTSYS)/include/ -I/$(PMTCALIB)/src/  -I/usr/include -I${GSL}

so = g++
soflags = -g -shared -fPIC
libs = $(ROOTLIBS) -lMinuit -lMinuit2 -lGeom -lXMLIO -lfftw3 -L/$(GSL)/lib -lgsl -lgslcblas 

all	: start touch_dftmethod $(dict).cc $(objs) $(lib) end

# 添加touch_dftmethod，确保每次编译时DFTmethod.cc都会被重新编译
touch_dftmethod:
	@touch src/DFTmethod.cc
	@echo ' * Touching DFTmethod.cc to force recompilation'
	@echo ''

start	: 
	@echo ''		
	@echo ' * PMTCalib make ... '
	@echo ''
	@rm -f ./#* ./*~ ./*.*~	
	@rm -f ./src/#* ./src/*~ ./src/*.*~
	@rm -f ./mac/#* ./mac/*~ ./mac/*.*~
	@mkdir -p lib

$(dict).cc : 
	@rootcling -f $(dict).cc -s $(lib) -rml $(lib) -rmf $(rootmap) $(incflags) -c $(head) LinkDef.h 
	@echo ' * Building ( dic ) :' $@
	@echo ''

%.o	: %.cc	
	@$(cxx) $(cxxflags) $(incflags) -c -o $@ $<
	@echo ' * Building ( obj ) :' $@
	@echo ''

$(lib) 	: $(objs) $(dict).o
	@$(so) $(soflags) $(libs) -o $@ $(objs) $(dict).o
	@echo ' * Building ( lib ) :' $@
	@echo ''

end	:
	@echo ' * PMTCalib done !'
	@echo ''

clean	:	
	@echo ''	
	@echo ' * PMTCalib clean ...'
	@echo ''
	@rm -f ./#* ./*~ ./*.*~	
	@rm -f ./src/#* ./src/*~ ./src/*.*~
	@rm -f ./mac/#* ./mac/*~ ./mac/*.*~
	@rm -f $(dict)*.cc
	@rm -f $(dict)*.o
	@rm -f ./src/*.o
	@rm -f ./$(lib)
	@rm -f ./$(lib:.so=_rdict.pcm)
	@rm -f ./$(lib:.so=.rootmap)
	@rm -f R6233/*.o
	@rm -f R6233/*-exec

fresh 	: clean all
