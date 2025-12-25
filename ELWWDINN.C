/*****************************************************************************
 *   ELWWDINN.C   V0.62                                 Worlds of Darkness   *
 *   Inn Routines                                                            *
 *                                                                           *
 *   Description:    Worlds of Darkness is a 3D role-playing game.           *
 *                   During the course of the game many races, classes,      *
 *                   and items can be found through out the game-world       *
 *                                                                           *
 *                   GraphicWares & Wizard Software v0.61 09/25/1994         *
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

VOID inninit(VOID)
{
    prfmsg(INN);
    outprf(usrnum);
    zvda->redraw = FALSE;
    bonk = FALSE;
    zvda->clrbonk = FALSE;
    zvda->mstate = 0;
    // row/col/width/#items/cmchars/rstate
    ansimenu(1, 48, 27, 4, "BQRL", 100, INNMENU1);
}

VOID delinm(VOID)
{
    prfmsg(WBLLN);
    outprf(usrnum);
    prfmsg(ABLLN);
    outprf(usrnum);
}

VOID innproc(VOID)
{

    switch (zvda->mstate) {
        case 0:
            switch (zvda->mnukey) {
                case 1:
                    delinm();
                    arxy(1, 15);        // bed
                    prfmsg(BEDC1);
                    zvda->lastcost = zplyr->level * 50;
                    prf("%u pp\n", zvda->lastcost);
                    prfmsg(BEDC2);
                    outprf(usrnum);
                    zvda->mstate = 1;
                    getyno(100);
                    break;
                case 2:                    // quest
                case 3:                    // rumours
                case 4:
                    restplay();        // leave
            }
            break;
        case 1:
            if (zvda->mnukey == 'Y') {
                delinm();
                if (cashcheck(zvda->lastcost)) {
                    prfmsg(ZBED);
                    outprf(usrnum);
                    zvda->stimer = 10;
                    zvda->mstate = 2;
                    ststimer(100);
                } else {
                    prfmsg(INNDBT);
                    outprf(usrnum);
                    zvda->mstate = 0;
                    ansimenu(1, 48, 27, 4, "BQRL", 100, INNMENU1);
                }
            } else {
                delinm();
                prfmsg(LCHUMP);
                outprf(usrnum);
                zvda->mstate = 0;
                ansimenu(1, 48, 27, 4, "BQRL", 100, INNMENU1);
            }
            break;
        case 2: delinm();
            prfmsg(WAKEUP);
            outprf(usrnum);
            zplyr->currhp = zplyr->maxhp;
            zplyr->currmp = zplyr->maxmp;
            zvda->nstat = TRUE;
            zvda->mstate = 0;
            ansimenu(1, 48, 27, 4, "BQRL", 100, INNMENU1);
            break;
        default:
            restplay();
            prf("unknown inn state");
            outprf(usrnum);
    }
}

