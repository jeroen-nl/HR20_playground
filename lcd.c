
#pragma once

/*****************************************************************************
*   Macros
*****************************************************************************/

// Modes for LCD_SetSymbol
#define LCD_MODE_OFF        0    //!< (0b00) segment off
#define LCD_MODE_BLINK_1    1    //!< (0b01) segment on during 1. frame (blinking)
#define LCD_MODE_BLINK_2    2    //!< (0b10) segment on during 2. frame (blinking)
#define LCD_MODE_ON         3    //!< (0b11) segment permanent on

#define LCD_CONTRAST_INITIAL  14 //!< initial LCD contrast (0-15)
#define LCD_BLINK_FRAMES      12 //!< refreshes for each frame @ 48 frames/s
                                 //!< 12 refreshes -> 4Hz Blink frequency
#define LCD_BITPLANES          2   //!< \brief two bitplanes for blinking

/*****************************************************************************
*   Global Vars
*****************************************************************************/
extern volatile uint8_t LCD_used_bitplanes; //!< \brief number of used bitplanes / used for power
extern uint8_t LCD_force_update;        //!< \brief force update LCD

/*****************************************************************************
*   Prototypes
*****************************************************************************/

void LCD_Init(void);                       // Init the LCD Controller
void LCD_AllSegments(uint8_t);             // Set all segments to LCD_MODE
void LCD_ClearAll(void);                   // Clear all segments
void LCD_ClearHourBar(void);               // Clear 24 bar segments
void LCD_ClearSymbols(void);               // Clear AUTO MANU PROG SUN MOON SNOW
void LCD_ClearNumbers(void);               // Clear 7 Segments and Collumns

void LCD_PrintDec(uint8_t, uint8_t, uint8_t);  // Print DEC-val (0-99)
void LCD_PrintDec3(uint16_t value, uint8_t pos, uint8_t mode); // Print DEC-val (0-255)
void LCD_PrintDecW(uint16_t, uint8_t);         // Print DEC-val (0-9999)                       
void LCD_PrintHex(uint8_t, uint8_t, uint8_t);  // Print HEX-val (0-ff)
void LCD_PrintHexW(uint16_t, uint8_t);         // Print HEX-val (0-ffff) 
void LCD_PrintChar(uint8_t, uint8_t, uint8_t); // Print one digit 
void LCD_PrintTemp(uint8_t, uint8_t);          // Print temperature (val+4,9)�C
void LCD_PrintTempInt(int16_t , uint8_t);      // Print temperature (val/100)�C
void LCD_PrintDayOfWeek(uint8_t, uint8_t);     // Print Day of Week (german)
void LCD_PrintStringID(uint8_t id, uint8_t mode); // Print LCD string ID
#define LCD_PrintDayOfWeek(dow,mode) (LCD_PrintStringID(dow,mode))

void LCD_SetSeg(uint8_t, uint8_t);              // Set one Segment (0-69)
void LCD_SetSegReg(uint8_t, uint8_t, uint8_t);  // Set multiple LCD Segment(s) with common register 
void LCD_SetHourBarSeg(uint8_t, uint8_t);       // Set HBS (0-23) (Hour-Bar-Segment)
void LCD_HourBarBitmap(uint32_t bitmap);        // Set HBS like bitmap
void task_lcd_update(void);

#define  LCD_Update()  ((LCDCRA |= (1<<LCDIE)),(LCD_force_update=1))
	// Update at next LCD_ISR
    // Enable LCD start of frame interrupt
    


//***************************
// LCD Chars:
//***************************
#define LCD_CHAR_0       0  //!< char "0"
#define LCD_CHAR_1       1  //!< char "1"
#define LCD_CHAR_2       2  //!< char "2"
#define LCD_CHAR_3       3  //!< char "3"
#define LCD_CHAR_4       4  //!< char "4"
#define LCD_CHAR_5       5  //!< char "5"
#define LCD_CHAR_6       6  //!< char "6"

#define LCD_CHAR_7       7  //!< char "7"
#define LCD_CHAR_8       8  //!< char "8"
#define LCD_CHAR_9       9  //!< char "9"
#define LCD_CHAR_A      10  //!< char "A"
#define LCD_CHAR_b      11  //!< char "b"
#define LCD_CHAR_C      12  //!< char "C"
#define LCD_CHAR_d      13  //!< char "d"

#define LCD_CHAR_E      14  //!< char "E"
#define LCD_CHAR_F      15  //!< char "F"
#define LCD_CHAR_deg    16  //!< symbol degree
#define LCD_CHAR_n      17  //!< char "n"
#define LCD_CHAR_P      18  //!< char "P"
#define LCD_CHAR_H      19  //!< char "H"
#define LCD_CHAR_I      20  //!< char "I"
#define LCD_CHAR_neg    22  //!< char "-"
#define LCD_CHAR_2lines 26  //!< line on top, line on bottom
#define LCD_CHAR_3lines 27  //!< 3 horizontal lines
#define LCD_CHAR_r      28  //!< char "r"
#define LCD_CHAR_o      31  //!< char "r"
#define LCD_CHAR_L      35  //!< char "L"
#define LCD_CHAR_c      36  //!< char "c"
#define LCD_CHAR_U      37  //!< char "U"
#define LCD_CHAR_t      38  //!< char "t"
#define LCD_CHAR_y      39  //!< char "y"
#define LCD_CHAR_S       5  //!< char "5" = "S"

#define LCD_CHAR_NULL  32  //!< space

/*! \verbatim
 *******************************************************************************
 *  LCD Layout:
 *
 *        B|B|B|B|B|B|B|B|B|B|B |B |B |B |B |B |B |B |B |B |B |B |B |B |    
 *        0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|    
 *                                                                          
 *        ---------------------------BAR24------------------------------    
 *                                                                          
 *      Auto      3A         2A                  1A         0A       SUN    
 *             3F    3B   2F    2B            1F    1B   0F    0B           
 *      Manu      3g         2g       Col2       1g         0g       MOON   
 *             3E    3C   2E    2C            1E    1C   0E    0C           
 *      Prog      3D         2D       Col1       1D         0D       STAR   
 *                                                                          
 *******************************************************************************
 \endverbatim   */

#if THERMOTRONIC==1
// LCD_SEG:_xx for LCD_SetSeg   // LCDDR | AtMega169 |  LCD_Data[]
#define LCD_SEG_B0          1   //  0, 0 |  SEG000   |  [0], BIT 0
                                //  0, 1 |  SEG001   |  [0], BIT 1
#define LCD_SEG_B1          2   //  0, 2 |  SEG002   |  [0], BIT 2
#define LCD_SEG_B2          3   //  0, 3 |  SEG003   |  [0], BIT 3
#define LCD_SEG_B3          4   //  0, 4 |  SEG004   |  [0], BIT 4
#define LCD_SEG_B4          5   //  0, 5 |  SEG005   |  [0], BIT 5
#define LCD_SEG_B5          6   //  0, 6 |  SEG006   |  [0], BIT 6
#define LCD_SEG_B6          7   //  0, 7 |  SEG007   |  [0], BIT 7
#define LCD_SEG_B7          8   //  1, 0 |  SEG008   |  [1], BIT 0
#define LCD_SEG_B8          9   //  1, 1 |  SEG009   |  [1], BIT 1
#define LCD_SEG_B9         10   //  1, 2 |  SEG010   |  [1], BIT 2
#define LCD_SEG_BAR24       0   //  1, 3 |  SEG011   |  [1], BIT 3
#define LCD_SEG_B14        11   //  1, 4 |  SEG012   |  [1], BIT 4
#define LCD_SEG_B15        12   //  1, 5 |  SEG013   |  [1], BIT 5
#define LCD_SEG_B16        13   //  1, 6 |  SEG014   |  [1], BIT 6
#define LCD_SEG_B17        14   //  1, 7 |  SEG015   |  [1], BIT 7
#define LCD_SEG_B18        15   //  2, 0 |  SEG016   |  [2], BIT 0
#define LCD_SEG_B19        16   //  2, 1 |  SEG017   |  [2], BIT 1
#define LCD_SEG_B20        17   //  2, 2 |  SEG018   |  [2], BIT 2
#define LCD_SEG_B21        18   //  2, 3 |  SEG019   |  [2], BIT 3
#define LCD_SEG_B22        19   //  2, 4 |  SEG020   |  [2], BIT 4
#define LCD_SEG_B23        20   //  2, 5 |  SEG021   |  [2], BIT 5
//*****************************************************************
#define LCD_SEG_AUTO       25   //  5, 0 |  SEG100   |  [3], BIT 0
                                //  5, 1 |  SEG101   |  [3], BIT 1
