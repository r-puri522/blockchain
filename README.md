# Blockchain Ledger (C++)

A lightweight, from-scratch **blockchain-style ledger** implemented in C++. It models a chain of blocks where each block stores data plus a hash that links it to the previous block—making tampering easy to detect.

## What it does

- Creates a **genesis block** automatically (the first block in the chain)
- Lets you **append new blocks** with user-provided data
- Can **display** the full chain
- Can **validate** the chain’s integrity (detects broken links / modified data)
- Supports **saving** the chain to disk and **loading** it back

## How the chain works

Each block includes:

- `index` — the block’s position in the chain
- `timestamp` — creation time as a string
- `data` — the payload (transaction/message)
- `prevHash` — the previous block’s hash
- `hash` — this block’s hash, derived from its contents

A block’s `prevHash` should exactly match the previous block’s `hash`. If any earlier block changes, the hashes stop matching and validation fails.

## Hashing approach

This project uses a simple deterministic hash (good for learning, not for real security):

1. Concatenate: `index + timestamp + data + prevHash`
2. Sum the **ASCII values** of every character in that concatenated string
3. Convert the sum to a **hex string**

That hex string is stored as the block’s hash.

## Data persistence format

When saved, the blockchain is written as **one block per line**, pipe-delimited:

    index|timestamp|data|previousHash|currentHash

Loading reconstructs the chain from that file content.

## CLI menu

The program provides a simple console menu:

1. Add a New Block  
2. Display the Blockchain  
3. Validate the Blockchain  
4. Save Blockchain to File  
5. Load Blockchain from File  
6. Exit  

## Build & run

To compile:

    g++ main.cpp -o PA4.exe

To run:

    ./PA4.exe

## Project structure

- `main.cpp` — menu + CLI driver
- `Block.h` — block definition + hashing utilities
- `Blockchain.h` — blockchain management (append/display/validate/save/load)
