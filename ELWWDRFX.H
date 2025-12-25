/*****************************************************************************
 *   ELWWDRFX.H   V0.62                                 Worlds of Darkness   *
 *   RIP Support Defines                                                     *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 06/27/1995         *
 *                   WG3.2+                        - R. Hadsall 02/25/2021   *
 *                   MBBS V10                      - R. Hadsall 12/23/2025   *
 *                                                                           *
 * Copyright (C) 2005-2025 Rick Hadsall.  All Rights Reserved.               *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      * 
 * it under the terms of the GNU Affero General Public License as published  *
 * by the Free Software Foundation, either version 3 of the License, or      *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.     *
 *                                                                           *
 * Additional Terms for Contributors:                                        *
 * 1. By contributing to this project, you agree to assign all right, title, *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies.                              *
 * 2. You grant Rick Hadsall and Elwynor Technologies a non-exclusive,       *
 *    royalty-free, worldwide license to use, reproduce, prepare derivative  *
 *    works of, publicly display, publicly perform, sublicense, and          *
 *    distribute your contributions                                          *
 * 3. You represent that you have the legal right to make your contributions *
 *    and that the contributions do not infringe any third-party rights.     *
 * 4. Rick Hadsall and Elwynor Technologies are not obligated to incorporate *
 *    any contributions into the project.                                    *
 * 5. This project is licensed under the AGPL v3, and any derivative works   *
 *    must also be licensed under the AGPL v3.                               *
 * 6. If you create an entirely new project (a fork) based on this work, it  *
 *    must also be licensed under the AGPL v3, you assign all right, title,  *
 *    and interest, including all copyrights, in and to your contributions   *
 *    to Rick Hadsall and Elwynor Technologies, and you must include these   *
 *    additional terms in your project's LICENSE file(s).                    *
 *                                                                           *
 * By contributing to this project, you agree to these terms.                *
 *                                                                           *
 *****************************************************************************/

#ifndef RIP2C_HEADER_H
#define RIP2C_HEADER_H

/***************************************************************************/
/*    The following variables are "private" to the library.  You should    */
/*    not have to interface with them directly under most circumstances    */
/***************************************************************************/

extern  CHAR tbuff[1540];       /* temp storage for RIP string             */
extern  VOID (*rip_output_fn)(CHAR *);  /* Used for custom cmd processing  */
extern  CHAR LNF[128];          /* Line-Feed (end of line) string          */
extern  CHAR RIC[128];          /* RIP introducer string (default="!")     */



/***************************************************************************/
/*      The following #define's are general constants used throughout      */
/***************************************************************************/

#define MAX_POLYPOINTS  512     /* Maximum number of poly point parameters */
#define POLYPOINTS_BUF  2100    /* Poly point character buffer size        */
#define MAX_X           640     /* Number of pixel columns                 */
#define MAX_Y           350     /* Number of pixel lines                   */

#define rEXCLAMATION    "!"     /* Character to introduce RIPscrip code    */
#define rCTRL_A         "\01"   /* Secondary char to introduce RIPscrip    */
#define rCTRL_B         "\02"   /* Third char to introduce RIPscrip code   */



/***************************************************************************/
/*   The following 3 macros pick-apart an EGA color palette and generate   */
/*      the RED, GREEN and BLUE portions of the master color number        */
/***************************************************************************/

#define RED_PART(x)    ((((x)&0x04)>>1)|(((x)&0x20)>>5))
#define GREEN_PART(x)  ((((x)&0x02))   |(((x)&0x10)>>4))
#define BLUE_PART(x)   ((((x)&0x01)<<1)|(((x)&0x08)>>3))



/***************************************************************************/
/*  The following two define's are used for creating an EGA color palette  */
/*  entry number from three RGB components (each range 0-3).  In the real  */
/* world, you will never need to use VSHIFT() - it is only used by RGB2PAL */
/***************************************************************************/

#define VSHIFT(x)      ((((x)&0x02)>>1)|(((x)&0x01)<<3))
#define RGB2PAL(r,g,b) ((VSHIFT(r)<<2)|(VSHIFT(g)<<1)|VSHIFT(b))



/***************************************************************************/
/*                                  Colors                                 */
/***************************************************************************/
                                        /*                                 */
