INCDIR = $(shell root-config --incdir)
LIBS  = $(shell root-config --glibs)
LD = g++

all:libTDDVCSGen.so
#libTDDVCSGen.so:TDDVCSGen.o TDDVCSGenDict.o
#	$(LD) -shared $(LIBS) $^ -o $@
#%Dict.h:%.h
#rootcint -f $@ $^ LinkDef.h
#	rootcint -f -o $@ -c $^ LinkDef.h
%Dict.C:%.h
	rootcint  -f $@ -c $^ LinkDef.h
lib%.so: %.o %Dict.o
	$(LD) -shared $(LIBS) $^ -o $@

%.o:%.C
	$(CXX) -fPIC -I $(INCDIR) -c $^

%.o:%.cxx
	$(CXX) -I $(INCDIR) -c $^

clean:
	rm *.o *.so *Dict.*
