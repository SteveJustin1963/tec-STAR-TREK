
### 1. Load the program

Paste the whole block of definitions into Mint:

```
:I 20 w! 20 h! 1 r! 1 c! 10 k! 10 l! P ;
:P `E=` r . ` K=` k . `,` l . ` POS=(` r . `,` c . `)` /N 
   h ( w ( /j r = /i c = & ( `E` ) /E ( /j k = /i l = & ( `K` ) /E ( `.` ) ) ) /N ) ;
:U r 1 > ( r 1 - r! ) P ;
:D r h < ( r 1 + r! ) P ;
:L c 1 > ( c 1 - c! ) P ;
:R c w < ( c 1 + c! ) P ;
:A 0 < ( - ) ;
:S k 0 > l 0 > & ( r k - A /i! c l - A /j! /i /j + 2 < 
     ( `Hit` /N 0 k! 0 l! ) 
     /E ( `No target` /N ) ) 
   /E ( `No enemy` /N ) P ;
```

---

### 2. Initialise

Type:

```
I
```

This sets the grid to 20×20, puts your ship `E` at row=1 col=1, and the Klingon `K` at row=10 col=10. It also draws the first map.

---

### 3. Commands you can use

* `U` → move **up** one cell
* `D` → move **down** one cell
* `L` → move **left** one cell
* `R` → move **right** one cell
* `S` → **shoot**.

  * If `K` is adjacent (in the 8 surrounding cells), it prints `Hit` and removes the Klingon.
  * Otherwise it prints `No target`.

Each command automatically **redraws** the map, so you always see where `E` and `K` are.

---

### 4. Objective

* Walk your ship (`E`) across the grid until you are right next to the Klingon (`K`).
* When adjacent, press `S` to fire.
* It will say `Hit` and `K` will disappear.
* After that, the map redraws showing only your ship.

---

That’s it: a super-minimal **move + shoot** loop written strictly in Mint-manual style.

Do you want me to expand this tiny demo into something closer to the **auto-scan / auto-shields / auto-weapons** version you described earlier, but still staying within the Mint manual limits?
