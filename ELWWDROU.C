/*****************************************************************************
 *   ELWWDROU.C   V0.62                                 Worlds of Darkness   *
 *   Misc Routines                                                           *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 02/06/1995         *
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

 // TODO: File needs linting

#include "gcomm.h"
#include "brkthu.h"
#include "majorbbs.h"
#include "elwwd.h"
#include "elwwdtyp.h"
#include "elwwdglb.h"
#include "elwwdrfx.h"

VOID drawmsg(VOID)
{
    ULONG wpos;
    size_t j;//=0;
    CHAR wstr[73] = { 0 };

    wstr[0] = 0;
    if (wwall != NULL) {
        wpos = (plevel - 1) * MAPHEIGHT * MAPWIDTH + (prow - 1) * MAPWIDTH + (pcol - 1);
        wpos *= 73;
        if (!fseek(wwall, wpos, SEEK_SET)) {
            j = fread(wstr, 73, 1, wwall);
            if (j) {
                wstr[72] = 0;
                if (strlen(wstr) > 1) {
                    delinm();
                    prfmsg(WWWR, wstr);
                    outprf(usrnum);
                }
            } else
                shocst("ELWWD WWRead Error", "ELWWD DrMsg Read Failed");
        } else
            shocst("ELWWD WWSeek Error", "ELWWD DrMsg Seek Failed");
    }
}

SHORT wdyak(VOID)
{
    VDABLK* yvda;
    USHORT i;
    yvda = (VDABLK*)vdaoff(othusn);
    if (ingame[othusn]) {
        yvda->yakflag = TRUE;
        stzcpy(yvda->yakmsg, prfbuf, 155);
        for (i = 0; i < strlen(yvda->yakmsg); i++)
            if (yvda->yakmsg[i] == '\n' ||
                yvda->yakmsg[i] == '\r')
                yvda->yakmsg[i] = ' ';
    }
    return(1);
}

VOID vstat(VOID)
{
    zvda->stmode++;
    if (zvda->stmode > zldr->memcnt) {
        zvda->stmode = 0;
        prfmsg(COMPRST);
        outprf(usrnum);
    }
    zvda->nstat = TRUE;
    drawstats();
}

VOID eyespy(VOID)
{
    CHAR kkey, stopme = FALSE;
    SHORT ich, erow = 1, ecol = 1;

    switch (zvda->mstate) {
        case 0: prfmsg(EYESPY);
            outprf(usrnum);
            zvda->mstate = 1;
            usrptr->substt = 32;
            break;
        case 1: kkey = getinput();
            if (kkey > 0) {
                switch (kkey) {
                    case 'E': zvda->eye = 'E';
                        zvda->mstate = 2;
                        zvda->lastch = 0;
                        break;
                    case 'G': zvda->eye = 'G';
                        zvda->mstate = 2;
                        zvda->lastch = 0;
                        break;
                    default: restplay();
                }
            }
            break;
        case 2: ich = zvda->lastch;
            prfmsg(CLRSCR);
            while (!stopme) {
                if (ich < nterms) {
                    othusp = usroff(ich); //othusp=&user[ich];
                    if (othusp->usrcls == ACTUSR) { //if (othusp->class==ACTUSR) {
                        if (zvda->eye == 'E' || (zvda->eye == 'G' &&
                            othusp->state == modnum)) {
                            arxy(ecol, erow);
                            othuap = uacoff(ich);
                            prf("%s", othuap->userid);
                            outprf(usrnum);
                            erow++;
                            if (erow == 21) {
                                if (ecol == 50) {
                                    stopme = TRUE;
                                } else {
                                    erow = 1;
                                    ecol = 50;
                                }
                            }
                        }
                    }
                } else {
                    stopme = TRUE;
                }
                ich++;
            }
            zvda->lastch = ich;
            if (ich < nterms)
                prfmsg(EYESPN);
            else
                prfmsg(EYESPX);
            outprf(usrnum);
            zvda->mstate = 3;
            break;
        case 3: kkey = getinput();
            if (kkey > 0) {
                switch (kkey) {
                    case 'X': restplay();
                        break;
                    case 'N':
                    default: if (zvda->lastch < nterms)
                        zvda->mstate = 2;
                           else
                        restplay();
                }
            }
            break;
    }
}

VOID drawdrop(VOID)
{
    USHORT i; size_t j;
    CHAR itstr[20] = { 0 }, dpnames[15][22] = { 0 }, nstr[30] = { 0 };
    DPREC dtemp;
    SHORT ioe = FALSE;

    for (i = 0; i < 20; i++)
        zvda->mnustr[i] = 0;
    for (i = 0; i < zvda->litcnt; i++) {
        if (fseek(dropf, dropidx[dpbase[zvda->dplist[i]].idxpos], SEEK_SET)) {
            shocst("ELWWD:ADICF I/O U Error", "ADICF SeekLR Failed");
            ioe = TRUE;
            break;
        } else {
            j = fread(&dtemp, sizeof(DPREC), 1, dropf);
            if (j != 1) {
                shocst("ELWWD: I/OE R ADICF", "ADICF LRead Failed");
                ioe = TRUE;
                break;
            } else {
                stzcpy(dpnames[i], dtemp.dpobj.objname, 20);
            }
        }
    }
    if (ioe) {
        prfmsg(WBLLN);
        prf("An Error Occurred Retrieving The Item List");
        outprf(usrnum);
        restcomp();
    } else {
        if (!zvda->rip) {
            prfmsg(ITSEL);
            for (i = 0; i < zvda->litcnt; i++) {
                arxy(50, i + 4);
                itstr[i] = (CHAR)'A' + (CHAR)i;
                prf("[0;1;41mº[33;40m %c[37;41m [40m [32m", itstr[i]);
                stzcpy(nstr, dpnames[i], 20);
                while (strlen(nstr) < 20)
                    strcat(nstr, " ");
                prf(nstr);
                prf("[37m[41mº[0m\n");
                outprf(usrnum);
            }
            if (zvda->dpch == 'B' || zvda->dpch == 'N') {
                itstr[i] = 'S';
                arxy(50, i + 4);
                prfmsg(NPAGL);
                i++;
            }
            if (zvda->dpch == 'B' || zvda->dpch == 'P') {
                itstr[i] = 'T';
                arxy(50, i + 4);
                prfmsg(PPAGL);
                i++;
            }
            itstr[i] = 'X';
            arxy(50, i + 4);
            prfmsg(XPAGL);
            i++;
            itstr[i] = 0;
            arxy(50, i + 4);
            prfmsg(ITSEL2);
            outprf(usrnum);
        } else {
            strcpy(zvda->query, "((*Get a Dropped Item::");
            for (i = 0; i < zvda->litcnt; i++) {
                itstr[i] = (CHAR)'A' + (CHAR)i;
                stzcpy(nstr, dpnames[i], 20);
                while (strlen(nstr) < 20)
                    strcat(nstr, " ");
                strcat(zvda->query, spr("%c@%s,", itstr[i], nstr));
            }
            if (zvda->dpch == 'B' || zvda->dpch == 'N') {
                itstr[i] = 'S';
                strcat(zvda->query, spr("%c@Next Page,", itstr[i]));
                i++;
            }
            if (zvda->dpch == 'B' || zvda->dpch == 'P') {
                itstr[i] = 'T';
                strcat(zvda->query, spr("%c@Previous Page,", itstr[i]));
                i++;
            }
            itstr[i] = 'X';
            strcat(zvda->query, spr("%c@Get Nothing))", itstr[i]));
            i++;
            itstr[i] = 0;
            rip_query(0, 0, zvda->query);
        }
        // row/col/width/#items/cmchars/rstate
        ansimenu(1, 50, 26, i, itstr, 46, -2);
    }
}

VOID droplist(VOID)
{
    USHORT i, j;
    DPREC dtemp;
    SHORT nxt = FALSE, ioe = FALSE, dir, npos, tcnt;
    switch (zvda->mstate) {
        case 0: if (!chkdrop()) {
            prfmsg(WBLLN);
            prfmsg(NUTHN);
            outprf(usrnum);
            usrptr->substt = 20;
        } else {
            i = j = 0;
            zvda->cshop = 0;
            while (j < 16 && i < totdrop) {
                if (dpbase[i].dx == pcol && dpbase[i].dy == prow &&
                    dpbase[i].dlvl == plevel) {
                    zvda->dplist[j] = i;
                    j++;
                }
                i++;
            }
            if (j == 16) {
                nxt = TRUE;
                j = 15;
            }
            zvda->litcnt = j;
            if (nxt)
                zvda->dpch = 'N';
            zvda->mstate = 1;
            drawdrop();
        }
              break;
              /* menu pick */
        case 1: zvda->mnukey--;
            if (zvda->mnukey < zvda->litcnt) {
                delbox(14, 50, 7);
                i = zvda->dplist[zvda->mnukey];
                if (dpbase[i].dx == pcol && dpbase[i].dy == prow &&
                    dpbase[i].dlvl == plevel) {
                    if (fseek(dropf, dropidx[dpbase[i].idxpos], SEEK_SET)) {
                        shocst("ELWWD:ADICF I/O U Error", "ADICF SeekGR Failed");
                        //ioe=TRUE;
                        break;
                    } else {
                        j = (USHORT)fread(&dtemp, sizeof(DPREC), 1, dropf);
                        if (j != 1) {
                            shocst("ELWWD: I/OE R ADICF", "ADICF GRead Failed");
                            //ioe=TRUE;
                            break;
                        } else {
                            for (j = 0; j < MAXPOBJC; j++)
                                if (zvda->pstuff[j].objname[0] == 0)
                                    break;
                            if (j < MAXPOBJC) {
                                zvda->pstuff[j] = dtemp.dpobj;
                                prfmsg(WBLLN);
                                prfmsg(PIKUP, zvda->pstuff[j].objname);
                                outprf(usrnum);
                                dropupd('d', i);
                                restcomp();
                                arxy(1, 18);
                                prfmsg(CLBAR);
                                outprf(usrnum);
                            } else {
                                prfmsg(WBLLN);
                                prfmsg(NOROOM);
                                outprf(usrnum);
                                restcomp();
                                arxy(1, 18);
                                prfmsg(CLBAR);
                                outprf(usrnum);
                            }
                        }
                    }
                } else {
                    prfmsg(WBLLN);
                    prfmsg(OBJGON);
                    outprf(usrnum);
                    if (!chkdrop()) {
                        restcomp();
                        arxy(1, 18);
                        prfmsg(CLBAR);
                        outprf(usrnum);
                    } else {
                        i = j = 0;
                        while (j < 16 && i < totdrop) {
                            if (dpbase[i].dx == pcol && dpbase[i].dy == prow &&
                                dpbase[i].dlvl == plevel) {
                                zvda->dplist[j] = i;
                                j++;
                            }
                            i++;
                        }
                        if (j == 16) {
                            nxt = TRUE;
                            j = 15;
                        }
                        if (j < zvda->litcnt)
                            delbox(j, 50, zvda->litcnt - j + 3);
                        zvda->litcnt = j;
                        if (nxt)
                            zvda->dpch = 'N';
                        drawdrop();
                    }
                }
            } else {
                dir = 0;
                switch (zvda->mnustr[zvda->mnukey]) {
                    case 'X': delbox(14, 50, 7);
                        restcomp();
                        arxy(1, 18);
                        prfmsg(CLBAR);
                        outprf(usrnum);
                        break;
                    case 'S': dir = 15;
                    case 'T': if (dir == 0)
                        dir = -15;
                        if (!chkdrop()) {
                            prfmsg(WBLLN);
                            prfmsg(NUTHNN);
                            outprf(usrnum);
                            delbox(14, 50, 7);
                            restcomp();
                            arxy(1, 18);
                            prfmsg(CLBAR);
                            outprf(usrnum);
                            break;
                        }
                        j = 0;
                        for (i = 0; i < totdrop; i++)
                            if (dpbase[i].dx == pcol && dpbase[i].dy == prow &&
                                dpbase[i].dlvl == plevel)
                                j++;
                        if (dir == 15) {
                            if (zvda->litcnt >= j) {
                                prfmsg(WBLLN);
                                prfmsg(NOMORE);
                                outprf(usrnum);
                                npos = zvda->cshop;
                                if (zvda->cshop > j)
                                    npos = 0;
                            } else {
                                npos = zvda->cshop + zvda->litcnt;
                            }
                        } else {
                            tcnt = zvda->cshop;
                            npos = tcnt + dir;
                            if (npos<0 || npos>j)
                                npos = 0;
                        }
                        i = 0;
                        zvda->cshop = npos;
                        j = npos;
                        while (j > 0 && i < totdrop) {
                            if (dpbase[i].dx == pcol && dpbase[i].dy == prow &&
                                dpbase[i].dlvl == plevel) {
                                j--;
                            }
                            i++;
                        }
                        if (i == totdrop) {
                            prfmsg(WBLLN);
                            prf("N/P Lost, D=%d,P=%d", dir, npos);
                            outprf(usrnum);
                            delbox(14, 50, 7);
                            restcomp();
                            arxy(1, 18);
                            prfmsg(CLBAR);
                            outprf(usrnum);
                            break;
                        }
                        j = 0;
                        nxt = FALSE;
                        while (j < 16 && i < totdrop) {
                            if (dpbase[i].dx == pcol && dpbase[i].dy == prow &&
                                dpbase[i].dlvl == plevel) {
                                zvda->dplist[j] = i;
                                j++;
                            }
                            i++;
                        }
                        if (j == 16) {
                            nxt = TRUE;
                            j = 15;
                        }
                        if (j < zvda->litcnt)
                            delbox(j + 3, 50, zvda->litcnt - j + 3);
                        zvda->litcnt = j;
                        if (nxt) {
                            if (zvda->cshop > 0)
                                zvda->dpch = 'B';
                            else
                                zvda->dpch = 'N';
                        } else {
                            if (zvda->cshop > 0)
                                zvda->dpch = 'P';
                        }
                        drawdrop();
                        break;
                    default: prfmsg(WBLLN);
                        prf("Uknown key");
                        outprf(usrnum);
                        delbox(14, 50, 7);
                        restcomp();
                        arxy(1, 18);
                        prfmsg(CLBAR);
                        outprf(usrnum);
                }
            }
            if (ioe) {
                prfmsg(WBLLN);
                prf("I/O Error Retrieving List");
                outprf(usrnum);
                restcomp();
                arxy(1, 18);
                prfmsg(CLBAR);
                outprf(usrnum);
            }
            break;
    }
}