#define rBLACK                   0      /* Symbol for color Black          */
#define rBLUE                    1      /* Symbol for color Blue           */
#define rGREEN                   2      /* Symbol for color Green          */
#define rCYAN                    3      /* Symbol for color Cyan           */
#define rRED                     4      /* Symbol for color Red            */
#define rMAGENTA                 5      /* Symbol for color Magenta        */
#define rBROWN                   6      /* Symbol for color Brown          */
#define rLIGHTGRAY               7      /* Symbol for color Light-Gray     */
#define rDARKGRAY                8      /* Symbol for color Dark-Gray      */
#define rLIGHTBLUE               9      /* Symbol for color Light-Blue     */
#define rLIGHTGREEN              10     /* Symbol for color Light-Green    */
#define rLIGHTCYAN               11     /* Symbol for color Light-Cyan     */
#define rLIGHTRED                12     /* Symbol for color Light-Red      */
#define rLIGHTMAGENTA            13     /* Symbol for color Light-Magenta  */
#define rYELLOW                  14     /* Symbol for color Yellow         */
#define rWHITE                   15     /* Symbol for color White          */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*       Font Sizes:  for calls to rip_text_window( size ) parameter       */
/***************************************************************************/
                                        /*                                 */
#define rFONT_8x8                0      /* System Font 0 - 80x43           */
#define rFONT_7x8                1      /* System Font 1 - 91x43           */
#define rFONT_8x14               2      /* System Font 2 - 80x25           */
#define rFONT_7x14               3      /* System Font 3 - 91x25           */
#define rFONT_16x14              4      /* System Font 4 - 40x25           */
                                        /*                                 */
                                        /***********************************/
                                        /*                                 */
#define rTEXT_CHOP               0      /* Text Window chops at border     */
#define rTEXT_WRAP               1      /* Text Window wraps at border     */
                                        /*                                 */
#define rNONE                    0      /* General "nothing here" value    */
#define rRESERVED                0      /* RESERVED PARAMETER STUB         */
                                        /*                                 */
/***************************************************************************/
/*  Font Direction used for rip_text(), rip_text_xy() & rip_font_style()   */
/***************************************************************************/
                                        /*                                 */
#define rHORIZONTAL              0      /* Text drawn horizontally         */
#define rVERTICAL                1      /* Text drawn vertically           */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*     Font Types used for rip_text(), rip_text_xy() & rip_font_style()    */
/***************************************************************************/
                                        /*                                 */
#define rDEFAULT_FONT            0      /* 8x8 font (bit-mapped)           */
#define rTRIPLEX_FONT            1      /* (scalable)                      */
#define rSMALL_FONT              2      /* (scalable)                      */
#define rSANS_SERIF_FONT         3      /* (scalable)                      */
#define rGOTHIC_FONT             4      /* (scalable)                      */
#define rSCRIPT_FONT             5      /* (scalable)                      */
#define rSIMPLEX_FONT            6      /* (scalable)                      */
#define rTRIPLEX_SCR_FONT        7      /* (scalable)                      */
#define rCOMPLEX_FONT            8      /* (scalable)                      */
#define rEUROPEAN_FONT           9      /* (scalable)                      */
#define rBOLD_FONT               10     /* (scalable)                      */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*     Font Sizes used for rip_text(), rip_text_xy() & rip_font_style()    */
/***************************************************************************/
                                        /*                                 */
#define rMAGNIFY_1               1      /* Default size                    */
#define rMAGNIFY_2               2      /* Magnification  2  (x2)          */
#define rMAGNIFY_3               3      /* Magnification  3  (x2)          */
#define rMAGNIFY_4               4      /* Magnification  4  (x4)          */
#define rMAGNIFY_5               5      /* Magnification  5  (x5)          */
#define rMAGNIFY_6               6      /* Magnification  6  (x6)          */
#define rMAGNIFY_7               7      /* Magnification  7  (x7)          */
#define rMAGNIFY_8               8      /* Magnification  8  (x8)          */
#define rMAGNIFY_9               9      /* Magnification  9  (x9)          */
#define rMAGNIFY_10              10     /* Magnification 10 (x10)          */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*           Line Style for the rip_line_style( style ) parameter          */
/***************************************************************************/
                                        /*                                 */
#define rNORMAL_LINE             0      /* Pat: 1111111111111111           */
#define rDOTTED_LINE             1      /* Pat: 0011001100110011           */
#define rCENTERED_LINE           2      /* Pat: 0001111000111111           */
#define rDASHED_LINE             3      /* Pat: 0001111100011111           */
#define rCUSTOM_PATTERN_LINE     4      /* 16 bit custom pattern           */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*     Line Thickness options for the rip_line_style(thick) parameter      */
/***************************************************************************/
                                        /*                                 */
#define rWIDTH_NORMAL            1      /* Lines are 1 pixel wide          */
#define rWIDTH_THICK             3      /* Lines are 3 pixels wide         */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*      Predefined patterns for the rip_fill_style(pattern) parameter      */
/***************************************************************************/
                                        /*                                 */