#define LCD_SEG_PROG       26   //  5, 2 |  SEG102   |  [3], BIT 2
#define LCD_SEG_3F         27   //  5, 3 |  SEG103   |  [3], BIT 3
#define LCD_SEG_3G         28   //  5, 4 |  SEG104   |  [3], BIT 4
#define LCD_SEG_3A         29   //  5, 5 |  SEG105   |  [3], BIT 5
#define LCD_SEG_3B         30   //  5, 6 |  SEG106   |  [3], BIT 6
#define LCD_SEG_2F         31   //  5, 7 |  SEG107   |  [3], BIT 7
#define LCD_SEG_2G         32   //  6, 0 |  SEG108   |  [4], BIT 0
#define LCD_SEG_2A         33   //  6, 1 |  SEG109   |  [4], BIT 1
#define LCD_SEG_2B         34   //  6, 2 |  SEG110   |  [4], BIT 2
#define LCD_SEG_COL2       24   //  6, 3 |  SEG111   |  [4], BIT 3
#define LCD_SEG_1F         35   //  6, 4 |  SEG112   |  [4], BIT 4
#define LCD_SEG_1G         36   //  6, 5 |  SEG113   |  [4], BIT 5
#define LCD_SEG_1A         37   //  6, 6 |  SEG114   |  [4], BIT 6
#define LCD_SEG_1B         38   //  6, 7 |  SEG115   |  [4], BIT 7
#define LCD_SEG_0F         39   //  7, 0 |  SEG116   |  [5], BIT 0
#define LCD_SEG_0G         40   //  7, 1 |  SEG117   |  [5], BIT 1
#define LCD_SEG_0A         41   //  7, 2 |  SEG118   |  [5], BIT 2
#define LCD_SEG_0B         42   //  7, 3 |  SEG119   |  [5], BIT 3
#define LCD_SEG_SNOW       43   //  7, 4 |  SEG120   |  [5], BIT 4
#define LCD_SEG_SUN        44   //  7, 5 |  SEG121   |  [5], BIT 5
//*****************************************************************
                                // 10, 0 |  SEG200   |  [6], BIT 0
                                // 10, 1 |  SEG201   |  [6], BIT 1
#define LCD_SEG_MANU       50   // 10, 2 |  SEG202   |  [6], BIT 2
#define LCD_SEG_3E         51   // 10, 3 |  SEG203   |  [6], BIT 3
#define LCD_SEG_3D         52   // 10, 4 |  SEG204   |  [6], BIT 4
#define LCD_SEG_B11        53   // 10, 5 |  SEG205   |  [6], BIT 5
#define LCD_SEG_3C         54   // 10, 6 |  SEG206   |  [6], BIT 6
#define LCD_SEG_2E         55   // 10, 7 |  SEG207   |  [6], BIT 7
#define LCD_SEG_2D         56   // 11, 0 |  SEG208   |  [7], BIT 0
#define LCD_SEG_B10        57   // 11, 1 |  SEG209   |  [7], BIT 1
#define LCD_SEG_2C         58   // 11, 2 |  SEG210   |  [7], BIT 2
#define LCD_SEG_COL1       48   // 11, 3 |  SEG211   |  [7], BIT 3
#define LCD_SEG_1E         59   // 11, 4 |  SEG212   |  [7], BIT 4
#define LCD_SEG_1D         60   // 11, 5 |  SEG213   |  [7], BIT 5
#define LCD_SEG_B13        61   // 11, 6 |  SEG214   |  [7], BIT 6
#define LCD_SEG_1C         62   // 11, 7 |  SEG215   |  [7], BIT 7
#define LCD_SEG_0E         63   // 12, 0 |  SEG216   |  [8], BIT 0
#define LCD_SEG_0D         64   // 12, 1 |  SEG217   |  [8], BIT 1
#define LCD_SEG_B12        65   // 12, 2 |  SEG218   |  [8], BIT 2
#define LCD_SEG_0C         66   // 12, 3 |  SEG219   |  [8], BIT 3
                                // 12, 4 |  SEG220   |  [8], BIT 4
#define LCD_SEG_MOON       68   // 12, 5 |  SEG221   |  [8], BIT 5
//*****************************************************************

#define LCD_DECIMAL_DOT     LCD_SEG_COL1

#else

#ifdef HR25
/*! \verbatim
 *******************************************************************************
 *  LCD Layout:
 *        ---------------------------BAR24------------------------------    
 *
 *        0|1|2|3|4|5|6|7|8|9|0a|0b|0c|0d|0e|B |0f|B |B |B |B |B |B |B |    
 *        0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|  
 *        --------------------------BAR_SUB-----------------------------
 *                                                                          
 *  MOON SUN SUPER2 D1   D2   D3      D4       D5    D6   D7         PADLOCK
 *  BATOUT SPANNER                                                                       
 *  BAT1,2 SNOW   3A         2A                  1A         0A       DEGREE CELCIUS       
 *      Prog   3F    3B   2F    2B    Col2    1F    1B   0F    0B    PERCENT
 *      Auto      3g         2g       Col1       1g         0g          
 *      Eco    3E    3C   2E    2C            1E    1C   0E    0C    MINUS/VERTPLUS       
 *      Manu      3D   Col3  2D       Col4       1D   Col5  0D       DOOROPEN   
 *                                                                          
 *******************************************************************************
 \endverbatim   */
#define LCD_SEG_B0          0
#define LCD_SEG_B1          1
#define LCD_SEG_B2          2
#define LCD_SEG_B3          3
#define LCD_SEG_B4          4
#define LCD_SEG_B5          5
#define LCD_SEG_B6          6
#define LCD_SEG_B7          7

#define LCD_SEG_B8          8
#define LCD_SEG_B9          9
#define LCD_SEG_B10        10
#define LCD_SEG_B11        11
#define LCD_SEG_B12        12
#define LCD_SEG_B13        13
#define LCD_SEG_B14        14
#define LCD_SEG_B16        15

#define LCD_SEG_B17        16
#define LCD_SEG_B20        17
#define LCD_SEG_B21        18
#define LCD_SEG_BAR_SUB    19
#define LCD_SEG_B23        20

#define LCD_SEG_ECO        24
#define LCD_SEG_PROG       25
#define LCD_SEG_3F         26
#define LCD_SEG_3G         27
#define LCD_SEG_3A         28
#define LCD_SEG_3B         29
#define LCD_SEG_2F         30
#define LCD_SEG_2G         31


#define LCD_SEG_2A         32
#define LCD_SEG_2B         33
#define LCD_SEG_COL2       34
#define LCD_SEG_1F         35
#define LCD_SEG_1G         36
#define LCD_SEG_1A         37
#define LCD_SEG_1B         38
#define LCD_SEG_0F         39

#define LCD_SEG_0G         40
#define LCD_SEG_0A         41
#define LCD_SEG_0B         42
#define LCD_SEG_MINUS      43
#define LCD_DEGREE         44
#define LCD_PADLOCK        45

