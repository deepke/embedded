/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/*
    Title: HIDDTransferDriverDescriptors

    About: Purpose
        Declaration of the descriptors used by the HID device Transfer driver.
*/

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "HIDDTransferDriverDesc.h"
#include <board.h>
#include <usb/common/core/USBDeviceDescriptor.h>
#include <usb/common/core/USBConfigurationDescriptor.h>
#include <usb/common/core/USBInterfaceDescriptor.h>
#include <usb/common/core/USBEndpointDescriptor.h>
#include <usb/common/core/USBStringDescriptor.h>
#include <usb/common/hid/HIDGenericDescriptor.h>
#include <usb/common/hid/HIDDeviceDescriptor.h>
#include <usb/common/hid/HIDInterfaceDescriptor.h>
#include <usb/common/hid/HIDDescriptor.h>
#include <usb/common/hid/HIDReport.h>
#include <usb/common/hid/HIDGenericDesktop.h>
#include <usb/common/hid/HIDLeds.h>
#include <usb/common/hid/HIDButton.h>
#include <usb/device/core/USBDDriverDescriptors.h>

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "HID Transfer Device Descriptor IDs"
/// ...
///
/// !IDs
/// - HIDDTransferDriverDescriptors_PRODUCTID
/// - HIDDTransferDriverDescriptors_VENDORID
/// - HIDDTransferDriverDescriptors_RELEASE

/// Device product ID.
#define HIDDTransferDriverDescriptors_PRODUCTID       0x6201
/// Device vendor ID.
#define HIDDTransferDriverDescriptors_VENDORID        0x03EB
/// Device release number.
#define HIDDTransferDriverDescriptors_RELEASE         0x0100
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Macros
//------------------------------------------------------------------------------

/// Returns the minimum between two values.
#define MIN(a, b)       ((a < b) ? a : b)

//------------------------------------------------------------------------------
//         Internal types
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/// List of descriptors that make up the configuration descriptors of a
/// device using the HID Transfer driver.
//------------------------------------------------------------------------------
typedef struct {

    /// Configuration descriptor.
    USBConfigurationDescriptor configuration;
    /// Interface descriptor.
    USBInterfaceDescriptor interface;
    /// HID descriptor.
    HIDDescriptor hid;
    /// Interrupt IN endpoint descriptor.
    USBEndpointDescriptor interruptIn;
    /// Interrupt OUT endpoint descriptor.
    USBEndpointDescriptor interruptOut;

} __attribute__ ((packed)) HIDDTransferDriverConfigurationDescriptors;

//------------------------------------------------------------------------------
//         Internal variables
//------------------------------------------------------------------------------

/// Device descriptor.
static const USBDeviceDescriptor deviceDescriptor = {

    sizeof(USBDeviceDescriptor),
    USBGenericDescriptor_DEVICE,
    USBDeviceDescriptor_USB2_00,
    HIDDeviceDescriptor_CLASS,
    HIDDeviceDescriptor_SUBCLASS,
    HIDDeviceDescriptor_PROTOCOL,
    BOARD_USB_ENDPOINTS_MAXPACKETSIZE(0),
    HIDDTransferDriverDescriptors_VENDORID,
    HIDDTransferDriverDescriptors_PRODUCTID,
    HIDDTransferDriverDescriptors_RELEASE,
    1, // Index of manufacturer description
    2, // Index of product description
    3, // Index of serial number description
    1  // One possible configuration
};

#if defined (BOARD_USB_UDPHS) || defined(BOARD_USB_OTGHS)
/// Device qualifier descriptor (high-speed only).
static const USBDeviceQualifierDescriptor qualifierDescriptor = {

    sizeof(USBDeviceQualifierDescriptor),
    USBGenericDescriptor_DEVICEQUALIFIER,
    HIDDeviceDescriptor_CLASS,
    HIDDeviceDescriptor_SUBCLASS,
    HIDDeviceDescriptor_PROTOCOL,
    BOARD_USB_ENDPOINTS_MAXPACKETSIZE(0),
    1, // One possible configuration
    0 // Reserved
};
#endif

