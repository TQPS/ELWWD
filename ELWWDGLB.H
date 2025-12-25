/*****************************************************************************
 *   ELWWDGLB.H   V0.62                                 Worlds of Darkness   *
 *   Globals                                                                 *
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


//#define ZARKALF                 /* supply defaults Allow special edits*/
#undef ZARKALF                 /* supply defaults */
extern USHORT ticker;          /* GSBL 1 second timer */
#define INCFSD

/* Procedure declarations */
//elwwd.c
VOID EXPORT init__wd(VOID);
VOID solvekey(VOID);
VOID animate(VOID);
VOID initplayer(VOID);
VOID plinit(VOID);
VOID dispmain(VOID);
SHORT wdmain(VOID);
VOID wdcycle(VOID);
VOID wddrop(VOID);
VOID wdterm(VOID);

//elwwdenc.c
SHORT chkusage(CHAR icls);
VOID chkexp(VOID);
VOID fireit(VOID);
VOID dodamage(SHORT targn,CHAR targid,SHORT dmg);
VOID castend(VOID);
VOID castenc(VOID);
VOID rape(CHAR kk);
SHORT dospec(CHAR targ, SHORT tnum, CHAR spwr,SHORT ddm,CHAR ap);
USHORT acplyr(SHORT unum);
SHORT calcthac(CHAR tch, SHORT tnum, CHAR atp, SHORT atn);
VOID monstproc(VOID);
VOID restfite(VOID);
VOID setdx(CHAR mvk);
VOID piktarg(SHORT oms);
VOID kiltm(ULONG kexp);
SHORT tsthit(SHORT tx, SHORT ty);
SHORT locmonst(SHORT tx, SHORT ty);
SHORT doequip(VOID);
VOID addnews(CHAR *nstr,SHORT unum);
VOID encnews(CHAR *nstr);
VOID tellthem(CHAR *nstr);
VOID xcdraw(CHAR who, SHORT pn);
VOID nxtplyr(VOID);
VOID rpfenc(VOID);
SHORT tstend(VOID);
VOID encleave(VOID);
VOID dlife(USHORT chp, USHORT maxl);
VOID plotguys(VOID);
VOID clrguy(VOID);
VOID plotguy(VOID);
VOID prtnews(VOID);
VOID movpl(CHAR mvk);
VOID movtarg(CHAR mvk);
VOID attakmons(CHAR mvk);
VOID plothair(VOID);
SHORT ami(VOID);
VOID encounter(VOID);
VOID assignmonst(SHORT flvl);
VOID initcbr(VOID);
VOID setfight(SHORT usrn, SHORT cbrn);
VOID cbcleanup(VOID);
SHORT getcbr(VOID);
VOID mencinit(VOID);
VOID pencinit(SHORT othp);

//elwwdgld.c
SHORT askpower(CHAR styp, SHORT rstate);
SHORT lspells(CHAR stty, CHAR kky, SHORT rstt);
SHORT chklern(CHAR stty);
VOID initwiz(VOID);
VOID wizkick(VOID);
VOID wizproc(VOID);
VOID wizguildinit(VOID);
VOID storelist(STORE *zstor);
VOID clerkick(VOID);
VOID initclers(VOID);
VOID clerguildinit(VOID);
VOID clerproc(VOID);

//elwwdinn.c
VOID inninit(VOID);
VOID delinm(VOID);
VOID innproc(VOID);

//elwwdrip.c
VOID build_icons(VOID);
VOID send_icons(VOID);
VOID misc_rip_detect(VOID);
SHORT check_icons(VOID);
VOID setripcol(SHORT iii);
VOID place_icon(SHORT x,SHORT y, CHAR *twall1);
VOID showicon(CHAR *twall1);
VOID riptext(SHORT ripx,SHORT ripy, SHORT col, CHAR *pstr);
VOID drawripbox(SHORT x1,SHORT y1,SHORT x2,SHORT y2,SHORT border,SHORT color,SHORT color1, SHORT noreset);
VOID wsound(SHORT noise);
VOID rip_clrscr(VOID);

