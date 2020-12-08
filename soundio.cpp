//
//  soundio.cpp
//
//  Created by Austin Sickels on 11/4/20.
//

#include "SoundSamples.h"
#include <iostream>
#include <fstream>
#include <string>
#include "wave.h"
#include "soundio.h"

// Method to output a sound to a file, takes a sound pointer and a file name
void OutputSound(SoundSamples *samplesToOut, string filename) {
  ofstream fileOut;
  fileOut.open(filename, ios::app);
  for (int i = 0; i < samplesToOut->GetLength(); i++) { // For each sample in SoundSample
    fileOut << (*samplesToOut)[i] << endl; // Print float value to file
  }
  fileOut.close();
}
