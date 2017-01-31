PROJECT(ParticleBasedSimulation)
cmake_minimum_required(VERSION 2.7)

## 実行ファイルの出力ディレクトリの設定
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

## ライブラリファイルの出力ディレクトリの設定
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)

## Bullet Physics
include_directories(${CMAKE_CURRENT_LIST_DIR}/vendor/bullet3/src)
include_directories(${CMAKE_CURRENT_LIST_DIR}/vendor/bullet3/Extras)
add_subdirectory(vendor/bullet3)

## eigen
include_directories(${CMAKE_CURRENT_LIST_DIR}/vendor/Eigen)


## プロジェクトに含むソースコードのトラッキング
SET(Include_Folder ${CMAKE_SOURCE_DIR}/include/particle_based_simulation/)
SET(Src_Folder ${CMAKE_SOURCE_DIR}/src/)

MESSAGE(Include_Folder)
MESSAGE(Src_Folder)

FILE(GLOB_RECURSE bullet_algorithm_files
	${Include_Folder}/simulation/bullet_algorithm/*.hpp
	${Src_Folder}/simulation/bullet_algorithm/*.cpp
)

FILE(GLOB_RECURSE simulation_files
	${Include_Folder}/simulation/particle_world.hpp
	${Src_Folder}/simulation/particle_world.cpp
	${Include_Folder}/simulation/overlap_particle_world.hpp
	${Src_Folder}/simulation/overlap_particle_world.cpp
	${Include_Folder}/simulation/general_particle_world.hpp
)

FILE(GLOB_RECURSE particle_files
	${Include_Folder}/simulation/collision_object/particle/*.hpp
	${Src_Folder}/simulation/collision_object/particle/*.cpp
)

FILE(GLOB_RECURSE general_algorithm_files
	${Include_Folder}/simulation/algorithm/general/*.hpp
	${Src_Folder}/simulation/algorithm/general/*.cpp
)

FILE(GLOB_RECURSE fine_particles_algorithm_files
	${Include_Folder}/simulation/algorithm/fine_particles/*.hpp
	${Src_Folder}/simulation/algorithm/fine_particles/*.cpp
)

FILE(GLOB_RECURSE collision_object_files
	${Include_Folder}/simulation/collision_object/collision_object.hpp
	${Src_Folder}/simulation/collision_object/collision_object.cpp
)

FILE(GLOB_RECURSE mesh_files
	${Include_Folder}/simulation/collision_object/mesh/*.hpp
	${Src_Folder}/simulation/collision_object/mesh/*.cpp
)

FILE(GLOB_RECURSE primitive_files
	${Include_Folder}/simulation/collision_object/primitive/*.hpp
	${Src_Folder}/simulation/collision_object/primitive/*.cpp
)


FILE(GLOB_RECURSE shape_2d_files
	${Include_Folder}/shape_2d/*.hpp
	${Src_Folder}/shape_2d/*.cpp
)

## Additional
FILE(GLOB_RECURSE povray_files
	${Include_Folder}/additional/povray/povray_output.hpp
	${Src_Folder}/additional/povray/povray_output.cpp
)

FILE(GLOB_RECURSE profile_files
	${Include_Folder}/additional/profile/*.hpp
	${Src_Folder}/additional/profile/*.cpp
)

FILE(GLOB_RECURSE additional_procedure_files
	${Include_Folder}/additional_procedure.hpp
	${Src_Folder}/additional/additional_procedure.cpp
	${Include_Folder}/particle_information_profiler.hpp
	${Src_Folder}/additional/particle_information_profiler.cpp
	${Include_Folder}/additional/rheorogy_simulator_profiler.hpp
	${Src_Folder}/additional/rheorogy_simulator_profiler.cpp
	${povray_files}
	${profile_files}
)

## IDEの表示における階層の設定
SOURCE_GROUP(simulation\\ FILES ${simulation_files})
SOURCE_GROUP(simulation\\algorithm\\general FILES ${general_algorithm_files})
SOURCE_GROUP(simulation\\algorithm\\fine_particles FILES ${fine_particles_algorithm_files})
SOURCE_GROUP(simulation\\collision_object FILES ${collision_object_files})
SOURCE_GROUP(simulation\\collision_object\\particle FILES ${particle_files})
SOURCE_GROUP(simulation\\collision_object\\mesh FILES ${mesh_files})
SOURCE_GROUP(simulation\\collision_object\\primitive FILES ${primitive_files})
SOURCE_GROUP(simulation\\bullet_algorithm FILES ${bullet_algorithm_files})
SOURCE_GROUP(additional\\ FILES ${additional_procedure_files})
SOURCE_GROUP(additional\\povray FILES ${povray_files})
SOURCE_GROUP(additional\\profile FILES ${profile_files})
SOURCE_GROUP(shape_2d FILES ${shape_2d_files})


# インクルードフォルダを相対パスの検索対象に設定する
IF(WIN32)
add_definitions("/I${CMAKE_SOURCE_DIR}/include")
ELSE()
add_definitions("-I ${CMAKE_SOURCE_DIR}/include")
ENDIF()

SET(algorithm_files
	${general_algorithm_files}
	${fine_particles_algorithm_files}
	${simulation_files}
)

add_library(particle_based_simulation STATIC
	${algorithm_files}
	${particle_files}
	${collision_object_files}
	${mesh_files}
	${profile_files}
	${primitive_files}
	${bullet_algorithm_files}
	${additional_procedure_files}
	${collision_dispatcher_files}
	${math_files}
	${particle_files}
	${world_files}
)


# ここからC++11を有効にする
add_definitions("-Wall -std=c++11")
add_subdirectory(example)
