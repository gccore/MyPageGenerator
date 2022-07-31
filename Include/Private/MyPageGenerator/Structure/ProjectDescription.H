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

#ifndef MYPAGEGENERATOR_PRIVATE_STRUCTURE_PROJECTDESCRIPTION_H
#define MYPAGEGENERATOR_PRIVATE_STRUCTURE_PROJECTDESCRIPTION_H

#include <QtCore/QPointer>
#include <QtCore/QString>
#include <QtCore/QUuid>
#include <QtCore/QMap>

namespace gccore {
namespace my_page_generator {
class ProjectSubWindow;
}  // namespace my_page_generator
}  // namespace gccore

namespace gccore {
namespace my_page_generator {
namespace structures {
struct ProjectDescription {
  using Map = QMap<QUuid, ProjectDescription>;

  QPointer<ProjectSubWindow> window;
  QString root_directory;
};
}  // namespace structures
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_STRUCTURE_PROJECTDESCRIPTION_H
