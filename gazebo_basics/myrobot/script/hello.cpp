#include <gazebo/gazebo.hh>

namespace gazebo
{
  // Inherits from Gazebo WorldPlugin
  class WorldPluginMyRobot : public WorldPlugin
  {
    public: WorldPluginMyRobot() : WorldPlugin()
            {
              printf("Hello World!\n");
            }
            
    // Receives information from world file
    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
            {
            }
  };
  // Register plugin with the simulator
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginMyRobot)
}