SHORT chkdrop(VOID)
{
    SHORT rc = FALSE;
    USHORT i;
    if (totdrop && dropf != NULL) {
        for (i = 0; i < totdrop; i++)
            if (dpbase[i].dx == pcol && dpbase[i].dy == prow &&
                dpbase[i].dlvl == plevel) {
                rc = TRUE;
                break;
            }
    }
    return(rc);
}

VOID dropupd(CHAR mode, SHORT itm)
{
    USHORT i; size_t j;
    DPREC dtemp = { 0 };
    LONG skp;
    if (dropf != NULL)
        switch (mode) {
            case 'a': if (totdrop == MAXDROP) {
                shocst("ELWWD:ADICF Compress", "");
                for (i = 0; i < 5; i++) {
                    dpbase[i].dlvl = 0;
                    fredrop[dpbase[i].idxpos] = TRUE;
                }
                totdrop = 0;
                for (i = 0; i < MAXDROP; i++)
                    if (dpbase[i].dlvl > 0) {
                        dpbase[totdrop] = dpbase[i];
                        totdrop++;
                    }
            }
                    dtemp.dpobj = zvda->pstuff[itm];
                    dpbase[totdrop].dx = dtemp.dx = pcol;
                    dpbase[totdrop].dy = dtemp.dy = prow;
                    dpbase[totdrop].dlvl = dtemp.dlvl = plevel;
                    for (i = 0; i < MAXDROP; i++)
                        if (fredrop[i])
                            break;
                    if (i == MAXDROP) {
                        shocst("ELWWD:ADICF Err 162", "");
                        break;
                    }
                    skp = dropidx[i];
                    dpbase[totdrop].idxpos = i;
                    fredrop[i] = FALSE;
                    if (fseek(dropf, skp, SEEK_SET))
                        shocst("ELWWD:ADICF I/O U Error", "ADICF SeekW Failed");
                    else {
                        j = fwrite(&dtemp, sizeof(DPREC), 1, dropf);
                        if (j != 1) {
                            shocst("ELWWD: I/OE W ADICF", "ADICF U/W Failed");
                        } else {
                            //            arxy(1,16);
                            //            prf("FSlot=%u",i);
                            //            outprf(usrnum);
                            totdrop++;
                        }
                    }
                    break;
            case 'd': skp = dropidx[dpbase[itm].idxpos];
                fredrop[dpbase[itm].idxpos] = TRUE;
                dpbase[itm].dlvl = 0;
                for (i = totdrop; i < MAXDROP; i++)
                    dpbase[i].dlvl = 0;
                totdrop = 0;
                for (i = 0; i < MAXDROP; i++)
                    if (dpbase[i].dlvl > 0) {
                        dpbase[totdrop] = dpbase[i];
                        totdrop++;
                    }
                if (fseek(dropf, skp, SEEK_SET))
                    shocst("ELWWD:ADICF I/O U Error", "ADICF SeekD Failed");
                else {
                    dtemp.dlvl = 0;
                    j = fwrite(&dtemp, sizeof(DPREC), 1, dropf);
                    if (j != 1) {
                        shocst("ELWWD: I/OE W ADICF", "ADICF U/W Failed");
                    }
                }
        } else
            totdrop = 0;
}

CHAR getinput(VOID)
{
    SHORT nbytes;

    btuict(usrnum, kpress); //nbytes=
    nbytes = ictact;
    if (nbytes > 0) {
        btucli(usrnum);
        return(xltkey());
    }
    return(0);
}

VOID restat(SHORT un)
{
    USHORT i;
    VDABLK* tvda;
    PLYRINF* pvda;
    tvda = (VDABLK*)vdaoff(un);
    pvda = &tvda->plyr;
    for (i = 0; i < 7; i++)
        pvda->attrib[i] = pvda->attrib[i + 7];
    for (i = 0; i < MAXPOBJC; i++)
        if (tvda->pstuff[i].objname[0] != 0 &&
            pvda->equip[i] == 1)
            statup(i, un, un);
}

VOID statoff(SHORT obn, SHORT sun, SHORT tun)
{
    USHORT i;
    SHORT tmod, lmod;
    VDABLK* tvda, * svda;
    PLYRINF* tply;
    tvda = (VDABLK*)vdaoff(tun);
    svda = (VDABLK*)vdaoff(sun);
    tply = &tvda->plyr;
    for (i = 0; i < 7; i++) {
        tmod = svda->pstuff[obn].oeffect[i];
        lmod = tply->attrib[i];
        lmod -= tmod;
        if (lmod < 0) {
            tply->attrib[i] = 0;
        } else {
            if (lmod > 25)
                tply->attrib[i] = 25;
            else
                tply->attrib[i] = (CHAR)lmod;
        }
    }
}

VOID statup(SHORT obn, SHORT sun, SHORT tun)
{
    USHORT i;
    SHORT tmod, lmod;
    VDABLK* tvda, * svda;
    PLYRINF* tply;
    tvda = (VDABLK*)vdaoff(tun);
    svda = (VDABLK*)vdaoff(sun);
    tply = &tvda->plyr;
    for (i = 0; i < 7; i++) {
        tmod = svda->pstuff[obn].oeffect[i];
        lmod = tply->attrib[i];
        lmod += tmod;
        if (lmod < 0) {
            tply->attrib[i] = 0;
        } else {
            if (lmod > 25)
                tply->attrib[i] = 25;
            else
                tply->attrib[i] = (CHAR)lmod;
        }
    }
}

VOID deccond(CHAR tgtid, SHORT targn)
{
    VDABLK* cvda, * clvda;
    CHAR nstr[81], tvar;
    USHORT i;

    switch (tgtid) {
        case 'm': if (zcbr->mcond[targn][1] && zcbr->mcond[targn][2] > 0) {
            zcbr->mcond[targn][2]--;
            if (zcbr->mcond[targn][2] == 0) {
                sprintf(nstr, "The %s is no longer paralyzed!", zcbr->cmonst[targn].name);
                zcbr->mcond[targn][1] = FALSE;
            }
        }
                if (zcbr->mcond[targn][3] && zcbr->mcond[targn][4] > 0) {
                    zcbr->mcond[targn][4]--;
                    if (zcbr->mcond[targn][4] == 0) {
                        sprintf(nstr, "The %s is no longer shielded!", zcbr->cmonst[targn].name);
                        zcbr->mcond[targn][3] = FALSE;
                    }
                }
                if (zcbr->mcond[targn][0]) {
                    zcbr->mcond[targn][5]--;
                    if (zcbr->mcond[targn][5] == 0) {
                        tvar = 11 - zcbr->mcond[targn][0];
                        zcbr->mcond[targn][5] = tvar;
                        tvar = zcbr->mcond[targn][0] * 2;
                        if (tvar > zcbr->cmonst[targn].hp) {
                            zcbr->cmonst[targn].hp = 0;
                            sprintf(nstr, "The %s is dead from poison!", zcbr->cmonst[targn].name);
                            encnews(nstr);
                            if (tstend())
                                encnews("The last creature has fallen!");
                        } else {
                            zcbr->cmonst[targn].hp -= tvar;
                            sprintf(nstr, "The %s suffers from poison!", zcbr->cmonst[targn].name);
                            encnews(nstr);
                        }
                    }
                }
                break;
        case 'p': cvda = (VDABLK*)vdaoff(targn);
            if (cvda->plyr.condition[2] && cvda->plyr.condition[3] > 0) {
                cvda->plyr.condition[3]--;
                if (cvda->plyr.condition[3] == 0) {
                    cvda->plyr.condition[2] = FALSE;
                    if (cvda->gstate == INFITE) {
                        addnews("You are no longer paralyzed!", targn);
                    } else {
                        prfmsg(WBLLN);
                        prfmsg(NOPLYZD);
                        outprf(targn);
                    }
                }
            }
            if (cvda->plyr.condition[4] && cvda->plyr.condition[5] > 0) {
                cvda->plyr.condition[5]--;
                if (cvda->plyr.condition[5] == 0) {
                    cvda->plyr.condition[4] = FALSE;
                    if (cvda->gstate == INFITE) {
                        addnews("You are no longer shielded!", targn);
                    } else {
                        prfmsg(WBLLN);
                        prfmsg(SHLDFL);
                        outprf(targn);
                    }
                }
            }
            if (cvda->spelltrue && cvda->plyr.condition[6] > 0) {
                cvda->plyr.condition[6]--;
                if (cvda->plyr.condition[6] == 0) {
                    cvda->spelltrue = FALSE;
                    if (cvda->gstate == INFITE) {
                        addnews("Your vision is less sharp!", targn);
                    } else {
                        prfmsg(WBLLN);
                        prfmsg(NOVIZN);
                        outprf(targn);
                    }
                }
            }
            if (cvda->plyr.condition[0]) {
                cvda->plyr.condition[7]--;
                if (cvda->plyr.condition[7] == 0) {
                    tvar = 11 - cvda->plyr.condition[0];
                    cvda->plyr.condition[7] = tvar;
                    tvar = cvda->plyr.condition[0] * 2;
                    if (tvar > cvda->plyr.currhp) {
                        cvda->dead = TRUE;
                        cvda->plyr.currhp = 0;
                        lparty(targn);
                        if (cvda->gstate == INFITE) {
                            cvda->plyr.encloss++;
                            cvda->rdlife = TRUE;
                            sprintf(nstr, "%s has died from poison", cvda->plyr.name);
                            encnews(nstr);
                        } else {
                            prfmsg(WBLLN);
                            prfmsg(PIZKIL);
                            outprf(usrnum);
                            if (cvda->party != targn) {
                                clvda = (VDABLK*)vdaoff(cvda->party);
                                clrprf();
                                prfmsg(WBLLN);
                                prfmsg(PIZKILT, cvda->plyr.name);
                                for (i = 0; i < clvda->memcnt; i++)
                                    if (clvda->members[i] != targn)
                                        outprf(clvda->members[i]);
                            }
                        }
                    } else {
                        cvda->plyr.currhp -= tvar;
                        if (cvda->gstate == INFITE) {
                            addnews("You feel the effects of the poison", targn);
                            cvda->rdlife = TRUE;
                        } else {
                            prfmsg(WBLLN);
                            prfmsg(PIZFEL);
                            outprf(usrnum);
                            drawstats();
                        }
                    }
                }
            }
            break;
    }
}

SHORT locplayer(SHORT x, SHORT y)
{
    SHORT i, lded = NOTFOUND, lliv = NOTFOUND;
    VDABLK* pvda;
    for (i = 0; i < zcbr->pcnt; i++)
        if (zcbr->plx[i] == x && zcbr->ply[i] == y && ingame[zcbr->plyrs[i]]) {
            pvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
            if (pvda->dead)
                lded = i;
            else
                lliv = i;
        }
    if (lliv != NOTFOUND)
        i = lliv;
    else
        i = lded;
    return(i);
}

