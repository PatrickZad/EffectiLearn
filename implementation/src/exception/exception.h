#ifndef __IMPL_EXCEPTION_H
#define __IMPL_EXCEPTION_H
#include <exception>
namespace patrick{
    class OutOfIndexException:std::exception{};
    class CalculationInvalidException:std::exception{};
    class ParameterInvalidException:std::exception{};
}
#endif