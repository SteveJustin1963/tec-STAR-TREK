// ============================================
// STAR TREK - Complete Game for MINT-Octave
// ============================================
// Variables: 
//   q,r = quadrant position (1-8)
//   i,j = sector position (1-8)
//   e = energy, f = torpedoes, g = shields
//   s = stardates, d = klingons left
//   z = galaxy array, m = map array, k = klingon array
//   t = temp direction, w = warp, a,b = temp

// Function A - Initialize Game
:A
3000 e!
10 f!
0 g!
30 s!
0 d!
[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] z!
0 l!
64 (
/i 8 % 1 + a!
a 1 = (
3 /i 8 / 1 + * b!
b z /i ?!
b d + d!
)
)
4 /i 8 / 1 + * q!
3 /i 8 / 1 + * r!
1 i!
1 j!
[46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46 46] m!
[0 0 0 0 0 0 0 0 0] k!
U
`STAR TREK` /N
`===========` /N
`Destroy ` d . ` Klingons in ` s . ` stardates` /N
`Good luck, Captain!` /N /N
;

// Function B - Display Short Range Scan
:B
`----- Short Range Scan -----` /N
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
`----------------------------` /N
;

// Function C - Display Status
:C
`Quadrant: ` q . `,` r . /N
`Sector: ` i . `,` j . /N
`Energy: ` e . /N
`Torpedoes: ` f . /N
`Shields: ` g . /N
`Stardates: ` s . /N
`Klingons: ` d . /N
;

// Function D - Navigate
:D
e 0 > (
`Course (1-9): ` /K 48 - t!
t 0 > t 9 < & (
`Warp (1-8): ` /K 48 - w!
w 0 > w 9 < & (
46 m i 1 - 8 * j + 1 - ?!
t 1 = ( j w - j! )
t 2 = ( i w + i! j w - j! )
t 3 = ( i w + i! )
t 4 = ( i w + i! j w + j! )
t 5 = ( j w + j! )
t 6 = ( i w - i! j w + j! )
t 7 = ( i w - i! )
t 8 = ( i w - i! j w - j! )
i 0 < ( q 1 - q! 8 i! )
i 8 > ( q 1 + q! 1 i! )
j 0 < ( r 1 - r! 8 j! )
j 8 > ( r 1 + r! 1 j! )
q 0 < ( 1 q! )
q 8 > ( 8 q! )
r 0 < ( 1 r! )
r 8 > ( 8 r! )
e w 10 * - e!
s 1 - s!
79 m i 1 - 8 * j + 1 - ?!
U
J
)
)
) /E (
`No energy!` /N
)
;

