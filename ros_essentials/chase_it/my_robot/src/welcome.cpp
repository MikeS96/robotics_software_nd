#include <gazebo/gazebo.hh>
#include <ros/ros.h>

namespace gazebo
{
  // Inherits from Gazebo WorldPlugin
  class WorldPluginProject : public WorldPlugin
  {
    public: WorldPluginProject() : WorldPlugin()
            {
            	ROS_INFO("Welcome to Mike's world!\n");
            }
            
    // Receives information from world file
    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
            {
            }
  };
  // Register plugin with the simulator
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginProject)
}
