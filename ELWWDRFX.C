/*****************************************************************************
 *   ELWWDRFX.C   V0.62                                 Worlds of Darkness   *
 *   RIP Support Routines                                                    *
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

#include "gcomm.h"
#include "elwwdrfx.h"

VOID(*rip_output_fn)(CHAR*) = NULL;

CHAR LNF[128] = "\n";
CHAR RIC[128] = rEXCLAMATION;

CHAR tbuff[1540];

/***************************************************************************/
/*  The following variables/define's are used for number conversion stuff  */
/***************************************************************************/

#define QLEN          10
#define MaxQue        20
#define MegaNumBase   36
#define MegaNumBaseL  36L

CHAR   cvrtTMPBUF[50];
CHAR* cvrtBUFFER = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

static SHORT  curbufpos = 0;
static SHORT  length = 0;

static CHAR cBUF[QLEN * MaxQue];


#define maxcols  76                 /* Maximum # of characters on a line   */

static SHORT PolyPoints = 0;     /* Set in rPolyPoints() and used by    */
/* rPolygon() and rPolyFill().         */
static SHORT PolyPointsRcv = 0;     /* # calls to rPolygon/rPolyFill since */
/* last call to rPolyPoints.           */
static SHORT PolyLen = 0;     /* Number of used bytes in buffer.     */
static SHORT PolyCol = 0;     /* Current column position in buffer.  */

static CHAR polybuf[POLYPOINTS_BUF + 1 + 256]; /* Poly point character buffer  */

/***************************************************************************/
/*      Transform special characters in text string for proper output      */
/***************************************************************************/

static CHAR xbuf[1025];

CHAR* AdjustString(CHAR* buf)
{
    CHAR* ptr = buf, * xptr = xbuf;

    // rip_banner();

    memset(xbuf, 0, 1025);

    while (*ptr) {
        if (*ptr == '\\' ||
            *ptr == '|' ||
            *ptr == '!' ||
            *ptr == 0x02 ||
            *ptr == 0x01) {

            *(xptr++) = '\\';
        }
        *(xptr++) = *(ptr++);
    }

    *xptr = '\0';

    return(xbuf);
}

