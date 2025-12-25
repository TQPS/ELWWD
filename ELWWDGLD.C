/*****************************************************************************
 *   ELWWDGLD.C   V0.62                                 Worlds of Darkness   *
 *   Guild Routines                                                          *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 02/03/1995         *
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

SHORT lspells(CHAR stty, CHAR kky, SHORT rstt)
{
    USHORT i, lsp = 0, j;
    STORE* tstor;
    CHAR pl, itstr[17] = { 0 }, nstr[24] = { 0 };
    SHORT rc = FALSE, match, k;

    tstor = (stty == 'w') ? &zwiz[zvda->cshop] : &zcler[zvda->cshop]; // RH: This was originally inside the if stty is w or c, but I moved it outside to avoid C4701

    if ((stty == 'w') || (stty == 'c')) {
        pl = kky + 1;

        for (i = 0; i < tstor->stospcnt; i++)
            if (tstor->stspells[i].level == pl) {
                match = FALSE;
                for (j = 0; j < 5; j++) {
                    if (stty == 'w') {
                        k = zplyr->mage[(9 - pl) * 5 + j];
                        //                        arxy(1,j+10);
                        //                        prf("chkkslot %u %u for %u",(pl-1)*5,j,k);
                        //                        outprf(usrnum);
                        if (k != NOTFOUND)
                            if (sameas(tstor->stspells[i].spellname, wizspell[k].spellname))
                                match = TRUE;
                        //                         else {
                        //                          arxy(1,j+1);
                        //                          prf("'%s' nm '%s'",tstor->stspells[i].spellname,wizspell[k].spellname);
                        //                          outprf(usrnum);
                        //                         }
                    } else {
                        // stty == 'c'!
                        k = zplyr->cleric[(9 - pl) * 5 + j];
                        if (k != NOTFOUND)
                            if (sameas(tstor->stspells[i].spellname, clerspell[k].spellname))
                                match = TRUE;

                    }
                    if (match)
                        break;
                }
                if (!match) {
                    zvda->mnuslt[lsp] = (CHAR)i;
                    lsp++;
                }
            }
    }

    if (lsp) {
        //pl=8-kky;
        prfmsg(PIKSPEL);
        outprf(usrnum);
        for (i = 0; i < lsp; i++) {
            arxy(48, i + 4);
            itstr[i] = (CHAR)'A' + (CHAR)i;
            prf("[0;1;41mº[0m [1;33;40m%c[37;41m [40m [32m", itstr[i]);
            stzcpy(nstr, tstor->stspells[zvda->mnuslt[i]].spellname, 20);
            while (strlen(nstr) < 20)
                strcat(nstr, " ");
            prf(nstr);
            prf(" [1;37m[41mº[0m");
        }
        itstr[i] = (CHAR)'A' + (CHAR)i;
        zvda->litcnt = lsp;
        arxy(48, i + 4);
        prfmsg(PKSPX, itstr[i]);
        outprf(usrnum);
        arxy(48, i + 5);
        prfmsg(PKSPXL);
        outprf(usrnum);
        rc = TRUE;
        ansimenu(1, 48, 27, lsp + 1, itstr, rstt, -2);
    } else {
        if (zvda->gstate == INFITE)
            arxy(1, 13);
        else
            arxy(1, 16);
        prfmsg(NOSPLVL);
        outprf(usrnum);
    }

    return(rc);
}

SHORT askpower(CHAR styp, SHORT rstate)
{
    CHAR itstr[12] = { 0 };
    USHORT i, j, mlvl;
    SHORT rc = FALSE;
    j = 0;
    switch (styp) {
        case 'w': while (j < 9 && zplyr->mage_new[j] == 0) {
            j++;
        }
                break;
        case 'c': while (j < 9 && zplyr->cleric_new[j] == 0) {
            j++;
        }
                break;
    }
    if (j < 9) {
        strcpy(zvda->query, "((*Spell Level Selection::");
        if (!zvda->rip) {
            prfmsg(ALVLH);
            outprf(usrnum);
        }
        mlvl = 9 - j;
        for (i = 0; i < mlvl; i++) {
            if (!zvda->rip) {
                itstr[i] = (CHAR)'A' + (CHAR)i;
                if (!zvda->rip) {
                    arxy(48, i + 4);
                    prfmsg(ALVLL, itstr[i], '1' + i);
                    outprf(usrnum);
                } else strcat(zvda->query, spr("%c@Level %c,", 65 + i, '1' + i));
            }
        }
        itstr[i] = (CHAR)'A' + (CHAR)i;
        strcat(zvda->query, spr("%c@Exit))", 65 + i));
        if (!zvda->rip) {
            arxy(48, i + 4);
            prfmsg(ALVLX, itstr[i]);
            outprf(usrnum);
            arxy(48, i + 5);
            prfmsg(ALVLB);
            outprf(usrnum);
        }
        zvda->litcnt = mlvl;
        ansimenu(1, 48, 27, mlvl + 1, itstr, rstate, -2);
        rc = TRUE;
    } else {
        prfmsg(SPCAP);
        outprf(usrnum);
    }
    return(rc);
}

SHORT chklern(CHAR stty)
{
    USHORT i, k;
    CHAR j;
    SHORT sprc = FALSE, nsp[9] = { 0 };
    STORE* tstor;
    switch (stty) {
        case 'w': tstor = &zwiz[zvda->cshop];
            break;
        case 'c': tstor = &zcler[zvda->cshop];
            break;
        default: return(FALSE);
    }
    for (i = 0; i < 9; i++)
        if (stty == 'w')
            nsp[i] = zplyr->mage_new[i];
        else
            nsp[i] = zplyr->cleric_new[i];
    k = 0;
    for (i = 0; i < 9; i++)
        k += nsp[i];
    if (k > 0) {
        for (i = 0; i < 9; i++)
            for (j = 0; j < 5; j++)
                switch (stty) {
                    case 'w':
                        if (zplyr->mage[i * 5 + j] != NOTFOUND && nsp[i] > 0)
                            nsp[i]--;
                        break;
                    case 'c':
                        if (zplyr->cleric[i * 5 + j] != NOTFOUND && nsp[i] > 0)
                            nsp[i]--;
                }

        for (i = 0; i < tstor->stospcnt; i++) {
            // prf ("%s is lvl %d\n",tstor->stspells[i].spellname,
            //                       tstor->stspells[i].level);
            j = tstor->stspells[i].level;
            if (j < 1 || j>9)
                j = 1;
            else
                j--;
            if (nsp[j] > 0) {
                sprc = TRUE;
                break;
            }
        }
    }
    return(sprc);
}

VOID wizproc(VOID)
{
    USHORT i, j, k, l, m;
    STORE* tstor;
    SHORT gobak = FALSE;

    switch (zvda->mstate) {
        case 0: switch (zvda->mnukey) {
            case 1: if (chklern('w')) {                 //learn spells
                zvda->mstate = 1;
                if (!askpower('w', 130)) {
                    ansimenu(1, 48, 27, 5, "LHISX", 130, WIZM1);
                    zvda->mstate = 0;
                }
            } else {
                prfmsg(NOLERN);
                outprf(usrnum);
                ansimenu(1, 48, 27, 5, "LHISX", 130, WIZM1);
            }
                  break;
            case 4: zvda->mstate = 3;
                ansimenu(1, 48, 27, 3, "SKX", 130, WIZM2);
                break;
            case 2:
            case 3:
            case 5: restplay();                         //exit
                break;
        }
              break;
        case 1: zvda->mnukey--;
            if (zvda->mnukey < zvda->litcnt) {
                k = (9 - zvda->mnukey) * 5;
                for (i = 0; i < 5; i++)
                    if (zplyr->mage[k + i] == NOTFOUND)
                        break;
                if (i < 5) {
                    delbox(1, 48, zvda->litcnt);
                    zvda->mstate = 2;
                    if (!lspells('w', zvda->mnukey, 130)) {
                        delbox(1, 48, zvda->litcnt);
                        zvda->mstate = 1;
                        askpower('w', 130);
                    }
                } else {
                    prfmsg(NOLRNM);
                    outprf(usrnum);
                    zvda->mstate = 1;
                    askpower('w', 130);
                }
            } else {
                delbox(1, 48, zvda->litcnt);
                zvda->mstate = 0;
                ansimenu(1, 48, 27, 5, "LHISX", 130, WIZM1);
            }
            break;
        case 2: zvda->mnukey--;
            tstor = &zwiz[zvda->cshop];
            if (zvda->mnukey < zvda->litcnt) {
                i = zvda->mnuslt[zvda->mnukey];
                //         j=tstor[zvda->cshop].stspells[i].level;
                j = tstor->stspells[i].level;
                if (j > 9 || j < 1) {
                    prfmsg(WZSPLC2, tstor->stspells[i].spellname);
                    outprf(usrnum);
                    j = 9;
                }
                k = (9 - j) * 5;
                for (l = 0; l < 5; l++)
                    if (zplyr->mage[k + l] == NOTFOUND)
                        break;
                if (l < 5) {
                    for (m = 0; m < wspellcnt; m++)
                        if (sameas(tstor->stspells[i].spellname, wizspell[m].spellname))
                            break;
                    if (m < wspellcnt) {
                        zplyr->mage[k + l] = m;
                        prfmsg(WBLLN);
                        prfmsg(LRNSPL, wizspell[m].spellname);
                        //            prf("\n at slot %u %u",k,l);
                        outprf(usrnum);
                    } else {
                        prfmsg(WZSPLC1, tstor->stspells[i].spellname);
                        outprf(usrnum);
                    }
                } else {
                    prfmsg(WZNFSF);
                    outprf(usrnum);
                }
                //         if (!lspells('w',zvda->mnukey,130)) {
                delbox(1, 48, zvda->litcnt);
                zvda->mstate = 1;
                askpower('w', 130);
                //         }
            } else {
                delbox(1, 48, zvda->litcnt);
                zvda->mstate = 0;
                ansimenu(1, 48, 27, 5, "LHISX", 130, WIZM1);
            }
            break;
            /* specials */
        case 3: switch (zvda->mnukey) {
            case 1: if (zplyr->condition[8]) {
                prfmsg(WBLLN);
                prfmsg(UHSENS);
                outprf(usrnum);
            } else {
                if (zplyr->level < 3) {
                    prfmsg(WBLLN);
                    prfmsg(UNHETHS);
                    outprf(usrnum);
                } else {
                    prfmsg(WBLLN);
                    prfmsg(SNSCOST);
                    outprf(usrnum);
                    zvda->mstate = 4;
                    getyno(130);
                }
            }
                  break;
            case 2: if (zplyr->condition[9]) {
                prfmsg(WBLLN);
                prfmsg(UHKNLG);
                outprf(usrnum);
            } else {
                if (zplyr->level < 3) {
                    prfmsg(WBLLN);
                    prfmsg(UNHETHK);
                    outprf(usrnum);
                } else {
                    prfmsg(WBLLN);
                    prfmsg(KNWCOST);
                    outprf(usrnum);
                    zvda->mstate = 5;
                    getyno(130);
                }
            }
                  break;
            default: gobak = TRUE;
        }
              if (gobak) {
                  zvda->mstate = 0;
                  ansimenu(1, 48, 27, 5, "LHISX", 130, WIZM1);
              } else {
                  if (zvda->mstate == 3)
                      ansimenu(1, 48, 27, 3, "SKX", 130, -2);
              }
              break;
        case 4: if (zvda->mnukey == 'Y') {
            if (zplyr->cash > 1000L) {
                prfmsg(WBLLN);
                prfmsg(UNHSENS);
                outprf(usrnum);
                zplyr->condition[8] = TRUE;
                zplyr->cash -= 1000L;
            } else {
                prfmsg(WBLLN);
                prfmsg(SCBWUHM);
                outprf(usrnum);
            }
        }
              zvda->mstate = 3;
              ansimenu(1, 48, 27, 3, "SKX", 130, -2);
              break;
        case 5: if (zvda->mnukey == 'Y') {
            if (zplyr->cash > 5000L) {
                prfmsg(WBLLN);
                prfmsg(UNHKNL);
                outprf(usrnum);
                zplyr->condition[9] = TRUE;
                zplyr->cash -= 5000L;
            } else {
                prfmsg(WBLLN);
                prfmsg(SCBWUHM);
                outprf(usrnum);
            }
        }
              zvda->mstate = 3;
              ansimenu(1, 48, 27, 3, "SKX", 130, -2);
              break;
        default: restplay();
            arxy(1, 16);
            prf("unknown wizard state");
            outprf(usrnum);
    }
}

