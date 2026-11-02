#include "uincampus/version.hpp"

#include <print>

int main()
{

    std::println("UIN-Campus - systeme de gestion academique");
    std::println("Version {}", uin::version());
}