#define LCD_SEG_MANU       48
#define LCD_SEG_AUTO       49
#define LCD_SEG_3E         50
#define LCD_SEG_3D         51
#define LCD_SEG_3C         52
#define LCD_SEG_COL3       53
#define LCD_SEG_2E         54
#define LCD_SEG_2D         55

#define LCD_SEG_2C         56
#define LCD_SEG_COL4       57
#define LCD_SEG_COL1       58
#define LCD_SEG_1E         59
#define LCD_SEG_1D         60
#define LCD_SEG_1C         61
#define LCD_SEG_COL5       62
#define LCD_SEG_0E         63

#define LCD_SEG_0D         64
#define LCD_SEG_0C         65
#define LCD_SEG_DOOR_OPEN  66
#define LCD_SEG_VERTPLUS   67
#define LCD_SEG_PERCENT    68
#define LCD_SEG_CELCIUS    69

#define LCD_SEG_BAT_OUTLINE 72
#define LCD_SEG_BAT_TOP     73 // BAT1
#define LCD_SEG_BAT_BOTTOM  74 // BAT2
#define LCD_SEG_SNOW        75
#define LCD_SEG_SPANNER     76
#define LCD_SEG_MOON        77
#define LCD_SEG_SUN         78
#define LCD_SEG_SUPER2      79

#define LCD_SEG_D1          80
#define LCD_SEG_D2          81
#define LCD_SEG_D3          82
#define LCD_SEG_D4          83
#define LCD_SEG_D5          84
#define LCD_SEG_D6          85
#define LCD_SEG_D7          86
#define LCD_SEG_B15         87

#define LCD_SEG_B18         88
#define LCD_SEG_B19         89
#define LCD_SEG_B22         90
#define LCD_SEG_BAR24       91

#define LCD_DECIMAL_DOT     LCD_SEG_COL4

#else /* HR20 */

// LCD_SEG:_xx for LCD_SetSeg   // LCDDR | AtMega169 |  LCD_Data[]
#define LCD_SEG_B0          0   //  0, 0 |  SEG000   |  [0], BIT 0
                                //  0, 1 |  SEG001   |  [0], BIT 1
#define LCD_SEG_B1          2   //  0, 2 |  SEG002   |  [0], BIT 2
#define LCD_SEG_B2          3   //  0, 3 |  SEG003   |  [0], BIT 3
#define LCD_SEG_B3          4   //  0, 4 |  SEG004   |  [0], BIT 4
#define LCD_SEG_B4          5   //  0, 5 |  SEG005   |  [0], BIT 5
#define LCD_SEG_B5          6   //  0, 6 |  SEG006   |  [0], BIT 6
#define LCD_SEG_B6          7   //  0, 7 |  SEG007   |  [0], BIT 7
#define LCD_SEG_B7          8   //  1, 0 |  SEG008   |  [1], BIT 0
#define LCD_SEG_B8          9   //  1, 1 |  SEG009   |  [1], BIT 1
#define LCD_SEG_B9         10   //  1, 2 |  SEG010   |  [1], BIT 2
#define LCD_SEG_BAR24      11   //  1, 3 |  SEG011   |  [1], BIT 3
#define LCD_SEG_B14        12   //  1, 4 |  SEG012   |  [1], BIT 4
#define LCD_SEG_B15        13   //  1, 5 |  SEG013   |  [1], BIT 5
#define LCD_SEG_B16        14   //  1, 6 |  SEG014   |  [1], BIT 6
#define LCD_SEG_B17        15   //  1, 7 |  SEG015   |  [1], BIT 7
#define LCD_SEG_B18        16   //  2, 0 |  SEG016   |  [2], BIT 0
#define LCD_SEG_B19        17   //  2, 1 |  SEG017   |  [2], BIT 1
#define LCD_SEG_B20        18   //  2, 2 |  SEG018   |  [2], BIT 2
#define LCD_SEG_B21        19   //  2, 3 |  SEG019   |  [2], BIT 3
#define LCD_SEG_B22        20   //  2, 4 |  SEG020   |  [2], BIT 4
#define LCD_SEG_B23        21   //  2, 5 |  SEG021   |  [2], BIT 5
//*****************************************************************
#define LCD_SEG_AUTO       24   //  5, 0 |  SEG100   |  [3], BIT 0
                                //  5, 1 |  SEG101   |  [3], BIT 1
#define LCD_SEG_PROG       26   //  5, 2 |  SEG102   |  [3], BIT 2
#define LCD_SEG_3F         27   //  5, 3 |  SEG103   |  [3], BIT 3
#define LCD_SEG_3G         28   //  5, 4 |  SEG104   |  [3], BIT 4
#define LCD_SEG_3A         29   //  5, 5 |  SEG105   |  [3], BIT 5
#define LCD_SEG_3B         30   //  5, 6 |  SEG106   |  [3], BIT 6
#define LCD_SEG_2F         31   //  5, 7 |  SEG107   |  [3], BIT 7
#define LCD_SEG_2G         32   //  6, 0 |  SEG108   |  [4], BIT 0
#define LCD_SEG_2A         33   //  6, 1 |  SEG109   |  [4], BIT 1
#define LCD_SEG_2B         34   //  6, 2 |  SEG110   |  [4], BIT 2
#define LCD_SEG_COL2       35   //  6, 3 |  SEG111   |  [4], BIT 3
#define LCD_SEG_1F         36   //  6, 4 |  SEG112   |  [4], BIT 4
#define LCD_SEG_1G         37   //  6, 5 |  SEG113   |  [4], BIT 5
#define LCD_SEG_1A         38   //  6, 6 |  SEG114   |  [4], BIT 6
#define LCD_SEG_1B         39   //  6, 7 |  SEG115   |  [4], BIT 7
#define LCD_SEG_0F         40   //  7, 0 |  SEG116   |  [5], BIT 0
#define LCD_SEG_0G         41   //  7, 1 |  SEG117   |  [5], BIT 1
#define LCD_SEG_0A         42   //  7, 2 |  SEG118   |  [5], BIT 2
#define LCD_SEG_0B         43   //  7, 3 |  SEG119   |  [5], BIT 3
#define LCD_SEG_SNOW       44   //  7, 4 |  SEG120   |  [5], BIT 4
#define LCD_SEG_SUN        45   //  7, 5 |  SEG121   |  [5], BIT 5
//*****************************************************************
                                // 10, 0 |  SEG200   |  [6], BIT 0
                                // 10, 1 |  SEG201   |  [6], BIT 1
#define LCD_SEG_MANU       50   // 10, 2 |  SEG202   |  [6], BIT 2
#define LCD_SEG_3E         51   // 10, 3 |  SEG203   |  [6], BIT 3
#define LCD_SEG_3D         52   // 10, 4 |  SEG204   |  [6], BIT 4
#define LCD_SEG_B11        53   // 10, 5 |  SEG205   |  [6], BIT 5
#define LCD_SEG_3C         54   // 10, 6 |  SEG206   |  [6], BIT 6
#define LCD_SEG_2E         55   // 10, 7 |  SEG207   |  [6], BIT 7
#define LCD_SEG_2D         56   // 11, 0 |  SEG208   |  [7], BIT 0
#define LCD_SEG_B10        57   // 11, 1 |  SEG209   |  [7], BIT 1
#define LCD_SEG_2C         58   // 11, 2 |  SEG210   |  [7], BIT 2
#define LCD_SEG_COL1       59   // 11, 3 |  SEG211   |  [7], BIT 3
#define LCD_SEG_1E         60   // 11, 4 |  SEG212   |  [7], BIT 4
#define LCD_SEG_1D         61   // 11, 5 |  SEG213   |  [7], BIT 5
#define LCD_SEG_B13        62   // 11, 6 |  SEG214   |  [7], BIT 6
#define LCD_SEG_1C         63   // 11, 7 |  SEG215   |  [7], BIT 7
#define LCD_SEG_0E         64   // 12, 0 |  SEG216   |  [8], BIT 0
#define LCD_SEG_0D         65   // 12, 1 |  SEG217   |  [8], BIT 1
#define LCD_SEG_B12        66   // 12, 2 |  SEG218   |  [8], BIT 2
#define LCD_SEG_0C         67   // 12, 3 |  SEG219   |  [8], BIT 3
                                // 12, 4 |  SEG220   |  [8], BIT 4
