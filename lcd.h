/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include "main.h"

#ifndef LCD_H_
#define LCD_H_

#define LCD_SCK_PORT    P1
#define LCD_SCK_PIN     BIT5

#define LCD_MOSI_PORT   P1
#define LCD_MOSI_PIN    BIT6

#define LCD_CS_PORT     P5
#define LCD_CS_PIN      BIT0

#define LCD_RST_PORT    P5
#define LCD_RST_PIN     BIT7

#define LCD_DC_PORT     P3
#define LCD_DC_PIN      BIT7

// LCD Screen Dimensions
#define LCD_VERTICAL_MAX                   132
#define LCD_HORIZONTAL_MAX                 132

#define LCD_ORIENTATION_UP    0
#define LCD_ORIENTATION_LEFT  1
#define LCD_ORIENTATION_DOWN  2
#define LCD_ORIENTATION_RIGHT 3

// ST7735 LCD controller Command Set
#define CM_NOP             0x00
#define CM_SWRESET         0x01
#define CM_RDDID           0x04
#define CM_RDDST           0x09
#define CM_SLPIN           0x10
#define CM_SLPOUT          0x11
#define CM_PTLON           0x12
#define CM_NORON           0x13
#define CM_INVOFF          0x20
#define CM_INVON           0x21
#define CM_GAMSET          0x26
#define CM_DISPOFF         0x28
#define CM_DISPON          0x29
#define CM_CASET           0x2A
#define CM_RASET           0x2B
#define CM_RAMWR           0x2C
#define CM_RGBSET          0x2d
#define CM_RAMRD           0x2E
#define CM_PTLAR           0x30
#define CM_MADCTL          0x36
#define CM_COLMOD          0x3A
#define CM_SETPWCTR        0xB1
#define CM_SETDISPL        0xB2
#define CM_FRMCTR3         0xB3
#define CM_SETCYC          0xB4
#define CM_SETBGP          0xb5
#define CM_SETVCOM         0xB6
#define CM_SETSTBA         0xC0
#define CM_SETID           0xC3
#define CM_GETHID          0xd0
#define CM_SETGAMMA        0xE0
#define CM_MADCTL_MY       0x80
#define CM_MADCTL_MX       0x40
#define CM_MADCTL_MV       0x20
#define CM_MADCTL_ML       0x10
#define CM_MADCTL_BGR      0x08
#define CM_MADCTL_MH       0x04

#define RED         0xF800
#define RED_50      0xB145
#define RED_75      0xD182

#define GREEN       0x07E0
#define GREEN_50    0x2623
#define GREEN_75    0x2722

#define BLUE        0x001F
#define BLUE_50     0x18D7
#define BLUE_75     0x10DC

#define BLACK       0x0000
#define WHITE       0xFFFF

extern uint16_t COLORS[];
extern uint16_t GEN_ANS[9];
extern uint16_t USR_ANS[];
extern uint16_t Lcd_Orientation;


#define HAL_LCD_delay(x)      __delay_cycles(x * 48)

extern void Crystalfontz128x128_Init(void);

