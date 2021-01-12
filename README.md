### Installation
```
~/.brew/bin/brew install sdl2 && ~/.brew/bin/brew install freetype && make -j
```
### Usage
```
./resources/filler_vm -f map -p1 player1.filler -p2 player2.filler
you can add :
              -s -SeedNumber (random by default)
              -t -TimeoutValue
              -q to silence
```
### Usage exemple
```
./resources/filler_vm -f resources/maps/map02 -p1 resources/players/rbalbous.filler  -p2 resources/players/rbalbous.filler | ./visu
```

