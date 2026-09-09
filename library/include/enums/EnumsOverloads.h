//
// Created by azex on 9/9/26.
//

#ifndef MEDICALCLINIC_ENUMSOVERLOADS_H
#define MEDICALCLINIC_ENUMSOVERLOADS_H

#include <vector>
#include <type_traits>

namespace MedicalClinic
{
    enum class Status;
    enum class Equipment;
    enum class Specialisation;
    enum class Title;

    template <typename T>
    inline constexpr bool is_my_enum_v =
        std::is_same_v<T, Status> ||
        std::is_same_v<T, Equipment> ||
        std::is_same_v<T, Specialisation> ||
        std::is_same_v<T, Title>;

    template <typename T, std::enable_if_t<is_my_enum_v<T>, int> = 1>
    std::ostream& operator<<(std::ostream& os, const T& eq) {
        return os << toString(eq);
    }

    template <typename T, std::enable_if_t<is_my_enum_v<T>, int> = 1>
    std::ostream& operator==(std::ostream& os, const T& eq) {
        return os << toString(eq);
    }

    template <typename T, std::enable_if_t<is_my_enum_v<T>, int> = 1>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
    {
        for (const T& Spec : vec)
        {
            if (vec[vec.size() - 1] != Spec)
            {
                os << toString(Spec) + ", ";
            }
            else os << toString(Spec) + ".";
        };
        return os;
    };
};

#endif //MEDICALCLINIC_ENUMSOVERLOADS_H
