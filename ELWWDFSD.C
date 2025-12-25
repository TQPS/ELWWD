/*****************************************************************************
 *   ELWWDFSD.C   V0.62                                 Worlds of Darkness   *
 *   FSD Editor                                                              *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 10/17/1994         *
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
#include "fsdbbs.h"
#include "elwwd.h"
#include "elwwdtyp.h"
#include "elwwdglb.h"
#include "elwwdfsd.h"

static CHAR classfld[] =   // Answer field format for spells
"CLNAME(MIN=3)"
"CLHP(MIN=4 MAX=30)"
"CLMAGE1(MIN=0 MAX=999999999)"
"CLPRIEST1(MIN=0 MAX=999999999)"
"CLEXP1(MIN=0 MAX=2000000000)"
"CLMAGE2(MIN=0 MAX=999999999)"
"CLPRIEST2(MIN=0 MAX=999999999)"
"CLEXP2(MIN=0 MAX=2000000000)"
"CLMP(MIN=0 MAX=30)"
"CLMAGE3(MIN=0 MAX=999999999)"
"CLPRIEST3(MIN=0 MAX=999999999)"
"CLEXP3(MIN=0 MAX=2000000000)"
"CLMAGE4(MIN=0 MAX=999999999)"
"CLPRIEST4(MIN=0 MAX=999999999)"
"CLEXP4(MIN=0 MAX=2000000000)"
"CLMAGE5(MIN=0 MAX=999999999)"
"CLPRIEST5(MIN=0 MAX=999999999)"
"CLEXP5(MIN=0 MAX=2000000000)"
"CLOBJ1(ALT=NO ALT=YES MULTICHOICE)"
"CLMAGE6(MIN=0 MAX=999999999)"
"CLPRIEST6(MIN=0 MAX=999999999)"
"CLEXP6(MIN=0 MAX=2000000000)"
"CLOBJ2(ALT=NO ALT=YES MULTICHOICE)"
"CLMAGE7(MIN=0 MAX=999999999)"
"CLPRIEST7(MIN=0 MAX=999999999)"
"CLEXP7(MIN=0 MAX=2000000000)"
"CLOBJ3(ALT=NO ALT=YES MULTICHOICE)"
"CLMAGE8(MIN=0 MAX=999999999)"
"CLPRIEST8(MIN=0 MAX=999999999)"
"CLEXP8(MIN=0 MAX=2000000000)"
"CLOBJ4(ALT=NO ALT=YES MULTICHOICE)"
"CLMAGE9(MIN=0 MAX=999999999)"
"CLPRIEST9(MIN=0 MAX=999999999)"
"CLEXP9(MIN=0 MAX=2000000000)"
"CLOBJ5(ALT=NO ALT=YES MULTICHOICE)"
"CLMAGE10(MIN=0 MAX=999999999)"
"CLPRIEST10(MIN=0 MAX=999999999)"
"CLEXP10(MIN=0 MAX=2000000000)"
"CLOBJ6(ALT=NO ALT=YES MULTICHOICE)"
"CLMAGE11(MIN=0 MAX=999999999)"
"CLPRIEST11(MIN=0 MAX=999999999)"
"CLEXP11(MIN=0 MAX=2000000000)"
"CLOBJ7(ALT=NO ALT=YES MULTICHOICE)"
"CLMAGE12(MIN=0 MAX=999999999)"
"CLPRIEST12(MIN=0 MAX=999999999)"
"CLEXP12(MIN=0 MAX=2000000000)"
"CLOBJ8(ALT=NO ALT=YES MULTICHOICE)"
"CLMAGE13(MIN=0 MAX=999999999)"
"CLPRIEST13(MIN=0 MAX=999999999)"
"CLEXP13(MIN=0 MAX=2000000000)"
"CLMAGE14(MIN=0 MAX=999999999)"
"CLPRIEST14(MIN=0 MAX=999999999)"
"CLEXP14(MIN=0 MAX=2000000000)"
"CLMAGE15(MIN=0 MAX=999999999)"
"CLPRIEST15(MIN=0 MAX=999999999)"
"CLEXP15(MIN=0 MAX=2000000000)"
"DONE(ALT=SAVE ALT=QUIT MULTICHOICE)";

static CHAR classans[] =   // Answer string format for spells
"CLNAME=%s%c"
"CLHP=%d%c"
"CLMAGE1=%s%c"
"CLPRIEST1=%s%c"
"CLEXP1=%s%c"
"CLMAGE2=%s%c"
"CLPRIEST2=%s%c"
"CLEXP2=%s%c"
"CLMP=%d%c"
"CLMAGE3=%s%c"
"CLPRIEST3=%s%c"
"CLEXP3=%s%c"
"CLMAGE4=%s%c"
"CLPRIEST4=%s%c"
"CLEXP4=%s%c"
"CLMAGE5=%s%c"
"CLPRIEST5=%s%c"
"CLEXP5=%s%c"
"CLOBJ1=%s%c"
"CLMAGE6=%s%c"
"CLPRIEST6=%s%c"
"CLEXP6=%s%c"
"CLOBJ2=%s%c"
"CLMAGE7=%s%c"
"CLPRIEST7=%s%c"
"CLEXP7=%s%c"
"CLOBJ3=%s%c"
"CLMAGE8=%s%c"
"CLPRIEST8=%s%c"
"CLEXP8=%s%c"
"CLOBJ4=%s%c"
"CLMAGE9=%s%c"
"CLPRIEST9=%s%c"
"CLEXP9=%s%c"
"CLOBJ5=%s%c"
"CLMAGE10=%s%c"
"CLPRIEST10=%s%c"
"CLEXP10=%s%c"
"CLOBJ6=%s%c"
"CLMAGE11=%s%c"
"CLPRIEST11=%s%c"
"CLEXP11=%s%c"
"CLOBJ7=%s%c"
"CLMAGE12=%s%c"
"CLPRIEST12=%s%c"
"CLEXP12=%s%c"
"CLOBJ8=%s%c"
"CLMAGE13=%s%c"
"CLPRIEST13=%s%c"
"CLEXP13=%s%c"
"CLMAGE14=%s%c"
"CLPRIEST14=%s%c"
"CLEXP14=%s%c"
"CLMAGE15=%s%c"
"CLPRIEST15=%s%c"
"CLEXP15=%s%c";

static CHAR dbanswer[] =        // Answer string format..........
"NAMEFLD=%s%c"
"WEIGHT=%d%c"
"SPOT=%s%c"
"TYPE=%s%c"
"CLASS=%s%c"
"STR=%d%c"
"DEX=%d%c"
"SHORT=%d%c"
"WIS=%d%c"
"CON=%d%c"
"CHR=%d%c"
"LCK=%d%c"
"AC=%d%c"
"MD=%d%c"
"RANGE=%d%c"
"RTYPE=%s%c"
"SP=%s%c"
"WHAT=%s%c"
"CSP=%d%c"
"TSP=%d%c"
"SPHD=%d%c"
"WHO=%s%c"
"COST=%s%c";

static CHAR dbfields[] =           // Field specs...........................
"NAMEFLD(MIN=3)"
"WEIGHT(MIN=0 MAX=255)"
"SPOT(ALT=N/A ALT=HEAD ALT=BODY ALT=FOOT ALT=NECK ALT=HAND "
"ALT=2_HANDED MULTICHOICE)"
"TYPE(ALT=WEAPON ALT=ARMOR ALT=RING ALT=POTION ALT=STONE ALT=AMULET "
"ALT=SCROLL MULTICHOICE)"
"CLASS(ALT=A ALT=B ALT=C ALT=D ALT=E ALT=F ALT=G ALT=H MULTICHOICE)"
"STR(MIN=0 MAX=20)"
"DEX(MIN=0 MAX=20)"
"SHORT(MIN=0 MAX=20)"
"WIS(MIN=0 MAX=20)"
"CON(MIN=0 MAX=20)"
"CHR(MIN=0 MAX=20)"
"LCK(MIN=0 MAX=20)"
"AC(MIN=0 MAX=200)"
"MD(MIN=0 MAX=200)"
"RANGE(MIN=0 MAX=15)"
"RTYPE(ALT=N/A ALT=ARROWS ALT=ROCKS ALT=DARTS MULTICHOICE)"
"SP(ALT=N/A ALT=POISON ALT=CURE_POISON ALT=LVL_DRAIN ALT=LIFE_DRAIN "
"ALT=AGING ALT=PARALYSIS ALT=CRITICAL ALT=HEAL ALT=X_DMG ALT=SHIELD "
"ALT=CURSED ALT=VISION MULTICHOICE)"
"WHAT(ALT=WEAR ALT=USE ALT=BATTLE MULTICHOICE)"
"CSP(MIN=0 MAX=100)"
"TSP(MIN=0 MAX=999)"
"SPHD(MIN=0 MAX=200)"
"WHO(ALT=SHOP ALT=MONSTER ALT=PERSONAL MULTICHOICE)"
"COST(MIN=0 MAX=2000000000)"
"DONE(ALT=SAVE ALT=QUIT MULTICHOICE)";

static CHAR spellans[] =   // Answer string format for spells
"SPNAME=%s%c"
"LEVEL=%d%c"
"ELEMENT=%s%c"
"CLASS=%s%c"
"MP=%d%c"
"RANGE=%d%c"
"XRANGE=%d%c"
"TARGET=%s%c"
"TYPE=%s%c"
"DURATION=%d%c"
"MHD=%d%c"
"XMHD=%d%c"
"TEXT=%s%c";

static CHAR spellfld[] =   // Answer field format for spells
"SPNAME(MIN=3)"
"LEVEL(MIN=1 MAX=15)"
"ELEMENT(ALT=EARTH ALT=AIR ALT=WATER ALT=FIRE MULTICHOICE)"
"CLASS(ALT=MAGE ALT=PRIEST MULTICHOICE)"
"MP(MIN=0 MAX=250)"
"RANGE(MIN=0 MAX=15)"
"XRANGE(MIN=0 MAX=15)"
"TARGET(ALT=N/A ALT=SINGLE ALT=GROUP ALT=E_GROUP ALT=REMOTE MULTICHOICE)"
"TYPE(ALT=PARALYZE ALT=DRAIN_LVL ALT=SCRY_SIGHT ALT=SHIELD "
"ALT=HIT_BONUS ALT=VISION ALT=LIFE_DRAIN ALT=HEAL ALT=DAMAGE "
"ALT=YOUTH ALT=AGING ALT=CURE_POISON ALT=RESURRECT ALT=KILL "
"MULTICHOICE)"
"DURATION(MIN=0 MAX=250)"
"MHD(MIN=1 MAX=250)"
"XMHD(MIN=1 MAX=250)"
"TEXT(MIN=3)"
"DONE(ALT=SAVE ALT=QUIT MULTICHOICE)";

static CHAR raceans[] =      // Race answer string
"RANAME=%s%c"
"RACAST=%d%c"
"RAMR=%d%c"
"RASTR=%d%c"
"RAMSTR=%d%c"
"RADEX=%d%c"
"RAMDEX=%d%c"
"RAEARTH=%d%c"
"RAINT1=%d%c"
"RAMINT1=%d%c"
"RAAIR=%d%c"
"RAWIS=%d%c"
"RAMWIS=%d%c"
"RAWATER=%d%c"
"RACON=%d%c"
"RAMCON=%d%c"
"RAFIRE=%d%c"
"RACHR=%d%c"
"RAMCHR=%d%c"
"RALCK=%d%c"
"RAMLCK=%d%c"
"RAHP=%d%c";

static CHAR racefld[] =      // Race field string
"RANAME(MIN=3)"
"RACAST(MIN=0 MAX=100)"
"RAMR(MIN=0 MAX=100)"
"RASTR(MIN=-5 MAX=5)"
"RAMSTR(MIN=10 MAX=25)"
"RADEX(MIN=-5 MAX=5)"
"RAMDEX(MIN=10 MAX=25)"
"RAEARTH(MIN=0 MAX=100)"
"RAINT1(MIN=-5 MAX=5)"
"RAMINT1(MIN=10 MAX=25)"
"RAAIR(MIN=0 MAX=100)"
"RAWIS(MIN=-5 MAX=5)"
"RAMWIS(MIN=10 MAX=25)"
"RAWATER(MIN=0 MAX=100)"
"RACON(MIN=-5 MAX=5)"
"RAMCON(MIN=10 MAX=25)"
"RAFIRE(MIN=0 MAX=100)"
"RACHR(MIN=-5 MAX=5)"
"RAMCHR(MIN=10 MAX=25)"
"RALCK(MIN=-5 MAX=5)"
"RAMLCK(MIN=10 MAX=25)"
"RAHP(MIN=-5 MAX=5)"
"DONE(ALT=SAVE ALT=QUIT MULTICHOICE)";

static CHAR monstans[] =
"MONAME=%s%c"
"MOLVL=%d%c"
"MOARMOR=%d%c"
"MOMOVES=%d%c"
"MOHP=%d%c"
"MOATT=%d%c"
"MODMG=%d%c"
"MOSP=%s%c"
"MOAPPEAR=%d%c"
"MOAMSG=%s%c"
"MOMR=%d%c"
"MOEARTH=%d%c"
"MOAIR=%d%c"
"MOWATER=%d%c"
"MOFIRE=%d%c"
"MORTYPE=%s%c"
"MORMSG=%s%c"
"MORDMG=%d%c"
"MORRANGE=%d%c"
"MORSP=%s%c"
"MORCH=%d%c"
"MOWEP=%d%c"
"MOARM=%d%c"
"MORIN=%d%c"
"MOPOT=%d%c"
"MOSTO=%d%c"
"MOAMU=%d%c"
"MOSCR=%d%c"
"MOGOLD=%d%c"
"MOEXP=%d%c";

static CHAR monstfld[] =
"MONAME(MIN=3)"
"MOLVL(MIN=1 MAX=15)"
"MOARMOR(MIN=0 MAX=250)"
"MOMOVES(MIN=1 MAX=5)"
"MOHP(MIN=1 MAX=999)"
"MOATT(MIN=1 MAX=5)"
"MODMG(MIN=1 MAX=100)"
"MOSP(ALT=N/A ALT=POISON ALT=LVL_DRAIN ALT=LIFE_DRAIN ALT=AGING "
"ALT=PARALYSIS ALT=CRITICAL ALT=HEAL ALT=SHIELD MULTICHOICE)"
"MOAPPEAR(MIN=1 MAX=10)"
"MOAMSG(MIN=3)"
"MOMR(MIN=0 MAX=100)"
"MOEARTH(MIN=0 MAX=100)"
"MOAIR(MIN=0 MAX=100)"
"MOWATER(MIN=0 MAX=100)"
"MOFIRE(MIN=0 MAX=100)"
"MORTYPE(ALT=N/A ALT=SELF ALT=SINGLE ALT=MON_GROUP ALT=PLY_GROUP MULTICHOICE)"
"MORMSG(MIN=3)"
"MORDMG(MIN=0 MAX=100)"
"MORRANGE(MIN=0 MAX=15)"
"MORSP(ALT=N/A ALT=POISON ALT=LVL_DRAIN ALT=LIFE_DRAIN ALT=AGING "
"ALT=PARALYSIS ALT=CRITICAL ALT=HEAL ALT=SHIELD MULTICHOICE)"
"MORCH(MIN=0 MAX=100)"
"MOWEP(MIN=0 MAX=100)"
"MOARM(MIN=0 MAX=100)"
"MORIN(MIN=0 MAX=100)"
"MOPOT(MIN=0 MAX=100)"
"MOSTO(MIN=0 MAX=100)"
"MOAMU(MIN=0 MAX=100)"
"MOSCR(MIN=0 MAX=100)"
"MOGOLD(MIN=0 MAX=65000)"
"MOEXP(MIN=0 MAX=65000)"
"DONE(ALT=SAVE ALT=QUIT MULTICHOICE)";

VOID prepfsd(SHORT msgno, SHORT amode, SHORT newitem)
{
    fsdroom(msgno, dbfields, amode);
    if (newitem) {
        sprintf(vdatmp, dbanswer, objinf.objname, '\0'
            , 0, '\0'
            , "N/A", '\0'
            , "WEAPON", '\0'
            , "A", '\0'
            , 0, '\0'
            , 0, '\0'
            , 0, '\0'
            , 0, '\0'
            , 0, '\0'
            , 0, '\0'
            , 0, '\0'
            , 0, '\0'
            , 0, '\0'
            , 0, '\0'
            , "N/A", '\0'
            , "N/A", '\0'
            , "WEAR", '\0'
            , 0, '\0'
            , 0, '\0'
            , 0, '\0'
            , "SHOP", '\0'
            , l2as(0), '\0');
    } else {
        sprintf(vdatmp, dbanswer, objinf.objname, '\0',
            objinf.oweight, '\0',
            mu1[objinf.ospot], '\0',
            mu2[objinf.otype], '\0',
            mu3[objinf.oclass], '\0',
            objinf.oeffect[0], '\0',
            objinf.oeffect[1], '\0',
            objinf.oeffect[2], '\0',
            objinf.oeffect[3], '\0',
            objinf.oeffect[4], '\0',
            objinf.oeffect[5], '\0',
            objinf.oeffect[6], '\0',
            objinf.oac, '\0',
            objinf.omd, '\0',
            objinf.orange, '\0',
            mu4[objinf.ortype], '\0',
            mu5[objinf.osp], '\0',
            mu6[objinf.owhat], '\0',
            objinf.ocsp, '\0',
            objinf.otsp, '\0',
            objinf.osphd, '\0',
            mu7[objinf.owho], '\0',
            l2as(objinf.ocost), '\0');
    }
    fsdapr(zvda->buff, edtsize, vdatmp);
}

VOID fsd_finish(SHORT save)
{
    CHAR inbuf[20];
    CHAR ctr = 0;
    OBJINF tobj;

    setmbk(msgblk);
    if (fsdscb->chgcnt == 0) { prfmsg(NONEW); }   // no changes made...
    else if (!save) { prfmsg(NOSAVE); }        // abort, don't save changes...
    else {
        strcpy(objinf.objname, fsdnan(OBNAMEFLD));
        objinf.oweight = (CHAR)atoi(fsdnan(OBWEIGHT));
        strcpy(inbuf, fsdnan(OBSPOT));
        do { objinf.ospot = ctr; ctr++; } while (!(sameas(inbuf, mu1[ctr - 1])));
        ctr = 0;
        strcpy(inbuf, fsdnan(OBTYPE));
        do { objinf.otype = ctr; ctr++; } while (!(sameas(inbuf, mu2[ctr - 1])));
        ctr = 0;
        strcpy(inbuf, fsdnan(OBCLASS));
        do { objinf.oclass = ctr; ctr++; } while (!(sameas(inbuf, mu3[ctr - 1])));
        objinf.oeffect[0] = (CHAR)atoi(fsdnan(OBSTR));
        objinf.oeffect[1] = (CHAR)atoi(fsdnan(OBDEX));
        objinf.oeffect[2] = (CHAR)atoi(fsdnan(OBINT));
        objinf.oeffect[3] = (CHAR)atoi(fsdnan(OBWIS));
        objinf.oeffect[4] = (CHAR)atoi(fsdnan(OBCON));
        objinf.oeffect[5] = (CHAR)atoi(fsdnan(OBCHR));
        objinf.oeffect[6] = (CHAR)atoi(fsdnan(OBLCK));
        objinf.oac = (CHAR)atoi(fsdnan(OBAC));
        objinf.omd = (CHAR)atoi(fsdnan(OBMD));
        objinf.orange = (CHAR)atoi(fsdnan(OBRANGE));
        ctr = 0;
        strcpy(inbuf, fsdnan(OBRTYPE));
        do { objinf.ortype = ctr; ctr++; } while (!(sameas(inbuf, mu4[ctr - 1])));
        ctr = 0;
        strcpy(inbuf, fsdnan(OBSP));
        do { objinf.osp = ctr; ctr++; } while (!(sameas(inbuf, mu5[ctr - 1])));
        strcpy(inbuf, fsdnan(OBWHAT));
        do { objinf.owhat = ctr; ctr++; } while (!(sameas(inbuf, mu6[ctr - 1])));
        objinf.ocsp = (CHAR)atoi(fsdnan(OBCSP));
        objinf.otsp = (SHORT)atoi(fsdnan(OBTSP));
        objinf.osphd = (SHORT)atoi(fsdnan(OBSPHD));
        strcpy(inbuf, fsdnan(OBWHO));
        do { objinf.owho = ctr; ctr++; } while (!(sameas(inbuf, mu7[ctr - 1])));
        objinf.ocost = (ULONG)atol(fsdnan(OBCOST));

        prfmsg(NEWDATA);
        dfaSetBlk(miscitem);
        if (dfaAcqEQ(&tobj, objinf.objname, 0)) { dfaUpdate(&objinf); } else { dfaInsert(&objinf); }
        dfaRstBlk();
    }
    usrptr->state = modnum;
    condex();
    prfmsg(OBJMNU, "Object", "Object");
    usrptr->substt = 11;
    rstmbk();
}

VOID spfsd(SHORT msgno, SHORT amode, SHORT newitem)
{
    fsdroom(msgno, spellfld, amode);
    if (newitem) {
        sprintf(vdatmp, spellans, spellinf.spellname, '\0',
            1, '\0',
            "EARTH", '\0',
            "MAGE", '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            "N/A", '\0',
            "PARALYZE", '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            "Spell text goes here", '\0');
    } else {
        sprintf(vdatmp, spellans, spellinf.spellname, '\0',
            spellinf.level, '\0',
            sp1[spellinf.element], '\0',
            sp2[spellinf.class], '\0',
            spellinf.mp, '\0',
            spellinf.range, '\0',
            spellinf.xrange, '\0',
            sp3[spellinf.target], '\0',
            sp4[spellinf.type], '\0',
            spellinf.duration, '\0',
            spellinf.mhd, '\0',
            spellinf.xmhd, '\0',
            spellinf.text, '\0');
    }
    fsdapr(zvda->buff, edtsize, vdatmp);
}

VOID spfsd_finish(SHORT save)
{
    CHAR inbuf[20];
    CHAR ctr = 0;
    SPELLINF tobj;

    setmbk(msgblk);
    if (fsdscb->chgcnt == 0) { prfmsg(NONEW); }   // no changes made...
    else if (!save) { prfmsg(NOSAVE); }        // abort, don't save changes...
    else {
        strcpy(spellinf.spellname, fsdnan(SPNAME));
        spellinf.level = (CHAR)atoi(fsdnan(SPLEVEL));
        strcpy(inbuf, fsdnan(SPELEMENT));
        do { spellinf.element = ctr; ctr++; } while (!(sameas(inbuf, sp1[ctr - 1])));
        ctr = 0;
        strcpy(inbuf, fsdnan(SPCLASS));
        do { spellinf.class = ctr; ctr++; } while (!(sameas(inbuf, sp2[ctr - 1])));
        spellinf.mp = (CHAR)atoi(fsdnan(SPMP));
        spellinf.range = (CHAR)atoi(fsdnan(SPRANGE));
        spellinf.xrange = (CHAR)atoi(fsdnan(SPXRANGE));
        ctr = 0;
        strcpy(inbuf, fsdnan(SPTARGET));
        do { spellinf.target = ctr; ctr++; } while (!(sameas(inbuf, sp3[ctr - 1])));
        ctr = 0;
        strcpy(inbuf, fsdnan(SPTYPE));
        do { spellinf.type = ctr; ctr++; } while (!(sameas(inbuf, sp4[ctr - 1])));
        spellinf.duration = (CHAR)atoi(fsdnan(SPDURAT));
        spellinf.mhd = (CHAR)atoi(fsdnan(SPMHD));
        spellinf.xmhd = (CHAR)atoi(fsdnan(SPXMHD));
        strcpy(spellinf.text, fsdnan(SPTEXT));

        prfmsg(NEWDATA);
        dfaSetBlk(dbspells);
        if (dfaAcqEQ(&tobj, spellinf.spellname, 0)) { dfaUpdate(&spellinf); } else { dfaInsert(&spellinf); }
        dfaRstBlk();
    }
    usrptr->state = modnum;
    condex();
    prfmsg(OBJMNU, "Spell", "Spell");
    usrptr->substt = 14;
    rstmbk();
}

VOID rafsd(SHORT msgno, SHORT amode, SHORT newitem)
{
    fsdroom(msgno, racefld, amode);
    if (newitem) {
        sprintf(vdatmp, raceans, raceinf.name, '\0',
            0, '\0',
            0, '\0',
            0, '\0',     // STR
            10, '\0',
            0, '\0',     // DEX
            10, '\0',
            0, '\0',     // EARTH
            0, '\0',     // INT
            10, '\0',
            0, '\0',     // AIR
            0, '\0',     // WIS
            10, '\0',
            0, '\0',     // WATER
            0, '\0',     // CON
            10, '\0',
            0, '\0',     // FIRE
            0, '\0',     // CHR
            10, '\0',
            0, '\0',     // LCK
            10, '\0',
            0, '\0');
    } else {
        sprintf(vdatmp, raceans, raceinf.name, '\0',
            raceinf.cast, '\0',
            raceinf.mr, '\0',
            raceinf.modify[0], '\0',
            raceinf.maxability[0], '\0',
            raceinf.modify[1], '\0',
            raceinf.maxability[1], '\0',
            raceinf.earth, '\0',
            raceinf.modify[2], '\0',
            raceinf.maxability[2], '\0',
            raceinf.air, '\0',
            raceinf.modify[3], '\0',
            raceinf.maxability[3], '\0',
            raceinf.water, '\0',
            raceinf.modify[4], '\0',
            raceinf.maxability[4], '\0',
            raceinf.fire, '\0',
            raceinf.modify[5], '\0',
            raceinf.maxability[5], '\0',
            raceinf.modify[6], '\0',
            raceinf.maxability[6], '\0',
            raceinf.modify[7], '\0');
    }
    fsdapr(zvda->buff, edtsize, vdatmp);
}

VOID rafsd_finish(SHORT save)
{
    RACEINF tobj;

    setmbk(msgblk);
    if (fsdscb->chgcnt == 0) { prfmsg(NONEW); }   // no changes made...
    else if (!save) { prfmsg(NOSAVE); }        // abort, don't save changes...
    else {
        strcpy(raceinf.name, fsdnan(RANAME));
        raceinf.cast = (CHAR)atoi(fsdnan(RACAST));
        raceinf.mr = (CHAR)atoi(fsdnan(RAMR));
        raceinf.modify[0] = (SHORT)atoi(fsdnan(RASTR));
        raceinf.maxability[0] = (CHAR)atoi(fsdnan(RAMSTR));
        raceinf.modify[1] = (SHORT)atoi(fsdnan(RADEX));
        raceinf.maxability[1] = (CHAR)atoi(fsdnan(RAMDEX));
        raceinf.earth = (CHAR)atoi(fsdnan(RAEARTH));
        raceinf.modify[2] = (SHORT)atoi(fsdnan(RAINT1));
        raceinf.maxability[2] = (CHAR)atoi(fsdnan(RAMINT1));
        raceinf.air = (CHAR)atoi(fsdnan(RAAIR));
        raceinf.modify[3] = (SHORT)atoi(fsdnan(RAWIS));
        raceinf.maxability[3] = (CHAR)atoi(fsdnan(RAMWIS));
        raceinf.water = (CHAR)atoi(fsdnan(RAWATER));
        raceinf.modify[4] = (SHORT)atoi(fsdnan(RACON));
        raceinf.maxability[4] = (CHAR)atoi(fsdnan(RAMCON));
        raceinf.fire = (CHAR)atoi(fsdnan(RAFIRE));
        raceinf.modify[5] = (SHORT)atoi(fsdnan(RACHR));
        raceinf.maxability[5] = (CHAR)atoi(fsdnan(RAMCHR));
        raceinf.modify[6] = (SHORT)atoi(fsdnan(RALCK));
        raceinf.maxability[6] = (CHAR)atoi(fsdnan(RAMLCK));
        raceinf.modify[7] = (SHORT)atoi(fsdnan(RAHP));

        prfmsg(NEWDATA);
        dfaSetBlk(dbrace);
        if (dfaAcqEQ(&tobj, raceinf.name, 0)) { dfaUpdate(&raceinf); } else { dfaInsert(&raceinf); }
        dfaRstBlk();
    }
    usrptr->state = modnum;
    condex();
    usrptr->substt = 16;
    prfmsg(OBJMNU, "Race", "Race");
    rstmbk();
}

VOID clfsd(SHORT msgno, SHORT amode, SHORT newitem)
{

    fsdroom(msgno, classfld, amode);
    if (newitem) {
        sprintf(vdatmp, classans, classinf.name, '\0',
            4, '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            4, '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "NO", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "NO", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "NO", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "NO", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "NO", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "NO", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "NO", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "NO", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "0000000000", '\0',
            "0000000000", '\0',
            "00000000000", '\0',
            "0000000000", '\0',
            "000000000", '\0',
            "0000000000", '\0');
    } else {
        sprintf(vdatmp, classans, classinf.name, '\0',
            classinf.hp, '\0',
            classinf.mage[0], '\0',
            classinf.priest[0], '\0',
            classinf.exp[0], '\0',
            classinf.mage[1], '\0',
            classinf.priest[1], '\0',
            classinf.exp[1], '\0',
            classinf.mp, '\0',
            classinf.mage[2], '\0',
            classinf.priest[2], '\0',
            classinf.exp[2], '\0',
            classinf.mage[3], '\0',
            classinf.priest[3], '\0',
            classinf.exp[3], '\0',
            classinf.mage[4], '\0',
            classinf.priest[4], '\0',
            classinf.exp[4], '\0',
            cl1[classinf.objects[0]], '\0',
            classinf.mage[5], '\0',
            classinf.priest[5], '\0',
            classinf.exp[5], '\0',
            cl1[classinf.objects[1]], '\0',
            classinf.mage[6], '\0',
            classinf.priest[6], '\0',
            classinf.exp[6], '\0',
            cl1[classinf.objects[2]], '\0',
            classinf.mage[7], '\0',
            classinf.priest[7], '\0',
            classinf.exp[7], '\0',
            cl1[classinf.objects[3]], '\0',
            classinf.mage[8], '\0',
            classinf.priest[8], '\0',
            classinf.exp[8], '\0',
            cl1[classinf.objects[4]], '\0',
            classinf.mage[9], '\0',
            classinf.priest[9], '\0',
            classinf.exp[9], '\0',
            cl1[classinf.objects[5]], '\0',
            classinf.mage[10], '\0',
            classinf.priest[10], '\0',
            classinf.exp[10], '\0',
            cl1[classinf.objects[6]], '\0',
            classinf.mage[11], '\0',
            classinf.priest[11], '\0',
            classinf.exp[11], '\0',
            cl1[classinf.objects[7]], '\0',
            classinf.mage[12], '\0',
            classinf.priest[12], '\0',
            classinf.exp[12], '\0',
            classinf.mage[13], '\0',
            classinf.priest[13], '\0',
            classinf.exp[13], '\0',
            classinf.mage[14], '\0',
            classinf.priest[14], '\0',
            classinf.exp[14], '\0');

    }
    fsdapr(zvda->buff, edtsize, vdatmp);
}

VOID clfsd_finish(SHORT save)
{
    CHAR inbuf[20];
    CHAR ctr;//=0;
    CLASSINF tobj;

    setmbk(msgblk);
    if (fsdscb->chgcnt == 0) { prfmsg(NONEW); }   // no changes made...
    else if (!save) { prfmsg(NOSAVE); }        // abort, don't save changes...
    else {
        strcpy(classinf.name, fsdnan(CLNAME));
        classinf.hp = (CHAR)atoi(fsdnan(CLHP));
        strcpy(classinf.mage[0], fsdnan(CLMAGE1));
        strcpy(classinf.priest[0], fsdnan(CLPRIEST1));
        strcpy(classinf.exp[0], fsdnan(CLEXP1));
        strcpy(classinf.mage[1], fsdnan(CLMAGE2));
        strcpy(classinf.priest[1], fsdnan(CLPRIEST2));
        strcpy(classinf.exp[1], fsdnan(CLEXP2));
        classinf.mp = (CHAR)atoi(fsdnan(CLMP));
        strcpy(classinf.mage[2], fsdnan(CLMAGE3));
        strcpy(classinf.priest[2], fsdnan(CLPRIEST3));
        strcpy(classinf.exp[2], fsdnan(CLEXP3));
        strcpy(classinf.mage[3], fsdnan(CLMAGE4));
        strcpy(classinf.priest[3], fsdnan(CLPRIEST4));
        strcpy(classinf.exp[3], fsdnan(CLEXP4));
        strcpy(classinf.mage[4], fsdnan(CLMAGE5));
        strcpy(classinf.priest[4], fsdnan(CLPRIEST5));
        strcpy(classinf.exp[4], fsdnan(CLEXP5));
        ctr = 0;
        strcpy(inbuf, fsdnan(CLOBJ1));
        do { classinf.objects[0] = ctr; ctr++; } while (!(sameas(inbuf, cl1[ctr - 1])));
        strcpy(classinf.mage[5], fsdnan(CLMAGE6));
        strcpy(classinf.priest[5], fsdnan(CLPRIEST6));
        strcpy(classinf.exp[5], fsdnan(CLEXP6));
        ctr = 0;
        strcpy(inbuf, fsdnan(CLOBJ2));
        do { classinf.objects[1] = ctr; ctr++; } while (!(sameas(inbuf, cl1[ctr - 1])));
        strcpy(classinf.mage[6], fsdnan(CLMAGE7));
        strcpy(classinf.priest[6], fsdnan(CLPRIEST7));
        strcpy(classinf.exp[6], fsdnan(CLEXP7));
        ctr = 0;
        strcpy(inbuf, fsdnan(CLOBJ3));
        do { classinf.objects[2] = ctr; ctr++; } while (!(sameas(inbuf, cl1[ctr - 1])));
        strcpy(classinf.mage[7], fsdnan(CLMAGE8));
        strcpy(classinf.priest[7], fsdnan(CLPRIEST8));
        strcpy(classinf.exp[7], fsdnan(CLEXP8));
        ctr = 0;
        strcpy(inbuf, fsdnan(CLOBJ4));
        do { classinf.objects[3] = ctr; ctr++; } while (!(sameas(inbuf, cl1[ctr - 1])));
        strcpy(classinf.mage[8], fsdnan(CLMAGE9));
        strcpy(classinf.priest[8], fsdnan(CLPRIEST9));
        strcpy(classinf.exp[8], fsdnan(CLEXP9));
        ctr = 0;
        strcpy(inbuf, fsdnan(CLOBJ5));
        do { classinf.objects[4] = ctr; ctr++; } while (!(sameas(inbuf, cl1[ctr - 1])));
        strcpy(classinf.mage[9], fsdnan(CLMAGE10));
        strcpy(classinf.priest[9], fsdnan(CLPRIEST10));
        strcpy(classinf.exp[9], fsdnan(CLEXP10));
        ctr = 0;
        strcpy(inbuf, fsdnan(CLOBJ6));
        do { classinf.objects[5] = ctr; ctr++; } while (!(sameas(inbuf, cl1[ctr - 1])));
        strcpy(classinf.mage[10], fsdnan(CLMAGE11));
        strcpy(classinf.priest[10], fsdnan(CLPRIEST11));
        strcpy(classinf.exp[10], fsdnan(CLEXP11));
        ctr = 0;
        strcpy(inbuf, fsdnan(CLOBJ7));
        do { classinf.objects[6] = ctr; ctr++; } while (!(sameas(inbuf, cl1[ctr - 1])));
        strcpy(classinf.mage[11], fsdnan(CLMAGE12));
        strcpy(classinf.priest[11], fsdnan(CLPRIEST12));
        strcpy(classinf.exp[11], fsdnan(CLEXP12));
        ctr = 0;
        strcpy(inbuf, fsdnan(CLOBJ8));
        do { classinf.objects[7] = ctr; ctr++; } while (!(sameas(inbuf, cl1[ctr - 1])));
        strcpy(classinf.mage[12], fsdnan(CLMAGE13));
        strcpy(classinf.priest[12], fsdnan(CLPRIEST13));
        strcpy(classinf.exp[12], fsdnan(CLEXP13));
        strcpy(classinf.mage[13], fsdnan(CLMAGE14));
        strcpy(classinf.priest[13], fsdnan(CLPRIEST14));
        strcpy(classinf.exp[13], fsdnan(CLEXP14));
        //  strcpy(classinf.mage[14],fsdnan(CLMAGE15));
        strcpy(classinf.priest[14], fsdnan(CLPRIEST15));
        strcpy(classinf.exp[14], fsdnan(CLEXP15));

        prfmsg(NEWDATA);
        dfaSetBlk(dbclass);
        if (dfaAcqEQ(&tobj, classinf.name, 0)) { dfaUpdate(&classinf); } else { dfaInsert(&classinf); }
        dfaRstBlk();
    }
    usrptr->state = modnum;
    condex();
    usrptr->substt = 18;
    prfmsg(OBJMNU, "Class", "Class");
    rstmbk();
}

VOID mofsd(SHORT msgno, SHORT amode, SHORT newitem)
{
    fsdroom(msgno, monstfld, amode);
    if (newitem) {
        sprintf(vdatmp, monstans, monstinf.name, '\0',
            1, '\0',
            1, '\0',
            1, '\0',
            1, '\0',
            1, '\0',
            1, '\0',
            "N/A", '\0',
            1, '\0',
            "Attack msg goes here", '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            "N/A", '\0',
            "Ranged attack msg goes here", '\0',
            0, '\0',
            0, '\0',
            "N/A", '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            0, '\0',
            0, '\0');
    } else {
        sprintf(vdatmp, monstans, monstinf.name, '\0',
            monstinf.level, '\0',
            monstinf.ac, '\0',
            monstinf.moves, '\0',
            monstinf.hp, '\0',
            monstinf.attacks, '\0',
            monstinf.dmg, '\0',
            mon2[monstinf.spa], '\0',
            monstinf.appear, '\0',
            monstinf.amsg, '\0',
            monstinf.mr, '\0',
            monstinf.earth, '\0',
            monstinf.air, '\0',
            monstinf.water, '\0',
            monstinf.fire, '\0',
            mon1[monstinf.trange], '\0',
            monstinf.rmsg, '\0',
            monstinf.rdmg, '\0',
            monstinf.range, '\0',
            mon2[monstinf.spr], '\0',
            monstinf.chance, '\0',
            monstinf.weapon, '\0',
            monstinf.armor, '\0',
            monstinf.ring, '\0',
            monstinf.potion, '\0',
            monstinf.stone, '\0',
            monstinf.amulet, '\0',
            monstinf.scroll, '\0',
            monstinf.gold, '\0',
            monstinf.exp, '\0');
    }
    fsdapr(zvda->buff, edtsize, vdatmp);
}

VOID mofsd_finish(SHORT save)
{
    MONSTINF tobj;
    CHAR inbuf[30], ctr;

    setmbk(msgblk);
    if (fsdscb->chgcnt == 0) { prfmsg(NONEW); }   // no changes made...
    else if (!save) { prfmsg(NOSAVE); }        // abort, don't save changes...
    else {
        // Insert read from fsd code here!!
        strcpy(monstinf.name, fsdnan(MONAME));
        monstinf.level = (CHAR)atoi(fsdnan(MOLVL));
        monstinf.ac = (CHAR)atoi(fsdnan(MOARMOR));
        monstinf.moves = (CHAR)atoi(fsdnan(MOMOVES));
        monstinf.hp = (CHAR)atoi(fsdnan(MOHP));
        monstinf.attacks = (CHAR)atoi(fsdnan(MOATT));
        monstinf.dmg = (CHAR)atoi(fsdnan(MODMG));
        ctr = 0;
        strcpy(inbuf, fsdnan(MOSP));
        do { monstinf.spa = ctr; ctr++; } while (!(sameas(inbuf, mon2[ctr - 1])));
        monstinf.appear = (CHAR)atoi(fsdnan(MOAPPEAR));
        strcpy(monstinf.amsg, fsdnan(MOAMSG));
        monstinf.mr = (CHAR)atoi(fsdnan(MOMR));
        monstinf.earth = (CHAR)atoi(fsdnan(MOEARTH));
        monstinf.air = (CHAR)atoi(fsdnan(MOAIR));
        monstinf.water = (CHAR)atoi(fsdnan(MOWATER));
        monstinf.fire = (CHAR)atoi(fsdnan(MOFIRE));
        ctr = 0;
        strcpy(inbuf, fsdnan(MORTYPE));
        do { monstinf.trange = ctr; ctr++; } while (!(sameas(inbuf, mon1[ctr - 1])));
        strcpy(monstinf.rmsg, fsdnan(MORMSG));
        monstinf.rdmg = (CHAR)atoi(fsdnan(MORDMG));
        monstinf.range = (CHAR)atoi(fsdnan(MORRANGE));
        ctr = 0;
        strcpy(inbuf, fsdnan(MORSP));
        do { monstinf.spr = ctr; ctr++; } while (!(sameas(inbuf, mon2[ctr - 1])));
        monstinf.chance = (CHAR)atoi(fsdnan(MORCH));
        monstinf.weapon = (CHAR)atoi(fsdnan(MOWEP));
        monstinf.armor = (CHAR)atoi(fsdnan(MOARM));
        monstinf.ring = (CHAR)atoi(fsdnan(MORIN));
        monstinf.potion = (CHAR)atoi(fsdnan(MOPOT));
        monstinf.stone = (CHAR)atoi(fsdnan(MOSTO));
        monstinf.amulet = (CHAR)atoi(fsdnan(MOAMU));
        monstinf.scroll = (CHAR)atoi(fsdnan(MOSCR));
        monstinf.gold = (USHORT)atoi(fsdnan(MOGOLD));
        monstinf.exp = (USHORT)atoi(fsdnan(MOEXP));
        prfmsg(NEWDATA);
        dfaSetBlk(dbmonst);
        if (dfaAcqEQ(&tobj, monstinf.name, 0)) { dfaUpdate(&monstinf); } else { dfaInsert(&monstinf); }
        dfaRstBlk();
    }
    usrptr->state = modnum;
    condex();
    usrptr->substt = 20;
    prfmsg(OBJMNU, "Monster", "Monster");
    rstmbk();
}
