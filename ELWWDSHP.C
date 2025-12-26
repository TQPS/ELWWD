/*****************************************************************************
 *   ELWWDSHP.C   V0.62                                 Worlds of Darkness   *
 *   Shop Routines                                                           *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 01/29/1995         *
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
#include "elwwdrfx.h"

VOID tavinit(VOID)
{
    prfmsg(TAVERN);
    outprf(usrnum);
    zvda->clrbonk = bonk = zvda->redraw = FALSE;
    zvda->mstate = 0;
    ansimenu(1, 48, 27, 5, "EDPCX", 43, TAVMENU1);
}

VOID tavproc(VOID)
{
    static USHORT fdp[] = { 5,7,10,15,20,25,50 },
        drkp[] = { 1,10,15,25,40,100,150 }, i,
        fdpr[] = { 3,4,6,8,11,13,26 },
        drkh[] = { 1,6,7,13,21,31,41 },
        drka[] = { 0,3,5,15,20,25,30 };

    switch (zvda->mstate) {
        case 0: switch (zvda->mnukey) {
            case 1: zvda->mstate = 1;
                ansimenu(1, 48, 27, 8, "ABCDEFGN", 43, FUDMNU);
                break;
            case 2: zvda->mstate = 2;
                ansimenu(1, 48, 27, 8, "ABCDEFGN", 43, DRKMNU);
                break;
            case 3: usrptr->substt = 44;
                prfmsg(OFFPTY);
                outprf(usrnum);
                break;
            case 4: ansimenu(1, 48, 27, 5, "EDPCX", 43, NOCASI);
                break;
            case 5: restplay();
                break;
            default: ansimenu(1, 48, 27, 5, "EDPCX", 43, TAVMENU1);
        }
              break;
              /* food menu */
        case 1: zvda->mnukey--;
            if (zvda->mnukey < 7) {
                if (zplyr->cash >= fdp[zvda->mnukey]) {
                    zplyr->cash -= fdp[zvda->mnukey];
                    i = (USHORT)random(fdpr[zvda->mnukey]) + 1;
                    if (zplyr->currhp + i > zplyr->maxhp)
                        zplyr->currhp = zplyr->maxhp;
                    else
                        zplyr->currhp += (CHAR)i;
                    prfmsg(MMMMM);
                    outprf(usrnum);
                    ansimenu(1, 48, 27, 8, "ABCDEFGN", 43, FUDMNU);
                } else {
                    prfmsg(NUFMN);
                    outprf(usrnum);
                    ansimenu(1, 48, 27, 8, "ABCDEFGN", 43, FUDMNU);
                }
            } else {
                delbox(1, 48, 8);
                prfmsg(TAVMENU1);
                prfmsg(WBLLN);
                outprf(usrnum);
                ansimenu(1, 48, 27, 5, "EDPCX", 43, TAVMENU1);
                zvda->mstate = 0;
            }
            break;
            /* booze menu */
        case 2: zvda->mnukey--;
            if (zvda->mnukey < 7) {
                if (zplyr->cash >= drkp[zvda->mnukey]) {
                    zplyr->cash -= drkp[zvda->mnukey];
                    i = (USHORT)random(drkh[zvda->mnukey]) + 1;
                    if (zplyr->currhp + i > zplyr->maxhp)
                        zplyr->currhp = zplyr->maxhp;
                    else
                        zplyr->currhp += (CHAR)i;
                    if (drka[zvda->mnukey] > 0)
                        i = (USHORT)(random(drka[zvda->mnukey]) + 1 + zplyr->condition[0]);
                    else
                        i = 0;
                    if (i > 250)
                        zplyr->condition[0] = 250;
                    else {
                        if (i > 0)
                            zplyr->condition[0] = (CHAR)i;
                    }
                    prfmsg(GLUG);
                    outprf(usrnum);
                    ansimenu(1, 48, 27, 8, "ABCDEFGN", 43, DRKMNU);
                } else {
                    prfmsg(NUFMN);
                    outprf(usrnum);
                    ansimenu(1, 48, 27, 8, "ABCDEFGN", 43, DRKMNU);
                }
            } else {
                delbox(1, 48, 8);
                prfmsg(TAVMENU1);
                prfmsg(WBLLN);
                outprf(usrnum);
                ansimenu(1, 48, 27, 5, "EDPCX", 43, TAVMENU1);
                zvda->mstate = 0;
            }
            break;
        default: restplay();
    }
}

