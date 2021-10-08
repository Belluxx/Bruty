# Bruty
Basic bruteforce dictionary generator written in C++

## Features
- Various charsets available
- Write to file or print or to stdout
- Show progress in real time

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
