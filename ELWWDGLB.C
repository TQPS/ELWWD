/*****************************************************************************
 *   ELWWDGLB.C   V0.62                                 Worlds of Darkness   *
 *   Global Data Area                                                        *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 01/27/1995         *
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
#include "majorbbs.h"
#include "elwwdtyp.h"

MONSTINF monstinf;
SPELLINF spellinf;
RACEINF raceinf;
OBJINF objinf;
CLASSINF classinf;
// CLASSINF2 classinf2;
TEMP_PLAYER tplayer;  // Temp player

/*  Global Static Allocations */

SGRATE grates[MAXLEVELS + 1];

XPORTREC xports[MAXLEVELS + 1];

USHORT wspellcnt, cspellcnt, zclercnt, totmonst, zwepcnt,
mwaitt, xpcount[MAXLEVELS + 1], objcnt[MAXOBJCL],
racecnt, classcnt, zwizcnt, mench, iwpos, totpriz, totdrop;

CHAR xpchars[] = "+=|\\{}<>", kpress[8],
textletters[] = "ABCDEFGHIJKLPQWXZ*",
direct1[] = " NESW",
doorchars[] = " XY",
doorcolor[] = "@06",                       /*  Shit brown */
tpcolor[] = "@13",                           /*  pink       */

/* 0   1    2     3    4   5       6      7
   blk blue green cyan red magenta yellow white 1-8 (0 attr
   9-16 are as above but the 1 attibute */

    * wcolors[] = { "   ","@15","@07","@08","@06" },
    * wcolours[] = { "[32m","[31m","[35m","[36m","[34m","[33m","[37m" },

    /* Colors for the above line.  Color place routine
    White, Light Grey, Dark Grey, Shit Brown-------- */

    wchars[6] = " €‹ﬂ±";  // '±' made this wchars[6] to support termination - RH

/*
 button placement for rip/inventory screen
 Insert location 28 depending on color :
1= Dark Blue
6= Dark Brown
5= Dark Purple
4= Dark Red
2= Dark Green
3= Dark Cyan
*/

CHAR holdmap[TMROW + 1][TMCOL + 1],
holdter[TMROW + 1][TMCOL + 1],
orgholder[TMROW + 1][TMCOL + 1],
doorishere, curxy, terrain, somethingthere, somethingthere1,
facechar, wall[WDWH + 1][150], doorme, leverme, doortype, bonk,
exit_door, tempwall1[252], tempwall[252], ztimerf,
snooze[256], ingame[256], fredrop[MAXDROP];

INT modnum;

SHORT cantrun, xyloc[4],
truerow[TMROW + 1][TMCOL + 1], truecol[TMROW + 1][TMCOL + 1],
fvert, scol, srow, fwid, drcol, face4, face5,
edtsize, gdx, gdy,
thactbl[15] = { 20,18,16,14,12,10,8,7,6,5,4,3,2,1,0 };

LONG dropidx[MAXDROP];

CHAR mu1[7][10] = { {"N/A"},{"HEAD"},{"BODY"},{"FOOT"},{"NECK"},{"HAND"},
                {"2_HANDED"} };
CHAR mu2[7][10] = { {"WEAPON"},{"ARMOR"},{"RING"},{"POTION"},{"STONE"},
                {"AMULET"},{"SCROLL"} };
CHAR mu3[8][2] = { {"A"},{"B"},{"C"},{"D"},{"E"},{"F"},{"G"},{"H"} };
CHAR mu4[4][10] = { {"N/A"},{"ARROWS"},{"ROCKS"},{"DARTS"} };
CHAR mu5[13][15] = { {"N/A"},{"POISON"},{"CURE_POISON"},{"LVL_DRAIN"},
                 {"LIFE_DRAIN"},{"AGING"},{"PARALYSIS"},{"CRITICAL"},
                 {"HEAL"},{"X_DMG"},{"SHIELD"},{"CURSED"},{"VISION"} };
CHAR mu6[3][10] = { {"WEAR"},{"USE"},{"BATTLE"} };
CHAR mu7[3][10] = { {"SHOP"},{"MONSTER"},{"PERSONAL"} };


CHAR sp1[4][10] = { {"EARTH"},{"AIR"},{"WATER"},{"FIRE"} };
CHAR sp2[2][7] = { {"MAGE"},{"PRIEST"} };
CHAR sp3[5][10] = { {"N/A"},{"SINGLE"},{"GROUP"},{"E_GROUP"},{"REMOTE"} };
CHAR sp4[14][15] = { {"PARALYZE"},{"DRAIN_LVL"},{"SCRY_SIGHT"},{"SHIELD"},
                 {"HIT_BONUS"},{"VISION"},{"LIFE_DRAIN"},{"HEAL"},
                 {"DAMAGE"},{"YOUTH"},{"AGING"},{"CURE_POISON"},
                 {"RESURRECT"},{"KILL"} };

CHAR cl1[2][5] = { {"NO"},{"YES"} };

CHAR mon1[5][10] = { {"N/A"},{"SELF"},{"SINGLE"},{"MON_GROUP"},
                        {"PLY_GROUP"} };

CHAR mon2[9][15] = { {"N/A"},{"POISON"},{"LVL_DRAIN"},{"LIFE_DRAIN"},
                        {"AGING"},{"PARALYSIS"},{"CRITICAL"},{"HEAL"},
                        {"SHIELD"} };
/*
  File I/O stuff
*/
FILE* sysin, * sysout, * dropf, * wwall;
HMCVFILE msgblk;
struct ffblk utlfblk;
DFAFILE* miscitem, * dbspells, * dbclass, * dbrace, * dbmonst,
* dbplayer, * dbupdate;

/* Global Pointers */

SMAP* zmap, * zterrain;
VDABLK* zvda, * xlvda, * zldr, * covda;
PLYRINF* zplyr;
OBJINF* zpobj, * wepbase, * armbase, * rinbase, * potbase, * stobase,
* amubase, * scrbase, * przbase;
struct usracc* uaptr;
//static char *edtptr;
SPELLINF* wizspell, * clerspell;
STORE* zcler, * zwiz;
WSTOR* zwep;
MONENT* monbase;
CBREC* zcbr;
CLASSENT* classbase;
RACENT* racebase;
DPITEM* dpbase;

// Generic status stuff
SHORT gamestat;
CHAR vernum[10];
ULONG reload_cost;

// RIP Stuff, needs to be global...  (Maybe)

CHAR ver_rip;
CHAR rstr[10];
SHORT lbutheight, arip1, arip2;
