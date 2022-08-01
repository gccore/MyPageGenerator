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

#ifndef MYPAGEGENERATOR_PRIVATE_UTILITY_FILE_H
#define MYPAGEGENERATOR_PRIVATE_UTILITY_FILE_H

#include <QtCore/QString>
#include <QtCore/QFile>

namespace gccore {
namespace my_page_generator {
namespace utilities {
class File {
 public:
  explicit File(QString const& file);

  void setFileName(QString const& new_file);
  QString fileName() const;

  bool isEmpty() const;

  void write(QString const& content);
  QString readAll();

 private:
  void openFile();
  void createPath();

  QString file_name_;
  QFile file_;
};
}  // namespace utilities
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_UTILITY_FILE_H
