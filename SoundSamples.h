//
//  SoundSamples.h
//
//  Created by Austin Sickels on 11/4/20.
//

#ifndef SoundSamples_h
#define SoundSamples_h

#include <string>
#include "iostream"
#include <cmath>


using namespace std;

class SoundSamples {
private:
  float * samples;
  int length;
  float sampleRate;

public:
  SoundSamples() { // Default Constructor
    length = 0;
    sampleRate = 8000;
  }

  SoundSamples(float * givenSamples, int givenLength, float givenSampleRate);

  SoundSamples(int givenLength, float givenSampleRate);

  float GetSampleRate();

  SoundSamples(const SoundSamples& origSound);

  SoundSamples& operator=(const SoundSamples& soundToCopy);

  SoundSamples operator+(SoundSamples& rhs);

  int GetLength();

  float operator[](int i);

  void reverb2(float delay, float attenuation);

  void adsr(float atime, float alevel, float dtime, float slevel, float rtime);
};

#endif
