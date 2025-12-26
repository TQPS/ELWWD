/*****************************************************************************
 *   ELWWDANS.C   V0.62                                 Worlds of Darkness   *
 *   3D ANSI Engine                                                          *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 01/17/1995         *
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

 //TODO: File needs linting

#include "gcomm.h"
#include "brkthu.h"
#include "majorbbs.h"
#include "elwwd.h"
#include "elwwdtyp.h"
#include "elwwdglb.h"

VOID ansi_color(SHORT blink, SHORT intensity, SHORT forcol, SHORT bakcol)
{
    CHAR kill = 0;

    if (blink == BLINK_ON)
        prf("[5;");
    else {
        prf("[0;");
        kill = 1;
    }
    if (intensity == INTENSITY_ON)
        prf("1;");
    else if (!kill)
        prf("0;");
    switch (forcol) {
        case 0:
            prf("30;");
            break;
        case 1:
            prf("34;");
            break;
        case 2:
            prf("32;");
            break;
        case 3:
            prf("36;");
            break;
        case 4:
            prf("31;");
            break;
        case 5:
            prf("35;");
            break;
        case 6:
            prf("33;");
            break;
        case 7:
            prf("37;");
            break;
        default:
            prf("31;");
    }
    switch (bakcol) {
        case 0:
            prf("40m");
            break;
        case 1:
            prf("44m");
            break;
        case 2:
            prf("42m");
            break;
        case 3:
            prf("46m");
            break;
        case 4:
            prf("41m");
            break;
        case 5:
            prf("45m");
            break;
        case 6:
            prf("43m");
            break;
        case 7:
            prf("47m");
            break;
        default:
            prf("42m");
    }
    if (forcol > 7)
        prf("fore range error");
    if (bakcol > 7)
        prf("bakc range error");
}

VOID drawcolor(CHAR* twall)
{
    SHORT i = 0, ii;
    CHAR laststr[3], colstr[3];
    //char pwall[152];

    if (!zvda->specialrip) {
        stzcpy(colstr, "00", 3);
        while (i < (SHORT)strlen(twall) && !exit_door) {
            stzcpy(laststr, colstr, 3);
            stzcpy(colstr, "00", 3);
            if (twall[i] == '@') {
                i++;
                colstr[0] = twall[i];
                i++;
                colstr[1] = twall[i];
                if (stricmp(colstr, laststr) != 0) {
                    ii = (SHORT)atoi(colstr);
                    if (ii < 8)
                        ansi_color(BLINK_OFF, INTENSITY_OFF, ii, zvda->background - 20);
                    else if (ii > 7 && ii < 20)
                        ansi_color(BLINK_OFF, INTENSITY_ON, ii - 8, zvda->background - 20);
                    if (ii > 19) {
                        if (zvda->forground < 8)
                            ansi_color(BLINK_OFF, INTENSITY_OFF, zvda->forground, ii - 20);
                        else ansi_color(BLINK_OFF, INTENSITY_ON, zvda->forground - 8, ii - 20);
                        zvda->background = (CHAR)ii;
                    } else zvda->forground = (CHAR)ii;
                }
                i++;
            }
            if (i < (SHORT)strlen(twall)) {
                if (twall[i] == '~') {
                    prf("%s", zplyr->name);
                    i++;
                }
                if (twall[i] == '|') {
                    prf("\n");
                    i++;
                }
                if (twall[i] != '@' && twall[i] != '|' && twall[i] != '~') {
                    prf("%c", twall[i]);
                    i++;
                }
            }
        }
    }
    //else {
    //  scopyc(pwall,twall);
    //  striprip(pwall);
    //  if (zvda->ripos<15)
    //    scopyc(tempwall1,storerip[zvda->ripos+2]);
    //  else {
    //    if (zvda->ripos>40) {
    //      zvda->ripos-=40;
    //      scopyc(tempwall1,storerip2[zvda->ripos+2]);
    //    }
    //    else {
    //      zvda->ripos-=14;
    //      scopyc(tempwall1,storerip1[zvda->ripos+2]);
    //    }
    //  }
    //  insert(pwall,tempwall1,9);
    //  scopy(tempwall,tempwall1);
    //  zvda->specialrip=FALSE;
    //  i=0;
    //  stzcpy(colstr,"00",3);
    //  cvstr(tempwall);
    //  while(i<strlen(twall) && !exit_door) {
    //    stzcpy(laststr,colstr,3);
    //    stzcpy(colstr,"00",3);
    //    if (twall[i]=='@') {
    //      i++;
    //      colstr[0]=twall[i];
    //      if (isdigit(twall[i+1])) {
    //        i++;
    //        colstr[1]=twall[i];
    //        colstr[2]=0;
    //      }
    //      if (stricmp(colstr,laststr)!=0) {
    //        ii=atoi(colstr);
    //        scopyc(tempwall1,ripcolcmd);
    //        insert(ripcolor[ii],tempwall1,7);
    //      }
    //      i++;
    //    }
    //    if (i<strlen(twall)) {
    //     switch(twall[i]) {
    //      case '~': td_writeln(zplyr->name);
    //                break;
    //      case '|': td_writeln("||");
    //                break;
    //      case '*': td_outchar(stats.comport,'|',ECHO_ON);
    //                break;
    //      case '^': td_outchar(stats.comport,'@',ECHO_ON);
    //                break;
     //      default: td_outchar(stats.comport,tempwall[i],ECHO_ON);
    //
    //     }
     //   }
    //  }
    //}
    zvda->ripos = 0;
    outprf(usrnum);
}

VOID drawdiag(VOID)
{
    SHORT i, j, k;
    CHAR doorchar = ' ';

    if (doorme) doorchar = doorchars[doortype];
    srow++;
    for (i = 1; i <= fwid; i++) {
        if (i == 2) wall[srow - 1][scol] = '>';
        else {
            wall[srow - 1][scol] = '<';
            wall[srow + fvert][scol] = '<';
        }
        j = fvert;
        k = srow;
        while (j != 0) {
            wall[k][scol] = '>';
            if (doorme && i == 2 && k >= drcol) wall[k][scol] = doorchar;
            if (leverme && i == 2 && k == srow + 1) wall[k][scol] = 'o';
            k++;
            j--;
        }
        if (scol < 14) {
            if (i == 1) srow++;
            fvert--;
            scol++;
        }
        if (scol > 14) {
            if (i == 2) srow--;
            fvert++;
            scol++;
        }
    }
}

VOID fill3d(VOID)
{
    SHORT i;

    if (wall[1][1] == '>') {
        for (i = 1; i <= 12; i++) {
            wall[i][2] = wchars[4];
            wall[i][1] = '>';
        }
    }
    if (wall[1][26] == '>') {
        for (i = 1; i <= 12; i++) {
            wall[i][25] = wchars[4];
            wall[i][26] = '>';
        }
    }
    fcolor();
}

VOID
insert(CHAR* colr, CHAR* cstr, CHAR pos)
{
    INT i, j;
    size_t colrlen;
    UCHAR oldlen, newlen;
    CHAR tstr[250] = { 0 };

    if (!colr || !cstr) {
        prf("insert has detected a null string\n");
        outprf(usrnum);
        return;
    }

    /* Cache these once (original called strlen(colr) repeatedly) */
    colrlen = strlen(colr);
    oldlen = (UCHAR)cstr[0];        /* Pascal-string length byte */

    /* Step 1: compute new length and bounds-check */
    if ((size_t)oldlen + colrlen > 240) {
        prf("ERROR: INSERT OVERRUN 240!!!\n");
        outprf(usrnum);
        return;
    }
    newlen = (UCHAR)((size_t)oldlen + colrlen);
    tstr[0] = (CHAR)newlen;

    // Likely debug
    /*
      prf("cstr before (len=%u)\n", (unsigned)oldlen);
      for (i=1; i <= (INT)oldlen; i++) {
       prf("%u,", (unsigned)((UCHAR)cstr[i]));
      }
      prf("\n");
      outprf(usrnum);

      prf("colr before (len=%u)\n", (unsigned)colrlen);
      for (i=0; i < (INT)colrlen; i++) {
       prf("%u,", (unsigned)((UCHAR)colr[i]));
      }
      prf("\n");
      outprf(usrnum);

      prf("pos=%u newlen=%u\n", (unsigned)((UCHAR)pos), (unsigned)newlen);
      outprf(usrnum);
    */

    /* Step 2: copy head (1..pos-1) */
    for (i = 1; i < (UCHAR)pos; i++) {
        tstr[i] = cstr[i];
    }

    /* Step 3: insert colr at pos */
    j = (UCHAR)pos;
    for (i = 0; i < (INT)colrlen; i++) {
        tstr[j] = colr[i];
        j++;
    }

    /* Step 4: copy tail (pos..oldlen) */
    for (i = (UCHAR)pos; i <= oldlen; i++) {
        tstr[j] = cstr[i];
        j++;
    }

    /* Step 5: copy back (0..newlen) */
    for (i = 0; i <= newlen; i++) {
        cstr[i] = tstr[i];
    }

    // Likely debug
    /*
      prf("cstr after (len=%u)\n", (unsigned)newlen);
      for (i=1; i <= (INT)newlen; i++) {
       prf("%u,", (unsigned)((UCHAR)cstr[i]));
      }
      prf("\n");
      outprf(usrnum);
    */
}

