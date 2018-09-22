g++ = g++
main = main.cpp
boostAndImp = BoostAndImp.cpp
script = script.cpp
omp = -fopenmp
args = NLR.mtx channel-500x100x100-b050.mtx delaunay_n19.mtx 
runMain = main_exe
all: main_exe boostAndImp_exe script_exe

script_exe:$(script)
	$(g++) $(script) -o $@

main_exe:$(main)
	$(g++)	$(omp)	$(main) -o $@

boostAndImp_exe:$(boostAndImp)
	$(g++)	$(omp)	$(boostAndImp)	-o	$@

clean:
	rm *_exe *.txt

run:$(runMain)
	./$(runMain)	$(args)
