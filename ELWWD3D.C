/*****************************************************************************
 *   ELWWD3D.C   V0.62                                  Worlds of Darkness   *
 *   General Drawing/Moving Prep Routines                                    *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 02/15/1995         *
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
#include "elwwdrfx.h"
#include "elwwd.h"
#include "elwwdtyp.h"
#include "elwwdglb.h"

VOID bonkme(VOID)
{
    CHAR k, l, mc;

    k = zmap->lvl[plevel].map[prow + face4][pcol + face5];
    mc = k;
    switch (mc) {
        case '$':
            if (zvda->spelltrue)
                bonk = FALSE;
            else
                bonk = TRUE;
            break;
        case '~':
        case '#':
            bonk = TRUE;
            break;
        case '*':
        case '%':
        case ' ':
            bonk = FALSE;
            break;
        default:
            bonk = TRUE;
    }
    if (k >= 'A' && k <= 'Z')
        bonk = FALSE;
    if (index(xpchars, k) != NOTFOUND)
        bonk = FALSE;
    if (k >= 'a' && k <= 'm') {
        k -= 'a';
        bonk = FALSE;
        for (l = 0; l < grates[plevel].levercnt[k]; l++)
            if (grates[plevel].leverstate[k][l] == 'u') {
                bonk = TRUE;
                break;
            }
    }
}

VOID spinme(VOID)
{

    if (zmap->lvl[plevel].map[prow][pcol] == '%')
        switch (pdirect) {
            case 1:
                pdirect = 3;
                break;
            case 2:
                pdirect = 4;
                break;
            case 3:
                pdirect = 1;
                break;
            case 4:
                pdirect = 2;
        }
}

VOID moveme(CHAR kkey)
{
    VDABLK* pvda;
    SHORT mi, mj, pl;
    USHORT dozt, hidoz, pdoz;

    if (zplyr->condition[2]) {
        if (zvda->pwtick != btuTicker()) { //ticker
            deccond('p', (SHORT)usrnum);
            if (zplyr->condition[2]) {
                zvda->pwtick = btuTicker(); //ticker;
            }
        }
    } else {
        deccond('p', (SHORT)usrnum);
    }

    prfmsg(YBLLN);
    outprf(usrnum);
    delinm();
    face4 = 0;
    face5 = 0;

    if (zvda->party == (SHORT)usrnum) {
        zvda->redraw = TRUE;
        pl = (SHORT)usrnum;
    } else {
        zvda->redraw = FALSE;
        pl = zvda->party;
    }

    if (zvda->clrbonk) {
        zvda->clrbonk = FALSE;
        prfmsg(WBLLN);
        outprf(usrnum);
    }

    switch (kkey) {
        case 'Q':
            saveplay();
            lparty((SHORT)usrnum);
            dispmain();
            bonk = FALSE;
            zvda->redraw = FALSE;
            break;
        case '6':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            if (zvda->party != usrnum) {
                qparty((SHORT)usrnum);
                zvda->redraw = TRUE;
                if (zvda->rip) arxy(1, 15);
                else arxy(1, 16);
                prfmsg(QPARTY);
                outprf(usrnum);
                clrprf();
                prfmsg(WAWAY, zplyr->name);
                xparty(pl);
            }
            if (direct1[pdirect] == 'N') face5 = 1;
            if (direct1[pdirect] == 'S') face5 = -1;
            if (direct1[pdirect] == 'E') face4 = 1;
            if (direct1[pdirect] == 'W') face4 = -1;
            bonkme();
            if (!bonk) {
                if (direct1[pdirect] == 'N')
                    pcol++;
                if (direct1[pdirect] == 'S')
                    pcol--;
                if (direct1[pdirect] == 'E')
                    prow++;
                if (direct1[pdirect] == 'W')
                    prow--;
                teleport();
                findshop();
            }
            break;
        case '8':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            if (zvda->party != usrnum) {
                qparty((SHORT)usrnum);
                zvda->redraw = TRUE;
                if (zvda->rip) arxy(1, 15);
                else arxy(1, 16);
                prfmsg(QPARTY);
                outprf(usrnum);
                clrprf();
                prfmsg(WAWAY, zplyr->name);
                xparty(pl);
            }
            if (direct1[pdirect] == 'N') face4 = -1;
            if (direct1[pdirect] == 'S') face4 = 1;
            if (direct1[pdirect] == 'E') face5 = 1;
            if (direct1[pdirect] == 'W') face5 = -1;
            bonkme();
            if (!bonk) {
                if (direct1[pdirect] == 'N')
                    prow--;
                if (direct1[pdirect] == 'S')
                    prow++;
                if (direct1[pdirect] == 'E')
                    pcol++;
                if (direct1[pdirect] == 'W')
                    pcol--;
                teleport();
                findshop();
            }
            break;
        case '2':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            if (zvda->party != usrnum) {
                qparty((SHORT)usrnum);
                zvda->redraw = TRUE;
                if (zvda->rip) arxy(1, 15);
                else arxy(1, 16);
                prfmsg(QPARTY);
                outprf(usrnum);
                clrprf();
                prfmsg(WAWAY, zplyr->name);
                xparty(pl);
            }
            if (direct1[pdirect] == 'N') face4 = 1;
            if (direct1[pdirect] == 'S') face4 = -1;
            if (direct1[pdirect] == 'E') face5 = -1;
            if (direct1[pdirect] == 'W') face5 = 1;
            bonkme();
            if (!bonk) {
                if (direct1[pdirect] == 'N')
                    prow++;
                if (direct1[pdirect] == 'S')
                    prow--;
                if (direct1[pdirect] == 'E')
                    pcol--;
                if (direct1[pdirect] == 'W')
                    pcol++;
                teleport();
                findshop();
            }
            break;
        case '4':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            if (zvda->party != usrnum) {
                qparty((SHORT)usrnum);
                zvda->redraw = TRUE;
                if (zvda->rip) arxy(1, 15);
                else arxy(1, 16);
                prfmsg(QPARTY);
                outprf(usrnum);
                clrprf();
                prfmsg(WAWAY, zplyr->name);
                xparty(pl);
            }
            if (direct1[pdirect] == 'N') face5 = -1;
            if (direct1[pdirect] == 'S') face5 = 1;
            if (direct1[pdirect] == 'E') face4 = -1;
            if (direct1[pdirect] == 'W') face4 = 1;
            bonkme();
            if (!bonk) {
                if (direct1[pdirect] == 'N')
                    pcol--;
                if (direct1[pdirect] == 'S')
                    pcol++;
                if (direct1[pdirect] == 'E')
                    prow--;
                if (direct1[pdirect] == 'W')
                    prow++;
                teleport();
                findshop();
            }
            break;
        case '7':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            if (zvda->party == usrnum)
                switch (direct1[pdirect]) {
                    case 'N': pdirect = 4;
                        break;
                    case 'W': pdirect = 3;
                        break;
                    case 'S': pdirect = 2;
                        break;
                    case 'E': pdirect = 1;
                        break;
                }
            bonk = FALSE;
            break;
        case '9':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            if (zvda->party == usrnum)
                switch (direct1[pdirect]) {
                    case 'N': pdirect = 2;
                        break;
                    case 'W': pdirect = 1;
                        break;
                    case 'S': pdirect = 4;
                        break;
                    case 'E': pdirect = 3;
                        break;
                }
            bonk = FALSE;
            break;
        case 'S':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            if (zvda->party == usrnum) {
                if (direct1[pdirect] == 'N') face4 = -1;
                if (direct1[pdirect] == 'S') face4 = 1;
                if (direct1[pdirect] == 'E') face5 = 1;
                if (direct1[pdirect] == 'W') face5 = -1;
                switchme();
            }
            break;
        case 'E':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            findshop();
            zvda->redraw = FALSE;
            break;
        case 'I':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            inventory();
            zvda->redraw = FALSE;
            break;
        case 'D':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            dropit();
            zvda->redraw = FALSE;
            break;
        case 'C':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            if (zplyr->currmp > 0) {
                castinit();
            } else {
                if (zvda->rip) arxy(1, 15);
                else arxy(1, 16);
                prfmsg(UHNOMP);
                outprf(usrnum);
            }
            zvda->redraw = FALSE;
            break;
        case 'W':
            zvda->mstate = 0;
            whodat();
            zvda->redraw = FALSE;
            break;
        case 'U':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            useinit();
            if (zvda->litcnt) {
                if (zvda->rip) arxy(1, 15);
                else arxy(1, 16);
                prfmsg(PICUSE);
                outprf(usrnum);
                pagemenu(26, zvda->litcnt, TRUE);
            } else {
                if (zvda->rip) arxy(1, 15);
                else arxy(1, 16);
                prfmsg(NOTHUSE);
                outprf(usrnum);
            }
            zvda->redraw = FALSE;
            break;
        case 'R':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            mj = 0;
            for (mi = 0; mi < MAXPOBJC; mi++) {
                zvda->mnuslt[mi] = 0;
                if (zvda->pstuff[mi].objname[0] != 0 &&
                    (zvda->pstuff[mi].otype == 0 ||
                        zvda->pstuff[mi].otype == 1)) {
                    mj++;
                    zvda->mnuslt[mi] = 1;
                }
            }
            zvda->litcnt = mj;
            if (mj) {
                if (zvda->rip) arxy(1, 15);
                else arxy(1, 16);
                prfmsg(PICEQU);
                outprf(usrnum);
                pagemenu(25, mj, TRUE);
            } else {
                if (zvda->rip) arxy(1, 15);
                else arxy(1, 16);
                prfmsg(NOTHEQU);
                outprf(usrnum);
            }
            zvda->redraw = FALSE;
            break;
        case 'T':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            zvda->redraw = FALSE;
            bonk = FALSE;
            talktest();
            if (zvda->ontop)
                gochat();
            break;
        case 'Z':
            if (zplyr->condition[2]) {
                prfmsg(STPLYZD);
                outprf(usrnum);
                zvda->redraw = FALSE;
                break;
            }
            if (zvda->party == usrnum) {
                hidoz = 0;
                for (mi = 0; mi < zvda->memcnt; mi++) {
                    mj = zvda->members[mi];
                    if (ingame[mj]) {
                        pvda = (VDABLK*)vdaoff(mj);
                        dozt = 0;
                        if (pvda->plyr.currhp < pvda->plyr.maxhp)
                            dozt = pvda->plyr.maxhp - pvda->plyr.currhp;
                        if (pvda->plyr.currmp < pvda->plyr.maxmp) {
                            pdoz = pvda->plyr.maxmp - pvda->plyr.currmp;
                            if (pdoz > dozt) {
                                pdoz -= dozt;
                                dozt += pdoz;
                            }
                        }
                        if (dozt > hidoz)
                            hidoz = dozt;
                    }
                }
                if (hidoz > 0) {
                    zvda->pwtick = btuTicker(); //ticker;
                    clrprf();
                    if (zvda->memcnt == 1) {
                        prfmsg(UDOZ);
                        outprf(usrnum);
                        zvda->obn = hidoz;
                        usrptr->substt = CAMPIN;
                    } else {
                        prfmsg(TPID);
                        for (mi = 0; mi < zvda->memcnt; mi++) {
                            mj = zvda->members[mi];
                            if (ingame[mj]) {
                                pvda = (VDABLK*)vdaoff(mj);
                                pvda->obn = hidoz;
                                pvda->myuser->substt = CAMPIN;
                                pvda->rdlife = FALSE;
                                outprf(mj);
                            }
                        }
                    }
                } else {
                    prfmsg(UNNSZ);
                    outprf(usrnum);
                }
            } else {
                prfmsg(OTLCS);
                outprf(usrnum);
            }
            zvda->redraw = FALSE;
            break;
        case 'G':
            bonk = FALSE;
            zvda->redraw = FALSE;
            if (!chkdrop()) {
                prfmsg(WBLLN);
                prfmsg(NUTHN);
                outprf(usrnum);
            } else {
                zvda->cshop = 0;
                zvda->mstate = 0;
                usrptr->substt = 46;
            }
            break;
        case ' ':
            restplay();
            bonk = FALSE;
            zvda->redraw = FALSE;
            break;
        case 'Y':
            bonk = FALSE;
            zvda->redraw = FALSE;
            zvda->mstate = 0;
            eyespy();
            break;
        case '+':
            bonk = FALSE;
            zvda->nstat = FALSE;
            zvda->redraw = FALSE;
            vstat();
            break;
        case 'N':
            bonk = FALSE;
            zvda->redraw = FALSE;
            if (zvda->party == usrnum) {
                prfmsg(EUSRN);
                outprf(usrnum);
                usrptr->substt = 33;
            } else {
                prfmsg(NLDRO);
                outprf(usrnum);
            }
            break;
        case 'B':
            bonk = FALSE;
            zvda->redraw = FALSE;
            if (zvda->party == usrnum) {
                delinm();
                prfmsg(EWMSG);
                outprf(usrnum);
                usrptr->substt = 38;
            } else {
                prfmsg(WLDRO);
                outprf(usrnum);
            }
            break;
            //  default: prf("Uknown key %c\n",kkey);
            //           outprf(usrnum);
    }
    if (bonk) {
        zvda->clrbonk = TRUE;
        if (zvda->rip) arxy(1, 15);
        else arxy(1, 16);
        prfmsg(HBANG);
        outprf(usrnum);
    } else if (zvda->redraw) {
        if (zvda->party != usrnum)
            zvda->pdraw = FALSE;
        if (zvda->party == usrnum && zvda->memcnt > 1)
            for (mi = 1; mi < zvda->memcnt; mi++) {
                mj = zvda->members[mi];
                pvda = (VDABLK*)vdaoff(mj);
                if (ingame[mj] && pvda->gstate == PLAYING) {
                    pvda->plyr.direct = pdirect;
                    pvda->plyr.curlvl = plevel;
                    pvda->plyr.row = prow;
                    pvda->plyr.col = pcol;
                    pvda->pdraw = TRUE;
                }
            }
        setwall();
        draw();
    }
}

VOID teleport(VOID)
{
    CHAR i;

    if (index(xpchars, zmap->lvl[plevel].map[prow][pcol]) != NOTFOUND) {
        for (i = 0; i < xpcount[plevel]; i++) {
            if (xports[plevel].xportx[i] != pcol &&
                xports[plevel].xporty[i] != prow &&
                xports[plevel].xportc[i] == zmap->lvl[plevel].map[prow][pcol]) {
                pcol = xports[plevel].xportx[i];
                prow = xports[plevel].xporty[i];
                switch (pdirect) {
                    case 1:
                        pdirect = 3;
                        break;
                    case 2:
                        pdirect = 4;
                        break;
                    case 3:
                        pdirect = 1;
                        break;
                    case 4:
                        pdirect = 2;
                        break;
                }
                break;
            }
        }
        if (i == xpcount[plevel]) {
            arxy(1, 15);
            prf("No match for xp");
            outprf(usrnum);
        }
    }
}

VOID switchme(VOID)
{
    CHAR di, dj, dk, dl;
    di = (CHAR)(prow + face4);
    dj = (CHAR)(pcol + face5);
    dk = lookahead();
    if (dk >= 'n' && dk <= 'z') {
        dk -= 'n';
        for (dl = 0; dl < grates[plevel].levercnt[dk]; dl++) {
            if (grates[plevel].leverrow[dk][dl] == di &&
                grates[plevel].levercol[dk][dl] == dj)
                break;
        }
        if (dl < grates[plevel].levercnt[dk]) {
            if (grates[plevel].leverstate[dk][dl] == 'u')
                grates[plevel].leverstate[dk][dl] = 'd';
            else
                grates[plevel].leverstate[dk][dl] = 'u';
        } else {
            prf("whoops cant find the lever\n");
            outprf(usrnum);
        }
    } else {
        prf("Flip what?\n");
        outprf(usrnum);
    }
}

VOID draw(VOID)
{
    USHORT i, j;
    CHAR kk;
    if (zvda->rip) {
        drawripbox(0, 154, 632, 210, 0, 0, 0, 1);
        drawstats();
        drawmsg();
        return;
    }
    prfmsg(WBLLN);
    outprf(usrnum);
    arxy(1, 1);
    prfmsg(TBORD);
    for (i = 1; i <= 12; i++) {
        cvstr(wall[i]);
        prfmsg(LBORD);
        drawcolor(wall[i]);
        prfmsg(RBORD);
    }
    prfmsg(BBORD);
    outprf(usrnum);
    for (i = 0; i < 7; i++) {
        arxy(30, i + 2);
        for (j = 0; j < 7; j++)
            prf("%c", zvda->oview[i][j]);
        outprf(usrnum);
    }
    /* Display any special stuff, Inns, etc. */
    kk = lookahead();
    if (index(textletters, kk) != NOTFOUND || (kk >= 'a' && kk <= 'm') ||
        index(xpchars, kk) != NOTFOUND) {
        if (kk >= 'a' && kk <= 'm')
            kk = 'Z';
        if (index(xpchars, kk) != NOTFOUND)
            kk = 'L';
        arxy(1, 15);
        prf("                                                          ");
        outprf(usrnum);
        arxy(1, 15);
        switch (kk) {
            case 'A':
                prfmsg(UCBANK);
                break;
            case 'B':
                prfmsg(UCWARGLD);
                break;
            case 'C':
                prfmsg(UCWIZGLD);
                break;
            case 'D':
                prfmsg(UCCHURCH);
                break;
            case 'E':
                prfmsg(UCJAIL);
                break;
            case 'F':
                prfmsg(UCGSHOP);
                break;
            case 'G':
                prfmsg(UCINN);
                break;
            case 'H':
                prfmsg(UCTAVRN);
                break;
            case 'I':
                prfmsg(UCCASINO);
                break;
            case 'J':
                prfmsg(UCWSHOP);
                break;
            case 'K':
                prfmsg(UCTHVGLD);
                break;
            case 'L':
                prfmsg(UCXPORT);
                break;
            case 'P':
                prfmsg(UCPALIS);
                break;
            case 'Q':
                prfmsg(UCARENA);
                break;
            case 'W':
                prfmsg(UCSTUP);
                break;
            case 'X':
                prfmsg(UCSTDWN);
                break;
            case 'Z':
                prfmsg(UCDOOR2);
                break;
            case '*':
                prfmsg(UCDOOR1);
                break;
            default:
                prfmsg(NUTHN);
        }
        outprf(usrnum);
    } else {
        arxy(1, 15);
        prf("                                                          ");
        arxy(1, 15);
        outprf(usrnum);
    }
    drawstats();
    drawmsg();
}