CHAR* rip_arc(SHORT x,
    SHORT y,
    SHORT st_ang,
    SHORT end_ang,
    SHORT radius)
{
    // rip_banner();

    sprintf(tbuff, "!|A%s%s%s%s%s%s",
        mnI(x, 2),
        mnI(y, 2),
        mnI(st_ang, 2),
        mnI(end_ang, 2),
        mnI(radius, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_bar(SHORT x0,
    SHORT y0,
    SHORT x1,
    SHORT y1)
{
    // rip_banner();

    sprintf(tbuff, "%s|B%s%s%s%s%s",
        RIC,
        mnI(x0, 2),
        mnI(y0, 2),
        mnI(x1, 2),
        mnI(y1, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_begin_text(SHORT x1,
    SHORT y1,
    SHORT x2,
    SHORT y2,
    SHORT res)
{
    // rip_banner();

    sprintf(tbuff, "%s|1T%s%s%s%s%s%s",
        RIC,
        mnI(x1, 2),
        mnI(y1, 2),
        mnI(x2, 2),
        mnI(y2, 2),
        mnI(res, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_bezier(SHORT x1, SHORT y1,
    SHORT x2, SHORT y2,
    SHORT x3, SHORT y3,
    SHORT x4, SHORT y4,
    SHORT cnt)
{
    // rip_banner();

    sprintf(tbuff, "%s|Z%s%s%s%s%s%s%s%s%s%s",
        RIC,
        mnI(x1, 2),
        mnI(y1, 2),
        mnI(x2, 2),
        mnI(y2, 2),
        mnI(x3, 2),
        mnI(y3, 2),
        mnI(x4, 2),
        mnI(y4, 2),
        mnI(cnt, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_enter_block_mode(SHORT   mode,
    SHORT   proto,
    SHORT   filetype,
    SHORT   reserved,
    CHAR* filename)
{
    // rip_banner();

    if (!filename || !strlen(filename)) {
        filename = "<>";
    }

    sprintf(tbuff, "%s|9\33%s%s%s%s%s%s",
        RIC,
        mnI(mode, 1),
        mnI(proto, 1),
        mnI(filetype, 2),
        mnI(reserved, 4),
        AdjustString(filename),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_button_style(SHORT wid,
    SHORT hgt,
    SHORT orient,
    SHORT flags,
    SHORT size,
    SHORT dfore,
    SHORT dback,
    SHORT bright,
    SHORT dark,
    SHORT surface,
    SHORT grp_no,
    SHORT flags2,
    SHORT uline_col,
    SHORT corner_col,
    SHORT res)
{
    // rip_banner();

    sprintf(tbuff, "%s|1B%s%s%s%s%s" "%s%s%s%s%s" "%s%s%s%s" "%s%s",
        RIC,
        mnI(wid, 2),
        mnI(hgt, 2),
        mnI(orient, 2),
        mnI(flags, 4),
        mnI(size, 2),

        mnI(dfore, 2),
        mnI(dback, 2),
        mnI(bright, 2),
        mnI(dark, 2),
        mnI(surface, 2),

        mnI(grp_no, 2),
        mnI(flags2, 2),
        mnI(uline_col, 2),
        mnI(corner_col, 2),

        mnI(res, 6),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_button(SHORT  x0,
    SHORT  y0,
    SHORT  x1,
    SHORT  y1,
    SHORT  hotkey,
    SHORT  flags,
    SHORT  res,
    CHAR* text)
{
    // rip_banner();

    sprintf(tbuff, "%s|1U%s%s%s%s%s%s%s%s%s",
        RIC,
        mnI(x0, 2),
        mnI(y0, 2),
        mnI(x1, 2),
        mnI(y1, 2),
        mnI(hotkey, 2),
        mnI(flags, 1),
        mnI(res, 1),
        AdjustString(text),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_circle(SHORT x_center,
    SHORT y_center,
    SHORT radius)
{
    // rip_banner();

    sprintf(tbuff, "%s|C%s%s%s%s",
        RIC,
        mnI(x_center, 2),
        mnI(y_center, 2),
        mnI(radius, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_color(SHORT rcolor)
{
    // rip_banner();

    sprintf(tbuff, "%s|c%s%s",
        RIC,
        mnI(rcolor, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_copy_region(SHORT x0,
    SHORT y0,
    SHORT x1,
    SHORT y1,
    SHORT res,
    SHORT dest_line)
{
    // rip_banner();

    sprintf(tbuff, "%s|1G%s%s%s%s%s%s%s",
        RIC,
        mnI(x0, 2),
        mnI(y0, 2),
        mnI(x1, 2),
        mnI(y1, 2),
        mnI(res, 2),
        mnI(dest_line, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_define(SHORT   flags,
    SHORT   res,
    CHAR* text)
{
    // rip_banner();

    sprintf(tbuff, "%s|1D%s%s%s%s",
        RIC,
        mnI(flags, 3),
        mnI(res, 2),
        AdjustString(text),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_end_text(VOID)
{
    // rip_banner();

    sprintf(tbuff, "%s|1E%s", RIC, LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_erase_window(VOID)
{
    // rip_banner();

    sprintf(tbuff, "%s|e%s", RIC, LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_erase_eol(VOID)
{
    // rip_banner();

    sprintf(tbuff, "%s|>%s", RIC, LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_erase_view(VOID)
{
    // rip_banner();

    sprintf(tbuff, "%s|E%s", RIC, LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_file_query(SHORT   mode,
    SHORT   res,
    CHAR* filename)
{
    // rip_banner();

    sprintf(tbuff, "%s|1F%s%s%s%s",
        RIC,
        mnI(mode, 2),
        mnI(res, 4),
        AdjustString(filename),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_fill(SHORT x,
    SHORT y,
    SHORT border)
{
    // rip_banner();

    sprintf(tbuff, "%s|F%s%s%s%s",
        RIC,
        mnI(x, 2),
        mnI(y, 2),
        mnI(border, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_fill_pattern(SHORT c1,
    SHORT c2,
    SHORT c3,
    SHORT c4,
    SHORT c5,
    SHORT c6,
    SHORT c7,
    SHORT c8,
    SHORT rcolor)
{
    // rip_banner();

    sprintf(tbuff, "%s|s%s%s%s%s%s%s%s%s%s%s",
        RIC,
        mnI(c1, 2),
        mnI(c2, 2),
        mnI(c3, 2),
        mnI(c4, 2),
        mnI(c5, 2),
        mnI(c6, 2),
        mnI(c7, 2),
        mnI(c8, 2),
        mnI(rcolor, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_fill_style(SHORT pattern,
    SHORT rcolor)
{
    // rip_banner();

    sprintf(tbuff, "%s|S%s%s%s",
        RIC,
        mnI(pattern, 2),
        mnI(rcolor, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_filled_oval(SHORT x_center,
    SHORT y_center,
    SHORT x_rad,
    SHORT y_rad)
{
    // rip_banner();

    sprintf(tbuff, "%s|o%s%s%s%s%s",
        RIC,
        mnI(x_center, 2),
        mnI(y_center, 2),
        mnI(x_rad, 2),
        mnI(y_rad, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_font_style(SHORT font,
    SHORT direction,
    SHORT size,
    SHORT res)
{
    // rip_banner();

    sprintf(tbuff, "%s|Y%s%s%s%s%s",
        RIC,
        mnI(font, 2),
        mnI(direction, 2),
        mnI(size, 2),
        mnI(res, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_get_image(SHORT x0,
    SHORT y0,
    SHORT x1,
    SHORT y1,
    SHORT res)
{
    // rip_banner();

    sprintf(tbuff, "%s|1C%s%s%s%s%s%s",
        RIC,
        mnI(x0, 2),
        mnI(y0, 2),
        mnI(x1, 2),
        mnI(y1, 2),
        mnI(res, 1),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_gotoxy(SHORT x1,
    SHORT y1)
{
    // rip_banner();

    sprintf(tbuff, "%s|g%s%s%s",
        RIC,
        mnI(x1, 2),
        mnI(y1, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_home(VOID)
{
    // rip_banner();

    sprintf(tbuff, "%s|H%s", RIC, LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

VOID set_rip_introducer(CHAR* intro_str)
{
    // rip_banner();

    memset(RIC, 0, 128);
    strncpy(RIC, intro_str, 127);
}

CHAR* rip_kill_mouse_fields(VOID)
{
    // rip_banner();

    sprintf(tbuff, "%s|1K%s", RIC, LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_line(SHORT x0,
    SHORT y0,
    SHORT x1,
    SHORT y1)
{
    // rip_banner();

    sprintf(tbuff, "%s|L%s%s%s%s%s",
        RIC,
        mnI(x0, 2),
        mnI(y0, 2),
        mnI(x1, 2),
        mnI(y1, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_line_style(SHORT style,
    USHORT user_pat,
    SHORT thick)
{
    // rip_banner();

    sprintf(tbuff, "%s|=%s%s%s%s",
        RIC,
        mnI(style, 2),
        mnI(user_pat, 4),
        mnI(thick, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

VOID set_rip_linefeed(CHAR* lf_str)
{
    // rip_banner();

    memset(LNF, 0, 128);

    strncpy(LNF, lf_str, 127);
}

CHAR* rip_load_icon(SHORT   x,
    SHORT   y,
    SHORT   mode,
    SHORT   clipboard,
    SHORT   scale,
    SHORT   res,
    CHAR* filename)
{

    sprintf(tbuff, "%s|1I%s%s%s%s%s%s%s%s",
        RIC,
        mnI(x, 2),
        mnI(y, 2),
        mnI(mode, 2),
        mnI(clipboard, 1),
        mnI(scale, 1),
        mnI(res, 1),
        AdjustString(filename),
        LNF); // RH: Added an additional %s to the end of the format string but unsure if that will work or screw it up, but there were too many arguments for the string prior.

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

/***********************************************************************/
/* Convert a decimal to Hexa-Tri-Decimal alias, Mega Number (base 36). */
/***********************************************************************/


CHAR* mnI(USHORT num,
    SHORT      outlen)
{
    CHAR* c;
    USHORT cvrt, remainder;
    SHORT      len;

    length = (num < MegaNumBase) ? 1 :
        (num < 1296) ? 2 :
        (num < 46656L) ? 3 : 4;

    /*********************************************************/
    /* Use a que so sprintf() will work with multiple calls! */
    /*********************************************************/

    c = cBUF + curbufpos * QLEN;

    if (outlen >= QLEN) {
        outlen = QLEN - 1;
    }

    len = (outlen < length) ? length : outlen;

    c[len--] = '\0';

    while (len && num >= MegaNumBase) {                  /* Get right digits */
        cvrt = num / MegaNumBase;
        remainder = num - cvrt * MegaNumBase;
        num = cvrt;
        c[len--] = cvrtBUFFER[remainder];
    }

    c[len--] = cvrtBUFFER[num];                     /* Get leftmost digit */

    while (len >= 0) {                  /* Force leading zeros if needed. */
        c[len--] = '0';
    }

    c[outlen] = '\0';                           /* Truncate if necessary. */

    if (++curbufpos == MaxQue) {                            /* reset que. */
        curbufpos = 0;
    }

    return(c);
}

/********************************************************************/
/* Convert a long to Hexa-Tri-Decimal alias, Mega Number (base 36). */
/********************************************************************/

CHAR* mnL(LONG num,
    SHORT outlen)
{
    CHAR* c;
    LONG cvrt, remainder;
    SHORT  len;


    // rip_banner();

    /*********************************************************/
    /* Use a que so sprintf() will work with multiple calls! */
    /*********************************************************/

    c = cBUF + curbufpos * QLEN;

    length = (num < MegaNumBaseL) ? 1 :
        (num < 1296L) ? 2 :
        (num < 46656L) ? 3 :
        (num < 1679616L) ? 4 : 5;

    if (outlen >= QLEN) {
        outlen = QLEN - 1;
    }

    len = (outlen < length) ? length : outlen;
    c[len--] = '\0';

    while (len && num >= MegaNumBaseL) {                 /* Get first digits */
        cvrt = num / MegaNumBaseL;
        remainder = num - cvrt * MegaNumBaseL;
        num = cvrt;
        c[len--] = cvrtBUFFER[(SHORT)remainder];
    }

    c[len--] = cvrtBUFFER[(SHORT)num];              /* Get leftmost digit */

    while (len >= 0) {                  /* Force leading zeros if needed. */
        c[len--] = '0';
    }

    c[outlen] = '\0';                           /* Truncate if necessary. */

    if (++curbufpos == MaxQue) {                            /* reset que. */
        curbufpos = 0;
    }

    return(c);
}

/*********************************************************************/
/* Convert Hexa-Tri-Decimal alias, Mega Number (base 36) to decimal. */
/*********************************************************************/

USHORT mtoI(CHAR* num,
    SHORT   len)
{
    CHAR* ch = num;
    SHORT i, column = MegaNumBase;
    LONG cvrt; //=-1L;


    // rip_banner();

    for (i = 0; i < len; i++) {
        if (*ch == ' ') {                  /* Replace any spaces with 0 */
            *ch = '0';
        }
    }

    for (i = 0, cvrt = 0L; len; len--, i++) {
        if ((ch = strchr(cvrtBUFFER, (SHORT)num[len - 1])) == NULL) {
            cvrt = -1L;
            break;
        }

        if (!i) {
            cvrt = (LONG)(ch - cvrtBUFFER);
        } else {
            cvrt += (LONG)(ch - cvrtBUFFER) * column;
            column *= column;
        }
    }

    return((USHORT)cvrt);
}

CHAR* rip_mouse(SHORT num,
    SHORT x0,
    SHORT y0,
    SHORT x1,
    SHORT y1,
    SHORT clk,
    SHORT clr,
    SHORT res,
    CHAR* text)
{
    // rip_banner();

    sprintf(tbuff, "%s|1M%s%s%s%s%s%s%s%s%s%s",
        RIC,
        mnI(num, 2),
        mnI(x0, 2),
        mnI(y0, 2),
        mnI(x1, 2),
        mnI(y1, 2),
        mnI(clk, 1),
        mnI(clr, 1),
        mnI(res, 5),
        AdjustString(text),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_move(SHORT x,
    SHORT y)
{
    // rip_banner();

    sprintf(tbuff, "%s|m%s%s%s",
        RIC,
        mnI(x, 2),
        mnI(y, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_no_more(VOID)
{
    // rip_banner();

    sprintf(tbuff, "%s|#%s", RIC, LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_one_palette(SHORT rcolor,
    SHORT value)
{
    // rip_banner();

    sprintf(tbuff, "%s|a%s%s%s",
        RIC,
        mnI(rcolor, 2),
        mnI(value, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_oval_pie_slice(SHORT x,
    SHORT y,
    SHORT st_ang,
    SHORT end_ang,
    SHORT x_rad,
    SHORT y_rad)
{
    // rip_banner();

    sprintf(tbuff, "%s|i%s%s%s%s%s%s%s",
        RIC,
        mnI(x, 2),
        mnI(y, 2),
        mnI(st_ang, 2),
        mnI(end_ang, 2),
        mnI(x_rad, 2),
        mnI(y_rad, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

VOID set_rip_output_fn(VOID(*fn_ptr)(CHAR*))
{
    // rip_banner();

    rip_output_fn = fn_ptr;
}

CHAR* rip_output(CHAR* msg)
{
    // rip_banner();

    if (rip_output_fn) rip_output_fn(msg);

    return(tbuff);
}

CHAR* rip_oval(SHORT x,
    SHORT y,
    SHORT st_ang,
    SHORT end_ang,
    SHORT x_rad,
    SHORT y_rad)
{
    // rip_banner();

    sprintf(tbuff, "%s|O%s%s%s%s%s%s%s",
        RIC,
        mnI(x, 2),
        mnI(y, 2),
        mnI(st_ang, 2),
        mnI(end_ang, 2),
        mnI(x_rad, 2),
        mnI(y_rad, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_oval_arc(SHORT x,
    SHORT y,
    SHORT st_ang,
    SHORT end_ang,
    SHORT x_rad,
    SHORT y_rad)
{
    // rip_banner();

    sprintf(tbuff, "%s|V%s%s%s%s%s%s%s",
        RIC,
        mnI(x, 2),
        mnI(y, 2),
        mnI(st_ang, 2),
        mnI(end_ang, 2),
        mnI(x_rad, 2),
        mnI(y_rad, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_pie_slice(SHORT x,
    SHORT y,
    SHORT st_ang,
    SHORT end_ang,
    SHORT radius)
{
    // rip_banner();

    sprintf(tbuff, "%s|I%s%s%s%s%s%s",
        RIC,
        mnI(x, 2),
        mnI(y, 2),
        mnI(st_ang, 2),
        mnI(end_ang, 2),
        mnI(radius, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_pixel(SHORT x,
    SHORT y)
{
    // rip_banner();

    sprintf(tbuff, "%s|X%s%s%s",
        RIC,
        mnI(x, 2),
        mnI(y, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_read_scene(SHORT   res,
    CHAR* filename)
{
    // rip_banner();

    sprintf(tbuff, "%s|1R%s%s%s",
        RIC,
        mnI(res, 8),
        AdjustString(filename),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

SHORT rip_polypoints(SHORT npoints)
{
    // rip_banner();

    if (npoints < 0) {
        npoints = 0;
    }

    PolyPoints = (npoints > MAX_POLYPOINTS) ? MAX_POLYPOINTS : npoints;

    PolyLen = PolyCol = PolyPointsRcv = 0;

    return(npoints);
}


CHAR* rip_polygon(SHORT x,
    SHORT y)
{
    // rip_banner();

    if (!PolyPoints) return(" ");

    if (PolyPointsRcv++ == 0) {
        sprintf(polybuf, "%s|P%s", RIC, mnI(PolyPoints, 2));
        PolyCol = PolyLen = (SHORT)strlen(polybuf);
    }

    sprintf(polybuf + PolyLen, "%s%s", mnI(x, 2), mnI(y, 2));
    PolyLen += 4;
    PolyCol += 4;

    if (PolyPoints != PolyPointsRcv) {
        if (PolyCol >= maxcols) {
            sprintf(polybuf + PolyLen, "\\%s", LNF);
            PolyCol = 0;
            PolyLen += 2;
        }
    } else {                                 /* IF LAST POLYPOINT RECEIVED. */
        strcat(polybuf, LNF);
    }

    if (rip_output_fn) rip_output_fn(polybuf);

    return(polybuf);
}

CHAR* rip_polyline(SHORT x,
    SHORT y)
{
    // rip_banner();

    if (!PolyPoints) return(" ");

    if (PolyPointsRcv++ == 0) {
        sprintf(polybuf, "%s|l%s", RIC, mnI(PolyPoints, 2));
        PolyCol = PolyLen = (SHORT)strlen(polybuf);
    }

    sprintf(polybuf + PolyLen, "%s%s", mnI(x, 2), mnI(y, 2));
    PolyLen += 4;
    PolyCol += 4;

    if (PolyPoints != PolyPointsRcv) {
        if (PolyCol >= maxcols) {
            sprintf(polybuf + PolyLen, "\\%s", LNF);
            PolyCol = 0;
            PolyLen += 2;
        }
    } else {                                 /* IF LAST POLYPOINT RECEIVED. */
        strcat(polybuf, LNF);
    }

    if (rip_output_fn) rip_output_fn(polybuf);

    return(polybuf);
}


CHAR* rip_fill_poly(SHORT x,
    SHORT y)
{
    // rip_banner();

    if (!PolyPoints) return(" ");

    if (PolyPointsRcv++ == 0) {
        sprintf(polybuf, "%s|p%s", RIC, mnI(PolyPoints, 2));
        PolyCol = PolyLen = (SHORT)strlen(polybuf);
    }

    sprintf(polybuf + PolyLen, "%s%s", mnI(x, 2), mnI(y, 2));
    PolyLen += 4;
    PolyCol += 4;

    if (PolyPoints != PolyPointsRcv) {
        if (PolyCol >= maxcols) {
            sprintf(polybuf + PolyLen, "\\%s", LNF);
            PolyCol = 0;
            PolyLen += 2;
        }
    } else {                                 /* IF LAST POLYPOINT RECEIVED. */
        strcat(polybuf, LNF);
    }

    if (rip_output_fn) rip_output_fn(polybuf);

    return(polybuf);
}

CHAR* rip_proc_off(VOID)
{
    // rip_banner();

    sprintf(tbuff, "\33[2!%s", LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_proc_on(VOID)
{
    // rip_banner();

    sprintf(tbuff, "\33[1!%s", LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_put_image(SHORT x,
    SHORT y,
    SHORT mode,
    SHORT res)
{
    // rip_banner();

    sprintf(tbuff, "%s|1P%s%s%s%s%s",
        RIC,
        mnI(x, 2),
        mnI(y, 2),
        mnI(mode, 2),
        mnI(res, 1),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_query(SHORT   mode,
    SHORT   res,
    CHAR* text)
{
    // rip_banner();

    sprintf(tbuff, "%s|1\33%s%s%s%s",
        RIC,
        mnI(mode, 1),
        mnI(res, 3),
        AdjustString(text),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_rectangle(SHORT x0,
    SHORT y0,
    SHORT x1,
    SHORT y1)
{
    // rip_banner();

    sprintf(tbuff, "%s|R%s%s%s%s%s",
        RIC,
        mnI(x0, 2),
        mnI(y0, 2),
        mnI(x1, 2),
        mnI(y1, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_region_text(SHORT   justify,
    CHAR* text)
{
    // rip_banner();

    sprintf(tbuff, "%s|1t%s%s%s",
        RIC,
        mnI(justify, 1),
        AdjustString(text),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_reset_windows(VOID)
{
    // rip_banner();

    sprintf(tbuff, "%s|*%s", RIC, LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_set_palette(SHORT c1, SHORT c2, SHORT c3, SHORT c4,
    SHORT c5, SHORT c6, SHORT c7, SHORT c8,
    SHORT c9, SHORT c10, SHORT c11, SHORT c12,
    SHORT c13, SHORT c14, SHORT c15, SHORT c16)
{
    SHORT x;//=0;

    // rip_banner();

    sprintf(tbuff, "%s|Q", RIC);

    x = 3;    strcpy(tbuff + x, mnI(c1, 2));
    x += 2;    strcpy(tbuff + x, mnI(c2, 2));
    x += 2;    strcpy(tbuff + x, mnI(c3, 2));
    x += 2;    strcpy(tbuff + x, mnI(c4, 2));
    x += 2;    strcpy(tbuff + x, mnI(c5, 2));
    x += 2;    strcpy(tbuff + x, mnI(c6, 2));
    x += 2;    strcpy(tbuff + x, mnI(c7, 2));
    x += 2;    strcpy(tbuff + x, mnI(c8, 2));
    x += 2;    strcpy(tbuff + x, mnI(c9, 2));
    x += 2;    strcpy(tbuff + x, mnI(c10, 2));
    x += 2;    strcpy(tbuff + x, mnI(c11, 2));
    x += 2;    strcpy(tbuff + x, mnI(c12, 2));
    x += 2;    strcpy(tbuff + x, mnI(c13, 2));
    x += 2;    strcpy(tbuff + x, mnI(c14, 2));
    x += 2;    strcpy(tbuff + x, mnI(c15, 2));
    x += 2;    strcpy(tbuff + x, mnI(c16, 2));
    x += 2;    strcpy(tbuff + x, LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}


CHAR* rip_text(CHAR* str)
{
    // rip_banner();

    sprintf(tbuff, "%s|T%s%s",
        RIC,
        AdjustString(str),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_text_window(SHORT x0,
    SHORT y0,
    SHORT x1,
    SHORT y1,
    SHORT wrap,
    SHORT size)
{
    // rip_banner();

    sprintf(tbuff, "%s|w%s%s%s%s%s%s%s",
        RIC,
        mnI(x0, 2),
        mnI(y0, 2),
        mnI(x1, 2),
        mnI(y1, 2),
        mnI(wrap, 1),
        mnI(size, 1),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_text_xy(SHORT   x,
    SHORT   y,
    CHAR* str)
{
    // rip_banner();

    sprintf(tbuff, "%s|@%s%s%s%s",
        RIC,
        mnI(x, 2),
        mnI(y, 2),
        AdjustString(str),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_get_version(VOID)
{
    // rip_banner();

    sprintf(tbuff, "\33[!%s", LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_viewport(SHORT x0,
    SHORT y0,
    SHORT x1,
    SHORT y1)
{
    // rip_banner();

    sprintf(tbuff, "%s|v%s%s%s%s%s",
        RIC,
        mnI(x0, 2),
        mnI(y0, 2),
        mnI(x1, 2),
        mnI(y1, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_write_mode(SHORT mode)
{
    // rip_banner();

    sprintf(tbuff, "%s|W%s%s",
        RIC,
        mnI(mode, 2),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

CHAR* rip_write_icon(SHORT   res,
    CHAR* filename)
{
    // rip_banner();

    sprintf(tbuff, "%s|1W%s%s%s",
        RIC,
        mnI(res, 1),
        AdjustString(filename),
        LNF);

    if (rip_output_fn) rip_output_fn(tbuff);

    return(tbuff);
}