VOID arenaproc(VOID)
{
    CHAR kky;
    SHORT cbnum;
    USHORT i, l, m;
    ULONG j, k;
    switch (zvda->mstate) {
        case 0: kky = getinput();
            if (kky) {
                prfmsg(ABLLN);
                outprf(usrnum);
                switch (kky) {
                    case 'F': prfmsg(WBLLN);
                        prfmsg(ARNL2);
                        outprf(usrnum);
                        zvda->mstate = 1;
                        getanum(42);
                        break;
                    case 'L': restplay();
                }
            }
            break;
        case 1: if (zvda->lastnum > 0 && zvda->lastnum < 16) {
            prfmsg(WBLLN);
            prfmsg(ARNL3);
            outprf(usrnum);
            zvda->mstate = 2;
            zvda->lastcost = zvda->lastnum;
            getanum(42);
        } else {
            prfmsg(ARNL1);
            outprf(usrnum);
            zvda->mstate = 0;
        }
              break;
        case 2: if (zvda->lastnum > 0 && zvda->lastnum < 11) {
            cbnum = getcbr();
            if (cbnum != nterms) {
                zcbr->entype = 'm';
                k = zvda->lastcost;          //lvl of crits
                j = zvda->lastnum;           //# of crits
                if (k < 1)
                    k = 1;
                if (j < 1)
                    j = 1;
                zcbr->mcount = (SHORT)j;
                for (i = 0; i < totmonst; i++)
                    if ((int)(unsigned char)monbase[i].monlvl == (int)k)
                        break;
                if (i < totmonst) {
                    l = i = 0;
                    m = 1;
                    dfaSetBlk(dbmonst);
                    do {
                        if ((int)(unsigned char)monbase[i].monlvl == (int)k) {
                            dfaGetAbs(&zcbr->cmonst[l], monbase[i].monpos, 0);
                            zcbr->mxlife[l] = zcbr->cmonst[l].hp;
                            zcbr->omony[l] = zcbr->mony[l] = 2;
                            zcbr->omonx[l] = zcbr->monx[l] = (CHAR)m;
                            zcbr->uatak[l] = 0;
                            zcbr->umov[l] = 0;
                            m += 2;
                            l++;
                        }
                        i++;
                        if (i >= totmonst)
                            i = 0;
                    } while (l < j && l < 10);
                    dfaRstBlk();
                    setfight((SHORT)usrnum, cbnum);
                    zcbr->xitx = 18;
                    zcbr->xity = 1;
                    zcbr->plx[0] = 1;
                    zcbr->ply[0] = 7;
                    zcbr->curmn = zcbr->wfor = 0;
                    zcbr->redf = TRUE;
                } else {
                    prfmsg(ARNOPP);
                    prfmsg(ARNL1);
                    outprf(usrnum);
                    zvda->mstate = 0;
                }
            } else {
                prfmsg(ARNFUL);
                prfmsg(ARNL1);
                outprf(usrnum);
                zvda->mstate = 0;
            }
        } else {
            prfmsg(ARNL1);
            outprf(usrnum);
            zvda->mstate = 0;
        }
              break;

    }
}

VOID arenainit(VOID)
{
    prfmsg(ARENA);
    prfmsg(ARNL1);
    outprf(usrnum);
    zvda->redraw = FALSE;
    bonk = FALSE;
    zvda->clrbonk = FALSE;
    zvda->mstate = 0;
    usrptr->substt = 42;
}

VOID bankinit(VOID)
{
    prfmsg(BANK);
    outprf(usrnum);
    prfmsg(URBAL, l2as(zplyr->bank));
    outprf(usrnum);
    zvda->redraw = FALSE;
    bonk = FALSE;
    zvda->clrbonk = FALSE;
    zvda->mstate = 0;
    ansimenu(1, 48, 27, 6, "IDWLRX", 41, BNKMNU1);
}

