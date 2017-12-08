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
    decayAttachment = new SliderAttachment(valueTreeState, "decay", decaySlider);
    dryWetAttachment = new SliderAttachment(valueTreeState, "dry/wet", dryWetSlider);
    
    float marginX = 10;
    float marginY = 10;
    float x = marginX;
    float y = marginY + decaySlider.getTextBoxHeight();
    float w = 100;
    float h = 100;
    
    decaySlider.setBounds(x, y, w, h);
    decaySlider.setSliderStyle(Slider::RotaryVerticalDrag);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, w * 0.75, decaySlider.getTextBoxHeight());
    decayLabel.setText("decay", NotificationType::sendNotificationAsync);
    decayLabel.setJustificationType(Justification::centred);
    decayLabel.attachToComponent(&decaySlider, false);
    addAndMakeVisible(decaySlider);
    
    x += w + marginX;
    
    dryWetSlider.setBounds(x, y, w, h);
    dryWetSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    dryWetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, w * 0.75, dryWetSlider.getTextBoxHeight());
    dryWetLabel.setText("dry/wet", NotificationType::sendNotificationAsync);
    dryWetLabel.setJustificationType(Justification::centred);
    dryWetLabel.attachToComponent(&dryWetSlider, false);
    addAndMakeVisible(dryWetSlider);
    
    int numX = 2;
    int numY = 1;
    setSize (numX * w + (numX + 1) * marginX, numY * h + (numY + 1) * marginY + marginY + decaySlider.getTextBoxHeight());
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
