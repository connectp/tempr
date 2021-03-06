/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/params.h"
#include "src/base.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
 Robot::Robot() : motion_handler_(this), motion_behavior_(this), lives_(9) {
   motion_handler_.set_velocity(1, 1);
   set_color(ROBOT_COLOR);
   set_pose(ROBOT_INIT_POS);
   set_radius(ROBOT_RADIUS);
   set_type(kRobot);
 }
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity();

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
} /* TimestepUpdate() */

void Robot::Reset() {
  set_pose(SetPoseRandomly());
  motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  set_radius(SetRadiusRandomlyForRobot());
  lives_ = 9;
  sensor_touch_->Reset();
} /* Reset() */

void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
//  motion_handler_.set_collision_timer(20);

  switch (object_type) {
    case kRightWall:
    case kLeftWall:
    case kTopWall:
    case kBottomWall:
    case kRobot:
      sensor_touch_->HandleCollision(object_type, object);
      break;
    case kBase:
      std::cout << gett_pose().x << gett_pose().y << std::endl;
    ///  set_pose(SetPoseRandomly());
      break;
    default:
      break;
  }
} /* HandleCollision() */


void Robot::IncreaseSpeed() {
  motion_handler_.IncreaseSpeed();
}
/*
void Robot::DecreaseSpeed() {
  motion_handler_.DecreaseSpeed();
}
void Robot::TurnRight() {
  motion_handler_.TurnRight();
}
void Robot::TurnLeft() {
  motion_handler_.TurnLeft();
}
*/
NAMESPACE_END(csci3081);