VOID bankproc(VOID)
{
    ULONG tworth, lnval;
    USHORT i;
    SHORT aloan = FALSE;

    switch (zvda->mstate) {
        case 0: switch (zvda->mnukey) {                  //pick an action
            case 1: if (zplyr->bank == 0) {          //Invest
                prfmsg(WBLLN);
                prfmsg(NOMINV);
                outprf(usrnum);
                //                  ansimenu(1,48,27,6,"IDWLRX",41);
            } else {
                prfmsg(WBLLN);
                prfmsg(NOINVC);
                outprf(usrnum);
            }
                  ansimenu(1, 48, 27, 6, "IDWLRX", 41, BNKMNU1);
                  break;
            case 2: if (zplyr->cash == 0) {          //Deposit
                prfmsg(WBLLN);
                prfmsg(NOMDEP);
                outprf(usrnum);
                ansimenu(1, 48, 27, 6, "IDWLRX", 41, BNKMNU1);
            } else {
                prfmsg(WBLLN);
                prfmsg(DEPHOW, l2as(zplyr->cash));
                outprf(usrnum);
                zvda->mstate = 1;
                getanum(41);
            }
                  break;
            case 3: if (zplyr->bank == 0) {          //Withdraw
                prfmsg(WBLLN);
                prfmsg(NOMWIT);
                outprf(usrnum);
                if (zvda->rip) prfmsg(BNKMNU1);
                ansimenu(1, 48, 27, 6, "IDWLRX", 41, BNKMNU1);
            } else {
                prfmsg(WBLLN);
                prfmsg(WITHOW, l2as(zplyr->bank));
                outprf(usrnum);
                zvda->mstate = 2;
                getanum(41);
            }
                  break;
            case 4: if (zplyr->loan) {             //Loan
                prfmsg(WBLLN);
                prfmsg(NOLOAN);
                outprf(usrnum);
                ansimenu(1, 48, 27, 6, "IDWLRX", 41, BNKMNU1);
            } else {
                tworth = zplyr->cash + zplyr->bank;
                for (i = 0; i < MAXPOBJC; i++)
                    if (zvda->pstuff[i].objname[0] != 0)
                        tworth += zvda->pstuff[i].ocost;
                if (tworth < 500)
                    lnval = 50L;
                else {
                    if (zplyr->condition[20] > 1)
                        lnval = tworth / zplyr->condition[20];
                    else
                        lnval = tworth;
                }
                prfmsg(WBLLN);
                outprf(usrnum);
                prfmsg(TERMS);
                prfmsg(PIKTERM, l2as(lnval));
                outprf(usrnum);
                zvda->lastnum = lnval;
                zvda->mstate = 3;
                ansimenu(1, 48, 27, 4, "ABCN", 41, -2);
            }
                  break;
            case 5: if (zplyr->loan == 0) {          //Repay Loan
                prfmsg(WBLLN);
                prfmsg(NOPAY);
                outprf(usrnum);
            } else {
                lnval = zplyr->loan + zplyr->intrest;
                if (zplyr->cash >= lnval ||
                    zplyr->bank >= lnval) {
                    if (zplyr->bank >= lnval)
                        zplyr->bank -= lnval;
                    else
                        zplyr->cash -= lnval;
                    zplyr->loan = zplyr->intrest = 0;
                    zplyr->condition[21] = zplyr->condition[22] = zplyr->condition[23] = 0;
                    prfmsg(WBLLN);
                    prfmsg(LREPY);
                    outprf(usrnum);
                } else {
                    prfmsg(WBLLN);
                    prfmsg(NORESV);
                    outprf(usrnum);
                }
            }
                  ansimenu(1, 48, 27, 6, "IDWLRX", 41, BNKMNU1);
                  break;
            case 6: restplay();                    //Exit
        }
              break;
        case 1: if (zvda->lastnum > 0) {
            if (zvda->lastnum > zplyr->cash)
                zvda->lastnum = zplyr->cash;
            zplyr->cash -= zvda->lastnum;
            zplyr->bank += zvda->lastnum;
        }
              prfmsg(WBLLN);
              prfmsg(URBAL, l2as(zplyr->bank));
              outprf(usrnum);
              zvda->mstate = 0;
              ansimenu(1, 48, 27, 6, "IDWLRX", 41, BNKMNU1);
              break;
        case 2: if (zvda->lastnum > 0) {
            if (zvda->lastnum > zplyr->bank)
                zvda->lastnum = zplyr->bank;
            zplyr->cash += zvda->lastnum;
            zplyr->bank -= zvda->lastnum;
        }
              prfmsg(WBLLN);
              prfmsg(URBAL, l2as(zplyr->bank));
              outprf(usrnum);
              zvda->mstate = 0;
              ansimenu(1, 48, 27, 6, "IDWLRX", 41, BNKMNU1);
              break;
        case 3: switch (zvda->mnukey) {                  //pick a term
            case 1: zplyr->condition[21] = 5;
                zplyr->condition[22] = 10;
                zplyr->condition[23] = 0;
                aloan = TRUE;
                break;
            case 2: zplyr->condition[21] = 10;
                zplyr->condition[22] = 20;
                zplyr->condition[23] = 0;
                aloan = TRUE;
                break;
            case 3: zplyr->condition[21] = 15;
                zplyr->condition[22] = 30;
                zplyr->condition[23] = 0;
                aloan = TRUE;
                break;
        }
              if (aloan) {
                  zplyr->bank += zvda->lastnum;
                  zplyr->loan = zvda->lastnum;
                  zplyr->intrest = zplyr->loan * 100 / zplyr->condition[21] / 100;
                  if (zplyr->intrest == 0)
                      zplyr->intrest++;
                  prfmsg(WBLLN);
                  prfmsg(NEWBAL, l2as(zplyr->bank), l2as(zplyr->loan + zplyr->intrest));
                  outprf(usrnum);
              } else {
                  prfmsg(WBLLN);
                  prfmsg(URBAL, l2as(zplyr->bank));
                  outprf(usrnum);
              }
              zvda->mstate = 0;
              ansimenu(1, 48, 27, 6, "IDWLRX", 41, BNKMNU1);
              break;
    }
}

