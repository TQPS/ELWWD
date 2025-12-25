/*****************************************************************************
 *   ELWWDENC.C   V0.62                                 Worlds of Darkness   *
 *   Encounter Routines                                                      *
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

 //TODO: File needs linting

#include "gcomm.h"
#include "brkthu.h"
#include "majorbbs.h"
#include "elwwd.h"
#include "elwwdtyp.h"
#include "elwwdglb.h"


SHORT chkusage(CHAR icls)
{
    SHORT rc;
    USHORT j;
    // j='A'-icls;
    j = icls;
    if (j > 7)
        j = 0;
    //obj[x]=0=NO
    if (zvda->pclass.objects[j] == 1)
        rc = TRUE;
    else
        rc = FALSE;
    return(rc);
}

VOID chkexp(VOID)
{
    ULONG exptbl[15] = { 0 };
    CHAR nstr[81] = { 0 }, ctr;
    USHORT i;

    for (ctr = 0; ctr < 15; ctr++) exptbl[ctr] = atol(zvda->pclass.exp[ctr]);
    if (zplyr->level == 0)
        zplyr->level = 1;
    if (zplyr->level < 15) {
        if (zplyr->exp >= exptbl[zplyr->level - 1]) {
            zplyr->maxhp += (CHAR)(random(zvda->pclass.hp) + 1);
            zplyr->maxmp += zvda->pclass.mp;
            zplyr->level++;
            for (i = 0; i < 9; i++) {

                nstr[0] = zvda->pclass.mage[zplyr->level - 1][i];
                nstr[1] = 0;
                zplyr->mage_new[9 - zplyr->level] += (SHORT)atoi(nstr);
                nstr[0] = zvda->pclass.priest[zplyr->level - 1][i];
                zplyr->cleric_new[9 - zplyr->level] += (SHORT)atoi(nstr);
                if (zplyr->mage_new[i] > 5)
                    zplyr->mage_new[i] = 5;
                if (zplyr->cleric_new[i] > 5)
                    zplyr->cleric_new[i] = 5;
            }

            if (zvda->gstate == INFITE) {
                sprintf(nstr, "[1;37m%s goes up a level![0m", zplyr->name);
                encnews(nstr);
            } else {
                prfmsg(WBLLN);
                outprf(usrnum);
                prfmsg(UPLVL);
                outprf(usrnum);
            }
        }
        if (zvda->gstate != INFITE) {
            if (zvda->rip) zvda->needed = exptbl[zplyr->level - 1] - zplyr->exp;
            else {
                arxy(70, 4);
                prf("[0;32m%s", l2as(exptbl[zplyr->level - 1] - zplyr->exp));
                outprf(usrnum);
            }
        }
    }
}

VOID fireit(VOID)
{
    SHORT tgt = NOTFOUND, abort = FALSE, px = NOTFOUND, tx = 0, ty = 0, fx = 0, fy = 0, trang = 0;
    CHAR tgtid = ' ';

    switch (tsthit(zcbr->chx, zcbr->chy)) {
        case HITMON:
            tgt = locmonst(zcbr->chx, zcbr->chy);
            if (tgt == NOTFOUND) {
                prfmsg(LOSTGT, 'm');
                outprf(usrnum);
                abort = TRUE;
            } else {
                tx = zcbr->monx[tgt];
                ty = zcbr->mony[tgt];
                tgtid = 'm';
            }
            break;

        case HITPLYR:
            px = locplayer(zcbr->chx, zcbr->chy);
            if (px != NOTFOUND) { // was tgt != NOTFOUND
                tgt = zcbr->plyrs[px];
                tx = zcbr->plx[px];
                ty = zcbr->ply[px];
                tgtid = 'p';
            } else {
                prfmsg(LOSTGT, 'p');
                outprf(usrnum);
                abort = TRUE;
            }
            break;
        default:
            tgtid = ' ';
            abort = TRUE;
            break;
    }

    if (!abort) {
        if (tgtid != ' ') {
            fx = zcbr->plx[zvda->cbrpos];
            fy = zcbr->ply[zvda->cbrpos];
            trang = abs(fx - tx) + abs(fy - ty);

            if (fx != tx && fy != ty) {
                trang >>= 1;
                if (trang == 0) trang = 1;
            }

            if (trang <= zvda->pstuff[zvda->obn].orange) {
                addnews("[1;32mTarget struck!", (SHORT)usrnum);
                dodamage(tgt, tgtid, zvda->pstuff[zvda->obn].omd);
            } else {
                addnews("[0;32mTarget was out of range!", (SHORT)usrnum);
            }
        } else {
            addnews("[1;32mMissed it by that much!", (SHORT)usrnum);
        }

        switch (zvda->pstuff[zvda->obn].ortype) {
            case 1:
                zplyr->arrows--;
                break;
            case 2:
                zplyr->rocks--;
                break;
            case 3:
                zplyr->darts--;
        }

    }
}

VOID dodamage(SHORT targn, CHAR targid, SHORT dmg)
{
    USHORT i;
    CHAR nstr[81];

    switch (targid) {
        case 'm': if (zcbr->cmonst[targn].hp <= dmg) {
            if (zcbr->cmonst[targn].hp > 0) {
                zcbr->cmonst[targn].hp = 0;
                xcdraw('m', targn);
                sprintf(nstr, "%s has killed the %s", zplyr->name, zcbr->cmonst[targn].name);
                tellthem(nstr);
                sprintf(nstr, "[1;31mYou killed the %s ", zcbr->cmonst[targn].name);
                addnews(nstr, (SHORT)usrnum);
                kiltm(zcbr->cmonst[targn].exp);
                zplyr->cash += zcbr->cmonst[targn].gold;
                zplyr->enckills++;
            } else {
                xcdraw('m', targn);
                sprintf(nstr, "[1;31mThe %s isn't any deader", zcbr->cmonst[targn].name);
                addnews(nstr, (SHORT)usrnum);
            }
            if (tstend())
                encnews("All monsters have been killed!");
        } else {
            zcbr->cmonst[targn].hp -= (CHAR)dmg;
            sprintf(nstr, "[1;31m%s struck %s for %d damage", zplyr->name, zcbr->cmonst[targn].name, dmg);
            tellthem(nstr);
            sprintf(nstr, "[1;37mYou struck %s for %d damage", zcbr->cmonst[targn].name, dmg);
            addnews(nstr, (SHORT)usrnum);
        }
                arxy(1, 4);
                dlife(zcbr->cmonst[targn].hp, zcbr->mxlife[targn]);
                outprf(usrnum);
                break;
        case 'p': xlvda = (VDABLK*)vdaoff(targn);
            if (xlvda->plyr.currhp <= dmg) {
                if (!xlvda->dead) {
                    if (targn != usrnum) {
                        zplyr->enckills++;
                        xlvda->plyr.encloss++;
                    }
                    xlvda->dead = TRUE;
                    xlvda->rdlife = TRUE;
                    xlvda->plyr.currhp = 0;
                    /* He's dead Jim */
                    if (zvda->gstate == INFITE) {
                        sprintf(nstr, "[1;37mYou have killed %s ", xlvda->plyr.name);
                        addnews(nstr, (SHORT)usrnum);
                        sprintf(nstr, "[1;32m%s has killed you", zplyr->name);
                        addnews(nstr, targn);
                        sprintf(nstr, "[1;36m%s has killed %s", zplyr->name, xlvda->plyr.name);
                        for (i = 0; i < zcbr->pcnt; i++)
                            if (zcbr->plyrs[i] != usrnum &&
                                zcbr->plyrs[i] != targn)
                                addnews(nstr, zcbr->plyrs[i]);
                        if (targn != usrnum)
                            kiltm(xlvda->plyr.level * 15);
                        if (tstend())
                            for (i = 0; i < zcbr->pcnt; i++)
                                if (zcbr->pgrp[i] == zcbr->pgrp[zvda->cbrpos]) {
                                    addnews("[1;37mYour party is victorious", zcbr->plyrs[i]);
                                    addnews("[1;35mThe other party has been killed!", zcbr->plyrs[i]);
                                }
                    } else {
                        clrprf();
                        prfmsg(KILT, zplyr->name);
                        outprf(targn);
                        prfmsg(UKILT, xlvda->plyr.name);
                        outprf(usrnum);
                    }
                } else {
                    sprintf(nstr, "[1;37mNo points for flogging a corpse");
                    addnews(nstr, (SHORT)usrnum);
                }
            } else {
                if (zvda->gstate == INFITE) {
                    xlvda->plyr.currhp -= (CHAR)dmg;
                    xlvda->rdlife = TRUE;
                    sprintf(nstr, "[1;32m%s takes %u damage", xlvda->plyr.name, dmg);
                    addnews(nstr, (SHORT)usrnum);
                    sprintf(nstr, "[1;37m%s has struck. You lose %u hp", zplyr->name, dmg);
                    addnews(nstr, targn);
                    sprintf(nstr, "%s has struck %s for %u hp", zplyr->name, xlvda->plyr.name, dmg);
                    for (i = 0; i < zcbr->pcnt; i++)
                        if (zcbr->plyrs[i] != usrnum &&
                            zcbr->plyrs[i] != targn)
                            addnews(nstr, zcbr->plyrs[i]);
                    arxy(1, 4);
                    dlife(xlvda->plyr.currhp, xlvda->plyr.maxhp);
                    outprf(usrnum);
                } else {
                    clrprf();
                    prfmsg(DMGED, zplyr->name, dmg);
                    outprf(targn);
                    prfmsg(UDMGED, xlvda->plyr.name, dmg);
                    outprf(usrnum);
                }
            }
    }

}

VOID castenc(VOID)
{

    switch (zvda->mstate) {
        case 2: if (zplyr->currmp > 0) {
            castinit();
        } else {
            arxy(1, 13);
            prfmsg(UHNOMP);
            outprf(usrnum);
        }
              break;
    }
}

