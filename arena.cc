/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <iostream>

#include "src/arena.h"
#include "src/arena_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params *const params)
    : x_dim_(params->x_dim),
      y_dim_(params->y_dim),
      factory_(new EntityFactory),
      entities_(),
      mobile_entities_(),
      game_status_(PAUSED) {
  for(int i=1;i<=10;i++) {AddRobot();};
  AddEntity(kBase, params->n_bases);
//  AddEntity(kObstacle, params->n_obstacles);
  AddEntity(kLight, params->n_lights);
}

Arena::~Arena() {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::AddRobot() {
  robot_ = dynamic_cast<Robot *>(factory_->CreateEntity(kRobot));
  entities_.push_back(robot_);
  mobile_entities_.push_back(robot_);
}

void Arena::AddEntity(EntityType type, int quantity) {
  for (int i = 0; i < quantity; i++) {
    if (type == kObstacle) {
      Obstacle* obstacle = dynamic_cast<Obstacle *>(
        factory_->CreateEntity(type));
      mobile_entities_.push_back(obstacle);
      entities_.push_back(obstacle);
    } else if (type == kLight) {
      Light* light = dynamic_cast<Light *>(
        factory_->CreateEntity(type));
      mobile_entities_.push_back(light);
      entities_.push_back(light);
    } else if (type == kRobot) {
      Robot* robot = dynamic_cast<Robot *>(
        factory_->CreateEntity(type));
      mobile_entities_.push_back(robot);
      entities_.push_back(robot);
    } else {
      entities_.push_back(factory_->CreateEntity(type));
    }
  }
}

void Arena::Reset() {
  game_status_ = PLAYING;
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

// controlls the simulation of the robot. Inherited by the controller.
void Arena::AdvanceTime(double dt) {
  if (!(dt > 0)) {
    return;
  }
  for (size_t i = 0; i < 1; ++i) {
    UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep() {
  /*
   * handles velocities of all current entities.
   *
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
    if(ent->get_type() == kBase) {
      posx_ = ent->get_pose().x;
      posx_ = ent->get_pose().y;
    }

  }

  /*
   * Check for win/loss
   */
  if (robot_->get_lives() == 0) {
    set_game_status(LOST);
  }
  if (robot_->num_bases_captured == N_BASES) {
    set_game_status(WON);
  }

  /* Checks and adjust the position of any entity (mobile) if it is colliding with the wall.
   */


  for (auto &ent1 : mobile_entities_) {
    EntityType wall = GetCollisionWall(ent1);
    if (kUndefined != wall) {
      AdjustWallOverlap(ent1, wall);
      ent1->HandleCollision(wall, NULL);
    }

    /* Checks and adjust the position of any entity (mobile) if it is colliding with the wall.
    */
    for (auto &ent2 : entities_) {
      if (ent2 == ent1) { continue; }
      if (IsColliding(ent1, ent2)) {
        if(ent1->get_type() == kRobot && ent2->get_type() == kLight) {
           if(ent1->get_id() < 6) {
           ent1->set_position(ent1->get_pose().x - 30, ent1->get_pose().y - 30);
          // std::cout << "fear" << std::endl;
         } else {
        //    std::cout << "explore" < std::endl;
            ent1->set_position(ent1->get_pose().x + 5, ent1->get_pose().y + 5);
            continue;
         }
       } else if (ent1->get_type() != kLight) {
        AdjustEntityOverlap(ent1, ent2);
        ent1->HandleCollision(ent2->get_type(), ent2);
      }
    }
  }
}
}//


// Check if the entity is colliding with a wall.
EntityType Arena::GetCollisionWall(ArenaMobileEntity *const ent) {
  if (ent->get_pose().x + ent->get_radius() >= x_dim_) {
    return kRightWall;  // at x = x_dim_
  } else if (ent->get_pose().x - ent->get_radius() <= 0) {
    return kLeftWall;  // at x = 0
  } else if (ent->get_pose().y + ent->get_radius() >= y_dim_) {
    return kBottomWall;  // at y = y_dim
  } else if (ent->get_pose().y - ent->get_radius() <= 0) {
    return kTopWall;  // at y = 0
  } else {
    return kUndefined;
  }
} /* GetCollisionWall() */

/* The entity type indicates which wall the entity is colliding with.
* This determines which way to move the entity to set it slightly off the wall. */
void Arena::AdjustWallOverlap(ArenaMobileEntity *const ent, EntityType object) {
  Pose entity_pos = ent->get_pose();
  switch (object) {
    case (kRightWall):  // at x = x_dim_
    ent->set_position(x_dim_-(ent->get_radius()+5), entity_pos.y);
    break;
    case (kLeftWall):  // at x = 0
    ent->set_position(ent->get_radius()+5, entity_pos.y);
    break;
    case (kTopWall):  // at y = 0
    ent->set_position(entity_pos.x, ent->get_radius()+5);
    break;
    case (kBottomWall):  // at y = y_dim_
    ent->set_position(entity_pos.x, y_dim_-(ent->get_radius()+5));
    break;
    default:
    {}
  }
}

/* Calculates the distance between the center points to determine overlap */
bool Arena::IsColliding (
  ArenaMobileEntity * const mobile_e,
  ArenaEntity * const other_e) {
    double delta_x = other_e->get_pose().x - mobile_e->get_pose().x;
    double delta_y = other_e->get_pose().y - mobile_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    return
    (distance_between <= (mobile_e->get_radius() + other_e->get_radius()));
}

/* This is called when it is known that the two entities overlap.
* We determine by how much they overlap then move the mobile entity to
* the edge of the other
*/
/*
*/
/*
 */
void Arena::AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
  ArenaEntity *const other_e) {
    double delta_x = other_e->get_pose().x - mobile_e->get_pose().x;
    double delta_y = other_e->get_pose().y - mobile_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    double distance_to_move =
      mobile_e->get_radius() + other_e->get_radius() - distance_between;
    double angle = atan(delta_y/delta_x);
    mobile_e->set_position(
      mobile_e->get_pose().x+cos(angle)*distance_to_move,
      mobile_e->get_pose().y+sin(angle)*distance_to_move);
}

// Accept communication from the controller. Dispatching as appropriate.
/**
  */
void Arena::AcceptCommand(Communication com) {
  switch (com) {
    case(kIncreaseSpeed):
      robot_->IncreaseSpeed();
      break;
    case(kDecreaseSpeed):
      //robot_->DecreaseSpeed();
      break;
    case(kTurnLeft):
    //  robot_->TurnLeft();
      break;
    case(kTurnRight):
    //  robot_->TurnRight();
      break;
    case(kPlay):
      game_status_ = PLAYING;
      break;
    case(kPause):
      game_status_ = PAUSED;
      break;
    case(kReset):
      Reset();
      break;
    case(kNewGame):
      Reset();
    case(kNone):
    default: break;
  }
} /* AcceptCommand */

NAMESPACE_END(csci3081);