/// Configuration descriptor.
static const HIDDTransferDriverConfigurationDescriptors configurationDescriptors = {

    // Configuration descriptor
    {
        sizeof(USBConfigurationDescriptor),
        USBGenericDescriptor_CONFIGURATION,
        sizeof(HIDDTransferDriverConfigurationDescriptors),
        1, // One interface in this configuration
        1, // This is configuration #1
        0, // No associated string descriptor
        BOARD_USB_BMATTRIBUTES,
        USBConfigurationDescriptor_POWER(100)
    },
    // Interface descriptor
    {
        sizeof(USBInterfaceDescriptor),
        USBGenericDescriptor_INTERFACE,
        0, // This is interface #0
        0, // This is alternate setting #0
        2, // Two endpoints used
        HIDInterfaceDescriptor_CLASS,
        HIDInterfaceDescriptor_SUBCLASS_NONE,
        HIDInterfaceDescriptor_PROTOCOL_NONE,
        0  // No associated string descriptor
    },
    // HID descriptor
    {
        sizeof(HIDDescriptor),
        HIDGenericDescriptor_HID,
        HIDDescriptor_HID1_11,
        0, // Device is not localized, no country code
        1, // One HID-specific descriptor (apart from this one)
        HIDGenericDescriptor_REPORT,
        HIDDTransferDriverDescriptors_REPORTSIZE
    },
    // Interrupt IN endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(
            USBEndpointDescriptor_IN,
            HIDDTransferDriverDescriptors_INTERRUPTIN),
        USBEndpointDescriptor_INTERRUPT,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(
                        HIDDTransferDriverDescriptors_INTERRUPTIN),
            MIN(USBEndpointDescriptor_MAXINTERRUPTSIZE_FS,
                                   HIDDTransferDriver_REPORTSIZE)),
        HIDDTransferDriverDescriptors_INTERRUPTIN_POLLING
    },
    // Interrupt OUT endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(
            USBEndpointDescriptor_OUT,
            HIDDTransferDriverDescriptors_INTERRUPTOUT),
        USBEndpointDescriptor_INTERRUPT,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(
                        HIDDTransferDriverDescriptors_INTERRUPTOUT),
            MIN(USBEndpointDescriptor_MAXINTERRUPTSIZE_FS,
                                    HIDDTransferDriver_REPORTSIZE)),
        HIDDTransferDriverDescriptors_INTERRUPTOUT_POLLING
    }
};

#if defined (BOARD_USB_UDPHS) || defined(BOARD_USB_OTGHS)
/// Other-speed configuration descriptor.
static const HIDDTransferDriverConfigurationDescriptors otherSpeedDescriptors = {

    // Configuration descriptor
    {
        sizeof(USBConfigurationDescriptor),
        USBGenericDescriptor_OTHERSPEEDCONFIGURATION,
        sizeof(HIDDTransferDriverConfigurationDescriptors),
        1, // One interface in this configuration
        1, // This is configuration #1
        0, // No associated string descriptor
        BOARD_USB_BMATTRIBUTES,
        USBConfigurationDescriptor_POWER(100)
    },
    // Interface descriptor
    {
        sizeof(USBInterfaceDescriptor),
        USBGenericDescriptor_INTERFACE,
        0, // This is interface #0
        0, // This is alternate setting #0
        2, // Two endpoints used
        HIDInterfaceDescriptor_CLASS,
        HIDInterfaceDescriptor_SUBCLASS_NONE,
        HIDInterfaceDescriptor_PROTOCOL_NONE,
        0  // No associated string descriptor
    },
    // HID descriptor
    {
        sizeof(HIDDescriptor),
        HIDGenericDescriptor_HID,
        HIDDescriptor_HID1_11,
        0, // Device is not localized, no country code
        1, // One HID-specific descriptor (apart from this one)
        HIDGenericDescriptor_REPORT,
        HIDDTransferDriverDescriptors_REPORTSIZE
    },
    // Interrupt IN endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(
            USBEndpointDescriptor_IN,
            HIDDTransferDriverDescriptors_INTERRUPTIN),
        USBEndpointDescriptor_INTERRUPT,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(
                        HIDDTransferDriverDescriptors_INTERRUPTIN),
            MIN(USBEndpointDescriptor_MAXINTERRUPTSIZE_HS,
                                    HIDDTransferDriver_REPORTSIZE)),
        HIDDTransferDriverDescriptors_INTERRUPTIN_POLLING
    },
    // Interrupt OUT endpoint descriptor
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(
            USBEndpointDescriptor_OUT,
            HIDDTransferDriverDescriptors_INTERRUPTIN),
        USBEndpointDescriptor_INTERRUPT,
        MIN(BOARD_USB_ENDPOINTS_MAXPACKETSIZE(
                        HIDDTransferDriverDescriptors_INTERRUPTOUT),
            MIN(USBEndpointDescriptor_MAXINTERRUPTSIZE_HS,
                                    HIDDTransferDriver_REPORTSIZE)),
        HIDDTransferDriverDescriptors_INTERRUPTIN_POLLING
    }
};
#endif

/*
    Variables: String descriptors
        languageIdDescriptor - Language ID string descriptor.
        manufacturerDescriptor - Manufacturer name.
        productDescriptor - Product name.
        serialNumberDescriptor - Product serial number.
        stringDescriptors - Array of pointers to string descriptors.
*/
static const unsigned char languageIdDescriptor[] = {

    USBStringDescriptor_LENGTH(1),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_ENGLISH_US
};

