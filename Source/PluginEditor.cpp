/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p, AudioProcessorValueTreeState &vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    decaySliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delay", decaySlider);
    gainSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "gain", gainSlider);
    balanceSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "balance", balanceSlider);
    
    decaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    decaySlider.setBounds(10, 10, 100, 100);
    decaySlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 25);
    addAndMakeVisible(decaySlider);
    
    gainSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    gainSlider.setBounds(110, 10, 100, 100);
    gainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 25);
    addAndMakeVisible(gainSlider);
    
    balanceSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    balanceSlider.setBounds(220, 10, 100, 100);
    balanceSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 25);
    addAndMakeVisible(balanceSlider);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
