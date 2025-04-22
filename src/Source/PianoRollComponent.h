#pragma once

#include <JuceHeader.h>
#include <tracktion_engine/tracktion_engine.h>

class PianoRollComponent : public juce::Component {
       public:
	PianoRollComponent();

	void paint(juce::Graphics &) override;
	void resized() override;
	void mouseDown(const juce::MouseEvent &) override;

       private:
	static constexpr int numRows = 12;     // one octave for now
	static constexpr int numCols = 16;     // 16 steps
	bool noteGrid[numRows][numCols] = {};  // all off initially

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PianoRollComponent)
       public:
	void setEdit(tracktion::engine::Edit *editToUse);
	void createMidiClip();
	void updateMidiClipFromGrid();

       private:
	// tracktion::engine::Edit *edit = nullptr;
	// tracktion::engine::MidiClip *currentMidiClip = nullptr;
	// int startBeat = 0;     // Where the clip should start
	// int beatsPerNote = 1;  // Duration of each piano roll column
	// int noteOffset = 60;   // MIDI note number for the top row (C4 = 60)
};