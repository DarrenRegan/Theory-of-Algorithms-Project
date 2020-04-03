# Theory-of-Algorithms-Project - MD5 message-digest algorithm. 

### Introduction
The algorithm takes as input a message of arbitrary length and produces as output a 128-bit "fingerprint" or "message digest" of the input. The MD5 algorithm is designed to be quite fast on 32-bit machines. In addition, the MD5 algorithm does not require any large substitution tables; the algorithm can be coded quite compactly. MD5 is used for verifying files and transmissions, it should never be used for more as its very easy to break.


### Installing

1. Clone the repo

```
git clone https://github.com/DarrenRegan/Theory-of-Algorithms-Project.git
```

2. cd Theory-of-Algorithms-Project and run commands
```
make md5
./md5 test.txt
```
###  MD5 Algorithm Description
The following five steps are performed to compute the message digest of the message.

##### Step 1. Append Padding Bits

##### Step 2. Append Length

##### Step 3. Initialize MD Buffer

##### Step 4. Process Message in 16-Word Blocks

##### Step 5. Output

## Author

* [Darren Regan](https://github.com/DarrenRegan)

## Research Links

* https://tools.ietf.org/html/rfc1321
* [Print int as set of 4 bytes in little endian](https://stackoverflow.com/questions/17912978/printing-integers-as-a-set-of-4-bytes-arranged-in-little-endian)
* https://en.wikipedia.org/wiki/MD5
* [Video - Hashing Algorithms and Security](https://www.youtube.com/watch?v=b4b8ktEV4Bg)
* [Video - SHA: Secure Hashing Algorithm](https://www.youtube.com/watch?v=DMtFhACPnTY)

