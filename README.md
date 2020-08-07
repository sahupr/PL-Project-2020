# PL-Project-2020

Project for CS3003

## Dependencies

### Haskell

-   ghc compiler

-   [aeson](https://hackage.haskell.org/package/aeson)
-   [utf8-string](https://hackage.haskell.org/package/utf8-string)

### C

-   gcc compiler

### Prolog

-   SWI-Prolog compiler

## Compile

-   `gcc bin/C/task2.c bin/C/json_parser/json.c -o task2 -lm`
-   `gcc bin/C/task3.c bin/C/json_parser/json.c -o task3 -lm`
-   `ghc bin/Haskell/task4.hs` (if not working try `ghc bin/Haskell/task4.hs -dynamic`)

## Run

-   `python main.py`
