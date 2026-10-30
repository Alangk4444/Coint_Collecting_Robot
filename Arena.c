#include "robot.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>
#include "graphics.h"

int GenerateRandomNumber(int min, int max){

    int randomNumber = (rand() % (max - min + 1)) + min;

    return randomNumber;
}

int main(){

    srand(time(NULL)); 

    bool allMarkersFound = false;

    Robot* robot;

    bool robotPlaced = false;

    int numberOfObstacles = GenerateRandomNumber(1,3);
    int numberOfMarkers = GenerateRandomNumber(1,3);

    int arenaHeight = GenerateRandomNumber(8, 13);
    int arenaWidth = GenerateRandomNumber(8, 13);
    
    int arena[arenaHeight][arenaWidth];

    // creating an arena initially filled with nothing and walls, 0 represents nothing, 3 represents a wall
    for(int i = 0; i < arenaHeight; i++){
        for(int j = 0; j < arenaWidth; j++){
            if(i == 0 || j == 0 || i == arenaHeight - 1 || j == arenaWidth - 1){
                arena[i][j] = 3;
            }
            else{
                arena[i][j] = 0;
            }
        }
    }

    printf("Arena Size: %d x %d\n", arenaWidth, arenaHeight);
    printf("Number of Obstacles: %d\n", numberOfObstacles);
    printf("Number of Markers: %d\n", numberOfMarkers);
   
    // placing markers and obstacles in random locations, 2 represents a marker, 1 represents an obstacle
    int m = numberOfMarkers;
    while(m > 0){
        int x = GenerateRandomNumber(0, arenaWidth - 1);
        int y = GenerateRandomNumber(0, arenaHeight - 1);

        if(arena[y][x] == 0){
            arena[y][x] = 2;
            m--;
        }
    };

    int o = numberOfObstacles;
    while(o > 0){
        int x = GenerateRandomNumber(0, arenaWidth - 1);
        int y = GenerateRandomNumber(0, arenaHeight - 1);

        if(arena[y][x] == 0){
            arena[y][x] = 1;
            o--;
        }
    }

    while(!robotPlaced){
        int robotStartX = GenerateRandomNumber(1, arenaWidth - 2);
        int robotStartY = GenerateRandomNumber(1, arenaHeight - 2);

        if(arena[robotStartY][robotStartX] == 0){
            robot = CreateRobot(robotStartY, robotStartX, GenerateRandomNumber(0,3));
            arena[robotStartY][robotStartX] = 4; // 4 represents the robot
            robotPlaced = true;
        }   
    }

    UpdateImage(robot, arenaHeight, arenaWidth, arena);

    GoToCorner(robot, arenaHeight, arenaWidth, arena);

    printf("\n %d", MarkerCount(robot));

    CollectMarkers(robot, arenaHeight, arenaWidth, arena);

    GoToCorner(robot, arenaHeight, arenaWidth, arena);

    for(int i = 0; i < numberOfMarkers; i++){
        DropMarker(robot);
    }

    return 0;
}