VOID fcolor(VOID)
{
    USHORT i, j;
    CHAR wasme, doorchar;
    if (zvda->movingaround) {
        for (i = 1; i <= 12; i++) {
            wall[i][27] = ' '; /* fix to prevent illegal line formations */
            for (j = 26; j >= 1; j--) {
                switch (wall[i][j]) {
                    case 'Y':
                    case 'X':
                        if ((wall[i][j - 1] == 'X' || wall[i][j - 1] == 'Y') && j > 1)
                            wasme = TRUE;
                        else
                            wasme = FALSE;
                        if (wall[i][j] == 'X') doorchar = wchars[4];
                        else doorchar = 206;
                        wall[i][j] = doorchar;
                        //              if (wall[i][j+1]==doorchar)
                        //                 insert(doorcolor,wall[i],j);
                        //              else if (!wasme)
                        if (!wasme)
                            insert(doorcolor, wall[i], (CHAR)j);
                        break;
                    case  '<':
                        if (i < 6) wall[i][j] = wchars[2]; /* invert patch */
                        else wall[i][j] = wchars[3];
                        insert(wcolors[2], wall[i], (CHAR)j);
                        break;
                    case '>':
                        wall[i][j] = wchars[1];
                        insert(wcolors[2], wall[i], (CHAR)j);
                        break;
                        /* always force bar color to solve door/border bleed */
                    case  '±':
                        insert(wcolors[2], wall[i], (CHAR)j);
                        break;
                    case  'l':
                        wall[i][j] = 205;
                        insert(doorcolor, wall[i], (CHAR)j);
                        break;
                    case 'm':
                        wall[i][j] = 202;
                        insert(doorcolor, wall[i], (CHAR)j);
                        break;
                    case 'o':
                        wall[i][j] = 186;
                        insert(doorcolor, wall[i], (CHAR)j);
                        break;
                    case 'n':
                        wall[i][j] = 203;
                        insert(doorcolor, wall[i], (CHAR)j);
                        break;
                    case 'W':
                        wall[i][j] = 'þ';
                        insert(tpcolor, wall[i], (CHAR)j);
                        break;
                }
            }
        }
    }
}

