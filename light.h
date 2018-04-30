/**
 * @file base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

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
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a immobile base within the Arena.
 *
 * Base can enhance a Robot. If a Robot touches the Base, it becomes
 * a super robot.
 *
 * Base have the capability of updating their own position when asked, and
 * also track their own velocity and heading. They have a touch sensor for
 * responding to collision events which is activated/deactivated on collision
 * events.
 *
 */
class Light : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   *
   * @param params A base_params passed down from main.cc for the
   * initialization of the Base.
   */
  Light();

  /**
   * @brief Reset the Base using the initialization parameters received
   * by the constructor.
   */
  void Reset() override;

  std::string get_name() const override {
    return "Light " + std::to_string(get_id());
  }

  void TimestepUpdate(unsigned int dt) override;

  void HandleCollision(EntityType object_type, ArenaEntity *
    object = NULL) override;

 private:
  MotionHandlerObstacle motion_handler_;
  MotionBehaviorDifferential motion_behavior_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BASE_H_
