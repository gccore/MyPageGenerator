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

#ifndef MYPAGEGENERATOR_PRIVATE_UTILITY_MARKDOWNCONVERTOR_H
#define MYPAGEGENERATOR_PRIVATE_UTILITY_MARKDOWNCONVERTOR_H

#include <QtCore/QString>

namespace gccore {
namespace my_page_generator {
namespace utilities {
namespace core {
class MarkdownConvertor {
 public:
  enum ExportKinds { EK_Html };

  explicit MarkdownConvertor(QString const& markdown);

  QString exportTo(ExportKinds const mode) const;
  QString exportToHtml() const;

 private:
  QString markdown_;
};
}  // namespace core
}  // namespace utilities
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_UTILITY_MARKDOWNCONVERTOR_H