VOID setcompass(VOID)
{
    CHAR arm[35], cp;
    USHORT j, k;

    if (zvda->rip) {
        if (zplyr->condition[8]) {  // Compass
            switch (pdirect) {
                case 1:
                    place_icon(184, 230, "COMPN.ICN");
                    break;
                case 2:
                    place_icon(184, 230, "COMPE.ICN");
                    break;
                case 3:
                    place_icon(184, 230, "COMPS.ICN");
                    break;
                case 4:
                    place_icon(184, 230, "COMPW.ICN");
                    break;
                default: break;
            }
        }
        if (zplyr->condition[9]) {  // Locator
            drawripbox(196, 298, 218, 309, 0, 0, 0, 1); /* Clear Locator Stuff */
            drawripbox(241, 298, 263, 309, 0, 0, 0, 1);
            rip_font_style(2, 0, 4, 0);
            itoa(prow, arm, 10);
            riptext(198, 297, 15, arm);
            itoa(pcol, arm, 10);
            riptext(243, 297, 15, arm);
        }
    } else {
        if (zplyr->condition[8]) {  // Compass
            switch (pdirect) {
                case 1:
                    cp = 'N';
                    break;
                case 2:
                    cp = 'E';
                    break;
                case 3:
                    cp = 'S';
                    break;
                case 4:
                    cp = 'W';
                    break;
                default:
                    cp = ' ';
            }
            arxy(51, 12);
            prf("%c", cp);
            outprf(usrnum);
        }
        if (zplyr->condition[9]) {  // Locator
            arxy(73, 12);
            j = prow;
            k = pcol;
            prf("%u %u", k, j);
            outprf(usrnum);
        }
    }
}