//elwwdrou.c
VOID drawmsg(VOID);
SHORT wdyak(VOID);
VOID vstat(VOID);
VOID eyespy(VOID);
VOID droplist(VOID);
SHORT chkdrop(VOID);
VOID dropupd(CHAR mode, SHORT itm);
CHAR getinput(VOID);
VOID xtavrn(CHAR who);
VOID restat(SHORT un);
VOID statoff(SHORT obn,SHORT sun,SHORT tun);
VOID statup(SHORT obn,SHORT sun,SHORT tun);
VOID deccond(CHAR tgtid,SHORT targn);
SHORT locplayer(SHORT x, SHORT y);
USHORT calcfspdmg(USHORT bdmg,USHORT ldmg,SHORT dmod);
VOID whodat(VOID);
VOID poison(CHAR targid, SHORT targn,CHAR castid,SHORT castn);
VOID paralyze(CHAR targid, SHORT targn,CHAR dtime,CHAR castid, SHORT castn);
VOID drainlvl(CHAR targid, SHORT targn,CHAR castid,SHORT castn);
VOID scry(SHORT rstate, SHORT mstate);
VOID mshield(CHAR targid, SHORT targn,CHAR dtime,CHAR castid,SHORT castn);
SHORT hitbonus(SHORT bval,SHORT castn,CHAR castid);
VOID vision(CHAR castid, CHAR dtime);
VOID drainlife(CHAR targid, SHORT targn,CHAR castid,SHORT castn, SHORT ddm);
VOID heal(CHAR targid,SHORT targn,SHORT hhp,SHORT castn);
VOID youth(CHAR targid, SHORT targn,SHORT ddm,SHORT castn);
VOID agehim(CHAR targid, SHORT targn,SHORT ddm,CHAR castid,SHORT castn);
VOID curepoison(CHAR targid, SHORT targn,SHORT castn);
VOID revive(CHAR targid, SHORT targn);
VOID kill(CHAR targid, SHORT targn,CHAR castid,SHORT castn);
VOID castit(SPELLINF *psp, SHORT rmod,CHAR tgtid, SHORT targn);
VOID castpwr(SPELLINF *psp, SHORT rmod);
VOID castproc(VOID);
VOID castinit(VOID);
VOID talktest(VOID);
SHORT loadrclass(VOID);
SHORT loadplay(VOID);
VOID saveplay(VOID);
VOID gen_CHAR(VOID);
VOID arxy(SHORT x, SHORT y);
SHORT index(CHAR *str1,CHAR ky);
VOID restplay(VOID);
VOID dospecial(SHORT itm);
VOID restcomp(VOID);
VOID useit(VOID);
VOID useinit(VOID);
VOID terror2(VOID);
VOID terror(VOID);
VOID cbroff(SHORT unum);
SHORT ptest(VOID);
VOID xparty(SHORT ldr);
VOID qparty(SHORT usern);
VOID lparty(SHORT usr);
VOID xlounge(CHAR who);
VOID gochat(VOID);
VOID itlist(SHORT pgno);
VOID pagemenu(SHORT rstate, SHORT obcnt,SHORT clrl);
VOID pageproc(VOID);
VOID dropit(VOID);
VOID dodrop(VOID);
VOID inventory(VOID);
CHAR xltkey(VOID);
USHORT loadmonst(VOID);
VOID getanum(SHORT rstt);
VOID delbox(SHORT r, SHORT c, SHORT cnt);
VOID setcycle(VOID);
VOID nocycle(VOID);
VOID td_writeln(CHAR *str1);
VOID striprip(CHAR *pstr);
USHORT length(CHAR *str1);
VOID scopy(CHAR *dest, CHAR *src);
VOID scopyc(CHAR *dest, CHAR *src);
VOID cvtostr(CHAR *dest,CHAR *src);
VOID cvstr(CHAR *str1);
VOID delete(CHAR *pstr1, SHORT dpos, SHORT dlen);
SHORT pos(CHAR ch, CHAR *pstr);
VOID snoozem(VOID);
VOID ststimer(SHORT rstt);
VOID getyno(SHORT rstt);
SHORT cashcheck(ULONG cost);
SHORT loaddb(VOID);
VOID uplevel(VOID);
VOID downlevel(VOID);
VOID dodrunk(VOID);
VOID drawarrows(SHORT r, SHORT c, SHORT ww);
VOID clrarrows(SHORT r, SHORT c,SHORT ww);
VOID ansimenu(SHORT r, SHORT c, SHORT ww, SHORT cnt, CHAR *cmstr, SHORT rstt, SHORT msgno);
VOID initrnd(VOID);
INT getrnd(INT lo, INT hi);
#ifdef __BUILDV10MODULE
INT random(INT hi);
VOID randomize(VOID);
#endif

//elwwdshp.c
VOID tavproc(VOID);
VOID tavinit(VOID);
VOID arenainit(VOID);
VOID arenaproc(VOID);
VOID bankproc(VOID);
VOID bankinit(VOID);
VOID findshop(VOID);
VOID wslist(SHORT wselt);
VOID wepshop(VOID);
VOID wepshopinit(VOID);
VOID wepkick(VOID);
VOID initweps(VOID);

//elwwd3d.c
VOID bonkme(VOID);
VOID spinme(VOID);
VOID moveme(CHAR kkey);
VOID teleport(VOID);
VOID switchme(VOID);
VOID draw(VOID);
VOID drawstats(VOID);
CHAR lookahead(VOID);
VOID checkstuff(USHORT l,USHORT r, USHORT c);
VOID bldoview(VOID);
VOID setwall(VOID);

