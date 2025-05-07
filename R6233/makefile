srcs = ana.cc

objs = $(srcs:.cc=.o)

exe = $(srcs:.cc=)-exec

# libs

GSL = /usr/include/gsl

PMTCALIB = /root/code

cxx = g++

cxxflags = -g -W -O -Wall -Wno-deprecated -fPIC -std=c++17

cxxflags += -Wl,-rpath,$(PMTCALIB)/lib -I$(ROOTSYS)/include/ -I/$(GSL)/include/gsl/ -I$(PMTCALIB)/src/ 

ROOTLIBS = -L/opt/root/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -Wl,-rpath,/opt/root/lib -lpthread -lm -ldl
# rootlibs = $(shell root-config --glibs) -lMinuit -lMinuit2 -lfftw3 -lm -L/$(GSL)/ -lgsl -lMinuit2 -lfftw3 -lgslcblas -L$(PMTCALIB)/lib -lPMTCalib
rootlibs =-L$(PMTCALIB)/lib -lPMTCalib $(ROOTLIBS) -lMinuit -lMinuit2 -lGeom -lXMLIO -lfftw3 -L/$(GSL)/lib -lgsl -lgslcblas 

# 主库路径
PMTCALIB_LIB = $(PMTCALIB)/lib/libPMTCalib.so

# targets

all	: start $(exe) end

start	: 
	@echo ''		
	@echo ' * make ...'
	@echo ''
	@rm -f ./#* ./*~ ./*.*~	

$(exe)	: $(objs) $(PMTCALIB_LIB)
	@$(cxx) $(cxxflags) -o $@ $(objs) $(rootlibs)
	@echo ' * building ( exe )  :' $@
	@echo ''


%.o	: %.cc	
	@$(cxx) $(cxxflags) -c -o $@ $<
	@echo ' * building ( objs ) :' $@
	@echo ''

end	:
	@echo ' * make done !'
	@echo ''

clean	:	
	@echo ''	
	@echo ' * make clean ...'
	@echo ''		
	@rm -f ./#* ./*~ ./*.*~ *.o *-exec

fresh	: clean all
