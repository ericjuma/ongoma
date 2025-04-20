#pragma once

#include <JuceHeader.h>

class MainComponent : public juce::Component {
       public:
	MainComponent();
	~MainComponent() override;

	void paint(juce::Graphics &) override;
	void resized() override;

       private:
	juce::TextButton beepButton;

	// New audio components for making sound
	juce::AudioDeviceManager deviceManager;
	juce::AudioSourcePlayer audioSourcePlayer;
	juce::ToneGeneratorAudioSource toneSource;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
