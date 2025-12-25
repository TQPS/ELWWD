/*****************************************************************************
 *   ELWWD.C   V0.62                                    Worlds of Darkness   *
 *   Main Routines                                                           *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 03/21/1995         *
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
#include "brkthu.h"
#include "filexfer.h"
#include "majorbbs.h"
#include "elwwdrfx.h"
#include "fsdbbs.h"
#include "elwwd.h"
#include "elwwdtyp.h"
#include "elwwdglb.h"

VOID* cobase;

static CHAR animated[63][100] = {
{"[44mº    [40mÛÜ            ÜÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ[0mÜ        Ü[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ[0mÛÛ[1;30mÜ    Ü[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ[0mÛÛ[1;30mß    ß[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ[0mß        ß[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛß            ßÛ[44m    º[40m"},

{"[44mº    [40mÛÜ            ÜÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ[0mÜ        Ü[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ[0mÛÛ     [1;30mÜ[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ[0mÛÛ     [1;30mß[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ[0mß        ß[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛß            ßÛ[44m    º[40m"},

{"[44mº    [40mÛÜ            ÜÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ         [0mÜ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ[30mÜÜÜÜÜÜÜÜ[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ[30mßßßßßßßß[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛ         [0mß[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛß            ßÛ[44m    º[40m"},

{"[44mº    [40m              ÜÛ[44m    º[40m"},
{"[44mº    [40m[0mÜÜÜÜÜÜÜÜÜÜÜÜÜ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m[0mÛÛÛÛÛÛÛÛÛÛÛÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m[0mÛÛÛÛÛÛÛÛÛÛÛÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m[0mßßßßßßßßßßßßß[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m              ßÛ[44m    º[40m"},

{"[44mº    [40mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[44m    º[40m"},

{"[44mº    [40m              ÜÛ[44m    º[40m"},
{"[44mº    [40m[0mÜ           Ü[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m[0mÛÛ[1;30mÜ       Ü[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m[0mÛÛ[1;30mß       ß[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m[0mß           ß[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m              ßÛ[44m    º[40m"},

{"[44mº    [40m              ÜÛ[44m    º[40m"},
{"[44mº    [40m            [0mÜ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [30;40mÜ         Ü[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [30;40mß         ß[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m            [0mß[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m              ßÛ[44m    º[40m"},

{"[44mº    [40m              ÜÛ[44m    º[40m"},
{"[44mº    [40m            [0mÜ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [30;40mÜÜÜÜÜÜÜÜÜÜÜ[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [30;40mßßßßßßßßßßß[0mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m            [0mß[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m              ßÛ[44m    º[40m"},

{"[44mº    [40m              ÜÛ[44m    º[40m"},
{"[44mº    [40m[0mÜÜÜÜÜÜÜÜÜÜÜÜÜ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m[0mÛÛÛÛÛÛÛ[30;47múúúú[37;40mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m[0mÛÛÛÛÛÛÛ[30;47múúúú[37;40mÛÛ[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m[0mßßßßßßßßßßßßß[1mÛÛÛ[44m    º[40m"},
{"[44mº    [40m              ßÛ[44m    º[40m"},

{"[44mº    [40mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[44m    º[40m"},
{"[44mº    [40mÛ[0;30;47mProg  & Design[1;37mÛ[44m    º[40m"},
{"[44mº    [40mÛ[0;30;47mby  : Alf and [1;37mÛ[44m    º[40m"},
{"[44mº    [40mÛ[0;30;47mZark  Wizard. [1;37mÛ[44m    º[40m"},
{"[44mº    [40mÛ[47m  [0;31;47mFrom  GWW!  [1;37mÛ[44m    º[40m"},
{"[44mº    [40mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[44m    º[40m"},

{"[0;1;44mÌÍ[47m [0;30;47mWorlds of Darkness! [1;37;44mÍÍË[40m"},
{"[44mÊ[47m [0;30;47mHas Finished Loading! [1;37;44mÍÊ[40m"},
{"[44mº                        º[40m"}
};
static CHAR sbuf[4000], dbuf[4000];


struct module wdmd = {         /*  Module interface block                    */
     "",                     /*  Name used to refer to this module         */
     NULL,                   /*  User Logon supplemental routine           */
     wdmain,                 /*  Input routine if selected                 */
     wdcycle,                /*  Status-Input routine if selected          */
     wdyak,                  /*  "injoth" routine for this module          */
     NULL,                   /*  User logoff supplemental routine          */
     wddrop,                 /*  Hangup Lost carrier routine               */
     NULL,                   /*  Midnight Cleanup routine                  */
     NULL,                   /*  delete-account routine                    */
     wdterm                  /*  finish-up (system shut down) routine      */
};


VOID EXPORT init__elwwd(VOID)
{
    USHORT i;

    set_rip_output_fn(td_writeln);
    ver_rip = 0;
    stzcpy(wdmd.descrp, gmdnam("ELWWD.MDF"), MNMSIZ);
    modnum = register_module(&wdmd);
    i = sizeof(CBREC);
    cobase = alcblok((SHORT)nterms, i);
    for (i = 0; i < nterms; i++) {
        cbroff(i);
        zcbr->entype = ' ';
    }
    msgblk = opnmsg("ELWWD.MCV");
    miscitem = dfaOpen("ELWWDOBJ.DAT", sizeof(OBJINF), NULL);      // Objects Database
    dbspells = dfaOpen("ELWWDSPE.DAT", sizeof(SPELLINF), NULL);    // Spells Database
    dbclass = dfaOpen("ELWWDCLA.DAT", sizeof(CLASSINF), NULL);    // Classes Database
    dbrace = dfaOpen("ELWWDRAC.DAT", sizeof(RACEINF), NULL);     // Race Database
    dbmonst = dfaOpen("ELWWDMON.DAT", sizeof(MONSTINF), NULL);    // Monster Database
    dbplayer = dfaOpen("ELWWDPLY.DAT", sizeof(TEMP_PLAYER), NULL); // Player Database
    zmap = (SMAP*)alcmem(sizeof(SMAP));
    zterrain = (SMAP*)alcmem(sizeof(SMAP));
    dclvda(sizeof(VDABLK));
    edtsize = 3000;
    wepbase = (OBJINF*)alczer(sizeof(OBJINF) * MAXOBJ); // weapons
    armbase = (OBJINF*)alczer(sizeof(OBJINF) * MAXOBJ); // armor
    rinbase = (OBJINF*)alczer(sizeof(OBJINF) * MAXOBJ); // rings
    potbase = (OBJINF*)alczer(sizeof(OBJINF) * MAXOBJ); // potions
    stobase = (OBJINF*)alczer(sizeof(OBJINF) * MAXOBJ); // stones
    amubase = (OBJINF*)alczer(sizeof(OBJINF) * MAXOBJ); // amulets
    scrbase = (OBJINF*)alczer(sizeof(OBJINF) * MAXOBJ); // scrolls
    przbase = (OBJINF*)alczer(sizeof(OBJINF) * MAXPRIZ);
    wizspell = (SPELLINF*)alczer(sizeof(SPELLINF) * MAXSPELL);
    clerspell = (SPELLINF*)alczer(sizeof(SPELLINF) * MAXSPELL);
    classbase = (CLASSENT*)alczer(sizeof(CLASSENT) * MAXCLASS);
    racebase = (RACENT*)alczer(sizeof(RACENT) * MAXRACES);
    cantrun = loadmaps();
    cantrun |= loaddb();
    cantrun |= loadmonst();
    cantrun |= loadrclass();
    setmbk(msgblk);
    reload_cost = lngopt(RESCOST, 0, 2000000L);
    rstmbk();
    ztimerf = FALSE;
    for (i = 0; i < 256; i++) {
        snooze[i] = FALSE;
        ingame[i] = FALSE;
    }
    randomize();
    if (!cantrun) {
        i = locstorez('D');                   // clerics
        if (i > 0) {
            zcler = (STORE*)alczer(sizeof(STORE) * i);
            initclers();
            clerkick();
        } else zclercnt = 0;
        i = locstorez('J');                   // weapons
        if (i > 0) {
            zwep = (WSTOR*)alczer(sizeof(WSTOR) * i);
            initweps();
            wepkick();
        } else zwepcnt = 0;
        i = locstorez('C');                   // wizard guilds
        if (i > 0) {
            zwiz = (STORE*)alczer(sizeof(STORE) * i);
            initwiz();
            wizkick();
        } else zwizcnt = 0;
    }
    initdrop();
    initwwall();

    mwaitt = 60;                          //time to move in fite
    mench = 4;                            //chace of enc
    iwpos = 0;

    animate();
    if (!cantrun) {
        strcpy(vernum, "0.62");
        build_icons();
        gamestat = 3;
        shocst(spr("ELW Worlds of Darkness v%s", vernum), "Copyright (C) 2025 Elwynor Technologies - www.elwynor.com");
    } else {
        shocst("ELW Worlds of Darkness Inactive", "Worlds of Darkness Load Errors");
        gamestat = 0;
    }
}

VOID animate(VOID)
{
    //CHAR *frzseg();  /* RH: Modified in WG32 port */
    CHAR scrnon = 0;
    SHORT sx, sy, x, xbase = 21, ybase = 11, ctr1;
    LONG ctr;

    if (random(50) < 1) {
        sx = (SHORT)curcurx();
        sy = (SHORT)curcury();
        //movmem(frzseg(),sbuf,4000); /* RH: this was an unusual use of movmem - usually this was scn2mem(frzseg(),sbuf,4000);
        scn2mem(sbuf, 0, 4000);

        ansion(1);
        for (x = 0; x < 10; x++) {
            movmem(sbuf, dbuf, 4000);
            setwin(dbuf, xbase, ybase - 1, xbase + 25, ybase + 6, 0);
            printfat(xbase, ybase - 1, animated[60]);
            printfat(xbase, ybase + 6, animated[62]);
            printfat(xbase, ybase + 7, animated[61]);
            for (ctr1 = 0; ctr1 < 6; ctr1++) {
                printfat(xbase, ybase + ctr1, animated[ctr1 + scrnon]);
            }
            rstwin();
            //movmem(dbuf,frzseg(),4000);
            mem2scn(dbuf, 0, 4000);
            scrnon += 6;
            for (ctr = 0L; ctr < 1500000L; ctr++) {
                ctr = ctr;
            }
        }
        for (ctr = 0L; ctr < 7000000L; ctr++) {
            ctr = ctr;
        }
        ansion(0);
        //movmem(sbuf,frzseg(),4000);
        mem2scn(sbuf, 0, 4000);
        locate(sx, sy);
        setatr(0x07);
        //unfrez();
    }
}