VOID wizkick(VOID)
{
    USHORT i, picked[15] = { 0 }, j, k;

    if (!cantrun && zwizcnt > 0 && wspellcnt > 0) {
        for (i = 0; i < zwizcnt; i++) {
            if (wspellcnt < 20) {
                for (j = 0; j < 15; j++)
                    zwiz[i].stspells[j] = wizspell[j];
                zwiz[i].stospcnt = 15;
            } else {
                zwiz[i].stospcnt = 0;
                for (j = 0; j < 15; j++)
                    picked[j] = wspellcnt;
                do {
                    j = (USHORT)random(wspellcnt);
                    for (k = 0; k < zwiz[i].stospcnt; k++)
                        if (picked[k] == j)
                            break;
                    if (k == zwiz[i].stospcnt) {
                        picked[zwiz[i].stospcnt] = j;
                        zwiz[i].stspells[zwiz[i].stospcnt] = wizspell[j];
                        zwiz[i].stospcnt++;
                    }
                } while (zwiz[i].stospcnt < 15);
            }
        }
        rtkick(3600, wizkick);
    }
}

VOID initwiz(VOID)
{
    USHORT i, j, k;
    zwizcnt = 0;
    for (i = 1; i <= ACTLEVELS; i++)
        for (j = 1; j <= MAPHEIGHT; j++)
            for (k = 1; k <= MAPWIDTH; k++)
                if (zmap->lvl[i].map[j][k] == 'C') {
                    zwiz[zwizcnt].stlevel = (CHAR)i;
                    zwiz[zwizcnt].strow = (CHAR)j;
                    zwiz[zwizcnt].stcol = (CHAR)k;
                    zwizcnt++;
                }
}

