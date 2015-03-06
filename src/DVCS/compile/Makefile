INCDIR = $(shell root-config --incdir)
LIBS  = $(shell root-config --glibs)
LD = g++

<<<<<<< HEAD
libTDDVCSGen.so:

=======
all:libTDDVCSGen.so
#libTDDVCSGen.so:TDDVCSGen.o TDDVCSGenDict.o
#	$(LD) -shared $(LIBS) $^ -o $@
>>>>>>> 2d029541eae5fdbb7c826b0a0179eb10469b81df
#%Dict.h:%.h
#rootcint -f $@ $^ LinkDef.h
#	rootcint -f -o $@ -c $^ LinkDef.h
%Dict.C:%.h
<<<<<<< HEAD
	rootcint -f $@ -c $^ LinkDef.h
=======
	rootcint  -f $@ -c $^ LinkDef.h
>>>>>>> 2d029541eae5fdbb7c826b0a0179eb10469b81df
lib%.so: %.o %Dict.o
	$(LD) -shared $(LIBS) $^ -o $@

%.o:%.C
	$(CXX) -fPIC -I $(INCDIR) -c $^

%.o:%.cxx
	$(CXX) -I $(INCDIR) -c $^

clean:
	rm *.o *.so *Dict.*