#define rFILL_BACKGROUND         0      /*             empty block         */
#define rFILL_SOLID              1      /* @@@@@@@@@@@ solid block         */
#define rFILL_LINE               2      /* ----------- thick lines         */
#define rFILL_LIGHT_SLASH        3      /* /  /  /  /  thick lines         */
#define rFILL_NORMAL_SLASH       4      /* // // // /  thick lines         */
#define rFILL_NORMAL_BACKSLASH   5      /* \\ \\ \\ \  thick lines         */
#define rFILL_LIGHT_BACKSLASH    6      /* \  \  \  \  thick lines         */
#define rFILL_LIGHT_HATCH        7      /* ##########  thick lines         */
#define rFILL_HEAVY_CROSS_HATCH  8      /* XXXXXXXXXX  thick lines         */
#define rFILL_INTERLEAVING_LINE  9      /* +-+-+-+-+-  thick lines         */
#define rFILL_WIDELY_SPACED_DOT  10     /* : . : .  :  pixels only         */
#define rFILL_CLOSELY_SPACED_DOT 11     /* ::::::::::  pixels only         */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*          Justify options for rip_region_text(justify) parameter         */
/***************************************************************************/
                                        /*                                 */
#define rJUSTIFY_LEFT            0      /* Left-justify only.              */
#define rJUSTIFY_RIGHT           1      /* Right/left margin justify       */
                                        /* except for last line of         */
                                        /* paragraph & indented lines      */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*    Options for rip_load_icon(mode) and rip_put_image(mode) parameters   */
/***************************************************************************/
                                        /*                                 */
#define rMODE_COPY               0      /* Paste the image normally        */
#define rMODE_XOR                1      /* Exclusive-OR with screen image  */
#define rMODE_OR                 2      /* Logically OR with screen image  */
#define rMODE_AND                3      /* Logically AND with screen image */
#define rMODE_NOT                4      /* Paste inverse with screen image */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*             Options for rip_load_icon(clipboard) parameter              */
/***************************************************************************/
                                        /*                                 */
#define rICON_PASTEONLY          0      /* Paste Icon on screen only       */
#define rICON_PASTECLIP          1      /* Paste on screen & on clipboard  */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*  Options for rip_mouse() for determining if region should be inverted   */
/***************************************************************************/
                                        /*                                 */
#define rINVERT_NO               0      /* Don't invert mouse region       */
#define rINVERT_YES              1      /* Do invert a mouse region        */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/* Used with rip_mouse() to determine if screen should be reset afterwards */
/***************************************************************************/
                                        /*                                 */
#define rRESET_NO                0      /* Don't reset windows when clicked*/
#define rRESET_YES               1      /* Do reset the windows at click   */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*  Options for rip_file_query(mode) parameter, which decides return value */
/***************************************************************************/
                                        /*                                 */
#define rFILE_NORMAL             0      /* EXISTS = "0" or "1"             */
#define rFILE_CR                 1      /* EXISTS <CR>                     */
#define rFILE_SIZE               2      /* EXISTS.SIZE <CR>                */
#define rFILE_EXTENDED           3      /* EXISTS.SIZE.DATE.TIME <CR>      */
#define rFILE_EXTFILENAME        4      /* EXISTS.FILE.SIZE.DATE.TIME <CR> */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*                 Options for rip_define(flags) parameter                 */
/*              NOTE: flags in this case can be OR'd together              */
/***************************************************************************/
                                        /*                                 */
#define rDEFINE_SAVE             1      /* Save to database                */
#define rDEFINE_FORCE_ANSWER     2      /* No blank responses              */
#define rDEFINE_NOT_INTERACTIVE  4      /* Non-interactive query           */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
#define rQUERY_NOW               0      /* Process Query NOW               */
#define rQUERY_GRAPHICS          1      /* Process with Graphics Click     */
#define rQUERY_TEXT              2      /* Process with Text Window Click  */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*             Options for rip_button_style(orient) parameter              */
/*              NOTE: flags in this case can be OR'd together              */
/***************************************************************************/
                                        /*                                 */
#define rLABEL_ABOVE             0      /* Display above button            */
#define rLABEL_LEFT              1      /* Display to left of button       */
#define rLABEL_CENTER            2      /* Diplay in center of button      */
#define rLABEL_RIGHT             3      /* Display to right of button      */
#define rLABEL_BELOW             4      /* Display beneath button          */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*             Options for rip_button_style(flags) parameter               */
/*   NOTE: flags in this case can be OR'd together. See pg 190 for table   */
/***************************************************************************/
                                        /*                                 */