static const unsigned char manufacturerDescriptor[] = {

    USBStringDescriptor_LENGTH(5),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('A'),
    USBStringDescriptor_UNICODE('T'),
    USBStringDescriptor_UNICODE('M'),
    USBStringDescriptor_UNICODE('E'),
    USBStringDescriptor_UNICODE('L')
};

static const unsigned char productDescriptor[] = {

    USBStringDescriptor_LENGTH(22),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('A'),
    USBStringDescriptor_UNICODE('T'),
    USBStringDescriptor_UNICODE('M'),
    USBStringDescriptor_UNICODE('E'),
    USBStringDescriptor_UNICODE('L'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('A'),
    USBStringDescriptor_UNICODE('T'),
    USBStringDescriptor_UNICODE('9'),
    USBStringDescriptor_UNICODE('1'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('H'),
    USBStringDescriptor_UNICODE('I'),
    USBStringDescriptor_UNICODE('D'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('T'),
    USBStringDescriptor_UNICODE('R'),
    USBStringDescriptor_UNICODE('A'),
    USBStringDescriptor_UNICODE('N'),
    USBStringDescriptor_UNICODE('S'),
    USBStringDescriptor_UNICODE('F'),
    USBStringDescriptor_UNICODE('E'),
    USBStringDescriptor_UNICODE('R'),
};

static const unsigned char serialNumberDescriptor[] = {

    USBStringDescriptor_LENGTH(12),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('0'),
    USBStringDescriptor_UNICODE('1'),
    USBStringDescriptor_UNICODE('2'),
    USBStringDescriptor_UNICODE('3'),
    USBStringDescriptor_UNICODE('4'),
    USBStringDescriptor_UNICODE('5'),
    USBStringDescriptor_UNICODE('6'),
    USBStringDescriptor_UNICODE('7'),
    USBStringDescriptor_UNICODE('8'),
    USBStringDescriptor_UNICODE('9'),
    USBStringDescriptor_UNICODE('A'),
    USBStringDescriptor_UNICODE('F')
};

static const unsigned char *stringDescriptors[] = {

    languageIdDescriptor,
    manufacturerDescriptor,
    productDescriptor,
    serialNumberDescriptor
};

//------------------------------------------------------------------------------
//         Exported variables
//------------------------------------------------------------------------------

/// List of descriptors used by the HID Transfer driver.
USBDDriverDescriptors hiddTransferDriverDescriptors = {

    &deviceDescriptor,
    (USBConfigurationDescriptor *) &configurationDescriptors,
#if defined (BOARD_USB_UDPHS) || defined(BOARD_USB_OTGHS)
    &qualifierDescriptor,
    (USBConfigurationDescriptor *) &otherSpeedDescriptors,
    &deviceDescriptor,
    (USBConfigurationDescriptor *) &configurationDescriptors,
    &qualifierDescriptor,
    (USBConfigurationDescriptor *) &otherSpeedDescriptors,
#else
    0, // No full-speed device qualifier descriptor
    0, // No full-speed other speed configuration
    0, // No high-speed device descriptor
    0, // No high-speed configuration descriptor
    0, // No high-speed device qualifier descriptor
    0, // No high-speed other speed configuration descriptor
#endif
    stringDescriptors,
    4 // Four string descriptors in list
};

/// Report descriptor used by the driver.
const unsigned char hiddReportDescriptor[] = {

    // Global Usage Page
    HIDReport_GLOBAL_USAGEPAGE + 2, 0xFF, 0xFF, // Vendor-defined
    // Collection: Application
    HIDReport_LOCAL_USAGE + 1, 0xFF, // Vendor-defined
    HIDReport_COLLECTION + 1, HIDReport_COLLECTION_APPLICATION,
        // Input report: Vendor-defined
        HIDReport_LOCAL_USAGE + 1, 0xFF, // Vendor-defined usage
        HIDReport_GLOBAL_REPORTCOUNT + 1, HIDDTransferDriver_REPORTSIZE,
        HIDReport_GLOBAL_REPORTSIZE + 1, 8,
        HIDReport_GLOBAL_LOGICALMINIMUM + 1, (unsigned char) -128,
        HIDReport_GLOBAL_LOGICALMAXIMUM + 1, (unsigned char)  127,
        HIDReport_INPUT + 1, 0,    // No Modifiers

        // Output report: vendor-defined
        HIDReport_LOCAL_USAGE + 1, 0xFF, // Vendor-defined usage
        HIDReport_GLOBAL_REPORTCOUNT + 1, HIDDTransferDriver_REPORTSIZE,
        HIDReport_GLOBAL_REPORTSIZE + 1, 8,
        HIDReport_GLOBAL_LOGICALMINIMUM + 1, (unsigned char) -128,
        HIDReport_GLOBAL_LOGICALMAXIMUM + 1, (unsigned char)  127,
        HIDReport_OUTPUT + 1, 0,    // No Modifiers
        
    HIDReport_ENDCOLLECTION
};