VOID initplayer(VOID)
{
    USHORT i, j;
    CHAR temp[3] = { 0,0,0 };

    prow = 41;
    pcol = 36;
    plevel = 8;
    pdirect = 3;
    stzcpy(zplyr->name, uaptr->userid, 30);
    zplyr->cash = 50;
    zplyr->currhp = 30;
    zplyr->maxhp = 30;
    zplyr->level = 1;
    zplyr->currmp = 15;
    zplyr->maxmp = 15;
    zplyr->age = 18;
    zplyr->new_age = 18;
    zplyr->lvl_drain = 0;
    zplyr->encloss = zplyr->enckills = 0;
    zplyr->arrows = zplyr->rocks = zplyr->darts = 0;
    zplyr->exp = zplyr->bank = zplyr->loan = 0;
    zplyr->intrest = zplyr->lowinvest = zplyr->medinvest = 0;
    zplyr->highinvest = 0;
    if (ynopt(SCOMP)) zplyr->condition[8] = TRUE;
    for (i = 0; i < MAXPOBJC; i++) {
        zvda->pstuff[i].objname[0] = 0;
        zplyr->equip[i] = 0;
    }
    for (i = 0; i < 30; i++)
        zplyr->condition[i] = 0;
    for (i = 0; i < 9; i++) {
        zplyr->mage_new[i] = zplyr->cleric_new[i] = 0;
        for (j = 0; j < 5; j++)
            zplyr->mage[i * 5 + j] = zplyr->cleric[i * 5 + j] = NOTFOUND;
    }
    for (i = 0; i < 9; i++) {
        temp[1] = 0;
        temp[0] = zvda->pclass.mage[0][i];
        zplyr->mage_new[i] = (SHORT)atoi(temp);
        temp[1] = 0;
        temp[0] = zvda->pclass.priest[0][i];
        zplyr->cleric_new[i] = (SHORT)atoi(temp);
    }
    j = 1;
    while (j != 0) {
        if (wepbase[iwpos].ocost < 60 && wepbase[iwpos].otype == 0 &&
            (wepbase[iwpos].ospot == 5 || wepbase[iwpos].ospot == 6))
            j = 0;
        else {
            iwpos++;
            if (iwpos >= objcnt[0])
                iwpos = 0;
        }
    }
    zvda->pstuff[0] = wepbase[iwpos];
    zplyr->equip[0] = 1;
    zplyr->condition[20] = 10;
    if (ynopt(SCOMP)) zplyr->condition[8] = TRUE;
    if (ynopt(SLOC)) zplyr->condition[9] = TRUE;
#ifdef ZARKALF
    if (sameas("Alfred", zplyr->name)) {
        // for (i=0; i<9; i++)
        //  zplyr->cleric_new[i]=5;
        prow = 4;
        pcol = 4;
        plevel = 1;
        zplyr->cash = 15000;
        zplyr->currmp = 150;
        zplyr->maxmp = 150;
    }
#endif
}

VOID plinit(VOID)
{
    zvda->movingaround = TRUE;
    zvda->spelltrue = FALSE;
    zvda->lmode = 0;
    zvda->specialrip = FALSE;
    zvda->forground = 0;
    zvda->background = 20;
    zvda->infight = FALSE;
    zvda->abort = TRUE;
    zvda->paging = FALSE;
    zvda->neverdraw = TRUE;
    zvda->redo = FALSE;
    zvda->lastwindow = 0;
    zvda->buywindow = 0;
    zvda->ripclr1 = 5;
    zvda->ripclr2 = 10;
    zvda->noyano = FALSE;
    zvda->endgame = FALSE;
    zvda->dead = FALSE;
    zvda->party = (SHORT)usrnum;
    zvda->memcnt = 1;
    zvda->gstate = ISACTIVE;
    zvda->members[0] = (SHORT)usrnum;
    zvda->myuser = usrptr;
    zvda->oldont = FALSE;
    zvda->nstat = TRUE;
    zvda->stmode = 0;
}

VOID disprace(VOID)
{

    prfmsg(DISRAC, zvda->prace.name,
        zvda->scan,
        spr("%d", zvda->prace.cast),
        spr("%d", zvda->prace.mr),
        spr("%d", zvda->prace.modify[0]),
        spr("%d", zvda->prace.maxability[0]),
        spr("%d", zvda->prace.modify[1]),
        spr("%d", zvda->prace.maxability[1]),
        spr("%d", zvda->prace.earth),
        spr("%d", zvda->prace.modify[2]),
        spr("%d", zvda->prace.maxability[2]),
        spr("%d", zvda->prace.fire),
        spr("%d", zvda->prace.modify[3]),
        spr("%d", zvda->prace.maxability[3]),
        spr("%d", zvda->prace.water),
        spr("%d", zvda->prace.modify[4]),
        spr("%d", zvda->prace.maxability[4]),
        spr("%d", zvda->prace.air),
        spr("%d", zvda->prace.modify[5]),
        spr("%d", zvda->prace.maxability[5]),
        spr("%d", zvda->prace.modify[6]),
        spr("%d", zvda->prace.maxability[6]),
        spr("%d", zvda->prace.modify[7]));
    outprf(usrnum);
}

VOID dispclass(VOID)
{
    prfmsg(DISCLA, zvda->pclass.name,
        zvda->scan,
        zvda->pclass.hp,
        zvda->pclass.mage[0],
        zvda->pclass.priest[0],
        zvda->pclass.exp[0],
        zvda->pclass.mage[1],
        zvda->pclass.priest[1],
        zvda->pclass.exp[1],
        zvda->pclass.mp,
        zvda->pclass.mage[2],
        zvda->pclass.priest[2],
        zvda->pclass.exp[2],
        zvda->pclass.mage[3],
        zvda->pclass.priest[3],
        zvda->pclass.exp[3],
        zvda->pclass.mage[4],
        zvda->pclass.priest[4],
        zvda->pclass.exp[4],
        cl1[zvda->pclass.objects[0]],
        zvda->pclass.mage[5],
        zvda->pclass.priest[5],
        zvda->pclass.exp[5],
        cl1[zvda->pclass.objects[1]],
        zvda->pclass.mage[6],
        zvda->pclass.priest[6],
        zvda->pclass.exp[6],
        cl1[zvda->pclass.objects[2]],
        zvda->pclass.mage[7],
        zvda->pclass.priest[7],
        zvda->pclass.exp[7],
        cl1[zvda->pclass.objects[3]],
        zvda->pclass.mage[8],
        zvda->pclass.priest[8],
        zvda->pclass.exp[8],
        cl1[zvda->pclass.objects[4]],
        zvda->pclass.mage[9],
        zvda->pclass.priest[9],
        zvda->pclass.exp[9],
        cl1[zvda->pclass.objects[5]],
        zvda->pclass.mage[10],
        zvda->pclass.priest[10],
        zvda->pclass.exp[10],
        cl1[zvda->pclass.objects[6]],
        zvda->pclass.mage[11],
        zvda->pclass.priest[11],
        zvda->pclass.exp[11],
        cl1[zvda->pclass.objects[7]],
        zvda->pclass.mage[12],
        zvda->pclass.priest[12],
        zvda->pclass.exp[12],
        zvda->pclass.mage[13],
        zvda->pclass.priest[13],
        zvda->pclass.exp[13],
        zvda->pclass.mage[14],
        zvda->pclass.priest[14],
        zvda->pclass.exp[14]);
    outprf(usrnum);
}

VOID dispmain(VOID)
{
    if (hasmkey(WODEDIT)) ansimenu(1, 1, 43, 9, "ABCDEFGHIJ", 3, MUMENU);
    else ansimenu(1, 1, 43, 8, "ABCDEFGHI", 3, MMENU);
}

