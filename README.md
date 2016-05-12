# raBBit

PNG to [BB]-forum codes translator.

# How to use

## Command line syntax

rabbit [-hlcropd] filename.png > output.txt

## Command line options

`-h` (`--help    `) - Print help  
`-l` (`--left    `) - Align image to the left (uses [left] tags)  
`-c` (`--center  `) - Align image to the center (uses [center] tags)  
`-r` (`--right   `) - Align image to the right (uses [right] tags)  
`-o` (`--optimise`) - Optimise output (removes unneeded spaces, depends on alignment)  
`-p` (`--paint   `) - Paint (uses [color=#XXXXXX] tags)  
`-d` (`--double  `) - Double. Use double block instead of single. More characters needed, but looks better.  

## Trasparency support

Program supports only full transparency, as most of the forums do not support alphablend in [color=#XXXXXX] tags.

# Examples

```
rabbit -codp bears.png > bears.txt
```

![Big picture](/screenshots/scr1.png?raw=true "Big picture")

```
rabbit -lodp hamton.png > hamton.txt
```

![Left-aligned picture](/screenshots/scr2.png?raw=true "Left-aligned picture")

The BB picture now has optimised spaces:

![Optimisation](/screenshots/scr3.png?raw=true "Optimisation demonstration")

You can also scale image 2x times by the width and use single (without --double option) filling to achieve bigger detalisation:

![Detalisation](/screenshots/scr4.png?raw=true "Detalisation demonstration")

