/*****************************************************************************
 *   ELWWDTYP.H   V0.62                                 Worlds of Darkness   *
 *   TypeDef Structures                                                      *
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

/* World defines */

#define MAXICNS 300      // Maximum icons to be found in the directory.
#define MAXTP 16         /* xporters per level */
#define MAPHEIGHT 50
#define MAPWIDTH  70
#define MAXLEVELS 16     /* abs max. do not set higher than 16 */
#define ACTLEVELS 9      /* actual # of levels present */
#define MAXGRATES 13
#define MAXDUPLEVER 8    /* max levers per single door */
#define MAXCLASS 2600    /* max # of player classes        */
#define MAXRACES 2600    /* max # of player races          */
#define MAXPRIZ 1000     /* max # of prizes */

#define MAXININVENT 21
#define MAXDROP 9300

/* Drawing Defines */
#define TMROW 4          /* rows for map temp array */
#define TMCOL 5          /* cols for temp map array */
#define WDWH 12          /* window height           */


                                        /* Misc defines */
#define NOTFOUND -1
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif
#define plevel zplyr->curlvl
#define prow zplyr->row
#define pcol zplyr->col
#define pdirect zplyr->direct
#define RIPBUTX  215
#define RIPBUTY  5
#define BLINK_OFF 0
#define BLINK_ON  1
#define INTENSITY_OFF 0
#define INTENSITY_ON 1
#define insbutcol 28
#define insbut   21
#define ANSMENU 500
#define RIPMENU 501
#define ANSYNO  502
#define DOZING  503
#define WFANUM  504
#define FATALE  505
#define CAMPIN  506
#define MAXOBJ 1000
#define MAXOBJCL 7
#define MAXPOBJC 20                 /* max objs ply kin carry */
#define MAXSPELL 700
#define INACTIVE 0
#define ISACTIVE 1
#define PLAYING 2
#define INCHAT 3
#define INFITE 4
#define TAVCHT 5
#define MAXMONST 10000                  /* # monent entries  */
#define NOTYET 0
#define WONIT 1
#define LOSTIT 2
#define ALIVE 222
#define HITMON 2
#define HITPLYR 3
#define HITXIT 4
#define THACP 125              /* ac for thactbl values */
                               /* World structure definitions

                                  teleporter && switch stuff */

typedef struct {
 CHAR xportx[MAXTP],xporty[MAXTP],xportc[MAXTP];
} XPORTREC;

typedef struct {
 CHAR  levercnt[MAXGRATES],
 leverstate[MAXGRATES][MAXDUPLEVER],
     leverrow[MAXGRATES][MAXDUPLEVER],
     levercol[MAXGRATES][MAXDUPLEVER];
} SGRATE;

typedef struct {
CHAR map[MAPHEIGHT+1][MAPWIDTH+2];
} AMAP;

typedef struct {
AMAP lvl[MAXLEVELS+1];
} SMAP;

/* attrib
   Str Dex SHORT Wis Con Chr Lck
   1st 7 are the current attribute
   2nd 7 are the real attributes minus boosters
*/
typedef struct {           // player data structure for in game and saving 
    CHAR  name[30],        // 000-029
          attrib[21],      // 030-050
          condition[30],   // 051-080
          equip[MAXPOBJC], // 081-100
          age,             // 101
          new_age,         // 102
          currhp,          // 103
          maxhp,           // 104
          currmp,          // 105
          maxmp,           // 106
          level,           // 107
          lvl_drain;       // 108
    CHAR  pack;            // xxx     109      packed byte from compiler
    SHORT class,           // 109-110 110-111
          race;            // 111-112 112-113
    SHORT arrows,          // 113-114 114-115
          rocks,           // 115-116 116-117
          darts;           // 117-118 118-119
    SHORT mage_new[9],     // 119-136 120-137
          cleric_new[9];   // 137-154 138-155
    SHORT mage[45],        // 155-244 156-245
          cleric[45];      // 245-334 246-335
    CHAR  row,             // 335     336
          col,             // 336     337
          curlvl,          // 337     338
          direct;          // 338     339
    ULONG encloss,         // 339-342 340-343
          enckills,        // 343-346 344-347
          exp,             // 347-350 348-351
          cash,            // 351-354 352-355
          bank,            // 355-358 356-359
          loan,            // 359-362 360-363
          intrest,         // 363-366 364-367
          lowinvest,       // 367-370 368-371
          medinvest,       // 371-374 372-375
          highinvest;      // 375-378 376-379
    CHAR  spare[500 - 380];  // 379-499 380-500   decreased size by 1 for v10   
} PLYRINF; // Size 500 wg32, 500 V10 now with spare adjustment

