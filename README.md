# Centipede-game_project
A game made by me as a project by my institue. It uses sfml as a library in the c++ for providing 
the graphics for the game and then the sfml commands are used for the functioning of those graphics.
For seeing and running the game you have to use the terminal with the commands i have provided.

Gameplay :-

Fighter Vs. Centipede

1. The entire field(Screen) is divided into rows and columns in a form of a multi-dimensional
array.
2. The player's fighter is represented by a rectangle at the bottom of the screen.
3. The enemy is represented by a centipede consisting of 12 segments at the first level..
4. The player can move only in payer area. This area is five rows high and spans the entire
width of the field. Upon moving upwards or sideways, the player can step a row or a column
at a time using keyboard arrow keys.
5. The player moves the fighter around the bottom area of the screen and fires laser shots at a
centipede advancing from the top of the screen down through a field of mushrooms. The
traveling of laser will be represented by white pixels.
6. Whenever the laser hits a centipede segment, it splits the into two pieces at that point. Each
piece then continues independently on its way down the screen, with the rear piece growing
its own head. If the head is destroyed, in the earlier levels then the whole segment will be
destroyed but in advanced levels if the head is destroyed then the segment behind it becomes
the next head.
7. The centipede starts at the random location of the screen and traveling to the left side.
8. The head of centipede can be of different colors in different levels. (See point 6.)
9. When the centipede eats a mushroom or reaches the edge of the screen, it descends one level
and reverses direction. Thus, more mushrooms on the screen cause the centipede to descend
more rapidly.
10. The player can destroy mushrooms by shooting them, but each takes two shots to destroy. The game
starts with a random number of mushrooms between 20 and 30 and displayed at random locations.
11. If there is only head remaining in the centipede segment and it is hit by laser then it is killed
12. Once the centipede reaches the bottom of the screen, it moves back and forth within the player area
and one-segment "head" centipedes will periodically appear from the side. This continues until the
player has eliminated both the original centipede and all heads.
13. In the player area if fighter hit the centipede with the laser, it will create a poisonous mushroom. If the
fighter touches poisonous mushroom then it will kills the fighter.
14. The fighter will be destroyed when hit by any segment of centipede.
15. The speed of centipede will be double in each advance level.

Scoring :
   Mushrooms: 1 (destroyed)
   Centipede: 10 (body) or 20 points (head).
