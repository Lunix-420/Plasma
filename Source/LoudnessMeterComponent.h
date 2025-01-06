#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>

class LoudnessMeterComponent
  : public Component
  , public Timer
{
public:
  LoudnessMeterComponent(PlasmaAudioProcessor& audioProcessor)
    : audioProcessor(audioProcessor)
  {
    startTimerHz(60);
  }

  ~LoudnessMeterComponent() override {}

  void timerCallback() override
  {
    rmsLevelLeftIn = audioProcessor.rmsLevelLeftIn;
    rmsLevelRightIn = audioProcessor.rmsLevelRightIn;
    repaint();
  }

  void paint(Graphics& g) override
  {
    const auto bounds = getLocalBounds().toFloat();
    const auto widht = bounds.getWidth();
    const auto height = bounds.getHeight();
    // g.setColour(backgroundColor);
    // g.fillRoundedRectangle(bounds, cornerRadius);

    const auto inBounds =
      bounds.withTrimmedRight(widht / 2).reduced(height / 24);
    // g.setColour(Colours::red);
    // g.fillRoundedRectangle(inBounds, cornerRadius);

    const auto inMeterBounds =
      inBounds.withTrimmedRight(inBounds.getWidth() * 0.60f);
    // g.setColour(accentColor);
    // g.fillRoundedRectangle(inMeterBounds, cornerRadius);

    const float trimFactor = 0.0f;
    const auto inMeterInnerBounds =
      inMeterBounds.reduced(0.3f * inMeterBounds.getWidth())
        .withTrimmedRight(inMeterBounds.getWidth() * trimFactor)
        .withTrimmedLeft(inMeterBounds.getWidth() * trimFactor)
        .toNearestInt();
    g.setColour(fontColor);
    const int meterBorderThickness = int(inMeterInnerBounds.getWidth() * 0.08f);
    g.drawRect(inMeterInnerBounds, meterBorderThickness);
    g.setColour(accentColor);
    g.fillRect(inMeterInnerBounds.reduced(meterBorderThickness * 2));

    // Let's calculate the bar size for the RMS level
    const float minValue = -60.0f;
    const float maxValue = 12.0f;
    const float rawValue = std::clamp(rmsLevelLeftIn, minValue, maxValue);
    const float normalizedValue = (rawValue - minValue) / (maxValue - minValue);
    const float rawHeight = inMeterInnerBounds.getHeight();
    const float barHeight = rawHeight * normalizedValue;
  }

  void setCornerRadius(float cornerRadius)
  {
    this->cornerRadius = cornerRadius;
  }

  void resized() override { auto bounds = getLocalBounds().toFloat(); }

  void setBackgroundColor(Colour c) { backgroundColor = c; }

  void setAccentColor(Colour c) { accentColor = c; }

  void setFontColor(Colour c) { fontColor = c; }

private:
  float rmsLevelLeftIn = 0.0f;
  float rmsLevelRightIn = 0.0f;
  PlasmaAudioProcessor& audioProcessor;
  float cornerRadius = 5.0f;
  Colour backgroundColor = Colours::black;
  Colour accentColor = Colours::green;
  Colour fontColor = Colours::white;
  Rectangle<float> inBounds, outBounds;
};