/*
  add as needed
  Condition :  [0] Drunk  [1] Poison [2] Paralyzed [3] Pz Tleft
               [4] Shielded [5] Shl Tleft [6]VizTime [7]Poi Lft
               [8] Comp [9]DirLc
               [20]=CredR [21]=%I [22]=Term [23]=Elapsed
*/


/*
  Monster Stuff
*/

typedef struct {        // monster data - ELWWDMON.DAT
    CHAR name[30],        // 000-029                         *KEY*
         level,           // 030
         ac,              // 031
         moves,           // 032
         hp,              // 033
         attacks,         // 034
         dmg,             // 035
         spa,             // 036
         appear,          // 037
         amsg[50],        // 038-087
         mr,              // 088
         earth,           // 089
         air,             // 090
         water,           // 091 
         fire,            // 092
         trange,          // 093
         rmsg[50],        // 094-143
         rdmg,            // 144
         range,           // 145
         spr,             // 146
         chance,          // 147
         weapon,          // 148
         armor,           // 149
         ring,            // 150
         potion,          // 151
         stone,           // 152
         amulet,          // 153
         scroll;          // 154
    CHAR pack;            // xxx              packed byte from compiler
  USHORT gold,            // 155-156 156-157
         exp;             // 157-158 158-159
    // Size 159 wg32, 160 v10
} MONSTINF;


typedef struct {
LONG monpos;
CHAR monlvl;
} MONENT;

/*
  Spell Stuff
*/
typedef struct {         // Spell data - ELWWDSPE.DAT
    CHAR spellname[20],   // 00-19 The name of the spell             *KEY*
        level,            // 20-20 The level spell can be earned
        element,          // 21-21 Element of spell (Earth, Air, Water, Fire)
        class,            // 22-22 Class of caster (0=Mage, 1=Priest)
        mp,               // 23-23 Magic Points used to cast spell
        range,            // 24-24 Range spell can go.
        xrange,           // 25-25 X-tra range per lvl of caster
        target,           // 26-26 N/A (Self), Single, Group, E-Group, Remote
        type,             // 27-27 Type of spell.
        duration,         // 28-28 Duration.  How long the spell lasts
        mhd,              // 29-29 Max heal/dmg/ac bonuses...
        xmhd,             // 30-30 X-tra heal/dmg/ac bonuses per lvl of caster...
        text[60];         // 31-90 What it says when you cast it.
} SPELLINF;               // Size 91 on wg32 and v10

/*
 Player Races
*/
typedef struct {         // The race structure - ELWWDRAC.DAT
    CHAR name[20],       // 00-19 Name of Race  *KEY*
        cast,            // 20-20 Casting %
        mr,              // 21-21 Magic Resistance
        earth,           // 22-22 MR Earth realm
        air,             // 23-23 MR Air realm
        water,           // 24-24 MR Water realm
        fire,            // 25-25 MR Fire realm
        maxability[7];   // 26-32 Max ability can be.  (25 is overall max)
    CHAR pack;           // xxx   33      packed byte from compiler
    SHORT  modify[8];    // 33-48 34-49 Modifiers to Attribs, (STR, DEX... HP)
} RACEINF;           // size 50 in V10

typedef struct {
CHAR name[20];
LONG racepos;
} RACENT;

/*
  Objects that player can carry/wear
*/
typedef struct {          // Object information - ELWWDOBJ.DAT
    CHAR  objname[20];    // 00-19 name of object                  *KEY*
    CHAR  oweight,        // 20-20 weight of object
          ospot,          // 21-21 wear it: Head,Foot,Body,Hand,etc
          otype,          // 22-22 Object type a=armor,w=weapon,s=scroll?
          oclass,         // 23-23 Object class.  Class type can use.
          oeffect[7],     // 24-30 effect to the 7 player attribs
          oac,            // 31-31 Armor points
          omd,            // 32-32 Max damage item can do.  (Weapon only)
          orange,         // 33-33 Range of object (If range Weapon)
          ortype,         // 34-34 Range type missle. (arrow, rocks....)
          osp,            // 35-35 Special Ability
          owho,           // 36-36 Weapshop, Monster, Personal
          owhat,          // 37-37 What you have to do with item.
          ocsp;           // 38-38 Chance SP will function if used
    CHAR  pack;           // xxx   39      packed byte from compiler
    SHORT otsp,           // 39-40 40-41 Times SP can be used 
          osphd;          // 41-42 42-43 Healing/Damage power of SP
    ULONG ocost;          // 43-46 44-47 cost of object
    CHAR  spare[60 - 48]; // 47-59 48-60   Max of 60 bytes per item.
} OBJINF;                 // Size 60 WG32, 60 V10 now with spare adjustment

