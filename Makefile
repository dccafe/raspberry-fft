build: lib src/main.cpp lib/FFT.o
	@ g++ -o exec src/main.cpp lib/FFT.o

lib: lib/fft/FFT.cc
	@ g++ -c -o lib/FFT.o lib/fft/FFT.cc

run: build
	@ cat samples/sample.wav | ./exec

clean:
	@ rm -rf exec