extern void Crystalfontz128x128_SetDrawFrame(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

/* ****************************************************************************
 * Used to configure the 5 pins that control the LCD interface on the MKII.
 *
 * CLK and MOSI will be configured as their Primary Module Function
 *
 * CS, C/D, and RST will be configured at output pins
 ******************************************************************************/
void HAL_LCD_PortInit(void);

/* ****************************************************************************
 * Used to configure the eUSCIB Interface as a 3-Wire SPI Interface
 *
 ******************************************************************************/
void HAL_LCD_SpiInit(void);

//*****************************************************************************
//
// Writes a command to the CFAF128128B-0145T.  This function implements the basic SPI
// interface to the LCD display.
//
//*****************************************************************************
void HAL_LCD_writeCommand(uint8_t command);

//*****************************************************************************
//
// Writes a data to the CFAF128128B-0145T.  This function implements the basic SPI
// interface to the LCD display.
//
//*****************************************************************************
void HAL_LCD_writeData(uint8_t data);

//*****************************************************************************
// Code adapted from TI LCD driver library
//*****************************************************************************
void Crystalfontz128x128_SetDrawFrame(uint16_t x0, uint16_t y0, uint16_t x1,
                                      uint16_t y1);

//*****************************************************************************
// Code adapted from TI LCD driver library
//
//! Initializes the display driver.
//!
//! This function initializes the ST7735 display controller on the panel,
//! preparing it to display data.
//!
//! \return None.
//
//*****************************************************************************
void Crystalfontz128x128_Init(void);

/*******************************************************************************
 * Function Name: lcd_draw_rectangle
 ********************************************************************************
 * Summary: draws a filled rectangle centered at the coordinates set by x, y
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_draw_rectangle(uint16_t x, uint16_t y, uint16_t width_pixels,
                        uint16_t height_pixels, uint16_t fColor);

/*******************************************************************************
 * Function Name: lcd_draw_rectangle_outline
 ********************************************************************************
 * Summary: draws a outline of rectangle centered at the coordinates set by x, y
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_draw_rectangle_outline(uint16_t x, uint16_t y, uint16_t width_pixels,
                                uint16_t height_pixels, uint16_t fColor,
                                uint16_t grid_number);

/*******************************************************************************
 * Function Name: lcd_draw_image
 ********************************************************************************
 * Summary: Prints an image centered at the coordinates set by x, y
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_draw_image(uint16_t x, uint16_t y, uint16_t image_width_pixels,
                    uint16_t image_height_pixels, const uint8_t *image,
                    uint16_t fColor, uint16_t bColor);

/*******************************************************************************
 * Function Name: lcd_clear_image
 ********************************************************************************
 * Summary: clears the image centered at x,y covered with bcolor
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_clear_image(uint16_t x, uint16_t y, uint16_t image_width_pixels,
                    uint16_t image_height_pixels, const uint8_t *image,
                    uint16_t fColor, uint16_t bColor);

/*******************************************************************************
 * Function Name: lcd_draw_block_grid
 ********************************************************************************
 * Summary: draws a specific grid with a specific color
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_draw_block_grid(uint16_t grid_number, uint16_t fColor);

/*******************************************************************************
 * Function Name: lcd_draw_block_outline_grid
 ********************************************************************************
 * Summary: draws a specific grid outline with a specific color
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_draw_block_outline_grid(uint16_t grid_number, uint16_t fcolor);

/*******************************************************************************
 * Function Name: lcd_generate_grid
 ********************************************************************************
 * Summary: generates a random grid of colors
 * Returns: Nothing
 *******************************************************************************/
void lcd_generate_grid();

/*******************************************************************************
 * Function Name: lcd_generate_startup_images
 ********************************************************************************
 * Summary: generates IN 3...2...1 before game begins
 * Returns: Nothing
 *******************************************************************************/
void lcd_generate_startup_images();

/*******************************************************************************
 * Function Name: lcd_check_result
 ********************************************************************************
 * Summary: Checks if the user inputted grid is correct or not
 * Returns: true or false
 *******************************************************************************/
bool lcd_check_result();

/*******************************************************************************
 * Function Name: lcd_display_result
 ********************************************************************************
 * Summary: Checks if the user inputted grid is correct or not and displays
 *          green or red accordingly
 * Returns: true or false
 *******************************************************************************/
bool lcd_display_result();

/*******************************************************************************
 * Function Name: lcd_clear_grid
 ********************************************************************************
 * Summary: clears the grid
 * Returns: Nothing
 *******************************************************************************/
void lcd_clear_grid();

/*******************************************************************************
 * Function Name: lcd_clear_screen
 ********************************************************************************
 * Summary: clears the screen
 * Returns: Nothing
 *******************************************************************************/
void lcd_clear_screen();

/*******************************************************************************
 * Function Name: Set orientation
 ********************************************************************************
 * Summary: sets the screen orientation
 * Returns: Nothing
 *******************************************************************************/
void Crystalfontz128x128_SetOrientation(uint8_t orientation);


#endif /* LCD_H_ */
