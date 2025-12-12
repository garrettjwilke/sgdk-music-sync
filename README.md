# sgdk-music-sync
SGDK sync game with MDSDRV music

## features

sync your game events to the music.
  * create interesting boss fights that adjust in realtime to your music tracks.
  * make a rhythm game
  * sync up the end of one song to perfectly transition into the next with perfect timing.
  * anything you can imagine :)

## how it works

i made a custom fork of [MDSDRV](https://github.com/garrettjwilke/MDSDRV/tree/rng-patterns) (use the `rng-patterns` branch).
it enables the unused `comm` byte to send a single byte every frame. this takes advantage of this by enabling it and allowing the user to send `comm` bytes.

the following MML will send `comm 1` at the start of the first `a` note, then it will send `comm 2` at the start of the `b` note. it will loop (`L`) and allow the user to keep track of when the notes happen
```
A @1 L l4 'comm 1' a 'comm 2' b
```

we use the `MDS_command(16, 0` function to track these `comm` signals in our SGDK code. the output of `MDS_command(16, 0)` will simply be a `u8` you can use in your game code:
```
u8 comm_signal;
comm_signal = MDS_command(16, 0);
switch (comm_signal):
{
  case 0:
    kprintf("signal 0");
    break;
  case 1:
    kprintf("signal 1");
    break;
}
```

---

## how to compile your music to actually use this thingy
this requires a custom MDSDRV and custom `mdslink` to compile the music:

[MDSDRV](https://github.com/garrettjwilke/MDSDRV/tree/rng-patterns)

[mdslink (ctrmml)](https://github.com/garrettjwilke/ctrmml/tree/rng-patterns)


building these from source and recompiling your MML with `mdslink` every time you make a change can be annoying/difficult. i have created a custom fork of `mmlgui` that has a tool to build your MML files:
[mmlgui - custom fork](https://github.com/garrettjwilke/mmlgui)

### recompile MML music from the mmlgui custom fork
1. click on `Tools` from the menu and choose `mdslink export`
2. choose your mml background music folder
3. choose your mml sfx folder
4. choose your export directory
5. click on `export` and copy the files to the `res/mdsdrv` directory
  * the files generated are:
    1. `mdspcm.bin`
    2. `mdsseq.bin`
    3. `mdsseq.h`

### recompile MML music using mdslink
1. compile `mdslink` from the [mdslink (ctrmml)](https://github.com/garrettjwilke/ctrmml/tree/rng-patterns) fork.
2. tell `mdslink` where your MML music and sfx data is, and compile:
  `./mdslink -o "PATH/TO/SGDK/PROJECT/res/mdsdrv/mdsseq.bin" "PATH/TO/SGDK/PROJECT/res/mdsdrv/mdspcm.bin" -h "PATH/TO/SGDK/PROJECT/res/mdsdrv/mdsseq.h" PATH/TO/MML_MUSIC/*.mml PATH/TO/MML_SFX/*.mml`
3. hopefully it works

---
