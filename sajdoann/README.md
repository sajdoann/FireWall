## FireWall
### Informace:
 FireWall je tower defense hra. 
 
 Počítači se rozbil firewall, a tak je úkolem hráče udělat **patche**, tak aby skrz firewall proniklo co nejméně zákeřných virů. 

Hráč má ale omezené prostředky - nemůže si koupit kolik patchů chce. A tak hráč rozmisťuje různé druhy patchů na hrací pole a musí si
vystačit s herními penězmi co má. Patche je možné upgradovat (na místo kde už patch je dát lepší).

Poté přichází na řadu simulace útoku. Hráč pozoruje, jak **viry** cestují z levého okraje a snaží se proniknout přes firewall. Viry se
pohybují různým stylem (zleva-doprava, nejkratší možná cesta) z levé strany a chtejí proniknout doprava.

Některé patche mají schopnost střílet na viry **hotfixy**. Hotfixy se pak pohybují dál po hracím poli.

### Fáze hry:
Hra má 3 části:
1. `menu` možnost načíst uloženou hru nebo rozehrát novou hru.
2. `preparation` hráč rozmusťuje patche
3. `attack` viry se snaží proniknout přes patche

### Dědičnost a polymorfismus:
Třídy:
- Object (SaveObject, PrintInfo, LoadObject, isEmpty, isMovingObj, isVirus, Attack)
    - empty
    - ObjectWithMoveAttributes
        - patch
        - moving object
            - hotfix
            - virus
       
- Strategy
    - Front
    - Bfs
    - Random (ve smeru do leva (tj diagonalne v levo a v levo) jinak smery zbyvající)      
 
 S těmito třídami jsou ještě spjaté třídy z Movement složky, kde jsou všechny možné
pohyby po board pro moving objects. Classa moving object si pamatuje movement type a movement direction.

Polymorfismus využívám pro metodu Attack, která se provede pro příslušný objekt. Tato metoda u moving objectů volá příslušnou 
strategii (getTargetCoords, ExecMove).
 
### Třídy a reprezentace
 Krom výše zmíněných tříd zde je: 
  - `Interface` - uživatelské rozhraní
  - `Command` - třída na příkazy, pamatuje si stringy jméno a help + co se má provést (function z functional většinou lambdu)
  - `Commands` - třída která si pamatuje všechny commandy
  - `Game` - instance hry, pamatuje si patche, virusy, board a skóre
  - `Reader` a `Writer` - pro načítání a ukládání
  - `App` - zastřešuje interface a game
  - `Movement složka` - třídy s pohybem, seznamem funkcí pohybu objektu, typu pohybu objektu
  - `enumy` na stavy hry, typu vráceného z commandu...
    
### Příkazy
(P ... zkratka patch)

například:

`help:`

- `google`       -   type the name of the object and all you will get all info about it
- `type(x,y)`    -   places patch, syntax: " patch Type (coord x, coord y)" ... for example "W(0,0)"
- `done`         -   type it when you are done - you think FireWall can survive the next attack.
- `exit`         -   exits the game witout saving. To save type save
- `explain`      -   explains game
- `help`         -   lists all the commands
- `patches`      -   describes all patches
- `quit`         -   quits the current game and goes to menu (where new game or load saved game can be choosed)
- `save`         -   saves the game into files
- `show`         -   shows the entire firewall that was till now coded.
- `viruses`      -   describes all viruses

### Ukázka 
stav preparation - náhled 
```
patches:
   0  1  2  3  4  5  6  7  8  9
0  D  -  -  -  -  -  -  -  -  -
1  -  -  W  W  W  -  -  -  -  -
2  -  -  -  W  W  R  -  -  -  -
3  -  -  -  -  W  -  -  -  -  -
4  -  -  -  -  -  -  -  -  -  -
5  -  Z  -  -  -  -  -  -  -  -
6  -  -  -  -  -  -  -  -  -  -
7  -  -  -  W  -  -  -  -  -  -
8  -  -  -  W  -  -  -  -  -  -
9  -  -  -  -  -  -  -  -  -  -
Enter command: 

W(4,4)
``` 


 


    