#define LCD_SEG_MOON       69   // 12, 5 |  SEG221   |  [8], BIT 5
//*****************************************************************

#define LCD_DECIMAL_DOT     LCD_SEG_COL1



//***************************
// LCD Strings:
//***************************

#define LCD_STRING_bloc         8
#define LCD_STRING_4xminus      9
#define LCD_STRING_minusCminus 10
#define LCD_STRING_Err         11
#define LCD_STRING_OFF         12
#define LCD_STRING_On          13
#define LCD_STRING_OPEn        14
#define LCD_STRING_BAtt        15
#define LCD_STRING_E2          16
#define LCD_STRING_E3          17
#define LCD_STRING_E4          18
#define LCD_STRING_EEPr        19



/*
 *  Open HR20
 *
 *  target:     ATmega169 @ 4 MHz in Honnywell Rondostat HR20E
 *
 *  compiler:    WinAVR-20071221
 *              avr-libc 1.6.0
 *              GCC 4.2.2
 *
 *  copyright:  2008 Dario Carluccio (hr20-at-carluccio-dot-de)
 * 				2008 Jiri Dobry (jdobry-at-centrum-dot-cz)
 *
 *  license:    This program is free software; you can redistribute it and/or
 *              modify it under the terms of the GNU Library General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later version.
 *
 *              This program is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *              GNU General Public License for more details.
 *
 *              You should have received a copy of the GNU General Public License
 *              along with this program. If not, see http:*www.gnu.org/licenses
 */

/*!
 * \file       lcd.c
 * \brief      functions to control the HR20 LCD
 * \author     Dario Carluccio <hr20-at-carluccio-dot-de>, Jiri Dobry <jdobry-at-centrum-dot-cz>
 * \date       $Date$
 * $Rev$
 */

// AVR LibC includes
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/version.h>

// redefine variable names for newer processor
#ifdef _AVR_IOM329_H_
#define LCDDR7 LCDDR07
#define LCDDR6 LCDDR06
#define LCDDR5 LCDDR05
#define LCDDR2 LCDDR02
#define LCDDR1 LCDDR01
#define LCDDR0 LCDDR00
#endif

// HR20 Project includes
#include "main.h"
#include "lcd.h"
#include "task.h"
#include "common/rtc.h"
#include "eeprom.h"

// Local Defines
#define LCD_CONTRAST_MIN       0   //!< \brief contrast minimum
#define LCD_CONTRAST_MAX      15   //!< \brief contrast maxmum
#define LCD_MAX_POS            4   //!< \brief number of 7 segment chars
#define LCD_MAX_CHARS  (sizeof(LCD_CharTablePrgMem))   //!< \brief no. of chars in \ref LCD_CharTablePrgMem
#ifdef HR25
#define LCD_REGISTER_COUNT     12   //!< \brief no. of registers each bitplane
#else
#define LCD_REGISTER_COUNT     9   //!< \brief no. of registers each bitplane
#endif

// Vars
volatile uint8_t LCD_used_bitplanes = 1; //!< \brief number of used bitplanes / used for power save

//! segment data for the segment registers in each bitplane
volatile uint8_t LCD_Data[LCD_BITPLANES][LCD_REGISTER_COUNT];

#ifdef LCD_UPSIDE_DOWN
  #define LCD_upside_down 1
#else
  #define LCD_upside_down 0
#endif

// Look-up table to convert value to LCD display data (segment control)
// Get value with: bitmap = pgm_read_byte(&LCD_CharTablePrgMem[position]);
const uint8_t LCD_CharTablePrgMem[] PROGMEM =
{
    0x77, //      0:0x77   1:0x06   2:0x6B   3:0x4F   4:0x1e   5:0x5D   6:0x7D
    0x06, // 1    ******        *   ******   ******   *    *   ******   ******
    0x6B, // 2    *    *        *        *        *   *    *   *        *
    0x4F, // 3    *    *        *   ******   ******   ******   ******   ******
    0x1e, // 4    *    *        *   *             *        *        *   *    *
    0x5d, // 5    ******        *   ******   ******        *   ******   ******
    0x7d, // 6   1110111  0000110  1101011  1001111  0011110  1011101  1111101

    0x07, // 7    7:0x07   8:0x7F   9:0x5F  10:0x3f  11:0x7C  12:0x71  13:0x5e
    0x7F, // 8    ******   ******   ******   ******   *        ******        *
    0x5F, // 9         *   *    *   *    *   *    *   *        *             *
    0x3f, //10         *   ******   ******   ******   ******   *        ******
    0x7C, //11         *   *    *        *   *    *   *    *   *        *    *
    0x71, //12         *   ******   ******   *    *   ******   ******   ******
    0x6E, //13   0000111  1111111  1011111  0111111  1111100  1110001  1101110

    0x79, //14   14:0x79  15:0x39  16:0x1b  17:0x2c  18:0x3b  19:0x3e 20:0x30
    0x39, //15    ******   ******   ******            ******   *    *  *
    0x1b, //16    *        *        *    *            *    *   *    *  *
    0x2c, //17    ******   ******   ******   ******   ******   ******  *
    0x3b, //18    *        *                 *    *   *        *    *  *
    0x3e, //19    ******   *                 *    *   *        *    *  *
    0x30, //20   1111001  0111001  0011011  0101100  0111011  0111110  0110000

    0x40, //21   21:0x40  22:0x08  23:0x01  24:0x48  25:0x09  26:0x41  27:0x49
    0x08, //22                      ******            ******   ******   ******
    0x01, //23
    0x48, //24             ******            ******   ******            ******
    0x09, //25
    0x41, //26    ******                     ******            ******   ******
    0x49, //27   1000000  0001000  0000001  1001000  0001001  1000001  1001001

    0x28, //28   28:0x28  29:0x2c  30:0x20  31:0x6c  32:0x00  33:0x33  34:0x17
    0x2c, //29                                                 ******   ******
    0x20, //30                                                 *    *   *    *
    0x6c, //31    ******   ******   *        ******   Space    *    *   *    *
    0x00, //32    *        *    *   *        *    *            *             *
    0x33, //33    *        *    *   *        ******            *             *
    0x17, //34   0101000  0101100  0100000  1101100  0000000  0110011  0010111

    0x70, //35   35:0x70  36:0x68  37:0x76  38:0x78  39:0x5e
    0x68, //36    *                 *    *   *        *    *
    0x76, //37    *                 *    *   *        *    *
    0x78, //38    *        ******   *    *   ******   ******
    0x5e  //39    *        *        *    *   *             *
          //40    ******   ******   ******   ******   ******
          //41   1110000  1101000  1110110  1111000  1011110
};

