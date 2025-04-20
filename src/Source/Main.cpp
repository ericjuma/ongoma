#include <JuceHeader.h>
#include "MainComponent.h"

class OngomaApplication : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override       { return "Ongoma"; }
    const juce::String getApplicationVersion() override    { return "0.1.0"; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise (const juce::String&) override
    {
        mainWindow.reset (new MainWindow ("Ongoma", new MainComponent(), *this));
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override
    {
        quit();
    }

private:
    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name, juce::Component* c, JUCEApplication& app)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                  .findColour (ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons),
              appRef (app)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (c, true);
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            appRef.systemRequestedQuit();
        }

    private:
        JUCEApplication& appRef;
    };

    std::unique_ptr<MainWindow> mainWindow;
};


// 🔥 This is what tells JUCE where your `main()` is.
START_JUCE_APPLICATION (OngomaApplication)
