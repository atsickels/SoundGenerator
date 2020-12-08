//
//  soundio.h
//
//  Created by Austin Sickels on 11/4/20.
//

#ifndef soundio_h
#define soundio_h

#include "SoundSamples.h"
#include <iostream>
#include <fstream>
#include <string>
#include "wave.h"
#include "soundio.h"

using namespace std;

void OutputSound(SoundSamples *samples, string filename);

#endif