USHORT calcfspdmg(USHORT bdmg, USHORT ldmg, SHORT dmod)
{
    USHORT fdmg, j;
    if (zplyr->lvl_drain > zplyr->level) {
        j = 1;
        if (zvda->gstate == INFITE)
            arxy(1, 14);
        else
            arxy(1, 22);
        prf("LvErr<DrN");
        outprf(usrnum);
    } else {
        j = zplyr->level - zplyr->lvl_drain;
    }
    fdmg = bdmg + ldmg * j;
    if (dmod > 0 && dmod < 100 && fdmg>0) {
        j = fdmg * dmod;
        if (j < 100)
            fdmg = 1;
        else
            fdmg = j / 100;
    }
    return(fdmg);
}

VOID whodat(VOID)
{
    CHAR kky;
    USHORT i;//=0;
    SHORT op;

    switch (zvda->mstate) {
        case 0: for (i = 0; i < 49; i++)
            if (zvda->ovchn[i] < nterms)
                break;
            if (i < 49) {
                prfmsg(WBLLN);
                prfmsg(WHOBE);
                zvda->mstate = 1;
                usrptr->substt = 28;
            } else {
                prfmsg(WBLLN);
                prfmsg(NOBDERE);
            }
            outprf(usrnum);
            break;
        case 1: if (btuica(usrnum, kpress, 4) > 0) {
            btucli(usrnum);
            kky = xltkey();
            if (kky >= 'A' && kky <= 'U') {
                i = kky - 'A';
                if (kky == 'U') {
                    prfmsg(WBLLN);
                    prfmsg(DATBU);
                    outprf(usrnum);
                } else
                    if (zvda->ovchn[i] < nterms) {
                        if (ingame[zvda->ovchn[i]]) {
                            xlvda = (VDABLK*)vdaoff(zvda->ovchn[i]);
                            if (xlvda->gstate > ISACTIVE) {
                                if (xlvda->party == zvda->ovchn[i]) {
                                    prfmsg(WBLLN);
                                    prfmsg(DATIS, xlvda->plyr.name);
                                } else {
                                    op = xlvda->party;
                                    xlvda = (VDABLK*)vdaoff(op);
                                    prfmsg(WBLLN);
                                    prfmsg(DATISP, xlvda->plyr.name);
                                }
                                outprf(usrnum);
                            } else {
                                prfmsg(WBLLN);
                                prfmsg(DAYBGN);
                                outprf(usrnum);
                            }
                        } else {
                            prfmsg(WBLLN);
                            prfmsg(DAYBGN);
                            outprf(usrnum);
                        }
                    } else {
                        prfmsg(WBLLN);
                        prfmsg(DAYBGN);
                        outprf(usrnum);
                    }
            } else {
                prfmsg(WBLLN);
                prfmsg(WBLLN);
                outprf(usrnum);
            }
            usrptr->substt = 20;
        }
              break;
    }
}

/* special effects */
VOID poison(CHAR targid, SHORT targn, CHAR castid, SHORT castn)
{
    VDABLK* ptvda;
    CHAR nstr[81];

    switch (targid) {
        case 'm': if (zvda->gstate != INFITE) {
            arxy(1, 23);
            prf("MTarg PiZ UxP !InCbr");
            outprf(usrnum);
        } else {
            if (zcbr->mcond[targn][0] < 10)
                zcbr->mcond[targn][0]++;
            zcbr->mcond[targn][5] = 1;
            sprintf(nstr, "The %s is poisoned!", zcbr->cmonst[targn].name);
            encnews(nstr);
        }
                break;
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            if (ptvda->plyr.condition[1] < 10)
                ptvda->plyr.condition[1]++;
            ptvda->plyr.condition[7] = 1;
            if (ptvda->gstate == INFITE) {
                if (castid == 'p') {
                    sprintf(nstr, "%s is poisoned!", ptvda->plyr.name);
                    addnews(nstr, (SHORT)usrnum);
                    sprintf(nstr, "You've been poisoned by %s", zplyr->name);
                } else
                    sprintf(nstr, "You've been poisoned by the %s", zcbr->cmonst[castn].name);
                addnews(nstr, targn);
            } else {
                clrprf();
                prfmsg(WBLLN);
                prfmsg(PIZND, zplyr->name);
                outprf(targn);
                prfmsg(WBLLN);
                prfmsg(UPIZND, ptvda->plyr.name);
                outprf(usrnum);
            }
            break;
    }
}

VOID paralyze(CHAR targid, SHORT targn, CHAR dtime, CHAR castid, SHORT castn)
{
    VDABLK* ptvda;
    CHAR nstr[81];

    switch (targid) {
        case 'm': if (zvda->gstate != INFITE) {
            arxy(1, 23);
            prf("MTarg PlZ UxP !InCbr");
            outprf(usrnum);
        } else {
            zcbr->mcond[targn][1] = TRUE;
            zcbr->mcond[targn][2] = dtime;
            sprintf(nstr, "The %s is paralyzed!", zcbr->cmonst[targn].name);
            encnews(nstr);
        }
                break;
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            ptvda->plyr.condition[2] = TRUE;
            ptvda->plyr.condition[3] = dtime;
            if (ptvda->gstate == INFITE) {
                if (castid == 'p') {
                    sprintf(nstr, "%s is paralyzed!", ptvda->plyr.name);
                    addnews(nstr, (SHORT)usrnum);
                    sprintf(nstr, "You've been paralyzed by %s", zplyr->name);
                } else
                    sprintf(nstr, "You've been paralyzed by the %s", zcbr->cmonst[castn].name);
                addnews(nstr, targn);
            } else {
                clrprf();
                prfmsg(WBLLN);
                prfmsg(PLYZD, zplyr->name);
                outprf(targn);
                prfmsg(WBLLN);
                prfmsg(UPLYZD, ptvda->plyr.name);
                outprf(usrnum);
                ptvda->pwtick = btuTicker(); //ticker
            }
            break;
    }
}

VOID drainlvl(CHAR targid, SHORT targn, CHAR castid, SHORT castn)
{
    VDABLK* ptvda;
    SHORT didhap = FALSE;
    CHAR nstr[81];

    switch (targid) {
        case 'm': if (zvda->gstate != INFITE) {
            arxy(1, 23);
            prf("MTarg DlV UxP !InCbr");
            outprf(usrnum);
        } else {
            if (zcbr->cmonst[targn].level > 1) {
                zcbr->cmonst[targn].level--;
                sprintf(nstr, "The %s has lost a level!", zcbr->cmonst[targn].name);
                encnews(nstr);
            } else {
                sprintf(nstr, "The %s lost nothing!", zcbr->cmonst[targn].name);
                addnews(nstr, (SHORT)usrnum);
            }
        }
                break;
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            if (ptvda->plyr.level - ptvda->plyr.lvl_drain - 1 > 1) {
                ptvda->plyr.lvl_drain++;
                //fix experience after Zark fixes classinf
                didhap = TRUE;
            }
            if (ptvda->gstate == INFITE) {
                if (castid == 'p') {
                    if (didhap) {
                        sprintf(nstr, "%s lost a level!", ptvda->plyr.name);
                        addnews(nstr, (SHORT)usrnum);
                        sprintf(nstr, "%s drained a level from you!", zplyr->name);
                        addnews(nstr, targn);
                    } else {
                        sprintf(nstr, "%s was unaffected!", ptvda->plyr.name);
                        addnews(nstr, (SHORT)usrnum);
                    }
                } else {
                    sprintf(nstr, "The %s has drained a level from you!", zcbr->cmonst[castn].name);
                    addnews(nstr, targn);
                }
            } else {
                clrprf();
                if (didhap) {
                    prfmsg(WBLLN);
                    prfmsg(DRNLVL, zplyr->name);
                    outprf(targn);
                    prfmsg(WBLLN);
                    prfmsg(UDRNLVL, ptvda->plyr.name);
                    outprf(usrnum);
                } else {
                    prfmsg(WBLLN);
                    prfmsg(NODRAIN, ptvda->plyr.name);
                    outprf(targn);
                }
            }
            break;
    }
}

VOID scry(SHORT rstate, SHORT mstate)
{
    SHORT i, j = 2, k = 1, l = 0;
    VDABLK* ptvda;
    CHAR kkey;
    switch (zvda->mstate) {
        case 0: usrptr->substt = 29;
            zvda->oustate = rstate;
            zvda->oumstate = mstate;
            zvda->mnucnt = 0;
            zvda->mstate = 1;
        case 1: prfmsg(SCRYL);
            outprf(usrnum);
            for (i = zvda->mnucnt; i < nterms; i++) {
                if (ingame[i]) {
                    ptvda = (VDABLK*)vdaoff(i);
                    if (ptvda->gstate > ISACTIVE) {
                        arxy(k, j);
                        prfmsg(SCRYLL, ptvda->plyr.name,
                            ptvda->plyr.curlvl,
                            ptvda->plyr.row,
                            ptvda->plyr.col);
                        outprf(usrnum);
                        j++;
                        l++;
                        //           if (j>22){
                        //            j=1;
                        //            k=45;
                        //           }
                        if (l > 22)
                            break;
                    }
                }
            }
            zvda->mnucnt = i;
            prfmsg(SCRYLC);
            outprf(usrnum);
            zvda->mstate = 2;
            break;
        case 2: if (btuica(usrnum, kpress, 4) > 0) {
            btucli(usrnum);
            kkey = xltkey();
            switch (kkey) {
                case 'Q': usrptr->substt = zvda->oustate;
                    zvda->mstate = zvda->oumstate;
                    break;
                case 'C':
                default: if (zvda->mnucnt < nterms)
                    zvda->mstate = 1;
                       else {
                    usrptr->substt = zvda->oustate;
                    zvda->mstate = zvda->oumstate;
                }
                       break;
            }
        }
              break;
    }
}

VOID mshield(CHAR targid, SHORT targn, CHAR dtime, CHAR castid, SHORT castn)
{
    VDABLK* ptvda;
    CHAR nstr[81];
    switch (targid) {
        case 'm': if (zvda->gstate != INFITE) {
            arxy(1, 23);
            prf("MTarg MsH UxP !InCbr");
            outprf(usrnum);
        } else {
            zcbr->mcond[targn][3] = TRUE;
            zcbr->mcond[targn][4] = zcbr->cmonst[targn].level * 2;
            sprintf(nstr, "The %s has a magic shield!", zcbr->cmonst[targn].name);
            encnews(nstr);
        }
                break;
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            ptvda->plyr.condition[4] = TRUE;
            ptvda->plyr.condition[5] = dtime;
            if (ptvda->gstate == INFITE) {
                if (castid == 'p') {
                    if (castn == targn) {
                        addnews("Magic Shield Activated!", (SHORT)usrnum);
                        sprintf(nstr, "%s is Shielded!", zplyr->name);
                        tellthem(nstr);
                    } else {
                        sprintf(nstr, "%s is Shielded!", ptvda->plyr.name);
                        encnews(nstr);
                    }
                }
            } else {
                clrprf();
                if (castn == targn) {
                    prfmsg(WBLLN);
                    prfmsg(USHLDD);
                    outprf(usrnum);
                } else {
                    prfmsg(WBLLN);
                    prfmsg(USHLDP, zplyr->name);
                    outprf(targn);
                    prfmsg(WBLLN);
                    prfmsg(USHLDU, ptvda->plyr.name);
                    outprf(usrnum);
                }
            }
            break;
    }
}

SHORT hitbonus(SHORT bval, SHORT castn, CHAR castid)
{

    switch (castid) {
        case 'p': if (zplyr->level > 8)
            bval *= 3;
                else
            bval *= 2;
            break;
        case 'm': if (zcbr->cmonst[castn].level > 8)
            bval *= 3;
                else
            bval *= 2;
            break;
    }
    return(bval);
}

VOID vision(CHAR castid, CHAR dtime)
{

    if (castid == 'p') {
        zvda->spelltrue = TRUE;
        zvda->plyr.condition[6] = dtime;
    }
}

