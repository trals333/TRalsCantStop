#ifndef ENUMS_HPP
#define ENUMS_HPP

#include "tools.hpp"

//Enumerated class type for colors a player can select
enum class ECcolor {WHITE, ORANGE, YELLOW, GREEN, BLUE};
extern const char* ECcolorArr[];

enum class EState {AVAILABLE, PENDING, CAPTURED};
extern const string EStateStrings[];


#endif //ENUMS_HPP