SHORT wdmain(VOID)
{
    SHORT rc = 1, li, lj, level, myrc, editskip = 0, ctr;
    CHAR holdchr, yakline[159], yaktxt[80];
    ULONG wpos;

    if ((gamestat == 0) && (channel[usrnum] != 0)) {
        prf("\n\nSorry, but Worlds of Darkness is disabled. Let your SysOp know!\n");
        outprf(usrnum);
        return(0);
    }
    zvda = (VDABLK*)vdaptr;
    zplyr = &zvda->plyr;
    zpobj = zvda->pstuff;
    uaptr = uacoff(usrnum);
    if (ingame[usrnum] && zvda->incycle)
        return(1);
    //shocst(spr("WD Main : %d",usrptr->substt)," ");
    setmbk(msgblk);
    switch (usrptr->substt) {
        case 0:
            zvda->obsize = (USHORT)btuoba(usrnum);
            zvda->curlang = (SHORT)clingo;
            if (!usaptr->ansifl & ANSON) {
                prf("\n\nsorry, must be in ansi to play....\n\n");
                outprf(usrnum);
                rc = 0;
                break;
            }
            if (cantrun == 50) {
                prfmsg(NOENTRY);
                outprf(usrnum);
                rc = 0;
            } else {
                ingame[usrnum] = TRUE;
                //usrptr->flags|=NOINJO;
                usrptr->flags |= NOGLOB;
                zvda->rip = FALSE;
                usrptr->substt = 1;
                zvda->nxtstt = 0;
                //else {
                //  prfmsg(TITLE);
                //  outprf(usrnum);
                //  usrptr->substt=2;
                //  zvda->redraw=TRUE;
                setcycle();
                btutrg(usrnum, 0);
            }
            break;
        case 1:
            rc = 0;
            ingame[usrnum] = FALSE;
            break;
        case 3:
            rc = 0;  /* exit case */
            ingame[usrnum] = FALSE;
            break;
        case 4:
            // Checking for rip using zvda->nxtstt..................
            // Loop through until all icons are checked.
            // First check WODTEST.TXT if this is current
            // no longer need to continue checking.
            rc = check_icons();
            break;
        case 5:
            if (margc == 1) {
                level = (SHORT)atoi(margv[0]);
                myrc = decompress(level, 'm');
                if (myrc)
                    prf("map failed to decomp\n");
                for (li = 1; li <= 50; li++) {
                    for (lj = 1; lj <= 70; lj++) {
                        prf("%c", zmap->lvl[level].map[li][lj]);
                    }
                    prf(" \n");
                }
                outprf(usrnum);
            } else {
                prf("Hit Return");
                outprf(usrnum);
            }
            usrptr->substt = 7;
            break;
#ifdef ZARKALF
        case 6:
            if (margc == 1) {
                level = atoi(margv[0]);
                //dsplever(level);
                dspxport(level);
            } else {
                prf("Hit Return");
                outprf(usrnum);
            }
            usrptr->substt = 7;
            break;
        case 7:
            usrptr->substt = 3;
            zvda->mnukey = 9;
            setcycle();
            break;
#endif
        case 10:
            if (sameas(margv[0], "1")) {        // Object Editor
                prfmsg(OBJMNU, "Object", "Object");
                outprf(usrnum);
                usrptr->substt = 11;
            } else if (sameas(margv[0], "2")) {        // Spell Editor
                prfmsg(OBJMNU, "Spell", "Spell");
                outprf(usrnum);
                usrptr->substt = 14;
            } else if (sameas(margv[0], "3")) {        // Race Editor
                prfmsg(OBJMNU, "Race", "Race");
                outprf(usrnum);
                usrptr->substt = 16;
            } else if (sameas(margv[0], "4")) {        // Class Editor
                prfmsg(OBJMNU, "Class", "Class");
                outprf(usrnum);
                usrptr->substt = 18;
            } else if (sameas(margv[0], "5")) {        // Monster Editor
                prfmsg(OBJMNU, "Monster", "Monster");
                outprf(usrnum);
                usrptr->substt = 20;
            } else {
#ifdef ZARKALF
                zvda->mnukey = 9;
                usrptr->substt = 3;
#else
                dispmain();
#endif
                setcycle();
            }
            break;
        case 11:
            if (sameas(margv[0], "e")) {  // Object Editor
                prfmsg(EDOBJ1, "Object");  // Edit what object??
                outprf(usrnum);
                usrptr->substt = 12;
                break;
            }
            if (sameas(margv[0], "l")) {
                outprf(usrnum);
                usrptr->substt = 200;
                zvda->retstt = 11;
                strcpy(zvda->dblist, "Object");
                zvda->curpos[0] = 'ê';
                setcycle();
                break;
            }
            if (sameas(margv[0], "x")) {
                usrptr->substt = 10;
                prfmsg(OBJDAT);
                outprf(usrnum);
                break;
            }
            prfmsg(OBJMNU, "Object", "Object");
            outprf(usrnum);
            break;
        case 12:
            if (margc > 0) {
                rstrin();
                dfaSetBlk(miscitem);
                if (dfaAcqEQ(&objinf, input, 0)) {
                    prepfsd(EDITOBJE, 1, FALSE);
                    fsdrhd("Object Editor");
                    fsdbkg(fsdrft());
                    fsdscb->flddat[0].flags |= FFFAVD;
                    fsdego(vfyadn, fsd_finish);
                } else {
                    strcpy(objinf.objname, input);
                    prepfsd(EDITOBJE, 1, TRUE);
                    fsdrhd("Object Editor");
                    fsdbkg(fsdrft());
                    fsdscb->flddat[0].flags |= FFFAVD;
                    fsdego(vfyadn, fsd_finish);
                }
                dfaRstBlk();
            } else {
                prfmsg(EDOBJ1, "Spell");
            }
            outprf(usrnum);
            break;
        case 14:
            // Spell Editor
            if (sameas(margv[0], "e")) {
                prfmsg(EDOBJ1, "Spell");  // Edit what object??
                outprf(usrnum);
                usrptr->substt = 15;
                break;
            }
            if (sameas(margv[0], "l")) {
                outprf(usrnum);
                usrptr->substt = 200;
                zvda->retstt = 14;
                strcpy(zvda->dblist, "Spell");
                zvda->curpos[0] = 'ê';
                setcycle();
                break;
            }
            if (sameas(margv[0], "x")) {
                usrptr->substt = 10;
                prfmsg(OBJDAT);
                outprf(usrnum);
                break;
            }
            prfmsg(OBJMNU, "Spell", "Spell");
            outprf(usrnum);
            break;
        case 15:
            if (margc > 0) {
                rstrin();
                dfaSetBlk(dbspells);
                if (dfaAcqEQ(&spellinf, input, 0)) {
                    spfsd(EDITSPEL, 1, FALSE);
                    fsdrhd("Spell Editor");
                    fsdbkg(fsdrft());
                    fsdscb->flddat[0].flags |= FFFAVD;
                    fsdego(vfyadn, spfsd_finish);
                } else {
                    strcpy(spellinf.spellname, input);
                    spfsd(EDITSPEL, 1, TRUE);
                    fsdrhd("Spell Editor");
                    fsdbkg(fsdrft());
                    fsdscb->flddat[0].flags |= FFFAVD;
                    fsdego(vfyadn, spfsd_finish);
                }
                dfaRstBlk();
            } else {
                prfmsg(EDOBJ1, "Spell");
            }
            outprf(usrnum);
            break;
        case 16:
            //  Race Editor
            if (sameas(margv[0], "e")) {
                prfmsg(EDOBJ1, "Race");  // Edit what??
                usrptr->substt = 17;
                outprf(usrnum);
                break;
            }
            if (sameas(margv[0], "l")) {
                outprf(usrnum);
                usrptr->substt = 200;
                zvda->retstt = 16;
                strcpy(zvda->dblist, "Race");
                zvda->curpos[0] = 'ê';
                setcycle();
                break;
            }
            if (sameas(margv[0], "x")) {
                usrptr->substt = 10;
                prfmsg(OBJDAT);
                outprf(usrnum);
                break;
            }
            prfmsg(OBJMNU, "Race", "Race");
            outprf(usrnum);
            break;
        case 17:
            if (margc > 0) {
                rstrin();
                dfaSetBlk(dbrace);
                if (dfaAcqEQ(&raceinf, input, 0)) {
                    rafsd(EDITRACE, 1, FALSE);
                    fsdrhd("Race Editor");
                    fsdbkg(fsdrft());
                    fsdscb->flddat[0].flags |= FFFAVD;
                    fsdego(vfyadn, rafsd_finish);
                } else {
                    strcpy(raceinf.name, input);
                    rafsd(EDITRACE, 1, TRUE);
                    fsdrhd("Race Editor");
                    fsdbkg(fsdrft());
                    fsdscb->flddat[0].flags |= FFFAVD;
                    fsdego(vfyadn, rafsd_finish);
                }
                dfaRstBlk();
            } else {
                prfmsg(EDOBJ1, "Race");
            }
            outprf(usrnum);
            break;
        case 18:
            //  Class Editor
            if (sameas(margv[0], "e")) {
                prfmsg(EDOBJ1, "Class");  // Edit what??
                usrptr->substt = 19;
                outprf(usrnum);
                break;
            }
            if (sameas(margv[0], "l")) {
                outprf(usrnum);
                usrptr->substt = 200;
                zvda->retstt = 18;
                strcpy(zvda->dblist, "Class");
                zvda->curpos[0] = 'ê';
                setcycle();
                break;
            }
            if (sameas(margv[0], "x")) {
                usrptr->substt = 10;
                prfmsg(OBJDAT);
                outprf(usrnum);
                break;
            }
            prfmsg(OBJMNU, "Class", "Class");
            outprf(usrnum);
            break;
        case 19:
            if (margc > 0) {
                rstrin();
                dfaSetBlk(dbclass);
                if (dfaAcqEQ(&classinf, input, 0)) {
                    clfsd(EDITCLAS, 1, FALSE);
                    fsdrhd("Class Editor");
                    fsdbkg(fsdrft());
                    fsdscb->flddat[0].flags |= FFFAVD;
                    fsdego(vfyadn, clfsd_finish);
                } else {
                    strcpy(classinf.name, input);
                    clfsd(EDITCLAS, 1, TRUE);
                    fsdrhd("Class Editor");
                    fsdbkg(fsdrft());
                    fsdscb->flddat[0].flags |= FFFAVD;
                    fsdego(vfyadn, clfsd_finish);
                }
                dfaRstBlk();
            } else {
                prfmsg(EDOBJ1, "Class");
            }
            outprf(usrnum);
            break;
        case 20:
            //  Monster Editor
            if (sameas(margv[0], "e")) {
                prfmsg(EDOBJ1, "Monster");  // Edit what??
                usrptr->substt = 21;
                outprf(usrnum);
                break;
            }
            if (sameas(margv[0], "l")) {
                outprf(usrnum);
                usrptr->substt = 200;
                zvda->retstt = 20;
                strcpy(zvda->dblist, "Monster");
                zvda->curpos[0] = 'ê';
                setcycle();
                break;
            }
            if (sameas(margv[0], "x")) {
                usrptr->substt = 10;
                prfmsg(OBJDAT);
                outprf(usrnum);
                break;
            }
            prfmsg(OBJMNU, "Monster", "Monster");
            outprf(usrnum);
            break;
        case 21:
            if (margc > 0) {
                rstrin();
                dfaSetBlk(dbmonst);
                if (dfaAcqEQ(&monstinf, input, 0)) {
                    mofsd(EDITMONS, 1, FALSE);
                    fsdrhd("Monster Editor");
                    fsdbkg(fsdrft());
                    fsdscb->flddat[0].flags |= FFFAVD;
                    fsdego(vfyadn, mofsd_finish);
                } else {
                    strcpy(monstinf.name, input);
                    mofsd(EDITMONS, 1, TRUE);
                    fsdrhd("Monster Editor");
                    fsdbkg(fsdrft());
                    fsdscb->flddat[0].flags |= FFFAVD;
                    fsdego(vfyadn, mofsd_finish);
                }
                dfaRstBlk();
            } else {
                prfmsg(EDOBJ1, "Monster");
            }
            outprf(usrnum);
            break;
        case 22:
            usrptr->substt = 22;
            rstrin();
            if (strlen(input) > 2) {  // Typed in a name......
                switch (zvda->retstt) {
                    case 11:
                        dfaSetBlk(miscitem);
                        if (dfaAcqEQ(&objinf, input, 0)) {
                            editskip = 1;
                            prepfsd(EDITOBJE, 1, FALSE);
                            fsdrhd("Object Editor");
                            fsdbkg(fsdrft());
                            fsdscb->flddat[0].flags |= FFFAVD;
                            fsdego(vfyadn, fsd_finish);
                        }
                        dfaRstBlk();
                        break;
                    case 14:
                        dfaSetBlk(dbspells);
                        if (dfaAcqEQ(&spellinf, input, 0)) {
                            editskip = 1;
                            spfsd(EDITSPEL, 1, FALSE);
                            fsdrhd("Spell Editor");
                            fsdbkg(fsdrft());
                            fsdscb->flddat[0].flags |= FFFAVD;
                            fsdego(vfyadn, spfsd_finish);
                        }
                        dfaRstBlk();
                        break;
                    case 16:
                        dfaSetBlk(dbrace);
                        if (dfaAcqEQ(&raceinf, input, 0)) {
                            editskip = 1;
                            rafsd(EDITRACE, 1, FALSE);
                            fsdrhd("Race Editor");
                            fsdbkg(fsdrft());
                            fsdscb->flddat[0].flags |= FFFAVD;
                            fsdego(vfyadn, rafsd_finish);
                        }
                        dfaRstBlk();
                        break;
                    case 18:
                        dfaSetBlk(dbclass);
                        if (dfaAcqEQ(&classinf, input, 0)) {
                            editskip = 1;
                            clfsd(EDITCLAS, 1, FALSE);
                            fsdrhd("Class Editor");
                            fsdbkg(fsdrft());
                            fsdscb->flddat[0].flags |= FFFAVD;
                            fsdego(vfyadn, clfsd_finish);
                        }
                        dfaRstBlk();
                        break;
                    case 20:
                        dfaSetBlk(dbmonst);
                        if (dfaAcqEQ(&monstinf, input, 0)) {
                            editskip = 1;
                            mofsd(EDITMONS, 1, FALSE);
                            fsdrhd("Monster Editor");
                            fsdbkg(fsdrft());
                            fsdscb->flddat[0].flags |= FFFAVD;
                            fsdego(vfyadn, mofsd_finish);
                        }
                        dfaRstBlk();
                        break;
                }
                if (editskip) {
                    outprf(usrnum);
                    return(1);
                }
            }
            parsin();
            holdchr = 0;
            if (margc != 0) {
                holdchr = margv[0][0];
            }
            if (holdchr != 0) {
                if (holdchr > 'Z') {
                    holdchr = holdchr - 32;
                }
                switch (holdchr) {
                    default:
                        usrptr->substt = zvda->nxtstt;
                        prf("\n");
                        outprf(usrnum);
                        setcycle();
                        break;
                    case 'Q':
                        usrptr->substt = zvda->retstt;
                        prf("\n");
                        switch (zvda->retstt) {
                            case 11:
                                prfmsg(OBJMNU, "Object", "Object");
                                break;
                            case 14:
                                prfmsg(OBJMNU, "Spell", "Spell");
                                break;
                            case 16:
                                prfmsg(OBJMNU, "Race", "Race");
                                break;
                            case 18:
                                prfmsg(OBJMNU, "Class", "Class");
                                break;
                            case 20:
                                prfmsg(OBJMNU, "Monster", "Monster");
                                break;
                        }
                        outprf(usrnum);
                        break;
                }
            } else {
                usrptr->substt = zvda->nxtstt;
                prf("\n");
                outprf(usrnum);
                setcycle();
            }
            break;
            /* Chatting zchat*/
        case 30:
            if (zvda->party != usrnum)
                zldr = (VDABLK*)vdaoff(zvda->party);
            else
                zldr = zvda;
            /* Give Stuff give xx pp to xx */
            if (margc == 5 && sameas(margv[0], "/give")) {
                if (sameas(margv[2], "pp") && sameas(margv[3], "to")) {
                    li = (SHORT)atoi(margv[4]);
                    wpos = (ULONG)atol(margv[1]);
                    if (wpos <= zplyr->cash) {
                        if (li < nterms && ingame[li] && li != usrnum) {
                            xlvda = (VDABLK*)vdaoff(li);
                            if (xlvda->gstate == INCHAT &&
                                xlvda->plyr.curlvl == plevel &&
                                xlvda->plyr.row == prow &&
                                xlvda->plyr.col == pcol) {
                                zplyr->cash -= wpos;
                                xlvda->plyr.cash += wpos;
                                prfmsg(CGVN);
                                outprf(usrnum);
                                clrprf();
                                prfmsg(GVUC, zplyr->name, l2as(wpos));
                                outprf(li);
                                clrprf();
                            } else {
                                prfmsg(NHERE);
                                outprf(usrnum);
                            }
                        } else {
                            prfmsg(NHERE);
                            outprf(usrnum);
                        }
                    } else {
                        prfmsg(NCTGV);
                        outprf(usrnum);
                    }
                } else {
                    prfmsg(SYNTX);
                    outprf(usrnum);
                }
                break;
            }
            if (margc == 1 || margc == 2) {
                /* Exit Chat */
                if (sameas(margv[0], "/x")) {
                    if (zvda->party != usrnum) {
                        qparty((SHORT)usrnum);
                        setcycle();
                        restplay();
                    } else {
                        for (li = 0; li < zvda->memcnt; li++) {
                            lj = zvda->members[li];
                            if (ingame[lj]) {
                                xlvda = (VDABLK*)vdaoff(lj);
                                xlvda->myuser->substt = 37;
                                xlvda->gstate = PLAYING;
                                xlvda->plyr.direct = pdirect;
                                xlvda->plyr.curlvl = plevel;
                                xlvda->plyr.row = prow;
                                xlvda->plyr.col = pcol;
                                xlvda->pdraw = FALSE;
                                xlvda->incycle = TRUE;
                                btutrg(lj, 4);
                                btuinj(lj, CYCLE);
                                btuxnf(lj, 0, 0);
                                btupbc(lj, 0);
                            }
                        }
                    }
                    break;
                }
                /* Show Help command..... */
                if (sameas(margv[0], "/?")) {
                    prfmsg(CHATHELP);
                    outprf(usrnum);
                    break;
                }
                /* List Party Users */
                if (sameas(margv[0], "/lp")) {
                    prf("Chn  User\n");
                    outprf(usrnum);
                    for (li = 0; li < zldr->memcnt; li++) {
                        lj = zldr->members[li];
                        if (ingame[lj]) {
                            xlvda = (VDABLK*)vdaoff(lj);
                            if (xlvda->memcnt > 1)
                                prf("%d L %s is present.\n", lj, xlvda->plyr.name);
                            else
                                prf("%d   %s is present.\n", lj, xlvda->plyr.name);
                            outprf(usrnum);
                        }
                    }
                    break;
                }
                /* List Users */
                if (sameas(margv[0], "/l")) {
                    prf("Chn  User\n");
                    outprf(usrnum);
                    for (li = 0; li < nterms; li++)
                        if (ingame[li]) {
                            xlvda = (VDABLK*)vdaoff(li);
                            if (xlvda->gstate == INCHAT &&
                                xlvda->plyr.curlvl == plevel &&
                                xlvda->plyr.row == prow &&
                                xlvda->plyr.col == pcol) {
                                if (xlvda->memcnt > 1)
                                    prf("%d L %s is present.\n", li, xlvda->plyr.name);
                                else
                                    prf("%d   %s is present.\n", li, xlvda->plyr.name);
                                outprf(usrnum);
                            }
                        }
                    break;
                }
                /* Extend Invite */
                if (sameas(margv[0], "/i") && zvda->party == usrnum) {
                    li = (SHORT)atoi(margv[1]);
                    if (li < nterms && ingame[li] && li != usrnum) {
                        xlvda = (VDABLK*)vdaoff(li);
                        if (xlvda->gstate == INCHAT &&
                            xlvda->plyr.curlvl == plevel &&
                            xlvda->plyr.row == prow &&
                            xlvda->plyr.col == pcol)
                            if (xlvda->party != usrnum) {
                                prfmsg(INVITE, zplyr->name, usrnum);
                                outprf(li);
                                xlvda->invf[usrnum] = 1;
                                prfmsg(INVSNT);
                                outprf(usrnum);
                            } else {
                                prfmsg(INURP);
                                outprf(usrnum);
                            }
                    } else {
                        prfmsg(NHERE);
                        outprf(usrnum);
                    }
                    break;
                }
                /* Join Invite */
                if (sameas(margv[0], "/j")) {
                    li = (SHORT)atoi(margv[1]);
                    if (ptest()) {
                        prfmsg(MLEEV);
                        outprf(usrnum);
                        break;
                    }
                    if (li < nterms && zvda->invf[li] == 1 && li != usrnum)
                        if (ingame[li]) {
                            xlvda = (VDABLK*)vdaoff(li);
                            if (xlvda->gstate == INCHAT && xlvda->party == li &&
                                xlvda->plyr.curlvl == plevel &&
                                xlvda->plyr.row == prow &&
                                xlvda->plyr.col == pcol) {
                                zvda->party = li;
                                xlvda->members[xlvda->memcnt] = (SHORT)usrnum;
                                xlvda->memcnt++;
                                zvda->invf[li] = 0;
                                clrprf();
                                prfmsg(HJOIN, zplyr->name);
                                xparty(li);
                            }
                        } else {
                            prf("That user has left.\n");
                            zvda->invf[li] = 0;
                            outprf(usrnum);
                        } else {
                            prfmsg(NOVITE);
                            outprf(usrnum);
                        }
                        break;
                }
                /* Leave Party */
                if (sameas(margv[0], "/q")) {
                    if (zvda->party != usrnum) {
                        li = zvda->party;
                        qparty((SHORT)usrnum);
                        prfmsg(QPARTY);
                        outprf(usrnum);
                        clrprf();
                        prfmsg(HLEFT, zplyr->name);
                        xparty(li);
                    } else
                        if (zvda->memcnt > 1) {
                            clrprf();
                            prfmsg(DISBAND);
                            while (zvda->memcnt > 1) {
                                outprf(zvda->members[zvda->memcnt - 1]);
                                qparty(zvda->members[zvda->memcnt - 1]);
                            }
                            outprf(usrnum);
                        } else {
                            prfmsg(NPARTY);
                            outprf(usrnum);
                        }
                    break;
                }
                /* Start Fight */
                if (sameas(margv[0], "/a")) {
                    if (margc == 2)
                        if (zvda->party != usrnum) {
                            prfmsg(NOSTART);
                            outprf(usrnum);
                        } else {
                            li = (SHORT)atoi(margv[1]);
                            if (li < nterms && ingame[li] && li != usrnum) {
                                xlvda = (VDABLK*)vdaoff(li);
                                if (xlvda->gstate == INCHAT && xlvda->party == li &&
                                    xlvda->plyr.curlvl == plevel &&
                                    xlvda->plyr.row == prow &&
                                    xlvda->plyr.col == pcol)
                                    if (xlvda->party != usrnum)
                                        pencinit(xlvda->party);
                                    else {
                                        prfmsg(NOTU);
                                        outprf(usrnum);
                                    } else {
                                        prfmsg(NHERE);
                                        outprf(usrnum);
                                    }
                            } else {
                                prfmsg(NOTU);
                                outprf(usrnum);
                            }
                        } else {
                            prfmsg(BADJOB);
                            outprf(usrnum);
                        }
                        break;
                }
            }
            rstrin();
            clrprf();
            if (input[0] == '\\') {
                input[0] = ' ';
                prf("P<%s>%s \n", zplyr->name, input);
                xlounge('p');
                prf("--Party Message Sent--\n");
            } else {
                prf("<%s> %s \n", zplyr->name, input);
                xlounge('a');
                prf("--Message Sent--\n");
            }
            outprf(usrnum);
            break;
            /* Notify */
        case 33:
            rstrin();
            if (inplen > 1) {
                stzcpy(zvda->yakusr, input, 30);
                if (onsys(zvda->yakusr)) {
                    delinm();
                    prfmsg(EUSRT);
                    outprf(usrnum);
                    btumil(usrnum, 42);
                    usrptr->substt = 34;
                } else {
                    prfmsg(NOTONL);
                    outprf(usrnum);
                    setcycle();
                    usrptr->substt = 20;
                }
            } else {
                delinm();
                setcycle();
                usrptr->substt = 20;
            }
            break;
        case 34:
            rstrin();
            if (inplen > 1) {
                if (onsys(zvda->yakusr)) {
                    stzcpy(yakline, usaptr->userid, 30);
                    strcat(yakline, ":");
                    stzcpy(yaktxt, input, 79);
                    strcat(yakline, yaktxt);
                    clrprf();
                    prf("%s", yakline);
                    li = (SHORT)injoth();
                    clrprf();
                    delinm();
                    if (li)
                        prfmsg(EUSNT);
                    else
                        prfmsg(EUNSNT);
                    outprf(usrnum);
                } else {
                    prfmsg(NOTONL);
                    outprf(usrnum);
                }
            } else {
                delinm();
            }
            setcycle();
            usrptr->substt = 20;
            break;
            /* WWall  */
        case 38:
            rstrin();
            if (inplen > 1) {
                stzcpy(yakline, input, 73);
                if (wwall != NULL) {
                    wpos = (plevel - 1) * MAPHEIGHT * MAPWIDTH + (prow - 1) * MAPWIDTH + (pcol - 1);
                    wpos *= 73;
                    if (!fseek(wwall, wpos, SEEK_SET)) {
                        lj = (SHORT)fwrite(yakline, 73, 1, wwall);
                        if (lj) {
                            delinm();
                            prfmsg(ADMHDW);
                            outprf(usrnum);
                        } else {
                            prfmsg(NOSCRB);
                            outprf(usrnum);
                            shocst("ELWWD WWWrt Error", "ELWWD DrMsg Write Failed");
                        }
                    } else
                        shocst("ELWWD WWSeek Error", "ELWWD DrMsg Seek Failed");
                } else {
                    prfmsg(NOSCRB);
                    outprf(usrnum);
                }
            } else {
                delinm();
            }
            setcycle();
            usrptr->substt = 20;
            break;
            /* Tavern Chat */
        case 45:
            if (margc == 1 || margc == 2) {
                /* Show Help command..... */
                if (sameas(margv[0], "/?")) {
                    prfmsg(TAVHELP);
                    outprf(usrnum);
                    break;
                }
                if (sameas(margv[0], "/l")) {
                    prf("Chn  User\n");
                    outprf(usrnum);
                    for (li = 0; li < nterms; li++)
                        if (ingame[li]) {
                            xlvda = (VDABLK*)vdaoff(li);
                            if (xlvda->gstate == TAVCHT) {
                                if (xlvda->plyr.curlvl == plevel &&
                                    xlvda->plyr.row == prow &&
                                    xlvda->plyr.col == pcol)
                                    prf("%d   %s is present.\n", li, xlvda->plyr.name);
                                else
                                    prf("%d * %s is present.\n", li, xlvda->plyr.name);
                                outprf(usrnum);
                            }
                        }
                    break;
                }
                if (sameas(margv[0], "/x")) {
                    clrprf();
                    prf("<%s> has left\n", zplyr->name);
                    xtavrn('t');
                    setcycle();
                    restplay();
                    break;
                }
            }
            rstrin();
            clrprf();
            prf("<%s> %s \n", zplyr->name, input);
            xtavrn('a');
            prf("--Message Sent--\n");
            outprf(usrnum);
            break;
            /* Combat Start from Chat */
        case 80:
            setcycle();
            break;
        case WFANUM:
            if (margc)
                zvda->lastnum = atol(margv[0]);
            else
                zvda->lastnum = 0;
            usrptr->substt = zvda->rstate;
            setcycle();
            break;
        case FATALE:
            prfmsg(FATALM);
            outprf(usrnum);
            saveplay();
            ingame[usrnum] = FALSE;
            break;
            // During Generate a Character (GENCHAR) .......(140-149)..............
        case 140:
            if (sameas(margv[0], "x")) {
                usrptr->substt = 149;
                prfmsg(ABCHAR);
                outprf(usrnum);
            } else if (sameas(margv[0], "s")) {
                zplyr->race = zvda->scan;
                usrptr->substt = 141;
                dfaSetBlk(dbclass);
                dfaAcqEQ(&zvda->pclass, classbase[0].name, 0);
                dfaRstBlk();
                zvda->scan = 0;
                dispclass();
            } else if (sameas(margv[0], "n")) {
                zvda->scan++;
                if (zvda->scan < racecnt) {
                    dfaSetBlk(dbrace);
                    dfaAcqEQ(&zvda->prace, racebase[zvda->scan].name, 0);
                    dfaRstBlk();
                } else {
                    zvda->scan = 0;
                    dfaSetBlk(dbrace);
                    dfaAcqEQ(&zvda->prace, racebase[0].name, 0);
                    dfaRstBlk();
                }
                disprace();
            } else if (sameas(margv[0], "p")) {
                zvda->scan--;
                if (zvda->scan > -1) {
                    dfaSetBlk(dbrace);
                    dfaAcqEQ(&zvda->prace, racebase[zvda->scan].name, 0);
                    dfaRstBlk();
                } else {
                    zvda->scan = racecnt - 1;
                    dfaSetBlk(dbrace);
                    dfaAcqEQ(&zvda->prace, racebase[zvda->scan].name, 0);
                    dfaRstBlk();
                }
                disprace();
            } else if (alldgs(margv[0])) {  // Typed in a number....
                zvda->scanmax = zvda->scan;
                zvda->scan = (SHORT)atoi(margv[0]);
                if (zvda->scan > -1 && zvda->scan < racecnt) {
                    dfaSetBlk(dbrace);
                    dfaAcqEQ(&zvda->prace, racebase[zvda->scan].name, 0);
                    dfaRstBlk();
                } else {
                    zvda->scan = zvda->scanmax;
                    dfaSetBlk(dbrace);
                    dfaAcqEQ(&zvda->prace, racebase[zvda->scan].name, 0);
                    dfaRstBlk();
                }
                disprace();
            } else {
                disprace();
            }
            break;
        case 141:
            if (sameas(margv[0], "x")) {
                usrptr->substt = 149;
                prfmsg(ABCHAR);
                outprf(usrnum);
            } else if (sameas(margv[0], "s")) {
                zplyr->class = zvda->scan;
                usrptr->substt = 142;
                zvda->scan = 0;
                prfmsg(THISCHAR, zvda->prace.name, zvda->pclass.name);
                outprf(usrnum);
            } else if (sameas(margv[0], "n")) {
                zvda->scan++;
                if (zvda->scan < classcnt) {
                    dfaSetBlk(dbclass);
                    dfaAcqEQ(&zvda->pclass, classbase[zvda->scan].name, 0);
                    dfaRstBlk();
                } else {
                    zvda->scan = 0;
                    dfaSetBlk(dbclass);
                    dfaAcqEQ(&zvda->pclass, classbase[0].name, 0);
                    dfaRstBlk();
                }
                dispclass();
            } else if (sameas(margv[0], "p")) {
                zvda->scan--;
                if (zvda->scan > -1) {
                    dfaSetBlk(dbclass);
                    dfaAcqEQ(&zvda->pclass, classbase[zvda->scan].name, 0);
                    dfaRstBlk();
                } else {
                    zvda->scan = classcnt - 1;
                    dfaSetBlk(dbclass);
                    dfaAcqEQ(&zvda->pclass, classbase[zvda->scan].name, 0);
                    dfaRstBlk();
                }
                dispclass();
            } else if (alldgs(margv[0])) {  // Typed in a number....
                zvda->scanmax = zvda->scan;
                zvda->scan = (SHORT)atoi(margv[0]);
                if (zvda->scan > -1 && zvda->scan < classcnt) {
                    dfaSetBlk(dbclass);
                    dfaAcqEQ(&zvda->pclass, classbase[zvda->scan].name, 0);
                    dfaRstBlk();
                } else {
                    zvda->scan = zvda->scanmax;
                    dfaSetBlk(dbclass);
                    dfaAcqEQ(&zvda->pclass, classbase[zvda->scan].name, 0);
                    dfaRstBlk();
                }
                dispclass();
            } else {
                dispclass();
            }
            break;
        case 142:
            // Almost Finished!!................................
            if (samein(margv[0], "no")) {
                dfaSetBlk(dbrace);
                dfaAcqEQ(&zvda->prace, racebase[0].name, 0);
                dfaRstBlk();
                zvda->scan = 0;
                usrptr->substt = 140;
                disprace();  // Display a race....
            } else if (samein(margv[0], "yes")) {
                initplayer();
                for (ctr = 0; ctr < 7; ctr++)
                    zplyr->attrib[ctr + 7] = zplyr->attrib[ctr] = (CHAR)(15 + zvda->prace.modify[ctr]);

                for (ctr = 0; ctr < 9; ctr++) {
                    yakline[0] = zvda->pclass.mage[zplyr->level - 1][ctr];
                    yakline[1] = 0;
                    zplyr->mage_new[9 - zplyr->level] = (SHORT)atoi(yakline);
                    yakline[0] = zvda->pclass.priest[zplyr->level - 1][ctr];
                    zplyr->cleric_new[9 - zplyr->level] = (SHORT)atoi(yakline);
                }

                zplyr->currhp += (CHAR)zvda->prace.modify[7];
                zplyr->maxhp = zplyr->currhp;
                saveplay();
                dispmain();
                setcycle();
            } else {
                prfmsg(THISCHAR, zvda->prace.name, zvda->pclass.name);
                outprf(usrnum);
            }
            break;
        case 149:
            // Aborted GENCHAR!!................................
            dispmain();
            setcycle();
            break;
        case 150:
            // Resurrect your character..........................
            if (samein(margv[0], "no")) {
                dispmain();
                setcycle();
            } else if (samein(margv[0], "yes")) {
                if (reload_cost > 0) {
                    if (!dedcrd(reload_cost * zplyr->level, 0)) {
                        prfmsg(NORES);
                        outprf(usrnum);
                        usrptr->substt = 2;
                        zvda->redraw = TRUE;
                        setcycle();
                    } else {
                        setcycle();
                        zplyr->currhp = zplyr->maxhp;
                        zplyr->currmp = zplyr->maxmp;
                        plinit();
                        restplay();
                    }
                } else {
                    setcycle();
                    zplyr->currhp = zplyr->maxhp;
                    zplyr->currmp = zplyr->maxmp;
                    plinit();
                    restplay();
                }
            } else {
                if (reload_cost > 0) {
                    prfmsg(SRESUR1, l2as(reload_cost * zplyr->level));
                    outprf(usrnum);
                } else {
                    prfmsg(SRESUR);
                    outprf(usrnum);
                }
            }
            break;
        default:
            prf("unexpected appearance in main, state=%d\n", usrptr->substt);
            outprf(usrnum);
            rc = 0;
    }
    rstmbk();
    if (rc == 0) clingo = zvda->curlang;

    return(rc);
}

