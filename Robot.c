#include "robot.h"
#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>
#include "graphics.h"

struct Robot {

    // the true x and y coordiantes and direction of the robot in the arena
    int trueX;
    int trueY;
    int trueDirection; // 0: North, 1: East, 2: South, 3: West

    int markers;
};

Robot* CreateRobot(int startY, int startX, int startDirection) {

    Robot* robot = malloc(sizeof(Robot));

    robot->trueX = startX;
    robot->trueY = startY;
    robot->trueDirection = startDirection;

    robot->markers = 0;

    return robot;
}

void Forward(Robot* robot, int height, int width, int arena[height][width]) {

    arena[robot->trueY][robot->trueX] = 0; // clearing the robot's previous position in the arena

    if(AtMarker(robot, height, width, arena)) { // picking up marker if there is one where it is going to move
        PickUpMarker(robot);
    }

    if (robot->trueDirection == 0) {
        robot->trueY -= 1;
    } else if (robot->trueDirection == 1) {
        robot->trueX += 1;
    } else if (robot->trueDirection == 2) {
        robot->trueY += 1;
    } else if (robot->trueDirection == 3) {
        robot->trueX -= 1;
    }

    arena[robot->trueY][robot->trueX] = 4; // 4 represents the robot, the new position after moving forward

    UpdateImage(robot, height, width, arena);
}

void Left(Robot* robot, int height, int width, int arena[height][width]) {
    robot->trueDirection = (robot->trueDirection + 3) % 4;
    UpdateImage(robot, height, width, arena);
}

void Right(Robot* robot, int height, int width, int arena[height][width]) {
    robot->trueDirection = (robot->trueDirection + 1) % 4;
    UpdateImage(robot, height, width, arena);
}

bool AtMarker(Robot* robot, int height, int width, int arena[height][width]) {
    switch(robot->trueDirection){
            case 0: //facing north
                if (arena[robot->trueY - 1][robot->trueX] == 2){
                    return true;
                }else{
                    return false;    
                }
                break;
            case 1: //facing east
                if (arena[robot->trueY][robot->trueX + 1] == 2){
                    return true;
                }else{
                    return false;
                }
                break;
            case 2: //facing south
                if (arena[robot->trueY + 1][robot->trueX] == 2){
                    return true;
                }else{
                    return false;
                }
                break;
            case 3: //facing west
                if (arena[robot->trueY][robot->trueX - 1] == 2){
                    return true;
                }else{
                    return false;
                }
                break;
        }
}

bool CanMoveForward(Robot* robot, int height, int width, int arena[height][width]) {
    switch(robot->trueDirection){
            case 0: //facing north
                if (arena[robot->trueY - 1][robot->trueX] == 3 || arena[robot->trueY - 1][robot->trueX] == 1){
                    return false;
                }else{
                    return true;    
                }
                break;
            case 1: //facing east
                if (arena[robot->trueY][robot->trueX + 1] == 3 || arena[robot->trueY][robot->trueX + 1] == 1){
                    return false;
                }else{
                    return true;
                }
                break;
            case 2: //facing south
                if (arena[robot->trueY + 1][robot->trueX] == 3 || arena[robot->trueY + 1][robot->trueX] == 1){
                    return false;
                }else{
                    return true;
                }
                break;
            case 3: //facing west
                if (arena[robot->trueY][robot->trueX - 1] == 3 || arena[robot->trueY][robot->trueX - 1] == 1){
                    return false;
                }else{
                    return true;
                }
                break;
        }
}

void PickUpMarker(Robot* robot) {
    robot->markers += 1;
}

void DropMarker(Robot* robot) {
    if (robot->markers != 0) {
        robot->markers -= 1;
    }

    background();
    setColour(yellow);
    fillOval(robot->trueX * 50 + 10, robot->trueY * 50 + 10, 30, 30);

}

int MarkerCount(Robot* robot) {
    return robot->markers;
} 