VOID ripstats(VOID)
{
    CHAR arm[35], pwep[35], swep[35], health[35];
    USHORT i, j;
    UINT pck;

    strcpy(pwep, "None");
    strcpy(swep, "None");
    strcpy(arm, "None");
    prf("\n");
    outprf(usrnum);
    for (i = 0; i < MAXPOBJC; i++)
        if (zvda->pstuff[i].objname[0] != 0 &&
            zvda->pstuff[i].otype == 0 &&
            (zvda->pstuff[i].ospot == 5 ||
                zvda->pstuff[i].ospot == 6) &&
            zplyr->equip[i] == 1)
            break;
    if (i < MAXPOBJC) {
        strcpy(pwep, zvda->pstuff[i].objname);
        i++;
        for (j = i; j < MAXPOBJC; j++)
            if (zvda->pstuff[j].objname[0] != 0 &&
                zvda->pstuff[j].otype == 0 &&
                (zvda->pstuff[j].ospot == 5 ||
                    zvda->pstuff[j].ospot == 6) &&
                zplyr->equip[j] == 1)
                break;
        if (j < MAXPOBJC) {
            strcpy(swep, zvda->pstuff[j].objname);
        }
    }
    for (i = 0; i < MAXPOBJC; i++)
        if (zvda->pstuff[i].objname[0] != 0 &&
            zvda->pstuff[i].otype == 1 &&
            zplyr->equip[i] == 1)
            break;
    if (i < MAXPOBJC) {
        strcpy(arm, zvda->pstuff[i].objname);
    }
    if (zplyr->enckills > 0)
        pck = (UINT)(zplyr->enckills * 100 / (zplyr->enckills + zplyr->encloss));
    else
        pck = 0;
    if (zplyr->condition[1])
        strcpy(health, "Poisoned");
    else
        strcpy(health, "Healthy");
    prfmsg(COMPDAT, zplyr->currhp, zplyr->maxhp, zplyr->currmp, zplyr->maxmp,
        l2as(zplyr->exp), l2as(zvda->needed), zvda->lac,
        zplyr->level, l2as(zplyr->cash), health,
        arm, pwep, swep, l2as(zplyr->enckills), pck);
    drawripbox(230, 24, 300, 80, 0, 0, 0, 1);
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++)
            if (zvda->oview[i][j] != ' ')
                riptext(230 + (i * 10), 24 + (j * 8), 16, spr("%c", zvda->oview[i][j]));
    }
    setcompass();
}

