/*****************************************************************************
 *   ELWWDRIP.C   V0.62                                 Worlds of Darkness   *
 *   RIP Routines                                                            *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 09/25/1994         *
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
#include "filexfer.h"
#include "majorbbs.h"
#include "elwwdrfx.h"
#include "elwwd.h"
#include "elwwdtyp.h"
#include "elwwdglb.h"

static RIP_ICONS rip1[MAXICNS], rip2[MAXICNS];  // Build lists for icons...

// ************************************************************************
// Code starts beyond this point

VOID show_title(VOID)
{
    echon();
    prfmsg(TITLE);
    outprf(usrnum);
}

VOID build_icons(VOID)
{
    struct ffblk impfb; // was fndblk
    CHAR impmask[60], thedate[9],
        testicn[13];
    SHORT done;

    arip1 = 0; arip2 = 0;
    strcpy(impmask, "ELWWD\\RIP154\\");
    strcat(impmask, "*.*");
    done = fnd1st(&impfb, impmask, 0); // was fnd1st
    while (done) {
        if (!sameas("WODTEST.TXT", impfb.ff_name)) {
            strcpy(rip1[arip1].name, impfb.ff_name);
            strcpy(rip1[arip1].date, ncdate(impfb.ff_fdate));
            arip1++;
        } else {
            strcpy(testicn, impfb.ff_name);
            strcpy(thedate, ncdate(impfb.ff_fdate));
        }
        done = fndnxt(&impfb);
    }
    strcpy(rip1[arip1].name, testicn);
    strcpy(rip1[arip1].date, thedate);
    strcpy(impmask, "ELWWD\\RIP20\\");
    strcat(impmask, "*.*");
    done = fnd1st(&impfb, impmask, 0); // was fnd1st
    while (done) {
        if (!sameas("WODTEST.TXT", impfb.ff_name)) {
            strcpy(rip2[arip2].name, impfb.ff_name);
            strcpy(rip2[arip2].date, ncdate(impfb.ff_fdate));
            arip2++;
        } else {
            strcpy(testicn, impfb.ff_name);
            strcpy(thedate, ncdate(impfb.ff_fdate));
        }
        done = fndnxt(&impfb);
    }
    strcpy(rip2[arip2].name, testicn);
    strcpy(rip2[arip2].date, thedate);
}

INT tshdnl(INT tshcod)
{
    INT rc = 1;

    zvda = (VDABLK*)vdaptr;
    setmbk(msgblk);
    switch (tshcod) {
        case TSHVIS:                       /* Visible to this user?           */
            break;
        case TSHDSC:                       /* Describe the file(s) in English */
            sprintf(tshmsg, "Icon %s", zvda->dlf);
            break;
        case TSHSCN:                       /* Multiple file breakdown         */
            rc = 2;
            break;
        case TSHNXT:                       /* Next file in the list           */
            if (zvda->ripver > 1550)
                strcpy(zvda->dlf, rip2[zvda->dlme[zvda->scanmax]].name);
            else
                strcpy(zvda->dlf, rip1[zvda->dlme[zvda->scanmax]].name);
            //          shocst("Get Next","Next:%s  INDX:%d  SCNMX:%d",zvda->dlf,zvda->dlme[zvda->scanmax],zvda->scanmax);
            zvda->scanmax++;
            if (sameas(zvda->curpos, "WODTEST.TXT")) rc = 0;
            strcpy(zvda->curpos, zvda->dlf);
            break;
        case TSHBEG:                       /* Begin downloading this file     */
            rip_enter_block_mode(0, 5, 2, 0, spr("%s<>", zvda->dlf));
            sprintf(tshmsg, spr("%s\\%s", zvda->rip_path, zvda->dlf));
            strcpy(ftfscb->fname, zvda->dlf);
            break;
        case TSHEND:                       /* End of downloading session      */
            prfmsg(CLRSCR);
            break;
        case TSHSKP:                       /* End of downloading session      */
            prfmsg(CLRSCR);
            prf("\n\nGame can not be played without the icons.  Sorry.\n");
            outprf(usrnum);
            rc = 0;      // Abort session totally....
            break;
        case TSHFIN:
            prfmsg(CLRSCR);
            zvda->nxtstt = 0;
            zvda->scan = 0;
            rip_file_query(3, 0, "WODTEST.TXT");
            zvda->curfile = -1;
            usrptr->substt = 4;
            zvda->nxtstt = 0;
            usrptr->state = modnum;
            break;
    }
    rstmbk();
    return(rc);
}