VOID plotface(VOID)
{
    USHORT i, j;
    for (i = srow; i <= srow + fvert - 1; i++) {
        for (j = scol; j <= scol + fwid - 1; j++) {
            wall[i][j] = facechar;
        }
    }
}

VOID plotxp(VOID)
{
    USHORT i, j, l;
    CHAR dome;

    dome = TRUE;
    for (i = srow; i <= srow + fvert - 1; i++) {
        j = scol;
        l = scol + fwid - 1;
        if (!dome) j++;
        if (dome) dome = FALSE;
        else dome = TRUE;
        while (j < l) {
            wall[i][j] = 'W';
            j += 2;
        }
    }
}

VOID draw3d(VOID)
{
    const USHORT fovl[4] = { 0,1,2,2 },
        fovr[4] = { 0,5,4,4 },
        facerow[4] = { 0,5,3,1 },
        facecol[4][6] =
    { {0,0,0,0,0,0},
     {0,1,4,11,18,25},
     {0,0,1,7,22,0},
     {0,0,1,3,26,0}, },
        facewid[4][6] =
    { {0,0,0,0,0,0},
     {0,2,6,6,6,2},
     {0,0,5,14,5,0},
     {0,0,1,22,1,0}, },
        facevert[4] = { 0,4,8,12 },
        ldverts[4] = { 0,2,4,8 };
    USHORT i, j, k, l, m, n;
    CHAR lfacev, rfacev, leverup, dobars, doorclosed;
    CHAR tc;

    /*  init flags & face chars */
    facechar = '>';
    for (i = 1; i <= 12; i++) {
        for (j = 1; j < 27; j++) {
            wall[i][j] = ' ';
        }
        wall[i][0] = 26;
    }
    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= 5; j++) {
            orgholder[i][j] = tc = holdmap[i][j];
            if (tc >= 'A' && tc <= 'Z') holdmap[i][j] = '*';
            if (tc >= 'a' && tc <= 'm') holdmap[i][j] = '&';
            if (tc >= 'n' && tc <= 'z') holdmap[i][j] = '@';
            if (tc == '%') holdmap[i][j] = ' ';
        }
    }
    /* start scan of holder walls */
    for (i = 1; i <= 3; i++) {
        for (j = fovl[i]; j <= fovr[i]; j++) {
            if (holdmap[i][j] != ' ' && facecol[i][j] > 0) {
                lfacev = rfacev = dobars = doorclosed = TRUE;
                srow = facerow[i];
                scol = facecol[i][j];
                fwid = facewid[i][j];
                fvert = facevert[i];
                if (holdmap[i][j] == '&') {  /* locate the door */
                    k = orgholder[i][j] - 'a';
                    doorclosed = FALSE;
                    if (k > 12) k = 12; // RH: Compiler thinks C6385 warning, k could be 65477... not sure how?
                    for (l = 0; l < grates[plevel].levercnt[k]; l++) {
                        if (grates[plevel].leverstate[k][l] == 'u')
                            doorclosed = TRUE;
                    }
                }
                if (index(xpchars, holdmap[i][j]) != NOTFOUND) {
                    dobars = FALSE;
                    plotxp();
                } else if (index("#*@", holdmap[i][j]) != NOTFOUND ||
                    (doorclosed && dobars))
                    plotface();
                //        if (index(xpchars,holdmap[i][j])!=NOTFOUND) plotxp();
                if (facecol[i][j] == 1) lfacev = FALSE;
                if (facecol[i][j] + facewid[i][j] > 25) rfacev = FALSE;
                /* plot full open door face */
                if (!doorclosed) {
                    /* plot the open door */
                    m = scol;
                    n = fwid - 1;
                    for (k = srow; k <= srow + fvert - 1; k++) {
                        for (l = m; l <= m + n; l++) {
                            if (k == srow || (l < scol + i && lfacev) ||
                                (l > scol + fwid - 1 - i && rfacev))
                                wall[k][l] = facechar;
                        }
                    }
                    if (i == 2 && rfacev && lfacev) {
                        k = facecol[1][j] - 2;
                        l = facerow[1] - 1;
                        wall[l][k] = ' ';
                        l = facerow[1] + facevert[1];
                        wall[l][k] = ' ';
                    }
                }
                /* plot left bar */
                if (lfacev && dobars) {
                    for (k = facerow[i]; k <= (facerow[i] + facevert[i]) - 1; k++) {
                        wall[k][facecol[i][j] - 1] = wchars[4];
                    }
                }
                /* plot right bar */
                if (rfacev && dobars) {
                    for (k = facerow[i]; k <= (facerow[i] + facevert[i]) - 1; k++) {
                        wall[k][facecol[i][j] + facewid[i][j]] = wchars[4];
                    }
                }
                /* plot face doors */
                if (index("*&", holdmap[i][j]) != NOTFOUND) {
                    if (holdmap[i][j] == '*')
                        doortype = 1;
                    else
                        doortype = 2;
                    if (doortype == 1 || doorclosed) {
                        for (k = facerow[i] + 1; k <= facerow[i] + facevert[i] - 1; k++) {
                            l = facecol[i][j];
                            if (lfacev) l = facecol[i][j] + i;
                            if (rfacev && lfacev)
                                m = facewid[i][j] - (i * 2);
                            else
                                m = facewid[i][j] - i;
                            if (m < 26)
                                for (n = l; n <= l + m - 1; n++) {
                                    if (n > 26 || k > 12) {
                                        prf("door error k=%u,n=%u,l=%u,m=%u\n", k, n, l, m);
                                        prf("door error i=%u,j=%u\n", i, j);
                                        prf("door error k=%u,n=%u,l=%u,m=%u\n", k, n, l, m);
                                        prf("door error i=%u,j=%u\n", i, j);
                                        outprf(usrnum);
                                        return;
                                    }
                                    wall[k][n] = doorchars[doortype];
                                }
                            if (k == facerow[i] + (i * 2)) {
                                if (rfacev)
                                    if (i > 1 && doortype == 1)
                                        // TODO: confirm intended door detail glyph (276 was invalid in wall[][] but aligns with UDOOR2 constant in ELWWD.H - Frank).
                                        wall[k][l + m - 2] = doorchars[doortype];   // keep door consistent for now
                                        // wall[k][l + m - 2] = 276;    // RH: BUG: This won't work, CHAR is 0..255! This will only copy lower bits and be 20.  TODO: Find this and figure out what wall[][] should really be
                            }
                        }
                    }

                    if (j == 3 && i > 1 && doortype == 1) {
                        srow = facerow[i] + 2;
                        fvert = i - 1;
                        if (i == 3)
                            fwid = 8;
                        else
                            fwid = 4;
                        if (i == 2) scol = facecol[i][j] + 5;
                        else scol = facecol[i][j] + 7;
                        facechar = ' ';
                        plotface();
                        facechar = '>';
                    }
                }
                /* plot diagonals */
                if (rfacev && j < 3 && dobars) {
                    leverme = FALSE;
                    srow = facerow[i];
                    scol = facecol[i][j] + facewid[i][j] + 1;
                    if (i == 1) fwid = 1;
                    else fwid = 3;
                    fvert = facevert[i] - 2;
                    if (index("*&", holdmap[i][j]) != NOTFOUND) {
                        if (holdmap[i][j] == '*')
                            doortype = 1;
                        else doortype = 2;
                        doorme = TRUE;
                        drcol = srow - 1;
                    } else doorme = FALSE;
                    if (holdmap[i][j] == '@') leverme = TRUE;
                    /* plot corners for missing blocks */
                    if (holdmap[i - 1][j] == ' ' && holdmap[i][j + 1] == ' ') {
                        for (k = facerow[i - 1]; k <= (facerow[i - 1] + facevert[i - 1]) - 1; k++) {
                            wall[k][facecol[i - 1][j] + facewid[i - 1][j]] = wchars[4];
                        }
                    }
                    drawdiag();
                }

                if (lfacev && j > 3 && dobars) {
                    doorme = FALSE;
                    fvert = ldverts[i];
                    if (i == 1) {
                        srow = 5;
                        scol = facecol[i][j] - 2;
                        fwid = 1;
                    } else {
                        scol = facecol[i - 1][j];
                        srow = facerow[i] + 1;
                        fwid = 3;
                        /* plot corners for missing blocks */
                        if (holdmap[i - 1][j] == ' ' && holdmap[i][j - 1] == ' ') {
                            for (k = facerow[i - 1]; k <= (facerow[i - 1] + facevert[i - 1]) - 1; k++) {
                                wall[k][facecol[i - 1][j] - 1] = wchars[4];
                            }
                        }
                    }
                    if (strchr("*&", holdmap[i][j]) != NULL) {
                        if (holdmap[i][j] == '*')
                            doortype = 1;
                        else doortype = 2;
                        if (i > 1) doorme = TRUE;
                        drcol = srow - 1;
                    }
                    if (holdmap[i][j] == '@') leverme = TRUE;
                    else leverme = FALSE;
                    if (holdmap[i][j - 1] == ' ')
                        drawdiag();
                }
                /* lever inserts here */
                if (j == 3 && i > 1 && holdmap[i][j] == '@') {
                    leverup = TRUE;
                    l = orgholder[i][j] - 'n'; /* lever */
                    /* find which lever of this one */
                    k = 0;
                    for (m = 0; m < grates[plevel].levercnt[l]; m++) {
                        if (grates[plevel].levercol[l][m] == truecol[i][j] &&
                            grates[plevel].leverrow[l][m] == truerow[i][j]) {
                            k = m;
                            break;
                        }
                    }
                    if (k == grates[plevel].levercnt[l]) {
                        prf("lever not found %u,%u\n", truecol[i][j], truerow[i][j]);
                        outprf(usrnum);
                    }
                    if (grates[plevel].leverstate[l][k] == 'd')
                        leverup = FALSE;
                    if (leverup) {
                        if (i == 3) {  /* small lever */
                            wall[5][13] = 'l';
                            wall[5][14] = 'm';
                            wall[5][15] = 'l';
                            wall[4][14] = 'o';
                            wall[3][14] = 'o';
                        }
                        if (i == 2) {
                            wall[6][14] = 'm';
                            wall[5][14] = 'o';
                        }
                    } else {
                        if (i == 3) {
                            wall[5][13] = 'l';
                            wall[5][14] = 'n';
                            wall[5][15] = 'l';
                            wall[6][14] = 'o';
                            wall[7][14] = 'o';
                        }
                        if (i == 2) {
                            wall[6][14] = 'n';
                            wall[7][14] = 'o';
                        }
                    }
                }
                /* insert here for additional nz blocks */
            }
        }
    }
    if (holdmap[4][2] != ' ') wall[1][1] = '>';
    if (holdmap[4][4] != ' ') wall[1][26] = '>';
}



