cmake_minimum_required(VERSION 3.15)

project(OngomaJUCE VERSION 0.1.0)

# C++20 because Tracktion is not for the weak
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Use position independent code (for Linux shared libs etc.)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# JUCE setup (assumes JUCE is cloned into JUCE/)
set(JUCE_DIR "${CMAKE_SOURCE_DIR}/JUCE")
list(APPEND CMAKE_PREFIX_PATH "${JUCE_DIR}")
add_subdirectory(${JUCE_DIR})

# Tracktion Engine modules
set(TRACKTION_MODULES_DIR "${CMAKE_SOURCE_DIR}/tracktion_engine/modules")

juce_add_module(${TRACKTION_MODULES_DIR}/tracktion_core)
juce_add_module(${TRACKTION_MODULES_DIR}/tracktion_graph)
juce_add_module(${TRACKTION_MODULES_DIR}/tracktion_engine)

# GUI app
juce_add_gui_app(OngomaJUCE
    VERSION "0.1.0"
    COMPANY_NAME "Omena"
    BUNDLE_ID com.omena.ongoma
    PRODUCT_NAME "Ongoma"
)

# JUCE generates this
juce_generate_juce_header(OngomaJUCE)

# App source files
target_sources(OngomaJUCE PRIVATE
    Source/Main.cpp
    Source/MainComponent.cpp
    Source/MainComponent.h
    Source/PianoRollComponent.h
    Source/PianoRollComponent.cpp
)

# JUCE libs
target_link_libraries(OngomaJUCE PRIVATE
    juce::juce_gui_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_data_structures
    juce::juce_dsp
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_extra
)

# Tracktion libs
target_link_libraries(OngomaJUCE PRIVATE
    tracktion_core
    tracktion_graph
    tracktion_engine
)

# Include path for JuceHeader.h
target_include_directories(OngomaJUCE PRIVATE
    ${CMAKE_BINARY_DIR}/OngomaJUCE_artefacts/JuceLibraryCode
)

# Disable optional Tracktion features
target_compile_definitions(OngomaJUCE PRIVATE
    TRACKTION_ENABLE_REWIRE=0
    TRACKTION_ENABLE_ARA=0
)

# OS-specific adjustments
if(APPLE)
    # macOS-specific stuff
    set_target_properties(OngomaJUCE PROPERTIES
        MACOSX_BUNDLE TRUE
    )
elseif(UNIX AND NOT APPLE)
    # Linux-specific: link against pthread and dl if needed
    target_link_libraries(OngomaJUCE PRIVATE
        dl
        pthread
    )
endif()