#define rSTYLE_CLIPBOARD         1      /* Button is a clipboard button    */
#define rSTYLE_INVERTABLE        2      /* Button is "invertable"          */
#define rSTYLE_RESET             4      /* Reset screen after button click */
#define rSTYLE_CHISEL            8      /* Display chisel special effect   */
#define rSTYLE_RECESSED          16     /* Display recessed special effect */
#define rSTYLE_DROPSHADOW        32     /* Dropshadow the label (if any)   */
#define rSTYLE_IMAGE_TO_CLIP     64     /* Auto-stamp image onto clipboard */
#define rSTYLE_ICON              128    /* Button is an "Icon Button"      */
#define rSTYLE_PLAIN             256    /* Button is an "Plain Button"     */
#define rSTYLE_BEVEL             512    /* Display Bevel special effect    */
#define rSTYLE_MOUSE             1024   /* Button is a Mouse Button        */
#define rSTYLE_UNDERLINE         2048   /* Underline hte hot-key in label  */
#define rSTYLE_HOT_ICON          4096   /* Make Icon Button user Hot Icons */
#define rSTYLE_ADJ_VERTICAL      8192   /* Adj vertical centering of label */
#define rSTYLE_RADIO_GROUP       16384  /* Button belongs to a Radio Group */
#define rSTYLE_SUNKEN            32768U /* Display Sunken special effect   */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*             Options for rip_button_style(flags2) parameter              */
/*   NOTE: flags in this case can be OR'd together. See pg 190 for table   */
/***************************************************************************/
                                        /*                                 */
#define rSTYLE_CHECKBOX_GROUP    1      /* Button is in a Checkbox Group   */
#define rSTYLE_HILIGHT_HOTKEY    2      /* Hilight Hotkey character        */
#define rSTYLE_EXPLODE           4      /* Explode (Zoom Out when clicked) */
#define rSTYLE_LEFT_JUSTIFY      8      /* Left just label (top/ctr/bot)   */
#define rSTYLE_RIGHT_JUSTIFY     16     /* Right just label (top/ctr/bot)  */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*                 Options for rip_button(flags) parameter                 */
/***************************************************************************/
                                        /*                                 */
#define rBTN_UNSELECTED          0      /* Button is drawn unselected      */
#define rBTN_SELECTED            1      /* Button is drawn selected        */
#define rBTN_DEFAULT             2      /* Button is a default Button      */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*   Used with rip_enter_block_mode() to determine direction of transfer   */
/***************************************************************************/
                                        /*                                 */
#define rBLOCK_DOWNLOAD          0      /* Download block mode             */
#define rBLOCK_UPLOAD            1      /* Upload block mode               */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*   Used with rip_enter_block_mode() to determine the transfer protocol   */
/***************************************************************************/
                                        /*                                 */
#define rPROT_XMODEM             0      /* Block Mode: Xmodem (checksum)   */
#define rPROT_XMODEM_CRC         1      /* Block Mode: Xmodem-CRC          */
#define rPROT_XMODEM_1K          2      /* Block Mode: Xmodem-1K           */
#define rPROT_XMODEM_1K_G        3      /* Block Mode: Xmodem-1K (G)       */
#define rPROT_KERMIT             4      /* Block Mode: Kermit              */
#define rPROT_YMODEM             5      /* Block Mode: Ymodem (batch)      */
#define rPROT_YMODEM_G           6      /* Block Mode: Ymodem (G)          */
#define rPROT_ZMODEM             7      /* Block Mode: Zmodem              */
                                        /*                                 */
                                        /*                                 */
                                        /*                                 */
/***************************************************************************/
/*   Used with rip_enter_block_mode() to see what to do with recvd files   */
/***************************************************************************/
                                        /*                                 */
#define rBLOCK_NOMODE            0      /* For UPLOAD - Mode irrelevant    */
                                        /*                                 */
#define rBLOCK_RIP_SHOW          0      /* Receive RIP file and show       */
#define rBLOCK_RIP_STORE         1      /* Receive RIP file - store only   */
#define rBLOCK_ICON              2      /* Receive ICN file - store only   */
#define rBLOCK_HELP_FILE         3      /* Receive HLP file (obsolete)     */
#define rBLOCK_DYNAMIC_NOSHOW    4      /* Receive files - store only      */
#define rBLOCK_DYNAMIC_SHOW      5      /* Receive files - show if possible*/
                                        /*                                 */
/***************************************************************************/




/***************************************************************************/
/*                     Host Numeric conversion functions                   */
/***************************************************************************/
                                        /*                                 */
