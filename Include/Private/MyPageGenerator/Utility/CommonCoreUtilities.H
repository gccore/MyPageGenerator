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

#ifndef MYPAGEGENERATOR_UTILITIES_COMMONCOREUTILITIES_H
#define MYPAGEGENERATOR_UTILITIES_COMMONCOREUTILITIES_H

#include <QtCore/QString>
#include <QtCore/QUuid>
#include <QtCore/QDir>

namespace gccore {
namespace my_page_generator {
namespace utilities {
namespace core {
inline QString JoinPath(QString const& left, QString const& right) {
  return left + QDir::separator() + right;
}
inline QString GenerateUniqueObjectName() {
  QString name = QUuid::createUuid().toString();
  return "GCCORE" + name.remove('{').remove('}').remove('-');
}
}  // namespace core
}  // namespace utilities
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_UTILITIES_COMMONCOREUTILITIES_H