bool IsWallInFront(Robot* robot, int height, int width, int arena[height][width]) {
    switch(robot->trueDirection){
            case 0: //facing north
                if (arena[robot->trueY - 1][robot->trueX] == 3){
                    return true;
                }else{
                    return false;
                }
                break;
            case 1: //facing east
                if (arena[robot->trueY][robot->trueX + 1] == 3){
                    return true;
                }else{
                    return false;
                }
                break;
            case 2: //facing south
                if (arena[robot->trueY + 1][robot->trueX] == 3){
                    return true;
                }else{
                    return false;
                }
                break;
            case 3: //facing west
                if (arena[robot->trueY][robot->trueX - 1] == 3){
                    return true;
                }else{
                    return false;
                }
                break;
        }
    return false;
}

bool CornerCheck(Robot* robot, int height, int width, int arena[height][width]) {
    int walls = 0;

    for(int i = 0; i < 4; i++) {
        if(IsWallInFront(robot, height, width, arena)) {
            walls++;
        }
        Right(robot, height, width, arena);
    }

    if (walls == 2){
        return true;
    }else{
        return false;
    }

}


void GoToCorner(Robot* robot, int height, int width, int arena[height][width]) {

    while(!CornerCheck(robot, height, width, arena)) {

        if(CanMoveForward(robot, height, width, arena)) {

            Forward(robot, height, width, arena);
    
        } else if(!CanMoveForward(robot, height, width, arena)) {
            Right(robot, height, width, arena);
        }
    }
}

void CollectMarkers(Robot* robot, int height, int width, int arena[height][width]) {
    bool finished = false;
    bool rightTurn = false; //decides when the robot should turn right or left when meeting a wall, first turn should always be a left turn

    while(IsWallInFront(robot, height, width, arena)){
        Left(robot, height, width, arena);
    }
    //when the robot is in the corner, the robot will always turn so that the wall is to the right of itself

    while(!finished){
        if(CanMoveForward(robot, height, width, arena)) {

            Forward(robot, height, width, arena);

        }else if(IsWallInFront(robot, height, width, arena)){ //how the robot should navigate when it meets a wall

            if(rightTurn){
                Right(robot, height, width, arena);
                if(CanMoveForward(robot, height, width, arena)){

                    Forward(robot, height, width, arena);
                    Right(robot, height, width, arena);

                }else if(IsWallInFront(robot, height, width, arena)){
                    finished = true;
                }else{
                    bool foundPathAround = false;

                    while(!foundPathAround){

                        Right(robot, height, width, arena);
                        if(CanMoveForward(robot, height, width, arena)){

                            Forward(robot, height, width, arena);
                            Left(robot, height, width, arena);
                        }
                        if(CanMoveForward(robot, height, width, arena)){
                            foundPathAround = true;
                        }
                    }

                    Forward(robot, height, width, arena);
                    Right(robot, height, width, arena);
                }


            rightTurn = false;
            }else{
                Left(robot, height, width, arena);
                if(CanMoveForward(robot, height, width, arena)){

                    Forward(robot, height, width, arena);
                    Left(robot, height, width, arena);

                }else if(IsWallInFront(robot, height, width, arena)){
                    finished = true;
                }else{
                    bool foundPathAround = false;
                    while(!foundPathAround){

                        Left(robot, height, width, arena);
                        if(CanMoveForward(robot, height, width, arena)){

                            Forward(robot, height, width, arena);
                            Right(robot, height, width, arena);
                        }
                        if(CanMoveForward(robot, height, width, arena)){
                            foundPathAround = true;
                        }
                    }
                    
                    Forward(robot, height, width, arena);
                    Left(robot, height, width, arena);
                }
                rightTurn = true;
            }

        }else{ //how the robot should navigate around obstacles

            int pathDeviation = 0; //how far the robot is perpendicular from its original position

            Right(robot, height, width, arena); //checking if there is a possible path to the right

            if (CanMoveForward(robot, height, width, arena)){

                Left(robot, height, width, arena);      //recentre the robot

                bool foundPathAround = false;

                while (!foundPathAround){
                    Right(robot, height, width, arena);
                    if(CanMoveForward(robot, height, width, arena)){

                        Forward(robot, height, width, arena);
                        pathDeviation++;
                        Left(robot, height, width, arena);
                        if(CanMoveForward(robot, height, width, arena)){
                            foundPathAround = true;
                        }
                    }
                }              

                if(CanMoveForward(robot, height, width, arena)){

                    Forward(robot, height, width, arena);
                }
                
                if(CanMoveForward(robot, height, width, arena)){

                    Forward(robot, height, width, arena);
                }


                Left(robot, height, width, arena);

                for(int i = 0; i < pathDeviation; i++){
                    if(CanMoveForward(robot, height, width, arena)){
                        Forward(robot, height, width, arena);
                    }
                }

                Right(robot, height, width, arena);
            }else{

                Left(robot, height, width, arena);

                bool foundPathAround = false;

                while (!foundPathAround){
                    Left(robot, height, width, arena);
                    if(CanMoveForward(robot, height, width, arena)){

                        Forward(robot, height, width, arena);
                        pathDeviation++;
                        Right(robot, height, width, arena);
                        if(CanMoveForward(robot, height, width, arena)){
                            foundPathAround = true;
                        }
                    }
                }
                    
                if(CanMoveForward(robot, height, width, arena)){

                    Forward(robot, height, width, arena);
                }

                if(CanMoveForward(robot, height, width, arena)){

                    Forward(robot, height, width, arena);
                }

                Right(robot, height, width, arena);

                for(int i = 0; i < pathDeviation; i++){
                    if(CanMoveForward(robot, height, width, arena)){
                        Forward(robot, height, width, arena);
                    }
                }

                Left(robot, height, width, arena);

            }
        }
    }
}


