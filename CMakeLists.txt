cmake_minimum_required(VERSION 3.1.0)
project( Yams )

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED Widgets REQUIRED)

find_package( OpenCV REQUIRED )



set(HEADERS
    
)

set(SRCS
    
)

set(CLASS_HEADERS
    src/models/CDice.hpp
)

set(CLASS_SRCS
    src/models/CDice.cpp
)

set(QT_CLASS_HEADERS
    src/models/QPlayerGrid.hpp

    src/views/QGameWindow.hpp
    src/views/QCameraWidget.hpp
    src/views/QPlayerGridWidget.hpp
)

set(QT_CLASS_SRCS
    src/models/QPlayerGrid.cpp

    src/views/QGameWindow.cpp
    src/views/QCameraWidget.cpp
    src/views/QPlayerGridWidget.cpp
)

set(QT_VIEW
    src/views/QGameWindow.ui
    src/views/QCameraWidget.ui
    src/views/QPlayerGridWidget.ui
)

set(QT_RESSOURCES
    src/views/QGameWindow.qrc
)

add_executable( ${PROJECT_NAME} 
    ${HEADERS} ${SRCS} 
    ${CLASS_HEADERS} ${CLASS_SRCS} 
    ${QT_CLASS_HEADERS} ${QT_CLASS_SRCS} ${QT_VIEW} ${QT_RESSOURCES}  
    
    src/main.cpp 
)

if(WIN32) # Regarde si on est sous Windows
	if(MSVC) # Regarde si on utilise le compilateur de Visual Studio
		set_target_properties(${PROJECT_NAME} PROPERTIES
			WIN32_EXECUTABLE YES
			LINK_FLAGS "/ENTRY:mainCRTStartup"
		)
	elseif(CMAKE_COMPILER_IS_GNUCXX)
			# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Pas testé
	else()
		message(SEND_ERROR "Vous utilisez un compilateur non supporté ! (Pas MSVC ou GCC)")
	endif(MSVC)
elseif(APPLE)
	set_target_properties(${PROJECT_NAME} PROPERTIES
			MACOSX_BUNDLE YES
	)
elseif(UNIX)
	# Rien de requis
else()
	message(SEND_ERROR "Vous êtes sur une plate-forme non suportée ! (Not Win32, Mac OS X or Unix)")
endif(WIN32)

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
# target_link_libraries( ${PROJECT_NAME} ${QT_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} Qt5::Core )
target_link_libraries( ${PROJECT_NAME} Qt5::Widgets )

