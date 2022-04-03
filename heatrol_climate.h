#include "esphome.h"
#include "heatrol.h"

class HeatrolClimate : public Component, public Climate {
 public:

  // API to control the heater
  Heatrol heatrol;
  // Pin1 and Pin2 to associate at this component
  uint8_t pin1;
  uint8_t pin2;
  hzOrder_t default_mode;

  HeatrolClimate(uint8_t pin1, uint8_t pin2, hzOrder_t default_mode) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->default_mode = default_mode;
  }

  void setup() override {
    // This will be called by App.setup()
    heatrol.begin(this->pin1, this->pin2, this->default_mode);
  }
  void control(const ClimateCall &call) override {

    if (call.get_mode().has_value()) {
      // User requested mode change
      ClimateMode mode = *call.get_mode();
      // Publish updated state
      this->mode = mode;
      if (mode == climate::CLIMATE_MODE_OFF) {
        heatrol.setOrder(ARRET);
        // Reset preset to NONE (heater is off)
        this->preset = climate::CLIMATE_PRESET_NONE;
      } else {
        heatrol.setOrder(this->default_mode);
      }
      this->publish_state();
    }

    if (call.get_preset().has_value()) {
      // User requested preset change
      ClimatePreset preset = *call.get_preset();
      // Publish updated state
      this->preset = preset;
      // Change the preset only in auto mode
      switch (preset) {
        case climate::CLIMATE_PRESET_NONE:
          heatrol.setOrder(this->default_mode);
          break;
        case climate::CLIMATE_PRESET_AWAY:
          heatrol.setOrder(HORSGEL);
          break;
        case climate::CLIMATE_PRESET_ECO:
          heatrol.setOrder(ECO);
          break;
        case climate::CLIMATE_PRESET_COMFORT:
          heatrol.setOrder(CONFORT);
          break;
        default:
          break;
      }
      this->publish_state();
    }
  }
  ClimateTraits traits() override {
    // The capabilities of the climate device
    auto traits = climate::ClimateTraits();
//    traits.set_supports_current_temperature(true);
    traits.set_supported_modes({
      climate::CLIMATE_MODE_OFF,
      climate::CLIMATE_MODE_AUTO,
      climate::CLIMATE_MODE_HEAT
    });
    traits.set_supported_presets({
      climate::CLIMATE_PRESET_NONE,
      climate::CLIMATE_PRESET_AWAY,
      climate::CLIMATE_PRESET_ECO,
      climate::CLIMATE_PRESET_COMFORT});
    return traits;
  }
};