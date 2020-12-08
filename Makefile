all: main

main: TestMain.cpp SoundSamples.cpp soundio.cpp wave.cpp
	g++ TestMain.cpp SoundSamples.cpp soundio.cpp wave.cpp -o main -lm

clean:
	rm main
