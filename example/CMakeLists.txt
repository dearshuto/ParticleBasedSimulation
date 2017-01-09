PROJECT(RayTracer)

add_executable(povray_example povray_example.cpp)
target_link_libraries( povray_example
	particle_based_simulation
	BulletDynamics
	BulletCollision
	LinearMath
)