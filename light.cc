/**
 * @file light.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/light.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Light::Light()  : motion_handler_(this), motion_behavior_(this) {
  motion_handler_.set_velocity(1, 1);
  set_type(kLight);
  set_color(LIGHT_COLOR);
  set_pose(SetPoseRandomly());
  set_radius(LIGHT_RADIUS);
}

void Light::TimestepUpdate(unsigned int dt) {
  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity();

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Light::Reset() {
  set_pose(SetPoseRandomly());
  set_color(LIGHT_COLOR);
  set_radius(LIGHT_RADIUS);
  sensor_touch_->Reset();
  motion_handler_.set_velocity(1, 1);
} /* Reset */

void Light::HandleCollision(EntityType object_type, ArenaEntity * object) {
//  motion_handler_.set_collision_timer(20);

  switch (object_type) {
    case kRightWall:
    case kLeftWall:
    case kTopWall:
    case kBottomWall:
    case kLight:
     sensor_touch_->HandleCollision(object_type, object);
     break;
    case kRobot:
    case kBase:
      break;;
    default:
      break;
  }
}

NAMESPACE_END(csci3081);