VOID wdcycle(VOID)
{
    SHORT ci;
    CHAR kkey, ctr, impline[81];
    OBJINF   tobj;    // temp holders for database lists.
    MONSTINF tmon;
    SPELLINF tspe;
    RACEINF  trac;
    CLASSINF tcla;

    if (samein("ansi", languages[clingo]->name)) {
        zvda->scanmax = usaptr->scnbrk - 7;
    } else {
        zvda->scanmax = 10;
    }
    if (zvda->rip) {
        zvda->scanmax = usaptr->scnbrk - 7;
    }
    if (zvda->scanmax < 1 || zvda->scanmax>50) zvda->scanmax = 17;

    zvda = (VDABLK*)vdaptr;
    zplyr = &zvda->plyr;
    zpobj = zvda->pstuff;
    uaptr = uacoff(usrnum);
    if (status == CYCLE) {
        if (zvda->party != usrnum)
            zldr = (VDABLK*)vdaoff(zvda->party);
        else
            zldr = zvda;
        if (!zvda->incycle)
            return;
        for (ci = 0; ci < zldr->memcnt; ci++)
            if (ingame[zldr->members[ci]] && btuoba(zldr->members[ci]) < zvda->obsize - 200) {
                btucli(usrnum);
                btuinj(usrnum, CYCLE);
                return;
            }
        setmbk(msgblk);
        switch (usrptr->substt) {
            // Rip version Number testing!!!
            case 1:
                if (zvda->nxtstt < 90) misc_rip_detect();
                else {
                    switch (zvda->nxtstt) {
                        case 99:
                            dispmain();
                            zvda->redraw = FALSE;
                            btuinj(usrnum, CYCLE);
                            break;
                        default:
                            if (btuica(usrnum, kpress, 4) > 0) {
                                btucli(usrnum);
                                dispmain();
                                zvda->redraw = FALSE;
                            }
                            btuinj(usrnum, CYCLE);
                            break;
                    }
                }
                break;
                /* Initial display menu */
            case 2:
                if (btuica(usrnum, kpress, 4) > 0) {
                    btucli(usrnum);
                    if (zvda->redraw) {
                        dispmain();
                        zvda->redraw = FALSE;
                    }
                }
                btuinj(usrnum, CYCLE);
                break;
            case 3:
                switch (zvda->mnukey) {
                    case 1:
                        if (loadplay()) {
                            prfmsg(CLRSCR);
                            prfmsg(SUICIDE);
                            outprf(usrnum);
                            usrptr->substt = 2;
                            zvda->redraw = TRUE;
                            btuinj(usrnum, CYCLE);
                            break;
                        } else {
                            usrptr->substt = 219;
                            zvda->nxtstt = 0;
                            btuinj(usrnum, CYCLE);
                        }
                        break;
                        /* play der game */
                    case 2:
                        plinit();
                        if (loadplay()) {
                            stzcpy(zplyr->name, uaptr->userid, 30);
                            if (zplyr->currhp > 0) {
                                acplyr((SHORT)usrnum);
                                restplay();
                            } else {
                                if (reload_cost > 0) {
                                    prfmsg(SRESUR1, l2as(reload_cost * zplyr->level));
                                    outprf(usrnum);
                                } else {
                                    prfmsg(SRESUR);
                                    outprf(usrnum);
                                }
                                usrptr->substt = 150;
                                nocycle();
                                return;
                            }
                        } else {
                            prfmsg(CLRSCR);
                            prfmsg(MAKECHAR);
                            outprf(usrnum);
                            usrptr->substt = 2;
                            zvda->redraw = TRUE;
                        }
                        btuinj(usrnum, CYCLE);
                        break;
                    case 3: // View the players listing....
                        dfaSetBlk(dbplayer);
                        if (!dfaAcqLE(&tplayer, "2000000000", 1)) {
                            prfmsg(NEWGAME);
                            outprf(usrnum);
                            usrptr->substt = 2;
                            strcpy(zvda->score, tplayer.score);
                            zvda->redraw = TRUE;
                        } else {
                            strcpy(zvda->score, tplayer.score);
                            strcpy(zvda->curpos, "ê");
                            usrptr->substt = 211;
                        }
                        dfaRstBlk();
                        btuinj(usrnum, CYCLE);
                        break;
                    case 5: // Player Docs listing...........................
                        zvda->readfile = fopen("ELWWDPLY.DOC", FOPRA);
                        if (zvda->readfile != NULL) {
                            prfmsg(CLRSCR);
                            outprf(usrnum);
                            usrptr->substt = 215;
                            zvda->scan = 0;
                            btuinj(usrnum, CYCLE);
                        } else {
                            prfmsg(FLERR, "ELWWDPLY.DOC");
                            shocst("INET ERROR!!", "Can not find : ELWWDPLY.DOC");
                            outprf(usrnum);
                            usrptr->substt = 2;
                            zvda->redraw = TRUE;
                            btuinj(usrnum, CYCLE);
                        }
                        break;
                    case 7:
                        dfaSetBlk(dbplayer); // Suicide!!
                        prfmsg(CLRSCR);
                        if (dfaAcqEQ(&tplayer, usaptr->userid, 0)) {
                            prf("Player KILLED!!!");
                            outprf(usrnum);
                            dfaDelete();
                            usrptr->substt = 2;
                            zvda->redraw = TRUE;
                            dfaRstBlk();
                            btuinj(usrnum, CYCLE);
                        } else {
                            dfaRstBlk();
                            dispmain();
                            btuinj(usrnum, CYCLE);
                        }
                        break;
                    case 8:
                        // usrptr->flags^=NOINJO;
                        usrptr->flags ^= NOGLOB;
                        prf("[1;24r");
                        prfmsg(CLRSCR);
                        prfmsg(TGABKS, vernum);
                        outprf(usrnum);
                        zvda->gstate = ISACTIVE;
                        usrptr->substt = 3;
                        nocycle();
                        break;
                    case 9:
                        if (hasmkey(WODEDIT)) {
#ifdef ZARKALF
                            btucli(usrnum);
                            ansimenu(1, 1, 43, 6, "ABCDEF", 4, UTLMENU);
                            btuinj(usrnum, CYCLE);
#else
                            prfmsg(CLRSCR);
                            prfmsg(OBJDAT);
                            outprf(usrnum);
                            usrptr->substt = 10;
                            nocycle();
#endif
                        }
                        break;
                    default:
                        btuinj(usrnum, CYCLE);
                        btucli(usrnum);
                        if (hasmkey(WODEDIT))
                            ansimenu(1, 1, 43, 9, "ABCDEFGHIJ", 3, MUMENU);
                        else
                            ansimenu(1, 1, 43, 8, "ABCDEFGHI", 3, MMENU);

                }
                break;
#ifdef ZARKALF
            case 4:
                switch (zvda->mnukey) {
                    case 1:
                        prfmsg(CLRSCR);
                        prfmsg(OBJDAT);
                        outprf(usrnum);
                        usrptr->substt = 10;
                        break;
                    case 2:
                        sqzmaps();
                        usrptr->substt = 3;
                        zvda->mnukey = 9;
                        break;
                    case 3:
                        prfmsg(CLRSCR);
                        prf("Object Counts\n");
                        for (ci = 0; ci < MAXOBJCL; ci++)
                            prf("Class: %s Count:%u\n", mu2[ci], objcnt[ci]);
                        outprf(usrnum);
                        prf("Total Monsters: %u\n", totmonst);
                        prf("Total WSpelss: %u\n", totmonst);
                        prf("Total Classes: %u\n", classcnt);
                        outprf(usrnum);
                        prf("Total Races: %u\n", racecnt);
                        prf("VDA size = %u\n", sizeof(VDABLK));
                        prf("Total WSpells: %u\n", wspellcnt);
                        prf("Total CSpells: %u\n", cspellcnt);
                        outprf(usrnum);
                        prf("Total Prizes: %u\n", totpriz);
                        outprf(usrnum);
                        arxy(44, 1);
                        prf("TotDrop=%u", totdrop);
                        arxy(44, 2);
                        prf("Zoba=%u", zvda->obsize);
                        outprf(usrnum);
                        btucli(usrnum);
                        usrptr->substt = 7;
                        zvda->mnukey = 1;
                        break;
                    case 4:
                        prf("Level to view: ");
                        outprf(usrnum);
                        usrptr->substt = 5;
                        break;
                    case 5:
                        prf("Level to view: ");
                        outprf(usrnum);
                        usrptr->substt = 6;
                        break;
                    case 6:
                        dispmain();
                        zvda->redraw = FALSE;
                        break;
                    default:
                        prf("unknown util state %d,%u", usrptr->substt, zvda->mnukey);
                        dispmain();
                        zvda->redraw = FALSE;
                }
                switch (zvda->mnukey) {
                    case 4:
                    case 5:
                    case 1:
                        nocycle();
                        break;
                    default:
                        btuinj(usrnum, CYCLE);
                }
                break;
#endif
                /* Moving About */
            case 20:
                kkey = getinput();
                if (kkey > 0) {
                    moveme(kkey);
                    if (usrptr->substt == 20) {
                        if (random(100) <= mench)
                            mencinit();
                    }
                } else {
                    if (zplyr->condition[2]) {
                        if (zvda->pwtick != btuTicker()) {  //ticker
                            deccond('p', (SHORT)usrnum);
                            if (zplyr->condition[2]) {
                                zvda->pwtick = btuTicker(); //ticker
                            }
                        }
                    }
                    if (zvda->party != usrnum) {
                        if (zvda->pdraw) {
                            setwall();
                            draw();
                            zvda->pdraw = FALSE;
                        }
                    }
                }
                btuinj(usrnum, CYCLE);
                if (zvda->dead) {
                    saveplay();
                    prfmsg(YRDEAD);
                    outprf(usrnum);
                    //          dispmain();
                    usrptr->substt = 2;
                    zvda->gstate = ISACTIVE;
                    zvda->redraw = TRUE;
                }
                if (zvda->yakflag && usrptr->substt == 20) {
                    zvda->yakflag = FALSE;
                    prfmsg(YBLLN);
                    outprf(usrnum);
                    prfmsg(WBLLN);
                    outprf(usrnum);
                    prfmsg(YAKM, zvda->yakmsg, " ");
                    outprf(usrnum);
                }
                break;
            case 21:
                if (btuica(usrnum, kpress, 4) > 0) {
                    btucli(usrnum);
                    if (kpress[0] == '\r')
                        restplay();
                }
                btuinj(usrnum, CYCLE);
                break;
            case 22:
                if (btuica(usrnum, kpress, 4) > 0) {
                    btucli(usrnum);
                    restplay();
                }
                btuinj(usrnum, CYCLE);
                break;
            case 23:
                dodrop();
                btuinj(usrnum, CYCLE);
                break;
            case 24:
                if (btuica(usrnum, kpress, 4) > 0) {
                    usrptr->substt = zvda->rstate;
                }
                btuinj(usrnum, CYCLE);
                break;
                /* equipping an item */
            case 25:
                if (zvda->mnukey) {
                    zvda->mnukey--;
                    if (doequip()) {
                        restplay();
                        acplyr((SHORT)usrnum);
                    } else
                        pagemenu(25, zvda->litcnt, FALSE);
                } else {
                    restplay();
                }
                btuinj(usrnum, CYCLE);
                break;
                /* using an item */
            case 26:
                if (zvda->mnukey) {
                    zvda->mnukey--;
                    useit();
                    restcomp();
                } else {
                    restcomp();
                }
                btuinj(usrnum, CYCLE);
                break;
            case 27:
                castproc();
                btuinj(usrnum, CYCLE);
                break;
            case 28:
                whodat();
                btuinj(usrnum, CYCLE);
                break;
            case 29:
                scry(29, 1);
                btuinj(usrnum, CYCLE);
                break;
            case 30:
                pageproc();
                btuinj(usrnum, CYCLE);
                break;
            case 31:
                drawstats();
                usrptr->substt = 20;
                btuinj(usrnum, CYCLE);
                break;
            case 32:
                eyespy();
                btuinj(usrnum, CYCLE);
                break;
            case 33:
                nocycle();
                btumil(usrnum, 40);
                break;
            case 35:
                prfmsg(CLRSCR);
                prfmsg(ILOUNG);
                outprf(usrnum);
                prf("<%s> has arrived.\n", zplyr->name);
                xlounge('t');
                usrptr->substt = 36;
                btuinj(usrnum, CYCLE);
                break;
            case 36:
                nocycle();
                usrptr->substt = 30;
                for (ci = 0; ci < nterms; ci++)
                    zvda->invf[ci] = 0;
                zvda->gstate = INCHAT;
                break;
            case 37:
                restplay();
                btuinj(usrnum, CYCLE);
                break;
            case 38:
                nocycle();
                btumil(usrnum, 72);
                break;
                /*  Shops   */
            case 40:
                wepshop();
                btuinj(usrnum, CYCLE);
                break;
            case 41:
                bankproc();
                btuinj(usrnum, CYCLE);
                break;
            case 42:
                arenaproc();
                btuinj(usrnum, CYCLE);
                break;
            case 43:
                tavproc();
                btuinj(usrnum, CYCLE);
                break;
            case 44:
                prfmsg(CLRSCR);
                prfmsg(ILOUNG);
                outprf(usrnum);
                prf("<%s> has arrived.\n", zplyr->name);
                xtavrn('a');
                usrptr->substt = 45;
                btuinj(usrnum, CYCLE);
                break;
            case 45:
                nocycle();
                zvda->gstate = TAVCHT;
                break;
            case 46:
                droplist();
                btuinj(usrnum, CYCLE);
                break;
                /*  Combat  */
            case 80:
                encounter();
                btuinj(usrnum, CYCLE);
                break;
                /*  Inn  */
            case 100:
                innproc();
                btuinj(usrnum, CYCLE);
                break;
                /*  Cleric Guild */
            case 110:
                clerproc();
                btuinj(usrnum, CYCLE);
                break;
                /*  Item Processor */
                //case 120: 
                //  itemproc();
                //  btuinj(usrnum,CYCLE);
                //  break;
                /*  Wizard Guild */
            case 130:
                wizproc();
                btuinj(usrnum, CYCLE);
                break;
                /*  Editor Listing routines  200-210   One lister does it all!! */
            case 200:
                btuech(usrnum, 0);
                zvda->plast = 0;
                switch (zvda->retstt) {
                    case 11:   // Item listing.........................
                        dfaSetBlk(miscitem);
                        if (zvda->curpos[0] == 'ê') {
                            prfmsg(EDLIST0);
                            outprf(usrnum);
                            zvda->scan = 0;
                            zvda->litcnt = 0;
                            for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                            dfaStepLO(&tobj);
                        } else dfaAcqEQ(&tobj, zvda->curpos, 0);
                        strcpy(zvda->plist[zvda->scan], tobj.objname);
                        prfmsg(EDLIST, tobj.objname, mu2[tobj.otype],
                            tobj.orange, tobj.omd, mu5[tobj.osp], l2as(tobj.ocost));
                        zvda->scan++;
                        zvda->litcnt++;
                        outprf(usrnum);
                        if (zvda->scan < zvda->scanmax) {
                            if (dfaStepNX(&tobj)) strcpy(zvda->curpos, tobj.objname);
                            else {
                                prfmsg(EOL);
                                usrptr->substt = 201;
                                arxy(1, 2);
                                prfmsg(EDLIST1, zvda->plist[0]);
                                outprf(usrnum);
                                zvda->scan = 0;
                                zvda->litcnt--;
                                zvda->plast = 1;
                            }
                        } else {
                            prfmsg(EOL);
                            usrptr->substt = 201;
                            arxy(1, 2);
                            prfmsg(EDLIST1, zvda->plist[0]);
                            outprf(usrnum);
                            zvda->scan = 0;
                            zvda->litcnt--;
                        }
                        break;
                    case 14:   // Spell listing.........................
                        dfaSetBlk(dbspells);
                        if (zvda->curpos[0] == 'ê') {
                            prfmsg(EDSPEL0);
                            outprf(usrnum);
                            zvda->scan = 0;
                            zvda->litcnt = 0;
                            for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                            dfaStepLO(&tspe);
                        } else dfaAcqEQ(&tspe, zvda->curpos, 0);
                        strcpy(zvda->plist[zvda->scan], tspe.spellname);
                        prfmsg(EDSPEL, tspe.spellname, tspe.level, sp2[tspe.class], sp4[tspe.type], sp3[tspe.target]);
                        zvda->scan++;
                        zvda->litcnt++;
                        outprf(usrnum);
                        if (zvda->scan < zvda->scanmax) {
                            if (dfaStepNX(&tspe)) strcpy(zvda->curpos, tspe.spellname);
                            else {
                                prfmsg(EOL);
                                usrptr->substt = 201;
                                arxy(1, 2);
                                prfmsg(EDLIST1, zvda->plist[0]);
                                outprf(usrnum);
                                zvda->scan = 0;
                                zvda->litcnt--;
                                zvda->plast = 1;
                            }
                        } else {
                            prfmsg(EOL);
                            usrptr->substt = 201;
                            arxy(1, 2);
                            prfmsg(EDLIST1, zvda->plist[0]);
                            outprf(usrnum);
                            zvda->scan = 0;
                            zvda->litcnt--;
                        }
                        break;
                    case 16:   // Race listing.........................
                        dfaSetBlk(dbrace);
                        if (zvda->curpos[0] == 'ê') {
                            prfmsg(EDRACE0);
                            outprf(usrnum);
                            zvda->scan = 0;
                            zvda->litcnt = 0;
                            for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                            dfaStepLO(&trac);
                        } else dfaAcqEQ(&trac, zvda->curpos, 0);
                        strcpy(zvda->plist[zvda->scan], trac.name);
                        prfmsg(EDRACE, trac.name, trac.cast, trac.mr);
                        zvda->scan++;
                        zvda->litcnt++;
                        outprf(usrnum);
                        if (zvda->scan < zvda->scanmax) {
                            if (dfaStepNX(&trac)) strcpy(zvda->curpos, trac.name);
                            else {
                                prfmsg(EOL);
                                usrptr->substt = 201;
                                arxy(1, 2);
                                prfmsg(EDLIST1, zvda->plist[0]);
                                outprf(usrnum);
                                zvda->scan = 0;
                                zvda->litcnt--;
                                zvda->plast = 1;
                            }
                        } else {
                            prfmsg(EOL);
                            usrptr->substt = 201;
                            arxy(1, 2);
                            prfmsg(EDLIST1, zvda->plist[0]);
                            outprf(usrnum);
                            zvda->scan = 0;
                            zvda->litcnt--;
                        }
                        break;
                    case 18:   // Class listing.........................
                        dfaSetBlk(dbclass);
                        if (zvda->curpos[0] == 'ê') {
                            prfmsg(EDCLAS0);
                            outprf(usrnum);
                            zvda->scan = 0;
                            zvda->litcnt = 0;
                            for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                            dfaStepLO(&tcla);
                        } else dfaAcqEQ(&tcla, zvda->curpos, 0);
                        strcpy(zvda->plist[zvda->scan], tcla.name);
                        prfmsg(EDCLAS, tcla.name, tcla.hp, tcla.hp);
                        zvda->scan++;
                        zvda->litcnt++;
                        outprf(usrnum);
                        if (zvda->scan < zvda->scanmax) {
                            if (dfaStepNX(&tcla)) strcpy(zvda->curpos, tcla.name);
                            else {
                                prfmsg(EOL);
                                usrptr->substt = 201;
                                arxy(1, 2);
                                prfmsg(EDLIST1, zvda->plist[0]);
                                outprf(usrnum);
                                zvda->scan = 0;
                                zvda->litcnt--;
                                zvda->plast = 1;
                            }
                        } else {
                            prfmsg(EOL);
                            usrptr->substt = 201;
                            arxy(1, 2);
                            prfmsg(EDLIST1, zvda->plist[0]);
                            outprf(usrnum);
                            zvda->scan = 0;
                            zvda->litcnt--;
                        }
                        break;
                    case 20:   // Monster listing.........................
                        dfaSetBlk(dbmonst);
                        if (zvda->curpos[0] == 'ê') {
                            prfmsg(EDMON0);
                            outprf(usrnum);
                            zvda->scan = 0;
                            zvda->litcnt = 0;
                            for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                            dfaStepLO(&tmon);
                        } else dfaAcqEQ(&tmon, zvda->curpos, 0);
                        strcpy(zvda->plist[zvda->scan], tmon.name);
                        prfmsg(EDMON, tmon.name, tmon.level, mon2[tmon.spa],
                            mon2[tmon.spr], tmon.exp, tmon.gold);
                        zvda->scan++;
                        zvda->litcnt++;
                        outprf(usrnum);
                        if (zvda->scan < zvda->scanmax) {
                            if (dfaStepNX(&tmon)) strcpy(zvda->curpos, tmon.name);
                            else {
                                prfmsg(EOL);
                                usrptr->substt = 201;
                                arxy(1, 2);
                                prfmsg(EDMON1, zvda->plist[0]);
                                outprf(usrnum);
                                zvda->scan = 0;
                                zvda->litcnt--;
                                zvda->plast = 1;
                            }
                        } else {
                            prfmsg(EOL);
                            usrptr->substt = 201;
                            arxy(1, 2);
                            prfmsg(EDMON1, zvda->plist[0]);
                            outprf(usrnum);
                            zvda->scan = 0;
                            zvda->litcnt--;
                        }
                        break;
                }
                dfaRstBlk();
                btuinj(usrnum, CYCLE);
                break;
            case 201: // Cursor Movement controls...........
                kkey = getinput();
                if (kkey > 0) {
                    switch (kkey) {
#ifdef ZARKALF
                        case 'D': // Delete this item from listing.....
                            switch (zvda->retstt) {
                                case 11:
                                    dfaSetBlk(miscitem);
                                    dfaAcqEQ(&objinf, zvda->plist[zvda->scan], 0);
                                    dfaDelete();
                                    strcpy(zvda->curpos, zvda->plist[0]);
                                    usrptr->substt = 200;
                                    prfmsg(EDLIST0);
                                    outprf(usrnum);
                                    zvda->scan = 0;
                                    zvda->litcnt = 0;
                                    for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                                    break;
                                case 14:
                                    dfaSetBlk(dbspells);
                                    dfaAcqEQ(&tspe, zvda->plist[zvda->scan], 0);
                                    dfaDelete();
                                    strcpy(zvda->curpos, zvda->plist[0]);
                                    usrptr->substt = 200;
                                    prfmsg(EDSPEL0);
                                    outprf(usrnum);
                                    zvda->scan = 0;
                                    zvda->litcnt = 0;
                                    for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                                    break;
                                case 16:
                                    dfaSetBlk(dbrace);
                                    dfaAcqEQ(&trac, zvda->plist[zvda->scan], 0);
                                    dfaDelete();
                                    strcpy(zvda->curpos, zvda->plist[0]);
                                    usrptr->substt = 200;
                                    prfmsg(EDRACE0);
                                    outprf(usrnum);
                                    zvda->scan = 0;
                                    zvda->litcnt = 0;
                                    for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                                    break;
                                case 18:
                                    dfaSetBlk(dbclass);
                                    dfaAcqEQ(&tcla, zvda->plist[zvda->scan], 0);
                                    dfaDelete();
                                    strcpy(zvda->curpos, zvda->plist[0]);
                                    usrptr->substt = 200;
                                    prfmsg(EDCLAS0);
                                    outprf(usrnum);
                                    zvda->scan = 0;
                                    zvda->litcnt = 0;
                                    for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                                    break;
                                case 20:
                                    dfaSetBlk(dbmonst);
                                    dfaAcqEQ(&tmon, zvda->plist[zvda->scan], 0);
                                    dfaDelete();
                                    strcpy(zvda->curpos, zvda->plist[0]);
                                    usrptr->substt = 200;
                                    prfmsg(EDMON0);
                                    outprf(usrnum);
                                    zvda->scan = 0;
                                    zvda->litcnt = 0;
                                    for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                                    break;
                            }
                            dfaRstBlk();
                            break;
#endif
                        case 'N': // Next page in listing....
                            if (!zvda->plast) {
                                usrptr->substt = 200;
                                switch (zvda->retstt) {
                                    case 11:
                                        prfmsg(EDLIST0);
                                        break;
                                    case 14:
                                        prfmsg(EDSPEL0);
                                        break;
                                    case 16:
                                        prfmsg(EDRACE0);
                                        break;
                                    case 18:
                                        prfmsg(EDCLAS0);
                                        break;
                                    case 20:
                                        prfmsg(EDMON0);
                                        break;
                                }
                                outprf(usrnum);
                                zvda->scan = 0;
                                zvda->litcnt = 0;
                                for (ctr = 0; ctr < 50; ctr++) strcpy(zvda->plist[ctr], " ");
                            } else {
                                arxy(1, zvda->scanmax + 3);
                                prfmsg(OBJMNU, zvda->dblist, zvda->dblist);
                                outprf(usrnum);
                                usrptr->substt = zvda->retstt;
                                dfaRstBlk();
                                rstmbk();
                                nocycle();
                                return;
                            }
                            btuinj(usrnum, CYCLE);
                            break;
                        case '8': // Up item
                            switch (zvda->retstt) {
                                default:
                                    arxy(1, zvda->scan + 2);
                                    prfmsg(EDLIST2, zvda->plist[zvda->scan]);
                                    zvda->scan--;
                                    if (zvda->scan < 0) zvda->scan = zvda->litcnt;
                                    arxy(1, zvda->scan + 2);
                                    prfmsg(EDLIST1, zvda->plist[zvda->scan]);
                                    outprf(usrnum);
                                    break;
                                case 20:
                                    arxy(1, zvda->scan + 2);
                                    prfmsg(EDMON2, zvda->plist[zvda->scan]);
                                    zvda->scan--;
                                    if (zvda->scan < 0) zvda->scan = zvda->litcnt;
                                    arxy(1, zvda->scan + 2);
                                    prfmsg(EDMON1, zvda->plist[zvda->scan]);
                                    outprf(usrnum);
                                    break;
                            }
                            break;
                        case '2': // Down item
                            switch (zvda->retstt) {
                                default:
                                    arxy(1, zvda->scan + 2);
                                    prfmsg(EDLIST2, zvda->plist[zvda->scan]);
                                    zvda->scan++;
                                    if (zvda->scan > zvda->litcnt) zvda->scan = 0;
                                    arxy(1, zvda->scan + 2);
                                    prfmsg(EDLIST1, zvda->plist[zvda->scan]);
                                    outprf(usrnum);
                                    break;
                                case 20:
                                    arxy(1, zvda->scan + 2);
                                    prfmsg(EDMON2, zvda->plist[zvda->scan]);
                                    zvda->scan++;
                                    if (zvda->scan > zvda->litcnt) zvda->scan = 0;
                                    arxy(1, zvda->scan + 2);
                                    prfmsg(EDMON1, zvda->plist[zvda->scan]);
                                    outprf(usrnum);
                                    break;
                            }
                            break;
                        case 13: // Select Item....
                            switch (zvda->retstt) {
                                case 11:
                                    dfaSetBlk(miscitem);
                                    dfaAcqEQ(&objinf, zvda->plist[zvda->scan], 0);
                                    prepfsd(EDITOBJE, 1, FALSE);
                                    fsdrhd("Object Editor");
                                    fsdbkg(fsdrft());
                                    fsdscb->flddat[0].flags |= FFFAVD;
                                    fsdego(vfyadn, fsd_finish);
                                    break;
                                case 14:
                                    dfaSetBlk(dbspells);
                                    dfaAcqEQ(&spellinf, zvda->plist[zvda->scan], 0);
                                    spfsd(EDITSPEL, 1, FALSE);
                                    fsdrhd("Spell Editor");
                                    fsdbkg(fsdrft());
                                    fsdscb->flddat[0].flags |= FFFAVD;
                                    fsdego(vfyadn, spfsd_finish);
                                    break;
                                case 16:
                                    dfaSetBlk(dbrace);
                                    dfaAcqEQ(&raceinf, zvda->plist[zvda->scan], 0);
                                    rafsd(EDITRACE, 1, FALSE);
                                    fsdrhd("Race Editor");
                                    fsdbkg(fsdrft());
                                    fsdscb->flddat[0].flags |= FFFAVD;
                                    fsdego(vfyadn, rafsd_finish);
                                    break;
                                case 18:
                                    dfaSetBlk(dbclass);
                                    dfaAcqEQ(&classinf, zvda->plist[zvda->scan], 0);
                                    clfsd(EDITCLAS, 1, FALSE);
                                    fsdrhd("Class Editor");
                                    fsdbkg(fsdrft());
                                    fsdscb->flddat[0].flags |= FFFAVD;
                                    fsdego(vfyadn, clfsd_finish);
                                    break;
                                case 20:
                                    dfaSetBlk(dbmonst);
                                    dfaAcqEQ(&monstinf, zvda->plist[zvda->scan], 0);
                                    mofsd(EDITMONS, 1, FALSE);
                                    fsdrhd("Monster Editor");
                                    fsdbkg(fsdrft());
                                    fsdscb->flddat[0].flags |= FFFAVD;
                                    fsdego(vfyadn, mofsd_finish);
                                    break;
                            }
                            outprf(usrnum);
                            dfaRstBlk();
                            nocycle();
                            return;
                        case 'X': // Exit the items scroller.....
                            arxy(1, zvda->scanmax + 3);
                            prfmsg(OBJMNU, zvda->dblist, zvda->dblist);
                            outprf(usrnum);
                            usrptr->substt = zvda->retstt;
                            dfaRstBlk();
                            rstmbk();
                            nocycle();
                            dfsthn();
                            return;
                    }
                }
                btuinj(usrnum, CYCLE);
                break;
                // Character Listing routines *****************(211-212)****************
            case 211: // Show the listing, highest first...
                zvda->plast = 0;
                zvda->nxtstt = 211;
                dfaSetBlk(dbplayer);
                if (zvda->curpos[0] == 'ê') {
                    zvda->curpos[0] = '?';
                    prfmsg(PLYRLST);
                    outprf(usrnum);
                    zvda->scan = 0;
                }
                dfaAcqEQ(&tplayer, zvda->score, 1);
                prfmsg(PLYRLST1, tplayer.name, tplayer.plyr.level, classbase[tplayer.plyr.class].name, tplayer.plyr.age, l2as(tplayer.plyr.exp));
                outprf(usrnum);
                strcpy(zvda->score, tplayer.score);
                zvda->scan++;
                if (zvda->scan < zvda->scanmax) {
                    if (!dfaAcqLT(&tplayer, zvda->score, 1)) {
                        prfmsg(PLYREND);
                        outprf(usrnum);
                        usrptr->substt = 212;
                        zvda->scan = 0;
                        zvda->plast = 1;
                        btuinj(usrnum, CYCLE);
                    } else {
                        strcpy(zvda->score, tplayer.score);
                        btuinj(usrnum, CYCLE);
                    }
                } else {
                    prfmsg(PLYREND);
                    outprf(usrnum);
                    usrptr->substt = 212;
                    zvda->scan = 0;
                    btuinj(usrnum, CYCLE);
                }
                dfaRstBlk();
                break;
            case 212: // Show the listing, highest first...
                kkey = getinput();
                if (kkey > 0) {
                    switch (kkey) {
                        default: // Next page in listing....
                            if (!zvda->plast) {
                                usrptr->substt = zvda->nxtstt;
                                switch (zvda->nxtstt) {
                                    case 211:
                                        prfmsg(PLYRLST);
                                        break;
                                    case 215:
                                        prfmsg(CLRSCR);
                                        break;
                                }
                                outprf(usrnum);
                                zvda->scan = 0;
                            } else {
                                switch (zvda->nxtstt) {
                                    case 215:
                                        fclose(zvda->readfile);
                                        break;
                                }
                                dispmain();
                            }
                            break;
                        case 'X': // Exit the items scroller.....
                            switch (zvda->nxtstt) {
                                case 215:
                                    fclose(zvda->readfile);
                                    break;
                            }
                            dispmain();
                            break;
                    }
                }
                btuinj(usrnum, CYCLE);
                break;

                // file listing routines *****************(215-218)****************
            case 215: // Viewing a file..........
                zvda->plast = 0;
                zvda->nxtstt = 215;
                if (fgets(impline, 80, zvda->readfile) != NULL) {
                    prf(impline);
                    outprf(usrnum);
                    zvda->scan++;
                    if (zvda->scan > zvda->scanmax) {
                        prfmsg(PLYREND);
                        outprf(usrnum);
                        usrptr->substt = 212;
                        btuinj(usrnum, CYCLE);
                        break;
                    } else {
                        usrptr->substt = 215;
                        btuinj(usrnum, CYCLE);
                        break;
                    }
                }
                zvda->plast = 1;
                prfmsg(PLYREND);
                outprf(usrnum);
                usrptr->substt = 212;
                btuinj(usrnum, CYCLE);
                break;
                // Character generation routines *****************(219-220)****************
            case 219:
                usrptr->substt = 140;
                dfaSetBlk(dbrace);
                dfaAcqEQ(&zvda->prace, racebase[0].name, 0);
                dfaRstBlk();
                zvda->scan = 0;
                disprace();  // Display a race....
                nocycle();
                break;
            case 220:
                if (btuica(usrnum, kpress, 1) > 0) {
                    btucli(usrnum);
                    zvda->redraw = 1;
                    usrptr->substt = zvda->nxtstt;
                }
                btuinj(usrnum, CYCLE);
                break;
            case ANSMENU:
                kkey = getinput();
                if (kkey > 0) {
                    btucli(usrnum);
                    if (kkey == '8' || kkey == '2') {
                        clrarrows(zvda->mnurow + zvda->mnupos + 2, zvda->mnucol, zvda->mnuwid);
                        if (kkey == '2') {
                            zvda->mnupos++;
                            if (zvda->mnupos > zvda->mnumax)
                                zvda->mnupos = 1;
                        } else {
                            zvda->mnupos--;
                            if (zvda->mnupos == 0)
                                zvda->mnupos = zvda->mnumax;
                        }
                        drawarrows(zvda->mnurow + zvda->mnupos + 2, zvda->mnucol, zvda->mnuwid);
                    }
                    if (index(zvda->mnustr, kkey) != NOTFOUND) {
                        clrarrows(zvda->mnurow + zvda->mnupos + 2, zvda->mnucol, zvda->mnuwid);
                        zvda->mnukey = (CHAR)index(zvda->mnustr, kkey) + (CHAR)1;
                        usrptr->substt = zvda->rstate;
                    }
                    if (kpress[0] == '\r') {
                        clrarrows(zvda->mnurow + zvda->mnupos + 2, zvda->mnucol, zvda->mnuwid);
                        zvda->mnukey = (CHAR)zvda->mnupos;
                        usrptr->substt = zvda->rstate;
                    }
                }
                btuinj(usrnum, CYCLE);
                break;
            case RIPMENU:
                kkey = getinput();
                if (kkey > 0) {
                    btucli(usrnum);
                    if (index(zvda->mnustr, kkey) != NOTFOUND) {
                        clrarrows(zvda->mnurow + zvda->mnupos + 2, zvda->mnucol, zvda->mnuwid);
                        zvda->mnukey = (CHAR)index(zvda->mnustr, kkey) + (CHAR)1;
                        usrptr->substt = zvda->rstate;
                    }
                    if (kpress[0] == '\r') {
                        clrarrows(zvda->mnurow + zvda->mnupos + 2, zvda->mnucol, zvda->mnuwid);
                        zvda->mnukey = (CHAR)zvda->mnupos;
                        usrptr->substt = zvda->rstate;
                    }
                }
                btuinj(usrnum, CYCLE);
                break;
            case ANSYNO:
                if (btuica(usrnum, kpress, 4) > 0) {
                    btucli(usrnum);
                    kkey = xltkey();
                    switch (kkey) {
                        case 'Y':
                        case 'N':
                            zvda->mnukey = kkey;
                            prf("%c", kkey);
                            outprf(usrnum);
                            usrptr->substt = zvda->rstate;
                    }
                }
                btuinj(usrnum, CYCLE);
                break;
            case CAMPIN:
                if (btuica(usrnum, kpress, 4) > 0) {
                    btucli(usrnum);
                    clrprf();
                    if (zvda->party == usrnum && zvda->memcnt == 1) {
                        prfmsg(UWAKE);
                        outprf(usrnum);
                        usrptr->substt = 31;
                    } else {
                        prfmsg(ROUST, zplyr->name);
                        for (ci = 0; ci < zldr->memcnt; ci++) {
                            xlvda = (VDABLK*)vdaoff(zldr->members[ci]);
                            outprf(zldr->members[ci]);
                            xlvda->myuser->substt = 31;
                        }
                    }
                } else
                    if (zvda->party == usrnum) {
                        if (zvda->pwtick != btuTicker()) { //ticker
                            zvda->obn--;
                            zvda->pwtick = btuTicker(); //ticker
                            if (random(100) < 3) mencinit();
                            for (ci = 0; ci < zldr->memcnt; ci++) {
                                deccond('p', zldr->members[ci]);
                                xlvda = (VDABLK*)vdaoff(zldr->members[ci]);
                                xlvda->nstat = xlvda->rdlife = TRUE;
                                if (xlvda->plyr.currhp != 0) {
                                    if (xlvda->plyr.currhp < xlvda->plyr.maxhp)
                                        xlvda->plyr.currhp++;
                                    if (xlvda->plyr.currmp < xlvda->plyr.maxmp)
                                        xlvda->plyr.currmp++;
                                }
                            }
                            if (zvda->obn == 0) {
                                if (zvda->memcnt == 1) {
                                    prfmsg(UWAKE);
                                    outprf(usrnum);
                                    usrptr->substt = 31;
                                } else {
                                    clrprf();
                                    prfmsg(PWAKE);
                                    for (ci = 0; ci < zldr->memcnt; ci++) {
                                        xlvda = (VDABLK*)vdaoff(zldr->members[ci]);
                                        outprf(zldr->members[ci]);
                                        xlvda->myuser->substt = 31;
                                    }
                                }
                            } else {
                                drawstats();
                            }
                        }
                    }
                if (zvda->rdlife) {
                    drawstats();
                    zvda->rdlife = FALSE;
                }
                btuinj(usrnum, CYCLE);
                break;
            case DOZING:
                if (btuica(usrnum, kpress, 4) > 0)
                    btucli(usrnum);
                btuinj(usrnum, CYCLE);
                break;
            case FATALE:
                nocycle();
                break;
        }
        rstmbk();
    } else dfsthn();

}