typedef struct {           // Class information - ELWWDCLA.DAT
    CHAR name[20],         // 000-019 The name of this class  **KEY**
         hp,               // 020-020 Hit points gained per level (Max)
         mp,               // 021-021 Magic points gained per level
         objects[8],       // 022-029 Object types class can use.  (A-H in types)
         mage[15][10],     // 030-179 Mage spells earned per level.  (15 Lvls)
         priest[15][10],   // 180-329 Cleric spells earned per level.  (15 Lvls)
         exp[15][11];      // 330-494 When user goes up 1 lvl.  (15 Lvls)
    CHAR spare[600 - 495]; // 495-599
} CLASSINF;                // size 600 in wg32 and v10

typedef struct {
CHAR name[20];
LONG classpos;
} CLASSENT;


typedef struct {
OBJINF stobj[15];
SPELLINF stspells[15];
CHAR strow,stcol,stchar,stlevel;
USHORT stobcnt,stospcnt;
} STORE;

typedef struct {
OBJINF wobj[15];
OBJINF aobj[15];
CHAR strow,stcol,stchar,stlevel;
USHORT wpncnt,armcnt;
} WSTOR;

/*
 mcond[][0]=poison
 mcond[][1]=paralyze
 mcond[][2]=paralyze turns left
 mcond[][3]=shield
 mcond[][4]=shield turns
 mcond[][5]=Poi Lft
*/
typedef struct {
SHORT plyrs[12],pcnt,mcount,wfor,pgrp[12];
CHAR monx[10],mony[10],plx[12],ply[12],
 xitx,xity,entype,mxlife[10],oplx[12],oply[12],
 omonx[10],omony[10],chx,chy,ochx,ochy,umov[10],uatak[10],
 mcond[10][9],mrape[10],ptikf,redf,mdrf,fmtik,fcol;
USHORT tick,mtick,curmn,ptick;
MONSTINF cmonst[10];
} CBREC;

/*
  Player VDA
*/

typedef struct {
 PLYRINF plyr;
 RACEINF prace;
 CLASSINF pclass;
 SPELLINF *savpzp;
 OBJINF  pstuff[MAXPOBJC];
 CHAR specialrip,itemaction,emov,incycle,mdrf,
  background,forground,ripos,rip,movingaround,spelltrue,
  noreset,abort,infight,paging,neverdraw,redo,xhair,rdlife,
  ansi_on,lastwindow,buywindow,ripclr1,ripclr2,noyano,
  endgame,dead,redraw,clrbonk,stimer,nplife,cstype,dwho[2],nwscnt,
  nstat,stmode,dpch,eye,yakmsg[158],yakflag,lmode,
  oview[7][7],invf[256],cnews[7][81],yakusr[30];
 SHORT oldripcol,party,gstate,members[6],obx,oby,ontop,dwhon[2],
  oldont,pdraw,cstate,cbrnum,cbrpos,cdraw,cnewsf,litcnt,
  lac,ovchn[49],spdmg,lastch;
 USHORT cshop,obsize,memcnt,obn,pwtick,dplist[17];
 ULONG lastcost,lastnum, needed;
 struct user *myuser;
/* menu stuff */
 SHORT mnumax,mnupos,rstate,mnucol,mnurow,mnuwid,mstate,mlkey,
 oustate,oumstate,uxitk,mnucnt,mpstate,mnulast;
 CHAR mnukey,mnustr[31],mnuslt[MAXPOBJC],mnupage;

/* listing routines for the editors */
 USHORT tick;
 CHAR curpos[30], dblist[10], buff[3501]; // for the VDA editors
 SHORT nxtstt, retstt, extstt, scan, scanmax, curlang, ripver, curfile;
 CHAR dlf[17], query[1024];
 SHORT dlme[300];
 CHAR plist[50][35], plast, chkdate[9], rip_path[60];
 CHAR score[11];
 FILE *readfile;       // Viewing a on-line file..............
} VDABLK;

/* file save btrieve structure */

typedef struct {                 // player data file - ELWWDPLY.DAT
    CHAR    name[30];            // 0000-0029   **KEY**
    CHAR    score[10];           // 0030-0039
    PLYRINF plyr;                // 0040-0539 -  500 bytes - same size but different offsets
    OBJINF  pstuff[MAXPOBJC];    // 0540-1739 - 1200 bytes - same size but different offsets
    CHAR    spare[2000 - 1740];  // 1740-1999 - 2000 Bytes Total
} TEMP_PLAYER;                   // Size 2000 wg32 and v10

typedef struct {
CHAR dx,dy,dlvl;
USHORT idxpos;
} DPITEM;

typedef struct {
CHAR dx,dy,dlvl;
OBJINF dpobj;
} DPREC;

typedef struct {
CHAR name[13];
CHAR date[9];
} RIP_ICONS;
