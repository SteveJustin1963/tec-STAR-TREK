[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] z!

[46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46] m!

[0 0 0 0 0 0 0 0 0] k!

:A
3000 e!
10 f!
0 g!
30 s!
3 d!
4 q!
3 r!
1 i!
1 j!
3 z 0 ?!
3 z 7 ?!
3 z 14 ?!
79 m 0 ?!
/N
`================================` /N
`     STAR TREK MISSION GAME    ` /N
`================================` /N /N
`Mission: Destroy ` d . ` Klingons` /N
`Time Limit: ` s . ` Stardates` /N
`Starting Energy: ` e . /N /N
`Good luck, Captain!` /N
`================================` /N /N
;

:C
/N
`---- STATUS REPORT ----` /N
`Energy: ` e . /N
`Torpedoes: ` f . /N
`Shields: ` g . /N
`Stardates: ` s . /N
`Klingons: ` d . /N
`-----------------------` /N /N
;

:B
/N
`---- SECTOR MAP ----` /N
`  1 2 3 4 5 6 7 8` /N
8 (
`  `
8 (
m /j 8 * /i + ? /C 32 /C
)
/N
)
`--------------------` /N /N
;

:D
`Direction (1=N 3=E 5=S 7=W): ` /K 48 - t!
46 m i 1 - 8 * j + 1 - ?!
t 1 = ( j 1 - j! )
t 3 = ( i 1 + i! )
t 5 = ( j 1 + j! )
t 7 = ( i 1 - i! )
i 1 < ( 1 i! )
i 8 > ( 8 i! )
j 1 < ( 1 j! )
j 8 > ( 8 j! )
79 m i 1 - 8 * j + 1 - ?!
e 10 - e!
s 1 - s!
/N
`Moved to sector ` i . `,` j . /N
;

:M
/N
`================================` /N
`          MAIN MENU             ` /N
`================================` /N
`1 - Navigate (Move Ship)` /N
`2 - View Status Report` /N
`3 - View Sector Map` /N
`4 - Quit Game` /N
`================================` /N
`Command: ` /K 48 - c!
/N
;

:G
C B
/U (
s 0 > d 0 > & /W
M
c 1 = ( D )
c 2 = ( C )
c 3 = ( B )
c 4 = ( `Exiting mission...` /N /F s! )
)
s 0 < s 0 = | (
/N
`================================` /N
`       MISSION FAILED!          ` /N
`================================` /N
`Out of time!` /N
d . ` Klingons remain` /N
`================================` /N /N
)
d 0 < d 0 = | (
/N
`================================` /N
`      MISSION COMPLETE!         ` /N
`================================` /N
`All Klingons destroyed!` /N
`Federation saved!` /N
`================================` /N /N
)
e 0 < e 0 = | (
/N
`================================` /N
`    ENTERPRISE DESTROYED!       ` /N
`================================` /N
`Ship lost with all hands` /N
`================================` /N /N
)
;

A G


