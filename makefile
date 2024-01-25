ofiles = main.o RandomGenerator.o FitnessFunction.o Chromosome.o GA.o
gpp_o = g++ -c -g -std=c++98 

main: $(ofiles)
	g++ -std=c++98 $(ofiles) -o main

main.o: main.cpp RandomGenerator.h FitnessFunction.h Chromosome.h GA.h
	$(gpp_o) main.cpp

RandomGenerator.o: RandomGenerator.cpp RandomGenerator.h
	$(gpp_o) RandomGenerator.cpp

FitnessFunction.o: FitnessFunction.cpp FitnessFunction.h Chromosome.h
	$(gpp_o) FitnessFunction.cpp

Chromosome.o: Chromosome.cpp Chromosome.h FitnessFunction.h RandomGenerator.h
	$(gpp_o) Chromosome.cpp

GA.o: GA.cpp GA.h Chromosome.h RandomGenerator.h FitnessFunction.h
	$(gpp_o) GA.cpp
	
run: main
	./main

clean:
	rm *.o main