VOID drainlife(CHAR targid, SHORT targn, CHAR castid, SHORT castn, SHORT ddm)
{
    VDABLK* ptvda;
    SHORT nhp;
    CHAR nstr[81];

    switch (targid) {
        case 'm': if (zvda->gstate != INFITE) {
            arxy(1, 23);
            prf("MTarg DlF UxP !InCbr");
            outprf(usrnum);
        } else {
            if (zcbr->cmonst[targn].hp > ddm) {
                nhp = zplyr->currhp + ddm;
                if (nhp > 250)
                    nhp = 250;
                sprintf(nstr, "The %s has been drained of life!", zcbr->cmonst[targn].name);
                tellthem(nstr);
                sprintf(nstr, "You gain life from the %s!", zcbr->cmonst[targn].name);
                addnews(nstr, (SHORT)usrnum);
                zplyr->currhp = (CHAR)nhp;
                zvda->rdlife = TRUE;
            } else {
                sprintf(nstr, "You gained nothing from the %s!", zcbr->cmonst[targn].name);
                addnews(nstr, (SHORT)usrnum);
            }
        }
                break;
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            ptvda->rdlife = TRUE;
            if (ptvda->plyr.currhp > 10) {
                nhp = ptvda->plyr.currhp - ddm;
                if (nhp < 10) {
                    nhp = 10;
                    ddm = ptvda->plyr.currhp - 10;
                }
                ptvda->plyr.currhp = (CHAR)nhp;
                switch (castid) {
                    case 'p': nhp = zplyr->currhp + ddm;
                        if (nhp > 250)
                            zplyr->currhp = 250;
                        else
                            zplyr->currhp = (CHAR)nhp;
                        if (zvda->gstate == INFITE) {
                            sprintf(nstr, "%s has drained your life!", zplyr->name);
                            addnews(nstr, targn);
                            sprintf(nstr, "You gain life from the %s!", ptvda->plyr.name);
                            addnews(nstr, (SHORT)usrnum);
                        } else {
                            clrprf();
                            prfmsg(WBLLN);
                            prfmsg(DRNLIF, zplyr->name);
                            outprf(targn);
                            prfmsg(WBLLN);
                            prfmsg(UDRNLIF, ptvda->plyr.name);
                            outprf(usrnum);
                        }
                        break;
                    case 'm': nhp = zcbr->cmonst[castn].hp + ddm;
                        if (nhp > 250)
                            zcbr->cmonst[castn].hp = 250;
                        else
                            zcbr->cmonst[castn].hp = (CHAR)nhp;
                        sprintf(nstr, "The %s has drained your life!", zcbr->cmonst[castn].name);
                        addnews(nstr, targn);
                        break;
                }
            }
            break;
    }
}

VOID heal(CHAR targid, SHORT targn, SHORT hhp, SHORT castn)
{
    VDABLK* ptvda;
    SHORT nhp;
    CHAR nstr[81];

    switch (targid) {
        case 'm': if (zvda->gstate != INFITE) {
            arxy(1, 23);
            prf("MTarg Hl UxP !InCbr");
            outprf(usrnum);
        } else {
            nhp = zcbr->cmonst[targn].hp + hhp;
            if (nhp > 250)
                nhp = 250;
            zcbr->cmonst[targn].hp = (CHAR)nhp;
            sprintf(nstr, "The %s is healed!", zcbr->cmonst[targn].name);
            encnews(nstr);
        }
                break;
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            ptvda->rdlife = TRUE;
            nhp = ptvda->plyr.currhp + hhp;
            if (nhp > ptvda->plyr.maxhp)
                ptvda->plyr.currhp = ptvda->plyr.maxhp;
            else
                ptvda->plyr.currhp = (CHAR)nhp;
            if (zvda->gstate == INFITE) {
                if (castn != targn) {
                    sprintf(nstr, "%s has healed you!", zplyr->name);
                    addnews(nstr, targn);
                    sprintf(nstr, "%s healed!", ptvda->plyr.name);
                    addnews(nstr, (SHORT)usrnum);
                } else {
                    addnews("You feel much better...", (SHORT)usrnum);
                }
            } else {
                if (castn != targn) {
                    clrprf();
                    prfmsg(WBLLN);
                    prfmsg(HEELD, zplyr->name);
                    outprf(targn);
                    prfmsg(WBLLN);
                    prfmsg(UHEELD, ptvda->plyr.name);
                    outprf(usrnum);
                } else {
                    prfmsg(WBLLN);
                    prfmsg(HEALD);
                    outprf(usrnum);
                }
            }
            break;
    }
}

VOID youth(CHAR targid, SHORT targn, SHORT ddm, SHORT castn)
{
    VDABLK* ptvda;
    SHORT nhp;
    CHAR nstr[81];

    switch (targid) {
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            if (ptvda->plyr.new_age > ptvda->plyr.age) {
                nhp = ptvda->plyr.new_age - ddm;
                if (nhp < ptvda->plyr.age)
                    ptvda->plyr.new_age = ptvda->plyr.age;
                else
                    ptvda->plyr.new_age = (CHAR)nhp;
                if (zvda->gstate == INFITE) {
                    if (castn != targn) {
                        sprintf(nstr, "%s has restored your youth!", zplyr->name);
                        addnews(nstr, targn);
                        sprintf(nstr, "%s is younger!", ptvda->plyr.name);
                        addnews(nstr, (SHORT)usrnum);
                    }
                } else {
                    if (castn != targn) {
                        clrprf();
                        prfmsg(WBLLN);
                        prfmsg(YOUTH, zplyr->name);
                        outprf(targn);
                        prfmsg(WBLLN);
                        prfmsg(UYOUTH, ptvda->plyr.name);
                        outprf(usrnum);
                    }
                }
            }
    }
}

VOID agehim(CHAR targid, SHORT targn, SHORT ddm, CHAR castid, SHORT castn)
{
    VDABLK* ptvda;
    SHORT nhp;
    CHAR nstr[81];

    switch (targid) {
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            nhp = ptvda->plyr.new_age + ddm;
            if (nhp > 250)
                ptvda->plyr.new_age = 250;
            else
                ptvda->plyr.new_age = (CHAR)nhp;
            if (zvda->gstate == INFITE) {
                if (castid == 'm') {
                    sprintf(nstr, "The %s has aged you!", zcbr->cmonst[castn].name);
                    addnews(nstr, targn);
                } else {
                    sprintf(nstr, "%s has stolen your youth!", zplyr->name);
                    addnews(nstr, targn);
                    sprintf(nstr, "%s is older!", ptvda->plyr.name);
                    addnews(nstr, (SHORT)usrnum);
                }
            } else {
                clrprf();
                prfmsg(WBLLN);
                prfmsg(AGED, zplyr->name);
                outprf(targn);
                prfmsg(WBLLN);
                prfmsg(UAGED, ptvda->plyr.name);
                outprf(usrnum);
            }
            break;
        case 'm': sprintf(nstr, "The %s is unaffected!", zcbr->cmonst[targn].name);
            addnews(nstr, (SHORT)usrnum);
            break;
    }
}

VOID curepoison(CHAR targid, SHORT targn, SHORT castn)
{
    VDABLK* ptvda;
    CHAR nstr[81];

    switch (targid) {
        case 'm': if (zvda->gstate != INFITE) {
            arxy(1, 23);
            prf("MTarg Cp UxP !InCbr");
            outprf(usrnum);
        } else {
            zcbr->mcond[targn][0] = 0;
            sprintf(nstr, "The %s is no longer poisoned!", zcbr->cmonst[targn].name);
            addnews(nstr, (SHORT)usrnum);
        }
                break;
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            ptvda->plyr.condition[1] = 0;
            if (zvda->gstate == INFITE) {
                if (castn != targn) {
                    sprintf(nstr, "%s has cured you!", zplyr->name);
                    addnews(nstr, targn);
                    sprintf(nstr, "%s is cured!", ptvda->plyr.name);
                    addnews(nstr, (SHORT)usrnum);
                } else {
                    addnews("You are cured!", (SHORT)usrnum);
                }
            } else {
                if (castn != targn) {
                    clrprf();
                    prfmsg(WBLLN);
                    prfmsg(CURED, zplyr->name);
                    outprf(targn);
                    prfmsg(WBLLN);
                    prfmsg(UCURED, ptvda->plyr.name);
                    outprf(usrnum);
                } else {
                    prfmsg(WBLLN);
                    prfmsg(NOPIZN);
                    outprf(usrnum);
                }
            }
            break;
    }
}

VOID revive(CHAR targid, SHORT targn)
{
    VDABLK* ptvda;
    USHORT i;
    CHAR nstr[81];

    switch (targid) {
        case 'm': if (zvda->gstate != INFITE) {
            arxy(1, 23);
            prf("MTarg RvV UxP !InCbr");
            outprf(usrnum);
        } else {
            for (i = 0; i < 9; i++)
                zcbr->mcond[targn][i] = 0;
            zcbr->cmonst[targn].hp = zcbr->mxlife[targn];
            sprintf(nstr, "The %s has been revived!", zcbr->cmonst[targn].name);
            encnews(nstr);
        }
                break;
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            for (i = 0; i < 30; i++)
                ptvda->plyr.condition[i] = 0;
            ptvda->dead = FALSE;
            ptvda->plyr.currhp = ptvda->plyr.maxhp;
            ptvda->rdlife = TRUE;
            ptvda->spelltrue = FALSE;
            if (ptvda->gstate == INFITE) {
                sprintf(nstr, "%s has been revived!", ptvda->plyr.name);
                encnews(nstr);
                sprintf(nstr, "%s revived you!", zplyr->name);
                addnews(nstr, targn);
            } else {
                clrprf();
                prfmsg(WBLLN);
                prfmsg(REVIV, zplyr->name);
                outprf(targn);
                prfmsg(WBLLN);
                prfmsg(UREVIV, ptvda->plyr.name);
                outprf(usrnum);
            }
            break;
    }
}

VOID kill(CHAR targid, SHORT targn, CHAR castid, SHORT castn)
{
    VDABLK* ptvda;
    CHAR nstr[81];

    switch (targid) {
        case 'm': if (zvda->gstate != INFITE) {
            arxy(1, 23);
            prf("MTarg KlL UxP !InCbr");
            outprf(usrnum);
        } else {
            zcbr->cmonst[targn].hp = 0;
            sprintf(nstr, "The %s has been killed!", zcbr->cmonst[targn].name);
            encnews(nstr);
        }
                break;
        case 'p': ptvda = (VDABLK*)vdaoff(targn);
            ptvda->plyr.currhp = 0;
            ptvda->dead = TRUE;
            if (ptvda->gstate == INFITE) {
                if (castid == 'm') {
                    sprintf(nstr, "%s has been killed by the %s!", ptvda->plyr.name, zcbr->cmonst[castn].name);
                    encnews(nstr);
                } else {
                    sprintf(nstr, "%s has been killed!", ptvda->plyr.name);
                    encnews(nstr);
                    sprintf(nstr, "%s killed you!", zplyr->name);
                    addnews(nstr, targn);
                }
            } else {
                clrprf();
                prfmsg(WBLLN);
                prfmsg(KILT, zplyr->name);
                outprf(targn);
                prfmsg(WBLLN);
                prfmsg(UKILT, ptvda->plyr.name);
                outprf(usrnum);
            }
            break;
    }
}

VOID castit(SPELLINF* psp, SHORT rmod, CHAR tgtid, SHORT targn)
{
    USHORT tmr = 0, mres[4] = { 0,0,0,0 };
    VDABLK* pvda = NULL;
    CHAR nstr[81];
    static SHORT nores[14] = { FALSE,FALSE,TRUE,TRUE,TRUE,TRUE,FALSE,
       TRUE,FALSE,TRUE,FALSE,TRUE,TRUE,FALSE };

    /* Test for resistance */
    switch (tgtid) {
        case 'm':
            tmr = zcbr->cmonst[targn].mr;
            mres[0] = zcbr->cmonst[targn].earth;
            mres[1] = zcbr->cmonst[targn].air;
            mres[2] = zcbr->cmonst[targn].water;
            mres[3] = zcbr->cmonst[targn].fire;
            break;
        case 'p':
            pvda = (VDABLK*)vdaoff(targn);
            tmr = pvda->prace.mr;
            mres[0] = pvda->prace.earth;
            mres[1] = pvda->prace.air;
            mres[2] = pvda->prace.water;
            mres[3] = pvda->prace.fire;
            break;
        default:
            // unknown tgtid!
            return; // RH: Not sure what else to do!
    }
    if ((tmr > 99 || mres[psp->element] > 99) && !nores[psp->type]) {  // RH: I added the parens to make the or one block against !nores; hopefully that's logically right
        if (tgtid == 'p') {
            pvda = (VDABLK*)vdaoff(targn);
            switch (zvda->mstate) {
                case INFITE:
                    addnews("Your elemental resistance has saved you!", targn);
                    sprintf(nstr, "Spell failed against %s", pvda->plyr.name);
                    addnews(nstr, (SHORT)usrnum);
                    break;
                default:
                    prfmsg(WBLLN);
                    prfmsg(SPLFL, pvda->plyr.name);
                    outprf(usrnum);
            }
        } else {
            sprintf(nstr, "Spell failed against %s", zcbr->cmonst[targn].name);
            addnews(nstr, (SHORT)usrnum);
        }
    } else {
        switch (psp->type) {
            case 0:
                paralyze(tgtid, targn, psp->duration, 'p', (SHORT)usrnum); //paralyze
                break;
            case 1:
                drainlvl(tgtid, targn, 'p', (SHORT)usrnum);         //drain lvl
                break;
                //put list up of online players
            case 2:
                zvda->mstate = 0;                           //scry sight
                scry(27, 4);
                break;
            case 3:
                mshield(tgtid, targn, psp->duration, 'p', (SHORT)usrnum); //shield
                break;
                //add # to his roll value
            case 4:
                hitbonus(2, 0, 'p');                        //hit bonus
                break;
                //wall walkthrough
            case 5:
                vision(tgtid, psp->duration);              //vision
                break;
            case 6:
                drainlife(tgtid, targn, 'p', (SHORT)usrnum, psp->mhd); //life drain
                break;
            case 7:
                heal(tgtid, (SHORT)usrnum, psp->mhd, (SHORT)usrnum);         //heal
                break;
                //plain damage
            case 8:
                dodamage(targn, tgtid, calcfspdmg(psp->mhd, psp->xmhd, rmod));
                break;
            case 9:
                youth(tgtid, targn, psp->mhd, (SHORT)usrnum);       //youth
                break;
            case 10:
                agehim(tgtid, targn, psp->mhd, 'p', (SHORT)usrnum);  //aging
                break;
            case 11:
                curepoison(tgtid, targn, (SHORT)usrnum);           //cure_poison
                break;
            case 12:
                revive(tgtid, targn);                      //resurrect
                break;
            case 13:
                kill(tgtid, targn, 'p', (SHORT)usrnum);             //kill
                break;
            default:
                prf("unknwon spell action");
                outprf(usrnum);
        }
    }
}

