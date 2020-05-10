##FireWall
###Informace:
 FireWall je tower defense hra. 
 
 Počítači se rozbil firewall, a tak je úkolem hráče udělat **patche**, tak aby skrz firewall proniklo co nejméně zákeřných virů.
 
Hráč má ale omezené prostředky - má konečnou velikost **ramky**. A tak hráč rozmisťuje různé druhy patchů na hrací pole a musí si
vystačit s ramkou co má (Patche jsou náročné na ram).

Poté přichází na řadu simulace útoku. Hráč pozoruje, jak **viry** cestují z levého okraje a snaží se proniknout přes firewall. Viry se
pohybují různým stylem (zleva-doprava, nejkratší možná cesta, inteligentní - vidí dopředu) z levé strany a chtejí proniknout doprava.

Některé patche mají schopnost střílet na viry **hotfixy**. Hotfixy se pak pohybují dál po hracím poli.

###Fáze hry:
Hra má 3 části:
1. `welcome` je hráč uveden do děje.
2. `preparation` hráč rozmusťuje patche
3. `attack` viry se snaží proniknout přes patche

###Dědičnost a polymorfismus:
Třídy:
- Object (PrintObject, PrintInfo)
    - moving object
        - hotfix
        - virus
    - patch
    - empty
    
jiné třídy nic nedědí. S těmito třídami jsou ještě spjaté třídy z Movement složky, kde jsou všechny možné
pohyby po board pro moving objects. Classa moving object si pamatuje movement type a movement direction.

Polymorfismus využívám pro metody PrintObject a PrintInfo v objektu, ty jsou implementovány v 
hotfixu, virusu, patchi a empty. 
 
 (stačí to?)
 
 // původně měl být ještě pro metodu move, ale k té
potřebuju board do kterého includuju objecty, tj objecty nemůžou 
includovat board(zacyklené includy).
 Jelikož pohyby mají být inteligentní board potřebuju nezbytně.
Asi by nebyl problém si poslat nějaký otisk board, typu každému typu objectu přiřadím číslo. Ale
nepřipadalo mi to úplně jako nej řešení, tak jsem to překopala na to,
 že mám třídu mimo (movement, includuju ji v game a beru si patche z pointru 
 na board co  si třída pamatuje.) Je to ok? 
 Plánuju si ještě hrát s barvičkami u printů.

###Třídy a reprezentace
 Krom výše zmíněných tříd zde je: 
  - `Interface` (uživatelské rozhraní)
  - `Command` - třída na příkazy, pamatuje si stringy jméno a help + co se má provést (function z functional většinou lambdu)
  - `Commands` - třída která si pamatuje všechny commandy
  - `Game` - instance hry, pamatuje si patche, virusy, board a skóre
  - `Reader` a `Writer` - pro načítání a ukládání
  - `App` - zastřešuje interface a game
  - `Movement složka` - třídy s pohybem, seznamem funkcí pohybu objektu, typu pohybu objektu
  - `enumy` na stavy hry, typu vráceného z commandu...
    
###Příkazy
(P ... zkratka patch)
help:
- `type P (x,y)` -   places patch, syntax: " patch Type (coord x, coord y)" ... for example "W(0,0)"
- `done`         -   Type it when you are done - you think FireWall can survive the next attack.
- `exit`         -   exits the game witout saving
- `help`         -   lists all the commands
- `google P`     -   prints all the available information about the patch

###Ukázka 
stav preparation - náhled ( bohužel markdown nemá rád barvičky, ale bude to barevně :D)
```
patches:
   0  1  2  3  4  5  6  7  8  9
0  W  -  -  -  -  -  -  -  -  -
1  -  -  W  -  -  -  -  -  -  -
2  -  -  -  W  -  -  -  -  -  -
3  R  -  -  -  -  -  -  -  -  -
4  -  -  -  -  -  -  -  -  -  -
5  -  -  -  -  -  -  W  -  -  -
6  -  -  -  -  -  -  W  -  -  -
7  -  -  -  -  -  -  W  W  -  -
8  -  -  -  -  -  -  -  W  -  -
9  D  -  -  -  -  -  -  -  -  -
Enter command: 
W(5,6)
``` 


 


    




