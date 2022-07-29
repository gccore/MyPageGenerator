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

#ifndef MYPAGEGENERATOR_PRIVATE_WIDGET_MDEDITOR_H
#define MYPAGEGENERATOR_PRIVATE_WIDGET_MDEDITOR_H

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>

namespace gccore {
namespace my_page_generator {
namespace widgets {
class MDEditor : public QWidget {
  Q_OBJECT

 public:
  explicit MDEditor(QWidget* const parent = nullptr);

  void setText(QString const& content);
  QString text() const;

 private:
  QPointer<QHBoxLayout> layout() const;

  void generateView();
  void generateLayout();
  void generateTextEditWidget();

  QPointer<QTextEdit> text_edit_;
};
}  // namespace widgets
}  // namespace my_page_generator
}  // namespace gccore

#endif  // GCCORE_MY_PAGE_GENERATOR_WIDGETS_MDEDITOR_H
