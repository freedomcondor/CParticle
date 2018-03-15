cmake_minimum_required(VERSION 3.5)

project(CVector)

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")  
	  
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")  
	MESSAGE(STATUS "current platform: Linux ")  
	#add_definitions(-Dlinux)

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")  
	MESSAGE(STATUS "current platform: Windows")  
	add_definitions(-Dwindows)
	SET(CMAKE_EXE_LINKER_FLAGS "/SAFESEH:NO")

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")  
	MESSAGE(STATUS "current platform: FreeBSD")  

ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")  
	MESSAGE(STATUS "current platform: Darwin(mac?)")  
	add_definitions(-Dmac)

ELSE ()  
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")  
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")  

#set(CMAKE_BUILD_TYPE Debug)
MESSAGE(STATUS "CMAKEFLAG = ${CMAKEFLAG}")  
IF (CMAKEFLAG)
	add_definitions(-DAAA)
	MESSAGE(STATUS "AAAisset")  
ENDIF (CMAKEFLAG)

add_executable(cVector src/main.cpp
					src/Quaternion.cpp
					src/Vector3.cpp
			  )