VOID send_icons(VOID)
{
    //SHORT ctr;

    if (ftgnew() == 0) {
        prfmsg(CLRSCR);
        ftgsbm("");
        return;
    }
    arxy(1, 8);
    zvda->scanmax = 0;
    prf("You need to update %d files...  Standby transmitting...\n", zvda->curfile);
    outprf(usrnum);
    if (zvda->ripver > 1550) strcpy(zvda->dlf, rip2[zvda->dlme[zvda->scanmax]].name);
    else strcpy(zvda->dlf, rip1[zvda->dlme[zvda->scanmax]].name);
    if (zvda->curfile > 1) {
        ftgptr->flags |= FTGWLD;
    }
    strcpy(ftgptr->tagspc, zvda->dlf);
    ftgptr->tshndl = tshdnl;
    ftgsbm("B");
}

VOID misc_rip_detect(VOID)
{  // USRPTR->SUBSTT=1  (cycle)
    SHORT ci, ctr;
    CHAR impline[81], testnum[10];

    switch (zvda->nxtstt) {
        case 0: prfmsg(CLRSCR);
            prf("Standby WOD Auto Sensing....");
            btuech(usrnum, 0);
            prf("\n[!");
            outprf(usrnum);
            zvda->nxtstt = 1;
            zvda->scan = 0;
            zvda->tick = btuTicker() + 2;  //ticker
            btuinj(usrnum, CYCLE);
            break;
        case 1: if (zvda->tick == btuTicker()) {  //ticker
            zvda->nxtstt = 2;
        }
              btuinj(usrnum, CYCLE);
              break;
        case 2: ctr = (SHORT)btuica(usrnum, impline, 14);
            if (ctr > 0) {
                btucli(usrnum);
                strcpy(testnum, "     ");
                testnum[0] = impline[9];
                testnum[1] = impline[10];
                testnum[2] = impline[11];
                testnum[3] = impline[12];
                ci = (SHORT)atoi(testnum);
                zvda->ripver = ci;
                if (ci > 1550) strcpy(zvda->rip_path, "ELWWD\\RIP20");
                else strcpy(zvda->rip_path, "ELWWD\\RIP154");
                //              shocst(spr("RIP: %d",ci)," ");
                if (ci > 1550 && ver_rip != 2) {
                    prfmsg(NOR20);
                    btutrg(usrnum, 4);
                    outprf(usrnum);
                    usrptr->substt = 2;
                    zvda->curlang = (SHORT)clingo;
                    ctr = (SHORT)lngfnd("English/ANSI");
                    clingo = usrptr->lingo = ctr; //extptr->lingo
                    zvda->rip = FALSE;
                    echon();
                    btuinj(usrnum, CYCLE);
                } else {
                    zvda->rip = TRUE;
                    usrptr->substt = 4;
                    zvda->nxtstt = 0;
                    zvda->scan = 0;
                    rip_file_query(3, 0, "WODTEST.TXT");
                    nocycle();
                }
            } else {
                echon();
                show_title();
                btutrg(usrnum, 4);
                zvda->nxtstt = 98;
                zvda->curlang = (SHORT)clingo;
                ctr = (SHORT)lngfnd("English/ANSI");
                clingo = usrptr->lingo = ctr; // extptr->lingo
                zvda->rip = FALSE;
                btuinj(usrnum, CYCLE);
            }
            break;
        case 5: if (btuica(usrnum, kpress, 4) > 0) {
            btucli(usrnum);
            zvda->nxtstt = 6;
        }
              btuinj(usrnum, CYCLE);
              break;
        case 6: if (ver_rip == 1 && zvda->ripver > 1550) {
            prfmsg(NOR20);
            echon();
            outprf(usrnum);
            zvda->curlang = (SHORT)clingo;
            ctr = (SHORT)lngfnd("English/ANSI");
            clingo = usrptr->lingo = ctr;
            zvda->rip = FALSE;
            usrptr->substt = 2;
            zvda->redraw = TRUE;
        } else zvda->nxtstt = 99;
              btuinj(usrnum, CYCLE);
              break;
    }
}