#if LANG==LANG_uni
  // Look-up chars table for LCD strings (universal/numbers)
  const uint8_t LCD_StringTable[][4] PROGMEM =
  {
      {32, 1,22, 7},    //!<  " 1-7" 
      {32,22, 1,22},    //!<  " -1-" MO
      {32,22, 2,22},    //!<  " -2-" TU
      {32,22, 3,22},    //!<  " -3-" WE
      {32,22, 4,22},    //!<  " -4-" TH
      {32,22, 5,22},    //!<  " -5-" FR
      {32,22, 6,22},    //!<  " -6-" SA
      {32,22, 7,22},    //!<  " -7-" SU
      {11, 1,31,36},    //!<  "b1oc"    LCD_STRING_bloc
      {22,22,22,22},    //!<  "----"    LCD_STRING_4xminus
      {32,22,12,22},    //!<  " -C-"    LCD_STRING_minusCminus
      {32,14,28,28},    //!<  " Err"    LCD_STRING_Err
      { 0,15,15,32},    //!<  "OFF "    LCD_STRING_OFF
      { 0,29,32,32},    //!<  "On  "    LCD_STRING_On
      { 0,18,14,29},    //!<  "OPEn"    LCD_STRING_OPEn
      {11,10,38,38},    //!<  "BAtt"    LCD_STRING_BAtt
      {32,14, 2,32},    //!<  " E2 "    LCD_STRING_E2
      {32,14, 3,32},    //!<  " E3 "    LCD_STRING_E3
      {32,14, 4,32},    //!<  " E4 "    LCD_STRING_E4
      {14,14,18,28},    //!<  "EEPr"    LCD_STRING_EEPr
  };
#elif LANG==LANG_de
  // Look-up chars table for LCD strings (german)
  const uint8_t LCD_StringTable[][4] PROGMEM =
  {
      {32, 1,22, 7},    //!<  " 1-7" 
      {33,34,31,32},    //!<  Montag:     'rno '
      {32,13,30,32},    //!<  Dienstag:   ' di '
      {33,34,30,32},    //!<  Mittwoch:   'rni '
      {32,13,31,32},    //!<  Donnerstag: ' do '
      {32,15,28,32},    //!<  Freitag:    ' Fr '
      {32, 5,10,32},    //!<  Samstag:    ' SA '
      {32, 5,31,32},    //!<  Sonntag:    ' So '
      {11, 1,31,36},    //!<  "b1oc"    LCD_STRING_bloc
      {22,22,22,22},    //!<  "----"    LCD_STRING_4xminus
      {32,22,12,22},    //!<  " -C-"    LCD_STRING_minusCminus
      {32,14,28,28},    //!<  " Err"    LCD_STRING_Err
      { 0,15,15,32},    //!<  "OFF "    LCD_STRING_OFF
      { 0,29,32,32},    //!<  "On  "    LCD_STRING_On
        tmp = value % 16;
        LCD_PrintChar(tmp, pos, mode);
      { 0,18,14,29},    //!<  "OPEn"    LCD_STRING_OPEn
      {11,10,38,38},    //!<  "BAtt"    LCD_STRING_BAtt
      {32,14, 2,32},    //!<  " E2 "    LCD_STRING_E2
      {32,14, 3,32},    //!<  " E3 "    LCD_STRING_E3
      {32,14, 4,32},    //!<  " E4 "    LCD_STRING_E4
      {14,14,18,28},    //!<  "EEPr"    LCD_STRING_EEPr
  };
#elif LANG==LANG_cs
  // Look-up chars table for LCD strings (czech)
  const uint8_t LCD_StringTable[][4] PROGMEM =
  {
      {32, 1,22, 7},    //!<  " 1-7" 
      {32,18,31,22},    //!<  " Po "
      {32,37,38,22},    //!<  " Ut "
      {32, 5,38,22},    //!<  " St "
      {32,12,38,22},    //!<  " Ct "
      {32,18,10,22},    //!<  " PA "
      {32, 5,31,22},    //!<  " So "
      {32,29,14,22},    //!<  " nE "
      {11, 1,31,36},    //!<  "b1oc"    LCD_STRING_bloc
      {22,22,22,22},    //!<  "----"    LCD_STRING_4xminus
      {32,22,12,22},    //!<  " -C-"    LCD_STRING_minusCminus
      {32,14,28,28},    //!<  " Err"    LCD_STRING_Err
      { 0,15,15,32},    //!<  "OFF "    LCD_STRING_OFF
      { 0,29,32,32},    //!<  "On  "    LCD_STRING_On
      { 0,18,14,29},    //!<  "OPEn"    LCD_STRING_OPEn
      {11,10,38,38},    //!<  "BAtt"    LCD_STRING_BAtt
      {32,14, 2,32},    //!<  " E2 "    LCD_STRING_E2
      {32,14, 3,32},    //!<  " E3 "    LCD_STRING_E3
      {32,14, 4,32},    //!<  " E4 "    LCD_STRING_E4
      {14,14,18,28},    //!<  "EEPr"    LCD_STRING_EEPr
  };
#endif



// Look-up table to adress element F for one Position. ( 32 : 10 )
const uint8_t LCD_FieldOffsetTablePrgMem[] PROGMEM =
{
#if THERMOTRONIC==1
    39,    //!<  Field 0
    35,    //!<  Field 1              
    31,    //!<  Field 2
    27     //!<  Field 3
#elif HR25==1
	39,    //!<  Field 0
	35,    //!<  Field 1
    30,    //!<  Field 2
    26     //!<  Field 3
#else
    40,    //!<  Field 0
    36,    //!<  Field 1              
    31,    //!<  Field 2
    27     //!<  Field 3
#endif
};


#ifdef HR25
// Look-up table to adress a segment inside a field
const uint8_t LCD_SegOffsetTablePrgMem[] PROGMEM =
{
     2,    //  Seg A            AAAA
     3,    //  Seg B           E    B
    26,    //  Seg C           E    B
     1,    //  Seg D            DDDD
     0,    //  Seg E           F    C
    24,    //  Seg F           F    C
    25     //  Seg G            GGGG
};
#else
// Look-up table to adress a segment inside a field
const uint8_t LCD_SegOffsetTablePrgMem[] PROGMEM =
{
     2,    //  Seg A            AAAA
     3,    //  Seg B           E    B
    27,    //  Seg C           E    B
     1,    //  Seg D            DDDD
     0,    //  Seg E           F    C
    24,    //  Seg F           F    C
    25     //  Seg G            GGGG
};
#endif

//! Look-up table for adress hour-bar segments
const uint8_t LCD_SegHourBarOffsetTablePrgMem[] PROGMEM =
{
    LCD_SEG_B0,    LCD_SEG_B1,    LCD_SEG_B2,    LCD_SEG_B3,    LCD_SEG_B4,
    LCD_SEG_B5,    LCD_SEG_B6,    LCD_SEG_B7,    LCD_SEG_B8,    LCD_SEG_B9,
    LCD_SEG_B10,   LCD_SEG_B11,   LCD_SEG_B12,   LCD_SEG_B13,   LCD_SEG_B14,
    LCD_SEG_B15,   LCD_SEG_B16,   LCD_SEG_B17,   LCD_SEG_B18,   LCD_SEG_B19,
    LCD_SEG_B20,   LCD_SEG_B21,   LCD_SEG_B22,   LCD_SEG_B23
};


static void LCD_calc_used_bitplanes(uint8_t mode);

/*!
 *******************************************************************************
 *  Init LCD
 *
 *  \note
 *  - Initialize LCD Global Vars
 *  - Set up the LCD (timing, contrast, etc.)
 ******************************************************************************/
void LCD_Init(void)
{
    // Clear segment buffer.
    LCD_AllSegments(LCD_MODE_OFF);

    //Set the initial LCD contrast level
    LCDCCR = (config.lcd_contrast << LCDCC0);

#ifdef HR25
    // LCD Control and Status Register B
    //   - clock source is TOSC1 pin
    //   - COM0:2 connected
    //   - SEG0:22 connected
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM0);
    // LCD Frame Rate Register
    //   - LCD Prescaler Select N=16       @32.768Hz ->   2048Hz
    //   - LCD Duty Cycle 1/4 (K=8)       2048Hz / 8 ->    256Hz
    //   - LCD Clock Divider  (D=5)        256Hz / 5 ->   51,2Hz
    LCDFRR = ((1<<LCDCD2));
