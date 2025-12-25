/*****************************************************************************
 *   ELWWDR3D.H   V0.62                                 Worlds of Darkness   *
 *   Icon Files That Can Be Displayed                                        *
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

// This is a list of the icon files that cam be displayed

CHAR walls[248][13]={    // Terrain walls and stuff.
{"112.ICN"},     {"1326.ICN"},    {"2736.ICN"},    {"BACELBT3.ICN"},
{"BACELRD3.ICN"},{"BACELWS3.ICN"},{"BACERBT3.ICN"},{"BACERRD3.ICN"},
{"BACERWS3.ICN"},{"BACESBT1.ICN"},{"BACESBT2.ICN"},{"BACESBT3.ICN"},
{"BACESBW1.ICN"},{"BACESCP1.ICN"},{"BACESCP2.ICN"},{"BACESCP3.ICN"},
{"BACESDR1.ICN"},{"BACESDR3.ICN"},{"BACESLBT.ICN"},{"BACESOP1.ICN"},
{"BACESOP2.ICN"},{"BACESOP3.ICN"},{"BACESP1.ICN"}, {"BACESP2.ICN"},
{"BACESP3.ICN"}, {"BACESRD2.ICN"},{"BACESSD1.ICN"},{"BACESSD2.ICN"},
{"BACESSD3.ICN"},{"BACESWS2.ICN"},{"BACESWS3.ICN"},{"BALFLBT1.ICN"},
{"BALFLBT2.ICN"},{"BALFLBT3.ICN"},{"BALFLRD1.ICN"},{"BALFLRD2.ICN"},
{"BALFLRD3.ICN"},{"BALFLWS1.ICN"},{"BALFLWS2.ICN"},{"BALFLWS3.ICN"},
{"BALFRBT1.ICN"},{"BALFRBT2.ICN"},{"BALFRBT3.ICN"},{"BALFRRD1.ICN"},
{"BALFRRD2.ICN"},{"BALFRRD3.ICN"},{"BALFRWS1.ICN"},{"BALFRWS2.ICN"},
{"BALFRWS3.ICN"},{"BALLLBT2.ICN"},{"BALLLBT3.ICN"},{"BALLLRD2.ICN"},
{"BALLLRD3.ICN"},{"BALLLWS2.ICN"},{"BALLLWS3.ICN"},{"BALLRBT2.ICN"},
{"BALLRBT3.ICN"},{"BALLRRD2.ICN"},{"BALLRRD3.ICN"},{"BALLRWS2.ICN"},
{"BALLRWS3.ICN"},{"BANK.ICN"},    {"BARENA.ICN"},  {"BARMOR.ICN"},
{"BBANK.ICN"},   {"BCLERIC.ICN"}, {"BINN.ICN"},    {"BPALACE.ICN"},
{"BTAVERN.ICN"}, {"BUT1V.ICN"},   {"BUT2V.ICN"},   {"BUTTON.ICN"},
{"BWIZARD.ICN"}, {"BWOOD.ICN"},   {"CASINO.ICN"},  {"CLERIC.ICN"},
{"COMPE.ICN"},   {"COMPN.ICN"},   {"COMPS.ICN"},   {"COMPW.ICN"},
{"DSCARD0C.ICN"},{"DSCARD0D.ICN"},{"DSCARD0H.ICN"},{"DSCARD0S.ICN"},
{"DSCARD2C.ICN"},{"DSCARD2D.ICN"},{"DSCARD2H.ICN"},{"DSCARD2S.ICN"},
{"DSCARD3C.ICN"},{"DSCARD3D.ICN"},{"DSCARD3H.ICN"},{"DSCARD3S.ICN"},
{"DSCARD4C.ICN"},{"DSCARD4D.ICN"},{"DSCARD4H.ICN"},{"DSCARD4S.ICN"},
{"DSCARD5C.ICN"},{"DSCARD5D.ICN"},{"DSCARD5H.ICN"},{"DSCARD5S.ICN"},
{"DSCARD6C.ICN"},{"DSCARD6D.ICN"},{"DSCARD6H.ICN"},{"DSCARD6S.ICN"},
{"DSCARD7C.ICN"},{"DSCARD7D.ICN"},{"DSCARD7H.ICN"},{"DSCARD7S.ICN"},
{"DSCARD8C.ICN"},{"DSCARD8D.ICN"},{"DSCARD8H.ICN"},{"DSCARD8S.ICN"},
{"DSCARD9C.ICN"},{"DSCARD9D.ICN"},{"DSCARD9H.ICN"},{"DSCARD9S.ICN"},
{"DSCARDAC.ICN"},{"DSCARDAD.ICN"},{"DSCARDAH.ICN"},{"DSCARDAS.ICN"},
{"DSCARDBK.ICN"},{"DSCARDJC.ICN"},{"DSCARDJD.ICN"},{"DSCARDJH.ICN"},
{"DSCARDJS.ICN"},{"DSCARDKC.ICN"},{"DSCARDKD.ICN"},{"DSCARDKH.ICN"},
{"DSCARDKS.ICN"},{"DSCARDOL.ICN"},{"DSCARDQC.ICN"},{"DSCARDQD.ICN"},
{"DSCARDQH.ICN"},{"DSCARDQS.ICN"},{"EVEN.ICN"},    {"FACELBT3.ICN"},
{"FACELDR3.ICN"},{"FACELWS3.ICN"},{"FACERBT3.ICN"},{"FACERDR3.ICN"},
{"FACERWS3.ICN"},{"FACESBT1.ICN"},{"FACESBT2.ICN"},{"FACESBT3.ICN"},
{"FACESDP1.ICN"},{"FACESDP2.ICN"},{"FACESDP3.ICN"},{"FACESDR1.ICN"},
{"FACESDR2.ICN"},{"FACESDR3.ICN"},{"FACESDS1.ICN"},{"FACESDS2.ICN"},
{"FACESDS3.ICN"},{"FACESOP1.ICN"},{"FACESOP2.ICN"},{"FACESOP3.ICN"},
{"FACESWS1.ICN"},{"FACESWS2.ICN"},{"FACESWS3.ICN"},{"FIGHTER2.ICN"},
{"FULL.ICN"},    {"GOBLIN2.ICN"}, {"HALFLBT2.ICN"},{"HALFLBT3.ICN"},
{"HALFLDP2.ICN"},{"HALFLDR2.ICN"},{"HALFLDR3.ICN"},{"HALFLOP2.ICN"},
{"HALFLWS2.ICN"},{"HALFLWS3.ICN"},{"HALFRBT2.ICN"},{"HALFRBT3.ICN"},
{"HALFRDP2.ICN"},{"HALFRDR2.ICN"},{"HALFRDR3.ICN"},{"HALFROP2.ICN"},
{"HALFRWS2.ICN"},{"HALFRWS3.ICN"},{"HALL.ICN"},    {"HALLBTL1.ICN"},
{"HALLBTL2.ICN"},{"HALLBTL3.ICN"},{"HALLBTR1.ICN"},{"HALLBTR2.ICN"},
{"HALLBTR3.ICN"},{"HALLRDL1.ICN"},{"HALLRDL2.ICN"},{"HALLRDL3.ICN"},
{"HALLRDR1.ICN"},{"HALLRDR2.ICN"},{"HALLRDR3.ICN"},{"HALLWSL1.ICN"},
{"HALLWSL2.ICN"},{"HALLWSL3.ICN"},{"HALLWSR1.ICN"},{"HALLWSR2.ICN"},
{"HALLWSR3.ICN"},{"INN.ICN"},     {"JAIL.ICN"},    {"JAIL1.ICN"},
{"NOICON.ICN"},  {"ODD.ICN"},     {"PLAY1.ICN"},   {"PLAY2.ICN"},
{"PLAY3.ICN"},   {"PORTAL1.ICN"}, {"PORTAL2.ICN"}, {"PORTAL3.ICN"},
{"SARENA.ICN"},  {"SARMOR.ICN"},  {"SBANK.ICN"},   {"SBUTL1.ICN"},
{"SBUTL2.ICN"},  {"SCLERIC.ICN"}, {"SDOWN.ICN"},   {"SINN.ICN"},
{"SLOT0.ICN"},   {"SLOT1.ICN"},   {"SLOT2.ICN"},   {"SLOT3.ICN"},
{"SLOT4.ICN"},   {"SLOT5.ICN"},   {"SLOT6.ICN"},   {"SPALACE.ICN"},
{"STAIR1.ICN"},  {"STAIR2.ICN"},  {"STAIR3.ICN"},  {"STAVERN.ICN"},
{"SUP.ICN"},     {"SWARRIOR.ICN"},{"SWIZARD.ICN"}, {"TAVERN.ICN"},
{"WIZARD.ICN"},  {"WWARMOR.ICN"}, {"WWCAMP2.ICN"}, {"WWCLERI2.ICN"},
{"WWCLERIC.ICN"},{"WWDEMON.ICN"}, {"WWDEMON2.ICN"},{"WWDEMON3.ICN"},
{"WWFLGSTN.ICN"},{"WWGUILD.ICN"}, {"WWROOM.ICN"},  {"WWSKULL.ICN"},
{"WWSPELL.ICN"}, {"WWSTAIR.ICN"}, {"WWTEST.ICN"},  {"WWWEAPON.ICN"}
};


