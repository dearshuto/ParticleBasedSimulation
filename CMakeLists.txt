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

# インクルードフォルダを相対パスの検索対象に設定する
IF(WIN32)
add_definitions("/I${CMAKE_SOURCE_DIR}/include")
ELSE()
add_definitions("-I ${CMAKE_SOURCE_DIR}/include")
ENDIF()

## プロジェクトに含むソースコードのトラッキング
# includeフォルダとsrcフォルダにあるファイルのみを対象にする
FILE(GLOB_RECURSE ALL_FILES
	RELATIVE ${CMAKE_SOURCE_DIR}
 	include/*.hpp src/*.cpp)

## ディレクトリ構成を保持したままビルドシステムを構築するマクロ
foreach(FILE ${ALL_FILES})
  get_filename_component(PARENT_DIR "${FILE}" PATH)
  # skip src or include and changes /'s to \\'s
  string(REGEX REPLACE "(\\./)?(src|include)/?" "" GROUP "${PARENT_DIR}")
  string(REPLACE "/" "\\" GROUP "${GROUP}")

  # group into "Source Files" and "Header Files"
  if ("${FILE}" MATCHES ".*\\.cpp")
    set(GROUP "Source Files\\${GROUP}")
  elseif("${FILE}" MATCHES ".*\\.h")
    set(GROUP "Header Files\\${GROUP}")
  endif()

  source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_library(particle_based_simulation STATIC
	${ALL_FILES}
)

# ここからC++11を有効にする
add_definitions("-Wall -std=c++11")
add_subdirectory(example)
