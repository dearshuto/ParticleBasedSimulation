add_executable(povray_example povray_example.cpp)
target_link_libraries( povray_example
	particle_based_simulation
	BulletDynamics
	BulletCollision
	LinearMath
)

add_executable(grid_example grid_example.cpp)
target_link_libraries( grid_example
	particle_based_simulation
	BulletDynamics
	BulletCollision
	LinearMath
)

add_executable(emitter_example emitter_example.cpp)
target_link_libraries( emitter_example
	particle_based_simulation
	BulletDynamics
	BulletCollision
	LinearMath
)