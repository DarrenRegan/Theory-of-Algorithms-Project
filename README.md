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
./md5 test.txt  //Runs MD5 Algorithm on text document
./md5 -h        //Runs help command which gives instructions on commands and how to run app
./md5 -x        //Runs a MD5 Test suite
./md5 -t        //Runs a unit test for FGHI
./md5 -v        //Displays current versions of software installations
```
###  MD5 Algorithm Description
The following five steps are performed to compute the message digest of the message.

##### Step 1. Append Padding Bits
Pad message so that its length is congrugent to 448, module 512. That is, the message is extended so that it is just 64 bits shy of being a multiple of 512 bits long.

##### Step 2. Append Length
A 64-bit representation of b is appended to the result of the previous step. In the unlikely event that b is greater than 2^64, then only the low-order 64 bits of b are used.

##### Step 3. Initialize MD Buffer
A four-word buffer (A, B, C, D) is used to compute the message digest.

##### Step 4. Process Message in 16-Word Blocks
Define four auxiliary functions that each take as input three 32-bit words and produce as output one 32-bit word.
```
F(X,Y,Z) = XY v not(X) Z
G(X,Y,Z) = XZ v Y not(Z)
H(X,Y,Z) = X xor Y xor Z
I(X,Y,Z) = Y xor (X v not(Z))
```
##### Step 5. Output
The message digest produced as output is A, B, C, D. That is, we 
begin with the low-order byte of A, and end with the high-order byte
of D.

## Author

* [Darren Regan](https://github.com/DarrenRegan)

## Research Links

* https://tools.ietf.org/html/rfc1321
* [Print int as set of 4 bytes in little endian](https://stackoverflow.com/questions/17912978/printing-integers-as-a-set-of-4-bytes-arranged-in-little-endian)
* https://en.wikipedia.org/wiki/MD5
* [Video - Hashing Algorithms and Security](https://www.youtube.com/watch?v=b4b8ktEV4Bg)
* [Video - SHA: Secure Hashing Algorithm](https://www.youtube.com/watch?v=DMtFhACPnTY)

