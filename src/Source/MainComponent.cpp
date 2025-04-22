#include "MainComponent.h"

MainComponent::MainComponent()
    : engine("Ongoma",
	     std::make_unique<tracktion::engine::UIBehaviour>(),
	     std::make_unique<tracktion::engine::EngineBehaviour>()) {
	addAndMakeVisible(pianoRoll);
	setSize(400, 300);
	tracktion::engine::Edit::Options options{ engine };
	// options.editID = tracktion::engine::ProjectItemID::createNewID();

	// edit = std::make_unique<tracktion::engine::Edit>(options);

	edit.ensureNumberOfAudioTracks(1);
}

MainComponent::~MainComponent() {}

void MainComponent::paint(juce::Graphics &g) {
	g.fillAll(juce::Colours::black);
	g.setColour(juce::Colours::white);
	g.setFont(20.0f);
	g.drawText("Welcome to ONGOMA", getLocalBounds(),
		   juce::Justification::centred, true);
}

void MainComponent::resized() {
	pianoRoll.setBounds(getLocalBounds().reduced(10));
}