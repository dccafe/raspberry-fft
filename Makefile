build: FFT.o src/main.cpp
	@ g++ -o bin/exec src/main.cpp lib/FFT.o

FFT.o: lib/fft/FFT.cc
	@ g++ -c -o lib/FFT.o lib/fft/FFT.cc

run: build
	@ cat samples/sample.wav | ./bin/exec

clean:
	@ rm -rf bin/exec lib/FFT.o
