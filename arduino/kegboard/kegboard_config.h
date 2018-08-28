//
// Feature configuration
//

// You may enable/disable kegboard features here as desired. The deafult are
// safe.

// Check for & report 1-wire temperature sensors?
#define KB_ENABLE_ONEWIRE_THERMO   1

// Check for & report 1-wire devices on the ID bus?
#define KB_ENABLE_ONEWIRE_PRESENCE 0

// Enable a selftest pulse?
#define KB_ENABLE_SELFTEST  1

// Enable buzzer?
#define KB_ENABLE_BUZZER    1

// Enable PARALLAX RFID?
#define KB_ENABLE_PARALLAX_RFID 0
#define KB_ENABLE_PARALLAX_RFID_LEGACY_TAGS 0

// Enable ID-12 RFID?
#define KB_ENABLE_ID12_RFID 0

// Enable MFRC522 SPI RFID
#define KB_ENABLE_MFRC522_RFID 1

// Enable Wiegand RFID reader?
// Note: Must set KB_ENABLE_ID12_RFID to 0 if enabling this.
#define KB_ENABLE_WIEGAND_RFID 0

// Enable software debounce? EXPERIMENTAL. Enabling this feature may negatively
// affect pour accuracy.  In particular, a delay is added to each flow meter
// ISR, disabling all other interrupts during this time.
#define KB_ENABLE_SOFT_DEBOUNCE 0

// Approximate minimum pulse width required for incoming external interrupts.
#define KB_SOFT_DEBOUNCE_MICROS 1200

// Enable chip LED?
#define KB_ENABLE_CHIP_LED 0

#if BOARD_KBPM
#undef KB_ENABLE_BUZZER
#undef KB_ENABLE_ID12_RFID
#undef KB_ENABLE_CHIP_LED
#undef KB_ENABLE_SELFTEST
#define KB_ENABLE_BUZZER 1
#define KB_ENABLE_ID12_RFID 0
#define KB_ENABLE_CHIP_LED 1
#define KB_ENABLE_SELFTEST 1
#endif

//
// Pin configuration - KEGBOARD VERSION
//

// You may change values in this section if you know what you are doing --
// though you ordinarily shouldn't need to change these.
//
//  Digital pin allocation:
//    2 - flowmeter 0 pulse (input)
//    3 - flowmeter 1 pulse (input)
//    4 - flow 0 LED (output)
//    5 - flow 1 LED (output)
//    6 - rfid (input from ID-12)
//    7 - thermo onewire bus (1-wire, input/output)
//    8 - presence onewire bus (1-wire, input/output)
//    9 - gpio pin C
//   10 - rfid reset
//   11 - buzzer (output)
//   12 - test pulse train (output)
//   13 - alarm (output)
//  Analog pin allocation:
//   A0 - relay 0 control (output)
//   A1 - relay 1 control (output)
//   A2 - relay 2 control (output)
//   A3 - relay 3 control (output)
//   A4 - gpio pin A
//   A5 - gpio pin B
//

//
// Pin configuration - KEGBOARD WITH MFRC522 RFID ENABLED
//

// On Arduino Uno, some of the pins are used for the SPI Interface
// so they cannot be used for other functions. Arduino Mega SPI pins
// do not conflict
//
//  Digital pin allocation:
//    2 - flowmeter 0 pulse (input)
//    3 - flowmeter 1 pulse (input)
//    4 - flow 0 LED (output)
//    5 - flow 1 LED (output)
//    6 - rfid (input from ID-12)
//    7 - thermo onewire bus (1-wire, input/output)
//    8 - presence onewire bus (1-wire, input/output)
//    9 - mfrc522 SS/SDA pin
//   10 - rfid reset
//   11 - Arduino Uno SPI MOSI
//   12 - Arduino Uno SPI MISO
//   13 - Arduino Uno SPI SCK
//  Analog pin allocation:
//   A0 - relay 0 control (output)
//   A1 - relay 1 control (output)
//   A2 - relay 2 control (output)
//   A3 - relay 3 control (output)
//   A4 - gpio pin A
//   A5 - gpio pin B
//

#define KB_PIN_METER_A            2
//Parallax RFID needs two IO pins, using flow meter B's by default
#if KB_ENABLE_PARALLAX_RFID
#define KB_PIN_SERIAL_RFID_TX     3
#else
#define KB_PIN_METER_B            3
#endif
#define KB_PIN_LED_FLOW_A         4
#define KB_PIN_LED_FLOW_B         5
#define KB_PIN_SERIAL_RFID_RX     6
#define KB_PIN_ONEWIRE_THERMO     7
#define KB_PIN_ONEWIRE_PRESENCE   8

#if KB_ENABLE_MFRC522_RFID
#define KB_PIN_MFRC522_SS         9
#define KB_PIN_LED_CHIP           0
#else
#define KB_PIN_LED_CHIP           9
#endif

#define KB_PIN_RFID_RESET         10

#if KB_ENABLE_MFRC522_RFID && !( defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) ) 
#define KB_PIN_BUZZER             0
#define KB_PIN_TEST_PULSE         0
#define KB_PIN_ALARM              0
#else
#define KB_PIN_BUZZER             11
#define KB_PIN_TEST_PULSE         12
#define KB_PIN_ALARM              13
#endif

#define KB_PIN_RELAY_A            A0
#define KB_PIN_RELAY_B            A1
#define KB_PIN_RELAY_C            A2
#define KB_PIN_RELAY_D            A3
#define KB_PIN_GPIO_A             A4
#define KB_PIN_GPIO_B             A5


#define KB_PIN_MAGSTRIPE_CLOCK    3
#define KB_PIN_MAGSTRIPE_DATA     A4
#define KB_PIN_MAGSTRIPE_CARD_PRESENT A5

#define KB_PIN_WIEGAND_RFID_DATA0 A4
#define KB_PIN_WIEGAND_RFID_DATA1 A5

// Atmega1280 (aka Arduino mega) section
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define KB_NUM_METERS             6
#define KB_PIN_METER_C            21
#define KB_PIN_METER_D            20
#define KB_PIN_METER_E            19
#define KB_PIN_METER_F            18
#else
#define KB_NUM_METERS             2
#endif // defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

//
// Device configuration defaults
//

#define KB_DEFAULT_BOARDNAME          "kegboard"
#define KB_DEFAULT_BOARDNAME_LEN      8  // must match #chars above
#define KB_DEFAULT_BAUD_RATE          115200

// Size in entries of the onewire presence bus cache.  This many IDs can be
// concurrently tracked on the bus.
#define ONEWIRE_CACHE_SIZE 8

// Number of full onewire bus searches to complete before considering a
// non-responding onewire id missing.  This is used to dampen against glitches
// where a device might be absent from a search.
#define ONEWIRE_CACHE_MAX_MISSING_SEARCHES 4

//
// Error checking
//

#if (KB_ENABLE_ID12_RFID + KB_ENABLE_WIEGAND_RFID + KB_ENABLE_PARALLAX_RFID + KB_ENABLE_MFRC522_RFID) > 1
// TODO(mikey): work around pin change interrupt sharing issues.
#error "ID12 RFID, MFRC522 RFID, and WIEGAND RFID cannot be used together."
#error "Please disable all but one of them in kegboard_config.h"
#endif