VOID castpwr(SPELLINF* psp, SHORT rmod)
{
    SHORT tgt = 0, abort = FALSE;
    CHAR tgtid = 0, nstr[81];
    USHORT i, srang, dist;
    VDABLK* pvda;
    SHORT mx = 0, my = 0, playerloc, playerx, playery;

    zplyr->currmp -= psp->mp;
    // locate the target
    if (psp->target == 0 || psp->type == 2 || psp->type == 5) {// scry fix
        tgtid = 'p';
        tgt = (SHORT)usrnum;
    } else {
        if (zvda->gstate == INFITE) {
            if (psp->target == 1) {
                switch (tsthit(zcbr->chx, zcbr->chy)) {
                    case HITMON:
                        tgt = locmonst(zcbr->chx, zcbr->chy);
                        if (tgt != NOTFOUND) {
                            mx = zcbr->monx[tgt];
                            my = zcbr->mony[tgt];
                            tgtid = 'm';
                        } else {
                            prfmsg(LOSTGT, 'm');
                            outprf(usrnum);
                            abort = TRUE;
                        }
                        break;
                    case HITPLYR:
                        playerloc = locplayer(zcbr->chx, zcbr->chy);
                        if (playerloc != NOTFOUND) {
                            tgt = zcbr->plyrs[playerloc];
                            mx = zcbr->plx[playerloc];
                            my = zcbr->ply[playerloc];
                            tgtid = 'p';
                        } else {
                            prfmsg(LOSTGT, 'p');
                            outprf(usrnum);
                            abort = TRUE;
                        }
                        break;
                    default:
                        sprintf(nstr, "%s manages to ensorcel a brick!", zplyr->name);
                        encnews(nstr);
                        abort = TRUE;
                }
                /* test range */

                if (!abort) {
                    // RH: Some of this only applies if we actually found a player or monster
                    playerx = zcbr->plx[zvda->cbrpos];
                    playery = zcbr->ply[zvda->cbrpos];
                    dist = abs(mx - playerx) + abs(my - playery);
                    srang = psp->range + (psp->xrange * zplyr->level);
                    if (mx != playerx && my != playery) {
                        dist >>= 1;
                        if (dist == 0)
                            dist = 1;
                    }
                    if (dist > srang) {
                        addnews(psp->text, (SHORT)usrnum);
                        addnews("But the target is out of range!", (SHORT)usrnum);
                        abort = TRUE;
                    }
                }
            } else {
                switch (zcbr->entype) {
                    case 'm':
                        tgtid = 'm';
                        // RH: was uninitialized use case
                        tgt = locmonst(zcbr->chx, zcbr->chy);
                        if (tgt == NOTFOUND) {
                            prfmsg(LOSTGT, 'm');
                            outprf(usrnum);
                            abort = TRUE;
                        }
                        // RH: end of added code
                        break;
                    case 'p':
                        if (psp->target == 2) {
                            tgt = zvda->party;
                            tgtid = 'p';
                        } else {
                            for (i = 0; i < zcbr->pcnt; i++)
                                if (zcbr->pgrp[zvda->cbrpos] != zcbr->pgrp[i])
                                    break;
                            if (i < zcbr->pcnt) {
                                pvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                                tgt = pvda->party;
                                tgtid = 'p';
                            } else {
                                prfmsg(EBLLN);
                                prfmsg(NOEGRPP);
                                outprf(usrnum);
                                abort = TRUE;
                            }
                        }
                        break;
                    default:
                        abort = TRUE;
                }
            }
        } else {      //not fite
            switch (psp->target) {
                case 3: prfmsg(WBLLN);
                    prfmsg(NOEGRP);
                    outprf(usrnum);
                    abort = TRUE;
                    break;
                case 1: tgt = (SHORT)usrnum;
                    tgtid = 'p';
                    break;
                case 2: tgt = zvda->party;
                    tgtid = 'p';
                    break;
                case 4: tgt = zvda->obn;
                    tgtid = 'p';
                    break;
                case 0: arxy(1, 21);
                    prf("%s has no target", psp->spellname);
                default: arxy(1, 22);
                    prf("uxpectd !FITE spell");
                    outprf(usrnum);
                    restcomp();
                    abort = TRUE;
                    break;
            }
        }
    }

    if (!abort) {
        if (zvda->gstate == INFITE)
            addnews(psp->text, (SHORT)usrnum);
        else {
            arxy(1, 16);
            prf("%s", psp->text);
            outprf(usrnum);
        }
        if ((tgtid == 'm' && psp->target != 3) ||
            (tgtid == 'p' && psp->target <= 1)) {
            castit(psp, rmod, tgtid, tgt);
        } else {
            switch (tgtid) {
                case 'p': pvda = (VDABLK*)vdaoff(tgt);
                    for (i = 0; i < pvda->memcnt; i++)
                        castit(psp, rmod, tgtid, pvda->members[i]);
                    break;
                case 'm': for (i = 0; i < zcbr->mcount; i++)
                    castit(psp, rmod, tgtid, i);
                    break;
            }
        }
    }
}

VOID castproc(VOID)
{
    USHORT i, j, k;
    CHAR itstr[7] = { 0 }, nstr[24] = { 0 }, kky;
    SHORT dmod;
    SPELLINF* pzp;

    switch (zvda->mstate) {
        case 0: zvda->mnukey--;
            delbox(1, 48, zvda->litcnt);
            if (zvda->mnukey < zvda->litcnt) {
                i = (8 - zvda->mnukey) * 5;
                zvda->uxitk = i;
                k = 0;
                for (j = 0; j < 5; j++)
                    switch (zvda->cstype) {
                        case 'w': if (zplyr->mage[i + j] != NOTFOUND) {
                            zvda->mnuslt[k] = (CHAR)j;
                            k++;
                        }
                                break;
                        case 'c': if (zplyr->cleric[i + j] != NOTFOUND) {
                            zvda->mnuslt[k] = (CHAR)j;
                            k++;
                        }
                                break;
                    }
                if (k > 0) {
                    prfmsg(WBLLN);
                    prfmsg(PIKSPEL);
                    outprf(usrnum);
                    for (j = 0; j < k; j++) {
                        arxy(48, j + 4);
                        itstr[j] = (CHAR)'A' + (CHAR)j;
                        prf("[0;1;41mº [33;40m%c[37;41m [40m [32m", itstr[j]);
                        switch (zvda->cstype) {
                            case 'w': stzcpy(nstr, wizspell[zplyr->mage[i + zvda->mnuslt[j]]].spellname, 20);
                                break;
                            case 'c': stzcpy(nstr, clerspell[zplyr->cleric[i + zvda->mnuslt[j]]].spellname, 20);
                                break;
                        }
                        while (strlen(nstr) < 20)
                            strcat(nstr, " ");
                        prf(nstr);
                        prf("[37m[41m º[0m");
                    }
                    itstr[j] = (CHAR)'A' + (CHAR)j;
                    zvda->litcnt = j;
                    arxy(48, j + 4);
                    prfmsg(PKSPX, itstr[j]);
                    outprf(usrnum);
                    arxy(48, j + 5);
                    prfmsg(PKSPXL);
                    outprf(usrnum);
                    zvda->mstate = 1;
                    ansimenu(1, 48, 27, j + 1, itstr, 27, -2);
                } else {
                    if (zvda->gstate == INFITE)
                        prfmsg(EBLLN);
                    else
                        prfmsg(WBLLN);
                    prfmsg(NOSPLVL);
                    outprf(usrnum);
                    askpower(zvda->cstype, 27);
                }
            } else {
                if (zvda->gstate == INFITE) {
                    zvda->mstate = 20;
                    usrptr->substt = 80;
                } else
                    restcomp();
            }
            break;
        case 1: zvda->mnukey--;
            delbox(1, 48, zvda->litcnt);
            if (zvda->mnukey < zvda->litcnt) {
                i = (USHORT)random(100);
                if (i > zvda->prace.cast)
                    dmod = 0 - zvda->prace.cast;
                else
                    dmod = 0;
                pzp = (zvda->cstype == 'w') ? &wizspell[zplyr->mage[zvda->uxitk + zvda->mnuslt[zvda->mnukey]]] :
                    &clerspell[zplyr->cleric[zvda->uxitk + zvda->mnuslt[zvda->mnukey]]];
                // RH: the below code was ambiguous - we know it should only be w or c but what if it isn't?
     /*           switch (zvda->cstype) {
                 case 'w': pzp=&wizspell[zplyr->mage[zvda->uxitk+zvda->mnuslt[zvda->mnukey]]];
                           break;
                 case 'c': pzp=&clerspell[zplyr->cleric[zvda->uxitk+zvda->mnuslt[zvda->mnukey]]];
                           break;
                } */
                zvda->spdmg = 0;
                if (zplyr->currmp >= pzp->mp) {
                    switch (zvda->gstate) {
                        case INFITE: zvda->mstate = 19;
                            usrptr->substt = 80;
                            switch (pzp->target) {
                                case 0:
                                case 2:
                                case 3: castpwr(pzp, dmod);
                                    break;
                                case 1: if (pzp->type == 2 ||
                                    pzp->type == 5) {
                                    castpwr(pzp, dmod);
                                } else {
                                    prfmsg(COMRST);
                                    outprf(usrnum);
                                    plotguys();
                                    prtnews();
                                    usrptr->substt = 80;
                                    zvda->cstate = dmod;
                                    zvda->savpzp = pzp;
                                    piktarg(18);
                                }
                                      break;
                            }
                            break;
                        case PLAYING: if (pzp->target == 4) {
                            for (j = 0; j < 49; j++)
                                if (zvda->ovchn[j] < nterms)
                                    break;
                            if (j < 49) {
                                zvda->mstate = 2;
                                zvda->cstate = dmod;
                                zvda->savpzp = pzp;
                                prfmsg(WBLLN);
                                prfmsg(PIKPTY);
                                outprf(usrnum);
                            } else {
                                prfmsg(WBLLN);
                                prfmsg(NOBTHR);
                                outprf(usrnum);
                                restcomp();
                            }
                        } else
                            castpwr(pzp, dmod);
                        break;
                    }
                } else {
                    if (zvda->gstate == INFITE)
                        prfmsg(EBLLN);
                    else
                        prfmsg(WBLLN);
                    prfmsg(NEMP);
                    outprf(usrnum);
                }
            } else {
                zvda->mstate = 0;
                askpower(zvda->cstype, 27);
            }
            break;
        case 2: if (btuica(usrnum, kpress, 4) > 0) {
            btucli(usrnum);
            kky = xltkey();
            if (kky >= 'A' && kky < 'U') {
                i = kky - 'A';
                if (zvda->ovchn[i] < nterms) {
                    if (ingame[i]) {
                        xlvda = (VDABLK*)vdaoff(i);
                        if (xlvda->gstate > ISACTIVE) {
                            if (xlvda->party == i)
                                zvda->obn = i;
                            else
                                zvda->obn = xlvda->party;
                            castpwr(zvda->savpzp, zvda->cstate);
                            restcomp();
                        } else {
                            prfmsg(WBLLN);
                            prfmsg(DAYBGN);
                            outprf(usrnum);
                            restcomp();
                        }
                    } else {
                        prfmsg(WBLLN);
                        prfmsg(DAYBGN);
                        outprf(usrnum);
                        restcomp();
                    }
                } else {
                    prfmsg(WBLLN);
                    prfmsg(DAYBGN);
                    outprf(usrnum);
                    restcomp();
                }
            } else {
                prfmsg(WBLLN);
                outprf(usrnum);
                restcomp();
            }
            usrptr->substt = 20;
        }
              break;
        case 3: castpwr(zvda->savpzp, zvda->cstate);
        case 4: if (zvda->gstate == INFITE) {
            usrptr->substt = 80;
            zvda->mstate = 19;
        } else {
            restplay();
        }
              break;
        case 44: zvda->mnukey--;
            switch (zvda->mnukey) {
                case 0: zvda->cstype = 'w';
                    zvda->mstate = 0;
                    askpower(zvda->cstype, 27);
                    break;
                case 1: zvda->cstype = 'c';
                    zvda->mstate = 0;
                    askpower(zvda->cstype, 27);
                    break;
                default: if (zvda->gstate == INFITE) {
                    zvda->mstate = 20;
                    usrptr->substt = 80;
                } else
                    restcomp();
            }
            break;
        default: if (zvda->gstate == INFITE) {
            zvda->mstate = 20;
            usrptr->substt = 80;
        } else
            restcomp();
    }
}

