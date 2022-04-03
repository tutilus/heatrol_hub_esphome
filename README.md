# Heatrol Hub Esphome

Esphome custom device to manage homemade Heating System.

This includes :

- Yaml file to produce the ESP8266 device as a Hub
- A [custom climate](https://esphome.io/components/climate/custom.html) device `heatrol_climate` using the [tutilus/heatrol](https://github.com/tutilus/heatrol) library to manage homemade heating system.
- (optional) `docker-compose.yml` to create a local [esphome](https://esphome.io/index.html) server. 

## Installation

This device can be installed using esphome command line. Let's see [esphome command line](https://esphome.io/guides/getting_started_command_line.html) for more information.

Create a `secrets.yaml` file in the root directory (or using esphome UI) with the following information:

```yaml
wifi_ssid: "<SSID>"
wifi_password: "<PASSWORD>"
ap_generic_password: "<PASSWORD FOR AP SPOT>"
hass_api_password: "'<API PASSWORD>'"
ota_generic_password: "<OTA PASSWORD>"
```

```sh
# To compile heatrolhub.
$ esphome compile heatrolhub.yml

# But compile and transfer can be excute with one commmand
$ esphome run heatrolhub.yml
```

## Settings


## License
This theme is released under the GPL license.

The Cardo and Montserrat fonts are distributed under the terms of the [Open Font License](https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL).