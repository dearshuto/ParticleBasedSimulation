PROJECT(RayTracer)

add_executable(povray_example povray_example.cpp)
target_link_libraries( povray_example
	particle_based_simulation
	BulletDynamics
	BulletCollision
	LinearMath
)

add_executable(profiling_example profiling_example.cpp)
target_link_libraries( profiling_example
	particle_based_simulation
	BulletDynamics
	BulletCollision
	LinearMath
)

# メッシュ操作
add_executable(mesh_example mesh_example.cpp)
target_link_libraries( mesh_example
	particle_based_simulation
	BulletDynamics
	BulletCollision
	LinearMath
	ConvexDecomposition
)
