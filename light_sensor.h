/**
 * @file light_sensor.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */
 #ifndef SRC_LIGHT_SENSOR_H_
 #define SRC_LIGHT_SENSOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include <string>

 #include "src/pose.h"
 #include "src/arena_mobile_entity.h"
 #include "src/common.h"
 #include "src/entity_type.h"
 #include "src/motion_handler_obstacle.h"
 #include "src/motion_behavior_differential.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
 class Light_Sensor {
  public:
   /**
    * @brief Constructor.
    *
    * @param params A base_params passed down from main.cc for the
    * initialization of the Base.
    */

   /**
    * @brief Reset the Base using the initialization parameters received
    * by the constructor.
    */
   void Reset();
   bool proximity(double pose1, double pose2);

  private:
   bool closeness_{false};
 };

NAMESPACE_END(csci3081);

#endif
