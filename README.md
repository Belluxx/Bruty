# Bruty
Basic bruteforce dictionary generator written in C++

## Features
- Various charsets available
- Write to file or print or to stdout
- Show progress in real time

## Build
Fastest way to build the project:
1. Download the [source code zip](https://github.com/Belluxx/Bruty/archive/refs/heads/main.zip)
2. Extract the source code
3. Open the extracted folder in a terminal and run the following commands
4. `mkdir Release`
5. `cd Release`
6. `cmake .. -DCMAKE_BUILD_TYPE=Release`
7. `make`
8. Run the compiled binary with `./Bruty`

## Usage
Usage: `bruty charset length [-f out_file]`
- **charset**: the code of the charset that will be used to compose the passwords
  - **Barebone** (code `0`): lowercase letters
  - **Minimal**  (code `1`): lowercase letters and digits
  - **Basic**    (code `2`): lowercase and uppercase letters
  - **Normal**   (code `3`): lowercase and uppercase letters and digits
  - **Big**      (code `4`): lowercase and uppercase letters, digits and symbols
- **length**: the length of the password
- **out_file**: the name of the file where passwords will be written

## Performance
Tests performed on a Macbook Air M1
- `bruty 0 6 > out.txt`: 12.6 seconds
- `bruty 0 6 -f out.txt`: 20.8 seconds
- `crunch 6 6 abcdefghijklmnopqrstuvwxyz > out.txt`: 30.0 seconds

So bruty appears to be around 2.4x faster than crunch (in output redirect mode).