VOID findshop(VOID)
{

    switch (zmap->lvl[plevel].map[prow][pcol]) {
        //case 'B': warguildinit();
        //          break;
        case 'A': if (!ptest()) {
            if (zvda->rip) {
                prfmsg(RIPCLR);
                outprf(usrnum);
            }
            bankinit();
        } else {
            prfmsg(WBLLN);
            prfmsg(NOENT);
            outprf(usrnum);
            zvda->clrbonk = TRUE;
        }
                break;
        case 'C': if (!ptest()) {
            if (zvda->rip) {
                prfmsg(RIPCLR);
                outprf(usrnum);
            }
            wizguildinit();
        } else {
            prfmsg(WBLLN);
            prfmsg(NOENT);
            outprf(usrnum);
            zvda->clrbonk = TRUE;
        }
                break;
        case 'D': if (!ptest()) {
            if (zvda->rip) {
                prfmsg(RIPCLR);
                outprf(usrnum);
            }
            clerguildinit();
        } else {
            prfmsg(WBLLN);
            prfmsg(NOENT);
            outprf(usrnum);
            zvda->clrbonk = TRUE;
        }
                break;
        case 'G': if (!ptest()) {
            if (zvda->rip) {
                prfmsg(RIPCLR);
                outprf(usrnum);
            }
            inninit();
        } else {
            prfmsg(WBLLN);
            prfmsg(NOENT);
            outprf(usrnum);
            zvda->clrbonk = TRUE;
        }
                break;
        case 'H': if (!ptest()) {
            if (zvda->rip) {
                prfmsg(RIPCLR);
                outprf(usrnum);
            }
            tavinit();
        } else {
            prfmsg(WBLLN);
            prfmsg(NOENT);
            outprf(usrnum);
            zvda->clrbonk = TRUE;
        }
                break;
        case 'J': if (!ptest()) {
            if (zvda->rip) {
                prfmsg(RIPCLR);
                outprf(usrnum);
            }
            wepshopinit();
        } else {
            prfmsg(WBLLN);
            prfmsg(NOENT);
            outprf(usrnum);
            zvda->clrbonk = TRUE;
        }
                break;
                //case 'P': palaceinit();
                //          break;
        case 'Q': if (!ptest()) {
            if (zvda->rip) {
                prfmsg(RIPCLR);
                outprf(usrnum);
            }
            arenainit();
        } else {
            prfmsg(WBLLN);
            prfmsg(NOENT);
            outprf(usrnum);
            zvda->clrbonk = TRUE;
        }
                break;
        case 'W': if (zvda->party == usrnum)
            uplevel();
            break;
        case 'X': if (zvda->party == usrnum)
            downlevel();
            break;
        case '%': if (zvda->party == usrnum)
            spinme();
            break;
    }
}

