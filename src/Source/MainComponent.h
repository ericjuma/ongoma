#pragma once

#include <JuceHeader.h>
#include <tracktion_engine/tracktion_engine.h>
#include "PianoRollComponent.h"

class MainComponent : public juce::Component {
       public:
	MainComponent();
	~MainComponent() override;

	void paint(juce::Graphics &) override;
	void resized() override;

       private:
	PianoRollComponent pianoRoll;
	// juce::TextButton beepButton;

	// New audio components for making sound
	// juce::AudioDeviceManager deviceManager;
	// juce::AudioSourcePlayer audioSourcePlayer;
	// juce::ToneGeneratorAudioSource toneSource;

	// tracktion::engine::UIBehaviour uiBehaviour;
	// tracktion::engine::EngineBehaviour engineBehaviour;
	tracktion::engine::Engine engine{ ProjectInfo::projectName };

	tracktion::engine::Edit edit{
		engine, tracktion::engine::Edit::EditRole::forEditing
	};
	// tracktion::engine::UIBehaviour dummyUI;
	// tracktion::engine::EngineBehaviour engineBehaviour;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
