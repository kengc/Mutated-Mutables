// Copyright 2012 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Settings

#include "braids/settings.h"

#include <cstring>

#include "stmlib/system/storage.h"

// Easter egg disable, murmurhash3 not required.
// #include "stmlib/utils/murmurhash3.h"

namespace braids {

using namespace stmlib;

const SettingsData kInitSettings = {
  MACRO_OSC_SHAPE_CSAW,
  
  RESOLUTION_16_BIT,
  6, // now the LFO speed/env duration, but make the default the same as sample rate
  
  0,  // Trig destination
  false,  // Trig source
  1,  // Trig delay
  false,  // Meta modulation
  
  PITCH_RANGE_EXTERNAL,
  2,
  PITCH_QUANTIZATION_OFF,
  false,
  false,
  false,
  
  2,
  0,
  
  { 0, 0, 0, 0, 0 },
  
  50,
  15401,
  2048,
  "GREETINGS FROM MUTABLE INSTRUMENTS *EDIT ME*",
};

Storage<0x8020000, 4> storage;

void Settings::Init() {
  if (!storage.ParsimoniousLoad(&data_, &version_token_)) {
    Reset();
  }
  CheckPaques();
}

void Settings::Reset() {
  memcpy(&data_, &kInitSettings, sizeof(SettingsData));
}

void Settings::Save() {
  storage.ParsimoniousSave(data_, &version_token_);
  CheckPaques();
}

void Settings::CheckPaques() {
  // Disable ability to invoke Easter egg mode
  // paques_ = !strcmp(data_.marquee_text, "49");
  paques_ = false;
}

const char* const boolean_values[] = { "OFF ", "ON  " };

const char* const algo_values[] = {
    "CSAW",
    "^\x88\x8D_",
    "\x88\x8A\x8C\x8D",
    "SYNC",
    "FOLD",
    "\x8E\x8E\x8E\x8E",
    "\x88\x88x3",
    "\x8C_x3",
    "/\\x3",
    "SIx3",
    "RING",
    "\x88\x89\x88\x89",
    "\x88\x88\x8E\x8E",
    "TOY*",
    "ZLPF",
    "ZPKF",
    "ZBPF",
    "ZHPF",
    "VOSM",
    "VOWL",
    "VFOF",
    "FM  ",
    "FBFM",
    "WTFM",
    "PLUK",
    "BOWD",
    "BLOW",
    "FLUT",
    "BELL",
    "DRUM",
    "KICK",
    "CYMB",
    "SNAR",
    "WTBL",
    "WMAP",
    "WLIN",
    "WTx4",
    "NOIS",
    "TWNQ",
    "CLKN",
    "CLOU",
    "PRTC",
    "QPSK",
    // "NAME" // For your algorithm
};

const char* const bits_values[] = {
    "2BIT",
    "3BIT",
    "4BIT",
    "6BIT",
    "8BIT",
    "12B ",
    "16B " };
    
const char* const rates_values[] = {
    "   0",
    "   1",
    "   2",
    "   3",
    "   4",
    "   5",
    "   6",
    "   7",
    "   8",
    "   9",
    "  10",
    "  11",
    "  12",
    "  13",
    "  14",
    "  15",
    "  16",
    "  17",
    "  18",
    "  19",
    "  20",
    "  21",
    "  22",
    "  23",
    "  24",
    "  25",
    "  26",
    "  27",
    "  28",
    "  29",
    "  30",
    "  31",
    "  32",
    "  33",
    "  34",
    "  35",
    "  36",
    "  37",
    "  38",
    "  39",
    "  40",
    "  41",
    "  42",
    "  43",
    "  44",
    "  45",
    "  46",
    "  47",
    "  48",
    "  49",
    "  50",
    "  51",
    "  52",
    "  53",
    "  54",
    "  55",
    "  56",
    "  57",
    "  58",
    "  59",
    "  60",
    "  61",
    "  62",
    "  63",
    "  64",
    "  65",
    "  66",
    "  67",
    "  68",
    "  69",
    "  70",
    "  71",
    "  72",
    "  73",
    "  74",
    "  75",
    "  76",
    "  77",
    "  78",
    "  79",
    "  80",
    "  81",
    "  82",
    "  83",
    "  84",
    "  85",
    "  86",
    "  87",
    "  88",
    "  89",
    "  90",
    "  91",
    "  92",
    "  93",
    "  94",
    "  95",
    "  96",
    "  97",
    "  98",
    "  99",
    " 100",
    " 101",
    " 102",
    " 103",
    " 104",
    " 105",
    " 106",
    " 107",
    " 108",
    " 109",
    " 110",
    " 111",
    " 112",
    " 113",
    " 114",
    " 115",
    " 116",
    " 117",
    " 118",
    " 119",
    " 120",
    " 121",
    " 122",
    " 123",
    " 124",
    " 125",
    " 126",
    " 127",
};
    
const char* const quantization_values[] = { "OFF ", "QRTR", "SEMI" };

const char* const trig_source_values[] = { "EXT.", "AUTO" };

const char* const pitch_range_values[] = {
    "EXT.",
    "FREE",
    "XTND",
    "440 ",
    "LFO "
};

const char* const octave_values[] = { "-2", "-1", "0", "1", "2" };

const char* const trig_delay_values[] = {
    "NONE",
    "125u",
    "250u",
    "500u",
    "1ms ",
    "2ms ",
    "4ms "
};

const char* const ad_shape_values[] = {
    "TT  ",
    "PIK ",
    "PING",
    "TONG",
    "BONG",
    "LONG",
    "SLOW",
    "WOMP",
    "YIFF",
    "M005",
    "M010",
    "M020",
    "M030",
    "M040",
    "M050",
    "M060",
    "M070",
    "M080",
    "M090",
    "M100",
    "M110",
    "M120",
    "M130",    
    "M140",    
    "M150",    
    "M160",    
    "M170",    
    "M180",    
    "M190",    
    "M200",    
    "M210",    
    "M220",    
    "M230",    
    "M240",    
    "M250",    
    "M255",    
};

const char* const trig_destination_values[] = {
    "SYNC",
    "TIMB",
    "LEVL",
    "T+L ",
    "COLR",
    "T+C ",
    "L+C ",
    "ALL "
};

const char* const brightness_values[] = {
    "\xff   ",
    "\xff\xff  ",
    "\xff\xff\xff\xff",
};

const char* const meta_values[] = { 
    "OFF ", // 0
    "MODL", // 1
    "ATTK",
    "DCAY",
    "AD02",
    "AD05",
    "AD10",
    "AD15",
    "AD20",
    "AD30",
    "AD40",
    "AD50",
    "AD75",
    "A=D ",
    "DA90",
    "DA80",
    "DA70",
    "DA60",
    "DA50",
    "DA25",
    "DA10",
    "LFOX",  // 21 exponentially-curved triangle
    "LFO^",  // 22 linear triangle
    "LFOw",  // 23 wiggly, using ws_sine_fold (a show about nothing?)
    "LFOs",  //  24 sine-ish, using ws_moderate_overdrive
    "LFO\x8C", // 25 square-ish, using ws_violent_overdrive
    "LFOb",    // 26 bowing friction LUT
    "LFO\x8F", // 27 saw
    "LFO\x88", // 28 ramp
};


/* static */
const SettingMetadata Settings::metadata_[] = {
  { 0, MACRO_OSC_SHAPE_LAST - 2, "WAVE", algo_values },
  { 0, RESOLUTION_LAST - 1, "BITS", bits_values },
  // { 0, SAMPLE_RATE_LAST - 1, "RATE", rates_values },
  { 0, 127, "RATE", rates_values },
  { 0, 7, "TDST", trig_destination_values },
  { 0, 1, "TSRC", trig_source_values },
  { 0, 6, "TDLY", trig_delay_values },
  { 0, 28, "META", meta_values },
  { 0, 3, "RANG", pitch_range_values },
  { 0, 4, "OCTV", octave_values },
  { 0, PITCH_QUANTIZATION_LAST - 1, "QNTZ", quantization_values },
  { 0, 1, "FLAT", boolean_values },
  { 0, 1, "DRFT", boolean_values },
  { 0, 1, "SIGN", boolean_values },
  { 0, 2, "BRIG", brightness_values },
  { 0, 35, "TENV", ad_shape_values },
  { 0, 0, "CAL.", NULL },
  { 0, 0, "    ", NULL },  // Placeholder for CV tester
  { 0, 0, "    ", NULL },  // Placeholder for marquee
  { 0, 0, "BT3e", NULL },  // Placeholder for version string
};

/* static */
const Setting Settings::settings_order_[] = {
  SETTING_OSCILLATOR_SHAPE,
  SETTING_RESOLUTION,
  SETTING_SAMPLE_RATE,
  SETTING_TRIG_SOURCE,
  SETTING_TRIG_DELAY,
  SETTING_TRIG_DESTINATION,
  SETTING_TRIG_AD_SHAPE,
  SETTING_META_MODULATION,
  SETTING_PITCH_RANGE,
  SETTING_PITCH_OCTAVE,
  SETTING_PITCH_QUANTIZER,
  SETTING_VCO_FLATTEN,
  SETTING_VCO_DRIFT,
  SETTING_SIGNATURE,
  SETTING_BRIGHTNESS,
  SETTING_CALIBRATION,
  SETTING_CV_TESTER,
  SETTING_MARQUEE,
  SETTING_VERSION,
};

/* extern */
Settings settings;

}  // namespace braids