SHORT check_icons(VOID)
{// USRPTR->SUBSTT=4  (nocycle)
    SHORT rc = 1, ctr, ctr1, ctr2 = 0;
    CHAR thedate[9], impline[81];

    switch (zvda->nxtstt) {
        case 0: btuech(usrnum, 0);
            if (strlen(margv[0]) > 0) {  // Check WODTEST.TXT file.....
                strcpy(impline, spr("%s.--/--/--.--/--/--.--/--/--.--/--/--", margv[0]));
                strcpy(zvda->chkdate, "00/00/00");
                ctr = 0;
                do {
                    if (impline[ctr] != '.') ctr++;
                    else {
                        ctr++;
                        ctr2++;
                        if (ctr2 == 2) {
                            for (ctr1 = 0; ctr1 < 8; ctr1++)
                                zvda->chkdate[ctr1] = impline[ctr + ctr1];
                            break;
                        }
                    }
                } while (ctr2 != 2);
                if (zvda->ripver > 1550) strcpy(thedate, rip2[arip2].date);
                else strcpy(thedate, rip1[arip1].date);
                //               shocst(spr("%s <> %s",zvda->chkdate,thedate)," ");
                if (!sameas(zvda->chkdate, thedate)) {
                    prfmsg(MISICNS);
                    outprf(usrnum);
                    zvda->scan = 0;  // Scan all icons....
                    zvda->scanmax = 0;
                    zvda->curfile = 0;
                    zvda->nxtstt = 1;
                    for (ctr = 0; ctr > MAXICNS; ctr++) zvda->dlme[ctr] = -1;
                    if (zvda->ripver > 1550)
                        rip_file_query(3, 0, rip2[zvda->scan].name);
                    else
                        rip_file_query(3, 0, rip1[zvda->scan].name);
                    zvda->nxtstt = 1;
                } else {
                    setcycle();
                    if (ver_rip == 2) {
                        show_title();
                        setcycle();
                        usrptr->substt = 2;
                        zvda->redraw = TRUE;
                    } else {
                        setcycle();
                        show_title();
                        usrptr->substt = 1;
                        zvda->nxtstt = 5;
                    }
                }
            } else rip_file_query(3, 0, "WODTEST.TXT");
            break;
        case 1: if (margv[0][0] == '0') {  // ICON is missing!
            zvda->dlme[zvda->curfile] = zvda->scan;
            arxy(1, 8);
            if (zvda->ripver > 1550)
                prf("Checking icon %d of %d  Needed : %d      ", zvda->scan, arip2, zvda->curfile);
            else prf("Checking icon %d of %d  Needed : %d      ", zvda->scan, arip1, zvda->curfile);
            outprf(usrnum);
            //               shocst("Missing file","ICN:%s CUR:%d SCN:%d",rip1[zvda->scan].name,zvda->curfile,zvda->scan);
            zvda->curfile++;
        } else {
            arxy(1, 8);
            if (zvda->ripver > 1550)
                prf("Checking icon %d of %d  Needed : %d      ", zvda->scan, arip2, zvda->curfile);
            else prf("Checking icon %d of %d  Needed : %d      ", zvda->scan, arip1, zvda->curfile);
            outprf(usrnum);
            strcpy(impline, spr("%s.--/--/--.--/--/--.--/--/--.--/--/--", margv[0]));
            strcpy(zvda->chkdate, "00/00/00");
            ctr = 0;
            do {
                if (impline[ctr] != '.') ctr++;
                else {
                    ctr++;
                    ctr2++;
                    if (ctr2 == 2) {
                        for (ctr1 = 0; ctr1 < 8; ctr1++)
                            zvda->chkdate[ctr1] = impline[ctr + ctr1];
                        break;
                    }
                }
            } while (ctr2 != 2);
            if (zvda->ripver > 1550) strcpy(thedate, rip2[zvda->scan].date);
            else strcpy(thedate, rip1[zvda->scan].date);
            //               shocst(spr("%s<>%s",zvda->chkdate,thedate)," ");
            if (!sameas(zvda->chkdate, thedate)) {
                // Icon was incorrect, save and continue...
                zvda->dlme[zvda->curfile] = zvda->scan;
                zvda->curfile++;
            }
        }
              zvda->scan++;
              if ((zvda->scan > arip2 && zvda->ripver > 1550) || (zvda->scan > arip1 && zvda->ripver < 1551))
                  send_icons();
              else {
                  if (zvda->ripver > 1550) rip_file_query(3, 0, rip2[zvda->scan].name);
                  else rip_file_query(3, 0, rip1[zvda->scan].name);
              }
              break;
        case 2: if (ver_rip == 1 && zvda->ripver > 1550) {
            echon();
            prfmsg(NOR20);
            outprf(usrnum);
            zvda->curlang = (SHORT)clingo;
            ctr = (SHORT)lngfnd("English/ANSI");
            clingo = usrptr->lingo = ctr;
            zvda->rip = FALSE;
            setcycle();
            usrptr->substt = 2;
            zvda->redraw = TRUE;
        } else {
            usrptr->substt = 4;
            zvda->nxtstt = 0;
            rip_file_query(3, 0, "WODTEST.TXT");
        }
              break;
    }
    return(rc);
}