void UpdateImage(Robot* robot, int height, int width, int arena[height][width]) {

    setWindowSize(width * 50, height * 50);
    foreground();
    clear();

    background();
    clear();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (arena[i][j] == 3) { // wall
                background();
                setColour(red);
                fillRect(j * 50, i * 50, 50, 50);
            } else if (arena[i][j] == 0) { // empty space
                background();
                setColour(black);
                drawRect(j * 50, i * 50, 50, 50);
            } else if (arena[i][j] == 1) { // obstacle
                background();
                setColour(black);
                fillRect(j * 50, i * 50, 50, 50);
            }else if(arena[i][j] == 2){ // marker
                background();
                setColour(yellow);
                fillOval(j * 50 + 10, i * 50 + 10, 30, 30);
            }else if(arena[i][j] == 4){
                foreground();
                setColour(blue);
                switch(robot->trueDirection){
                    case 0: //facing north
                        fillPolygon(3, (int[]){j * 50 + 25, j * 50 + 5, j * 50 + 45}, (int[]){i * 50 + 10, i * 50 + 40, i * 50 + 40});
                        break;
                    case 1: //facing east
                        fillPolygon(3, (int[]){j * 50 + 40, j * 50 + 10, j * 50 + 10}, (int[]){i * 50 + 25, i * 50 + 5, i * 50 + 45});
                        break;
                    case 2: //facing south
                        fillPolygon(3, (int[]){j * 50 + 25, j * 50 + 5, j * 50 + 45}, (int[]){i * 50 + 40, i * 50 + 10, i * 50 + 10});
                        break;
                    case 3: //facing west
                        fillPolygon(3, (int[]){j * 50 + 10, j * 50 + 40, j * 50 + 40}, (int[]){i * 50 + 25, i * 50 + 5, i * 50 + 45});
                        break;
                }

            }
        }
    }
sleep(100);
    // Update the display
}
