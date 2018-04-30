/**
 * @file base.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/light_sensor.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

bool Light_Sensor::proximity(double pose1, double pose2) {
   if (pose2 - pose1 < 10) {
      closeness_ = true;
   }
   return closeness_;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Light_Sensor::Reset() {
   closeness_ = false;
} /* Reset */



NAMESPACE_END(csci3081);
