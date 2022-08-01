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

#include <MyPageGenerator/Utility/File.H>

#include <QtCore/QByteArray>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>

namespace gccore {
namespace my_page_generator {
namespace utilities {
namespace core {
File::File(QString const& file) : file_name_(file) {}

void File::setFileName(QString const& file) { file_name_ = file; }
QString File::fileName() const { return file_name_; }

bool File::isEmpty() const { return file_name_.isEmpty(); }

void File::write(QString const& content) {
  createPath();
  openFile();
  file_.write(content.toUtf8());
}
QString File::readAll() {
  openFile();
  return file_.readAll();
}

void File::openFile() {
  assert(!file_name_.isEmpty());
  if (!file_.isOpen()) {
    file_.setFileName(file_name_);
    file_.open(QIODevice::ReadWrite);
    assert(file_.isOpen());
  }
}
void File::createPath() {
  QDir parent_directory = QFileInfo(file_name_).dir();
  if (!parent_directory.exists()) {
    bool const creating_parent_dir_result =
        parent_directory.mkpath(parent_directory.path());
    assert(creating_parent_dir_result);
  }
}
}  // namespace core
}  // namespace utilities
}  // namespace my_page_generator
}  // namespace gccore
