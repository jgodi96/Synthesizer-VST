/*
  ==============================================================================

    SynthSound.h
    Created: 10 Jan 2020 7:10:48pm
    Author:  Joshua Godinez

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote (int /*midiNoteNumber*/)
    {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
            
};