VOID wslist(SHORT wselt)
{
    USHORT i;
    CHAR usable;

    if (!zvda->rip) {
        prfmsg(SSEL);
        outprf(usrnum);
        for (i = 0; i < 15; i++) {
            arxy(45, i + 4);
            if (!wselt) {
                if (zvda->pclass.objects[zwep[zvda->cshop].wobj[i].oclass])
                    prf("[1;32m");
                else
                    prf("[1;31m");
                prf("%s", zwep[zvda->cshop].wobj[i].objname);
                outprf(usrnum);
                arxy(68, i + 4);
                prf("[0m%s", l2as(zwep[zvda->cshop].wobj[i].ocost));
                outprf(usrnum);
            } else {
                if (zvda->pclass.objects[zwep[zvda->cshop].aobj[i].oclass])
                    prf("[1;32m");
                else
                    prf("[1;31m");
                prf("%s", zwep[zvda->cshop].aobj[i].objname);
                outprf(usrnum);
                arxy(68, i + 4);
                prf("%s[0m", l2as(zwep[zvda->cshop].aobj[i].ocost));
                outprf(usrnum);
            }
        }
    } else {
        if (!wselt) {
            strcpy(zvda->query, spr("((*Weapon Selection  PP On Hand %s::", l2as(zplyr->cash)));
            for (i = 0; i < 15; i++) {
                if (zvda->pclass.objects[zwep[zvda->cshop].wobj[i].oclass])
                    usable = '+';
                else
                    usable = '-';
                strcat(zvda->query, spr("%c@%c%-20.20s %spp,", 65 + i, usable,
                    zwep[zvda->cshop].wobj[i].objname,
                    l2as(zwep[zvda->cshop].wobj[i].ocost)));
            }
            strcat(zvda->query, "P@Nothing Thanks))");
        } else {
            strcpy(zvda->query, spr("((*Armor Selection  PP On Hand %s::", l2as(zplyr->cash)));
            for (i = 0; i < 15; i++) {
                if (zvda->pclass.objects[zwep[zvda->cshop].aobj[i].oclass])
                    usable = '+';
                else
                    usable = '-';
                strcat(zvda->query, spr("%c@%c%-20.20s %s,", 65 + i, usable,
                    zwep[zvda->cshop].aobj[i].objname,
                    l2as(zwep[zvda->cshop].aobj[i].ocost)));
            }
            strcat(zvda->query, "P@Nothing Thanks))");
        }
    }
}