VOID rape(CHAR kk)
{
    SHORT tx, ty, ti, pkok;
    CHAR xmsg[81];
    ULONG maxval;
    USHORT pospriz[100] = { 0 }, ppriz, i, j, fspot;

    if (zplyr->level < 11) {
        maxval = 500;
        if (zplyr->level > 1) {
            maxval += 1000 * (zplyr->level - 1);
        }
    } else
        maxval = 999999L;
    setdx(kk);
    tx = zcbr->plx[zvda->cbrpos];
    ty = zcbr->ply[zvda->cbrpos];
    tx += gdx;
    ty += gdy;
    ti = tsthit(tx, ty);
    switch (ti) {
        case HITMON: if ((tx = locmonst(tx, ty)) != NOTFOUND) {
            if (zcbr->cmonst[tx].hp > 0) {
                addnews("[1;33mNice try but it isn't dead yet", (SHORT)usrnum);
            } else
                if (zcbr->mrape[tx] == 0) {
                    for (i = 0; i < MAXPOBJC; i++)
                        if (zvda->pstuff[i].objname[0] == 0)
                            break;
                    if (i < MAXPOBJC && totpriz) {
                        fspot = i;
                        zcbr->mrape[tx] = 1;
                        pkok = FALSE;
                        i = (USHORT)random(7);
                        switch (i) {
                            case 0: if (random(100) < zcbr->cmonst[tx].weapon)
                                pkok = TRUE;
                                break;
                            case 1: if (random(100) < zcbr->cmonst[tx].armor)
                                pkok = TRUE;
                                break;
                            case 2: if (random(100) < zcbr->cmonst[tx].ring)
                                pkok = TRUE;
                                break;
                            case 3: if (random(100) < zcbr->cmonst[tx].potion)
                                pkok = TRUE;
                                break;
                            case 4: if (random(100) < zcbr->cmonst[tx].stone)
                                pkok = TRUE;
                                break;
                            case 5: if (random(100) < zcbr->cmonst[tx].amulet)
                                pkok = TRUE;
                                break;
                            case 6: if (random(100) < zcbr->cmonst[tx].scroll)
                                pkok = TRUE;
                                break;
                        }
                        if (pkok) {
                            ppriz = 0;
                            for (j = 0; j < totpriz; j++)
                                if (przbase[j].otype == i &&
                                    przbase[j].ocost <= maxval) {
                                    pospriz[ppriz] = j;
                                    ppriz++;
                                    if (ppriz == 100)
                                        break;
                                }
                            if (ppriz) {
                                j = (USHORT)random(ppriz);
                                zvda->pstuff[fspot] = przbase[pospriz[j]];
                                sprintf(xmsg, "[1;37mYou find a %s on the corpse", zvda->pstuff[fspot].objname);
                                addnews(xmsg, (SHORT)usrnum);
                            } else {
                                addnews("[1;35mYou find nothing worthwhile", (SHORT)usrnum);
                            }
                        } else {
                            addnews("[1;35mYou don't find anything", (SHORT)usrnum);
                        }
                    } else {
                        addnews("[1;35mYou search and find nothing", (SHORT)usrnum);
                    }
                } else {
                    addnews("[1;36mThe body has been picked clean", (SHORT)usrnum);
                }
        } else {
            addnews("[1;36mYou don't find anything", (SHORT)usrnum);
        }
                   break;
        case HITPLYR: addnews("[1;35mYou discover nothing", (SHORT)usrnum);
            break;
    }
}

SHORT dospec(CHAR targ, SHORT tnum, CHAR spwr, SHORT ddm, CHAR ap)
{
    SHORT rdmg = 0, targn; // tpch = 0;
    CHAR nstr[81];

    if (targ == 'p') {
        targn = zcbr->plyrs[tnum]; // RH: was targn = tpch = zcbr->plyrs[tnum];
        xlvda = (VDABLK*)vdaoff(targn); // RH: was vdaoff(tpch);
    } else
        targn = tnum;

    switch (spwr) {
        case 1:
            poison(targ, targn, 'p', (SHORT)usrnum);           // poison
            break;
        case 2:
            curepoison(targ, targn, (SHORT)usrnum);         //cure poison
            break;
        case 3:
            drainlvl(targ, targn, 'p', (SHORT)usrnum);    //level drain
            break;
        case 4:
            drainlife(targ, targn, 'p', (SHORT)usrnum, ddm); //life drain
            break;
        case 5:
            agehim(targ, targn, ddm, 'p', (SHORT)usrnum);
            break;
        case 6:
            paralyze(targ, targn, (CHAR)(random(6) + 1), 'p', (SHORT)usrnum);  //paralysis
            break;
        case 7:
            if (targ == 'm') {              //critical
                if (ddm < zcbr->cmonst[tnum].hp)
                    rdmg = zcbr->cmonst[tnum].hp - ddm;
                if (rdmg < 5)
                    rdmg = 0;
                else {
                    sprintf(nstr, "[1;32m%s suffers critical damage", zcbr->cmonst[tnum].name);
                    addnews(nstr, (SHORT)usrnum);
                }
            }
            if (targ == 'p') {
                if (ddm < xlvda->plyr.currhp) {
                    rdmg = xlvda->plyr.currhp - ddm;
                    if (rdmg < 10)
                        rdmg = 0;
                    else
                        addnews("[1;33mYou've taken critical damage!", targn); // RH: This was tpch, but why?
                }
            }
            break;
        case 8:
            heal(targ, targn, zvda->pstuff[zvda->obn].osphd, (SHORT)usrnum);    //heal
            break;
        case 9:
            if (ap == 'p')                 //xdmg
                rdmg = zvda->pstuff[zvda->obn].osphd;
            break;
        case 10:
            mshield(targ, targn, (CHAR)(random(6) + 1), 'p', (SHORT)usrnum);
            break;
    }
    return(rdmg);
}

USHORT acplyr(SHORT unum)
{
    SHORT i, tac;
    VDABLK* pvda;
    pvda = (VDABLK*)vdaoff(unum);
    tac = 0;
    for (i = 0; i < MAXPOBJC; i++)
        if (pvda->pstuff[i].objname[0] != 0 &&
            pvda->plyr.equip[i] == 1) {
            if (pvda->pstuff[i].osp == 11)
                tac -= pvda->pstuff[i].oac;
            else
                tac += pvda->pstuff[i].oac;
        }
    if (tac > 0)
        pvda->lac = tac;
    else
        pvda->lac = 0;
    return(pvda->lac);
}


SHORT calcthac(CHAR tch, SHORT tnum, CHAR atp, SHORT atn)
{
    SHORT tac, rmod = 0, roll;
    USHORT i;

    /* do target first */
    tac = (tch == 'm') ? zcbr->cmonst[tnum].ac : acplyr(zcbr->plyrs[tnum]);
    /*
   switch(tch) {
     case 'm': tac=zcbr->cmonst[tnum].ac;
               break;
     case 'p': tac=acplyr(zcbr->plyrs[tnum]);
               break;
    }*/
    if (tac < 125) {
        if (tac < 0)
            tac = 0;
        i = (125 - tac) / 10;
        rmod = 0 - i;
    }
    if (tac > 125)
        rmod = (tac - 125) / 10;
    /* now do attacker */
    roll = 0;
    switch (atp) {
        case 'm': i = zcbr->cmonst[atn].level;
            roll = thactbl[i] + rmod;
            break;
        case 'p': xlvda = (VDABLK*)vdaoff(zcbr->plyrs[atn]);
            i = xlvda->plyr.level;
            roll = thactbl[i] + rmod;
            if (xlvda->plyr.attrib[0] > 5) {
                i = xlvda->plyr.attrib[0] / 5;
                roll -= i;
            }
            break;
    }
    if (roll < 0)
        roll = 0;
    return(roll);
}

