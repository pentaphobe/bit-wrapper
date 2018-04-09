# bit-wrapper

This was a quick (read: no build environment or documentation) experiment in making arbitrary data sets more compressible

The idea is loosely based on a shuffling approach used in classical cryptography in which data is written out in rows and read back in columns


## Caveat Dolor

- This is extremely barebones, and was hacked up just to test the concept
- Although I have prior implementations of this experiment, they're tied up in antique encryption projects and never really got tested against real world data
- As a result, this repo is lazy
  - generates some random stuff
  - outputs a series of shuffled binary files
  - compresses them with the zip commandline tool
  - lists the smallest results

Any real implementation would have:

- [ ] unit tests
- [ ] optimisation
- [ ] internal compression
- [ ] optional blocksize limiting (ie. shuffle on a per-block basis)
  - ideally sharing dictionary between all blocks (if worthwhile)
    - by default, forward motion through the blocks would mean later blocks are optimised based on what worked for earlier ones (not ideal)
  - a back-and-forth mode which tries to find the best shuffle + dictionary based on matches with other blocks (slow mode)

## How to run

  *NB: don't!*

technically just `./run.sh` (assuming your config is magically compatible with Works On My Machine™)




## Example

To keep things simple, assume we're using Run Length Encoded compression and we're acting on individual symbols rather than bits

eg.

Say our original stream is:
```
A C D A D E A D E B D F

result: 1A 1C 1D 1A 1D 1E 1A 1D 1E 1B 1D 1F
        `-------------- 12 entries -------'
```

Write it out in fixed columns
```
A C D
A D E
A D E
B D F
```

Read it back in running down the columns
```
A A A B C D D D D E E F

result: 3A 1B 1C 4D 2E 1F
         `--6 entries--'
```

## But really..

The actual approach benefits more than the contrived example, as it's reordering _bits_

All compression types I've tried so far on large-ish files seem to get some benefit from applying this (ZIP tests on random data and JPGs yield around a 30% reduction)

(On the occasions that there is not decent match in the spread selected, it's rarely 1% larger than the original)
