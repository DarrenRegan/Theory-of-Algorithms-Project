# MD5 message-digest algorithm - Report

## Introduction
The algorithm takes as input a message of arbitrary length and produces as output a 128-bit "fingerprint" or "message digest" of the input. The MD5 algorithm is designed to be quite fast on 32-bit machines. In addition, the MD5 algorithm does not require any large substitution tables; the algorithm can be coded quite compactly. MD5 is used for verifying files and transmissions, it should never be used for more as its very easy to break.

This repository contains the C code in the file md5.c aswell has a document used for testing test.txt, a folder of some of the labs that are extremely useful before attempting the project and finally a README and a overview report of the project.

### What the code does - Use of MD5
As explained in the introduction the MD5 algorithm takes an input of arbitrary length and produces as output a 128-bit "fingerprint" or "message digest" of the input. While the MD5 algorithm was originally designed for use as a secure hash algorithm for authenticating digitial signatures. MD5 has been deprecated for uses other than as a non-cryptographic checksum to verify data integrity and detect unintentional data corruption.

![](images/md5_hashing.jpg)<br>

## Run

1. Install using these commands in command line on a linux machine

```
Run sudo apt-get update before running commands below
1. vim - sudo apt-get install vim
2. gcc - sudo apt install gcc
3. GIT - sudo apt-get install git
```

2. Clone the repo

```
git clone https://github.com/DarrenRegan/Theory-of-Algorithms-Project.git
```

3. cd Theory-of-Algorithms-Project and run commands
```
make md5
./md5 test.txt  //Runs MD5 Algorithm on text document
./md5 -t        //Runs a unit test for FGHI
./md5 -h        //Runs help command which gives instructions on commands and how to run app
./md5 -v        //Displays current versions of software installations
```

## Tests
To run the unit test all you need to do is run the ./md5 -t provided in the Run section.
This will run a unit test on Step 4. of the Algorithm which processes messages in 16-Word Blocks

This test will test the F, G, H, I functions with the logic below
```
F(X,Y,Z) = XY v not(X) Z 
G(X,Y,Z) = XZ v Y not(Z)
H(X,Y,Z) = X xor Y xor Z
I(X,Y,Z) = Y xor (X v not(Z))
```
## Algorithm
The following five steps are performed to compute the message digest of the message.

## Complexity
The following five steps are performed to compute the message digest of the message.

## References

* [The MD5 Message-Digest Algorithm](https://tools.ietf.org/html/rfc1321) - This is a document from MIT that describes the MD5 message-digest algorithm. It was by far the most useful reference for this project, it very clearly lays out the steps of the algorithm and how it works. I recommened reading this document to gain a good understanding of the MD5 Algorithm
* [MD5 Wikipedia](https://en.wikipedia.org/wiki/MD5) - provides good information on what the MD5 Algorithm is, what it's used for and the history around it. There is also sections on the vulnerabilities of the algorithm and links to other implementations of such algorithm.
* [Video - Hashing Algorithms and Security](https://www.youtube.com/watch?v=b4b8ktEV4Bg) - Excellent video on Hashing Algorithms and Security, the video is well worth watching. The video will give you a good idea of the use of Hashing Algorithms if you we're unsure on exactly what they do.
* [Video - SHA: Secure Hashing Algorithm](https://www.youtube.com/watch?v=DMtFhACPnTY) - Explains Hash Functions and SHA, talks about hash functions for cryptography that are used for message authentication and digital signatures. Explains that MD5 is made to be slow because of it's uses, but these hash functions need to be quick to verify and compute.

