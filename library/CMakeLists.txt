cmake_minimum_required(VERSION 3.10)
project(Library)

cmake_policy(SET CMP0167 NEW)

set(SOURCE_FILES
        include/typedefs.h

        src/enums/Specialisation.cpp
        include/enums/Specialisation.h

        src/enums/Equipment.cpp
        include/enums/Equipment.h

        src/enums/Status.cpp
        include/enums/Status.h

        src/enums/Title.cpp
        include/enums/Title.h

        src/Statusable.cpp
        include/Statusable.h

        src/Person.cpp
        include/Person.h

        src/patient/Address.cpp
        include/patient/Address.h

        src/patient/Patient.cpp
        include/patient/Patient.h

        src/personnel/Personnel.cpp
        include/personnel/Personnel.h

        src/personnel/Doctor.cpp
        include/personnel/Doctor.h

        src/personnel/Nurse.cpp
        include/personnel/Nurse.h

#        src/rooms/Room.cpp
#        src/rooms/RehabillitationRoom.cpp
#        src/rooms/ConsultationRoom.cpp
#        src/services/Service.cpp
#        src/services/Consultation.cpp
#        src/services/Rehabillitation.cpp
#        src/Appointment.cpp
#        src/enums/Specialisation.cpp
#        src/repositories/PatientRepository.cpp
#        src/repositories/PersonnelRepository.cpp
#        src/repositories/AppointmentRepository.cpp
#        src/repositories/RoomRepository.cpp
#        src/repositories/ServiceRepository.cpp
#        src/managers/RoomManager.cpp
#        src/managers/AppointmentManager.cpp
#        src/managers/ServiceManager.cpp
#        src/managers/PatientManager.cpp
#        src/managers/PersonnelManager.cpp
#        src/managers/LogicManger.cpp
#        src/menu/TerminalMenu.cpp
#        include/menu/TerminalMenu.h
        #        include/managers/ManagerTemplate.h
        #        include/managers/LogicManager.h
        #        include/Exceptions.h

)# tu będą dodawan pliki zrodlowe
# Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library STATIC ${SOURCE_FILES})
target_include_directories(Library PUBLIC include)

enable_testing()
find_package(Boost 1.90.0 COMPONENTS unit_test_framework REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/master.cpp
        test/enums/Enums.cpp
        test/PersonTest.cpp
        test/patient/AddressTest.cpp
        test/patient/PatientTest.cpp
        test/StatusableTest.cpp
        test/personnel/PersonnelTest.cpp
        test/personnel/DoctorTest.cpp
        test/personnel/NurseTest.cpp
#        test/rooms/ConsultationRoomTest.cpp
#        test/rooms/RehabillitationRoomTest.cpp
#        test/rooms/RoomTest.cpp
#        test/services/ServiceTest.cpp
#        test/services/ConsultationTest.cpp
#        test/services/RehabillitationTest.cpp
#        test/AppointmentTest.cpp
#        test/repositories/RepositoryTemplateTest.cpp
#        test/repositories/PatientRepositoryTest.cpp
#        test/repositories/PersonnelRepositoryTest.cpp
#        test/repositories/RoomRepositoryTest.cpp
#        test/repositories/ServiceRepositoryTest.cpp
#        test/repositories/AppointmentRepositoryTest.cpp
#        test/managers/ManagerTemplateTest.cpp
#        test/managers/PatientManagerTest.cpp
#        test/managers/RoomManagerTest.cpp
#        test/managers/PersonnelManagerTest.cpp
#        test/managers/AppointmentManagerTest.cpp
#        test/managers/ServiceManagerTest.cpp
#        test/managers/LogicManagerTest.cpp
) # tu w przyszłości będą dodawane pliki źródłowe testów

add_executable (LibraryTester ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (LibraryTester
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

#dodaj test LibraryTest. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest LibraryTester
        --report_level=detailed
        --log_level=all
        --color_output=yes
)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