/* Dropped carrier */
VOID wddrop(VOID)
{
    VDABLK* hvda, * fvda;
    USHORT i;
    SHORT dnxt = FALSE;

    hvda = (VDABLK*)vdaoff(usrnum);
    setmbk(msgblk);
    if (usrptr->state == modnum) { /* if was in me */
        if (hvda->gstate > PLAYING)
            saveplay();
        if (hvda->memcnt > 1 && usrptr->substt == CAMPIN) {
            clrprf();
            prfmsg(ROUS2, hvda->plyr.name);
            for (i = 1; i < hvda->memcnt; i++) {
                fvda = (VDABLK*)vdaoff(hvda->members[i]);
                outprf(hvda->members[i]);
                fvda->myuser->substt = 20;
            }
        }
        if (hvda->gstate == INFITE) {
            cbroff(hvda->cbrnum);
            //if (zcbr->wfor==hvda->cbrpos)
            //  dnxt=TRUE;
            rpfenc();
            if (zcbr->pcnt == 0)
                zcbr->entype = ' ';
        } else if (dnxt)
            nxtplyr();
        lparty((SHORT)usrnum);
        hvda->gstate = INACTIVE;
    }
    ingame[usrnum] = FALSE;
    rstmbk();
}

/* System Termination */
VOID wdterm(VOID)
{
    savelevers();
    fclose(dropf);
    fclose(wwall);
    dfaClose(miscitem);
    dfaClose(dbspells);
    dfaClose(dbclass);
    dfaClose(dbrace);
    dfaClose(dbmonst);
    clsmsg(msgblk);
    //shocst("ELW Worlds of Darkness Ended","Termination Complete for Worlds of Darkness");
}
