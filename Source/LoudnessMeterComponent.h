#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>

class LoudnessMeterComponent : public Component
{
public:
  LoudnessMeterComponent(PlasmaAudioProcessor& audioProcessor)
    : audioProcessor(audioProcessor)
  {
  }

  ~LoudnessMeterComponent() override {}

  void paint(Graphics& g) override
  {
    auto bounds = getLocalBounds().toFloat();
    g.setColour(Colours::red);
    g.fillAll();
  }

  void setCornerRadius(float cornerRadius)
  {
    this->cornerRadius = cornerRadius;
  }

  void resized() override {}

private:
  PlasmaAudioProcessor& audioProcessor;
  float cornerRadius = 5.0f;
};