VOID castinit(VOID)
{
    USHORT i, j;
    SHORT spell = FALSE, cly = FALSE, magy = FALSE;
    for (i = 0; i < 9; i++)
        if (zplyr->mage_new[i] > 0) {
            for (j = 0; j < 5; j++)
                if (zplyr->mage[i * 5 + j] != NOTFOUND) {
                    spell = TRUE;
                    break;
                }
            if (spell) {
                magy = TRUE;
                zvda->cstype = 'w';
                break;
            }
        }
    for (i = 0; i < 9; i++)
        if (zplyr->cleric_new[i] > 0) {
            for (j = 0; j < 5; j++)
                if (zplyr->cleric[i * 5 + j] != NOTFOUND) {
                    spell = TRUE;
                    break;
                }
            if (spell) {
                cly = TRUE;
                zvda->cstype = 'c';
                break;
            }
        }
    if (!spell) {
        if (zvda->gstate == INFITE)
            prfmsg(EBLLN);
        else
            prfmsg(WBLLN);
        prfmsg(NOSPELC);
        outprf(usrnum);
    } else {
        if (magy && cly) {
            zvda->mstate = 44;
            ansimenu(1, 48, 27, 3, "WCX", 27, PIKWOC);
        } else {
            zvda->mstate = 0;
            askpower(zvda->cstype, 27);
        }
    }
}

VOID talktest(VOID)
{
    SHORT i;
    zvda->ontop = FALSE;
    if (ptest())
        zvda->ontop = TRUE;
    else {
        for (i = 0; i < nterms; i++)
            if (ingame[i]) {
                xlvda = (VDABLK*)vdaoff(i);
                if (plevel == xlvda->plyr.curlvl && i != usrnum &&
                    prow == xlvda->plyr.row &&
                    pcol == xlvda->plyr.col &&
                    (xlvda->gstate == PLAYING || xlvda->gstate == INCHAT)) {
                    zvda->ontop = TRUE;
                    break;
                }
            }
    }
}

SHORT loadrclass(VOID)
{
    SHORT ioc, rc = 0, match;
    USHORT i;

    racecnt = classcnt = 0;
    dfaSetBlk(dbrace);
    ioc = dfaStepNX(&raceinf);
    while (ioc == 1) {
        match = FALSE;
        if (racecnt) {
            for (i = 0; i < racecnt; i++)
                if (sameas(raceinf.name, racebase[i].name)) {
                    match = TRUE;
                    break;
                }
        } else {
            match = FALSE;
        }
        if (!match) {
            racebase[racecnt].racepos = dfaAbs();
            stzcpy(racebase[racecnt].name, raceinf.name, 20);
            racecnt++;
        }
        ioc = dfaStepNX(&raceinf);
        if (racecnt == MAXRACES)
            ioc = 0;
    }
    dfaRstBlk();
    if (racecnt == 0)
        rc = 1;
    dfaSetBlk(dbclass);
    ioc = dfaStepNX(&classinf);
    while (ioc == 1) {
        match = FALSE;
        if (classcnt) {
            for (i = 0; i < classcnt; i++)
                if (sameas(classinf.name, classbase[i].name)) {
                    match = TRUE;
                    break;
                }
        } else {
            match = FALSE;
        }
        if (!match) {
            classbase[classcnt].classpos = dfaAbs();
            stzcpy(classbase[classcnt].name, classinf.name, 20);
            classcnt++;
        }
        ioc = dfaStepNX(&classinf);
        if (classcnt == MAXCLASS)
            ioc = 0;
    }
    dfaRstBlk();
    if (classcnt == 0)
        rc = 1;
    return(rc);
}

SHORT loadplay(VOID)
{
    GBOOL rc; SHORT ctr; //=0, ctr;

    dfaSetBlk(dbplayer);
    rc = dfaAcqEQ(&tplayer, usaptr->userid, 0);
    if (rc) {
        zvda->plyr = tplayer.plyr;
        for (ctr = 0; ctr < MAXPOBJC; ctr++) { zvda->pstuff[ctr] = tplayer.pstuff[ctr]; }
        dfaSetBlk(dbrace);
        dfaAcqAbs(&zvda->prace, racebase[zplyr->race].racepos, 0);
        dfaRstBlk();
        dfaSetBlk(dbclass);
        dfaAcqAbs(&zvda->pclass, classbase[zplyr->class].classpos, 0);
        dfaRstBlk();
    }
    dfaRstBlk();
    return(rc);
}

VOID saveplay(VOID)
{
    GBOOL rc; SHORT ctr; //=0, ctr;
    VDABLK* hzvda;        //local for hangup case

    hzvda = (VDABLK*)vdaoff(usrnum);
    dfaSetBlk(dbplayer);
    rc = dfaAcqEQ(&tplayer, usaptr->userid, 0);
    strcpy(tplayer.name, usaptr->userid);
    tplayer.plyr = hzvda->plyr;
    for (ctr = 0; ctr < MAXPOBJC; ctr++)
        tplayer.pstuff[ctr] = hzvda->pstuff[ctr];
    if (rc) {
        strcpy(tplayer.score, l2as(tplayer.plyr.exp));
        dfaUpdate(&tplayer);
    } else {
        strcpy(tplayer.plyr.name, usaptr->userid);
        strcpy(tplayer.score, "0");
        dfaInsert(&tplayer);
    }
    dfaRstBlk();
}

VOID gen_CHAR(VOID)
{
    saveplay();
    usrptr->substt = 2;
    zvda->redraw = 1;
}

VOID arxy(SHORT x, SHORT y)
{
    CHAR xstr[15];
    strcpy(xstr, spr("[%d;%dH", y, x));
    prf(xstr);
}

SHORT index(CHAR* str1, CHAR ky)
{
    SHORT j, len;

    len = (SHORT)strlen(str1);
    for (j = 0; j < len; j++) {
        if (toupper(str1[j]) == toupper(ky))
            break;
    }
    if (j == len) j = NOTFOUND;

    return(j);
}

VOID riprest(VOID)
{
    prfmsg(RIPCLR);
    outprf(usrnum);
    prfmsg(CLBAR);
    outprf(usrnum);
    if (chkdrop()) {
        prfmsg(SUMMAT);
        outprf(usrnum);
    } else {
        dodrunk();
    }
}


VOID restplay(VOID)
{
    if (zvda->rip) {
        riprest();
        goto restfin;
    }
    prfmsg(CLRSCR);
    prfmsg(COMPDAT);
    arxy(1, 18);
    prfmsg(CLBAR);
    outprf(usrnum);
    if (chkdrop()) {
        prfmsg(SUMMAT);
        outprf(usrnum);
    } else {
        dodrunk();
    }
restfin:
    zvda->nstat = TRUE;
    setwall();
    draw();
    zvda->redraw = FALSE;
    zvda->gstate = PLAYING;
    usrptr->substt = 20;
}

VOID dospecial(SHORT itm)
{

    switch (zvda->pstuff[itm].osp) {
        case 12: vision('p', (CHAR)(random(10) + 1));   //vision
            break;
        case 0:                              //nada
        case 11: prfmsg(WBLLN);
            prfmsg(NOHAPP);              //cursed
            outprf(usrnum);
            break;
            /* battle spells */
        case 1:                              //poison
        case 3:                              //level drain
        case 4:                              //life drain
        case 5:                              //aging
        case 6:                              //paralysis
        case 7:                              //critical
            //bonus on top of wpn damage
        case 9:                              //xdmg
        case 10: prfmsg(WBLLN);               //shield
            prfmsg(ICBONLY);
            outprf(usrnum);
            break;
        case 2: if (zplyr->condition[1] > 0) {   //cure poison
            curepoison('p', (SHORT)usrnum, (SHORT)usrnum);
            statup(itm, (SHORT)usrnum, (SHORT)usrnum);
        } else {
            prfmsg(WBLLN);
            prfmsg(NOHAPP);
            outprf(usrnum);
        }
              break;
        case 8: if (zplyr->currhp >= zplyr->maxhp) {     //heal
            prfmsg(WBLLN);
            prfmsg(NONEEDH);
            outprf(usrnum);
        } else {
            heal('p', (SHORT)usrnum, zvda->pstuff[itm].osp, (SHORT)usrnum);
            statup(itm, (SHORT)usrnum, (SHORT)usrnum);
        }
              break;
    }
}

VOID restcomp(VOID)
{
    prfmsg(COMPRST);
    outprf(usrnum);
    zvda->nstat = TRUE;
    drawstats();
    zvda->redraw = FALSE;
    zvda->gstate = PLAYING;
    usrptr->substt = 20;
}

VOID useit(VOID)
{
    SHORT i, tg, tgt, ttp, nogo = FALSE;

    i = zvda->mnukey;
    if (!chkusage(zvda->pstuff[i].oclass)) {
        if (zvda->gstate == INFITE)
            prfmsg(EBLLN);
        else
            prfmsg(WBLLN);
        prfmsg(NYCLS);
        outprf(usrnum);
    }
    if (zvda->pstuff[i].objname[0] != 0 && zplyr->equip[i] != 1 && (zvda->pstuff[i].owhat == 1 || (zvda->pstuff[i].owhat == 2 && zvda->gstate == INFITE))) {
        switch (zvda->pstuff[i].otype) {
            case 0:                                 //weapon
            case 1:
                if (zvda->gstate == INFITE)         //armor
                    prfmsg(EBLLN);
                else
                    prfmsg(WBLLN);
                outprf(usrnum);
                prfmsg(NOUSE);                      //armor
                outprf(usrnum);
                break;
            case 2:                                 //ring
            case 3:                                 //potion
            case 4:                                 //stone
            case 5:                                 //amulet
            case 6:
                if (zvda->pstuff[i].osp != 0) {     //scroll
                    if (zvda->pstuff[i].ocsp >= 100 || (zvda->pstuff[i].ocsp > 0 && random(100) <= zvda->pstuff[i].ocsp)) {
                        if (zvda->pstuff[i].ortype != 0) {
                            switch (zvda->pstuff[i].ortype) {
                                case 1:
                                    if (zplyr->arrows < 1) {           //arrows
                                        if (zvda->gstate == INFITE)
                                            prfmsg(EBLLN);
                                        else
                                            prfmsg(WBLLN);
                                        prfmsg(NOARW);
                                        outprf(usrnum);
                                        nogo = TRUE;
                                    } else {
                                        zplyr->arrows--;
                                    }
                                    break;
                                case 2:
                                    if (zplyr->rocks < 1) {           //rocks
                                        if (zvda->gstate == INFITE)
                                            prfmsg(EBLLN);
                                        else
                                            prfmsg(WBLLN);
                                        prfmsg(NOROKS);
                                        outprf(usrnum);
                                        nogo = TRUE;
                                    } else {
                                        zplyr->rocks--;
                                    }
                                    break;
                                case 3:
                                    if (zplyr->darts < 1) {           //darts
                                        if (zvda->gstate == INFITE)
                                            prfmsg(EBLLN);
                                        else
                                            prfmsg(WBLLN);
                                        prfmsg(NODART);
                                        outprf(usrnum);
                                        nogo = TRUE;
                                    } else {
                                        zplyr->darts--;
                                    }
                                    break;
                            }
                        }
                        if (!nogo)
                            if (zvda->gstate != INFITE) {
                                dospecial(i);
                            } else {
                                tg = tsthit(zcbr->chx, zcbr->chy);
                                if (tg == HITMON || tg == HITPLYR) {
                                    ttp = ' ';
                                    tgt = 0;
                                    switch (tg) {
                                        case HITMON:
                                            tgt = locmonst(zcbr->chx, zcbr->chy);
                                            if (tgt != NOTFOUND)
                                                ttp = 'm';
                                            else
                                                ttp = ' ';
                                            break;
                                        case HITPLYR:
                                            for (tgt = 0; tgt < zcbr->pcnt; tgt++)
                                                if (zcbr->plx[tgt] == zcbr->chx &&
                                                    zcbr->ply[tgt] == zcbr->chy)
                                                    break;
                                            if (tgt < zcbr->pcnt)
                                                ttp = 'p';
                                            else
                                                ttp = ' ';
                                            break;
                                    }
                                    if (ttp != ' ') {
                                        zvda->obn = i;
                                        dospec((CHAR)ttp, tgt, zvda->pstuff[i].osp, zvda->pstuff[i].osphd, 'p');
                                    } else {
                                        prfmsg(EBLLN);
                                        prf("Nothing to use it on!");
                                        outprf(usrnum);
                                    }
                                } else {
                                    prfmsg(EBLLN);
                                    prf("Nothing to use it on!");
                                    outprf(usrnum);
                                }
                            }
                    } else {
                        prfmsg(EBLLN);
                        if (zvda->gstate != INFITE) {
                            prfmsg(WBLLN);
                            prfmsg(NOHAPP);
                            outprf(usrnum);
                        } else {
                            prfmsg(EBLLN);
                            prfmsg(IFIZZL);
                            outprf(usrnum);
                        }
                    }
                    if (zvda->pstuff[i].otsp != 999)
                        zvda->pstuff[i].otsp--;
                    if (zvda->pstuff[i].otsp < 1)
                        zvda->pstuff[i].objname[0] = 0;
                } else {
                    if (zvda->gstate != INFITE) {
                        prfmsg(WBLLN);
                        prfmsg(NOHAPP);
                        outprf(usrnum);
                    } else {
                        prfmsg(EBLLN);
                        prfmsg(IFIZZN);
                        outprf(usrnum);
                    }
                }
        }
    }
}