VOID wizguildinit(VOID)
{
    USHORT i;
    for (i = 0; i < zwizcnt; i++) {
        if (plevel == zwiz[i].stlevel &&
            prow == zwiz[i].strow &&
            pcol == zwiz[i].stcol)
            break;
    }
    if (i < zwizcnt) {
        zvda->cshop = i;
        prfmsg(MAGE);
        arxy(1, 15);
        prfmsg(WIZOP1);
        outprf(usrnum);
        zvda->redraw = FALSE;
        bonk = FALSE;
        zvda->clrbonk = FALSE;
        zvda->mstate = 0;
        // row/col/width/#items/cmchars/rstate
        ansimenu(1, 48, 27, 5, "LHISX", 130, WIZM1);
    } else {
        arxy(1, 22);
        prf("WZG LOCATE Error %u %u %u", plevel, prow, pcol);
        outprf(usrnum);
    }
}

VOID storelist(STORE* zstor)
{
    USHORT i;
    CHAR usable;

    if (!zvda->rip) {
        prfmsg(SSEL);
        outprf(usrnum);
        for (i = 0; i < 15; i++) {
            arxy(45, i + 4);
            if (zvda->pclass.objects[zstor->stobj[i].oclass])
                prf("[1;32m");
            else
                prf("[1;31m");
            prf("%s", zstor->stobj[i].objname);
            outprf(usrnum);
            arxy(68, i + 4);
            prf("%s[0m", l2as(zstor->stobj[i].ocost));
            outprf(usrnum);
        }
    } else {
        strcpy(zvda->query, spr("((*Selection List PP On Hand %s::", l2as(zplyr->cash)));
        for (i = 0; i < 15; i++) {
            if (zvda->pclass.objects[zstor->stobj[i].oclass])
                usable = '+';
            else
                usable = '-';
            strcat(zvda->query, spr("%c@%c%-20.20s %spp,", 65 + i, usable,
                zstor->stobj[i].objname,
                l2as(zstor->stobj[i].ocost)));
        }
        strcat(zvda->query, "P@Nothing Thanks))");
    }
}

