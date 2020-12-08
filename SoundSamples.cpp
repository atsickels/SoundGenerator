//
//  SoundSamples.cpp
//
//  Created by Austin Sickels on 11/4/20.
//

#include <string>
#include "wave.h"
#include "soundio.h"
#include "iostream"
#include <stdexcept>
#include <cmath>

// Constructor for a SoundSample with all user input
SoundSamples::SoundSamples(float * givenSamples, int givenLength, float givenSampleRate) {
  length = givenLength;
  sampleRate = givenSampleRate;
  samples = new float[length];
  for (int i = 0; i < length; i++) {
    samples[i] = givenSamples[i];
  }
}

// Constructor for a SoundSample with a given length and sample rate, initialize to all 0's
SoundSamples::SoundSamples(int givenLength, float givenSampleRate) {
  length = givenLength;
  sampleRate = givenSampleRate;
  samples = new float[length];
  for (int i = 0; i < length; i++) {
    samples[i] = 0; // each float assigned to 0
  }
}

// Getter method for the sample rate
float SoundSamples::GetSampleRate() {
  return sampleRate;
}

// Copy Constructor for SoundSample
SoundSamples::SoundSamples(const SoundSamples& origSound) {
  int length;
  float sampleRate;
  samples = new float[length];
  length = origSound.length; // copy the length
  sampleRate = origSound.sampleRate; // copy the sample rate
  for (int i = 0; i < length; i++) {
    samples[i] = origSound.samples[i]; // copy each sample one by one
  }
}

// Copy Constructor for SoundSample using overloaded = operator
SoundSamples& SoundSamples::operator=(const SoundSamples& origSound) {
  int length;
  float sampleRate;
  samples = new float[length];
  length = origSound.length; // copy the length
  sampleRate = origSound.sampleRate; // copy the sample rate
  for (int i = 0; i < length; i++) {
    samples[i] = origSound.samples[i]; // copy each sample one by one
  }
  return *this;
}

// Overloaded + operator to add two SoundSamples together, appends all float values
// of rhs to the end of the float array of the lhs, adds the length of the two
// SoundSamples for the new length, sample rate remains (and should be equal)
SoundSamples SoundSamples::operator+(SoundSamples& rhs) {
  if (this->sampleRate != rhs.GetSampleRate()) { // if the sample rates dont match throw error
    throw invalid_argument("SampleRateMismatchException");
  }
  int newLength = this->length + rhs.GetLength(); // the new length is both lengths added together
  float newSampleRate = this->sampleRate; // sample rates match so we can just assign
  float *newSamples = new float[newLength]; // declare new array to hold values
  for (int i = 0; i < this->length; i++) { // for the first x samples (lhs) just insert them into the new array
    newSamples[i] = this->samples[i];
  }
  int k = 0; // separate iterator to handle the rhs array
  for (int j = this->length; j < newLength; j++) { // for the second x samples (rhs) append to the last half of the array
    newSamples[j] = rhs.samples[k];
    k++;
  }
  SoundSamples snd(newSamples, newLength, newSampleRate);
  return snd;
}

// Getter for the length of a SoundSample
int SoundSamples::GetLength() {
  return length;
}

// Overloaded [] operator to access the float value at i for a given SoundSample
float SoundSamples::operator[](int i) {
  if (i < length && i > -1) { // If i is valid return the float at i
    return this->samples[i];
  } // otherwise throw exception
  throw out_of_range("IndexOutOfBoundsException");
}

void SoundSamples::reverb2(float delay, float attenuation) {
  if (delay < 0) {
    throw out_of_range("Negative Delay");
  }
  if (attenuation < 0) {
    throw out_of_range("Negative Attenuation");
  }
  int sdelay = (int) (delay) * this->sampleRate; // how many samples we should calculate delay with
  float * newSamples = new float[length];
  for (int i = 0; i < length; i++) { // init the new samples list to the old list
    newSamples[i] = this->samples[i];
  }
  for (int i = 0; i < length; i++) {
    if (i - sdelay >= 0) { // if the delay wont be too far in the past, calculate the delay
      newSamples[i] = (this->samples[i] + newSamples[i-sdelay]*attenuation);
    }
  }
  for (int i = 0; i < length; i++) { // assign the original sample array to the one we calculated
    this->samples[i] = newSamples[i];
  }
  delete[] newSamples; // delete the temp array
}

void SoundSamples::adsr(float atime, float alevel, float dtime, float slevel, float rtime) {
  float duration = length / this->sampleRate;
  float aend = atime; // end of atime
  float dend = atime + dtime; // total end of dtime
  float rstart = duration - rtime; // beginning of rtime
  if ((atime + dtime + rtime) > duration) { // if the sum is longer than the total song, it's invalid
    cout << atime + dtime + rtime << endl;
    throw invalid_argument("Times sum to greater than the duration");
  } else if (dend > rstart) {
    throw invalid_argument("Decay end overlaps release begin");
  } else if (alevel < slevel) {
    throw invalid_argument("Attack level is less than sustain level");
  } else if (alevel <= 0) {
    throw invalid_argument("Attack level is negative");
  } else if (slevel <= 0) {
    throw invalid_argument("Sustain level is negative");
  }

  // To calculate linear growth divide time by sample rate (sample rate is samples/second)
  // then multiply each sample by the step at each second interval
  int j = 0; // keeps track of the true int value throughout the entire set of loops
  for (int i = 0; i < atime * this->sampleRate; i++) { // Attack loop to set the first values to build up to the alevel
    this->samples[i] = (i * ((alevel / atime)/this->sampleRate)) * this->samples[i];
    j++;
  }
  for (int i = 0; i < dtime * this->sampleRate; i++) { // Decay loop to set the values to decay down to the sustain level
    this->samples[j] = (alevel + (i * (((slevel - alevel) / dtime)/this->sampleRate))) * this->samples[j];
    j++;
  }
  for (int i = 0; i < (duration - (rtime+atime+dtime)) * this->sampleRate; i++) { // Sustain loop to set the levels to the correct level
    this->samples[j] = this->samples[j] * slevel;
    j++;
  }
  for (int i = 1; i <= rtime * this->sampleRate; i++) { // Loop to release the sound back down to 0 from sustain
    this->samples[j] = (slevel + (i * (((0 - slevel) / rtime)/this->sampleRate))) * this->samples[j];
    j++;
  }
}
