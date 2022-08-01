/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * @gccore
 * g1999raemzani@gmail.com
 */

#ifndef MYPAGEGENERATOR_UTILITY_OPTIONAL_H
#define MYPAGEGENERATOR_UTILITY_OPTIONAL_H

#include <tl/optional.hpp>

namespace gccore {
namespace my_page_generator {
namespace utilities {
namespace core {
template <typename Type>
using Optional = tl::optional<Type>;
static tl::nullopt_t constexpr kNullOptional = tl::nullopt;
}  // namespace core
}  // namespace utilities
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_UTILITY_OPTIONAL_H
