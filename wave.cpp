//
//  wave.cpp
//
//  Created by Austin Sickels on 11/4/20.
//

#include <string>
#include "wave.h"
#include "soundio.h"
#include "iostream"
#include <cmath>


// Method to create the float values for an entire array given the frequency sample rate and duration
SoundSamples * Wave::generateSamples(float frequency, float samplerate, float duration) {
  int length = samplerate*duration;
  this->sampleRate = samplerate;
  this->frequency = frequency;
  float *samples = new float[length];
  for (int i = 0; i < length; i++) {
    samples[i] = generateFunction(i); // generate each sample using a super class method to determine which math to use
  }
  SoundSamples * snd = new SoundSamples(samples, length, sampleRate);
  return snd;
}

// Getter for the name attribute
string Wave::GetName() {
  return this->name;
}

// Setter for the name attribute
void Wave::SetName(string name) {
  this->name = name;
}

// Getter for the frequency attribute
float Wave::GetFrequency() {
  return this->frequency;
}

// Setter for the frequency attribute
float Wave::GetSampleRate() {
  return this->sampleRate;
}

// Constructor for a sine wave
SineWave::SineWave(string givenName) {
  SetName(givenName);
}

// Math to create a sample at a given point in time for a sine wave
float SineWave::generateFunction(float time) {
  float result = sin(time*(2*M_PI)/(this->GetSampleRate()/this->GetFrequency()));
  return result;
}

// Constructor for a square wave
SquareWave::SquareWave(string givenName) {
  SetName(givenName);
}

// Math to create a sample at a given point in time for a square wave
float SquareWave::generateFunction(float time) {
  float result = sin(time*(2*M_PI)/(this->GetSampleRate()/this->GetFrequency()));
      if (result < 0) {
        result = -1;
      } else {
        result = 1;
      }
  return result;
}

//Constructor for a triangle wave
TriangleWave::TriangleWave(string givenName) {
  SetName(givenName);
}

// Math to create a sample at a given point in time for a triangle wave
float TriangleWave::generateFunction(float time) {
  float result = fabs(2*(((time*this->GetFrequency())/this->GetSampleRate()) - floor(.5+(time*this->GetFrequency())/this->GetSampleRate())));
  result = (result - 0.5) * 2;
  return result;
}

//Constructor for a sawtooth wave
SawtoothWave::SawtoothWave(string givenName) {
  SetName(givenName);
}

// Math to create a sample at a given point in time for a sawtooth wave
float SawtoothWave::generateFunction(float time) {
  float result = 2*(((time*this->GetFrequency())/this->GetSampleRate())-floor(.5+(time*this->GetFrequency())/this->GetSampleRate()));
  return result;
}

//Constructor for silence
SilenceWave::SilenceWave(string givenName) {
  SetName(givenName);
}

// On silence return 0
float SilenceWave::generateFunction(float time) {
  return 0;
}
