/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "AllPass.h"
#include "Inlet.h"
#include "Outlet.h"
#include "Chain.h"


//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#else
    :
#endif
    parameters(*this, nullptr), dryGain(0.0), wetGain(1.0), directGain(0.5), feedbackGain(-0.5), outGain(1.0 - 0.5 * 0.5),
    preDelay(0.03)
{
    parameters.createAndAddParameter("gain",
                                     "gain", "",
                                     NormalisableRange<float>(0, 1, 0.001),
                                     0.7,
                                     nullptr,
                                     nullptr);
    parameters.createAndAddParameter("delay",
                                     "delay", "",
                                     NormalisableRange<float>(0.01, 1, 0.0001),
                                     0.5,
                                     nullptr,
                                     nullptr);
    parameters.createAndAddParameter("balance",
                                     "balance", "",
                                     NormalisableRange<float>(0.00, 1, 0.0001),
                                     0.7,
                                     nullptr,
                                     nullptr);
    
    Allpass *allpassA = new Allpass(0.1, 0.7);
    // Allpass *allpassB = new Allpass(0.3, 0.7);
    // Allpass *allpassC = new Allpass(0.09, 0.2);
    // Allpass *allpassD = new Allpass(0.027, 0.2);
    // Chain allpasses = *allpassA > *allpassB > *allpassC > *allpassD;
    
    inlet >> inSum >> *allpassA >> outGain >> outSum >> outlet;
    inlet >> directGain >> outSum;
    *allpassA >> feedbackGain >> inSum;
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

/*
float lastAllpassed = 0;
Allpass *allpassA = new Allpass(0.1, 0.7);
Allpass *allpassB = new Allpass(0.03, 0.6);
Allpass *allpassC = new Allpass(0.01, 0.5);
// Allpass *allpassD = new Allpass(0.003, 0.4);
*/
 
float NewProjectAudioProcessor::process(float t, float x)
{
    /*
    float g = 0.2;
    float inSum = x + lastAllpassed;
    
    float allpassed = inSum;
    allpassed = allpassA->alone(t, allpassed);
    // allpassed = allpassD->alone(t, allpassed);
    
    float outSum = x * (-g) + allpassed * (1 - g * g);
    lastAllpassed = allpassed * g;
    return outSum;
     */
    return testVerb.process(x);
}

void NewProjectAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float* channelData = buffer.getWritePointer (0);
    
    float dryWetRatio = *parameters.getRawParameterValue("balance");
    wetGain.setGain(sqrt(dryWetRatio));
    dryGain.setGain(sqrt(1.0 - dryWetRatio));
    
    for (int i = 0; i < buffer.getNumSamples(); ++ i) {
        // float x = outlet.run(0, channelData[i]);
        float x = process(0, channelData[i]);
        channelData[i] = x;
    }
    
    for (int channel = 1; channel < totalNumInputChannels; ++channel)
    {
        float *channelData = buffer.getWritePointer (channel);
        float *channelZeroData = buffer.getWritePointer(0);
        
        for (int i = 0; i < buffer.getNumSamples(); ++ i) {
            channelData[i] = channelZeroData[i];
        }
    }
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