#else
    // LCD Control and Status Register B
    //   - clock source is TOSC1 pin
    //   - COM0:3 connected
    //   - SEG0:22 connected
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDPM2)| (1<<LCDPM0);
    // LCD Frame Rate Register
    //   - LCD Prescaler Select N=16       @32.768Hz ->   2048Hz
    //   - LCD Duty Cycle 1/3 (K=6)       2048Hz / 6 -> 341,33Hz
    //   - LCD Clock Divider  (D=7)     341,33Hz / 7 ->  47,76Hz
    LCDFRR = ((1<<LCDCD2)|(1<<LCDCD1));
#endif

    // LCD Control and Status Register A
    //  - Enable LCD
    //  - Set Low Power Waveform
    LCDCRA = (1<<LCDEN) | (1<<LCDAB);

    // Enable LCD start of frame interrupt
    LCDCRA |= (1<<LCDIE);

	LCD_used_bitplanes=1;
}


/*!
 *******************************************************************************
 *  Switch LCD on/off
 *
 *  \param mode
 *       -      0: clears all digits
 *       -  other: set all digits
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF
 ******************************************************************************/
void LCD_AllSegments(uint8_t mode)
{
    uint8_t i;
    uint8_t val = (mode==LCD_MODE_ON)?0xff:0x00;

    for (i=0; i<LCD_REGISTER_COUNT*LCD_BITPLANES; i++){
            ((uint8_t *)LCD_Data)[i] = val;
    }
	LCD_used_bitplanes=1;
    LCD_Update();
}

/*!
 *******************************************************************************
 *  Print char in LCD field
 *
 *  \note  segments inside one 7 segment array are adressed using address of
 *         segment "F" \ref LCD_FieldOffsetTablePrgMem[] as base address adding
 *         \ref LCD_SegOffsetTablePrgMem[] *
 *
 *  \note  You have to call \ref LCD_Update() to trigger update on LCD if not
 *         it is triggered automatically at change of bitframe
 *
 *  \param value char to print see \ref LCD_CharTablePrgMem[]
 *  \param pos   position in lcd 0=right to 3=left <tt> 32 : 10 </tt>
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 *  \param value
 *        - 0: clears all digits,
 *        - other: set all digits
 ******************************************************************************/
void LCD_PrintChar(uint8_t value, uint8_t pos, uint8_t mode)
{
    uint8_t fieldbase;
    uint8_t bitmap;
    uint8_t seg;
    uint8_t i;
    uint8_t mask;

    // Boundary Check 
    if ((pos < LCD_MAX_POS) && (value < LCD_MAX_CHARS)) {

        // Get Fieldbase for Position
		if (LCD_upside_down)
		  pos = 3-pos;
        fieldbase = pgm_read_byte(&LCD_FieldOffsetTablePrgMem[pos]);
        // Get Bitmap for Value
        bitmap = pgm_read_byte(&LCD_CharTablePrgMem[value]);
        mask = 1;

        // Set 7 Bits
        for (i=0; i<7; i++){
            seg = fieldbase + pgm_read_byte(&LCD_SegOffsetTablePrgMem[LCD_upside_down?6-i:i]);
            // Set or Clear?
            LCD_SetSeg(seg,((bitmap & mask)?mode:LCD_MODE_OFF));
            mask <<= 1;
        }
    }
}


/*!
 *******************************************************************************
 *  Print Hex value in LCD field
 *
 *  \note  You have to call \ref LCD_Update() to trigger update on LCD if not
 *         it is triggered automatically at change of bitframe
 *
 *  \param value value to be printed (0-0xff)
 *  \param pos   position in lcd 0:left, 1:right
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_PrintHex(uint8_t value, uint8_t pos, uint8_t mode)
{
    uint8_t tmp;
    // Boundary Check
    if (pos <= 2) {
        // 1st Digit at 0 (2)
        pos++;
        // 2nd Digit at 1 (3)
        tmp = value / 16;
        LCD_PrintChar(tmp, pos, mode);
    }
}


/*!
 *******************************************************************************
 *  Print decimal value in LCD field (only 2 digits)
 *
 *  \note You have to call \ref LCD_Update() to trigger update on LCD if not
 *        it is triggered automatically at change of bitframe
 *
 *  \param value value to be printed (0-99)
 *  \param pos   position in lcd 
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_PrintDec(uint8_t value, uint8_t pos, uint8_t mode)
{
    uint8_t tmp;
    // Boundary Check
    if ((pos <= 2) && (value < 100)) {
        // 1st Digit at 0 (2)
        tmp = value % 10;
        LCD_PrintChar(tmp, pos, mode);
        pos++;
        // 2nd Digit at 1 (3)
        tmp = value / 10;
        LCD_PrintChar(tmp, pos, mode);
    }
}
/*!
 *******************************************************************************
 *  Print decimal value in LCD field (3 digits)
 *
 *  \note You have to call \ref LCD_Update() to trigger update on LCD if not
 *        it is triggered automatically at change of bitframe
 *
 *  \param value value to be printed (0-999)
 *  \param pos   position in lcd
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_PrintDec3(uint16_t value, uint8_t pos, uint8_t mode)
{
    if (value>999) value=999;
    if (pos <= 1) {
        // 3nd Digit 
        LCD_PrintChar(value / 100, pos+2, mode);
        LCD_PrintDec(value%100, pos, mode);
    }
}


/*!
 *******************************************************************************
 *  Print decimal uint16 value in LCD field
 *
 *  \note You have to call \ref LCD_Update() to trigger update on LCD if not
 *        it is triggered automatically at change of bitframe
 *
 *  \param value value to be printed (0-9999)
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_PrintDecW(uint16_t value, uint8_t mode)
{
    uint8_t tmp;
    // Boundary Check
    if (value > 9999){
        value = 9999;        
    }
    // Print     
    tmp = (uint8_t) (value / 100);
    LCD_PrintDec(tmp, 2, mode);
    tmp = (uint8_t) (value % 100);
    LCD_PrintDec(tmp, 0, mode);
}


/*!
 *******************************************************************************
 *  Print hex uint16 value in LCD field
 *
 *  \note You have to call \ref LCD_Update() to trigger update on LCD if not
 *        it is triggered automatically at change of bitframe
 *
 *  \param value value to be printed (0-0xffff)
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_PrintHexW(uint16_t value, uint8_t mode)
{
    uint8_t tmp;
    // Print     
    tmp = (uint8_t) (value >> 8);
    LCD_PrintHex(tmp, 2, mode);
    tmp = (uint8_t) (value & 0xff);
    LCD_PrintHex(tmp, 0, mode);
}


/*!
 *******************************************************************************
 *  Print BYTE as temperature on LCD (desired temperature)
 *
 *  \note  You have to call \ref LCD_Update() to trigger update on LCD if not
 *         it is triggered automatically at change of bitframe
 *
 *  \note  range for desired temperature 5,0�C - 30�C, OFF and ON 
 *
 *  \param temp<BR>
 *     - TEMP_MIN-1          : \c OFF <BR>
 *     - TEMP_MIN to TEMP_MAX : temperature = temp/2  [5,0�C - 30�C]
 *     - TEMP_MAX+1          : \c ON  <BR>
 *     -    other: \c invalid <BR>
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_PrintTemp(uint8_t temp, uint8_t mode)
{
    if (temp==TEMP_MIN-1){
        // OFF
        LCD_PrintStringID(LCD_STRING_OFF,mode); 
    } else if (temp==TEMP_MAX+1){
        // On
        LCD_PrintStringID(LCD_STRING_On,mode); 
    } else if (temp>TEMP_MAX+1){
        // Error -E rr
        LCD_PrintStringID(LCD_STRING_Err,mode); 
    } else {
#ifdef HR25
        #define START_POS 0
        LCD_PrintChar(LCD_CHAR_NULL, 3, mode);
        LCD_SetSeg(LCD_DEGREE, mode);      // Display degrees sign
        LCD_SetSeg(LCD_SEG_CELCIUS, mode); // Display celsius sign
        LCD_SetSeg(LCD_SEG_COL5, mode);    // decimal point
#else
        #define START_POS 1
        LCD_PrintChar(LCD_CHAR_C, 0, mode);// Print C on last segment
        LCD_SetSeg(LCD_SEG_COL1, mode);    // decimal point
#endif
        LCD_PrintDec(temp>>1, START_POS + 1, mode);
        LCD_PrintChar(((temp&1)?5:0), START_POS, mode);
        if (temp < (100/5)) {
            LCD_PrintChar(LCD_CHAR_NULL, START_POS + 2, mode);
        }
    }
}


/*!
 *******************************************************************************
 *  Print INT as temperature on LCD (measured temperature)
 *
 *  \note  You have to call \ref LCD_Update() to trigger update on LCD if not
 *         it is triggered automatically at change of bitframe
 *
 *
 *  \param temp temperature in 1/100 deg C<BR>
 *     min:  -999 => -9,9�C
 *     max:  9999 => 99,9�C
  *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_PrintTempInt(int16_t temp, uint8_t mode)
{
    bool neg;

    // check min / max
    if (temp < -999){
        temp = -999;
    }
 
    // negative ?    
    neg = (temp < 0); 
    if (neg){        
        temp = -temp;    
    } 

#ifdef HR25
    #define START_POS 0
    LCD_PrintChar(LCD_CHAR_NULL, 3, mode);
    LCD_SetSeg(LCD_DEGREE, mode);      // Display degrees sign
    LCD_SetSeg(LCD_SEG_CELCIUS, mode); // Display celsius sign
    LCD_SetSeg(LCD_SEG_COL5, mode);    // decimal point
#else
    #define START_POS 1
    LCD_PrintChar(LCD_CHAR_C, 0, mode);// Print C on last segment
    LCD_SetSeg(LCD_SEG_COL1, mode);    // decimal point
#endif

    // 1/100�C not printed
    LCD_PrintDec3(temp/10, START_POS, mode);
    
    if (neg){
        // negative Temp      
        LCD_PrintChar(LCD_CHAR_neg, START_POS + 2, mode);
    } else if (temp < 1000){
        // Temp < 10�C
        LCD_PrintChar(LCD_CHAR_NULL, START_POS + 2, mode);
    }                             
}

/*!
 *******************************************************************************
 *  Print LCD string from table
 *
 *  \note  something weird due to 7 Segments
 *
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_PrintStringID(uint8_t id, uint8_t mode) {
    uint8_t i;
    uint8_t tmp;
    // Put 4 chars
    for (i=0; i<4; i++) {
        tmp = pgm_read_byte(&LCD_StringTable[id][i]);
        LCD_PrintChar(tmp, 3-i, mode);
    }
}


/*!
 *******************************************************************************
 *  Set segment of the hour-bar
 *
 *  \note  You have to call \ref LCD_Update() to trigger update on LCD if not
 *         it is triggered automatically at change of bitframe
 *
 *  \param seg No of the hour bar segment 0-23
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_SetHourBarSeg(uint8_t seg, uint8_t mode)
{
    uint8_t segment;
    // Get segment number for this element
    segment = pgm_read_byte(&LCD_SegHourBarOffsetTablePrgMem[seg]);
    // Set segment 
    LCD_SetSeg(segment, mode);
}

/*!
 *******************************************************************************
 *  Set all segments of the hour-bar (ON/OFF) like bitmap
 *
 *  \note  You have to call \ref LCD_Update() to trigger update on LCD if not
 *         it is triggered automatically at change of bitframe
 *
 *  \param bitmap of hour bar segment 0-23 (bit0 is segment0 etc.)
 *  \note blink is not supported
 ******************************************************************************/
