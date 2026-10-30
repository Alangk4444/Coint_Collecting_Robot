#ifndef ROBOT_H
#define ROBOT_H
#include <stdbool.h>
typedef struct Robot Robot;

Robot* CreateRobot(int startY, int startX, int startDirection);

void Forward(Robot* robot, int height, int width, int arena[height][width]);

void Left(Robot* robot, int height, int width, int arena[height][width]);

void Right(Robot* robot, int height, int width, int arena[height][width]);

bool AtMarker(Robot* robot, int height, int width, int arena[height][width]);

bool CanMoveForward(Robot* robot, int height, int width, int arena[height][width]);

void PickUpMarker(Robot* robot);

void DropMarker(Robot* robot);

int MarkerCount(Robot* robot);

bool IsWallInFront(Robot* robot, int height, int width, int arena[height][width]);

bool CornerCheck(Robot* robot, int height, int width, int arena[height][width]);

void GoToCorner(Robot* robot, int height, int width, int arena[height][width]);

void CollectMarkers(Robot* robot, int height, int width, int arena[height][width]);

void UpdateImage(Robot* robot, int height, int width, int arena[height][width]);

#endif