VOID wepshop(VOID)
{
    CHAR wsel = 0;
    USHORT j,
        pnc[3] = { 2,1,1 };
    ULONG i, icost;
    static CHAR* pns[3] = { "Arrows","Darts","Rocks" };
    switch (zvda->mstate) {
        case 0: prfmsg(WBLLN);
            outprf(usrnum);
            switch (zvda->mnukey) {  //AWPSL
                case 1: wsel = 1;
                case 2: if (zwepcnt) {
                    delinm();
                    for (i = 0; i < zwepcnt; i++) {
                        if (plevel == zwep[i].stlevel &&
                            prow == zwep[i].strow &&
                            pcol == zwep[i].stcol)
                            break;
                    }
                    if (i < zwepcnt) {
                        zvda->cshop = (SHORT)i; // RH: Generally bad to cast a long to a short but he's using it as an iterator ... SMH
                        zvda->cstype = wsel;
                        wslist(wsel);
                        if (zvda->rip) rip_query(0, 0, zvda->query);
                        else {
                            arxy(1, 22);
                            prfmsg(MONHND, l2as(zplyr->cash));
                            arxy(1, 24);
                            prfmsg(ENTSEL);
                            outprf(usrnum);
                        }
                        zvda->mstate = 1;
                        ansimenu(1, 43, 36, 16, "ABCDEFGHIJKLMNOP", 40, -2);
                    } else {
                        prf("Wshop NF");
                        outprf(usrnum);
                        ansimenu(1, 48, 27, 5, "AWPSL", 40, WPNMENU);
                    }
                } else ansimenu(1, 48, 27, 5, "AWPSL", 40, WPNMENU);
                      break;
                case 3: ansimenu(1, 48, 27, 4, "ADRN", 40, PRJMENU);
                    zvda->mstate = 6;
                    break;
                case 4: j = 0;
                    for (i = 0; i < MAXPOBJC; i++) {
                        zvda->mnuslt[i] = 0;
                        if (zvda->pstuff[i].objname[0] != 0 &&
                            (zplyr->equip[i] == 0 || zvda->pstuff[i].osp != 11) &&
                            (zvda->pstuff[i].otype == 0 ||
                                zvda->pstuff[i].otype == 1)) {
                            j++;
                            zvda->mnuslt[i] = 1;
                        }
                    }
                    if (j) {
                        zvda->mstate = 3;
                        pagemenu(40, j, TRUE);
                    } else {
                        zvda->mstate = 0;
                        ansimenu(1, 48, 27, 5, "AWPSL", 40, WPNMENU);
                    }
                    break;
                default: restplay();
            }
            break;
        case 1: zvda->mnukey--;
            if (zvda->mnukey < 15) {
                arxy(1, 22);
                prf("                                                                 ");
                arxy(1, 24);
                prf("                                                                 ");
                outprf(usrnum);
                arxy(1, 23);
                prf("                                                                 ");
                arxy(1, 22);
                outprf(usrnum);
                if (!zvda->cstype)
                    prfmsg(UWANT, zwep[zvda->cshop].wobj[zvda->mnukey].objname, l2as(zwep[zvda->cshop].wobj[zvda->mnukey].ocost));
                else
                    prfmsg(UWANT, zwep[zvda->cshop].aobj[zvda->mnukey].objname, l2as(zwep[zvda->cshop].aobj[zvda->mnukey].ocost));
                if (!zvda->rip) {
                    arxy(1, 24);
                    prfmsg(ISRITE);
                    outprf(usrnum);
                }
                zvda->mstate = 2;
                zvda->mlkey = zvda->mnukey;
                getyno(40);
            } else {
                delbox(1, 41, 16);
                arxy(1, 22);
                prf("                                                                 ");
                arxy(1, 24);
                prf("                                                                 ");
                outprf(usrnum);
                zvda->mstate = 0;
                // row/col/width/#items/cmchars/rstate
                ansimenu(1, 48, 27, 5, "AWPSL", 40, WPNMENU);
            }
            break;
        case 2: if (zvda->mnukey == 'Y') {
            arxy(1, 22);
            prf("                                                                 ");
            arxy(1, 24);
            prf("                                                                 ");
            arxy(1, 24);
            outprf(usrnum);
            if (!zvda->cstype)
                icost = zwep[zvda->cshop].wobj[zvda->mlkey].ocost;
            else
                icost = zwep[zvda->cshop].aobj[zvda->mlkey].ocost;
            if (zplyr->cash >= icost) {
                for (i = 0; i < MAXPOBJC; i++)
                    if (zvda->pstuff[i].objname[0] == 0)
                        break;
                if (i < MAXPOBJC) {
                    zplyr->cash -= icost;
                    zplyr->equip[i] = 0;
                    if (!zvda->cstype)
                        zvda->pstuff[i] = zwep[zvda->cshop].wobj[zvda->mlkey];
                    else
                        zvda->pstuff[i] = zwep[zvda->cshop].aobj[zvda->mlkey];
                } else {
                    arxy(1, 22);
                    prf("                                                                 ");
                    arxy(1, 24);
                    prf("                                                                 ");
                    arxy(1, 23);
                    prf("                                                                 ");
                    arxy(1, 23);
                    prfmsg(NOROOM);
                }
            }
        }
              arxy(1, 22);
              prf("                                                                 ");
              if (zvda->rip) rip_query(0, 0, zvda->query);
              else {
                  arxy(1, 22);
                  outprf(usrnum);
                  prfmsg(MONHND, l2as(zplyr->cash));
                  arxy(1, 24);
                  prfmsg(ENTSEL);
                  outprf(usrnum);
              }
              zvda->mstate = 1;
              ansimenu(1, 43, 36, 16, "ABCDEFGHIJKLMNOP", 40, -2);
              break;
        case 3: if (zvda->mnukey) {
            zvda->mnukey--;
            arxy(1, 15);
            if (zvda->pstuff[zvda->mnukey].ocost == 0)
                zvda->pstuff[zvda->mnukey].ocost = 500;
            prfmsg(SELLIT, zvda->pstuff[zvda->mnukey].objname, l2as(zvda->pstuff[zvda->mnukey].ocost / 2));
            outprf(usrnum);
            zvda->mstate = 4;
            zvda->uxitk = zvda->mnukey;
            getyno(40);
        } else {
            delinm();
            zvda->mstate = 0;
            ansimenu(1, 48, 27, 5, "AWPSL", 40, WPNMENU);
        }
              break;
        case 4: if (zvda->mnukey == 'Y') {
            arxy(1, 15);
            prfmsg(SOLD, zvda->pstuff[zvda->uxitk].objname);
            zvda->pstuff[zvda->uxitk].objname[0] = 0;
            zplyr->cash += (zvda->pstuff[zvda->uxitk].ocost >> 1);
            prfmsg(ANYKEY);
            outprf(usrnum);
            usrptr->substt = 24;
            zvda->mstate = 5;
            zvda->rstate = 40;
        } else {
            zvda->mstate = 0;
            delinm();
            if (zvda->mnupage == 0)
                itlist(0);
            else
                itlist(1);
        }
              break;
        case 5: j = 0;
            for (i = 0; i < MAXPOBJC; i++) {
                zvda->mnuslt[i] = 0;
                if (zvda->pstuff[i].objname[0] != 0 &&
                    (zvda->pstuff[i].otype == 0 ||
                        zvda->pstuff[i].otype == 1)) {
                    j++;
                    zvda->mnuslt[i] = 1;
                }
            }
            if (j) {
                zvda->mstate = 3;
                pagemenu(40, j, TRUE);
            } else {
                zvda->mstate = 0;
                delbox(1, 48, 15);
                ansimenu(1, 48, 27, 5, "AWPSL", 40, WPNMENU);
            }
            break;
        case 6: zvda->mnukey--;
            if (zvda->mnukey < 3) {

                prfmsg(HWMPRJ, pns[zvda->mnukey], pnc[zvda->mnukey]);
                outprf(usrnum);
                zvda->obn = zvda->mnukey;
                zvda->mstate = 7;
                getanum(40);
            } else {
                zvda->mstate = 0;
                ansimenu(1, 48, 27, 5, "AWPSL", 40, WPNMENU);
            }
            break;
        case 7: if (zvda->lastnum > 0) {
            if (zvda->lastnum > 250L)
                i = 250;
            else
                i = zvda->lastnum;
            j = 0; // RH: initialize it to something....
            switch (zvda->obn) {
                case 0: j = zplyr->arrows;
                    break;
                case 1: j = zplyr->darts;
                    break;
                case 2: j = zplyr->rocks;
            }
            if ((i + j) > 500) {
                prfmsg(WBLLN);
                prfmsg(TMYPRJ);
                outprf(usrnum);
            } else {
                icost = zvda->lastnum * pnc[zvda->obn];
                if (icost > zplyr->cash) {
                    prfmsg(WBLLN);
                    prfmsg(PRJMNY);
                    outprf(usrnum);
                } else {
                    zplyr->cash -= icost;
                    switch (zvda->obn) {
                        case 0: zplyr->arrows += (SHORT)zvda->lastnum; // RH: This is risky... why are we using such small types on these structs?
                            break;
                        case 1: zplyr->darts += (SHORT)zvda->lastnum; // RH: This is risky...
                            break;
                        case 2: zplyr->rocks += (SHORT)zvda->lastnum; // RH: This is risky... 
                    }
                    prfmsg(WBLLN);
                    prfmsg(TGKPRJ);
                    outprf(usrnum);
                }
            }
        }
              zvda->mstate = 0;
              ansimenu(1, 48, 27, 5, "AWPSL", 40, WPNMENU);
              break;
    }
}

