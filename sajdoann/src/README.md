FireWall
    FireWall je tower defense hra. Počítači se rozbil firewall, a tak je úkolem hráče udělat patche, tak aby skrz firewall proniklo
co nejméně zákeřných virů.
    Hráč má ale omezené prostředky - má konečnou velikost ramky. A tak hráč rozmisťuje různé druhy patchů na hrací pole a musí si
vystačit s ramkou co má (Patche jsou náročné na ram).
    Poté přichází na řadu simulace útoku. Hráč pozoruje, jak viry cestují z levého okraje a snaží se proniknout přes firewall. Viry se
pohybují různým stylem (zleva-doprava, nejkratší možná cesta, inteligentní - vidí dopředu) z levé strany a chtejí proniknout doprava.
Některé patche mají schopnost střílet na viry hotfixy. Hotfixy se pak šíří dál po hracím poli podle druhu patche, co je vystřelil.

Zkráceně tato tower defense hra má 3 části:
    1. "welcome" je hráč uveden do děje.
    2. "set-up" hráč rozmusťuje patche
    3. "attack" viry se snaží proniknout přes patche



main
Game - while loop
levels - waves (po uspesne wave pribydou body na koupi hotfixu)
enum GameOptions {resqueOldPC, newGame, exit };
enum GameState   {setUp, preparation, attack};
enum GameTurns   {hackerTime, engeneersTime};
enum Result      {win, lose, inPlay}; //later add FinalResult

scoreCounter
    - budget(money to buy hotfixes)
    - engeniers efficiency (how many have breached)


Player
    defender
    AI

Canvas(clear, draw, add shape)
\Game
CLIHeadline
CLIBoard
CLIscoreCounter
CLIHelp

\Intro
CLIStory

Reader, Writer of Game into file

Board
    - width
    - height
    - Tiles [][] tiles;

AbstractObject (isAt)
    - expirementDate
    -

Tile
    tower
    empty
    wall

Moving objects (movementDef)
    virus                               //needs BFS
    hotfix
    (virus ma zivoty napr 5, zasah hotfixem snizuje o 1)

FireWall ON!
          ----------------------------------
         ||       *   X     #              <
         ||   A *     _              =     <
         ||                          &     <  HACKER
         ||  D ) ) )                 @     <
         ||                          #     <
         ||                                <
         -----------------------------------
super script minus


 keys  hotfix type      char   hotfix
 w     wall             #
 a     abstract         a         *
 d     right            D         )
 z     down                       -
enter - hit my wall with next wave
ctrl+c quit program

¤, «, », ¦, ^,
co s #?
+ ... black hole

_________________________________
||       *     N       W        ¦
||   i *       _                ¦
||             _           &    ¦
||  D ) ) )                @    ¦
||                         #    ¦
||_________________________%____¦


attacers
&  powerful tool of every hacker -3
<

GRAPHICS:

FireWall ON!
----------------------------------
||       *   X     #/W            <
||   A *     _              =     <
||                          &     <  HACKER
||  D ) ) )                 @     <
||                          %     <
||                                <
-----------------------------------


Congrats! You've made it through the attack!
Now its time to take more security measures before the next vicious hackers come!
To commit the changes press enter.
After that your fix goes online and the hacker might try to make a breach;

press
    h for help
    ctrl + c to exit
    ctrl + s to exit and save the game