CHAR *mnI(USHORT num, SHORT outlen);    /* int    to Hexa-Tri-Decimal      */
CHAR *mnL(LONG     num, SHORT outlen);  /* long   to Hexa-Tri-Decimal      */
CHAR *AdjustString(CHAR *buf);          /* Adjust string for output        */
USHORT mtoI(CHAR *num, SHORT len);      /* Hexa-Tri-Decimal to Decimal     */
                                        /*                                 */
                                        /***********************************/



/***************************************************************************/
/*                        Special ANSI functions                           */
/***************************************************************************/

CHAR *rip_version(VOID);
CHAR *rip_proc_off(VOID);
CHAR *rip_proc_on(VOID);



/***************************************************************************/
/*                          Function Prototypes                            */
/***************************************************************************/

SHORT  rip_polypoints(SHORT npoints);

CHAR *rip_arc(SHORT x, SHORT y, SHORT st_ang, SHORT end_ang, SHORT radius);
CHAR *rip_bar(SHORT x0, SHORT y0, SHORT x1, SHORT y1);
CHAR *rip_begin_text(SHORT x1, SHORT y1, SHORT x2, SHORT y2, SHORT res);
CHAR *rip_bezier(SHORT x1, SHORT y1, SHORT x2, SHORT y2, SHORT x3, SHORT y3, SHORT x4, SHORT y4, SHORT cnt);
CHAR *rip_enter_block_mode(SHORT mode, SHORT proto, SHORT filetype, SHORT reserved, CHAR *filename);
CHAR *rip_button_style(SHORT wid, SHORT hgt, SHORT orient, SHORT flags, SHORT size, SHORT dfore, SHORT dback, SHORT bright, SHORT dark, SHORT surface, SHORT grp_no, SHORT flags2, SHORT uline_col, SHORT corner_col, SHORT res);
CHAR *rip_button(SHORT x0, SHORT y0, SHORT x1, SHORT y1, SHORT hotkey, SHORT flags, SHORT res, CHAR *text);
CHAR *rip_circle(SHORT x_center, SHORT y_center, SHORT radius);
CHAR *rip_color(SHORT color);
CHAR *rip_copy_region(SHORT x0, SHORT y0, SHORT x1, SHORT y1, SHORT res, SHORT dest_line);
CHAR *rip_define(SHORT flags, SHORT res, CHAR *text);
CHAR *rip_end_text(VOID);
CHAR *rip_erase_window(VOID);
CHAR *rip_erase_eol(VOID);
CHAR *rip_erase_view(VOID);
CHAR *rip_file_query(SHORT mode, SHORT res, CHAR *filename);
CHAR *rip_fill(SHORT x, SHORT y, SHORT border);
CHAR *rip_fill_pattern(SHORT c1, SHORT c2, SHORT c3, SHORT c4, SHORT c5, SHORT c6, SHORT c7, SHORT c8, SHORT color);
CHAR *rip_fill_style(SHORT pattern, SHORT color);
CHAR *rip_filled_oval(SHORT x_center, SHORT y_center, SHORT x_rad, SHORT y_rad);
CHAR *rip_font_style(SHORT font, SHORT direction, SHORT size, SHORT res);
CHAR *rip_get_image(SHORT x0, SHORT y0, SHORT x1, SHORT y1, SHORT res);
CHAR *rip_gotoxy(SHORT x1, SHORT y1);
CHAR *rip_home(VOID);
VOID set_rip_introducer(CHAR *intro_str);
CHAR *rip_kill_mouse_fields(VOID);
CHAR *rip_line(SHORT x0, SHORT y0, SHORT x1, SHORT y1);
CHAR *rip_line_style(SHORT style, USHORT user_pat, SHORT thick);
VOID set_rip_linefeed(CHAR *lf_str);
CHAR *rip_load_icon(SHORT x, SHORT y, SHORT mode, SHORT clipboard, SHORT scale, SHORT res, CHAR *filename);
CHAR *rip_mouse(SHORT num, SHORT x0, SHORT y0, SHORT x1, SHORT y1, SHORT clk, SHORT clr, SHORT res, CHAR *text);
CHAR *rip_move(SHORT x, SHORT y);
CHAR *rip_no_more(VOID);
CHAR *rip_one_palette(SHORT color, SHORT value);
CHAR *rip_oval_pie_slice(SHORT x, SHORT y, SHORT st_ang, SHORT end_ang, SHORT x_rad, SHORT y_rad);
CHAR *rip_oval(SHORT x, SHORT y, SHORT st_ang, SHORT end_ang, SHORT x_rad, SHORT y_rad);
CHAR *rip_oval_arc(SHORT x, SHORT y, SHORT st_ang, SHORT end_ang, SHORT x_rad, SHORT y_rad);
CHAR *rip_pie_slice(SHORT x, SHORT y, SHORT st_ang, SHORT end_ang, SHORT radius);
CHAR *rip_pixel(SHORT x, SHORT y);
CHAR *rip_read_scene(SHORT  res, CHAR *filename);
CHAR *rip_polygon(SHORT x, SHORT y);
CHAR *rip_polyline(SHORT x, SHORT y);
CHAR *rip_fill_poly(SHORT x, SHORT y);
CHAR *rip_put_image(SHORT x, SHORT y, SHORT mode, SHORT res);
CHAR *rip_query(SHORT mode, SHORT res, CHAR *text);
CHAR *rip_rectangle(SHORT x0, SHORT y0, SHORT x1, SHORT y1);
CHAR *rip_region_text(SHORT justify, CHAR *text);
CHAR *rip_reset_windows(VOID);
CHAR *rip_set_palette(SHORT c1,  SHORT c2,  SHORT c3,  SHORT c4, SHORT c5,  SHORT c6,  SHORT c7,  SHORT c8, SHORT c9,  SHORT c10, SHORT c11, SHORT c12, SHORT c13, SHORT c14, SHORT c15, SHORT c16);
CHAR *rip_text(CHAR *str);
CHAR *rip_text_window(SHORT x0, SHORT y0, SHORT x1, SHORT y1, SHORT wrap, SHORT size);
CHAR *rip_text_xy(SHORT x, SHORT y, CHAR *str);
CHAR *rip_viewport(SHORT x0, SHORT y0, SHORT x1, SHORT y1);
CHAR *rip_write_mode(SHORT mode);
CHAR *rip_write_icon(SHORT res, CHAR *filename);
CHAR *rip_output(CHAR *msg);