VOID monstproc(VOID)
{
    SHORT i, j = NOTFOUND, tx, ty, themov = FALSE, mn, dist, tdist, ap = NOTFOUND;
    static CHAR mmk[] = "78946123";
    CHAR xstr[81];

    mn = zcbr->curmn;
    if (zcbr->cmonst[mn].hp > 0 && !zcbr->mcond[mn][1]) {
        /* is there anyone beside me */
        for (i = 0; i < 8; i++) {
            setdx(mmk[i]);
            tx = zcbr->monx[mn] + gdx;
            ty = zcbr->mony[mn] + gdy;
            if (tx >= 0 && tx < 39 && ty >= 0 && ty <= 9)
                if (tsthit(tx, ty) == HITPLYR) {
                    ap = locplayer(tx, ty);
                    if (ap != NOTFOUND) {
                        xlvda = (VDABLK*)vdaoff(zcbr->plyrs[ap]);
                        if (!xlvda->dead)
                            break;
                    }
                }
        }
        if (i < 8) {
            themov = HITPLYR;
        }

        if (zcbr->cmonst[mn].moves > 0 && themov == FALSE) {
            /* see where to go */
            dist = 99;
            for (i = 0; i < zcbr->pcnt; i++) {
                xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                if (!xlvda->dead) {
                    tx = abs(zcbr->monx[mn] - zcbr->plx[i]);
                    ty = abs(zcbr->mony[mn] - zcbr->ply[i]);
                    tdist = tx + ty;
                    if (tdist < dist) {
                        dist = tdist;
                        j = i;
                    }
                }
            }
            if (dist != 99) {
                themov = HITMON;
            } else {
                themov = FALSE;
            }
        }
        /* add more code here for range wepons & spells */

        /* now do whatever */
        switch (themov) {
            case HITMON:
                if (j == NOTFOUND) {
                    themov = FALSE; break;
                } // RH: guard against invalid j
                if (zcbr->umov[mn] < zcbr->cmonst[mn].moves) {
                    tx = zcbr->monx[mn] - zcbr->plx[j];
                    ty = zcbr->mony[mn] - zcbr->ply[j];
                    if (tx > 0) tx = -1;
                    else if (tx < 0) tx = 1;
                    if (ty > 0) ty = -1;
                    else if (ty < 0) ty = 1;
                    if ((zcbr->monx[mn] == 0 && tx == -1) ||
                        (zcbr->monx[mn] == 39 && tx == 1))
                        tx = 0;
                    if ((zcbr->mony[mn] == 0 && ty == -1) ||
                        (zcbr->mony[mn] == 9 && ty == 1))
                        ty = 0;
                    j = zcbr->mony[mn] + ty;
                    i = zcbr->monx[mn] + tx;
                    /* scope for blockages */
                    dist = tsthit(i, j);
                    switch (dist) {
                        case HITMON:
                            tdist = locmonst(i, j);
                            if (tdist == NOTFOUND ||
                                zcbr->cmonst[tdist].hp == 0)
                                dist = FALSE;
                            break;
                        case HITPLYR:
                            ap = locplayer(i, j);
                            if (ap != NOTFOUND) {
                                xlvda = (VDABLK*)vdaoff(zcbr->plyrs[ap]);
                                if (xlvda->dead)
                                    dist = FALSE;
                            }
                            break;
                        case HITXIT:
                            dist = FALSE;
                    }
                    if ((tx || ty) && !dist) {
                        zcbr->omonx[mn] = zcbr->monx[mn];
                        zcbr->omony[mn] = zcbr->mony[mn];
                        zcbr->mony[mn] += (CHAR)ty;
                        zcbr->monx[mn] += (CHAR)tx;
                        zcbr->umov[mn]++;
                        xcdraw('m', mn);
                    } else
                        themov = FALSE;
                } else
                    themov = FALSE;
                break;
            case HITPLYR:
                if (zcbr->uatak[mn] < zcbr->cmonst[mn].attacks) {
                    zcbr->uatak[mn]++;
                    dist = calcthac('p', ap, 'm', mn);
                    tdist = (SHORT)random(20) + 1;
                    xlvda = (VDABLK*)vdaoff(zcbr->plyrs[ap]);
                    sprintf(xstr, "The %s is attacking %s", zcbr->cmonst[mn].name, xlvda->plyr.name);
                    for (i = 0; i < zcbr->pcnt; i++)
                        if (i != ap)
                            addnews(xstr, zcbr->plyrs[i]);
                    if (tdist >= dist) {   // got a hit
                        addnews(zcbr->cmonst[mn].amsg, zcbr->plyrs[ap]);
                        j = zcbr->cmonst[mn].dmg;
                        if (xlvda->lac > 5)
                            i = xlvda->lac / 5;
                        else
                            i = 0;
                        if (i < j)
                            j -= i;
                        else
                            j = 0;
                        if (j) {
                            xlvda->rdlife = TRUE;
                            if (j >= xlvda->plyr.currhp) {
                                xlvda->plyr.currhp = 0;
                                xlvda->dead = TRUE;
                                xlvda->plyr.encloss++;
                                sprintf(xstr, "The %s has killed %s", zcbr->cmonst[mn].name, xlvda->plyr.name);
                                for (i = 0; i < zcbr->pcnt; i++)
                                    if (i != ap)
                                        addnews(xstr, zcbr->plyrs[i]);
                                sprintf(xstr, "[1;33mThe %s has killed you", zcbr->cmonst[mn].name);
                                addnews(xstr, zcbr->plyrs[ap]);
                            } else {
                                xlvda->plyr.currhp -= (CHAR)j;
                                sprintf(xstr, "[1;31m%s loses %d hp", xlvda->plyr.name, j);
                                encnews(xstr);
                            }
                        } else {
                            sprintf(xstr, "[1;34m%s shrugs off the blow", xlvda->plyr.name);
                            encnews(xstr);
                        }
                    } else {
                        sprintf(xstr, "[1;33mThe %s missed!", zcbr->cmonst[mn].name);
                        encnews(xstr);
                    }
                } else
                    themov = FALSE;
                break;
        }
    }

    if (zcbr->cmonst[mn].hp > 0)
        deccond('m', mn);
    /* check for termination of mp */
    ap = j = FALSE;
    if (!themov ||
        (themov == HITMON && zcbr->umov[mn] == zcbr->cmonst[mn].moves) ||
        (themov == HITPLYR && zcbr->uatak[mn] == zcbr->cmonst[mn].attacks)) {
        do {
            zcbr->curmn++;
            if (zcbr->curmn >= zcbr->mcount) {
                if (ap)
                    j = TRUE;
                ap = TRUE;
                zcbr->curmn = 0;
            }
            if (zcbr->cmonst[zcbr->curmn].hp > 0) {
                if (!zcbr->mcond[zcbr->curmn][1]) {
                    zcbr->uatak[zcbr->curmn] = 0;
                    zcbr->umov[zcbr->curmn] = 0;
                    j = TRUE;
                } else {
                    deccond('m', zcbr->curmn);
                }
            }
        } while (!j);
    }
    if (ap) {
        zcbr->redf = TRUE;
        zcbr->entype = 'p';
        nxtplyr();
        if (zcbr->entype != ' ')
            zcbr->entype = 'm';
    } else
        for (i = 0; i < zcbr->pcnt; i++) {
            xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
            xlvda->mdrf = FALSE;
            xlvda->mstate = 6;
        }
}

VOID restfite(VOID)
{
    prf("[1;24r");
    prfmsg(COMBAT);
    outprf(usrnum);
    arxy(1, 1);
    prf("[1;37m%s", zplyr->name);
    outprf(usrnum);
    arxy(1, 2);
    dlife(zplyr->currhp, zplyr->maxhp);
    plotguys();
    zvda->cnewsf = TRUE;
}

VOID setdx(CHAR mvk)
{
    switch (mvk) {
        case '8': gdx = 0;
            gdy = -1;
            break;
        case '2': gdx = 0;
            gdy = 1;
            break;
        case '4': gdx = -1;
            gdy = 0;
            break;
        case '6': gdx = 1;
            gdy = 0;
            break;
        case '7': gdx = -1;
            gdy = -1;
            break;
        case '9': gdx = 1;
            gdy = -1;
            break;
        case '1': gdx = -1;
            gdy = 1;
            break;
        case '3': gdx = 1;
            gdy = 1;
            break;
        default: gdx = gdy = 0;
    }
}

VOID piktarg(SHORT oms)
{
    SHORT i;
    zvda->oumstate = oms;
    zvda->mstate = 40;
    zcbr->chx = zcbr->plx[zvda->cbrpos];
    zcbr->chy = zcbr->ply[zvda->cbrpos];
    zcbr->ochx = 99;
    for (i = 0; i < zcbr->pcnt; i++) {
        xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
        xlvda->xhair = TRUE;
    }
}

VOID kiltm(ULONG kexp)
{
    SHORT i;
    CHAR nstr[81];
    ULONG k;
    VDABLK* lvda;
    if (zvda->party == usrnum && zvda->memcnt == 1) {
        zplyr->exp += kexp;
        sprintf(nstr, "[1;37mYou receive %s experience", l2as(kexp));
        addnews(nstr, (SHORT)usrnum);
        chkexp();
    } else {
        k = kexp;
        if (k)
            k /= 2;
        if (k == 0)
            k = 1;
        zplyr->exp += k;
        sprintf(nstr, "[1;37mYou receive %s experience", l2as(k));
        addnews(nstr, (SHORT)usrnum);
        chkexp();
        if (zvda->party == usrnum)
            lvda = zvda;
        else
            lvda = (VDABLK*)vdaoff(zvda->party);
        if (k)
            k /= lvda->memcnt;
        if (!k)
            k = 1;
        sprintf(nstr, "[1;37mYou receive %s experience", l2as(k));
        for (i = 0; i < zcbr->pcnt; i++)
            if (zcbr->plyrs[i] != usrnum) {
                lvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                lvda->plyr.exp += k;
                addnews(nstr, zcbr->plyrs[i]);
            }

    }
}

SHORT tsthit(SHORT tx, SHORT ty)
{
    SHORT i, ishit = FALSE;
    if (zcbr->entype == 'm')
        for (i = 0; i < zcbr->mcount; i++)
            if (zcbr->monx[i] == tx && zcbr->mony[i] == ty) {
                ishit = HITMON;
                break;
            }
    if (!ishit && zcbr->xitx == tx && zcbr->xity == ty)
        ishit = HITXIT;
    if (!ishit)
        for (i = 0; i < zcbr->pcnt; i++)
            if (zcbr->plx[i] == tx && zcbr->ply[i] == ty) {
                ishit = HITPLYR;
                break;
            }
    return(ishit);
}

SHORT locmonst(SHORT tx, SHORT ty)
{
    SHORT i, lded = NOTFOUND, lliv = NOTFOUND;
    for (i = 0; i < zcbr->mcount; i++)
        if (zcbr->monx[i] == tx && zcbr->mony[i] == ty) {
            if (zcbr->cmonst[i].hp > 0)
                lliv = i;
            else
                lded = i;
        }
    if (lliv != NOTFOUND)
        i = lliv;
    else
        i = lded;
    return(i);
}

