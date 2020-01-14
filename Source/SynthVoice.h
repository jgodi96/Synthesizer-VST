/*
  ==============================================================================

    SynthVoice.h
    Created: 10 Jan 2020 7:10:55pm
    Author:  Joshua Godinez

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

#include "maximilian.h"
using namespace std;
class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound)
    {
        //cast sound a class synth sound. if sucessful return true else return false
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    void getParam (float* attack)
    {
        
    }

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        
    }
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        
        
        if(velocity == 0)
            clearCurrentNote();
    }
    void renderNextBlock (AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
    {
        env1.setAttack(1000);
        env1.setDecay(500);
        env1.setSustain(0.8);
        env1.setRelease(2000);
    
        
        for (int sample = 0; sample <  numSamples; ++sample)
        {
            double theWave = osc1.saw(frequency);
           double theSound = env1.adsr(theWave, env1.trigger)* level;
            double filteredSound = filter1.lores(theSound,100,0.1);
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel,startSample, filteredSound);
            }
            ++startSample;
        }
        
        
    }
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
private:
    double level;
    double frequency;
    
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
    
};
