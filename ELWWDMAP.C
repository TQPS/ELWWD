/*****************************************************************************
 *   ELWWDMAP.C   V0.62                                 Worlds of Darkness   *
 *   Map/Terrain/Lever Loader Routines                                       *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 01/09/1995         *
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
#include "elwwd.h"
#include "elwwdtyp.h"
#include "elwwdglb.h"

VOID initwwall(VOID)
{
    USHORT ok = TRUE;
    size_t j;
    CHAR wwmsg[73];
    ULONG maxrec = ACTLEVELS * MAPHEIGHT * MAPWIDTH,
        actrec = 0;

    shocst("ELWWD:WWALL Scan", "ELWWD WWALL Scan Begins");
    if ((wwall = fopen("ELWWD\\WWALL.DAT", "rb")) != NULL) {
        while (actrec < maxrec) {
            if (feof(wwall) || ferror(wwall))
                break;
            j = fread(wwmsg, 73, 1, wwall);
            actrec++;
            if (j != 1)
                break;
        }
        fclose(wwall);
        if (actrec < maxrec)
            ok = FALSE;
    } else {
        ok = FALSE;
    }
    if (!ok) {
        shocst("ELWWD:WWALL INIT", "ELWWD WWALL Initializing");
        if ((wwall = fopen("ELWWD\\WWALL.DAT", "wb")) != NULL) {
            actrec = 0;
            wwmsg[0] = 0;
            while (actrec < maxrec && !ferror(wwall)) {
                fwrite(wwmsg, 73, 1, wwall); // j=
                actrec++;
            }
            if (!ferror(wwall))
                ok = TRUE;
            fclose(wwall);
            if (ok)
                wwall = fopen("ELWWD\\WWALL.DAT", "r+b");
            else
                wwall = NULL;
        }
    } else {
        wwall = fopen("ELWWD\\WWALL.DAT", "r+b");
    }
    if (!ok) {
        wwall = NULL;
        shocst("ELWWD:WWALL No-Op", "ELWWD WWALL Not Operational");
    }
    shocst("ELWWD:WWALL Ends", "ELWWD WWALL Init Ended");
}

VOID initdrop(VOID)
{
    SHORT nn = FALSE;
    USHORT i;
    size_t j;
    DPREC dtemp;

    dpbase = (DPITEM*)alczer(sizeof(DPITEM) * MAXDROP);
    totdrop = 0;
    for (i = 0; i < MAXDROP; i++) {
        dpbase[i].dlvl = 0;
        fredrop[i] = TRUE;
    }

    if ((dropf = fopen("ELWWD\\ADICF.DAT", "rb")) != NULL) {
        for (i = 0; i < MAXDROP; i++)
            if (feof(dropf))
                break;
            else {
                dropidx[i] = ftell(dropf);
                j = fread(&dtemp, sizeof(DPREC), 1, dropf);
                if (j != 1) {
                    shocst("ELWWD: I/OE R ADICF", "");
                    break;
                }
                dpbase[i].dx = dtemp.dx;
                dpbase[i].dy = dtemp.dy;
                dpbase[i].dlvl = dtemp.dlvl;
                dpbase[i].idxpos = i;
                if (dtemp.dpobj.objname[0] == 0)
                    dpbase[i].dlvl = 0;
            }
        if (i < MAXDROP) {
            nn = TRUE;
            shocst("ELWWD:ReInit ADICF", "ADICF Is Damaged");
        } else {
            for (i = 0; i < MAXDROP; i++)
                if (dpbase[i].dlvl > ACTLEVELS)
                    dpbase[i].dlvl = 0;
            totdrop = 0;
            for (i = 0; i < MAXDROP; i++)
                if (dpbase[i].dlvl > 0) {
                    dpbase[totdrop] = dpbase[i];
                    totdrop++;
                }
            for (i = 0; i < totdrop; i++)
                fredrop[dpbase[i].idxpos] = FALSE;
            for (i = totdrop; i < MAXDROP; i++)
                dpbase[i].dlvl = 0;
        }
        if (dropf) fclose(dropf);
    } else
        nn = TRUE;
    if (nn) {
        totdrop = 0;
        shocst("ELWWD: Build ADICF", "Creating ADICF File");
        dropf = fopen("ELWWD\\ADICF.DAT", "wb");
        if (dropf != NULL) {
            dtemp.dlvl = 0;
            nn = FALSE;
            for (i = 0; i < MAXDROP; i++) {
                dropidx[i] = ftell(dropf);
                fredrop[i] = TRUE;
                j = fwrite(&dtemp, sizeof(DPREC), 1, dropf);
                if (j != 1) {
                    shocst("ELWWD: I/OE W ADICF", "");
                    nn = TRUE;
                    break;
                }
            }
            fclose(dropf);
            if (nn)
                dropf = NULL;
            else
                dropf = fopen("ELWWD\\ADICF.DAT", "r+b");
        } else {
            shocst("ELWWD: Build ADICF Failed", "Error Creating ADICF File");
        }
        fclose(dropf);
    } else {
        dropf = fopen("ELWWD\\ADICF.DAT", "r+b");
    }
}

USHORT locstorez(CHAR stype)
{
    USHORT i, j, k, scnt = 0;

    for (i = 1; i <= ACTLEVELS; i++)
        for (j = 1; j <= MAPHEIGHT; j++)
            for (k = 1; k <= MAPWIDTH; k++)
                if (zmap->lvl[i].map[j][k] == stype)
                    scnt++;

    return(scnt);
}

SHORT calcrc(SHORT oldcrc, CHAR ch)
{
    SHORT j;

    oldcrc ^= (ch << 8);
    for (j = 0; j < 8; j++) {
        if (oldcrc & 0x8000) {
            oldcrc = (oldcrc << 1) ^ 0x1021;
        } else {
            oldcrc = oldcrc << 1;
        }
    }

    return (oldcrc);
}

SHORT mapcrc(CHAR* bp, USHORT blen)
{
    SHORT crc = 0, i;

    for (i = 0; i < blen; i++) {
        crc = calcrc(crc, bp[i]);
    }

    return(crc);
}

#ifdef ZARKALF
VOID dsplever(USHORT l)
{
    USHORT i, j, k;

    for (i = 0; i < MAXGRATES; i++) {
        if ((k = grates[l].levercnt[i]) != 0) {
            prf("Lever states for lever %c\n", i + 'a');
            for (j = 0; j < k; j++) {
                prf("%u,%u,%c\n", grates[l].leverrow[i][j],
                    grates[l].levercol[i][j],
                    grates[l].leverstate[i][j]);
            }
            outprf(usrnum);
        }
    }
}

VOID sqzmaps(VOID)
{
    SHORT done;
    USHORT srclen, bptr, rrow;
    CHAR fch, chcnt, tchar, srcpos, stopme,
        * bufr;
    CHAR ifn[60], ofn[60], srcline[210];
    SHORT crc;

    prf("map squeezing starts...\n");
    outprf(usrnum);
    done = fnd1st(&utlfblk, "ELWWD\\MAP\\*.MAP", 0); // was fnd1st
    bufr = (CHAR*)alcmem(8000);
    while (done) {
        strcpy(ifn, "ELWWD\\MAP\\");
        strcpy(ofn, "ELWWD\\");
        strcat(ifn, utlfblk.ff_name);
        strcat(ofn, utlfblk.ff_name);
        prf("squeezing %s to %s \n", ifn, ofn);
        outprf(usrnum);
        if ((sysin = fopen(ifn, FOPRA)) != NULL
            && (sysout = fopen(ofn, FOPWB)) != NULL) {
            fgets(srcline, 200, sysin);
            srcpos = 1;
            bptr = 0;
            fch = srcline[0];
            chcnt = 1;
            srclen = 1;
            rrow = 1;
            stopme = 0;
            while (!stopme) {
                tchar = srcline[srcpos];
                srclen++;
                if (fch == tchar) {
                    if (chcnt < 255) chcnt++;
                    else {
                        bufr[bptr] = fch;
                        bptr++;
                        bufr[bptr] = chcnt;
                        bptr++;
                        chcnt = 1;
                    }
                } else {
                    bufr[bptr] = fch;
                    bptr++;
                    bufr[bptr] = chcnt;
                    bptr++;
                    chcnt = 1;
                    fch = tchar;
                }
                srcpos++;
                if (srcpos == MAPWIDTH) {
                    if (feof(sysin)) stopme = 1;
                    else {
                        fgets(srcline, 200, sysin);
                        rrow++;
                        srcpos = 0;
                    }
                }
            }
            bufr[bptr] = fch;
            bptr++;
            bufr[bptr] = chcnt;
            bptr++;

            crc = mapcrc(bufr, bptr);

            fwrite(&bptr, sizeof(USHORT), 1, sysout);
            fwrite(&crc, sizeof(SHORT), 1, sysout);
            fwrite(bufr, 1, bptr, sysout);
            fclose(sysin);
            fclose(sysout);
        }
        done = fndnxt(&utlfblk);
    }
    free(bufr);
    prf("...end squeezing\n");
    outprf(usrnum);
}
#endif

SHORT decompress(SHORT level, CHAR wmap)
{
    CHAR mrow, mcol, fch, chcnt, stopme, * bufr;
    CHAR fn[40], lstr[8];
    USHORT msize, rsize, lvptr, ccntr;
    SHORT oldcrc, crc, rc = 1;//=0,rc=1;

    if (wmap == 't') strcpy(fn, "ELWWD\\T");
    else strcpy(fn, "ELWWD\\M");
    itoa(level, lstr, 10);
    strcat(fn, lstr);
    strcat(fn, ".MAP");
    // prf("processing %s\n",fn);
    // outprf(usrnum);
    if ((sysin = fopen(fn, FOPRB)) != NULL) {
        fread(&msize, sizeof(USHORT), 1, sysin);
        fread(&oldcrc, sizeof(SHORT), 1, sysin);
        if (!msize || msize > 10000) {
            shocst("ELWWD map size error", "");
        } else {
            bufr = (CHAR*)alcmem(10000);
            rsize = (USHORT)fread(bufr, 1, msize, sysin);
            crc = mapcrc(bufr, msize);
            if (crc != oldcrc)
                shocst("ELWWD Bad map crc", "");
            if (rsize == msize) {
                mrow = 1;
                mcol = 1;
                fch = bufr[0];
                chcnt = bufr[1];
                lvptr = 1;
                stopme = 0;
                ccntr = 2;
                while (stopme == 0) {
                    if (wmap == 't')
                        zterrain->lvl[level].map[mrow][mcol] = fch;
                    else
                        zmap->lvl[level].map[mrow][mcol] = fch;
                    //   themap[level].map[mrow][mcol]=fch;
                    chcnt--;
                    if (chcnt == 0) {
                        lvptr++;
                        fch = bufr[lvptr];
                        lvptr++;
                        chcnt = bufr[lvptr];
                        ccntr += 2;
                    }
                    if (ccntr == msize) {
                        stopme = 1;
                        rc = 0;
                    }
                    if (!stopme && mcol == MAPWIDTH) {
                        mcol = 1;
                        if (mrow == MAPHEIGHT) {
                            if (!stopme) {
                                if (msize - ccntr != 2)
                                    shocst("ELWWD map overrun", "mapvr cc=%u,ms=%u", ccntr, msize);
                                else rc = 0;
                            }
                            break;
                        } else mrow++;
                    } else mcol++;
                }
            } else {
                shocst("ELWWD map size err", "rrsize %u\n", rsize);
            }
            free(bufr);
        }
        fclose(sysin);
    } else {
        shocst("ELWWD map opn error", "Fopen failed for %s\n", fn);
    }

    return(rc);
}

VOID savelevers(VOID)
{
    size_t wsize;

    if ((sysout = fopen("ELWWD\\LLV.DAT", FOPWB)) != NULL) {
        wsize = fwrite(grates, sizeof(grates), 1, sysout);
        if (wsize != 1)
            shocst("ELWWD levrf werr", "levrf wsiz=%zu\n", wsize);
        fclose(sysout);
    }
}

VOID loadlevers(SHORT lcnt)
{
    USHORT cold = 0, i, j, k;
    size_t rtsize;
    CHAR q, p;

    if ((sysin = fopen("ELWWD\\LLV.DAT", FOPRB)) != NULL) {
        rtsize = fread(grates, sizeof(grates), 1, sysin);
        if (rtsize != 1) {
            shocst("ELWWD leverf truncd", "levrf read=%zu", rtsize);
            cold = 1;
        }
        fclose(sysin);
    } else cold = 1;

    if (cold) { /* supply defaults */
        for (i = 1; i <= lcnt; i++) {
            for (j = 0; j < MAXGRATES; j++) {
                for (k = 0; k < MAXDUPLEVER; k++) {
                    grates[i].leverstate[j][k] = 'u';
                    grates[i].levercnt[j] = 0;
                }
            }
        }
        for (i = 1; i <= lcnt; i++) {
            for (j = 1; j <= MAPHEIGHT; j++) {
                for (k = 1; k <= MAPWIDTH; k++) {
                    q = zmap->lvl[i].map[j][k];
                    if (q >= 'n' && q <= 'z') {
                        q -= 'n';
                        if (grates[i].levercnt[q] == MAXDUPLEVER) {
                            shocst("ELWWD Too many levers", "");
                        } else {
                            p = grates[i].levercnt[q];
                            grates[i].levercnt[q]++;
                            grates[i].levercol[q][p] = (CHAR)k;
                            grates[i].leverrow[q][p] = (CHAR)j;
                        }
                    }
                }
            }
        }
        savelevers();
    }
}