VOID drawstats(VOID)
{
    ULONG pck;
    USHORT i, j, k;
    VDABLK* svda;
    static CHAR* cnams[] = { "Drunk","Poisoned","Paralyzed",
      "Shielded" };
    CHAR con[4][11] = { 0 };
    SHORT cxpos[] = { 40,46,55,65 },
        pospos[] = { 0,1,2,4 };

    switch (zvda->stmode) {
        default: zvda->stmode = 0;
        case 0:
            chkexp();
            if (zvda->nstat) {
                if (zvda->rip) {
                    ripstats();
                } else {
                    arxy(70, 2);
                    prf("[0;32m%u", zplyr->maxhp);
                    arxy(48, 2);
                    prf("%u", zplyr->currhp);
                    arxy(48, 5);
                    prf("%u", zvda->lac);
                    outprf(usrnum);
                    arxy(48, 6);
                    prf("%s", l2as(zplyr->cash));
                    arxy(48, 4);
                    prf("%s", l2as(zplyr->exp));
                    arxy(70, 5);
                    prf("%u", zplyr->level);
                    for (i = 0; i < MAXPOBJC; i++)
                        if (zvda->pstuff[i].objname[0] != 0 &&
                            zvda->pstuff[i].otype == 0 &&
                            (zvda->pstuff[i].ospot == 5 ||
                                zvda->pstuff[i].ospot == 6) &&
                            zplyr->equip[i] == 1)
                            break;
                    if (i < MAXPOBJC) {
                        arxy(48, 8);
                        prf("%s", zvda->pstuff[i].objname);
                        outprf(usrnum);
                        i++;
                        for (j = i; j < MAXPOBJC; j++)
                            if (zvda->pstuff[j].objname[0] != 0 &&
                                zvda->pstuff[j].otype == 0 &&
                                (zvda->pstuff[j].ospot == 5 ||
                                    zvda->pstuff[j].ospot == 6) &&
                                zplyr->equip[j] == 1)
                                break;
                        if (j < MAXPOBJC) {
                            arxy(48, 9);
                            prf("%s", zvda->pstuff[j].objname);
                            outprf(usrnum);
                        }
                    }
                    for (i = 0; i < MAXPOBJC; i++)
                        if (zvda->pstuff[i].objname[0] != 0 &&
                            zvda->pstuff[i].otype == 1 &&
                            zplyr->equip[i] == 1)
                            break;
                    if (i < MAXPOBJC) {
                        arxy(48, 7);
                        prf("%s", zvda->pstuff[i].objname);
                        outprf(usrnum);
                    }
                    arxy(50, 11);
                    prf("%s", l2as(zplyr->enckills));
                    outprf(usrnum);
                    arxy(73, 11);
                    if (zplyr->enckills > 0)
                        pck = zplyr->enckills * 100 / (zplyr->enckills + zplyr->encloss);
                    else
                        pck = 0;
                    prf("%s", l2as(pck));
                    outprf(usrnum);
                    for (i = 0; i < 15; i++) {
                        for (k = 0; k < 5; k++)
                            if (zvda->pclass.mage[i * 5][k] != 0 ||
                                zvda->pclass.priest[i * 5][k] != 0)
                                break;
                        if (k < 5)
                            break;
                    }
                    if (i < 15) {
                        arxy(48, 3);
                        prf("%u", zplyr->currmp);
                        arxy(70, 3);
                        prf("%u", zplyr->maxmp);
                        outprf(usrnum);
                    } else {
                        arxy(48, 3);
                        prf("N/A");
                        arxy(70, 3);
                        prf("N/A");
                        outprf(usrnum);
                    }
                    if (zplyr->condition[1])
                        prfmsg(PIZLIN);
                    else
                        prfmsg(HELTY);
                    outprf(usrnum);
                }
            }
            setcompass();
            if (chkdrop()) {
                prfmsg(SUMMAT);
                outprf(usrnum);
            } else {
                dodrunk();
            }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            svda = (VDABLK*)vdaoff(zldr->members[zvda->stmode - 1]);
            if (zvda->rip) {
                for (i = 0; i < 4; i++) {
                    if (svda->plyr.condition[pospos[i]]) strcpy(con[i], cnams[i]);
                    else strcpy(con[i], " ");
                }
                i = acplyr(zldr->members[zvda->stmode - 1]);
                prfmsg(PLSTAT, svda->plyr.name, svda->plyr.currhp, svda->plyr.maxhp,
                    svda->plyr.attrib[0], svda->prace.maxability[0],
                    svda->plyr.currmp, svda->plyr.maxmp,
                    svda->plyr.attrib[1], svda->prace.maxability[1],
                    svda->plyr.new_age,
                    svda->plyr.attrib[2], svda->prace.maxability[2],
                    svda->plyr.level,
                    svda->plyr.attrib[3], svda->prace.maxability[3],
                    svda->pclass.name,
                    svda->plyr.attrib[4], svda->prace.maxability[4],
                    svda->prace.name,
                    svda->plyr.attrib[5], svda->prace.maxability[5],
                    l2as(svda->plyr.exp),
                    svda->plyr.attrib[6], svda->prace.maxability[6],
                    l2as(svda->plyr.cash), i, con[0], con[1], con[2], con[3]);
                outprf(usrnum);
            } else {
                prfmsg(PLSTAT);
                outprf(usrnum);
                arxy(51, 1);
                prf("%s", svda->plyr.name);
                outprf(usrnum);
                arxy(48, 2);
                prf("%d/%d", svda->plyr.currhp, svda->plyr.maxhp);
                outprf(usrnum);
                arxy(48, 3);
                prf("%d/%d", svda->plyr.currmp, svda->plyr.maxmp);
                outprf(usrnum);
                arxy(48, 4);
                prf("%d/%d", svda->plyr.new_age, svda->plyr.age);
                outprf(usrnum);
                arxy(48, 5);
                prf("%d", svda->plyr.level);
                outprf(usrnum);
                arxy(48, 6);
                prf("%s", svda->pclass.name);
                outprf(usrnum);
                arxy(48, 7);
                prf("%s", svda->prace.name);
                outprf(usrnum);
                arxy(48, 8);
                prf("%s", l2as(svda->plyr.exp));
                outprf(usrnum);
                arxy(48, 9);
                prf("%s", l2as(svda->plyr.cash));
                outprf(usrnum);
                for (i = 0; i < 7; i++) {
                    arxy(70, 2 + i);
                    prf("%d/%d", svda->plyr.attrib[i],
                        svda->prace.maxability[i]);
                    outprf(usrnum);
                }
                i = acplyr(zldr->members[zvda->stmode - 1]);
                arxy(70, 9);
                prf("%u", i);
                outprf(usrnum);
                for (i = 0; i < 4; i++) {
                    if (svda->plyr.condition[pospos[i]]) {
                        arxy(cxpos[i], 11);
                        prf("%s", cnams[i]);
                        outprf(usrnum);
                    }
                }
            }
            break;
    }
    zvda->nstat = FALSE;
}