/***************************************************************************/
/*        Routines for the RIP2C library - customization routines          */
/***************************************************************************/

VOID set_rip_linefeed(CHAR *lf_str);
VOID set_rip_output_fn(VOID (*fn_ptr)(CHAR *));
VOID set_rip_introducer(CHAR *intro_str);



/***************************************************************************/
/*                       Useful Macros for simple tasks                    */
/***************************************************************************/

#define rip_disable_text_window() rip_text_window(0,0,0,0,0,0)
#define rip_disable_viewport()    rip_viewport(0,0,0,0)



/***************************************************************************/
/* The following #define's are used for quick and easy access to built-in  */
/* text variables (both DATA and ACTIVE).  It is not intended to replace   */
/* you using the RIP_QUERY command, but provides quick and easy ways of    */
/* accessing them from within your C program without having to remember    */
/* the text variables' names.                                              */
/***************************************************************************/

#define query_abbr_dow()     rip_query(rQUERY_NOW, rRESERVED, "\$ADOW\$")
#define query_am_pm()        rip_query(rQUERY_NOW, rRESERVED, "\$AMPM\$")
#define query_is_cursor_on() rip_query(rQUERY_NOW, rRESERVED, "\$CURSOR\$")
#define query_cursor_x()     rip_query(rQUERY_NOW, rRESERVED, "\$CURX\$")
#define query_cursor_y()     rip_query(rQUERY_NOW, rRESERVED, "\$CURY\$")
#define query_date()         rip_query(rQUERY_NOW, rRESERVED, "\$DATE\$")
#define query_date_time()    rip_query(rQUERY_NOW, rRESERVED, "\$DATETIME\$")
#define query_day_of_month() rip_query(rQUERY_NOW, rRESERVED, "\$DAY\$")
#define query_day_of_week()  rip_query(rQUERY_NOW, rRESERVED, "\$DOW\$")
#define query_day_of_year()  rip_query(rQUERY_NOW, rRESERVED, "\$DOY\$")
#define query_4_digit_year() rip_query(rQUERY_NOW, rRESERVED, "\$FYEAR\$")
#define query_hour()         rip_query(rQUERY_NOW, rRESERVED, "\$HOUR\$")
#define query_mouse_buts()   rip_query(rQUERY_NOW, rRESERVED, "\$M\$")
#define query_hour_24()      rip_query(rQUERY_NOW, rRESERVED, "\$MHOUR\$")
#define query_minutes()      rip_query(rQUERY_NOW, rRESERVED, "\$MIN\$")
#define query_month_name()   rip_query(rQUERY_NOW, rRESERVED, "\$MONTH\$")
#define query_month_num()    rip_query(rQUERY_NOW, rRESERVED, "\$MONTHNUM\$")
#define query_mouse_status() rip_query(rQUERY_NOW, rRESERVED, "\$MSTAT\$")
#define query_rip_version()  rip_query(rQUERY_NOW, rRESERVED, "\$RIPVER\$")
#define query_status_bar()   rip_query(rQUERY_NOW, rRESERVED, "\$STATBAR\$")
#define query_seconds()      rip_query(rQUERY_NOW, rRESERVED, "\$SEC\$")
#define query_time()         rip_query(rQUERY_NOW, rRESERVED, "\$TIME\$")
#define query_timezone()     rip_query(rQUERY_NOW, rRESERVED, "\$TIMEZONE\$")
#define query_text_font()    rip_query(rQUERY_NOW, rRESERVED, "\$TWFONT\$")
#define query_twin_height()  rip_query(rQUERY_NOW, rRESERVED, "\$TWH\$")
#define query_twin_active()  rip_query(rQUERY_NOW, rRESERVED, "\$TWIN\$")
#define query_twin_width()   rip_query(rQUERY_NOW, rRESERVED, "\$TWW\$")
#define query_twin_x0()      rip_query(rQUERY_NOW, rRESERVED, "\$TWX0\$")
#define query_twin_x1()      rip_query(rQUERY_NOW, rRESERVED, "\$TWX1\$")
#define query_twin_y0()      rip_query(rQUERY_NOW, rRESERVED, "\$TWY0\$")
#define query_twin_y1()      rip_query(rQUERY_NOW, rRESERVED, "\$TWY1\$")
#define query_weekday_num()  rip_query(rQUERY_NOW, rRESERVED, "\$WDAY\$")
#define query_week_sunday()  rip_query(rQUERY_NOW, rRESERVED, "\$WOY\$")
#define query_week_monday()  rip_query(rQUERY_NOW, rRESERVED, "\$WOYM\$")
#define query_mouse_x()      rip_query(rQUERY_NOW, rRESERVED, "\$X\$")
#define query_mouse_xy()     rip_query(rQUERY_NOW, rRESERVED, "\$XY\$")
#define query_full_mouse()   rip_query(rQUERY_NOW, rRESERVED, "\$XYM\$")
#define query_mouse_y()      rip_query(rQUERY_NOW, rRESERVED, "\$Y\$")
#define query_year()         rip_query(rQUERY_NOW, rRESERVED, "\$YEAR\$")

