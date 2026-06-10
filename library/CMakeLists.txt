cmake_minimum_required(VERSION 3.4)
project(Library)
set(SOURCE_FILES
        include/typedefs.h
        include/managers/ManagerTemplate.h
        include/managers/LogicManager.h
        include/Exceptions.h
        src/enums/Specialisation.cpp
        src/enums/Equipment.cpp
        src/patient/Patient.cpp
        src/patient/Address.cpp
        src/Person.cpp
        src/personnel/Personnel.cpp
        src/personnel/Doctor.cpp
        src/personnel/Nurse.cpp
        src/rooms/Room.cpp
        src/rooms/RehabillitationRoom.cpp
        src/rooms/ConsultationRoom.cpp
        src/services/Service.cpp
        src/services/Consultation.cpp
        src/services/Rehabillitation.cpp
        src/Appointment.cpp
        src/enums/Specialisation.cpp
        src/repositories/PatientRepository.cpp
        src/repositories/PersonnelRepository.cpp
        src/repositories/AppointmentRepository.cpp
        src/repositories/RoomRepository.cpp
        src/repositories/ServiceRepository.cpp
        src/managers/RoomManager.cpp
        src/managers/AppointmentManager.cpp
        src/managers/ServiceManager.cpp
        src/managers/PatientManager.cpp
        src/managers/PersonnelManager.cpp
        src/managers/LogicManger.cpp

)# tu będą dodawan pliki zrodlowe
# Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})
target_include_directories(Library PUBLIC include)

enable_testing()
find_package (Boost 1.80.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/master.cpp
        test/PersonTest.cpp
        test/patient/AddressTest.cpp
        test/patient/PatientTest.cpp
        test/personnel/PersonnelTest.cpp
        test/personnel/DoctorTest.cpp
        test/personnel/NurseTest.cpp
        test/rooms/ConsultationRoomTest.cpp
        test/rooms/RehabillitationRoomTest.cpp
        test/rooms/RoomTest.cpp
        test/services/ServiceTest.cpp
        test/services/ConsultationTest.cpp
        test/services/RehabillitationTest.cpp
        test/AppointmentTest.cpp
        test/repositories/RepositoryTemplateTest.cpp
        test/repositories/PatientRepositoryTest.cpp
        test/repositories/PersonnelRepositoryTest.cpp
        test/repositories/RoomRepositoryTest.cpp
        test/repositories/ServiceRepositoryTest.cpp
        test/repositories/AppointmentRepositoryTest.cpp
        test/managers/ManagerTemplateTest.cpp
        test/managers/PatientManagerTest.cpp
        test/managers/RoomManagerTest.cpp
        test/managers/PersonnelManagerTest.cpp
        test/managers/AppointmentManagerTest.cpp
        test/managers/ServiceManagerTest.cpp
        test/managers/LogicManagerTest.cpp

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
