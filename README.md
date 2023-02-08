# Bruty
Basic bruteforce dictionary generator written in C++, with a focus on maximum efficiency and generation speed.

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
Usage: `bruty charset length [-s]`
- **charset**: the code of the charset that will be used to compose the passwords
  - `0`: lowercase letters
  - `1`: lowercase letters and digits
  - `2`: lowercase and uppercase letters
  - `3`: lowercase and uppercase letters and digits
  - `4`: lowercase and uppercase letters, digits and symbols
- **length**: the length of the password
- **-s**: silent mode, do not print progress information

## Performance
Tests performed on a Macbook Air M1
- `bruty 0 6 > out.txt`: 10.3 seconds
- `crunch 6 6 abcdefghijklmnopqrstuvwxyz > out.txt`: 30.0 seconds

So bruty appears to be around 3x faster than crunch.