VOID clerkick(VOID)
{
    USHORT i, j, k, l, picked[15] = { 0 }, lc;
    if (!cantrun && zclercnt > 0 && cspellcnt > 0) {
        for (i = 0; i < zclercnt; i++) {
            zcler[i].stobcnt = 0;
            zcler[i].stospcnt = 0;
            if (objcnt[3] > 0) {
                if (objcnt[3] < 20) {
                    if (objcnt[3] < 15)
                        k = objcnt[3];
                    else
                        k = 15;
                    for (j = 0; j < k; j++)
                        if (potbase[j].owho == 0)
                            zcler[i].stobj[j] = potbase[j];
                    zcler[i].stobcnt = k;
                } else {
                    for (l = 0; l < 15; l++)
                        picked[l] = MAXOBJ + 1;
                    l = (USHORT)random(objcnt[3]);
                    zcler[i].stobj[0] = potbase[l];
                    picked[0] = l;
                    j = 1;
                    lc = 0;
                    while (j < 15) {
                        l = (USHORT)random(objcnt[3]);
                        lc++;
                        for (k = 0; k < j; k++)
                            if (picked[k] == l)
                                break;
                        if (lc > 500)
                            k = j;
                        if (k == j) {
                            zcler[i].stobj[j] = potbase[l];
                            picked[j] = l;
                            j++;
                        }
                    }
                    zcler[i].stobcnt = 15;
                }
            }
        }
        for (i = 0; i < zclercnt; i++) {
            if (cspellcnt < 20) {
                for (j = 0; j < 15; j++)
                    zcler[i].stspells[j] = clerspell[j];
                zcler[i].stospcnt = 15;
            } else {
                zcler[i].stospcnt = 0;
                for (j = 0; j < 15; j++)
                    picked[j] = cspellcnt;
                do {
                    j = (USHORT)random(cspellcnt);
                    for (k = 0; k < zcler[i].stospcnt; k++)
                        if (picked[k] == j)
                            break;
                    if (k == zcler[i].stospcnt) {
                        picked[zcler[i].stospcnt] = j;
                        zcler[i].stspells[zcler[i].stospcnt] = clerspell[j];
                        zcler[i].stospcnt++;
                    }
                } while (zcler[i].stospcnt < 15);
            }
        }
        rtkick(3600, clerkick);
    }
}