VOID useinit(VOID)
{
    SHORT i, j;//=0;

    j = 0;
    for (i = 0; i < MAXPOBJC; i++) {
        zvda->mnuslt[i] = 0;
        if (zvda->pstuff[i].objname[0] != 0 &&
            (zvda->pstuff[i].owhat == 1 ||
                (zvda->pstuff[i].owhat == 2 && zvda->gstate == INFITE))) {
            j++;
            zvda->mnuslt[i] = 1;
        }
    }
    zvda->litcnt = j;
}

VOID terror2(VOID)
{
    SHORT i;
    for (i = 0; i < nterms; i++) {
        if (ingame[i]) {
            xlvda = (VDABLK*)vdaoff(i);
            if (xlvda->myuser->state == modnum)
                xlvda->myuser->substt = FATALE;
        }
        ingame[i] = FALSE;
    }
}

VOID terror(VOID)
{
    terror2();
    cantrun = TRUE;
}

VOID cbroff(SHORT unum)
{
    zcbr = (CBREC*)ptrblok(cobase, unum);
}

SHORT ptest(VOID)
{
    SHORT j = FALSE;

    if (zvda->party != usrnum ||
        (zvda->party == usrnum && zvda->memcnt > 1))
        j = TRUE;
    return(j);
}

VOID xparty(SHORT ldr)
{
    SHORT i, mch;
    VDABLK* lvda, * mvda;
    lvda = (VDABLK*)vdaoff(ldr);
    if (lvda->party == ldr) {
        for (i = 0; i < lvda->memcnt; i++) {
            mch = lvda->members[i];
            mvda = (VDABLK*)vdaoff(mch);
            if (ingame[mch] && mvda->party == ldr)
                outprf(mch);
        }
    }
}

VOID qparty(SHORT usern)
{
    VDABLK* tvda, * pvda;
    SHORT i, j = 0;

    pvda = (VDABLK*)vdaoff(usern);
    if (pvda->party != usern && ingame[usern]) {
        tvda = (VDABLK*)vdaoff(pvda->party);
        if (tvda != NULL && ingame[pvda->party]) {
            for (i = 0; i < tvda->memcnt; i++)
                if (tvda->members[i] != usern) {
                    tvda->members[j] = tvda->members[i];
                    j++;
                }
            tvda->memcnt = j;
        }
        pvda->party = usern;
        pvda->memcnt = 1;
        pvda->members[0] = usern;
    }
}

VOID lparty(SHORT usr)
{
    VDABLK* lvda, * pvda;

    if (ingame[usr]) {
        pvda = (VDABLK*)vdaoff(usr);
        if (pvda->party != usr)
            qparty(usr);
        else {
            lvda = (VDABLK*)vdaoff(pvda->party);
            while (lvda->memcnt > 1) {
                qparty(lvda->members[lvda->memcnt - 1]);
            }
        }
    }
}

VOID xtavrn(CHAR who)
{
    SHORT i;

    for (i = 0; i < nterms; i++)
        if (ingame[i]) {
            xlvda = (VDABLK*)vdaoff(i);
            if (xlvda->gstate == TAVCHT)
                switch (who) {
                    case 'a': outprf(i);
                        break;
                    case 't': if (i != usrnum)
                        outprf(i);
                        break;
                }
        }
    clrprf();
}

VOID xlounge(CHAR who)
{
    SHORT i;

    for (i = 0; i < nterms; i++)
        if (ingame[i] && i != usrnum) {
            xlvda = (VDABLK*)vdaoff(i);
            if (xlvda->gstate == INCHAT &&
                xlvda->plyr.curlvl == plevel &&
                xlvda->plyr.row == prow &&
                xlvda->plyr.col == pcol)
                switch (who) {
                    case 'a': outprf(i);
                        break;
                    case 't': if (i != usrnum)
                        outprf(i);
                    case 'p': if (xlvda->party == zvda->party)
                        outprf(i);
                }
        }
    clrprf();
}

VOID gochat(VOID)
{
    SHORT i;
    VDABLK* mvda;
    for (i = 0; i < nterms; i++)
        if (ingame[i]) {
            mvda = (VDABLK*)vdaoff(i);
            if (plevel == mvda->plyr.curlvl &&
                prow == mvda->plyr.row &&
                pcol == mvda->plyr.col &&
                mvda->gstate == PLAYING) {
                mvda->myuser->substt = 35;
            }
        }

}

VOID itlist(SHORT pgno)
{
    USHORT i, j, stpos;
    CHAR itstr[30] = { 0 }, nstr[30] = { 0 };

    stpos = 0;
    if (pgno) {
        for (i = 0; i < MAXPOBJC; i++)
            if (zvda->mnuslt[i] == 1) {
                stpos++;
                if (stpos == 11)
                    break;
            }
        stpos = i;
    }
    j = 0;
    if (!zvda->rip) {
        prfmsg(ITSEL);
        for (i = stpos; i < MAXPOBJC; i++) {
            arxy(50, j + 4);
            if (zvda->mnuslt[i] == 1) {
                itstr[j] = (CHAR)'A' + (CHAR)j;
                prf("[0;1;41mº[33;40m %c[37;41m [40m [32m", itstr[j]);
                stzcpy(nstr, zvda->pstuff[i].objname, 20);
                while (strlen(nstr) < 20)
                    strcat(nstr, " ");
                prf(nstr);
                prf("[37m[41mº[0m\n");
                j++;
            }
            outprf(usrnum);
            if (j == 10)
                break;
        }
        itstr[j] = 0;
        zvda->mnulast = j;
        if (zvda->mnucnt > 10) {
            strcat(itstr, "KL");
            if (pgno) {
                if (j < 10)
                    delbox(j + 6, 50, 10 - j + 2);
                prfmsg(PPAGE, j + 4, j + 5, j + 6);
            } else
                prfmsg(NPAGE);
            j += 2;
        } else {
            itstr[j] = (CHAR)'A' + (CHAR)j;
            arxy(50, j + 4);
            prfmsg(ITSEL1, itstr[j]);
            j++;
            arxy(50, j + 4);
            prfmsg(ITSEL2);
            itstr[j] = 0;
        }
        outprf(usrnum);
    } else {
        strcpy(zvda->query, "((*Inventory List::");
        for (i = stpos; i < MAXPOBJC; i++) {
            if (zvda->mnuslt[i] == 1) {
                itstr[j] = (CHAR)'A' + (CHAR)j;
                stzcpy(nstr, zvda->pstuff[i].objname, 20);
                while (strlen(nstr) < 20)
                    strcat(nstr, " ");
                strcat(zvda->query, spr("%c@%s,", itstr[j], nstr));
                j++;
            }
            if (j == 10)
                break;
        }
        itstr[j] = 0;
        zvda->mnulast = j;
        if (zvda->mnucnt > 10) {
            strcat(itstr, "KL");
            if (pgno) {
                if (j < 10)
                    strcat(zvda->query, "K@Previous Page,L@Abort))");
            } else
                strcat(zvda->query, "K@Next Page,L@Abort))");
            j += 2;
        } else {
            itstr[j] = (CHAR)'A' + (CHAR)j;
            strcat(zvda->query, spr("%c@Abort))", itstr[j]));
            j++;
            itstr[j] = 0;
        }
        rip_query(0, 0, zvda->query);
    }
    // row/col/width/#items/cmchars/rstate
    ansimenu(1, 50, 26, j, itstr, 30, -2);
}

VOID pagemenu(SHORT rstate, SHORT obcnt, SHORT clrl)
{

    zvda->mnupage = 0;
    zvda->mnucnt = obcnt;
    zvda->mpstate = rstate;
    if (clrl)
        delinm();
    itlist(0);
}

VOID pageproc(VOID)
{
    USHORT i;

    if (zvda->mnukey > zvda->mnulast) {
        if (zvda->mnucnt <= 10) {
            zvda->mnukey = 0;
            usrptr->substt = zvda->mpstate;
        } else {
            if (zvda->mnupage == 0) {
                if (zvda->mnukey == zvda->mnulast + 1 && zvda->mnucnt > 10) {
                    zvda->mnupage = 1;
                    itlist(1);
                } else {
                    zvda->mnukey = 0;
                    usrptr->substt = zvda->mpstate;
                }
            } else {
                if (zvda->mnukey == zvda->mnulast + 1) {
                    zvda->mnupage = 0;
                    itlist(0);
                } else {
                    zvda->mnukey = 0;
                    usrptr->substt = zvda->mpstate;
                }
            }
        }
    } else {
        if (zvda->mnupage == 1)
            zvda->mnukey += 10;
        for (i = 0; i < MAXPOBJC; i++)
            if (zvda->mnuslt[i] == 1) {
                zvda->mnukey--;
                if (zvda->mnukey == 0)
                    break;
            }
        zvda->mnukey = (CHAR)i;
        zvda->mnukey++;
        usrptr->substt = zvda->mpstate;
    }
}

VOID dropit(VOID)
{
    USHORT i, ocnt = 0;

    for (i = 0; i < MAXPOBJC; i++)
        if (zvda->pstuff[i].objname[0] != 0) ocnt++;
    if (ocnt) {
        for (i = 0; i < MAXPOBJC; i++)
            if (zvda->pstuff[i].objname[0] != 0)
                zvda->mnuslt[i] = 1;
            else
                zvda->mnuslt[i] = 0;
        zvda->mstate = 0;
        pagemenu(23, ocnt, TRUE);
    } else {
        prfmsg(NODROP);
        prfmsg(ANYKEY);
        outprf(usrnum);
        usrptr->substt = 22;
    }
}

VOID dodrop(VOID)
{

    switch (zvda->mstate) {
        case 0: if (zvda->mnukey) {
            zvda->mnukey--;
            prfmsg(WBLLN);
            prfmsg(DROPIT, zvda->pstuff[zvda->mnukey].objname);
            outprf(usrnum);
            zvda->mstate = 1;
            zvda->uxitk = zvda->mnukey;
            getyno(23);
        } else {
            delbox(14, 50, 7);
            restcomp();
            arxy(1, 18);
            prfmsg(CLBAR);
            outprf(usrnum);
        }
              break;
        case 1: if (zvda->mnukey == 'Y') {
            if (zvda->pstuff[zvda->uxitk].osp != 11) {
                prfmsg(WBLLN);
                prfmsg(DROPPED, zvda->pstuff[zvda->uxitk].objname);
                dropupd('a', zvda->uxitk);
                zvda->pstuff[zvda->uxitk].objname[0] = 0;
                acplyr((SHORT)usrnum);
            } else {
                prfmsg(WBLLN);
                prfmsg(NDCI);
                outprf(usrnum);
            }
            if (!zvda->rip) {
                delbox(14, 50, 7);
                restcomp();
                arxy(1, 18);
                prfmsg(CLBAR);
                outprf(usrnum);
            }
        } else {
            zvda->mstate = 0;
            delinm();
            if (zvda->mnupage == 0)
                itlist(0);
            else
                itlist(1);
        }
              break;
        default: if (!zvda->rip) {
            delbox(14, 50, 7);
            restcomp();
            arxy(1, 18);
            prfmsg(CLBAR);
            outprf(usrnum);
        }
               break;
    }
}

