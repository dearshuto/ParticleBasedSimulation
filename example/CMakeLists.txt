add_executable(fluid_example fluid_example.cpp)
target_link_libraries( fluid_example
	particle_based_simulation
	BulletDynamics
	BulletCollision
	LinearMath
)