VOID initclers(VOID)
{
    USHORT i, j, k;
    zclercnt = 0;
    for (i = 1; i <= ACTLEVELS; i++)
        for (j = 1; j <= MAPHEIGHT; j++)
            for (k = 1; k <= MAPWIDTH; k++)
                if (zmap->lvl[i].map[j][k] == 'D') {
                    zcler[zclercnt].stlevel = (CHAR)i;
                    zcler[zclercnt].strow = (CHAR)j;
                    zcler[zclercnt].stcol = (CHAR)k;
                    zclercnt++;
                }
}

VOID clerguildinit(VOID)
{
    USHORT i;
    for (i = 0; i < zclercnt; i++) {
        if (plevel == zcler[i].stlevel &&
            prow == zcler[i].strow &&
            pcol == zcler[i].stcol)
            break;
    }
    if (i < zclercnt) {
        zvda->cshop = i;
        prfmsg(CLERIC);
        arxy(1, 15);
        prfmsg(CLEROP1);
        outprf(usrnum);
        zvda->redraw = FALSE;
        bonk = FALSE;
        zvda->clrbonk = FALSE;
        zvda->mstate = 0;
        // row/col/width/#items/cmchars/rstate
        ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
    } else {
        arxy(1, 22);
        prf("CLG LOCATE Error %u %u %u", plevel, prow, pcol);
        outprf(usrnum);
    }
}

