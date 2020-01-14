/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthesizerJdgodiAudioProcessorEditor::SynthesizerJdgodiAudioProcessorEditor (SynthesizerJdgodiAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.1f);
    //attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    //linking parameter with processor side
    sliderTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"attack",attackSlider);
}

SynthesizerJdgodiAudioProcessorEditor::~SynthesizerJdgodiAudioProcessorEditor()
{
}

//==============================================================================
void SynthesizerJdgodiAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void SynthesizerJdgodiAudioProcessorEditor::resized()
{
    attackSlider.setBounds(10, 10, 40, 100);
}
void SynthesizerJdgodiAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &attackSlider)
    {
        processor.attackTime = attackSlider.getValue();
    }
    
}
