//
//  wave.h
//
//  Created by Austin Sickels on 11/4/20.
//

#ifndef wave_h
#define wave_h

#include <string>
#include "SoundSamples.h"

using namespace std;

class Wave {
private:
  string name;

protected:
  float frequency;
  float sampleRate;

public:
  SoundSamples * generateSamples(float frequency, float samplerate, float duration);

  virtual float generateFunction(float time)=0; // Virtual method for subclasses to use

  string GetName();

  void SetName(string name);

  float GetFrequency();

  void SetFrequency(float frequency);

  float GetSampleRate();

  void SetSampleRate(float sampleRate);

};

class SineWave : public Wave
{
public:
  SineWave(string givenName);

  float generateFunction(float time);
};

class SquareWave : public Wave
{
public:
  SquareWave(string givenName);

  float generateFunction(float time);

};

class TriangleWave : public Wave
{
public:
  TriangleWave(string givenName);

  float generateFunction(float time);
};

class SawtoothWave : public Wave
{
public:
  SawtoothWave(string givenName);

  float generateFunction(float time);
};

class SilenceWave : public Wave
{
public:
  SilenceWave(string givenName);

  float generateFunction(float time);
};

#endif
