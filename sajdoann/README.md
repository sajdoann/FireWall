##FireWall
###Informace:
 FireWall je tower defense hra. 
 
 Počítači se rozbil firewall, a tak je úkolem hráče udělat **patche**, tak aby skrz firewall proniklo co nejméně zákeřných virů.
 
Hráč má ale omezené prostředky - má konečnou velikost **ramky**. A tak hráč rozmisťuje různé druhy patchů na hrací pole a musí si
vystačit s ramkou co má (Patche jsou náročné na ram).

Poté přichází na řadu simulace útoku. Hráč pozoruje, jak **viry** cestují z levého okraje a snaží se proniknout přes firewall. Viry se
pohybují různým stylem (zleva-doprava, nejkratší možná cesta, inteligentní - vidí dopředu) z levé strany a chtejí proniknout doprava.

Některé patche mají schopnost střílet na viry **hotfixy**. Hotfixy se pak šíří dál po hracím poli podle druhu patche, co je vystřelil.

###Fáze hry:
Hra má 3 části:
1. `welcome` je hráč uveden do děje.
2. `set-up` hráč rozmusťuje patche
3. `attack` viry se snaží proniknout přes patche

###Dědičnost:
- Object
    - moving object
        - hotfix
        - virus
    - patch
    - empty
    
jiné třídy nic nedědí. S těmito třídami je ještě spjatá třída MovementFunction, kde jsou všechny možné
pohyby po board pro moving objects.

###Polymorfismus
Polymorfismus využívám pro metody PrintObject a PrintInfo v objektu, ty jsou implementovány v 
hotfixu, virusu, patchi a empty. Dále pro moving objects mám metodu move, kterou implementují hotfixy a viry.


###Třídy a reprezentace
 Krom výše zmíněných tříd zde je: 
  - `Interface` (uživatelské rozhraní)
  - `Command` - třída na příkazy, pamatuje si stringy jméno a help + co se má provést (function z functional většinou lambdu)
  - `Commands` - mapa s klíčem (regexem na příkaz) a commandem
  - `Game` - instance hry, pamatuje si patche, virusy, board a skóre
  - `Reader` a `Writer` - pro načítání a ukládání
  - `App` - zastřešuje interface a game
  - `Movements` - třída se _seznamem_ pohybu objektu
  - `enumy` na stavy hry, typu vráceného z commandu...
    
###Příkazy
(P ... zkratka patch)
- `type P (x,y)` -   places patch, syntax: " patch Type (coord x, coord y)" ... for example "W(0,0)"
- `done`         -   Type it when you are done - you think FireWall can survive the next attack.
- `exit`         -   exits the game witout saving
- `help`         -   lists all the commands
- `google P`     -   prints all the available information about the patch


 


    