VOID clerproc(VOID)
{
    USHORT hp, i, j, k, l, m;
    STORE* tstor;
    CHAR nstr[12];
    LONG tcost, cost;

    switch (zvda->mstate) {
        case 0: switch (zvda->mnukey) {
            case 2: delbox(1, 48, 5);    // healing
                delinm();
                prfmsg(HLCOST);
                outprf(usrnum);
                zvda->mstate = 1;
                getyno(110);
                break;
            case 1: if (zclercnt) {    // potion
                delbox(1, 48, 5);
                delinm();
                storelist(&zcler[zvda->cshop]);
                if (!zvda->rip) {
                    arxy(1, 22);
                    prfmsg(MONHND, l2as(zplyr->cash));
                    arxy(1, 24);
                    prfmsg(ENTSEL);
                    outprf(usrnum);
                } else rip_query(0, 0, zvda->query);
                zvda->mstate = 3;
                ansimenu(1, 43, 36, 16, "ABCDEFGHIJKLMNOP", 110, -2);
            } else {
                zvda->mstate = 0;
                ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
            }
                  break;
            case 4: if (chklern('c')) {                 //learn spells
                zvda->mstate = 5;
                if (!askpower('c', 110)) {
                    ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
                    zvda->mstate = 0;
                }
            } else {
                prfmsg(NOLERN);
                outprf(usrnum);
                ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
            }
                  break;
            case 3: zvda->litcnt = 0;     // remove curse
                for (i = 0; i < MAXPOBJC; i++)
                    if (zvda->pstuff[i].objname[0] != 0 &&
                        zplyr->equip[i] == TRUE &&
                        zvda->pstuff[i].osp == 11) {
                        zvda->litcnt++;
                        zvda->mnuslt[i] = (CHAR)i;
                    }
                if (!zvda->litcnt) {
                    prfmsg(NCITR);
                    outprf(usrnum);
                    ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
                } else {
                    tcost = 0;
                    for (i = 0; i < zvda->litcnt; i++) {
                        cost = zvda->pstuff[zvda->mnuslt[i]].ocost;
                        if (cost > 0)
                            cost /= 5;
                        if (cost == 0)
                            cost = 5;
                        tcost += cost;
                    }
                    delinm();
                    prfmsg(CTRCI, l2as(tcost));
                    outprf(usrnum);
                    zvda->mstate = 8;
                    getyno(110);
                }
                break;
            case 5: restplay();        // exit
        }
              break;
        case 1: delinm();
            if (zvda->mnukey == 'Y') {

                scopyc(tempwall, "@02How many hit points do you want @15  []-=> @12 ");
                hp = zplyr->maxhp - zplyr->currhp;
                itoa(hp, nstr, 10);
                insert(nstr, tempwall, 42);
                cvstr(tempwall);
                drawcolor(tempwall);
                zvda->mstate = 2;
                getanum(110);
            } else {
                zvda->mstate = 0;
                arxy(1, 15);
                prfmsg(CLEROP1);
                outprf(usrnum);
                ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
            }
            break;
        case 2: delinm();
            if (margc)
                hp = (USHORT)atoi(margv[0]);
            else
                hp = zplyr->maxhp - zplyr->currhp;
            if (hp > 0)
                if ((USHORT)(hp * 2) > zplyr->cash) {
                    prfmsg(NODOUGH);
                    outprf(usrnum);
                    break;
                } else {
                    zplyr->cash -= hp * 2;
                    i = zplyr->currhp + hp;
                    if (i > 250)
                        i = 250;
                    zplyr->currhp = (CHAR)i;
                    zvda->nstat = TRUE;
                    prfmsg(FEELOK);
                }
            if (zplyr->condition[1] > 0) {
                i = zplyr->condition[1] * 3;
                if (zplyr->cash > 0) {
                    prfmsg(WBLLN);
                    prfmsg(CURPIZ, i);
                    outprf(usrnum);
                    zvda->mstate = 7;
                    getyno(110);
                }
            } else {
                zvda->mstate = 0;
                arxy(1, 15);
                prfmsg(CLEROP1);
                outprf(usrnum);
                ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
            }
            break;
        case 3: zvda->mnukey--;
            if (zvda->mnukey < 15) {
                arxy(1, 22);
                prf("                                                                 ");
                outprf(usrnum);
                arxy(1, 24);
                prf("                                                                 ");
                outprf(usrnum);
                arxy(1, 23);
                prf("                                                                 ");
                outprf(usrnum);
                arxy(1, 22);
                prfmsg(UWANT, zcler[zvda->cshop].stobj[zvda->mnukey].objname, l2as(zcler[zvda->cshop].stobj[zvda->mnukey].ocost));
                if (!zvda->rip) {
                    arxy(1, 24);
                    prfmsg(ISRITE);
                    outprf(usrnum);
                }
                zvda->mstate = 4;
                zvda->mlkey = zvda->mnukey;
                getyno(110);
            } else {
                delbox(1, 41, 16);
                arxy(1, 22);
                prf("                                                                 ");
                arxy(1, 24);
                prf("                                                                 ");
                arxy(1, 15);
                prfmsg(CLEROP1);
                outprf(usrnum);
                zvda->mstate = 0;
                // row/col/width/#items/cmchars/rstate
                ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
            }
            break;
        case 4: if (zvda->mnukey == 'Y') {
            arxy(1, 22);
            prf("                                                                 ");
            arxy(1, 24);
            prf("                                                                 ");
            outprf(usrnum);
            if (zplyr->cash >= zcler[zvda->cshop].stobj[zvda->mlkey].ocost) {
                for (i = 0; i < MAXPOBJC; i++)
                    if (zvda->pstuff[i].objname[0] == 0)
                        break;
                if (i < MAXPOBJC) {
                    zplyr->cash -= zcler[zvda->cshop].stobj[zvda->mlkey].ocost;
                    zvda->pstuff[i] = zcler[zvda->cshop].stobj[zvda->mlkey];
                } else {
                    arxy(1, 22);
                    prf("                                                                 ");
                    arxy(1, 24);
                    prf("                                                                 ");
                    outprf(usrnum);
                    arxy(1, 23);
                    prf("                                                                 ");
                    arxy(1, 23);
                    prfmsg(NOROOM);
                    outprf(usrnum);
                }

            }

        }
              arxy(1, 22);
              prf("                                                                 ");
              if (!zvda->rip) {
                  arxy(1, 22);
                  prfmsg(MONHND, l2as(zplyr->cash));
                  arxy(1, 24);
                  prfmsg(ENTSEL);
                  outprf(usrnum);
              } else rip_query(0, 0, zvda->query);
              zvda->mstate = 3;
              ansimenu(1, 43, 36, 16, "ABCDEFGHIJKLMNOP", 110, -2);
              break;
        case 5: zvda->mnukey--;
            if (zvda->mnukey < zvda->litcnt) {
                k = (9 - zvda->mnukey) * 5;
                for (i = 0; i < 5; i++)
                    if (zplyr->cleric[k + i] == NOTFOUND)
                        break;
                if (i < 5) {
                    delbox(1, 48, zvda->litcnt);
                    zvda->mstate = 6;
                    if (!lspells('c', zvda->mnukey, 110)) {
                        delbox(1, 48, zvda->litcnt);
                        zvda->mstate = 5;
                        askpower('c', 110);
                    }
                } else {
                    prfmsg(NOLRNM);
                    outprf(usrnum);
                    zvda->mstate = 5;
                    askpower('c', 110);
                }
            } else {
                delbox(1, 48, zvda->litcnt);
                zvda->mstate = 0;
                ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
            }
            break;
        case 6: zvda->mnukey--;
            tstor = &zcler[zvda->cshop];
            if (zvda->mnukey < zvda->litcnt) {
                i = zvda->mnuslt[zvda->mnukey];
                j = tstor->stspells[i].level;
                if (j > 9 || j < 1) {
                    prfmsg(WZSPLC2, tstor->stspells[i].spellname);
                    outprf(usrnum);
                    j = 9;
                }
                k = (9 - j) * 5;
                for (l = 0; l < 5; l++)
                    if (zplyr->cleric[k + l] == NOTFOUND)
                        break;
                if (l < 5) {
                    for (m = 0; m < cspellcnt; m++)
                        if (sameas(tstor->stspells[i].spellname, clerspell[m].spellname))
                            break;
                    if (m < cspellcnt) {
                        zplyr->cleric[k + l] = m;
                        prfmsg(LRNSPL, clerspell[m].spellname);
                        //            prf("\n at slot %u %u",k,l);
                        outprf(usrnum);
                    } else {
                        prfmsg(WZSPLC1, tstor->stspells[i].spellname);
                        outprf(usrnum);
                    }
                } else {
                    prfmsg(WZNFSF);
                    outprf(usrnum);
                }
                //         if (!lspells('w',zvda->mnukey,130)) {
                delbox(1, 48, zvda->litcnt);
                zvda->mstate = 5;
                askpower('c', 110);
                //         }
            } else {
                delbox(1, 48, zvda->litcnt);
                zvda->mstate = 0;
                ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
            }
            break;
        case 7: if (zvda->mnukey == 'Y') {
            j = TRUE;
            while (j) {
                if (zplyr->cash >= 3) {
                    zplyr->condition[1]--;
                    zplyr->cash -= 3;
                    if (zplyr->condition[1] == 0 || zplyr->cash < 3)
                        j = FALSE;
                } else
                    j = FALSE;
            }
        }
              if (zplyr->condition[1] == 0) {
                  prfmsg(NOPIZN);
              } else {
                  prfmsg(PIZISF);
              }
              outprf(usrnum);
              zvda->mstate = 0;
              arxy(1, 15);
              prfmsg(CLEROP1);
              outprf(usrnum);
              ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
              break;
        case 8: if (zvda->mnukey == 'Y') {
            for (i = 0; i < zvda->litcnt; i++) {
                cost = zvda->pstuff[zvda->mnuslt[i]].ocost;
                if (cost > 0)
                    cost /= 5;
                if (cost == 0)
                    cost = 5;
                if ((ULONG)cost > zplyr->cash)
                    break;
                else {
                    zvda->pstuff[zvda->mnuslt[i]].osp = 0;
                    zplyr->cash -= cost;
                }
            }
            delinm();
            if (i == zvda->litcnt)
                prfmsg(ACIR);
            else
                prfmsg(NACIR);
            outprf(usrnum);
        } else
            delinm();
        zvda->mstate = 0;
        ansimenu(1, 48, 27, 5, "PHRLX", 110, CLERM1);
        break;
        default: restplay();
            prf("unknown cleric state");
            outprf(usrnum);
    }
}