#define rip_sound_alarm()    rip_query(rQUERY_NOW, rRESERVED, "\$ALARM\$")
#define rip_run_app0()       rip_query(rQUERY_NOW, rRESERVED, "\$APP0\$")
#define rip_run_app1()       rip_query(rQUERY_NOW, rRESERVED, "\$APP1\$")
#define rip_run_app2()       rip_query(rQUERY_NOW, rRESERVED, "\$APP2\$")
#define rip_run_app3()       rip_query(rQUERY_NOW, rRESERVED, "\$APP3\$")
#define rip_run_app4()       rip_query(rQUERY_NOW, rRESERVED, "\$APP4\$")
#define rip_run_app5()       rip_query(rQUERY_NOW, rRESERVED, "\$APP5\$")
#define rip_run_app6()       rip_query(rQUERY_NOW, rRESERVED, "\$APP6\$")
#define rip_run_app7()       rip_query(rQUERY_NOW, rRESERVED, "\$APP7\$")
#define rip_run_app8()       rip_query(rQUERY_NOW, rRESERVED, "\$APP8\$")
#define rip_run_app9()       rip_query(rQUERY_NOW, rRESERVED, "\$APP9\$")
#define rip_sound_beep()     rip_query(rQUERY_NOW, rRESERVED, "\$BEEP\$")
#define rip_sound_blip()     rip_query(rQUERY_NOW, rRESERVED, "\$BLIP\$")
#define rip_cursor_off()     rip_query(rQUERY_NOW, rRESERVED, "\$COFF\$")
#define rip_cursor_on()      rip_query(rQUERY_NOW, rRESERVED, "\$CON\$")
#define rip_disable_twin()   rip_query(rQUERY_NOW, rRESERVED, "\$DTW\$")
#define rip_doorway_off()    rip_query(rQUERY_NOW, rRESERVED, "\$DWAYOFF\$")
#define rip_doorway_on()     rip_query(rQUERY_NOW, rRESERVED, "\$DWAYON\$")
#define rip_erase_gwin()     rip_query(rQUERY_NOW, rRESERVED, "\$EGW\$")
#define rip_erase_twin()     rip_query(rQUERY_NOW, rRESERVED, "\$ETW\$")
#define rip_hotkeys_off()    rip_query(rQUERY_NOW, rRESERVED, "\$HKEYOFF\$")
#define rip_hotkeys_on()     rip_query(rQUERY_NOW, rRESERVED, "\$HKEYON\$")
#define rip_kill_fields()    rip_query(rQUERY_NOW, rRESERVED, "\$MKILL\$")
#define rip_sound_music()    rip_query(rQUERY_NOW, rRESERVED, "\$MUSIC\$")
#define rip_paste_clip()     rip_query(rQUERY_NOW, rRESERVED, "\$PCB\$")
#define rip_restore_clip()   rip_query(rQUERY_NOW, rRESERVED, "\$RCB\$")
#define rip_sound_phaser()   rip_query(rQUERY_NOW, rRESERVED, "\$PHASER\$")
#define rip_reset()          rip_query(rQUERY_NOW, rRESERVED, "\$RESET\$")
#define rip_restore_scrn()   rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE\$")
#define rip_restore_scrn0()  rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE0\$")
#define rip_restore_scrn1()  rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE1\$")
#define rip_restore_scrn2()  rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE2\$")
#define rip_restore_scrn3()  rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE3\$")
#define rip_restore_scrn4()  rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE4\$")
#define rip_restore_scrn5()  rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE5\$")
#define rip_restore_scrn6()  rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE6\$")
#define rip_restore_scrn7()  rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE7\$")
#define rip_restore_scrn8()  rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE8\$")
#define rip_restore_scrn9()  rip_query(rQUERY_NOW, rRESERVED, "\$RESTORE9\$")
#define rip_restore_all()    rip_query(rQUERY_NOW, rRESERVED, "\$RESTOREALL\$")
#define rip_sound_rphaser()  rip_query(rQUERY_NOW, rRESERVED, "\$REVPHASER\$")
#define rip_restore_fields() rip_query(rQUERY_NOW, rRESERVED, "\$RMF\$")
#define rip_restore_twin()   rip_query(rQUERY_NOW, rRESERVED, "\$RTW\$")
#define rip_save_scrn()      rip_query(rQUERY_NOW, rRESERVED, "\$SAVE\$")
#define rip_save_scrn0()     rip_query(rQUERY_NOW, rRESERVED, "\$SAVE0\$")
#define rip_save_scrn1()     rip_query(rQUERY_NOW, rRESERVED, "\$SAVE1\$")
#define rip_save_scrn2()     rip_query(rQUERY_NOW, rRESERVED, "\$SAVE2\$")
#define rip_save_scrn3()     rip_query(rQUERY_NOW, rRESERVED, "\$SAVE3\$")
#define rip_save_scrn4()     rip_query(rQUERY_NOW, rRESERVED, "\$SAVE4\$")
#define rip_save_scrn5()     rip_query(rQUERY_NOW, rRESERVED, "\$SAVE5\$")
#define rip_save_scrn6()     rip_query(rQUERY_NOW, rRESERVED, "\$SAVE6\$")
#define rip_save_scrn7()     rip_query(rQUERY_NOW, rRESERVED, "\$SAVE7\$")
#define rip_save_scrn8()     rip_query(rQUERY_NOW, rRESERVED, "\$SAVE8\$")
#define rip_save_scrn9()     rip_query(rQUERY_NOW, rRESERVED, "\$SAVE9\$")
#define rip_save_all()       rip_query(rQUERY_NOW, rRESERVED, "\$SAVEALL\$")
#define rip_status_off()     rip_query(rQUERY_NOW, rRESERVED, "\$SBAROFF\$")
#define rip_status_on()      rip_query(rQUERY_NOW, rRESERVED, "\$SBARON\$")
#define rip_save_clip()      rip_query(rQUERY_NOW, rRESERVED, "\$SCB\$")
#define rip_save_fields()    rip_query(rQUERY_NOW, rRESERVED, "\$SMF\$")
#define rip_save_twin()      rip_query(rQUERY_NOW, rRESERVED, "\$STW\$")
#define rip_tab_fields_off() rip_query(rQUERY_NOW, rRESERVED, "\$TABOFF\$")
#define rip_tab_fields_on()  rip_query(rQUERY_NOW, rRESERVED, "\$TABON\$")
#define rip_vt102_off()      rip_query(rQUERY_NOW, rRESERVED, "\$VT102OFF\$")
#define rip_vt102_on()       rip_query(rQUERY_NOW, rRESERVED, "\$VT102ON\$")

#endif    /* RIP2C_HEADER_H */