//elwwdans.c
VOID ansi_color(SHORT blink, SHORT intensity, SHORT forcol, SHORT bakcol);
VOID drawcolor(CHAR *twall);
VOID drawdiag(VOID);
VOID fill3d(VOID);
VOID insert(CHAR *colr, CHAR *cstr, CHAR pos);
VOID fcolor(VOID);
VOID plotface(VOID);
VOID plotxp(VOID);
VOID draw3d(VOID);
VOID rip3d(VOID);

//elwwdfsd.c
VOID prepfsd(SHORT msgno, SHORT amode, SHORT newitem);
VOID fsd_finish(SHORT save);
VOID spfsd(SHORT msgno, SHORT amode, SHORT newitem);
VOID spfsd_finish(SHORT save);
VOID rafsd(SHORT msgno, SHORT amode, SHORT newitem);
VOID rafsd_finish(SHORT save);
VOID clfsd(SHORT msgno, SHORT amode, SHORT newitem);
VOID clfsd_finish(SHORT save);
VOID mofsd(SHORT msgno, SHORT amode, SHORT newitem);
VOID mofsd_finish(SHORT save);

//elwwdmap.c
VOID initwwall(VOID);
VOID initdrop(VOID);
USHORT locstorez(CHAR stype);
SHORT mapcrc(CHAR *bp,USHORT blen);
VOID dsplever(USHORT l);
VOID dspxport(SHORT lvl);
VOID sqzmaps(VOID);
SHORT decompress(SHORT level,CHAR wmap);
VOID savelevers(VOID);
VOID loadlevers(SHORT lcnt);
VOID initxport(SHORT lcnt);
SHORT loadmaps(VOID);



/*
   Global Data Area
*/

extern MONSTINF monstinf;
extern SPELLINF spellinf;
extern RACEINF raceinf;
extern OBJINF objinf;
extern CLASSINF classinf;
// extern CLASSINF2 classinf2;
extern TEMP_PLAYER tplayer;  // Temp player

/*  Global Static Allocations */

extern SGRATE grates[MAXLEVELS+1];

extern XPORTREC xports[MAXLEVELS+1];

extern USHORT wspellcnt,cspellcnt,zclercnt,totmonst,zwepcnt,
       mwaitt,xpcount[MAXLEVELS+1],objcnt[MAXOBJCL],
       racecnt,classcnt,zwizcnt,mench,iwpos,totpriz,totdrop;

extern CHAR xpchars[],kpress[8],
       textletters[],
       direct1[],
       doorchars[],
       doorcolor[],                               /*  Shit brown */
       tpcolor[],                                 /*  pink       */
       *wcolors[],
       *wcolours[],
       wchars[5];

extern CHAR holdmap[TMROW+1][TMCOL+1],
                     holdter[TMROW+1][TMCOL+1],
                   orgholder[TMROW+1][TMCOL+1],
  doorishere,curxy,terrain,somethingthere,somethingthere1,
  facechar,wall[WDWH+1][150],doorme,leverme,doortype,bonk,
  exit_door,tempwall1[252],tempwall[252],ztimerf,
  snooze[256],ingame[256],fredrop[MAXDROP];

extern INT modnum;

extern SHORT cantrun,xyloc[4],
  truerow[TMROW+1][TMCOL+1],truecol[TMROW+1][TMCOL+1],
  fvert,scol,srow,fwid,drcol,face4,face5,
  edtsize,gdx,gdy,
  thactbl[15];

extern LONG dropidx[MAXDROP];

extern CHAR mu1[7][10],
            mu2[7][10],
            mu3[8][2],
            mu4[4][10],
            mu5[13][15],
            mu6[3][10],
            mu7[3][10],
            sp1[4][10],
            sp2[2][7],
            sp3[5][10],
            sp4[14][15],
            cl1[2][5],
            mon1[5][10],
            mon2[9][15];
/*
  File I/O stuff
*/
extern FILE *sysin,*sysout,*dropf,*wwall;
extern HMCVFILE msgblk;
extern struct fndblk utlfblk;
extern DFAFILE *miscitem, *dbspells, *dbclass, *dbrace, *dbmonst,
               *dbplayer, *dbupdate;

/* Global Pointers */

extern SMAP *zmap,*zterrain;
extern VDABLK *zvda,*xlvda,*zldr,*covda;
extern PLYRINF *zplyr;
extern OBJINF *zpobj,*wepbase,*armbase,*rinbase,*potbase,*stobase,
              *amubase,*scrbase,*przbase;
extern struct usracc *uaptr;
//static char *edtptr;
extern SPELLINF *wizspell, *clerspell;
extern STORE *zcler,*zwiz;
extern WSTOR *zwep;
extern MONENT *monbase;
extern CBREC *zcbr;
extern VOID *cobase;
extern CLASSENT *classbase;
extern RACENT *racebase;
extern DPITEM *dpbase;
// Generic status stuff
extern SHORT gamestat;
extern CHAR vernum[10];
extern ULONG reload_cost;

// RIP Stuff, needs to be global...  (Maybe)

extern CHAR ver_rip;
extern CHAR rstr[10];
extern SHORT lbutheight, arip1, arip2;