VOID initxport(SHORT lcnt)
{
    USHORT i, j, l;

    for (l = 1; l <= lcnt; l++) {
        xpcount[l] = 0;
        for (i = 1; i <= MAPHEIGHT; i++) {
            for (j = 1; j <= MAPWIDTH; j++) {
                if (index(xpchars, zmap->lvl[l].map[i][j]) != NOTFOUND) {
                    if (xpcount[l] == MAXTP) {
                        shocst("ELWWD xport overrun", "");
                        i = MAPHEIGHT + 1;
                        break;
                    } else {
                        xports[l].xportx[xpcount[l]] = (CHAR)j;
                        xports[l].xporty[xpcount[l]] = (CHAR)i;
                        xports[l].xportc[xpcount[l]] = zmap->lvl[l].map[i][j];
                        xpcount[l]++;
                    }
                }
            }
        }
    }
}

VOID dspxport(SHORT lvl)
{
    USHORT i;

    prfmsg(CLRSCR);
    outprf(usrnum);
    if (xpcount[lvl] > 0) {
        prf("level %d has %u xports", lvl, xpcount[lvl]);
        outprf(usrnum);
        for (i = 0; i < xpcount[lvl]; i++) {
            prf("%c at row=%u,col=%u\n",
                xports[lvl].xportc[i],
                xports[lvl].xporty[i],
                xports[lvl].xportx[i]);
            outprf(usrnum);
        }
    } else {
        prf("Level has no xporters");
        outprf(usrnum);
    }
}

static VOID fixmap(VOID)
{
    USHORT i, j, k;

    for (i = 1; i <= ACTLEVELS; i++)
        for (j = 1; j <= MAPHEIGHT; j++)
            for (k = 1; k <= MAPWIDTH; k++)
                switch (zmap->lvl[i].map[j][k]) {
                    case 'B':
                    case 'E':
                    case 'F':
                    case 'I':
                    case 'K':
                    case 'P':
                        zmap->lvl[i].map[j][k] = '#';
                        break;
                }
}

SHORT loadmaps(VOID)
{
    SHORT rc = 0, j;

    for (j = 1; j <= ACTLEVELS; j++) {
        rc |= decompress(j, 'm');
        rc |= decompress(j, 't');
        if (rc) {
            shocst("ELWWD loadmap terminated", "");
            break;
        }
    }
    if (!rc) {
        fixmap();
        initxport(ACTLEVELS);
        loadlevers(ACTLEVELS);
    }

    return(rc);
}