void LCD_HourBarBitmap(uint32_t bitmap)
{
#if 0
    uint8_t i;
    for (i=0;i<24;i++) {
        uint8_t segment = pgm_read_byte(&LCD_SegHourBarOffsetTablePrgMem[i]);
        LCD_SetSeg(segment, (((uint8_t)bitmap & 1)? LCD_MODE_ON : LCD_MODE_OFF ));
        bitmap = bitmap>>1;
    }
#else
    asm volatile (
    "    movw r14,r22                                     " "\n"
    "    mov  r16,r24                                     " "\n"
    "    ldi r28,lo8(LCD_SegHourBarOffsetTablePrgMem)     " "\n"       
    "    ldi r29,hi8(LCD_SegHourBarOffsetTablePrgMem)     " "\n"
    "L2:                                                  " "\n"
    "    movw r30,r28                                     " "\n"
    "	 lpm r24, Z                                       " "\n"
    "	 clr r22                                          " "\n"
    "	 lsr r16                                          " "\n"
    "	 ror r15                                          " "\n"
    "	 ror r14                                          " "\n"
    "    brcc L3                                          " "\n"
    "    ldi r22,lo8(%0)                                  " "\n"
    "L3:                                                  " "\n"
    "	call LCD_SetSeg                                   " "\n"
    "	adiw r28,1                                        " "\n"
    "	cpi r28,lo8(LCD_SegHourBarOffsetTablePrgMem+24)   " "\n"
    "	brne L2                                           " "\n"
    :
    : "I" (LCD_MODE_ON)
    : "r14", "r15", "r16", "r28", "r29", "r30", "r31"
    );
#endif
}


/*!
 *******************************************************************************
 *  Set all segments from left up to val and clear all other segments
 *
 *  \note  You have to call \ref LCD_Update() to trigger update on LCD if not
 *         it is triggered automatically at change of bitframe
 *
 *  \param seg No of the last hour bar segment to be set 0-23
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
#if 0
void LCD_SetHourBarBar(uint8_t val, uint8_t mode)
{
    uint8_t i;
    // Only Segment 0:23
    if (val > 23){
        val = 23;
    }
    // For each Segment 0:23
    for (i=0; i<24; i++) {
        if (i > val){
            LCD_SetHourBarSeg(i, LCD_MODE_OFF);
        } else {
            LCD_SetHourBarSeg(i, mode);
        } 
    }
}
#endif


/*!
 *******************************************************************************
 *  Set only one segment and clear all others
 *
 *  \note You have to call \ref LCD_Update() to trigger update on LCD if not
 *         it is triggered automatically at change of bitframe
 *
 *  \param seg No of the hour bar segment to be set 0-23
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
#if 0
void LCD_SetHourBarVal(uint8_t val, uint8_t mode)
{
    uint8_t i;
    // Only Segment 0:23
    if (val > 23){
        val = 23;
    }
    // For each Segment 0:23
    for (i=0; i<24; i++) {
        if (i == val){
            LCD_SetHourBarSeg(i, mode);
        } else {
            LCD_SetHourBarSeg(i, LCD_MODE_OFF);
        }
    }
}
#endif


/*!
 *******************************************************************************
 *  Clear LCD Display
 *
 *  \note Sets all Segments of the to \ref LCD_MODE_OFF
 ******************************************************************************/
#if 0
void LCD_ClearAll(void)
{
    LCD_AllSegments(LCD_MODE_OFF);
}
#endif

/*!
 *******************************************************************************
 *  Clear hour-bar 
 *
 *  \note Sets all Hour-Bar Segments to \ref LCD_MODE_OFF
 ******************************************************************************/
#if 0
void LCD_ClearHourBar(void)
{
    LCD_SetHourBarVal(23, LCD_MODE_OFF);
    LCD_Update();
}
#endif

/*!
 *******************************************************************************
 *  Clear all Symbols 
 *
 *  \note  Sets Symbols <tt> AUTO MANU PROG SUN MOON SNOW</tt>
 *         to \ref LCD_MODE_OFF
 ******************************************************************************/
