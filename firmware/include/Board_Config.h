/**
 * @file Board_Config.h
 * @brief Configuration settings specific to the hardware board.
 *
 * This file contains settings and initializations specific to the hardware board used in the project,
 * such as pin configurations, specific hardware feature settings, and board-specific constants.
 */

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "Config.h"

extern const char *name;
extern const char *wifi_hostname;
extern const char *ap_ssid;
extern const char *ap_password;


#define ds_3231

#ifdef ds_3231
extern RtcDS3231<TwoWire> Rtc;
extern int sdaPin;
extern int sclPin;
#endif
#ifdef ds_1302
extern ThreeWire myWire;
extern RtcDS1302<ThreeWire> Rtc;
#endif

#endif