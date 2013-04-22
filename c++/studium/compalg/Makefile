LIBS= compalg1_11.o

CXXFLAGS= -O2 #-g
%:%.o; ${CXX} -o $@ $^

clean:; -rm *.o 
distclean:clean; -rm test?_?? 

test1_01: test1_01.o compalg1_00.o compalg1_01.o                             ${LIBS}
test1_02: test1_02.o compalg1_00.o compalg1_01.o compalg1_02.o               ${LIBS}
test1_03: compalg1_00.o compalg1_01.o compalg1_02.o compalg1_03.o test1_03.o ${LIBS} 
test1_04: test1_04.o compalg1_00.o compalg1_01.o compalg1_04.o               ${LIBS}
test1_06: test1_06.o compalg1_00.o compalg1_06.o                             ${LIBS}
test1_07: test1_07.o compalg1_00.o compalg1_01.o compalg1_02.o compalg1_03.o \
	  compalg1_04.o compalg1_07.o                                        ${LIBS}
test1_08: test1_08.o compalg1_00.o compalg1_01.o compalg1_02.o compalg1_03.o \
	  compalg1_04.o compalg1_07.o compalg1_08.o                          ${LIBS}
test1_09: test1_09.o compalg1_00.o compalg1_01.o compalg1_02.o compalg1_03.o \
	  compalg1_09.o                                                      ${LIBS}
test1_10: test1_10.o compalg1_00.o compalg1_01.o compalg1_02.o compalg1_03.o \
	  compalg1_04.o compalg1_07.o compalg1_08.o compalg1_09.o            \
	  compalg1_10.o compalg1_10_2.o                                      ${LIBS}
test1_11: test1_11.o compalg1_11.o
