/*****************************************************************************
 *   ELWWDFSD.H  V0.62                                  Worlds of Darkness   *
 *   FSD Defines                                                             *
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


//  The FSD Header file.  So defines are not global!!

                                        /* FSD Object Defines */
#define OBNAMEFLD 0
#define OBWEIGHT  1
#define OBSPOT    2
#define OBTYPE    3
#define OBCLASS   4
#define OBSTR     5
#define OBDEX     6
#define OBINT     7
#define OBWIS     8
#define OBCON     9
#define OBCHR    10
#define OBLCK    11
#define OBAC     12
#define OBMD     13
#define OBRANGE  14
#define OBRTYPE  15
#define OBSP     16
#define OBWHAT   17
#define OBCSP    18
#define OBTSP    19
#define OBSPHD   20
#define OBWHO    21
#define OBCOST   22

                                        // FSD Spell defines

#define SPNAME    0
#define SPLEVEL   1
#define SPELEMENT 2
#define SPCLASS   3
#define SPMP      4
#define SPRANGE   5
#define SPXRANGE  6
#define SPTARGET  7
#define SPTYPE    8
#define SPDURAT   9
#define SPMHD     10
#define SPXMHD    11
#define SPTEXT    12

                                        // FSD Class Defines

#define CLNAME      0
#define CLHP        1
#define CLMAGE1     2
#define CLPRIEST1   3
#define CLEXP1      4
#define CLMAGE2     5
#define CLPRIEST2   6
#define CLEXP2      7
#define CLMP        8
#define CLMAGE3     9
#define CLPRIEST3   10
#define CLEXP3      11
#define CLMAGE4     12
#define CLPRIEST4   13
#define CLEXP4      14
#define CLMAGE5     15
#define CLPRIEST5   16
#define CLEXP5      17
#define CLOBJ1      18
#define CLMAGE6     19
#define CLPRIEST6   20
#define CLEXP6      21
#define CLOBJ2      22
#define CLMAGE7     23
#define CLPRIEST7   24
#define CLEXP7      25
#define CLOBJ3      26
#define CLMAGE8     27
#define CLPRIEST8   28
#define CLEXP8      29
#define CLOBJ4      30
#define CLMAGE9     31
#define CLPRIEST9   32
#define CLEXP9      33
#define CLOBJ5      34
#define CLMAGE10    35
#define CLPRIEST10  36
#define CLEXP10     37
#define CLOBJ6      38
#define CLMAGE11    39
#define CLPRIEST11  40
#define CLEXP11     41
#define CLOBJ7      42
#define CLMAGE12    43
#define CLPRIEST12  44
#define CLEXP12     45
#define CLOBJ8      46
#define CLMAGE13    47
#define CLPRIEST13  48
#define CLEXP13     49
#define CLMAGE14    50
#define CLPRIEST14  51
#define CLEXP14     52
#define CLMAGE15    53
#define CLPRIEST15  54
#define CLEXP15     55

                                         // FSD Race Defines

#define RANAME    0
#define RACAST    1
#define RAMR      2
#define RASTR     3
#define RAMSTR    4
#define RADEX     5
#define RAMDEX    6
#define RAEARTH   7
#define RAINT1    8
#define RAMINT1   9
#define RAAIR    10
#define RAWIS    11
#define RAMWIS   12
#define RAWATER  13
#define RACON    14
#define RAMCON   15
#define RAFIRE   16
#define RACHR    17
#define RAMCHR   18
#define RALCK    19
#define RAMLCK   20
#define RAHP     21
                                        // FSD Monster Defines

#define MONAME     0
#define MOLVL      1
#define MOARMOR    2
#define MOMOVES    3
#define MOHP       4
#define MOATT      5
#define MODMG      6
#define MOSP       7
#define MOAPPEAR   8
#define MOAMSG     9
#define MOMR       10
#define MOEARTH    11
#define MOAIR      12
#define MOWATER    13
#define MOFIRE     14
#define MORTYPE    15
#define MORMSG     16
#define MORDMG     17
#define MORRANGE   18
#define MORSP      19
#define MORCH      20
#define MOWEP      21
#define MOARM      22
#define MORIN      23
#define MOPOT      24
#define MOSTO      25
#define MOAMU      26
#define MOSCR      27
#define MOGOLD     28
#define MOEXP      29