#if 0
void LCD_ClearSymbols(void)
{
    LCD_SetSeg(LCD_SEG_AUTO, LCD_MODE_OFF);
    LCD_SetSeg(LCD_SEG_MANU, LCD_MODE_OFF);
    LCD_SetSeg(LCD_SEG_PROG, LCD_MODE_OFF);
    LCD_SetSeg(LCD_SEG_SUN, LCD_MODE_OFF);
    LCD_SetSeg(LCD_SEG_MOON, LCD_MODE_OFF);
    LCD_SetSeg(LCD_SEG_SNOW, LCD_MODE_OFF);

    LCD_Update();
}
#endif

/*!
 *******************************************************************************
 *  Clear all 7 segment fields
 *
 *  \note  Sets the four 7 Segment and the Columns to \ref LCD_MODE_OFF
 ******************************************************************************/
#if 0
void LCD_ClearNumbers(void)
{
    LCD_PrintChar(LCD_CHAR_NULL, 3, LCD_MODE_OFF);
    LCD_PrintChar(LCD_CHAR_NULL, 2, LCD_MODE_OFF);
    LCD_PrintChar(LCD_CHAR_NULL, 1, LCD_MODE_OFF);
    LCD_PrintChar(LCD_CHAR_NULL, 0, LCD_MODE_OFF);
    LCD_SetSeg(LCD_SEG_COL1, LCD_MODE_OFF);
    LCD_SetSeg(LCD_SEG_COL2, LCD_MODE_OFF);

    LCD_Update();
}
#endif

/*!
 *******************************************************************************
 *  Set segment of LCD
 *
 *  \note  You have to call \ref LCD_Update() to trigger update on LCD if not
 *         it is triggered automatically at change of bitframe
 *
 *  \param seg No of the segment to be set see \ref LCD_SEG_B0 ...
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_SetSeg(uint8_t seg, uint8_t mode)
{
    LCD_SetSegReg(seg / 8, 1<<(seg % 8), mode);
}

/*!
 *******************************************************************************
 *  Set segment of LCD
 *
 *  \note  You have to call \ref LCD_Update() to trigger update on LCD if not
 *         it is triggered automatically at change of bitframe
 *
 *  \param Register = segment DIV 8 to be set see \ref LCD_SEG_B0 ...
 *  \param Bitposition = segment mod 8
 *  \param mode  \ref LCD_MODE_ON, \ref LCD_MODE_OFF, \ref LCD_MODE_BLINK_1
 ******************************************************************************/
void LCD_SetSegReg(uint8_t r, uint8_t b, uint8_t mode)
{
    // Set bits in each bitplane
	#if LCD_BITPLANES == 2
        if (mode & 1){
            // Set Bit in Bitplane if ON (0b11) or Blinkmode 1 (0b01)
            LCD_Data[0][r] |= b;
        } else {
            // Clear Bit in Bitplane if OFF (0b00) or Blinkmode 2 (0b10)
            LCD_Data[0][r] &= ~b;
        } 
        if (mode & 2){
            // Set Bit in Bitplane if ON (0b11) or Blinkmode 2 (0b10)
            LCD_Data[1][r] |= b;
        } else {
            // Clear Bit in Bitplane if OFF (0b00) or Blinkmode 1 (0b01)
            LCD_Data[1][r] &= ~b;
        } 
    #else
      {
        uint8_t bp;
        for (bp=0; bp<LCD_BITPLANES;  bp++){
            if (mode & (1<<bp)){
                // Set Bit in Bitplane if ON (0b11) or Blinkmode 1 (0b01)
                LCD_Data[bp][r] |= b;
            } else {
                // Clear Bit in Bitplane if OFF (0b00) or Blinkmode 2 (0b10)
                LCD_Data[bp][r] &= ~b;
            }
        }
      }
    #endif
	LCD_calc_used_bitplanes(mode);
}

/*!
 *******************************************************************************
 *  Calculate used bitplanes
 *
 *	\note used only for update LCD, in any other cases intterupt is disabled
 *  \note copy LCD_Data to LCDREG
 *
 ******************************************************************************/
static void LCD_calc_used_bitplanes(uint8_t mode) {
    uint8_t i;
	if ((mode==LCD_MODE_BLINK_1)||(mode==LCD_MODE_BLINK_2)) {
		LCD_used_bitplanes=2;
		return; // just optimalization
	} 
	// mode must be LCD_MODE_ON or LCD_MODE_OFF
	if (LCD_used_bitplanes==1) {
		return; // just optimalization, nothing to do
	} 

    for (i=0; i<LCD_REGISTER_COUNT; i++){
		#if LCD_BITPLANES != 2
			#error optimized for 2 bitplanes // TODO?
		#endif
		if (LCD_Data[0][i] != LCD_Data[1][i]) {
			LCD_used_bitplanes=2;
			return; // it is done
		}
	}
	LCD_used_bitplanes=1;
}


/*!
 *******************************************************************************
 *
 *	LCD_BlinkCounter and LCD_Bitplane for LCD blink
 *
 ******************************************************************************/
static uint8_t LCD_BlinkCounter;   //!< \brief counter for bitplane change
static uint8_t LCD_Bitplane;       //!< \brief currently active bitplane
uint8_t LCD_force_update=0;        //!< \brief force update LCD


/*!
 *******************************************************************************
 *  LCD Interrupt Routine
 *
 *	\note used only for update LCD, in any other cases intterupt is disabled
 *  \note copy LCD_Data to LCDREG
 *
 ******************************************************************************/

void task_lcd_update(void) {
    if (++LCD_BlinkCounter > LCD_BLINK_FRAMES){
		#if LCD_BITPLANES == 2
			// optimized version for LCD_BITPLANES == 2
			LCD_Bitplane = (LCD_Bitplane +1) & 1;
		#else
			LCD_Bitplane = (LCD_Bitplane +1) % LCD_BITPLANES;
		#endif
        LCD_BlinkCounter=0;
		LCD_force_update=1;
    }


	if (LCD_force_update) {
		LCD_force_update=0;
		// Copy desired segment buffer to the real segments
    	LCDDR0 = LCD_Data[LCD_Bitplane][0];
    	LCDDR1 = LCD_Data[LCD_Bitplane][1];
    	LCDDR2 = LCD_Data[LCD_Bitplane][2];
    	LCDDR5 = LCD_Data[LCD_Bitplane][3];
    	LCDDR6 = LCD_Data[LCD_Bitplane][4];
    	LCDDR7 = LCD_Data[LCD_Bitplane][5];
    	LCDDR10 = LCD_Data[LCD_Bitplane][6];
    	LCDDR11 = LCD_Data[LCD_Bitplane][7];
    	LCDDR12 = LCD_Data[LCD_Bitplane][8];
#ifdef HR25
    	LCDDR15 = LCD_Data[LCD_Bitplane][9];
    	LCDDR16 = LCD_Data[LCD_Bitplane][10];
    	LCDDR17 = LCD_Data[LCD_Bitplane][11];
#endif
	}



	if (LCD_used_bitplanes == 1) {
		// only one bitplane used, no blinking
    	// Updated; disable LCD start of frame interrupt
    	LCDCRA &= ~(1<<LCDIE);
	}
}

/*!
 *******************************************************************************
 *  LCD Interrupt Routine
 *
 *	\note used only for update LCD, in any other cases intterupt is disabled
 *  \note copy LCD_Data to LCDREG
 *
 ******************************************************************************/
#if ! TASK_IS_SFR
// not optimized
ISR(LCD_vect) {
    task |= TASK_LCD;
}
#else
// optimized
ISR_NAKED ISR (LCD_vect) {
    asm volatile(
        // prologue and epilogue is not needed, this code  not touch flags in SREG
        "	sbi %0,%1" "\t\n"
        "	reti" "\t\n"
        ::"I" (_SFR_IO_ADDR(task)) , "I" (TASK_LCD_BIT)
    );
}
#endif 
