HOW THE PROGRAM WORKS

This program places a robot in a random position facing a random way in an arena.

The arena is a rectangle with random dimensions.

There are a random amount of obstacles and markers in arena placed in random positions.

The way my robot sweeps through the arena to locate the markers is through these steps:

- Go to a corner, going around any obstacles and picking up any markers

- Look at the direction where the wall is to the right of the robot

- Go Up and Down or Left and Right through each column or row, avoiding any obstacles and picking up any markers.

- Once it is done sweeping through all the squares it finds a corner if it is not already in one and drops all its markers


HOW TO RUN THE CODE

the commands are:

gcc Robot.c Arena.c Graphics.c -o (program name)

./(program name) | java -jar DrawApp-4.5.jar