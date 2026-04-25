use an OOP design:
- the game runs on ticks, on every time, some progress is made
  - this progress can stop if there is a game win or loss
- first, let's list out what progress happens:
  - user input is taken
  - snake moves
    - if there is a collision: game lost
    - if snake length is maximum: game win
    - if there is a piece of food: increase snake length
      - spawn a fruit at a random position
- to implement this, we can encapsulate the game in a SnakeGame object with a tick() function
  - tick() will advance all pieces and return the status of the game
  - render() will print the game board

main logic is a FSM:
  - print overview, wait for user to ENTER (START STATE) ->
    - render board and ask for user input (INPUT STATE) ->
      - run SnakeGame.tick() and based on the state of the board:
        - if PLAYING: go back to INPUT STATE
        - if LOST: go to LOSS state
        - if WIN: go to WIN state
  - render board, and print game lost and score (LOSS state)
    - on ENTER, go back to START STATE
  - render board, and print game win and score (WIN state)
    - on ENTER, go back to START STATE
