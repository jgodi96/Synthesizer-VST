/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"
#include "SynthSound.h"


//==============================================================================
SynthesizerJdgodiAudioProcessor::SynthesizerJdgodiAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
attackTime(0.1f),
tree(*this,nullptr)
#endif
{
    NormalisableRange<float> attackParam (0.1f,5000.0f);
    
    tree.createAndAddParameter("attack","Attack","Attack",attackParam,0.1f,nullptr,nullptr);
    tree.state = ValueTree("Foo");
    mySynth.clearVoices();
    for (int i=0; i<5; i++)
    {
        mySynth.addVoice(new SynthVoice());
        
    
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}


SynthesizerJdgodiAudioProcessor::~SynthesizerJdgodiAudioProcessor()
{
}

//==============================================================================
const String SynthesizerJdgodiAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthesizerJdgodiAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthesizerJdgodiAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthesizerJdgodiAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthesizerJdgodiAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthesizerJdgodiAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthesizerJdgodiAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthesizerJdgodiAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthesizerJdgodiAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthesizerJdgodiAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SynthesizerJdgodiAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SynthesizerJdgodiAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthesizerJdgodiAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthesizerJdgodiAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
  
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->getParam(tree.getRawParameterValue("attack"));
        }
    }
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SynthesizerJdgodiAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthesizerJdgodiAudioProcessor::createEditor()
{
    return new SynthesizerJdgodiAudioProcessorEditor (*this);
}

//==============================================================================
void SynthesizerJdgodiAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthesizerJdgodiAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthesizerJdgodiAudioProcessor();
}
