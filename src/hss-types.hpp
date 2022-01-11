/**
 * @file        hss-types.hpp
 * @brief       High side switch types
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_TYPES_HPP_
#define HSS_TYPES_HPP_

namespace hss
{
    /**
     * @addtogroup hssCorelib
     * @{
     */

	/**
	 * @brief Error codes
	 * @{
	 */
	enum Error_t
	{
		OK          	     =  0,   /**< No error */
		INTF_ERROR  	     = -1,   /**< Interface error */
		CONF_ERROR  	     = -2,   /**< Configuration error */
		READ_ERROR  	     = -3,   /**< Read error */
		WRITE_ERROR 	     = -4,   /**< Write error */
		NULLPTR_ERROR        = -5,   /**< Null pointer error */
		INVALID_CH_ERROR     = -6,   /**< Invalid channel error */
        UNSUPPORTED_OP_ERROR = -7,   /**< Invalid channel error */
        INIT_ERROR           = -8    /**< Not initialized */
	};
	/** @} */

	/**
	 * @brief Channel numbers
	 * @{
	 */
	enum Channel_t
	{
		CHANNEL0 	 = 0,           /**< Channel 1 : Valid for BTT shields */
		CHANNEL1 	 = 1,           /**< Channel 2 : Valid for BTT shields */
		ALL_CHANNELS = 2,           /**< Select all channels : Valid for BTT shields */
        NO_CHANNEL   = 3            /**< No channel to select */
	};
	/** @} */

    /**
     * @brief Switch status
     * @{
     */
    enum Status_t{
        UNINITED    = 0,    /**< Not initialized */
        INITED      = 1,    /**< Initiliazed */
        POWER_ON    = 2,    /**< Power on */
        POWER_OFF   = 3,    /**< Power off */
    };
    /** @} */

    /**
     * @brief Diagnosis enable
     * @{
     */
    enum DiagEnable_t{
        DIAG_EN      = 0,    /**< Enabled */
        DIAG_DIS     = 1,    /**< Disabled */
    };
    /** @} */

    /**
     * @brief Diagnosis status
     * @{
     */
    enum DiagStatus_t{
        DIAG_READ_ERROR     = -1,   /**< Read Error */
        NOT_ENABLED         = -2,   /**< Diagnosis not enabled */
        NORMAL              = 0,    /**< Switch works correctly */
        FAULT               = 1,    /**< Switch is in fault condition (Is_fault at IS pin), which can mean "Short to GND", "Overtemperature" or "Overload" */
        FAULT_OL_IC         = 2,    /**< Switch is is either in Open Load (whit enable channel) or inverse current is flowing */
        SHORT_TO_GND_OR_OT  = 3,    /**< Short to the ground or Overtemperature detected*/
        SHORT_TO_VSS        = 5,    /**< Short to the supply voltage */
        OPEN_LOAD           = 6,    /**< Open load detected */
    };
    /** @} */

}

/**
 * @brief Asserts the HSS return code, returning if it is not OK
 */
#define HSS_ASSERT_RET(x)       if( x != OK ) { return x; }

/**
 * @brief Assert if a pointer is nullptr, returning NULLPTR error if null
 */
#define HSS_ASSERT_NULLPTR(x)   if( x == nullptr ) { return NULLPTR_ERROR; }

/** @} */


#endif /** HSS_TYPES_HPP_ **/