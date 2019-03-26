cmake_minimum_required (VERSION 2.8.12)
project(soundLayer)

set(openAL_SDK "openal_sdk_path" CACHE PATH "choose openAL_SDK")
set(libogg "libogg_path" CACHE PATH "choose ogg_path")
set(libvorbis "libvorbis_path" CACHE PATH "choose vorbis_path")

# specify which version you need
find_package(OGRE 1.11 REQUIRED)



# the search paths
include_directories(${OGRE_INCLUDE_DIRS}
                    ${OGRE_INCLUDE_DIRS}/Bites
                    ${OGRE_INCLUDE_DIRS}/Plugins/OggSound
		    ${openAL_SDK}/include
                    ${libogg}/include
                    ${libvorbis}/include)
link_directories(${OGRE_LIBRARY_DIRS}
		 ${openAL_SDK}/libs/Win64
                 ${openAL_SDK}/libs/Win64/EFX-Util_MT
		 ${libogg}/lib
                 ${libvorbis}/lib)

set(LINK_LIBS OGRE/Plugin_OggSound EFX-Util.lib OpenAL32.lib ogg.lib vorbis.lib vorbisfile.lib)



option(BUILD_EXAMPLE "build example app" ON)
if(BUILD_EXAMPLE)
add_executable(soundExample demo.cpp)
target_link_libraries(soundExample PUBLIC ${OGRE_LIBRARIES} ${LINK_LIBS})
endif()


include_directories(${CMAKE_SOURCE_DIR})
add_library(soundLayerlib soundlayer.cpp)
target_link_libraries(soundLayerlib PUBLIC ${OGRE_LIBRARIES} ${LINK_LIBS})




find_package(SWIG 3.0.8)
find_package(PythonInterp)
find_package(PythonLibs)

if(NOT PYTHONLIBS_FOUND OR NOT SWIG_FOUND)
    return()
endif()

include(${SWIG_USE_FILE})
include_directories(${PYTHON_INCLUDE_PATH})

set(CMAKE_SWIG_FLAGS -w401,314 -builtin -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS)

set_source_files_properties(${CMAKE_SOURCE_DIR}/soundlayer.i PROPERTIES CPLUSPLUS ON)

if(MSVC)
	add_definitions(/wd4101 /wd4102)
else()
    add_definitions(-Wno-cast-qual -Wno-shadow -Wno-maybe-uninitialized -Wno-unused-label -Wno-unused-but-set-variable -Wno-missing-declarations)
endif()

swig_add_module(soundlayer python ${CMAKE_SOURCE_DIR}/soundlayer.i ${CMAKE_SOURCE_DIR}/soundlayer.cpp)
swig_link_libraries(soundlayer soundLayerlib OgreMain OgreBites ${PYTHON_LIBRARIES})
set_target_properties(${SWIG_MODULE_soundlayer_REAL_NAME} PROPERTIES DEBUG_POSTFIX "")

# install
set(PYTHON_SITE_PACKAGES lib/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/dist-packages/)
install(TARGETS ${SWIG_MODULE_soundlayer_REAL_NAME} LIBRARY DESTINATION ${PYTHON_SITE_PACKAGES})
install(FILES ${PROJECT_BINARY_DIR}/soundlayer.py DESTINATION ${PYTHON_SITE_PACKAGES})



