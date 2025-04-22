#include "PianoRollComponent.h"
#include <tracktion_engine/tracktion_engine.h>
PianoRollComponent::PianoRollComponent() {
	// Nothing needed here (yet)
}

void PianoRollComponent::paint(juce::Graphics &g) {
	auto bounds = getLocalBounds();
	int cellWidth = bounds.getWidth() / numCols;
	int cellHeight = bounds.getHeight() / numRows;

	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			auto x = col * cellWidth;
			auto y = row * cellHeight;
			g.setColour(noteGrid[row][col]
					? juce::Colours::hotpink
					: juce::Colours::darkgrey);
			g.fillRect(x, y, cellWidth - 1, cellHeight - 1);
		}
	}
}

void PianoRollComponent::resized() {
	// Optional: nothing yet
}

void PianoRollComponent::mouseDown(const juce::MouseEvent &event) {
	int cellWidth = getWidth() / numCols;
	int cellHeight = getHeight() / numRows;

	int col = event.x / cellWidth;
	int row = event.y / cellHeight;

	if (juce::isPositiveAndBelow(row, numRows) &&
	    juce::isPositiveAndBelow(col, numCols)) {
		noteGrid[row][col] = !noteGrid[row][col];  // toggle
		repaint();
	}
}

/*

void PianoRollComponent::setEdit(tracktion::engine::Edit *editToUse) {
	edit = editToUse;
}

void PianoRollComponent::createMidiClip() {
	if (edit == nullptr)
		return;

	auto tracks = tracktion::engine::getAudioTracks(*edit);
	if (tracks.isEmpty())
		return;

	auto *track = tracks[0];
	if (track == nullptr)
		return;

// Create a new MIDI clip
tracktion::engine::EditTimeRange clipRange{
	tracktion::engine::BeatPosition::fromBeats(startBeat),
	tracktion::engine::BeatDuration::fromBeats(numCols *
						   beatsPerNote)
};
currentMidiClip =
    track->insertMIDIClip("Piano Roll Clip", clipRange, nullptr);
if (currentMidiClip)
	updateMidiClipFromGrid();
}

void PianoRollComponent::updateMidiClipFromGrid() {
	if (currentMidiClip == nullptr)
		return;

	// Clear existing MIDI sequence
	auto &sequence = currentMidiClip->getSequence();
	sequence.clear();

	// Convert grid to MIDI notes
	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			if (noteGrid[row][col]) {
				// Convert row to MIDI note (invert row since
				// top row is highest note)
				int noteNumber = noteOffset - row;

				// Calculate beat position and duration
				double beatPos = col * beatsPerNote;
				double duration = beatsPerNote;

				// Create a MIDI note and add it to the sequence
				sequence.addNote(
				    noteNumber, beatPos, duration,
				    127,  // Velocity (max)
				    0,    // MIDI Channel
				    tracktion::engine::MidiList::notesToUse);
			}
		}
	}

	// Make sure the edit knows the MIDI data changed
	currentMidiClip->setChanged();
	currentMidiClip->updateHashCode();
}

*/