/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LateReverb.h"


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
    parameters(*this, nullptr)
{
    parameters.createAndAddParameter("decay",
                                     "decay", "",
                                     NormalisableRange<float>(0, 1),
                                     0.7,
                                     nullptr,
                                     nullptr);
    
    parameters.createAndAddParameter("dry/wet",
                                     "dry/wet", "",
                                     NormalisableRange<float>(-0.5, 0.5),
                                     0.0,
                                     nullptr,
                                     nullptr);
    time = 0;
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

void NewProjectAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float decay = *parameters.getRawParameterValue("decay");
    float dryWet = 0.5 + *parameters.getRawParameterValue("dry/wet");
    lateReverb.setDecay(decay);
    float* channelData = buffer.getWritePointer (0);
    
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
        float mix = 0;
        time += 1 / (float)getSampleRate();
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            mix += buffer.getSample(channel, sample);
        }
        
        earlyReflections.process(mix);
        float l = earlyReflections.left;
        float r = earlyReflections.right;
        
        l = lateReverb.processLeft(time, l);
        r = lateReverb.processRight(time, r);
        lateReverb.crossower();
        
        l = sqrt(dryWet) * l + sqrt(1 - dryWet) * mix;
        r = sqrt(dryWet) * r + sqrt(1 - dryWet) * mix;
        
        
        if (l > 1.0) {
            std::cout << "Overflow left!\n";
        }
        
        if (r > 1.0) {
            std::cout << "Overflow right!\n";
        }
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            if (channel % 2 == 0)
                buffer.setSample(channel, sample, l);
            else
                buffer.setSample(channel, sample, r);
        }
    }
    
    // nestedAllPass.setScale(*parameters.getRawParameterValue("delay"));
    // nestedAllPass.setInnerGain(*parameters.getRawParameterValue("gain"));
    // nestedAllPass.setGain(*parameters.getRawParameterValue("balance"));
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