//mnukey is the item he wants to equip
SHORT doequip(VOID)
{
    USHORT loc, i, rcnt, lring, rc = TRUE, j; //rcnt=0
    SHORT spuse, nrem;


    if (!chkusage(zvda->pstuff[zvda->mnukey].oclass)) {
        if (zvda->gstate == INFITE)
            prfmsg(EBLLN);
        else
            prfmsg(WBLLN);
        prfmsg(NYCLS);
        rc = FALSE;
        outprf(usrnum);
        return(rc);
    }
    if (zvda->pstuff[zvda->mnukey].objname[0] != 0 &&
        zplyr->equip[zvda->mnukey] == 1) {
        /* Cursed stuff stays on */
        if (zvda->pstuff[zvda->mnukey].osp == 11) {
            if (zvda->gstate == INFITE)
                prfmsg(EBLLN);
            else
                prfmsg(WBLLN);
            prfmsg(CRCI);
            outprf(usrnum);
        } else {
            /* Unequip equipped item */
            zplyr->equip[zvda->mnukey] = 0;
            if (zvda->gstate == INFITE)
                prfmsg(EBLLN);
            else
                prfmsg(WBLLN);
            prfmsg(REQP, zvda->pstuff[zvda->mnukey].objname);
            outprf(usrnum);
        }
    } else
        if (zvda->pstuff[zvda->mnukey].objname[0] != 0 &&
            zvda->pstuff[zvda->mnukey].owhat != 1) {  //wear or battle
            loc = zvda->pstuff[zvda->mnukey].ospot;
            spuse = FALSE;
            //lring=0;
            /* see if there is a free spot */
            for (i = 0; i < MAXPOBJC; i++)
                if (zplyr->equip[i]) {
                    switch (zvda->pstuff[i].ospot) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4: if (zvda->pstuff[i].ospot == loc)
                            spuse = TRUE;
                            break;
                        case 5: if (zvda->pstuff[i].otype == 2) {
                            //lring++;  /* might need this later when we add features */
                        } else {
                            if (zvda->pstuff[zvda->mnukey].otype != 2)
                                spuse = TRUE;
                        }
                              break;
                        case 6: if (loc == 5 || loc == 6)
                            spuse = TRUE;
                    }
                    if (spuse)
                        break;
                }

            if (!spuse) {
                zplyr->equip[zvda->mnukey] = 1;
                statup(zvda->mnukey, (SHORT)usrnum, (SHORT)usrnum);
                acplyr((SHORT)usrnum);
            } else {
                /* see if can remove thing in way */
                switch (zvda->pstuff[i].ospot) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 6:
                    case 4: if (zvda->pstuff[i].osp != 11) {
                        statoff(i, (SHORT)usrnum, (SHORT)usrnum);
                        zplyr->equip[i] = 0;
                        zplyr->equip[zvda->mnukey] = 1;
                        statup(zvda->mnukey, (SHORT)usrnum, (SHORT)usrnum);
                        acplyr((SHORT)usrnum);
                    } else {
                        if (zvda->gstate == INFITE)
                            prfmsg(EBLLN);
                        else
                            prfmsg(WBLLN);
                        prfmsg(CRCI);
                        outprf(usrnum);
                    }
                          break;
                    case 5: if (zvda->pstuff[zvda->mnukey].otype == 2) {
                        rcnt = 0;
                        for (j = 0; j < MAXPOBJC; j++)
                            if (zplyr->equip[j] && zvda->pstuff[j].ospot == 5 &&
                                zvda->pstuff[j].otype == 2)
                                rcnt++;
                        if (rcnt < 8) {
                            zplyr->equip[zvda->mnukey] = 1;
                            statup(zvda->mnukey, (SHORT)usrnum, (SHORT)usrnum);
                            acplyr((SHORT)usrnum);
                        } else {
                            for (j = 0; j < MAXPOBJC; j++)
                                if (zplyr->equip[j] && zvda->pstuff[j].ospot == 5 &&
                                    zvda->pstuff[j].otype == 2 && zvda->pstuff[j].osp != 11) {
                                    statoff(j, (SHORT)usrnum, (SHORT)usrnum);
                                    zplyr->equip[j] = 0;
                                    zplyr->equip[zvda->mnukey] = 1;
                                    statup(zvda->mnukey, (SHORT)usrnum, (SHORT)usrnum);
                                    acplyr((SHORT)usrnum);
                                    break;
                                }
                            if (j == MAXPOBJC) {
                                if (zvda->gstate == INFITE)
                                    prfmsg(EBLLN);
                                else
                                    prfmsg(WBLLN);
                                prfmsg(CRCI);
                                outprf(usrnum);
                            }
                        }
                    } else {
                        if (zvda->pstuff[zvda->mnukey].ospot == 6) {
                            nrem = FALSE;
                            for (j = 0; j < MAXPOBJC; j++)
                                if (zplyr->equip[j] && zvda->pstuff[j].ospot == 5 &&
                                    zvda->pstuff[j].otype != 2) {
                                    if (zvda->pstuff[j].osp != 11) {
                                        statoff(j, (SHORT)usrnum, (SHORT)usrnum);
                                        zplyr->equip[j] = 0;
                                    } else {
                                        nrem = TRUE;
                                        break;
                                    }
                                }
                            if (!nrem) {
                                zplyr->equip[zvda->mnukey] = 1;
                                statup(zvda->mnukey, (SHORT)usrnum, (SHORT)usrnum);
                                acplyr((SHORT)usrnum);
                            } else {
                                if (zvda->gstate == INFITE)
                                    prfmsg(EBLLN);
                                else
                                    prfmsg(WBLLN);
                                prfmsg(CRCI);
                                outprf(usrnum);
                            }
                        } else {
                            rcnt = lring = 0;
                            for (j = 0; j < MAXPOBJC; j++)
                                if (zplyr->equip[j] && zvda->pstuff[j].ospot == 5 &&
                                    zvda->pstuff[j].otype != 2) {
                                    lring++;
                                    if (zvda->pstuff[j].osp == 11)
                                        rcnt++;
                                }
                            if (lring < 2) {
                                zplyr->equip[zvda->mnukey] = 1;
                                statup(zvda->mnukey, (SHORT)usrnum, (SHORT)usrnum);
                                acplyr((SHORT)usrnum);
                            } else {
                                if (lring == rcnt) {
                                    if (zvda->gstate == INFITE)
                                        prfmsg(EBLLN);
                                    else
                                        prfmsg(WBLLN);
                                    prfmsg(CRCI);
                                    outprf(usrnum);
                                } else {
                                    for (j = 0; j < MAXPOBJC; j++)
                                        if (zplyr->equip[j] && zvda->pstuff[j].ospot == 5 &&
                                            zvda->pstuff[j].otype != 2 && zvda->pstuff[j].osp != 11) {
                                            statoff(j, (SHORT)usrnum, (SHORT)usrnum);
                                            zplyr->equip[j] = 0;
                                            zplyr->equip[zvda->mnukey] = 1;
                                            statup(zvda->mnukey, (SHORT)usrnum, (SHORT)usrnum);
                                            acplyr((SHORT)usrnum);
                                            break;
                                        }
                                    if (j == MAXPOBJC) {
                                        if (zvda->gstate == INFITE)
                                            prfmsg(EBLLN);
                                        else
                                            prfmsg(WBLLN);
                                        prfmsg(CRCI);
                                        outprf(usrnum);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else
            rc = FALSE;
        acplyr((SHORT)usrnum);
        return(rc);
}

VOID addnews(CHAR* nstr, SHORT unum)
{
    SHORT i;
    VDABLK* mvda;
    mvda = (VDABLK*)vdaoff(unum);
    if (mvda->nwscnt < 7)
        mvda->nwscnt++;
    for (i = 0; i < 6; i++)
        stzcpy(mvda->cnews[i], mvda->cnews[i + 1], 79);
    stzcpy(mvda->cnews[6], nstr, 79);
    mvda->cnewsf = TRUE;
}

VOID encnews(CHAR* nstr)
{
    SHORT i;
    for (i = 0; i < zcbr->pcnt; i++)
        addnews(nstr, zcbr->plyrs[i]);
}

VOID tellthem(CHAR* nstr)
{
    SHORT i;
    for (i = 0; i < zcbr->pcnt; i++)
        if (zcbr->plyrs[i] != usrnum)
            addnews(nstr, zcbr->plyrs[i]);
}

VOID xcdraw(CHAR who, SHORT pn)
{
    SHORT i;
    for (i = 0; i < zcbr->pcnt; i++) {
        xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
        xlvda->cdraw = TRUE;
        switch (who) {
            case 'm': xlvda->dwho[0] = who;
                xlvda->dwhon[0] = pn;
                break;
            case 'p': xlvda->dwho[1] = who;
                xlvda->dwhon[1] = pn;
        }
    }
}

VOID nxtplyr(VOID)
{
    SHORT i, rset = FALSE, lp;

    if (zcbr->pcnt == 0) {
        prf("\nELWWD: Critical Error in CBR\nNxtPlyr Spinning");
        outprf(usrnum);
        terror2();
        return;
    }
    for (i = 0; i < zcbr->pcnt; i++) {
        xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
        if (!xlvda->dead)
            break;
    }
    if (i == zcbr->pcnt) {
        if (i > 1)
            encnews("Everybody's Dead!");
        else
            encnews("You failed!");
        for (i = 0; i < zcbr->pcnt; i++) {
            xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
            xlvda->mstate = 3;
        }
        zcbr->entype = ' ';
        return;
    }
    lp = zcbr->wfor;
    do {
        zcbr->wfor++;
        if (zcbr->wfor >= zcbr->pcnt) {
            zcbr->wfor = 0;
            if (zcbr->entype == 'm')
                rset = TRUE;
        }
        if (zcbr->wfor < 0)             zcbr->wfor = 0; // RH: Safety check; compiler thinks the next line could be C6385 where wfor=-2
        xlvda = (VDABLK*)vdaoff(zcbr->plyrs[zcbr->wfor]);
    } while (xlvda->dead);
    if (rset) {
        for (i = 0; i < zcbr->mcount; i++)
            if (zcbr->cmonst[i].hp > 0) {
                if (!zcbr->mcond[i][1]) {
                    break;
                } else {
                    deccond('m', i);
                }
            }
        if (i < zcbr->mcount) {
            zcbr->curmn = i;
            zcbr->uatak[i] = 0;
            zcbr->umov[i] = 0;
            // zcbr->mtick=btuTicker(); //ticker;
            // zcbr->fmtik=TRUE;
            encnews("Monsters are moving");
        } else
            rset = FALSE;
    }
    for (i = 0; i < zcbr->pcnt; i++) {
        xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
        if (zcbr->entype == 'm' && rset == TRUE)
            xlvda->mstate = 5;
        else
            xlvda->mstate = 4;
    }
    if (!rset) {
        zcbr->ptick = mwaitt;
        zcbr->tick = btuTicker(); //ticker;
        deccond('p', (SHORT)usrnum);
        zcbr->redf = TRUE;
    } else {
        zcbr->redf = FALSE;
        zcbr->wfor = zcbr->pcnt;
    }
    if (lp < 0) lp = 0; // RH: Safety check again, same issue as above - thinks lp could be -2.
    if (lp < zcbr->pcnt && ingame[zcbr->plyrs[lp]])
        xcdraw('p', lp);
}

VOID rpfenc(VOID)
{
    SHORT i, j = 0;
    VDABLK* pvda;
    for (i = 0; i < zcbr->pcnt; i++)
        if (zcbr->plyrs[i] != usrnum) {
            zcbr->plyrs[j] = zcbr->plyrs[i];
            zcbr->plx[j] = zcbr->plx[i];
            zcbr->ply[j] = zcbr->ply[i];
            zcbr->oplx[j] = zcbr->oplx[i];
            zcbr->oply[j] = zcbr->oply[i];
            zcbr->pgrp[j] = zcbr->pgrp[i];
            pvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
            pvda->cbrpos = j;
            j++;
        }
    zcbr->pcnt = j;
}

SHORT tstend(VOID)
{
    SHORT isover = FALSE;
    USHORT i, j;
    switch (zcbr->entype) {
        case 'm': for (i = 0; i < zcbr->mcount; i++)
            if (zcbr->cmonst[i].hp > 0)
                break;
            if (i == zcbr->mcount)
                isover = TRUE;
            break;
        case 'p': isover = TRUE;
            j = zcbr->pgrp[zvda->cbrpos];
            for (i = 0; i < zcbr->pcnt; i++)
                if (zcbr->pgrp[i] != j) {
                    xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                    if (!xlvda->dead) {
                        isover = FALSE;
                        break;
                    }
                }
            break;
    }
    return(isover);
}

VOID encleave(VOID)
{
    CHAR xstr[81];
    USHORT i;

    if (tstend()) {
        /* everybody out of the pool */
        for (i = 0; i < zcbr->pcnt; i++) {
            xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
            if (xlvda->dead)
                lparty(zcbr->plyrs[i]);
            xlvda->mstate = 3;
        }
        zcbr->entype = ' ';
        zcbr->pcnt = 0;
    } else {
        sprintf(xstr, "[1;37m%s has run away", zplyr->name);
        zplyr->encloss++;
        encnews(xstr);
        rpfenc();
        if (zcbr->pcnt == 0)
            zcbr->entype = ' ';
        restplay();
    }
}

VOID dlife(USHORT chp, USHORT maxl)
{
    USHORT j, k, sf;
    CHAR lfl[20];

    if (zvda->lmode == 0) {
        if (maxl == 0) {
            arxy(1, 13);
            prf("X13: ZeroDiv in DLIFE for maxl\n");
            outprf(usrnum);
        } else {
            sf = maxl / 16;
            if (sf == 0) {
                sf = 1;
            }
            if (sf * 16 < maxl)
                sf++;
            if (chp > 0) {
                j = chp / sf;
                if (j == 0) j = 1;
            } else
                j = 0;
            k = j;
            while (j > 0) {
                prf("Û");
                j--;
            }
            while (k < 16) {
                prf(" ");
                k++;
            }
            outprf(usrnum);
        }
    } else {
        sprintf(lfl, "%u/%u", chp, maxl);
        while (strlen(lfl) < 16)
            strcat(lfl, " ");
        prf("%s", lfl);
        outprf(usrnum);
    }
}

VOID plotguys(VOID)
{
    SHORT i;
    arxy(zcbr->xitx + 39, zcbr->xity + 2);
    prf("X");
    outprf(usrnum);
    for (i = 0; i < zcbr->pcnt; i++)
        if (ingame[zcbr->plyrs[i]]) {
            arxy(zcbr->plx[i] + 39, zcbr->ply[i] + 2);
            if (zcbr->wfor == i)
                prf("[0;1;31mê[0m");
            else
                if (zcbr->pgrp[i] == zcbr->fcol)
                    prf("[1;32mê[0m");
                else
                    prf("[1;36mê[0m");
            outprf(usrnum);
        }
    if (zcbr->entype == 'm')
        for (i = 0; i < zcbr->mcount; i++)
            if (zcbr->monx[i] != 99) {
                arxy(zcbr->monx[i] + 39, zcbr->mony[i] + 2);
                if (zcbr->cmonst[i].hp > 0)
                    prf("[0mï");
                else
                    prf("[0mU");
                outprf(usrnum);
            }
    zvda->cdraw = FALSE;
}

VOID clrguy(VOID)
{
    SHORT x = 0, y = 0, mn, i, nogo; // RH: Added initialization to y
    CHAR pch;

    for (i = 0; i < 2; i++) {
        nogo = FALSE;
        switch (zvda->dwho[i]) {
            case 'm':
                x = zcbr->omonx[zvda->dwhon[0]];
                y = zcbr->omony[zvda->dwhon[0]];
                break;
            case 'p':
                x = zcbr->oplx[zvda->dwhon[1]];
                y = zcbr->oply[zvda->dwhon[1]];
                break;
            default:
                nogo = TRUE;
        }
        if (nogo) continue; // RH: let's be triple sure!
        if (!nogo) {
            switch (tsthit(x, y)) {
                case HITMON:
                    mn = locmonst(x, y);
                    if (mn != NOTFOUND) {
                        if (zcbr->cmonst[mn].hp > 0)
                            pch = 'ï';
                        else
                            pch = 'U';
                    } else
                        pch = ' ';
                    break;
                case HITPLYR:
                    pch = 'ê';
                    break;
                case HITXIT:
                    pch = 'X';
                    break;
                default:
                    pch = ' ';
            }
            x += 39;
            y += 2;
            if ((x > 0 && x < 80) && (y > 0 && y < 25)) {
                arxy(x, y);
                prf("[0m%c", pch);
                outprf(usrnum);
            }
        }
    }
}

VOID plotguy(VOID)
{
    SHORT x = 99, y = 0, colr = FALSE, doit = TRUE; // RH: Added initialization to y
    CHAR pch = ' ';
    USHORT i;
    VDABLK* pvda;

    for (i = 0; i < 2; i++) {
        switch (zvda->dwho[i]) {
            case 'm':
                x = zcbr->monx[zvda->dwhon[i]] + 39;
                y = zcbr->mony[zvda->dwhon[i]] + 2;
                if (zcbr->cmonst[zvda->dwhon[i]].hp > 0)
                    pch = 'ï';
                else
                    pch = 'U';
                break;
            case 'p':
                x = zcbr->plx[zvda->dwhon[i]] + 39;
                y = zcbr->ply[zvda->dwhon[i]] + 2;
                if (zcbr->wfor == zvda->dwhon[i])
                    colr = TRUE;
                pch = 'ê';
                pvda = (VDABLK*)vdaoff(zcbr->plyrs[zvda->dwhon[i]]);
                if (!ingame[zcbr->plyrs[zvda->dwhon[i]]]) {
                    arxy(1, 14);
                    prf("bad whon=%u", zvda->dwhon[i]);
                    outprf(usrnum);
                    doit = FALSE;
                } else {
                    if (pvda->gstate != INFITE)
                        doit = FALSE;
                }
                break;
        }
        if (doit)
            if ((x > 0 && x < 81) && (y > 0 && y < 25)) {
                arxy(x, y);
                if (zvda->dwho[i] == 'm')
                    prf("%c", pch);
                else {
                    if (colr)
                        prf("[0;1;31m%c[0m", pch);
                    else
                        if (zcbr->pgrp[zvda->dwhon[i]] == zcbr->fcol)
                            prf("[1;32m%c[0m", pch);
                        else
                            prf("[1;36m%c[0m", pch);
                }
                outprf(usrnum);
            }
        zvda->dwhon[i] = 0;
        zvda->dwho[i] = ' ';
    }
    zvda->cdraw = FALSE;
}

VOID prtnews(VOID)
{
    SHORT i;
    if (zvda->nwscnt > 0) {
        prf("[15;23r");
        outprf(usrnum);
        arxy(1, 23);
        if (zvda->nwscnt == 1) {
            prf("\n%s", zvda->cnews[6]);
            outprf(usrnum);
        } else {
            for (i = 7 - zvda->nwscnt; i < 7; i++) {
                prf("\n%s", zvda->cnews[i]);
                outprf(usrnum);
            }
        }
        prf("[1;24r");
        outprf(usrnum);
    }
    zvda->nwscnt = 0;
    zvda->cnewsf = FALSE;
}

VOID movpl(CHAR mvk)
{
    SHORT ppos, tx, ty, badmov = FALSE, iod;
    VDABLK* ivda;

    setdx(mvk);
    if (gdx == 0 && gdy == 0)
        badmov = TRUE;
    if (!badmov && (ppos = zvda->cbrpos) < nterms) {
        tx = zcbr->plx[ppos] + gdx;
        ty = zcbr->ply[ppos] + gdy;
        if ((tx < 0 || tx>38) ||
            (ty < 0 || ty>9))
            badmov = TRUE;
        else {
            badmov = tsthit(tx, ty);
            switch (badmov) {
                case HITMON: iod = locmonst(tx, ty);
                    if (iod != NOTFOUND && zcbr->cmonst[iod].hp == 0)
                        badmov = FALSE;
                    break;
                case HITPLYR: iod = locplayer(tx, ty);
                    if (iod != NOTFOUND) {
                        ivda = (VDABLK*)vdaoff(zcbr->plyrs[iod]);
                        if (ivda->dead)
                            badmov = FALSE;
                    }
            }
        }
        if (!badmov || badmov == HITXIT) {
            zcbr->oplx[ppos] = zcbr->plx[ppos];
            zcbr->oply[ppos] = zcbr->ply[ppos];
            zcbr->plx[ppos] = (CHAR)tx;
            zcbr->ply[ppos] = (CHAR)ty;
            xcdraw('p', ppos);
            addnews("[1;35mYour turn ended", (SHORT)usrnum);
            prfmsg(EBLLN);
            outprf(usrnum);
            if (zcbr->xitx == tx && ty == zcbr->xity) {
                encleave();
            }
            badmov = FALSE;
        }
    }
    if (badmov) {
        prfmsg(EBLLN);
        prfmsg(INVMOV);
        outprf(usrnum);
        zvda->mstate = 2;
    }
}

VOID movtarg(CHAR mvk)
{
    SHORT tx, ty, badmov = FALSE, i;

    setdx(mvk);

    if (gdx != 0 || gdy != 0) {
        tx = zcbr->chx + gdx;
        ty = zcbr->chy + gdy;
        if ((tx < 0 || tx>38) ||
            (ty < 0 || ty>9))
            badmov = TRUE;
        if (!badmov) {
            zcbr->ochx = zcbr->chx;
            zcbr->ochy = zcbr->chy;
            zcbr->chx = (CHAR)tx;
            zcbr->chy = (CHAR)ty;
            for (i = 0; i < zcbr->pcnt; i++) {
                xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                xlvda->xhair = TRUE;
            }
            badmov = tsthit(tx, ty);
            switch (badmov) {
                case HITMON: i = locmonst(tx, ty);
                    if (i != NOTFOUND) {
                        arxy(1, 3);
                        prf("[1;33m%s[0m", zcbr->cmonst[i].name);
                        outprf(usrnum);
                        arxy(1, 4);
                        dlife(zcbr->cmonst[i].hp, zcbr->mxlife[i]);
                        outprf(usrnum);
                    } else {
                        arxy(1, 3);
                        prf("[0;37munknown");
                        outprf(usrnum);
                    }
                    break;
                case HITPLYR: for (i = 0; i < zcbr->pcnt; i++)
                    if (zcbr->plx[i] == tx && zcbr->ply[i] == ty)
                        break;
                    if (i < zcbr->pcnt) {
                        xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                        arxy(1, 3);
                        prf("[1;33m%s", xlvda->plyr.name);
                        arxy(1, 4);
                        dlife(xlvda->plyr.currhp, xlvda->plyr.maxhp);
                        outprf(usrnum);
                    }
            }
        }
    }
}

VOID attakmons(CHAR mvk)
{
    SHORT mn, tx, ty, thacv, roll, tp;
    USHORT dmg, mres;
    CHAR amsg[81];

    setdx(mvk);
    if (gdx == 0 && gdy == 0) {
        prfmsg(EBLLN);
        prfmsg(INVMOV);
        outprf(usrnum);
        zvda->mstate = 2;
    } else {
        tx = zcbr->plx[zvda->cbrpos] + gdx;
        ty = zcbr->ply[zvda->cbrpos] + gdy;
        if ((tx < 0 || tx>38) ||
            (ty < 0 || ty>9)) {
            prfmsg(EBLLN);
            prfmsg(SWISH);
            outprf(usrnum);
        } else
            switch (tsthit(tx, ty)) {
                case HITMON: mn = locmonst(tx, ty);
                    arxy(1, 3);
                    prf("                    ");
                    arxy(1, 3);
                    prf("[1;33m%s[0m", zcbr->cmonst[mn].name);
                    outprf(usrnum);
                    arxy(1, 4);
                    dlife(zcbr->cmonst[mn].hp, zcbr->mxlife[mn]);
                    outprf(usrnum);
                    if (zcbr->cmonst[mn].hp > 0) {
                        thacv = calcthac('m', mn, 'p', zvda->cbrpos);
                        roll = (SHORT)random(20) + 1;
                        if (roll >= thacv) {   // got a hit
                            dmg = (USHORT)random(zvda->pstuff[zvda->obn].omd) + 1;
                            if (roll == 20) {
                                dmg += (USHORT)random(zvda->pstuff[zvda->obn].omd) + 1;
                                mres = zvda->pstuff[zvda->obn].ocsp;
                                if (random(100) < mres &&
                                    zvda->pstuff[zvda->obn].otsp > 0) {
                                    dmg += dospec('m', mn, zvda->pstuff[zvda->obn].osp, dmg, 'p');
                                    if (zvda->pstuff[zvda->obn].otsp < 999)
                                        zvda->pstuff[zvda->obn].otsp--;
                                }
                            }
                            //1 less dmg for every 5 armors
                            if (zcbr->cmonst[mn].ac >= 5)
                                mres = zcbr->cmonst[mn].ac / 5;
                            else
                                mres = 0;
                            if (mres >= dmg)
                                dmg = 0;
                            else
                                dmg -= mres;
                        } else
                            dmg = 0;
                        prfmsg(EBLLN);
                        if (dmg == 0) {
                            prfmsg(MEVADE);
                            outprf(usrnum);
                        } else {
                            prfmsg(AHIT);
                            outprf(usrnum);
                            dodamage(mn, 'm', dmg);
                        }
                    } else {
                        sprintf(amsg, "[1;36m%s is already dead", zcbr->cmonst[mn].name);
                        addnews(amsg, (SHORT)usrnum);
                    }
                    break;
                case HITPLYR: for (tp = 0; tp < zcbr->pcnt; tp++)
                    if (zcbr->plx[tp] == tx && zcbr->ply[tp] == ty)
                        break;
                    if (tp < zcbr->pcnt) {
                        xlvda = (VDABLK*)vdaoff(zcbr->plyrs[tp]);
                        arxy(1, 3);
                        prf("[1;33m%s[0m", xlvda->plyr.name);
                        arxy(1, 4);
                        dlife(xlvda->plyr.currhp, xlvda->plyr.maxhp);
                        outprf(usrnum);
                        if (xlvda->dead) {
                            sprintf(amsg, "[1;36m%s is already dead", xlvda->plyr.name);
                            addnews(amsg, (SHORT)usrnum);
                        } else {
                            thacv = calcthac('p', tp, 'p', zvda->cbrpos);
                            roll = (SHORT)random(20) + 1;
                            if (roll >= thacv) {   // got a hit
                                dmg = (USHORT)random(zvda->pstuff[zvda->obn].omd) + 1;
                                if (roll == 20) {
                                    dmg += (USHORT)random(zvda->pstuff[zvda->obn].omd) + 1;
                                    mres = zvda->pstuff[zvda->obn].ocsp;
                                    if (random(100) < mres &&
                                        zvda->pstuff[zvda->obn].otsp > 0) {
                                        dmg += dospec('p', tp, zvda->pstuff[zvda->obn].osp, dmg, 'p');
                                        if (zvda->pstuff[zvda->obn].otsp < 999)
                                            zvda->pstuff[zvda->obn].otsp--;
                                    }
                                }
                                xlvda = (VDABLK*)vdaoff(zcbr->plyrs[tp]);
                                //1 less dmg for every 5 armors
                                if (xlvda->lac >= 5)
                                    mres = xlvda->lac / 5;
                                else
                                    mres = 0;
                                if (mres >= dmg)
                                    dmg = 0;
                                else
                                    dmg -= mres;
                            } else
                                dmg = 0;
                            prfmsg(EBLLN);
                            if (dmg == 0) {
                                prfmsg(PEVADE);
                                outprf(usrnum);
                            } else {
                                prfmsg(AHIT);
                                outprf(usrnum);
                                dodamage(zcbr->plyrs[tp], 'p', dmg);
                            }
                        }
                    } else {
                        prfmsg(EBLLN);
                        prf("lost ptarg");
                        outprf(usrnum);
                    }
                    break;
                default: prfmsg(EBLLN);
                    prfmsg(SWISH);
                    outprf(usrnum);
            }
        nxtplyr();
    }
}

VOID plothair(VOID)
{
    USHORT i, x, y;
    SHORT rc, nohit = TRUE, mn;
    zvda->xhair = FALSE;
    if (zcbr->ochx != 99) {
        rc = tsthit(zcbr->ochx, zcbr->ochy);
        arxy(zcbr->ochx + 39, zcbr->ochy + 2);
        switch (rc) {
            case HITMON: mn = locmonst(zcbr->ochx, zcbr->ochy);
                if (mn != NOTFOUND && zcbr->cmonst[mn].hp > 0)
                    prf("ï");
                else
                    prf("U");
                break;
            case HITPLYR: mn = locplayer(zcbr->ochx, zcbr->ochy);;
                if (mn != NOTFOUND)
                    if (zcbr->pgrp[mn] == zcbr->fcol)
                        prf("[1;32mê[0m");
                    else
                        prf("[1;36mê[0m");
                break;
            case HITXIT:  prf("X");
                break;
            default: prf(" ");
        }
    }
    outprf(usrnum);

    if (zcbr->chx != 99) {
        x = zcbr->chx;
        y = zcbr->chy;
        arxy(x + 39, y + 2);
        prf("Å");
        outprf(usrnum);
        rc = tsthit(x, y);
        switch (rc) {
            case HITMON: i = locmonst(x, y);
                arxy(1, 3);
                prf("                    ");
                arxy(1, 3);
                prf("[1;33m%s[0m", zcbr->cmonst[i].name);
                outprf(usrnum);
                arxy(1, 4);
                dlife(zcbr->cmonst[i].hp, zcbr->mxlife[i]);
                nohit = FALSE;
                break;
            case HITPLYR: for (i = 0; i < zcbr->pcnt; i++)
                if (zcbr->plx[i] == x && zcbr->ply[i] == y)
                    break;
                if (i < zcbr->pcnt) {
                    xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                    arxy(1, 3);
                    prf("[1;33m%s[0m", xlvda->plyr.name);
                    arxy(1, 4);
                    dlife(xlvda->plyr.currhp, xlvda->plyr.maxhp);
                    outprf(usrnum);
                    nohit = FALSE;
                }
                break;
            case HITXIT:  arxy(1, 3);
                prf("[1;37mExit");
                outprf(usrnum);
                break;
        }
    }
    if (nohit) {
        arxy(1, 3);
        prf("                    ");
        arxy(1, 4);
        prf("                ");
        outprf(usrnum);
    }
}

SHORT ami(VOID)
{
    SHORT i, j = FALSE;
    VDABLK* pvda;
    if (zcbr->pcnt > 1) {
        for (i = 0; i < zcbr->pcnt; i++) {
            pvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
            if (!pvda->dead && zcbr->plyrs[i] != usrnum)
                break;
        }
        if (i == zcbr->pcnt)
            j = TRUE;
    } else
        j = TRUE;
    return(j);
}

VOID encounter(VOID)
{
    CHAR kkey, nstr[82];
    SHORT i, j, onlyme; //onlyme=FALSE; //i=0
    cbroff(zvda->cbrnum);
    switch (zvda->mstate) {
        case 0: restfite();
            zvda->mstate = 1;
            if (zcbr->redf) {
                xcdraw('p', zcbr->wfor);
                zcbr->redf = FALSE;
                zcbr->ptick = mwaitt;
                zcbr->tick = btuTicker(); //ticker;
                zcbr->ptikf = FALSE;
            }
            if (zvda->cbrpos == zcbr->wfor) {
                zcbr->tick = btuTicker(); //ticker;
            }
            break;
            /* Wait for my turn to move */
        case 1: if (zvda->cbrpos == zcbr->wfor) {
            onlyme = ami();
            if (zplyr->condition[2]) {
                addnews("[1;33mUnable to move, you are paralyzed!", (SHORT)usrnum);
                nxtplyr();
                break;
            }
            if (onlyme)
                addnews("[1;37mAwaiting your move", (SHORT)usrnum);
            else {
                sprintf(nstr, "[1;37mAwaiting your move. You have %u seconds.", zcbr->ptick);
                addnews(nstr, (SHORT)usrnum);
                prfmsg(EBLLN);
                prf("%u...", zcbr->ptick);
                zcbr->ptikf = TRUE;
                outprf(usrnum);
            }
        } else {
            prfmsg(EBLLN);
            outprf(usrnum);
            xlvda = (VDABLK*)vdaoff(zcbr->plyrs[zcbr->wfor]);
            sprintf(nstr, "[1;34mWaiting for %s to move", xlvda->plyr.name);
            addnews(nstr, (SHORT)usrnum);
        }
              if (zvda->cdraw) {
                  clrguy();
                  plotguy();
              }
              if (zcbr->redf) {
                  xcdraw('p', zcbr->wfor);
                  zcbr->redf = FALSE;
                  // stop blank out of critter/player
                  zcbr->oplx[zcbr->wfor] = zcbr->plx[zcbr->wfor];
                  zcbr->oply[zcbr->wfor] = zcbr->ply[zcbr->wfor];
              }
              zvda->mstate = 2;
              break;
        case 2: while (zcbr->tick != btuTicker()) { //ticker
            zcbr->tick++;
            if (zcbr->ptick > 0)
                zcbr->ptick--;
        }
              onlyme = ami();
              if (zcbr->wfor == zvda->cbrpos)
                  if (btuica(usrnum, kpress, 4) > 0) {
                      btucli(usrnum);
                      kkey = xltkey();
                      switch (kkey) {
                          case 'E': j = 0;
                              for (i = 0; i < MAXPOBJC; i++) {
                                  zvda->mnuslt[i] = 0;
                                  if (zvda->pstuff[i].objname[0] != 0 &&
                                      (zvda->pstuff[i].otype == 0 ||
                                          zvda->pstuff[i].otype == 1)) {
                                      j++;
                                      zvda->mnuslt[i] = 1;
                                  }
                              }
                              prfmsg(EBLLN);
                              outprf(usrnum);
                              zvda->litcnt = j;
                              if (j) {
                                  prfmsg(PICEQU);
                                  outprf(usrnum);
                                  zvda->mstate = 30;
                                  pagemenu(80, j, TRUE);
                              } else {
                                  prfmsg(NOTHEQU);
                                  outprf(usrnum);
                              }
                              break;
                          case 'A':  for (i = 0; i < MAXPOBJC; i++)
                              if (zvda->pstuff[i].objname[0] != 0 &&
                                  (zvda->pstuff[i].ospot == 5 ||
                                      zvda->pstuff[i].ospot == 6) &&
                                  zplyr->equip[i] == 1)
                                  break;
                              if (i < MAXPOBJC) {
                                  arxy(1, 13);
                                  prfmsg(ADIREC);
                                  outprf(usrnum);
                                  zvda->mstate = 15;
                                  zvda->obn = i;
                              } else {
                                  prfmsg(EBLLN);
                                  prfmsg(BAREH);
                                  nxtplyr();
                              }
                              break;
                          case 'S': arxy(1, 13);
                              prfmsg(SDIREC);
                              outprf(usrnum);
                              zvda->mstate = 16;
                              break;
                          case 'P': nxtplyr();
                              prfmsg(TRNPAS);
                              outprf(usrnum);
                              break;
                          case 'R': for (i = 0; i < MAXPOBJC; i++)
                              if (zvda->pstuff[i].objname[0] != 0 &&
                                  zvda->pstuff[i].otype == 0 &&
                                  zvda->pstuff[i].orange > 0 &&
                                  zplyr->equip[i] == 1)
                                  break;
                              if (i < MAXPOBJC) {
                                  j = TRUE;
                                  switch (zvda->pstuff[i].ortype) {
                                      case 1: if (zplyr->arrows == 0) {
                                          j = FALSE;
                                          prfmsg(NOARW);
                                          outprf(usrnum);
                                      }
                                            break;
                                      case 2: if (zplyr->rocks == 0) {
                                          j = FALSE;
                                          prfmsg(NOROKS);
                                          outprf(usrnum);
                                      }
                                            break;
                                      case 3: if (zplyr->darts == 0) {
                                          j = FALSE;
                                          prfmsg(NODART);
                                          outprf(usrnum);
                                      }
                                            break;
                                  }
                                  if (j) {
                                      zvda->obn = i;
                                      piktarg(33);
                                  }
                              } else {
                                  prfmsg(NORANG);
                                  outprf(usrnum);
                              }
                              break;
                          case 'C': castenc();
                              break;
                          case '+': zvda->lmode ^= 1;
                              zvda->rdlife = TRUE;
                              break;
                          case 'U': useinit();
                              if (zvda->litcnt == 0) {
                                  prfmsg(EBLLN);
                                  prfmsg(NOTHUSE);
                                  outprf(usrnum);
                              } else {
                                  zvda->mstate = 31;
                                  pagemenu(80, zvda->litcnt, TRUE);
                              }
                              break;
                          case '7':
                          case '8':
                          case '9':
                          case '4':
                          case '6':
                          case '1':
                          case '2':
                          case '3': movpl(kkey);
                              if (zcbr->pcnt > 0) {
                                  nxtplyr();
                              }
                              break;
                      }
                  } else {
                      if (!onlyme) {
                          if (zcbr->ptick > 0)
                              if (zcbr->ptick % 5 == 0) {
                                  if (!zcbr->ptikf) {
                                      arxy(1, 13);
                                      prf("%u...", zcbr->ptick);
                                      outprf(usrnum);
                                      zcbr->ptikf = TRUE;
                                  }
                              } else
                                  zcbr->ptikf = FALSE;
                      }
                  } else {  /* waiting guys */
                      if (zvda->dead) {
                          if (btuica(usrnum, kpress, 4) > 0) {
                              btucli(usrnum);
                              kkey = xltkey();
                              if (kkey == 'X') {
                                  rpfenc();
                                  lparty((SHORT)usrnum);
                                  sprintf(nstr, "[1;34m%s has retired", zplyr->name);
                                  tellthem(nstr);
                                  saveplay();
                                  dispmain();
                                  zvda->gstate = ISACTIVE;
                                  zvda->redraw = FALSE;
                              }
                          }
                      } else {
                          chkexp();
                          if (zcbr->ptick == 0 && !onlyme) {
                              /* Took too long, my turn */
                              addnews("[1;31mYou took too LONG.", zcbr->plyrs[zcbr->wfor]);
                              if (zcbr->chx != 99) {
                                  zcbr->chx = 99;
                                  for (i = 0; i < zcbr->pcnt; i++)
                                      xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                                  xlvda->xhair = TRUE;
                              }
                              xlvda = (VDABLK*)vdaoff(zcbr->plyrs[zcbr->wfor]);
                              //i=zcbr->wfor; /* unused */
                              if (xlvda->myuser->substt != 80 &&
                                  xlvda->mstate != 1 && xlvda->mstate != 2) {
                                  xlvda->myuser->substt = 80;
                                  xlvda->mstate = 20;
                              }
                              nxtplyr();
                          }
                          btucli(usrnum);
                      }
                  }
                  /* common exit */
                  if (zvda->gstate == INFITE) {
                      if (zvda->cdraw) {
                          clrguy();
                          plotguy();
                      }
                      if (zvda->cnewsf) {
                          prtnews();
                      }
                      if (zvda->xhair) {
                          plothair();
                      }
                      if (zvda->rdlife) {
                          arxy(1, 2);
                          dlife(zplyr->currhp, zplyr->maxhp);
                          zvda->rdlife = FALSE;
                      }
                  }
                  break;
                  /* Leave after winning/losing */
        case 3: if (zvda->dead) {
            zvda->memcnt = 1;
            zvda->members[0] = zvda->party = (SHORT)usrnum;
            saveplay();
            prfmsg(YRDEAD);
            outprf(usrnum);
            usrptr->substt = 2;
            zvda->gstate = ISACTIVE;
            zvda->redraw = TRUE;
        } else {
            usrptr->substt = 37;
            zvda->nstat = TRUE;
        }
              break;
        case 4: if (zvda->cdraw) {
            clrguy();
            plotguy();
        }
              if (zvda->cnewsf) {
                  prtnews();
              }
              if (zvda->rdlife) {
                  arxy(1, 2);
                  dlife(zplyr->currhp, zplyr->maxhp);
                  zvda->rdlife = FALSE;
              }
              zvda->mstate = 1;
              break;
              /* wait for monsters to move */
        case 5: if (zvda->cdraw) {
            clrguy();
            plotguy();
        }
              monstproc();
              //        zcbr->fmtik=FALSE;
              //        zcbr->mtick=ticker;
              break;
        case 6: if (zvda->cdraw) {
            clrguy();
            plotguy();
        }
              if (zvda->cnewsf) {
                  prtnews();
              }
              if (zvda->rdlife) {
                  arxy(1, 2);
                  dlife(zplyr->currhp, zplyr->maxhp);
                  zvda->rdlife = FALSE;
              }
              if (zvda->mdrf)
                  zvda->mstate = 5;
              else
                  zvda->mdrf = TRUE;
              break;
              /* enter attack direction */
        case 15: if (btuica(usrnum, kpress, 4) > 0) {
            btucli(usrnum);
            kkey = xltkey();
            attakmons(kkey);
            if (zvda->cdraw) {
                clrguy();
                plotguy();
            }
        }
               break;
               /* enter search direction */
        case 16: if (btuica(usrnum, kpress, 4) > 0) {
            btucli(usrnum);
            kkey = xltkey();
            rape(kkey);
            nxtplyr();
        }
               break;
               /* termination of maigic targeting */
        case 18: usrptr->substt = 27;
            zvda->mstate = 3;
            break;
        case 19: prfmsg(COMRST);
            outprf(usrnum);
            plotguys();
            prtnews();
            nxtplyr();
            break;
        case 20: prfmsg(COMRST);
            outprf(usrnum);
            plotguys();
            prtnews();
            zvda->mstate = 2;
            break;
        case 30: if (zvda->mnukey) {
            zvda->mnukey--;
            if (doequip()) {
                zvda->mstate = 19;
            } else
                pagemenu(80, zvda->litcnt, TRUE);
        } else {
            zvda->mstate = 20;
        }
               break;
               /* use an item */
        case 31: if (zvda->mnukey) {
            zvda->mnukey--;
            delbox(13, 50, 8);
            prfmsg(COMRST);
            outprf(usrnum);
            plotguys();
            prtnews();
            /* see if item has a range */
            if (zvda->pstuff[zvda->mnukey].objname[0] != 0 &&
                zvda->pstuff[zvda->mnukey].otype != 0 &&
                zvda->pstuff[zvda->mnukey].otype != 1 &&
                zvda->pstuff[zvda->mnukey].orange > 0) {
                piktarg(32);
            } else {
                zcbr->chx = zcbr->plx[zvda->cbrpos];
                zcbr->chy = zcbr->ply[zvda->cbrpos];
                useit();
                nxtplyr();
            }
        } else
            zvda->mstate = 20;
        break;
        case 32: if (zcbr->chx != 99) {
            useit();
            zcbr->chx = 99;
            for (i = 0; i < zcbr->pcnt; i++) {
                xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                xlvda->xhair = TRUE;
            }
        } else {
            prfmsg(EBLLN);
            prfmsg(WSTNGT);
            outprf(usrnum);
        }
               nxtplyr();
               break;
        case 33: if (zcbr->chx != 99) {
            fireit();
            zcbr->chx = 99;
            for (i = 0; i < zcbr->pcnt; i++) {
                xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                xlvda->xhair = TRUE;
            }
        } else {
            prfmsg(EBLLN);
            prfmsg(WSTNGT);
            outprf(usrnum);
        }
               nxtplyr();
               break;
               /* target moving */
        case 40: if (btuica(usrnum, kpress, 4) > 0) {
            btucli(usrnum);
            kkey = xltkey();
            switch (kkey) {
                case 27: zcbr->chx = 99;
                    for (i = 0; i < zcbr->pcnt; i++) {
                        xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
                        xlvda->xhair = TRUE;
                    }
                case '\r': zvda->mstate = zvda->oumstate;
                    break;
                default: movtarg(kkey);
                    break;
            }
        }
               if (zvda->xhair) {
                   plothair();
               }
               break;
        default: //i++; /* unused, but might need this later? */
            break;
    }
}

VOID assignmonst(SHORT flvl)
{
    SHORT i, j, k, x, y, z, spin;
    USHORT mct, mch[15] = { 0 };

    /* player odds are 2-1 */
    mct = (USHORT)((random(2) + 1) * zcbr->pcnt);
    if (mct > 10)
        mct = 10;
    if (mct == 0)
        mct = 1;
    zcbr->mcount = mct;

    for (i = 0; i < 10; i++) {
        zcbr->monx[i] = 99;
        zcbr->mrape[i] = FALSE;
        zcbr->uatak[i] = 0;
        zcbr->umov[i] = 0;
        for (j = 0; j < 9; j++)
            zcbr->mcond[i][j] = 0;
    }

    j = 0;
    for (i = 0; i < totmonst; i++)
        if (monbase[i].monlvl == flvl) {
            mch[j] = i;
            j++;
            if (j == 15)
                break;
        }

    if (j == 0) {
        j = 1;
        mch[0] = 0;
        mch[1] = 1;
        prf("\nNo qualified monsters\n");
        outprf(usrnum);
    }

    dfaSetBlk(dbmonst);
    for (k = 0; k < zcbr->mcount; k++) {
        i = (SHORT)random(j);
        x = mch[i];
        dfaGetAbs(&zcbr->cmonst[k], monbase[x].monpos, 0);
    }
    dfaRstBlk();

    for (i = 0; i < zcbr->mcount; i++) {
        zcbr->mxlife[i] = zcbr->cmonst[i].hp;
        k = TRUE;
        z = TRUE;
        spin = 0;
        x = (SHORT)random(38); // RH: Just in case
        y = (SHORT)random(9);  // RH: Just in case
        while (k) {
            x = (SHORT)random(38);
            y = (SHORT)random(9);
            for (j = 0; j < zcbr->pcnt; j++)
                if (zcbr->plx[j] == x && zcbr->ply[j] == y) {
                    z = FALSE;
                    break;
                }
            if (zcbr->xitx == x && zcbr->xity == y)
                z = FALSE;
            for (j = 0; j < zcbr->mcount; j++)
                if (zcbr->monx[j] == x && zcbr->mony[j] == y) {
                    z = FALSE;
                    break;
                }
            if (z)
                k = FALSE;
            else {
                spin++;
                if (spin > 50)
                    randomize();
                if (spin > 90)
                    randomize();
                if (spin > 150)
                    randomize();
                if (spin > 999) {
                    k = FALSE;
                    prf("\nExcessive M spin\n");
                    outprf(usrnum);
                }
            }
        }
        zcbr->monx[i] = (CHAR)x;
        zcbr->mony[i] = (CHAR)y;
    }
}

VOID initcbr(VOID)
{
    SHORT i, x, y, j, k;

    for (i = 0; i < zcbr->pcnt; i++)
        zcbr->plx[i] = 99;

    /* Assign initial player positions */
    for (i = 0; i < zcbr->pcnt; i++) {
        k = TRUE;
        x = (SHORT)random(38); // RH: Just in case 
        y = (SHORT)random(9);  // RH: JUst in case
        while (k) {
            x = (SHORT)random(38);
            y = (SHORT)random(9);
            for (j = 0; j < zcbr->pcnt; j++)
                if (zcbr->plx[j] == x && zcbr->ply[j] == y)
                    break;
            if (j == zcbr->pcnt)
                k = FALSE;
        }
        zcbr->plx[i] = (CHAR)x;
        zcbr->ply[i] = (CHAR)y;
        zcbr->oplx[i] = (CHAR)x;
        zcbr->oply[i] = (CHAR)y;
    }
    prf("player pos done");
    outprf(usrnum);

    /* Assign the exit point */
    k = TRUE;
    x = (SHORT)random(38); // RH: Just in case
    y = (SHORT)random(9);  // RH: Just in case
    while (k) {
        x = (SHORT)random(38);
        y = (SHORT)random(9);
        for (j = 0; j < zcbr->pcnt; j++)
            if (zcbr->plx[j] == x && zcbr->ply[j] == y)
                break;
        if (j == zcbr->pcnt)
            k = FALSE;
    }
    zcbr->xitx = (CHAR)x;
    zcbr->xity = (CHAR)y;
    prf("xit placed");
    outprf(usrnum);
    /* Assign critters */
    if (zcbr->entype == 'm') {
        j = 0;
        for (i = 0; i < zcbr->pcnt; i++) {
            xlvda = (VDABLK*)vdaoff(zcbr->plyrs[i]);
            j += xlvda->plyr.level;
        }
        if (j > 1) {
            j /= zcbr->pcnt;
            if (j == 0)
                j = 1;
        } else
            j = 1;
        assignmonst(j);
        zcbr->curmn = 0;
    }
    /* Set for first player */
    zcbr->wfor = 0;
    zcbr->redf = TRUE;   /* issue global notify */
}

VOID setfight(SHORT usrn, SHORT cbrn)
{
    SHORT i, k, j, lgrp = 0;
    VDABLK* tvda;
    CHAR c_lgrp, c_party;

    if (usrn == usrnum) {
        zcbr->pcnt = 0;
        covda = (VDABLK*)vdaoff(zvda->party);
        c_lgrp = (CHAR)lgrp;
        c_party = (CHAR)zvda->party;
        zcbr->fcol = c_lgrp = c_party;
    } else {
        tvda = (VDABLK*)vdaoff(usrn);
        covda = (VDABLK*)vdaoff(tvda->party);
        lgrp = tvda->party;
    }
    clrprf();
    if (zcbr->entype == 'p')
        prfmsg(WBLLN);
    prfmsg(ENCBGN);
    for (i = 0; i < covda->memcnt; i++) {
        k = covda->members[i];
        if (ingame[k]) {
            outprf(k);
            btutrg(k, 1);
            btuinj(k, CYCLE);
            btuxnf(k, 0, 0);
            btupbc(k, 0);
            tvda = (VDABLK*)vdaoff(k);
            tvda->incycle = TRUE;
            tvda->nwscnt = 0;
            tvda->xhair = FALSE;
            tvda->infight = TRUE;
            tvda->mstate = 0;
            tvda->myuser->substt = 80;
            tvda->cstate = ALIVE;
            tvda->cdraw = FALSE;
            tvda->gstate = INFITE;
            tvda->cbrnum = cbrn;
            tvda->cnewsf = FALSE;
            tvda->cbrpos = zcbr->pcnt;
            zcbr->plyrs[zcbr->pcnt] = k;
            zcbr->pgrp[zcbr->pcnt] = lgrp;
            zcbr->pcnt++;
            for (j = 0; j < 7; j++)
                tvda->cnews[j][0] = 0;
        }
    }
}

VOID cbcleanup(VOID)
{
    SHORT i, j, k;
    VDABLK* cbvda;
    for (i = 0; i < nterms; i++) {
        cbroff(i);
        switch (zcbr->entype) {
            case 'p':
            case 'm': for (j = 0; j < zcbr->pcnt; j++) {
                if (zcbr->plyrs[j] < nterms &&
                    zcbr->plyrs[j] >= 0 &&
                    ingame[zcbr->plyrs[j]]) {
                    cbvda = (VDABLK*)vdaoff(zcbr->plyrs[j]);
                    if (!cbvda->infight)
                        zcbr->plyrs[j] = (SHORT)nterms;
                } else
                    zcbr->plyrs[j] = (SHORT)nterms;
            }
                    k = 0;
                    for (j = 0; j < zcbr->pcnt; j++)
                        if (zcbr->plyrs[j] < nterms) {
                            zcbr->plyrs[k] = zcbr->plyrs[j];
                            zcbr->plx[k] = zcbr->plx[j];
                            zcbr->ply[k] = zcbr->ply[j];
                            zcbr->oplx[k] = zcbr->oplx[j];
                            zcbr->oply[k] = zcbr->oply[j];
                            zcbr->pgrp[k] = zcbr->pgrp[j];
                            cbvda = (VDABLK*)vdaoff(zcbr->plyrs[j]);
                            cbvda->cbrpos = k;
                            k++;
                        }
                    zcbr->pcnt = k;
                    if (k == 0)
                        zcbr->entype = ' ';
                    break;
            case ' ':
            default: break;
        }
    }
}

SHORT getcbr(VOID)
{
    SHORT i;
    for (i = 0; i < nterms; i++) {
        cbroff(i);
        if (zcbr->entype == ' ')
            break;
    }
    if (i == nterms) {
        shocst("ELWWD S Error", "ELWWD Severe Error:CBR Full");
        cbcleanup();
        for (i = 0; i < nterms; i++) {
            cbroff(i);
            if (zcbr->entype == ' ')
                break;
        }
        if (i == nterms) {
            shocst("ELWWD F Error", "ELWWD Fatal Error:CBR Full");
            terror();
        }
    }
    return(i);
}

VOID mencinit(VOID)
{
    SHORT cbnum;

    cbnum = getcbr();
    if (cbnum != nterms) {
        zcbr->entype = 'm';
        setfight((SHORT)usrnum, cbnum);
        initcbr();
    }
}

VOID pencinit(SHORT othp)
{
    SHORT cbnum;

    cbnum = getcbr();
    if (cbnum != nterms) {
        zcbr->entype = 'p';
        setfight((SHORT)usrnum, cbnum);
        setfight(othp, cbnum);
        initcbr();
    }
}
