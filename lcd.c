/*
 *  Created on: Dec 01, 2021
 *      Author: Arnav Mehta
 */

#include "main.h"

uint16_t COLORS[]    = { 0x0000, 0xF800, 0x07E0, 0x001F }; // BLACK, RED, GREEN, BLUE
uint16_t GEN_ANS[9]; //Generated Ans
uint16_t USR_ANS[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //User Ans
uint16_t Lcd_Orientation;
uint32_t seed; //seed for random generator

/* ****************************************************************************
 * Used to configure the 5 pins that control the LCD interface on the MKII.
 *
 * CLK and MOSI will be configured as their Primary Module Function
 *
 * CS, C/D, and RST will be configured at output pins
 ******************************************************************************/
void HAL_LCD_PortInit(void)
{
    // LCD_SCK
    LCD_SCK_PORT->SEL0 |= LCD_SCK_PIN;
    LCD_SCK_PORT->SEL1 &= ~LCD_SCK_PIN;

    // LCD_MOSI
    LCD_MOSI_PORT->SEL0 |= LCD_MOSI_PIN;
    LCD_MOSI_PORT->SEL1 &= ~LCD_MOSI_PIN;

    // LCD_CS
    LCD_CS_PORT->DIR |= LCD_CS_PIN;

    // LCD_RST
    LCD_RST_PORT->DIR |= LCD_RST_PIN;

    // LCD_RS
    LCD_DC_PORT->DIR |= LCD_DC_PIN;
}

/* ****************************************************************************
 * Used to configure the eUSCIB Interface as a 3-Wire SPI Interface
 *
 ******************************************************************************/
void HAL_LCD_SpiInit(void)
{
    EUSCI_B0->CTLW0 = EUSCI_B_CTLW0_SWRST;   // Put eUSCI state machine in reset

    // ADD CODE to define the behavior of the eUSCI_B0 as a SPI interface
    EUSCI_B0->CTLW0 = EUSCI_B_CTLW0_CKPH |        // Phase 1
            EUSCI_B_CTLW0_MSB |         // MSB First
            EUSCI_B_CTLW0_MST |         // Set as SPI master
            EUSCI_B_CTLW0_MODE_0 |      // 3 Pin SPI Mode
            EUSCI_B_CTLW0_SYNC |        // Set as synchronous mode
            EUSCI_B_CTLW0_SSEL__SMCLK | // Use SMCLK
            //EUSCI_B_CTLW0_STEM |        // UCxSTE digital output
            EUSCI_B_CTLW0_SWRST;// Remain eUSCI state machine in reset

    // ADD CODE to set the SPI Clock to 12MHz.

    // Divide clock speed by 2 (24MHz/2) = 12 MHz
    //fBitClock = fBRCLK/(UCBRx+1).
    EUSCI_B0->BRW = 1;

    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;    // Initialize USCI state machine

    // set the chip select low
    // The chip select will be held low forever!  There is only 1 device (LCD) 
    // connected to the SPI device, so we will leave it activated all the time.
    LCD_CS_PORT->OUT &= ~LCD_CS_PIN;

    // Set the DC pin high (put it in data mode)
    LCD_DC_PORT->OUT |= LCD_DC_PIN;

}

//*****************************************************************************
//
// Writes a command to the CFAF128128B-0145T.  This function implements the basic SPI
// interface to the LCD display.
//
//*****************************************************************************
void HAL_LCD_writeCommand(uint8_t command)
{
    // Set to command mode -- DC PIN Set to 0
    LCD_DC_PORT->OUT &= ~LCD_DC_PIN;

    // Busy wait while the data is being transmitted. Check the STATW register and see if it is busy 
    while ((EUSCI_B0->STATW & BIT0 ) == 1)
    {
    };

    // Transmit data
    EUSCI_B0->TXBUF = command;

    // Busy wait while the data is being transmitted. Check the STATW register and see if it is busy 
    while ((EUSCI_B0->STATW & BIT0 ) == 1)
    {
    };

    // Set back to data mode, set the DC pin high
    LCD_DC_PORT->OUT |= LCD_DC_PIN;
}

//*****************************************************************************
//
// Writes a data to the CFAF128128B-0145T.  This function implements the basic SPI
// interface to the LCD display.
//
//*****************************************************************************
void HAL_LCD_writeData(uint8_t data)
{
    // Busy wait while the data is being transmitted. Check the STATW register and see if it is busy 
    while ((EUSCI_B0->STATW & BIT0 ) == 1)
    {
    };

    // Transmit data
    EUSCI_B0->TXBUF = data;

    // Busy wait while the data is being transmitted. Check the STATW register and see if it is busy 
    while ((EUSCI_B0->STATW & BIT0 ) == 1)
    {
    };
}

//*****************************************************************************
// Code adapted from TI LCD driver library
//*****************************************************************************
void Crystalfontz128x128_SetDrawFrame(uint16_t x0, uint16_t y0, uint16_t x1,
                                      uint16_t y1)
{

    // ADD CODE
    // Write the CM_CASET command followed by the 4 bytes of data
    // used to set the Column start and end rows.
    HAL_LCD_writeCommand(CM_CASET);
    HAL_LCD_writeData(x0 >> 8);
    HAL_LCD_writeData(x0);
    HAL_LCD_writeData(x1 >> 8);
    HAL_LCD_writeData(x1);

    // ADD CODE
    // Write the CM_RASET command followed by the 4 bytes of data
    // used to set the Row start and end rows.
    HAL_LCD_writeCommand(CM_RASET);
    HAL_LCD_writeData(y0 >> 8);
    HAL_LCD_writeData(y0);
    HAL_LCD_writeData(y1 >> 8);
    HAL_LCD_writeData(y1);
}

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
void Crystalfontz128x128_Init(void)
{
    int i;
    int j;
    uint8_t upper8 = 0x00;
    uint8_t lower8 = 0x00;

    HAL_LCD_PortInit();
    HAL_LCD_SpiInit();

    LCD_RST_PORT->OUT &= ~LCD_RST_PIN;
    HAL_LCD_delay(50);

    LCD_RST_PORT->OUT |= LCD_RST_PIN;
    HAL_LCD_delay(120);

    HAL_LCD_writeCommand(CM_SLPOUT);
    HAL_LCD_delay(200);

    HAL_LCD_writeCommand(CM_GAMSET);
    HAL_LCD_writeData(0x04);

    HAL_LCD_writeCommand(CM_SETPWCTR);
    HAL_LCD_writeData(0x0A);
    HAL_LCD_writeData(0x14);

    HAL_LCD_writeCommand(CM_SETSTBA);
    HAL_LCD_writeData(0x0A);
    HAL_LCD_writeData(0x00);

    HAL_LCD_writeCommand(CM_COLMOD);
    HAL_LCD_writeData(0x05);
    HAL_LCD_delay(10);

    HAL_LCD_writeCommand(CM_MADCTL);
    HAL_LCD_writeData(CM_MADCTL_MX | CM_MADCTL_MY | CM_MADCTL_BGR);

    HAL_LCD_writeCommand(CM_NORON);

    Crystalfontz128x128_SetDrawFrame(0, 0, LCD_HORIZONTAL_MAX,
    LCD_VERTICAL_MAX);
    HAL_LCD_writeCommand(CM_RAMWR);

    for (i = 0; i < LCD_VERTICAL_MAX; i++)
    {

        for (j = 0; j < LCD_HORIZONTAL_MAX; j++)
        {
            HAL_LCD_writeData(upper8);
            HAL_LCD_writeData(lower8);
        }
    }

    HAL_LCD_delay(10);

    HAL_LCD_writeCommand(CM_DISPON);

    HAL_LCD_writeCommand(CM_MADCTL);
    HAL_LCD_writeData(CM_MADCTL_MX | CM_MADCTL_MY | CM_MADCTL_BGR);
}

//*****************************************************************************
//
//! Sets the LCD Orientation.
//!
//! \param orientation is the desired orientation for the LCD. Valid values are:
//!           - \b LCD_ORIENTATION_UP,
//!           - \b LCD_ORIENTATION_LEFT,
//!           - \b LCD_ORIENTATION_DOWN,
//!           - \b LCD_ORIENTATION_RIGHT,
//!
//! This function sets the orientation of the LCD
//!
//! \return None.
//
//*****************************************************************************
void Crystalfontz128x128_SetOrientation(uint8_t orientation)
{
    HAL_LCD_writeCommand(CM_MADCTL);
    Lcd_Orientation = orientation;

    switch (Lcd_Orientation) {
        case LCD_ORIENTATION_UP:
            HAL_LCD_writeData(CM_MADCTL_MX | CM_MADCTL_MY | CM_MADCTL_BGR);
            break;
        case LCD_ORIENTATION_LEFT:
            HAL_LCD_writeData(CM_MADCTL_MY | CM_MADCTL_MV | CM_MADCTL_BGR);
            break;
        case LCD_ORIENTATION_DOWN:
            HAL_LCD_writeData(CM_MADCTL_BGR);
            break;
        case LCD_ORIENTATION_RIGHT:
            HAL_LCD_writeData(CM_MADCTL_MX | CM_MADCTL_MV | CM_MADCTL_BGR);
            break;
    }
}

/*******************************************************************************
 * Function Name: lcd_draw_rectangle
 ********************************************************************************
 * Summary: draws a filled rectangle centered at the coordinates set by x, y
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_draw_rectangle(uint16_t x, uint16_t y, uint16_t width_pixels,
                        uint16_t height_pixels, uint16_t fColor)
{
    uint16_t i, j;
    uint16_t x0;
    uint16_t x1;
    uint16_t y0;
    uint16_t y1;

    // Set the left Col to be the center point minus half the width
    x0 = x - (width_pixels / 2);

    // Set the Right Col to be the center point plus half the width
    x1 = x + (width_pixels / 2);

    // Account for a width that is an even number
    if ((width_pixels & 0x01) == 0x00)
    {
        x1--;
    }

    // Set the upper Row to be the center point minus half the height
    y0 = y - (height_pixels / 2);

    // Set the upper Row to be the center point minus half the height
    y1 = y + (height_pixels / 2);

    // Account for a height that is an  number
    if ((height_pixels & 0x01) == 0x00)
    {
        y1--;
    }

    // Set the boundry of the image to draw
    Crystalfontz128x128_SetDrawFrame(x0, y0, x1, y1);

    // Inform the LCD we are going to send image data
    HAL_LCD_writeCommand(CM_RAMWR);

    // Write out the image data
    for (i = 0; i < height_pixels; i++)
    {
        for (j = 0; j < width_pixels; j++)
        {
            HAL_LCD_writeData(fColor >> 8);
            HAL_LCD_writeData(fColor);
        }
    }

}

/*******************************************************************************
 * Function Name: lcd_draw_rectangle_outline
 ********************************************************************************
 * Summary: draws a outline of rectangle centered at the coordinates set by x, y
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_draw_rectangle_outline(uint16_t x, uint16_t y, uint16_t width_pixels,
                                uint16_t height_pixels, uint16_t fColor,
                                uint16_t grid_number)
{
    uint16_t i, j;
    uint16_t x0;
    uint16_t x1;
    uint16_t y0;
    uint16_t y1;

    // Set the left Col to be the center point minus half the width
    x0 = x - (width_pixels / 2);

    // Set the Right Col to be the center point plus half the width
    x1 = x + (width_pixels / 2);

    // Account for a width that is an even number
    if ((width_pixels & 0x01) == 0x00)
    {
        x1--;
    }

    // Set the upper Row to be the center point minus half the height
    y0 = y - (height_pixels / 2);

    // Set the upper Row to be the center point minus half the height
    y1 = y + (height_pixels / 2);

    // Account for a height that is an  number
    if ((height_pixels & 0x01) == 0x00)
    {
        y1--;
    }

    // Set the boundry of the image to draw
    Crystalfontz128x128_SetDrawFrame(x0, y0, x1, y1);

    // Inform the LCD we are going to send image data
    HAL_LCD_writeCommand(CM_RAMWR);

    // Write out the image data
    for (i = 0; i < height_pixels; i++)
    {
        for (j = 0; j < width_pixels; j++)
        {
            if ((i == 0) || (i == height_pixels - 1) || (j == 0)
                || (j == width_pixels - 1) || (i == 1)
                || (i == height_pixels - 2) || (j == 1)
                || (j == width_pixels - 2))
            {
                HAL_LCD_writeData(fColor >> 8);
                HAL_LCD_writeData(fColor);
            }
            else
            {
                HAL_LCD_writeData(COLORS[USR_ANS[grid_number]] >> 8);
                HAL_LCD_writeData(COLORS[USR_ANS[grid_number]]);
            }
        }
    }

}

/*******************************************************************************
 * Function Name: lcd_draw_image
 ********************************************************************************
 * Summary: Prints an image centered at the coordinates set by x, y
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_draw_image(uint16_t x, uint16_t y, uint16_t image_width_pixels,
                    uint16_t image_height_pixels, const uint8_t *image,
                    uint16_t fColor, uint16_t bColor)
{
    uint16_t i, j;
    uint8_t data;
    uint16_t byte_index;
    uint16_t bytes_per_row;
    uint16_t x0;
    uint16_t x1;
    uint16_t y0;
    uint16_t y1;

    x0 = x - (image_width_pixels / 2);
    x1 = x + (image_width_pixels / 2);
    if ((image_width_pixels & 0x01) == 0x00)
    {
        x1--;
    }

    y0 = y - (image_height_pixels / 2);
    y1 = y + (image_height_pixels / 2);
    if ((image_height_pixels & 0x01) == 0x00)
    {
        y1--;
    }

    Crystalfontz128x128_SetDrawFrame(x0, y0, x1, y1);
    HAL_LCD_writeCommand(CM_RAMWR);
    //lcd_set_pos(x0, x1, y0, y1);

    bytes_per_row = image_width_pixels / 8;
    if ((image_width_pixels % 8) != 0)
    {
        bytes_per_row++;
    }

    for (i = 0; i < image_height_pixels; i++)
    {
        for (j = 0; j < image_width_pixels; j++)
        {
            if ((j % 8) == 0)
            {
                byte_index = (i * bytes_per_row) + j / 8;
                data = image[byte_index];
            }
            if (data & 0x80)
            {
                HAL_LCD_writeData(fColor >> 8);
                HAL_LCD_writeData(fColor);
            }
            else
            {
                HAL_LCD_writeData(bColor >> 8);
                HAL_LCD_writeData(bColor);
            }
            data = data << 1;
        }
    }
}

/*******************************************************************************
 * Function Name: lcd_clear_image
 ********************************************************************************
 * Summary: clears the image centered at x,y covered with bcolor
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_clear_image(uint16_t x, uint16_t y, uint16_t image_width_pixels,
                    uint16_t image_height_pixels, const uint8_t *image,
                    uint16_t fColor, uint16_t bColor)
{
    uint16_t i, j;
    uint16_t bytes_per_row;
    uint16_t x0;
    uint16_t x1;
    uint16_t y0;
    uint16_t y1;

    x0 = x - (image_width_pixels / 2);
    x1 = x + (image_width_pixels / 2);
    if ((image_width_pixels & 0x01) == 0x00)
    {
        x1--;
    }

    y0 = y - (image_height_pixels / 2);
    y1 = y + (image_height_pixels / 2);
    if ((image_height_pixels & 0x01) == 0x00)
    {
        y1--;
    }

    Crystalfontz128x128_SetDrawFrame(x0, y0, x1, y1);
    HAL_LCD_writeCommand(CM_RAMWR);
    //lcd_set_pos(x0, x1, y0, y1);

    bytes_per_row = image_width_pixels / 8;
    if ((image_width_pixels % 8) != 0)
    {
        bytes_per_row++;
    }

    for (i = 0; i < image_height_pixels; i++)
    {
        for (j = 0; j < image_width_pixels; j++)
        {
            HAL_LCD_writeData(bColor >> 8);
            HAL_LCD_writeData(bColor);
        }
    }
}

/*******************************************************************************
 * Function Name: lcd_draw_block_grid
 ********************************************************************************
 * Summary: draws a specific grid with a specific color
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_draw_block_grid(uint16_t grid_number, uint16_t fColor)
{
    lcd_draw_rectangle(grid_X[grid_number],
                       grid_Y[grid_number],
                       42, 42,
                       fColor);
}

/*******************************************************************************
 * Function Name: lcd_draw_block_outline_grid
 ********************************************************************************
 * Summary: draws a specific grid outline with a specific color
 * Returns:
 *  Nothing
 *******************************************************************************/
void lcd_draw_block_outline_grid(uint16_t grid_number, uint16_t fcolor)
{
    lcd_draw_rectangle_outline(grid_X[grid_number], grid_Y[grid_number], 42, 42,
                               fcolor, grid_number);
}

/*******************************************************************************
 * Function Name: lcd_generate_grid
 ********************************************************************************
 * Summary: generates a random grid of colors
 * Returns: Nothing
 *******************************************************************************/
void lcd_generate_grid()
{

    lcd_draw_image(64, 64, grid_image_bitmapWidthPixels,
                   grid_image_bitmapHeightPixels, grid_image_bitmapBitmaps,
                   WHITE,
                   BLACK);

    uint8_t i = 0;
    int r = 0;
    seed += 1;
    srand(seed);

    for (i = 0; i < 9; i++)
    {
        r = 1 + (rand() % 3);
        GEN_ANS[i] = r;
        USR_ANS[i] = BLACK;
        lcd_draw_block_grid(i, COLORS[r]);
    }
}

/*******************************************************************************
 * Function Name: lcd_generate_startup_images
 ********************************************************************************
 * Summary: generates IN 3...2...1 before game begins
 * Returns: Nothing
 *******************************************************************************/
void lcd_generate_startup_images()
{

    lcd_draw_image(64, 32, in_image_bitmapWidthPixels,
                   in_image_bitmapHeightPixels, in_image_bitmapBitmaps,
                   WHITE,
                   BLACK);
    lcd_draw_image(64, 96, image_3_bitmapWidthPixels,
                   image_3_bitmapHeightPixels, image_3_bitmapBitmaps,
                   WHITE,
                   BLACK);
    ece353_T32_1_wait_1S();
    lcd_clear_image(64, 96, image_3_bitmapWidthPixels,
                   image_3_bitmapHeightPixels, image_3_bitmapBitmaps,
                   WHITE,
                   BLACK);
    lcd_draw_image(64, 96, image_2_bitmapWidthPixels,
                   image_2_bitmapHeightPixels, image_2_bitmapBitmaps,
                   WHITE,
                   BLACK);
    ece353_T32_1_wait_1S();
    lcd_clear_image(64, 96, image_2_bitmapWidthPixels,
                   image_2_bitmapHeightPixels, image_2_bitmapBitmaps,
                   WHITE,
                   BLACK);
    lcd_draw_image(64, 96, image_1_bitmapWidthPixels,
                   image_1_bitmapHeightPixels, image_1_bitmapBitmaps,
                   WHITE,
                   BLACK);
    ece353_T32_1_wait_1S();
}

/*******************************************************************************
 * Function Name: lcd_check_result
 ********************************************************************************
 * Summary: Checks if the user inputted grid is correct or not
 * Returns: true or false
 *******************************************************************************/
bool lcd_check_result()
{
    int count = 0;
    int i = 0;

    for (i = 0; i < 9; i++)
    {
        if (USR_ANS[i] == GEN_ANS[i])
        {
            count++;
        }
    }
    if (count == 9)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
 * Function Name: lcd_display_result
 ********************************************************************************
 * Summary: Checks if the user inputted grid is correct or not and displays
 *          green or red accordingly
 * Returns: true or false
 *******************************************************************************/
bool lcd_display_result()
{
    uint16_t fColor = RED;
    bool result = lcd_check_result();

    char s[256];
    sprintf(s, "%d", 10);
    printf(s);
    if(result) {
        if(als_read_light() < LUX_MIN) {
            fColor = GREEN_50;
        } else if (als_read_light() < LUX_MAX && als_read_light() > LUX_MIN) {
            fColor = GREEN_75;
        } else {
            fColor = GREEN;
        }
    } else {
        if(als_read_light() < LUX_MIN) {
            fColor = RED_50;
        } else if (als_read_light() < LUX_MAX && als_read_light() > LUX_MIN) {
            fColor = RED_75;
        } else {
            fColor = RED;
        }
    }

    int i;
    int j;
    Crystalfontz128x128_SetDrawFrame(0, 0, LCD_HORIZONTAL_MAX,
    LCD_VERTICAL_MAX);
    HAL_LCD_writeCommand(CM_RAMWR);

    for (i = 0; i < LCD_VERTICAL_MAX; i++)
    {
        for (j = 0; j < LCD_HORIZONTAL_MAX; j++)
        {
            HAL_LCD_writeData(fColor >> 8);
            HAL_LCD_writeData(fColor);
        }
    }
    return result;
}

/*******************************************************************************
 * Function Name: lcd_clear_grid
 ********************************************************************************
 * Summary: clears the grid
 * Returns: Nothing
 *******************************************************************************/
void lcd_clear_grid()
{
    lcd_draw_image(64, 64, grid_image_bitmapWidthPixels,
                   grid_image_bitmapHeightPixels, grid_image_bitmapBitmaps,
                   WHITE,
                   BLACK);
}

/*******************************************************************************
 * Function Name: lcd_clear_screen
 ********************************************************************************
 * Summary: clears the screen
 * Returns: Nothing
 *******************************************************************************/
void lcd_clear_screen()
{
    uint16_t fColor = BLACK;

    int i;
    int j;
    Crystalfontz128x128_SetDrawFrame(0, 0, LCD_HORIZONTAL_MAX,
    LCD_VERTICAL_MAX);
    HAL_LCD_writeCommand(CM_RAMWR);

    for (i = 0; i < LCD_VERTICAL_MAX; i++)
    {
        for (j = 0; j < LCD_HORIZONTAL_MAX; j++)
        {
            HAL_LCD_writeData(fColor >> 8);
            HAL_LCD_writeData(fColor);
        }
    }
}

