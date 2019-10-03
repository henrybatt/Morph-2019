#include <Position.h>


void  Position::calcRobotPosition(Camera Cam, float _heading){
   
    heading = heading;
    camVisible = false;

    if (Cam.attack.visible || Cam.defend.visible){

        camVisible = true;

        int angle = Cam.attackClosest() ? Cam.attack.angle  : mod(Cam.defend.angle + 180, 360);
        angle = mod(angle + heading, 360);

        double distance = Cam.closestCentimeter();

        // Decide if in attacking or defending side of field to determine what quadrant group were in. (Positive or negative y)
        int quadrant = ((Cam.attackClosest()) ? 1 : -1);

        // Robot Position calculation. Polar > Cartesian
        int i = constrain(distance * -sin(degreesToRadians(angle)), (-FIELD_WIDTH_CM / 2), (FIELD_WIDTH_CM / 2));
        int j = constrain(FIELD_LENGTH_WITH_GOAL * quadrant  + (distance * -cos(degreesToRadians(angle))), (-FIELD_LENGTH_CM / 2), (FIELD_LENGTH_CM / 2));
        robotPosition = Vector(i, j);

        #if DEBUG_POSITION
            Serial.print(robotPosition.i);
            Serial.print(" , ");
            Serial.println(robotPosition.j);
        #endif
    }

}


void Position::calcBallPosition(){
    ballRelPosition = ballInfo.vector(heading);
    ballPosition = robotPosition + ballRelPosition;
}



bool Position::moveToCoord(MoveData *moveData,  Vector vector){
    if (camVisible){
        // Movement can be calculated, move by the point difference between coords
        return moveByDifference(*&moveData, vector - robotPosition);
    } else {
        //Cannot calculate position, stop
        *moveData = MoveData(-1,0);
        return false;
    }

}


bool Position::moveByDifference(MoveData *moveData, Vector diff){
    if (diff.mag < COORD_THRESHOLD_DISTANCE){
        //At coords, stop
        *moveData = MoveData(-1,0);
        return true;
    } else {
        // Calculate direction towards coords
        *moveData = MoveData(mod(diff.arg - heading, 360), abs(coordPID.update(diff.mag, 0)));
        return false;
    }

}

void Position::test(){


}