CHAR lookahead(VOID)
{
    CHAR rchar;
    SHORT f4 = 0, f5 = 0;

    switch (direct1[pdirect]) {
        case 'N':
            f4 = -1;
            break;
        case 'S':
            f4 = 1;
            break;
        case 'E':
            f5 = 1;
            break;
        case 'W':
            f5 = -1;
    }
    rchar = zmap->lvl[plevel].map[prow + f4][pcol + f5];
    return(rchar);
}

VOID checkstuff(USHORT l, USHORT r, USHORT c)
{
    SHORT ixpos;
    curxy = zmap->lvl[l].map[r][c];
    terrain = zterrain->lvl[l].map[r][c];
    if (curxy == '$' || curxy == '#') {
        if (curxy == '$' && zvda->spelltrue)
            curxy = ' ';
        else
            curxy = '#';
        doorishere = FALSE;
    }
    if (((curxy >= 'A' && curxy <= 'Z') && (curxy != 'W' && curxy != 'Z')) ||
        curxy == '*') {
        if ((ixpos = index(textletters, curxy)) != NOTFOUND) {
            somethingthere = textletters[ixpos];
            somethingthere1 = (CHAR)ixpos;
            doorishere = TRUE;
        }
    }
}

VOID bldoview(VOID)
{
    VDABLK* tvda;
    SHORT i, j, k = 0;
    CHAR tch = 'A', orow, ocol, lcol, rcol, trow, brow;

    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            zvda->oview[i][j] = ' ';
    for (i = 0; i < 49; i++)
        zvda->ovchn[i] = (SHORT)nterms;

    lcol = pcol - 3;
    rcol = pcol + 3;
    trow = prow - 3;
    brow = prow + 3;
    zvda->oldont = zvda->ontop;
    zvda->ontop = FALSE;

    for (i = 0; i < nterms; i++)
        if (ingame[i]) {
            tvda = (VDABLK*)vdaoff(i);
            if (tvda->plyr.curlvl == plevel && !tvda->dead) {
                orow = tvda->plyr.row;
                ocol = tvda->plyr.col;
                if ((orow >= trow && orow <= brow) &&
                    (ocol >= lcol && ocol <= rcol)) {
                    if (i == usrnum)
                        zvda->oview[orow - trow][ocol - lcol] = 'U';
                    else {
                        zvda->ovchn[k] = i;
                        k++;
                        zvda->oview[orow - trow][ocol - lcol] = tch++;
                    }
                }
            }
        }
}

