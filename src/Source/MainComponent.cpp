#include "MainComponent.h"

MainComponent::MainComponent()
{
    beepButton.setButtonText ("Beep");
    addAndMakeVisible (beepButton);
    deviceManager.initialise (0, 2, nullptr, true);
    toneSource.setFrequency (440.0f); // A4
    audioSourcePlayer.setSource (&toneSource);
    deviceManager.addAudioCallback (&audioSourcePlayer);
    beepButton.onClick = [this]() {
        juce::Logger::outputDebugString("Beep button was clicked!");
	toneSource.setAmplitude (0.25f);
	juce::Timer::callAfterDelay (500, [&] { toneSource.setAmplitude (0.0f); }); // stop beep after 500ms
    };

    setSize (400, 300);
}

MainComponent::~MainComponent() {}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("Welcome to ONGOMA", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    beepButton.setBounds (getWidth() / 2 - 50, getHeight() / 2 + 40, 100, 30);
}
