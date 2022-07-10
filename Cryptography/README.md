# Cryptography
These programs showcase various methods of encrypting and decrypting some input.

List of currently implemented algorithms and ciphers:

## Affine
A type of monoalphabetic substitution cipher. Each letter is mapped to its equivalent number, ran through a simple mathematical formula, 
and converted back to a letter. Works similar to a Ceasar cipher, except you're also multiplying the letter by a key before shifting. 

Example: 
With a key of (5,8)
```
affine cipher
 |
 v
ihhwvc swfrcp
```

To run, simply compile and run the resulting executable. 
I still need to implement file I/O.

## ROT13
A very simple substitution cipher. Essentially a modified Ceaser shift in which every letter is shifted 13 spaces to the right. 
Because of this, running a piece of text through the program twice will result in the original text.

Example:
```
this is a sentence
abcdefghijklmnopqrstuvwxyz
 |
 v
guvf vf n fragrapr
nopqrstuvwxyzabcdefghijklm
 | (And if you run this through again...)
 v
this is a sentence
abcdefghijklmnopqrstuvwxyz
```