VOID inventory(VOID)
{
    USHORT i, py = 3;
    prfmsg(INVLIN);
    outprf(usrnum);
    for (i = 0; i < MAXPOBJC; i++)
        if (zvda->pstuff[i].objname[0] != 0) {
            arxy(1, py);
            prf("%s", wcolours[zvda->pstuff[i].otype]);
            if (zplyr->equip[i] == 1)
                prf("*");
            else
                prf(" ");
            prf("%s", zvda->pstuff[i].objname);
            arxy(25, py);
            prf("%s", mu2[zvda->pstuff[i].otype]);
            arxy(50, py);
            prf("%s", mu6[zvda->pstuff[i].owhat]);
            prf("\n");
            outprf(usrnum);
            py++;
        }
    if (zplyr->arrows > 0) {
        prf("Arrows: %d  ", zplyr->arrows);
    }
    if (zplyr->darts > 0) {
        prf("Darts: %d  ", zplyr->darts);
    }
    if (zplyr->rocks > 0) {
        prf("Rocks: %d  ", zplyr->rocks);
    }
    outprf(usrnum);
    prf("\nPress return");
    outprf(usrnum);
    usrptr->substt = 21;
}

CHAR xltkey(VOID)
{
    CHAR rkey = '5';
    if (kpress[0] != 27) rkey = (CHAR)toupper(kpress[0]);
    else if (kpress[1] == '[') {
        switch (kpress[2]) {
            case 'A': rkey = '8';
                break;
            case 'B': rkey = '2';
                break;
            case 'C': rkey = '6';
                break;
            case 'D': rkey = '4';
                break;
            case 'H': rkey = '7';
                break;
            case 'K': rkey = '9';
                break;
        }
    }
    return(rkey);
}

USHORT loadmonst(VOID)
{
    USHORT pass = 0, stopme, mcnt = 0, rc; //=0;
    stopme = FALSE;
    dfaSetBlk(dbmonst);
    rc = dfaStepLO(&monstinf);
    while (!stopme) {
        switch (pass) {
            case 0: if (rc == 1) {
                rc = dfaStepNX(&monstinf);
                mcnt++;
            } else {
                if (mcnt > MAXMONST)
                    mcnt = MAXMONST;
                if (mcnt == 0) {
                    stopme = TRUE;
                    rc = 1;
                    break;
                }
                monbase = (MONENT*)alczer(mcnt * sizeof(MONENT));
                pass = 1;
                totmonst = 0;
                rc = dfaStepLO(&monstinf);
            }
                  break;
            case 1: if (rc == 1) {
                monbase[totmonst].monpos = dfaAbs();
                monbase[totmonst].monlvl = monstinf.level;
                rc = dfaStepNX(&monstinf);
                totmonst++;
            } else {
                stopme = TRUE;
            }
        }
    }
    dfaRstBlk();
    return(rc);
}

VOID getanum(SHORT rstt)
{
    zvda->rstate = rstt;
    usrptr->substt = WFANUM;
    nocycle();
}

VOID delbox(SHORT r, SHORT c, SHORT cnt)
{
    USHORT i, j;
    CHAR nstr[77] = { 0 };

    j = 78 - c + 1;
    for (i = 0; i < j; i++)
        nstr[i] = ' ';
    nstr[i] = 0;
    for (i = 0; i < cnt + 5; i++) {
        arxy(c, r + i);
        prf("%s", nstr);
        outprf(usrnum);
    }
}

VOID setcycle(VOID)
{
    zvda->incycle = TRUE;
    btutrg(usrnum, 4);
    btuxnf(usrnum, 0, 0);
    btupbc(usrnum, 0);
    btuinj(usrnum, CYCLE);
}

VOID nocycle(VOID)
{
    echon();
    zvda->incycle = FALSE;
    btutrg(usrnum, 0);
    btuxnf(usrnum, 0, 22);
    btupbc(usrnum, 20);
    dfsthn();
}

VOID td_writeln(CHAR* str1)
{
    prf("[s[1;1H\n");
    prf("%s\n", str1);
    prf("[u");
    outprf(usrnum);
}

VOID striprip(CHAR* pstr)
{
    SHORT j;
    if ((j = pos('~', pstr)) != 0) {
        delete(pstr, j, 1);
        insert(zplyr->name, pstr, (CHAR)j);
    }
    while ((j = pos('@', pstr)) != 0) {
        delete(pstr, j, 3);
    }
    while ((j = pos('|', pstr)) != 0) {
        delete(pstr, j, 1);
    }
}

USHORT length(CHAR* str1)
{
    USHORT i;
    i = str1[0];
    return(i);
}

// pascal to pascal type
VOID scopy(CHAR* dest, CHAR* src)
{
    CHAR i;
    for (i = 0; i <= length(src); i++) {
        dest[i] = src[i];
    }
}

// C to pascal copier
VOID scopyc(CHAR* dest, CHAR* src)
{
    CHAR i;
    for (i = 0; i < strlen(src); i++) {
        dest[i + 1] = src[i];
    }
    dest[0] = (CHAR)strlen(src);
}

//pascal s to C s
VOID cvtostr(CHAR* dest, CHAR* src)
{
    CHAR i = 0, j;
    j = src[0];
    while (i < j) {
        dest[i] = src[i + 1];
        i++;
    }
    dest[i] = 0;
}

//pascal to C in place
VOID cvstr(CHAR* str1)
{
    CHAR i = 0, j;
    j = str1[0];
    while (i < j) {
        str1[i] = str1[i + 1];
        i++;
    }
    str1[i] = 0;
}

VOID delete(CHAR* pstr1, SHORT dpos, SHORT dlen)
{
    SHORT i, j, k;
    j = pstr1[0];
    if (j) {
        if (dpos + dlen >= j) {
            if (dpos == 1)
                pstr1[0] = 0;
            else
                pstr1[0] = (CHAR)dpos;
        } else {
            pstr1[0] -= (CHAR)dlen;
            i = dpos;
            k = dpos + dlen;
            while (k <= j) {
                pstr1[i] = pstr1[k];
                i++;
                k++;
            }
        }
    }
}

SHORT pos(CHAR ch, CHAR* pstr)
{
    SHORT i = 1, match = FALSE;
    while (i <= pstr[0]) {
        if (pstr[i] == ch) {
            match = TRUE;
            break;
        }
        i++;
    }
    if (match)
        return(i);
    else
        return(0);
}

VOID snoozem(VOID)
{
    USHORT i;
    CHAR isin = FALSE;
    for (i = 0; i < 256; i++) {
        if (usrptr->state == modnum)
            isin = TRUE;
        if (snooze[i] == TRUE) {
            zvda->stimer -= 5;
            if (zvda->stimer == 0)
                usrptr->substt = zvda->rstate;
        }
    }
    if (isin)
        rtkick(5, snoozem);
    else
        ztimerf = FALSE;
}

VOID ststimer(SHORT rstt)
{
    zvda->rstate = rstt;
    usrptr->substt = DOZING;
    snooze[usrnum] = TRUE;
    if (!ztimerf) {
        ztimerf = TRUE;
        rtkick(5, snoozem);
    }
}

VOID getyno(SHORT rstt)
{
    zvda->rstate = rstt;
    usrptr->substt = ANSYNO;
}

SHORT cashcheck(ULONG cost)
{
    SHORT rc;
    if (zplyr->cash == 0 || zplyr->cash < cost)
        rc = FALSE;
    else {
        zplyr->cash -= cost;
        rc = TRUE;
    }
    return(rc);
}

SHORT loaddb(VOID)
{
    USHORT i;
    SHORT rc;//=0;
    OBJINF zobj;
    SPELLINF zspl;
    dfaSetBlk(miscitem);
    totpriz = 0;
    for (i = 0; i < MAXOBJCL; i++)
        objcnt[i] = 0;
    if ((rc = dfaStepLO(&zobj)) == 1) {
        while (rc) {
            if (totpriz < MAXPRIZ) {
                przbase[totpriz] = zobj;
                totpriz++;
            }
            if (objcnt[zobj.otype] < MAXOBJ) {
                i = objcnt[zobj.otype];
                switch (zobj.otype) {
                    case 0: wepbase[i] = zobj;
                        break;
                    case 1: armbase[i] = zobj;
                        break;
                    case 2: rinbase[i] = zobj;
                        break;
                    case 3: potbase[i] = zobj;
                        break;
                    case 4: stobase[i] = zobj;
                        break;
                    case 5: amubase[i] = zobj;
                        break;
                    case 6: scrbase[i] = zobj;
                        break;
                }
                objcnt[zobj.otype] += 1;
            }
            rc = dfaStepNX(&zobj);
        }
        rc = 0;
    } else rc = 1;
    dfaSetBlk(dbspells);
    wspellcnt = 0;
    cspellcnt = 0;
    if ((i = dfaStepLO(&zspl)) == 1) {
        while (i) {
            switch (zspl.class) {
                case 0: if (wspellcnt < MAXSPELL) {
                    if (zspl.target != 0) {
                        wizspell[wspellcnt] = zspl;
                        wspellcnt++;
                    }
                }
                      break;
                case 1: if (cspellcnt < MAXSPELL) {
                    if (zspl.target != 0) {
                        clerspell[cspellcnt] = zspl;
                        cspellcnt++;
                    }
                }
                      break;
            }
            i = dfaStepNX(&zspl);
        }
    } else rc = 1;
    dfaRstBlk();
    return(rc);
}

VOID uplevel(VOID)
{
    plevel += 1;
}

VOID downlevel(VOID)
{
    plevel -= 1;
}

VOID dodrunk(VOID)
{
    prfmsg(SUMBIT);
    outprf(usrnum);
    arxy(53, 13);
    if (zplyr->condition[0] == 0)
        prfmsg(SOBER);
    else if (zplyr->condition[0] > 60)
        prfmsg(INEB);
    else if (zplyr->condition[0] > 25)
        prfmsg(INTOX);
    else prfmsg(DRUNK);
    outprf(usrnum);
}

VOID drawarrows(SHORT r, SHORT c, SHORT ww)
{
    arxy(c + 1, r);
    prf("¯");
    arxy(c + ww - 2, r);
    prf("®");
    outprf(usrnum);
}

VOID clrarrows(SHORT r, SHORT c, SHORT ww)
{
    arxy(c + 1, r);
    prf(" ");
    arxy(c + ww - 2, r);
    prf(" ");
    outprf(usrnum);
}

/*
   r,c is top left corner of box CHAR
   cnt is # of objs
   rstt is return state
*/

VOID ansimenu(SHORT r, SHORT c, SHORT ww, SHORT cnt, CHAR* cmstr, SHORT rstt, SHORT msgno)
{

    switch (msgno) {
        case -2: break;
        default: prfmsg(msgno);
            outprf(usrnum);
            break;
    }
    zvda->rstate = rstt;
    zvda->mnumax = cnt;
    zvda->mnupos = 1;
    zvda->mnurow = r;
    zvda->mnucol = c;
    zvda->mnuwid = ww;
    stzcpy(zvda->mnustr, cmstr, 30);
    drawarrows(r + 3, c, ww);
    usrptr->substt = ANSMENU;
}

VOID initrnd(VOID)                 /* initialize random number seed        */
{
#ifdef __BUILDV10MODULE  
    srand((unsigned)time(NULL)); // BBSV10
#else
    randomize(); // WG32, MBBS6/WG1/WG2
#endif
}

INT getrnd(INT lo, INT hi)         /* Returns random # between lo and hi   */
{
    if ((hi < 0) || (lo < 0)) {
        return(0);
    }

    if (hi < lo) {
        INT tmp = lo;
        lo = hi;
        hi = tmp;
    }

    if (hi == lo) {
        return lo;
    }

#ifdef __BUILDV10MODULE
    return(lo + rand() % (hi - lo + 1)); // BBSV10
#else
    return (random(hi - lo + 1) + lo); //WG32, MBBS6/WG1/WG2
#endif
}

#ifdef __BUILDV10MODULE
INT random(INT hi)
{
    if (hi <= 0) {
        return 0;
    }
    return getrnd(0, hi - 1); // replicate the behavior of Borland's random(int hi); 
}

VOID randomize(VOID)
{
    initrnd(); // just a stub for the old borland seeding function
}
#endif