VOID setripcol(SHORT iii)
{
    if (zvda->rip && zvda->oldripcol != iii) {
        rip_color(iii);
        zvda->oldripcol = iii;
    }
}

VOID place_icon(SHORT x, SHORT y, CHAR* twall1)
{
    if (zvda->rip) {
        rip_load_icon(x, y, 0, 0, 1, 0, twall1);
    }
}

VOID showicon(CHAR* twall1)
{
    if (zvda->rip) {
        rip_font_style(2, 0, 4, 0);
        place_icon(0, 0, twall1);
    }
}

VOID riptext(SHORT ripx, SHORT ripy, SHORT col, CHAR* pstr)
{
    if (zvda->rip) {
        setripcol(col);
        rip_font_style(2, 0, 4, 0);
        rip_text_xy(ripx, ripy, pstr);
    }
}

VOID drawripbox(SHORT x1, SHORT y1, SHORT x2, SHORT y2, SHORT border, SHORT rcolor, SHORT color1, SHORT noreset)
{
    if (zvda->rip) {
        if (border != 0) {
            rip_color(rcolor);
            rip_rectangle(x1 - 1, y1 - 1, x2 + 1, y2 + 1);
        }
        rip_color(color1);
        rip_bar(x1, y1, x2, y2);
        if (!noreset) rip_kill_mouse_fields();
    }
}

VOID wsound(SHORT noise)
{
    static CHAR* narray[] = { "BEEP","BLIP","MUSIC" };

    if (zvda->rip) rip_query(0, 0, narray[noise]);
}

VOID rip_clrscr(VOID)
{
    if (zvda->rip)
        td_writeln("\n!|1K|*|w0000000000|#|#|#\n");
    else {
        prf("[2J");
        outprf(usrnum);
    }
}
