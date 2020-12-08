//
//  TestMain.cpp
//
//  Created by Austin Sickels on 11/14/20.
//


#include "SoundSamples.h"
#include <iostream>
#include <fstream>
#include <string>
#include "wave.h"
#include "soundio.h"
#include <vector>


int main(int argc, const char * argv[]) {
    if (argc != 1) { // If the command line holds more than just ./main we throw an error
      throw invalid_argument("Invalid number of arguments from command line");
    }
    int count = 0;
    int waveType; // Stores the inputted wave type
    float sample_rate; // Stores the inputted sample rate
    float frequency; // Stores the inputted frequency
    float TONE_DURATION = 1; // Constant for tone Duration
    float SILENCE_DURATION = .25; // Constant for silence Duration
    int SAMPLE_RATE = 8000;
    string filename; // Filename of the file to output to
    float delay; // Delay value for reverb2
    float attenuation; // Attenuation value for reverb2
    float atime; // Delta time for attack in adsr
    float alevel; // Level to reach at end of atime
    float dtime; // Delta time for decay between atime and dtime
    float slevel; // Level to reach at end of dtime
    float rtime; // Delta time for release
    vector<int> notes; // Vector to hold the notes
    int input; // Input for key
    std::cout << "Enter wave type; delay; attenuation; atime; alevel; dtime; slevel; rtime; and filename\n";
    cin >> waveType;
    cin >> delay;
    cin >> attenuation;
    cin >> atime;
    cin >> alevel;
    cin >> dtime;
    cin >> slevel;
    cin >> rtime;
    cin >> filename;
    cout << "Enter notes terminated by -1 to exit:" << endl;
    cin >> input;
    while (input != -1) {
      if (input >= 0 && input <= 88) { // between 0 and 88 are the standard keys of the piano
        notes.push_back(input); // add key to the vector
        cin >> input; // take next input
      } else { // key wasnt a valid piano key, end
        cout << "Key input invalid" << endl;
        return 1;
      }
    }
    if (notes.size() == 0) { // If the vector is empty we don't have any notes to play, end
      cout << "No notes entered" << endl;
      return 1;
    }

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
    SoundSamples *silence = new SoundSamples(SILENCE_DURATION * SAMPLE_RATE, SAMPLE_RATE); // .25 seconds of silence between notes
    for (int i = 0; i < notes.size(); i++) { // for every note in vector
      int key = notes[i]; // the int value we got from the user input representing a key
      float frequency = pow(1.059463, key - 49) * 440; //calculate the frequency given by the key
      SoundSamples *s = w->generateSamples(frequency, SAMPLE_RATE, TONE_DURATION); // SoundSample to create based default constructor
      s->adsr(atime, alevel, dtime, slevel, rtime); // Call adsr with the given parameters
      s->reverb2(delay, attenuation); // Call reverb2 with given parameters
      OutputSound(s, filename); // Output the sound we created to the file we want
      OutputSound(silence, filename); // Silence follows a note
    }
    return 0;
}