// Function E - Fire Phasers
:E
e 0 > (
`Phaser energy (1-` e . `): ` /K /K /K 48 - 100 * a! /K 48 - 10 * a + a! /K 48 - a + a!
a 0 > a e < & (
e a - e!
I /T = (
1 l!
3 (
k l 1 - 3 * 3 + ? a 3 / - b!
b 0 > (
b k l 1 - 3 * 3 + ?!
) /E (
`Klingon destroyed!` /N
d 1 - d!
0 k l 1 - 3 * 3 + ?!
46 m k l 1 - 3 * 1 + ? 1 - 8 * k l 1 - 3 * 2 + ? + 1 - ?!
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
`No energy!` /N
)
;

// Function F - Fire Photon Torpedo
:F
f 0 > (
`Course (1-9): ` /K 48 - t!
t 0 > t 9 < & (
f 1 - f!
i u!
j v!
`Torpedo track:` /N
8 (
t 1 = ( v 1 - v! )
t 2 = ( u 1 + u! v 1 - v! )
t 3 = ( u 1 + u! )
t 4 = ( u 1 + u! v 1 + v! )
t 5 = ( v 1 + v! )
t 6 = ( u 1 - u! v 1 + v! )
t 7 = ( u 1 - u! )
t 8 = ( u 1 - u! v 1 - v! )
u 0 < u 8 > | v 0 < | v 8 > | (
`Missed!` /N
8 /i!
)
u . `,` v . 32 /C
m u 1 - 8 * v + 1 - ? a!
a 43 = (
`Klingon destroyed!` /N
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
a 42 = (
`Star!` /N
)
)
/N
J
)
) /E (
`No torpedoes!` /N
)
;

// Function G - Main Game Loop
:G
C /N
/U (
s 0 > d 0 > & /W
`Command (1-9,0=help): ` /K 48 - c!
c 1 = ( B )
c 2 = ( L )
c 3 = ( D )
c 4 = ( E )
c 5 = ( F )
c 6 = ( S )
c 7 = ( C )
c 8 = ( N )
c 9 = ( 0 0 = )
c 0 = ( H )
/N
N
)
;

// Function H - Help
:H
`Commands:` /N
`1 = Short Range Scan` /N
`2 = Long Range Scan` /N
`3 = Navigate` /N
`4 = Fire Phasers` /N
`5 = Fire Photon Torpedo` /N
`6 = Shield Control` /N
`7 = Status Report` /N
`8 = End Mission` /N
`0 = Help` /N
;

// Function I - Check for Klingons
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
I /T = (
`Klingon fires!` /N
1 l!
3 (
k l 1 - 3 * 3 + ? 0 > (
k l 1 - 3 * 3 + ? 5 / h!
g h - g!
g 0 < (
e g + e!
0 g!
)
`Hit for ` h . ` damage` /N
)
l 1 + l!
)
)
;

// Function K - Calculate Distance
:K
x u - a!
y v - b!
a a * b b * + a!
;

// Function L - Long Range Scan
:L
`Long Range Scan:` /N
q 1 - 0 > ( q 1 - 8 * r + 1 - z ? . 32 /C )
z q 1 - 8 * r + 1 - ? . 32 /C
q 1 + 8 < ( z q 1 - 8 * r + 1 - ? . )
/N
q 1 - 0 > ( z q 1 - 8 * r + 1 - 1 - ? . 32 /C )
z q 1 - 8 * r + 1 - ? . 32 /C
q 1 + 8 < ( z q 1 - 8 * r + 1 - 1 + ? . )
/N
;

// Function M - Place Random Object
:M
/U (
8 /i 8 / 1 + * 1 + u!
8 /i 8 / 1 + * 1 + v!
m u 1 - 8 * v + 1 - ? 46 = /W
)
u v
;

// Function N - Check Win/Lose
:N
d 0 < d 0 = | (
`*** VICTORY! ***` /N
`All Klingons destroyed!` /N
`Mission complete!` /N
/F s!
)
s 0 < s 0 = | (
`*** DEFEAT ***` /N
`Out of time!` /N
d . ` Klingons remain` /N
/F s!
)
e 0 < e 0 = | (
`*** DESTROYED ***` /N
`Enterprise destroyed!` /N
/F s!
)
;

// Function O - Update Quadrant
:O
46 a!
64 (
a m /i ?!
)
79 m i 1 - 8 * j + 1 - ?!
;

// Function P - Populate Klingons
:P
0 l!
z q 1 - 8 * r + 1 - ? n!
n 0 > (
n (
l 1 + l!
M k l 1 - 3 * 1 + ?! k l 1 - 3 * 2 + ?!
200 k l 1 - 3 * 3 + ?!
43 m k l 1 - 3 * 1 + ? 1 - 8 * k l 1 - 3 * 2 + ? + 1 - ?!
)
)
;

// Function Q - Quadrant Entry
:Q
O
P
;

// Function R - Damage Report
:R
`All systems operational` /N
;

// Function S - Shield Control
:S
`Shields (0-` e . `): ` /K /K /K 48 - 100 * a! /K 48 - 10 * a + a! /K 48 - a + a!
a 0 > a e < & (
e a - e!
g a + g!
`Shields now at ` g . /N
) /E (
`Invalid!` /N
)
;

// Function T - Test Function
:T
`Test OK` /N
;

// Function U - Setup Current Quadrant
:U
O
P
;

// Function V - Victory Check
:V
d 0 < d 0 = | s 0 < | s 0 = | e 0 < | e 0 = |
;

// Function W - Warp Check
:W
e 0 >
;

// Function X - Extra Utility
:X
;

// Function Y - Extra Utility
:Y
;

// Function Z - Extra Utility
:Z
;
