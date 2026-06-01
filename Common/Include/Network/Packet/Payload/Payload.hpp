#ifndef __NETWORK_PACKET_PAYLOAD_PAYLOAD_HPP
#define __NETWORK_PACKET_PAYLOAD_PAYLOAD_HPP

#include <cstdint>
#include "Action.hpp"
#include "Measurement.hpp"
#include "Phase.hpp"
#include "State.hpp"
#include "Status.hpp"
#include "Test.hpp"

class Payload
{
public:
    /**
     * Handshake command payload: synchronization package between apps.
     */
    typedef struct __attribute__((packed)) Handshake
    {
        /// Version of the communication protocol should be enabled.
        uint8_t  protoVer;
        /// Timestamp offset, in milliseconds, to be applied by both sides.
        uint32_t tstampMs;
        /// Reserved.
        uint8_t  rsv;
    } Handshake_t;

    /**
     * Configuration command payload: identify the basic settings for the whole
     * testing session.
     */    
    typedef struct __attribute__((packed)) Config
    {
        /// Configuration for the test session.
        Test::Option_t opt;
    } Config_t;

    /**
     * Test phase selection command payload: transmits an index of a testing
     * phase the backend should be switched to.
     */    
    typedef struct __attribute__((packed)) Select
    {
        /// Index of a target phase might to be selected.
        Phase::Index_t phase;
    } Select_t;

    /**
     * Control selection command payload: identify the action operation might
     * to be done, or start/continue/pause/stop.
     */    
    typedef struct __attribute__((packed)) Control
    {
        /// Index of a target command should be executed.
        Action::Index_t act;
    } Control_t;

    /**
     * Testing phase processing status payload: sharing information about the
     * current processing step, status, about errors and other temporary stuff.
     */    
    typedef struct __attribute__((packed)) StatusOut
    {
        /// Instance of the status information structure to be transmitted to
        /// the frontend.
        Status::Info_t info;
    } Status_t;

    /**
     * Measurements payload: contains a set of 
     */    
    typedef struct __attribute__((packed)) Measure
    {
        /// Array of measurement structure instances to be sure enough set of
        /// measurement values can be moved to the frontend.
        Measurement::Info_t meas[Measurement::skArraySize];
    } Measure_t;
};

#endif // #ifndef __NETWORK_PACKET_PAYLOAD_PAYLOAD_HPP