VOID setwall(VOID)
{
    static SHORT count, row, col;

    bldoview();
    if (zvda->movingaround) {
        for (row = 1; row <= TMROW; row++) {
            for (col = 1; col <= TMCOL; col++) {
                holdmap[row][col] = ' ';
                holdter[row][col] = ' ';
            }
        }
        doorishere = FALSE;
        switch (pdirect) {
            case 1:
                xyloc[0] = -3;              /* North */
                xyloc[1] = 1;
                xyloc[2] = -2;
                xyloc[3] = 1;
                break;
            case 2:
                xyloc[0] = 3;               /* East */
                xyloc[1] = -1;
                xyloc[2] = -2;
                xyloc[3] = 1;
                break;
            case 3:
                xyloc[0] = 3;               /* South */
                xyloc[1] = -1;
                xyloc[2] = 2;
                xyloc[3] = -1;
                break;
            case 4:
                xyloc[0] = -3;              /* West */
                xyloc[1] = 1;
                xyloc[2] = 2;
                xyloc[3] = -1;
        }
        switch (pdirect) {
            case 1:
            case 3:
                count = xyloc[2];
                for (row = 1; row <= TMROW; row++) {
                    xyloc[2] = count;
                    for (col = 1; col <= TMCOL; col++) {
                        truerow[row][col] = prow + xyloc[0];
                        truecol[row][col] = pcol + xyloc[2];
                        checkstuff(plevel, truerow[row][col], truecol[row][col]);
                        holdmap[row][col] = curxy;
                        holdter[row][col] = terrain;
                        xyloc[2] += xyloc[3];
                    }
                    xyloc[0] += xyloc[1];
                }
                break;
            case 2:
            case 4:
                count = xyloc[2];
                for (row = 1; row <= TMROW; row++) {
                    xyloc[2] = count;
                    for (col = 1; col <= TMCOL; col++) {
                        truerow[row][col] = prow + xyloc[2];
                        truecol[row][col] = pcol + xyloc[0];
                        checkstuff(plevel, truerow[row][col], truecol[row][col]);
                        holdmap[row][col] = curxy;
                        holdter[row][col] = terrain;
                        xyloc[2] += xyloc[3];
                    }
                    xyloc[0] += xyloc[1];
                }
                break;
        }
        if (zvda->rip)
            rip3d();
        else {
            draw3d();
            fill3d();
        }

    }
}
