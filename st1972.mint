// ============================================
// STAR TREK - CORRECTED for MINT-Octave
// ============================================

// Function A - Initialize Game (FIXED)
:A
3000 e!
10 f!
0 g!
30 s!
0 d!
[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] z!
8 (
8 (
/j 8 * /i + a!
a 7 % 0 = (
3 z a ?!
d 3 + d!
)
)
)
4 q!
3 r!
1 i!
1 j!
[46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46] m!
[0 0 0 0 0 0 0 0 0] k!
`STAR TREK` /N
`=========` /N /N
`Destroy ` d . ` Klingons in ` s . ` stardates` /N
`Good luck, Captain!` /N /N
;

// Function B - Short Range Scan
:B
`---- Short Range Scan ----` /N
`  1 2 3 4 5 6 7 8` /N
1 l!
8 (
l . 32 /C
1 o!
8 (
m l 1 - 8 * o + 1 - ? /C 32 /C
o 1 + o!
)
/N
l 1 + l!
)
`--------------------------` /N
;

// Function C - Status Report
:C
`Status:` /N
`Quadrant ` q . `,` r . `  Sector ` i . `,` j . /N
`Energy: ` e . `  Torpedoes: ` f . `  Shields: ` g . /N
`Stardates: ` s . `  Klingons: ` d . /N /N
;

// Function D - Navigate
:D
e 10 > (
`Course (1-8): ` /K 48 - t!
t 0 > t 9 < & (
`Warp (1-3): ` /K 48 - w!
w 0 > w 4 < & (
46 m i 1 - 8 * j + 1 - ?!
t 1 = ( j w - j! )
t 2 = ( i w + i! j w - j! )
t 3 = ( i w + i! )
t 4 = ( i w + i! j w + j! )
t 5 = ( j w + j! )
t 6 = ( i w - i! j w + j! )
t 7 = ( i w - i! )
t 8 = ( i w - i! j w - j! )
i 1 < ( 1 i! )
i 8 > ( 8 i! )
j 1 < ( 1 j! )
j 8 > ( 8 j! )
e w 10 * - e!
s 1 - s!
79 m i 1 - 8 * j + 1 - ?!
`Moved to ` i . `,` j . /N
J
) /E (
`Invalid warp!` /N
)
) /E (
`Invalid course!` /N
)
) /E (
`Low energy!` /N
)
;

// Function E - Fire Phasers
:E
e 100 > (
`Phaser energy (100-500): ` /K 48 - a!
a 100 > a 500 < & (
e a - e!
I (
`Klingons present!` /N
1 l!
3 (
k l 1 - 3 * 3 + ? 0 > (
k l 1 - 3 * 3 + ? a 3 / - b!
b 0 > (
b k l 1 - 3 * 3 + ?!
`Hit Klingon at ` k l 1 - 3 * 1 + ? . `,` k l 1 - 3 * 2 + ? . /N
) /E (
`Klingon destroyed!` /N
d 1 - d!
0 k l 1 - 3 * 3 + ?!
46 m k l 1 - 3 * 1 + ? 1 - 8 * k l 1 - 3 * 2 + ? + 1 - ?!
)
)
l 1 + l!
)
J
) /E (
`No Klingons here!` /N
)
) /E (
`Invalid energy!` /N
)
) /E (
`Low energy!` /N
)
;

// Function F - Fire Photon Torpedo
:F
f 0 > (
`Course (1-8): ` /K 48 - t!
t 0 > t 9 < & (
f 1 - f!
i u!
j v!
`Torpedo fired!` /N
8 (
t 1 = ( v 1 - v! )
t 2 = ( u 1 + u! v 1 - v! )
t 3 = ( u 1 + u! )
t 4 = ( u 1 + u! v 1 + v! )
t 5 = ( v 1 + v! )
t 6 = ( u 1 - u! v 1 + v! )
t 7 = ( u 1 - u! )
t 8 = ( u 1 - u! v 1 - v! )
u 1 < u 8 > | v 1 < | v 8 > | (
`Missed!` /N
8 /i!
) /E (
m u 1 - 8 * v + 1 - ? 43 = (
`Klingon destroyed at ` u . `,` v . `!` /N
d 1 - d!
1 l!
3 (
k l 1 - 3 * 1 + ? u = k l 1 - 3 * 2 + ? v = & (
0 k l 1 - 3 * 3 + ?!
)
l 1 + l!
)
46 m u 1 - 8 * v + 1 - ?!
8 /i!
)
)
)
J
)
) /E (
`No torpedoes!` /N
)
;