VOID wepshopinit(VOID)
{

    prfmsg(WPNSHOP);
    outprf(usrnum);
    zvda->redraw = FALSE;
    bonk = FALSE;
    zvda->clrbonk = FALSE;
    zvda->mstate = 0;
    // row/col/width/#items/cmchars/rstate
    ansimenu(1, 48, 27, 5, "AWPSL", 40, WPNMENU);
}

VOID wepkick(VOID)
{
    USHORT i, j, k, l, picked[15] = { 0 }, lc;

    if (cantrun)
        return;
    for (i = 0; i < zwepcnt; i++) {
        zwep[i].wpncnt = 0;
        zwep[i].armcnt = 0;
        /* Pick Weapons */
        if (objcnt[0] > 0) {
            if (objcnt[0] < 20) {
                if (objcnt[0] < 15)
                    k = objcnt[0];
                else
                    k = 15;
                zwep[i].wpncnt = 0;
                for (j = 0; j < k; j++)
                    if (wepbase[j].owho == 0) {
                        zwep[i].wobj[j] = wepbase[j];
                        zwep[i].wpncnt++;
                    }
            } else {
                for (l = 0; l < 15; l++)
                    picked[l] = MAXOBJ + 1;
                l = (USHORT)random(objcnt[0]);
                zwep[i].wobj[0] = wepbase[l];
                picked[0] = l;
                j = 1;
                lc = 0;
                while (j < 15) {
                    l = (USHORT)random(objcnt[0]);
                    lc++;
                    for (k = 0; k < j; k++)
                        if (picked[k] == l || wepbase[l].owho != 0)
                            break;
                    if (lc > 500)
                        k = j;
                    if (k == j) {
                        zwep[i].wobj[j] = wepbase[l];
                        picked[j] = l;
                        j++;
                    }
                }
                zwep[i].wpncnt = 15;
            }
        }

        /* Pick Armour */
        if (objcnt[1] > 0) {
            if (objcnt[1] < 15) {
                for (j = 0; j < objcnt[1]; j++)
                    zwep[i].aobj[j] = armbase[j];
                zwep[i].armcnt = objcnt[1];
            } else {
                for (l = 0; l < 15; l++)
                    picked[l] = MAXOBJ + 1;
                l = (USHORT)random(objcnt[1]);
                zwep[i].aobj[0] = armbase[l];
                picked[0] = l;
                j = 1;
                while (j < 15) {
                    l = (USHORT)random(objcnt[1]);
                    for (k = 0; k < j; k++)
                        if (picked[k] == l)
                            break;
                    if (k == j) {
                        zwep[i].aobj[j] = armbase[l];
                        picked[j] = l;
                        j++;
                    }
                }
                zwep[i].armcnt = 15;
            }
        }

    }
    if (!cantrun)
        rtkick(3600, wepkick);
}

VOID initweps(VOID)
{
    CHAR i, j, k;

    zwepcnt = 0;
    for (i = 1; i <= ACTLEVELS; i++)
        for (j = 1; j <= MAPHEIGHT; j++)
            for (k = 1; k <= MAPWIDTH; k++)
                if (zmap->lvl[i].map[j][k] == 'J') {
                    zwep[zwepcnt].stlevel = i;
                    zwep[zwepcnt].strow = j;
                    zwep[zwepcnt].stcol = k;
                    zwepcnt++;
                }
}
