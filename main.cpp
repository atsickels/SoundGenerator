//
//  main.cpp
//
//  Created by Austin Sickels on 11/4/20.
//


#include "SoundSamples.h"
#include <iostream>
#include <fstream>
#include <string>
#include "wave.h"
#include "soundio.h"


int main(int argc, const char * argv[]) {
    if (argc != 1) { // If the command line holds more than just ./main we throw an error
      throw invalid_argument("Invalid number of arguments from command line");
    }
    int waveType; // Stores the inputted wave type
    float sample_rate; // Stores the inputted sample rate
    float frequency; // Stores the inputted frequency
    float duration; // Stores the inputted duration
    string filename; // Filename of the file to output to
    std::cout << "Enter wave type; sample rate; frequency; duration; and filename\n";

    cin >> waveType;
    cin >> sample_rate;
    cin >> frequency;
    cin >> duration;
    cin >> filename;

    Wave *w;

    if (waveType == 1) { // Determine what kind of wave the user wants to generate
      w = new SineWave("MySineWave");
    } else if (waveType == 2){
      w = new SquareWave("MySquareWave");
    } else if (waveType == 3){
      w = new TriangleWave("MyTriangleWave");
    } else if (waveType == 4) {
      w = new SawtoothWave("MySawtoothWave");
    } else { // If not 1, 2, 3, or 4, we dont know what kind of wave to output
      throw invalid_argument("InvalidWaveTypeException");
    }
    SoundSamples *s = w->generateSamples(frequency, sample_rate, duration); // SoundSample to create based on parameters
    OutputSound(s, filename); // Output the sound we created to the file we want

    return 0;
}
