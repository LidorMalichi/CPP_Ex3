
# CATAN

## Overview

This repository contains a C++ catan game

 ## Game commands

  * **board**: Prints the game board to the terminal.
  * **roll**: rolls the dices.
  * **status**: Prints the players victory points and resources to the terminal.
  * **settlements**: Prints the player's settlements locations.
  * **build-road <vertex1#-vertex2# >**: Builds a road on the given edge.
  * **build-settlement <vertex#>**: Builds a settlement on the given vertex.
  * **improve <vertex#>**: Builds a city on the given vertex.
  * **trade <id> <give> <take>**: Trades given resources with given player.
  * **trade-dev <id> <give> <take>**: Trades given dev cards with given player.
  * **buy-dev**: Buy dev card
  * **devs**: Prints player's dev cards to the terminal
  * **play-dev <card (Victory, Monopoly <resource>, Year-of-plenty <resource1,resource2>,
            Road-building <vertex1#-vertex2#,vertex1#-vertex2#>, knight)>**: Plays given dev card.
  * **end**: Ends player's turn.
  * **help**: Prints valid commands to the terminal.

## Usage

### Running the Game

To run the game, use the following command:

```bash
make run
```

### Running Tests

To run tests, use the following command:

```bash
make runtests
```
### Cleaning Up Files

To delete files created during compilation and execution, use the following command:

```bash
make clean
```
