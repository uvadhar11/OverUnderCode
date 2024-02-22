#include "vex.h"

// set the physical distances for odometry tracking wheels
void Odom::set_physical_distances(float ForwardTracker_center_distance, float SidewaysTracker_center_distance)
{
  this->ForwardTracker_center_distance = ForwardTracker_center_distance;
  this->SidewaysTracker_center_distance = SidewaysTracker_center_distance;
}

// set the positions for robot's odometry
void Odom::set_position(float X_position, float Y_position, float orientation_deg, float ForwardTracker_position, float SidewaysTracker_position)
{
  this->ForwardTracker_position = ForwardTracker_position;
  this->SideWaysTracker_position = SidewaysTracker_position;
  this->X_position = X_position;
  this->Y_position = Y_position;
  this->orientation_deg = orientation_deg;
}

// updating robot position using odometry algorithm
// REMEMBER: this algorithm calculates the global orientation and position of your robot on the field at any given time. We still need our drive to point and turn to point algorithms using this information to actually move/account for changes with the robot.
void Odom::update_position(float ForwardTracker_position, float SidewaysTracker_position, float orientation_deg)
{
  // IMPORTANT NOTE: this-> always refers to the old version of the variable, so subtracting this->x from x gives delta x.

  // getting change in forward and sideways tracker postitions
  float Forward_delta = ForwardTracker_position - this->ForwardTracker_position;
  float Sideways_delta = SidewaysTracker_position - this->SideWaysTracker_position;

  // updating forward and sideways tracker positions (this-> refers to prev so we are updating the prev values)
  this->ForwardTracker_position = ForwardTracker_position;
  this->SideWaysTracker_position = SidewaysTracker_position;

  // converting orientation from degrees to radians for the orientation and prev orientation - STORING THESE DEG VALUES CONVERTED INTO RADIANS IN THESE VARIABLES, THE READINGS ARE STILL KEPT IN DEGREES
  // (assuming inertial sensor is using degrees and it is the orientation_deg value we are converting)
  float orientation_rad = to_rad(orientation_deg);
  float prev_orientation_rad = to_rad(this->orientation_deg);

  // calculating change in orientation in radians
  float orientation_delta_rad = orientation_rad - prev_orientation_rad;

  // updating prev orientation deg
  this->orientation_deg = orientation_deg;

  // declaraing local x and y position variables
  float local_X_position;
  float local_Y_position;

  // All of the following lines are pretty well documented in 5225A's Into to Position Tracking
  // Document at http://thepilons.ca/wp-content/uploads/2018/10/Tracking.pdf

  // if the orientation change is 0, then we are moving straight forward or backward, so we can use the simplified equations
  if (orientation_delta_rad == 0)
  {
    local_X_position = Sideways_delta;
    local_Y_position = Forward_delta;
  }
  // if the orientation change is not 0, then we are moving in an arc, so we have to use the more complex equations
  else
  {
    // for these calculations see position vector of robot on my calculation paper.
    // for these formulas: theta = change in orientation angle

    // distance x coord: 2 * sin (theta/2) * ((change in left tracking wheel / theta) + sideways tracking wheel distance - constant value)
    local_X_position = (2 * sin(orientation_delta_rad / 2)) * ((Sideways_delta / orientation_delta_rad) + SidewaysTracker_center_distance);

    // distance y coord: 2 * sin (theta/2) * ((change in right tracking wheel / theta) + forward tracking wheel distance - constant value)
    local_Y_position = (2 * sin(orientation_delta_rad / 2)) * ((Forward_delta / orientation_delta_rad) + ForwardTracker_center_distance);
  }

  // declaring local polar angle and length variables
  float local_polar_angle;
  float local_polar_length;

  // if the local x and y position are both 0, then we are not moving, so we don't want to calculate the polar angle and length
  if (local_X_position == 0 && local_Y_position == 0)
  {
    local_polar_angle = 0;
    local_polar_length = 0;
  }

  // if we did move, then we want to calculate the polar angle and length
  else
  {
    // converting x, y to polar coordinates (gets theta)
    local_polar_angle = atan2(local_Y_position, local_X_position);
    // calculating polar length (gets r) - its essentially pythagorean theorem
    local_polar_length = sqrt(pow(local_X_position, 2) + pow(local_Y_position, 2));
  }

  // updating global polar angle - since the global orientation is offset by previous orientation + change in orientation/2, we need to subtract this from our local polar angle in order to get the global orientation (See pilons document, step 9, also explained near Equation 6)
  float global_polar_angle = local_polar_angle - prev_orientation_rad - (orientation_delta_rad / 2);

  // calculating global offset (we converted to polar in the else statement step above and now we convert back to cartesian coordinates in order to get the offset)- see step 10 on pilons document
  // calculate change in x position
  float X_position_delta = local_polar_length * cos(global_polar_angle);
  // calculate change in y position
  float Y_position_delta = local_polar_length * sin(global_polar_angle);

  // update x and y position by adding the change in x and y from this iteration
  X_position += X_position_delta;
  Y_position += Y_position_delta;
}