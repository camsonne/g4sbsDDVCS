INCDIR = $(shell root-config --incdir)
LIBS  = $(shell root-config --glibs)
LD = g++

%Dict.h:%.h
#rootcint -f $@ $^ LinkDef.h
	rootcint  $@ -c $^ LinkDef.h
%Dict.C:%.h
	rootcint -f $@ $^ LinkDef.h
lib%.so: %.o %Dict.o
	$(LD) -shared $(LIBS) $^ -o $@

%.o:%.C
	$(CXX) -fPIC -I $(INCDIR) -c $^

%.o:%.cxx
	$(CXX) -I $(INCDIR) -c $^

clean:
	rm *.o *.so