// Function G - Main Game Loop
:G
Q
/U (
s 0 > d 0 > & /W
C
B
`Command: 1=Nav 2=Phaser 3=Torpedo 4=Shield 5=Help 6=Quit` /N
`> ` /K 48 - c!
c 1 = ( D )
c 2 = ( E )
c 3 = ( F )
c 4 = ( S )
c 5 = ( H )
c 6 = ( `Quitting...` /N /F s! )
/N
N
)
V
;

// Function H - Help
:H
`Commands:` /N
`1 = Navigate (move ship)` /N
`2 = Fire Phasers` /N
`3 = Fire Photon Torpedo` /N
`4 = Shield Control` /N
`5 = Help` /N
`6 = Quit` /N /N
;

// Function I - Check for Klingons (returns true/false)
:I
/F a!
1 l!
3 (
k l 1 - 3 * 3 + ? 0 > (
/T a!
)
l 1 + l!
)
a
;

// Function J - Klingon Attack
:J
I (
`*** KLINGON ATTACKS! ***` /N
1 l!
3 (
k l 1 - 3 * 3 + ? 0 > (
k l 1 - 3 * 3 + ? 10 / h!
g h > (
g h - g!
`Shields absorb ` h . ` damage` /N
) /E (
e g h - + e!
0 g!
`Hull damage! Energy: ` e . /N
)
)
l 1 + l!
)
)
;

// Function K - Unused
:K
;

// Function L - Long Range Scan
:L
`Long Range Scan:` /N
q 1 - 0 > ( z q 2 - 8 * r + 1 - ? . 32 /C )
z q 1 - 8 * r + 1 - ? . 32 /C
q 1 + 8 < ( z q 8 * r + 1 - ? . )
/N
;

// Function M - Place Random Empty Location
:M
/U (
8 /i 8 / 1 + * u!
8 /i 8 / 1 + * v!
m u 1 - 8 * v + 1 - ? 46 = /W
)
u v
;

// Function N - Check Win/Lose
:N
d 0 < d 0 = | (
`*** VICTORY! ***` /N
`All Klingons destroyed!` /N
/F s!
)
s 0 < s 0 = | (
`*** DEFEAT ***` /N
`Out of time! ` d . ` Klingons remain` /N
/F s!
)
e 0 < e 0 = | (
`*** DESTROYED ***` /N
`Enterprise destroyed!` /N
/F s!
)
;

// Function O - Clear Map
:O
64 (
46 m /i ?!
)
;

// Function P - Populate Klingons in Current Quadrant
:P
z q 1 - 8 * r + 1 - ? n!
n 0 > (
n (
/i 1 + l!
M k l 1 - 3 * 1 + ?! k l 1 - 3 * 2 + ?!
200 k l 1 - 3 * 3 + ?!
43 m k l 1 - 3 * 1 + ? 1 - 8 * k l 1 - 3 * 2 + ? + 1 - ?!
)
)
;

// Function Q - Setup Quadrant
:Q
O
79 m i 1 - 8 * j + 1 - ?!
P
;

// Function R - Damage Report
:R
`All systems operational` /N
;

// Function S - Shield Control
:S
`Transfer energy to shields (0-` e . `): ` /K 48 - a!
a 0 > a e < & (
e a - e!
g a + g!
`Shields: ` g . /N
) /E (
`Invalid!` /N
)
;

// Function T - Test
:T
`Test OK` /N
;

// Function U - Utility
:U
;

// Function V - End Game Message
:V
d 0 < d 0 = | s 0 < | s 0 = | e 0 < | e 0 = | (
`Game Over!` /N
`Play again? Type: A G` /N
)
;
