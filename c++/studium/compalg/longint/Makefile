CXXFLAGS=-O2
%:%.o; ${CXX} -o $@ $^

clean:; -rm *.o
distclean:clean; -rm test?_??

test1_11: test1_11.o compalg1_11.o 