// *************************************************************************
// Rip 3D drawing code starts beyond this point ****************************
// *************************************************************************

VOID rip3d(VOID)
{
    CHAR tmap[TMROW + 1][TMCOL + 1] = { 0 }, thechr, store, tstr[30] = { 0 }, ix, iy;
    CHAR i, ii, iii;

    store = holdmap[3][3];
    // Convert the map to the form we need!!!
    for (i = 1; i < TMROW + 1; i++) {
        for (ii = 1; ii < TMCOL + 1; ii++) {
            thechr = holdmap[i][ii];
            for (iii = 0; iii < 8; iii++) {
                if (thechr == xpchars[iii]) {
                    thechr = '[';
                }
            }
            if ((thechr >= 'n') && (thechr <= 'z')) {
                thechr = '#';
            }
            if ((thechr >= 'A') && (thechr <= 'Z')) {
                thechr = '?';
            }
            if (thechr == '%') {
                thechr = ' ';
            }
            tmap[i][ii] = thechr;
        }
    }

    //  Position being checked :     1#####    ^
    //                               2#####    |
    //                               3##*##    N
    //                                12345

    drawripbox(1, 1, 197, 147, 1, 10, 0, 1);
    place_icon(1, 1, "WOD3D");
    if (tmap[3][3] != ' ') {   // There is something infront of me.. Finish....
        switch (holdter[3][3]) {
            case 'A':
                // stone work...........................................
                switch (tmap[3][3]) {
                    case '[':
                        place_icon(1, 1, "PORTAL1");
                        break;
                    case '~':
                        place_icon(1, 1, "FACESBT1");
                        break;
                    case '*':
                        place_icon(1, 1, "FACESDR1");
                        break;
                    case '#':
                        place_icon(1, 1, "FACESWS1");
                        break;
                    case '$':
                        place_icon(1, 1, "FACESBT1");
                        break;
                    case '?':
                        place_icon(1, 1, "FACESDS1");
                        switch (store) {
                            case 'W':
                                place_icon(1, 1, "STAIR1");
                                break;
                            case 'X':
                                place_icon(1, 1, "STAIR1");
                                break;
                            case 'A':
                                place_icon(1, 24, "SBANK");
                                break;
                            case 'B':
                                place_icon(1, 24, "SWARRIOR");
                                break;
                            case 'C':
                                place_icon(1, 24, "SWIZARD");
                                break;
                            case 'D':
                                place_icon(1, 24, "SCLERIC");
                                break;
                            case 'G':
                                place_icon(1, 24, "SINN");
                                break;
                            case 'H':
                                place_icon(1, 24, "STAVERN");
                                break;
                            case 'J':
                                place_icon(1, 24, "SARMOR");
                                break;
                            case 'P':
                                place_icon(1, 24, "SPALACE");
                                break;
                            case 'Q':
                                place_icon(1, 24, "SARENA");
                                break;
                        }
                        break;
                }
                break;

            case 'B':
                // brick work...........................................
                switch (tmap[3][3]) {
                    case '[':
                        place_icon(1, 1, "BACESP1");
                        break;
                    case '~':
                        place_icon(1, 1, "BACESBT1");
                        break;
                    case '*':
                        place_icon(1, 1, "BACESDR1");
                        break;
                    case '#':
                        place_icon(1, 1, "BACESBW1");
                        break;
                    case '$':
                        place_icon(1, 1, "BACESBT1");
                        break;
                    case '?': switch (store) {
                        case 'W':
                            place_icon(1, 1, "STAIR1");
                            break;
                        case 'X':
                            place_icon(1, 1, "STAIR1");
                            break;
                        case 'A':
                            place_icon(1, 31, "BBANK");
                            break;
                        case 'B':
                            place_icon(1, 31, "BWARRIOR");
                            break;
                        case 'C':
                            place_icon(1, 31, "BWIZARD");
                            break;
                        case 'D':
                            place_icon(1, 31, "BCLERIC");
                            break;
                        case 'G':
                            place_icon(1, 31, "BINN");
                            break;
                        case 'H':
                            place_icon(1, 31, "BTAVERN");
                            break;
                        case 'J':
                            place_icon(1, 31, "BARMOR");
                            break;
                        case 'P':
                            place_icon(1, 31, "BPALACE");
                            break;
                        case 'Q':
                            place_icon(1, 31, "BARENA");
                            break;
                    }
                            break;
                }
                // button code
                switch (store) {
                    case 'W':
                        strcpy(tstr, "UP");
                        break;
                    case 'X':
                        strcpy(tstr, "DOWN");
                        break;
                }
                if ((store == 'W') || (store == 'X')) {
                    td_writeln("||!|1B0000020PHS030F000F080100000F07000000||");
                    td_writeln(spr("||!|Y02000400|1U270I3B0Z0000<>%s<>|#|#|#||", tstr));
                }
                break;

        }

    } else {                   // There is nothing infront of me.. Continue....

        //  Position being checked :     1*####    ^
        //                               2#####    |
        //                               3#####    N
        //                                12345

        if ((tmap[1][1] != ' ') && (tmap[2][2] == ' ') && (tmap[3][2] == ' ')) {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[1][1]) {
                case 'A':
                    switch (tmap[1][1]) {
                        case '~':
                            strcpy(tstr, "HALFLBT3");
                            break;
                        case '*':
                            strcpy(tstr, "HALFLDR3");
                            break;
                        case '#':
                            strcpy(tstr, "HALFLWS3");
                            break;
                        case '$':
                            strcpy(tstr, "HALFLBT3");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 1; iy = 56;
                    } else {
                        ix = 1; iy = 50;
                    }
                    break;
                case 'B':
                    switch (tmap[1][1]) {
                        case '~':
                            strcpy(tstr, "BALLLBT3");
                            break;
                        case '*':
                            strcpy(tstr, "BALLLDR3");
                            break;
                        case '#':
                            strcpy(tstr, "BALLLWS3");
                            break;
                        case '$':
                            strcpy(tstr, "BALLLBT3");
                            break;

                    }
                    ix = 1; iy = 56;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 on ix, iy here
            }
        }

        //  Position being checked :     1####*    ^
        //                               2#####    |
        //                               3#####    N
        //                                12345

        if ((tmap[1][5] != ' ') && (tmap[2][4] == ' ') && (tmap[3][4] == ' ')) {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[1][5]) {
                case 'A':
                    switch (tmap[1][5]) {
                        case '~':
                            strcpy(tstr, "HALFRBT3");
                            break;
                        case '*':
                            strcpy(tstr, "HALFRDR3");
                            break;
                        case '#':
                            strcpy(tstr, "HALFRWS3");
                            break;
                        case '$':
                            strcpy(tstr, "HALFRBT3");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 145; iy = 56;
                    } else {
                        ix = 141; iy = 50;
                    }
                    break;
                case 'B':
                    switch (tmap[1][5]) {
                        case '~':
                            strcpy(tstr, "BALLRBT3");
                            break;
                        case '*':
                            strcpy(tstr, "BALLRRD3");
                            break;
                        case '#':
                            strcpy(tstr, "BALLRWS3");
                            break;
                        case '$':
                            strcpy(tstr, "BALLRBT3");
                            break;

                    }
                    ix = 145; iy = 56;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }

        //  Position being checked :     1#*###    ^
        //                               2#####    |
        //                               3#####    N
        //                                12345

        if ((tmap[1][2] != ' ') && (tmap[2][2] == ' ')) {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[1][2]) {
                case 'A':
                    switch (tmap[1][2]) {
                        case '~':
                            strcpy(tstr, "FACELBT3");
                            break;
                        case '*':
                            strcpy(tstr, "FACELDR3");
                            break;
                        case '#':
                            strcpy(tstr, "FACELWS3");
                            break;
                        case '$':
                            strcpy(tstr, "FACELBT3");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 33; iy = 56;
                    } else {
                        ix = 26; iy = 50;
                    }
                    break;
                case 'B':
                    switch (tmap[1][2]) {
                        case '~':
                            strcpy(tstr, "BACELBT3");
                            break;
                        case '*':
                            strcpy(tstr, "BACELRD3");
                            break;
                        case '#':
                            strcpy(tstr, "BACELWS3");
                            break;
                        case '$':
                            strcpy(tstr, "BACELBT3");
                            break;

                    }
                    ix = 33; iy = 56;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }
        //  Position being checked :     1###*#    ^
        //                               2#####    |
        //                               3#####    N
        //                                12345

        if ((tmap[1][4] != ' ') && (tmap[2][4] == ' ')) {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[1][4]) {
                case 'A':
                    switch (tmap[1][4]) {
                        case '~':
                            strcpy(tstr, "FACERBT3");
                            break;
                        case '*':
                            strcpy(tstr, "FACERDR3");
                            break;
                        case '#':
                            strcpy(tstr, "FACERWS3");
                            break;
                        case '$':
                            strcpy(tstr, "FACERBT3");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 105; iy = 56;
                    }

                    else {
                        ix = 111; iy = 50;
                    }
                    break;
                case 'B':
                    switch (tmap[1][4]) {
                        case '~':
                            strcpy(tstr, "BACERBT3");
                            break;
                        case '*':
                            strcpy(tstr, "BACERRD3");
                            break;
                        case '#':
                            strcpy(tstr, "BACERWS3");
                            break;
                        case '$':
                            strcpy(tstr, "BACERBT3");
                            break;

                    }
                    ix = 105; iy = 56;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }
        //  Position being checked :     1#*###    ^     (angle)
        //                               2#####    |
        //                               3#####    N
        //                                12345

        if ((tmap[1][2] != ' ') && (tmap[2][2] != ' ') &&
            (tmap[1][3] == ' ') && (tmap[2][3] == ' ')) {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[1][2]) {
                case 'A':
                    switch (tmap[1][2]) {
                        case '~':
                            strcpy(tstr, "HALLBTL3");
                            break;
                        case '*':
                            strcpy(tstr, "HALLRDL3");
                            break;
                        case '#':
                            strcpy(tstr, "HALLWSL3");
                            break;
                        case '$':
                            strcpy(tstr, "HALLBTL3");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 68; iy = 2;
                    } else {
                        ix = 70; iy = 1;
                    }
                    break;
                case 'B':
                    switch (tmap[1][2]) {
                        case '~':
                            strcpy(tstr, "BALFLBT3");
                            break;
                        case '*':
                            strcpy(tstr, "BALFLRD3");
                            break;
                        case '#':
                            strcpy(tstr, "BALFLWS3");
                            break;
                        case '$':
                            strcpy(tstr, "BALFLBT3");
                            break;

                    }
                    ix = 68; iy = 2;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }
        //  Position being checked :     1###*#    ^     (angle)
        //                               2#####    |
        //                               3#####    N
        //                                12345

        if ((tmap[1][4] != ' ') && (tmap[2][4] != ' ') &&
            (tmap[1][3] == ' ') && (tmap[2][3] == ' ')) {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[1][4]) {
                case 'A':
                    switch (tmap[1][4]) {
                        case '~':
                            strcpy(tstr, "HALLBTR3");
                            break;
                        case '*':
                            strcpy(tstr, "HALLRDR3");
                            break;
                        case '#':
                            strcpy(tstr, "HALLWSR3");
                            break;
                        case '$':
                            strcpy(tstr, "HALLBTR3");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 108; iy = 1;
                    } else {
                        ix = 110; iy = 1;
                    }
                    break;
                case 'B':
                    switch (tmap[1][4]) {
                        case '~':
                            strcpy(tstr, "BALFRBT3");
                            break;
                        case '*':
                            strcpy(tstr, "BALFRRD3");
                            break;
                        case '#':
                            strcpy(tstr, "BALFRWS3");
                            break;
                        case '$':
                            strcpy(tstr, "BALFRBT3");
                            break;

                    }
                    ix = 108; iy = 1;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }
        //  Position being checked :     1##*##    ^
        //                               2#####    |
        //                               3#####    N
        //                                12345

        if ((tmap[1][3] != ' ') && (tmap[2][3] == ' ')) {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[1][3]) {
                case 'A':
                    switch (tmap[1][3]) {
                        case '[':
                            strcpy(tstr, "PORTAL3");
                            break;
                        case '~':
                            strcpy(tstr, "FACESBT3");
                            break;
                        case '*':
                            strcpy(tstr, "FACESDR3");
                            break;
                        case '#':
                            strcpy(tstr, "FACESWS3");
                            break;
                        case '$':
                            strcpy(tstr, "FACESBT3");
                            break;
                        case '?':
                            strcpy(tstr, "FACESDS3");
                            break;
                        case 'W':
                            strcpy(tstr, "STAIR3");
                            break;
                        case 'X':
                            strcpy(tstr, "STAIR3");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 70; iy = 56;
                    } else {
                        ix = 70; iy = 50;
                    }
                    break;
                case 'B':
                    switch (tmap[1][3]) {
                        case '[':
                            strcpy(tstr, "BACESP3");
                            break;
                        case '~':
                            strcpy(tstr, "BACESBT3");
                            break;
                        case '*':
                            strcpy(tstr, "BACESRD3");
                            break;
                        case '#':
                            strcpy(tstr, "BACESWS3");
                            break;
                        case '$':
                            strcpy(tstr, "BACESBT3");
                            break;
                        case '?':
                            strcpy(tstr, "BACESSD3");
                            break;
                        case 'W':
                        case 'X':
                            strcpy(tstr, "STAIR3");
                            break;

                    }
                    ix = 70; iy = 56;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }
        //  Position being checked :     1#####    ^
        //                               2#*###    |
        //                               3#####    N
        //                                12345

        if ((tmap[2][2] != ' ') && (tmap[3][2] == ' ')) {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[2][2]) {
                case 'A':
                    switch (tmap[2][2]) {
                        case '~':
                            strcpy(tstr, "HALFLBT2");
                            break;
                        case '*':
                            strcpy(tstr, "HALFLDR2");
                            break;
                        case '#':
                            strcpy(tstr, "HALFLWS2");
                            break;
                        case '$':
                            strcpy(tstr, "HALFLBT2");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 2; iy = 27;
                    } else {
                        ix = 1; iy = 24;
                    }
                    break;
                case 'B':
                    switch (tmap[2][2]) {
                        case '~':
                            strcpy(tstr, "BALLLBT2");
                            break;
                        case '*':
                            strcpy(tstr, "BALLLRD2");
                            break;
                        case '#':
                            strcpy(tstr, "BALLLWS2");
                            break;
                        case '$':
                            strcpy(tstr, "BALLLBT2");
                            break;

                    }
                    ix = 2; iy = 27;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }
        //  Position being checked :     1#####    ^
        //                               2###*#    |
        //                               3#####    N
        //                                12345

        if ((tmap[2][4] != ' ') && (tmap[3][4] == ' ')) {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[2][4]) {
                case 'A':
                    switch (tmap[2][4]) {
                        case '~':
                            strcpy(tstr, "HALFRBT2");
                            break;
                        case '*':
                            strcpy(tstr, "HALFRDR2");
                            break;
                        case '#':
                            strcpy(tstr, "HALFRWS2");
                            break;
                        case '$':
                            strcpy(tstr, "HALFRBT2");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 127; iy = 27;
                    } else {
                        ix = 124; iy = 24;
                    }
                    break;
                case 'B':
                    switch (tmap[2][4]) {
                        case '~':
                            strcpy(tstr, "BALLRBT2");
                            break;
                        case '*':
                            strcpy(tstr, "BALLRRD2");
                            break;
                        case '#':
                            strcpy(tstr, "BALLRWS2");
                            break;
                        case '$':
                            strcpy(tstr, "BALLRBT2");
                            break;

                    }
                    ix = 127; iy = 27;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }
        //  Position being checked :     1#####    ^     (angle)
        //                               2#*###    |
        //                               3#####    N
        //                                12345

        if ((tmap[2][2] != ' ') && (tmap[3][2] != ' ') &&
            (tmap[2][3] == ' ')) {
            strcpy(tstr, " #");
            ix = 33; iy = 1;
            switch (holdter[2][2]) {
                case 'A':
                    switch (tmap[2][2]) {
                        case '~':
                            strcpy(tstr, "HALLBTL2");
                            break;
                        case '*':
                            strcpy(tstr, "HALLRDL2");
                            break;
                        case '#':
                            strcpy(tstr, "HALLWSL2");
                            break;
                        case '$':
                            strcpy(tstr, "HALLBTL2");
                            break;

                    }
                    break;
                case 'B':
                    switch (tmap[2][2]) {
                        case '~':
                            strcpy(tstr, "BALFLBT2");
                            break;
                        case '*':
                            strcpy(tstr, "BALFLRD2");
                            break;
                        case '#':
                            strcpy(tstr, "BALFLWS2");
                            break;
                        case '$':
                            strcpy(tstr, "BALFLBT2");
                            break;

                    }
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr);
            }
        }
        //  Position being checked :     1#####    ^     (angle)
        //                               2###*#    |
        //                               3#####    N
        //                                12345

        if ((tmap[2][4] != ' ') && (tmap[3][4] != ' ') &&
            (tmap[2][3] == ' ')) {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[2][4]) {
                case 'A':
                    switch (tmap[2][4]) {
                        case '~':
                            strcpy(tstr, "HALLBTR2");
                            break;
                        case '*':
                            strcpy(tstr, "HALLRDR2");
                            break;
                        case '#':
                            strcpy(tstr, "HALLWSR2");
                            break;
                        case '$':
                            strcpy(tstr, "HALLBTR2");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 128; iy = 1;
                    } else {
                        ix = 125; iy = 1;
                    }
                    break;
                case 'B':
                    switch (tmap[2][4]) {
                        case '~':
                            strcpy(tstr, "BALFRBT2");
                            break;
                        case '*':
                            strcpy(tstr, "BALFRRD2");
                            break;
                        case '#':
                            strcpy(tstr, "BALFRWS2");
                            break;
                        case '$':
                            strcpy(tstr, "BALFRBT2");
                            break;

                    }
                    ix = 128; iy = 1;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }
        //  Position being checked :     1#####    ^
        //                               2##*##    |
        //                               3#####    N
        //                                12345

        if (tmap[2][3] != ' ') {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[2][3]) {
                case 'A':
                    switch (tmap[2][3]) {
                        case '[':
                            strcpy(tstr, "PORTAL2");
                            break;
                        case '~':
                            strcpy(tstr, "FACESBT2");
                            break;
                        case '*':
                            strcpy(tstr, "FACESDR2");
                            break;
                        case '#':
                            strcpy(tstr, "FACESWS2");
                            break;
                        case '$':
                            strcpy(tstr, "FACESBT2");
                            break;
                        case '?':
                            strcpy(tstr, "FACESDS2");
                            break;
                        case 'W':
                            strcpy(tstr, "STAIR2");
                            break;
                        case 'X':
                            strcpy(tstr, "STAIR2");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 33; iy = 26;
                    } else {
                        ix = 34; iy = 26;
                    }
                    break;
                case 'B':
                    switch (tmap[2][3]) {
                        case '[':
                            strcpy(tstr, "BACESP2");
                            break;
                        case '~':
                            strcpy(tstr, "BACESBT2");
                            break;
                        case '*':
                            strcpy(tstr, "BACESRD2");
                            break;
                        case '#':
                            strcpy(tstr, "BACESWS2");
                            break;
                        case '$':
                            strcpy(tstr, "BACESBT2");
                            break;
                        case '?':
                            strcpy(tstr, "BACESSD2");
                            break;
                        case 'W':
                            strcpy(tstr, "STAIR2");
                            break;
                        case 'X':
                            strcpy(tstr, "STAIR2");
                            break;

                    }
                    ix = 33; iy = 26;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }
        //  Position being checked :     1#####    ^     (angle)
        //                               2#####    |
        //                               3#*###    N
        //                                12345

        if (tmap[3][2] != ' ') {
            strcpy(tstr, " #");
            ix = 1; iy = 1;
            switch (holdter[3][2]) {
                case 'A':
                    switch (tmap[3][2]) {
                        case '~':
                            strcpy(tstr, "HALLBTL1");
                            break;
                        case '*':
                            strcpy(tstr, "HALLRDL1");
                            break;
                        case '#':
                            strcpy(tstr, "HALLWSL1");
                            break;
                        case '$':
                            strcpy(tstr, "HALLBTL1");
                            break;

                    }
                    break;
                case 'B':
                    switch (tmap[3][2]) {
                        case '~':
                            strcpy(tstr, "BALFLBT1");
                            break;
                        case '*':
                            strcpy(tstr, "BALFLRD1");
                            break;
                        case '#':
                            strcpy(tstr, "BALFLWS1");
                            break;
                        case '$':
                            strcpy(tstr, "BALFLBT1");
                            break;

                    }
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr);
            }
        }
        //  Position being checked :     1#####    ^     (angle)
        //                               2#####    |
        //                               3###*#    N
        //                                12345

        if (tmap[3][4] != ' ') {
            strcpy(tstr, " #");
            ix = 1; // RH: avoid C4701 on line below
            iy = (zvda->ripver > 1550) ? 56 : 50; // RH: avoid C4701 on line below
            switch (holdter[3][4]) {
                case 'A':
                    switch (tmap[3][4]) {
                        case '~':
                            strcpy(tstr, "HALLBTR1");
                            break;
                        case '*':
                            strcpy(tstr, "HALLRDR1");
                            break;
                        case '#':
                            strcpy(tstr, "HALLWSR1");
                            break;
                        case '$':
                            strcpy(tstr, "HALLBTR1");
                            break;

                    }
                    if (zvda->ripver > 1550) {
                        ix = 163; iy = 1;
                    } else {
                        ix = 162; iy = 1;
                    }
                    break;
                case 'B':
                    switch (tmap[3][4]) {
                        case '~':
                            strcpy(tstr, "BALFRBT1");
                            break;
                        case '*':
                            strcpy(tstr, "BALFRRD1");
                            break;
                        case '#':
                            strcpy(tstr, "BALFRWS1");
                            break;
                        case '$':
                            strcpy(tstr, "BALFRBT1");
                            break;

                    }
                    ix = 163; iy = 1;
                    break;
            }
            if (!samein("#", tstr)) {
                place_icon(ix, iy, tstr); // RH: C4701 here
            }
        }

    }

}
