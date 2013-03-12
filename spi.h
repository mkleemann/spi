/**
 * ----------------------------------------------------------------------------
 *
 * "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware license):
 * <dev@layer128.net> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a be(ve)er(age) in return. (I don't
 * like beer much.)
 *
 * Matthias Kleemann
 *
 * ----------------------------------------------------------------------------
 *
 * \file spi.h
 *
 * \date Created: 28.11.2011 18:16:21
 * \author Matthias Kleemann
 **/



#ifndef SPI_H_
#define SPI_H_

#include "../config/spi_config.h"

/***************************************************************************/
/* CALCULATE BIT VALUES                                                    */
/***************************************************************************/

/**
 * \def R_SPSR
 * \brief register value of AVR's SPSR
 *
 * In the calculation the value of the SPI2X bit is determined. It is only
 * set if the prescaler value is 2^2n-1 (n = 1..4).
 *
 * \def SPI_PRESCALER_
 * \brief intermediate value of SPI prescaler
 *
 * When used within the calculation of register values, the original
 * prescaler may be multiplied, so the value can be used easier in
 * calculating the next stage.
 *
 * \def R_SPCR
 * \brief register value of AVR's SPCR
 *
 * The setup of the SPR0 and SPR1 bit in SPCR register.
 */

// now start calculating prescaler values. Start with SPI2X bit...
#if (SPI_PRESCALER == 2) || (SPI_PRESCALER == 8) || (SPI_PRESCALER == 32) || (SPI_PRESCALER == 64)
   #define R_SPSR             (1 << SPI2X)
   #define SPI_PRESCALER_     (SPI_PRESCALER * 2)  // to make it easier in the next step
#else
   #define R_SPSR             0
   #define SPI_PRESCALER_     SPI_PRESCALER
#endif

// ... and add SPR0/1.
#if (SPI_PRESCALER_ == 4)
   #define  R_SPCR            0
#elif (SPI_PRESCALER_ == 16)
   #define  R_SPCR            (1 << SPR0)
#elif (SPI_PRESCALER_ == 64)
   #define  R_SPCR            (1 << SPR1)
#elif (SPI_PRESCALER_ == 128)
   #define  R_SPCR            (1 << SPR1) | (1 << SPR0)
#else
   #error   SPI_PRESCALER must be one of the values of 2^n with n = 1..7!
#endif


/***************************************************************************/
/* PROTOTYPES                                                              */
/***************************************************************************/

/**
 * @brief activate SPI pins of AVR
 */
void spi_pin_init(void);


/**
 * @brief activate SPI interface as master
 */
void spi_master_init(void);


/**
 * @brief activate SPI interface as slave
 */
void spi_slave_init(void);

/**
 * @brief  writes (and reads!) a byte via hardware SPI
 * @param  data byte to send
 * @return data byte received
 */
uint8_t spi_putc(uint8_t data);


#endif /* SPI_H_ */