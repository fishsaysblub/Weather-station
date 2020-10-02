#pragma once

#include "esp_wifi.h"


#ifdef DEBUG
#define IS_DEBUG 1
#else 
#define IS_DEBUG 0
#endif

//! Logger for weather station
/*!
    Will be automatically removed due to optimiser when compiling in release.
    Be carefule that the regular compilation is in release.
    When in debug, logs data to the console.
*/
#define LOGGER(log)(IS_DEBUG ? printf("Weather station: %s\n", log) : 0)


#define ESP_MAXIMUM_RETRY   5

#define WIFI_CONNECTED_BIT  BIT0
#define WIFI_CONNECTION_FAILED_BIT   BIT1

//! Class handling WIFI interactions
/*!
    The Wi-Fi module aims to allow for Wi-Fi connections to be established as an AT module.
    Must construct the Wifi class followed by a call to 
    \sa InitializeWifi();
*/
class Wifi
{
    private:
        //! Initialises NVS for wifi credentials
        /*!
            Initialises NVS for wifi credentials
            Must be called otherwise we cant do much.
            Claiming part of the NVS for wifi storage.
        */
        void InitializeNVS();

        //! Initialises parameters required for WIFI
        /*!
            Initialises the config for WIFI.
            Sets methods and sets it as station.
        */
        void InitWifiConfig(wifi_config_t *config);

        //! Manages the wifi events.
        /*!
            Determines what action to take with certain WIFI events
            Will connect or retry to establish a connection.
            Sets bits of the "EventGroupHandle_t s_wifi_event_group" kept globally.
        */
        static void HandleWifiEvent(int32_t event_id);

        //! Blocking wait for establishing wifi.
        /*!
            Holds thread hostage for as long as required.
            Determines whether connection is established or has failed.
        */
        void AwaitConnection();

        //! Handler of IP and WIFI events.
        /*!
            Handles events given by the WIFI class.
            Sends WIFI events to 
            \sa HandleWifiEvent()
        */
		static void EventHandler(void* arg, esp_event_base_t event_base, 
                                    int32_t event_id, void* event_data);

	public:
        //! Reasonably easy implementation to interact as wifi client (Station).
        /*!
            Aims to establish a wifi connection as Client (station).
            Expects a follow up call to 
            \a InitialiseWifi()
        */
		Wifi();

        //! Blocking initialisation of the wifi class.
        /*!
            Blocking initialisation of the wifi class.
            Will cause a large power draw spike.
            \returns whether it connected or failed.
        */
		int InitializeWifi();
};


