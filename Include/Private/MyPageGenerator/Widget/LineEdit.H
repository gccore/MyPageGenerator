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

#ifndef MYPAGEGENERATOR_WIDGET_LINEEDIT_H
#define MYPAGEGENERATOR_WIDGET_LINEEDIT_H

#include <QtCore/QPointer>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>

namespace gccore {
namespace my_page_generator {
namespace widgets {
class LineEdit : public QWidget {
  Q_OBJECT

 public:
  using LayoutType = QHBoxLayout;

  explicit LineEdit(QWidget* const parent = nullptr);

  void setText(QString const& new_text);
  QString text() const;

  void setPlaceholderText(QString const& new_placeholder_text);
  QString placeholderText() const;

  void setLabelText(QString const& new_label_text);
  QString labelText() const;

  Q_SIGNAL void textChanged(QString const& text);

 private:
  QPointer<LayoutType> layout() const;

  void generateView();
  void generateLayout();
  void generateLabel();
  void generateLineEdit();

  QPointer<QLabel> label_;
  QPointer<QLineEdit> line_edit_;
};
}  // namespace widgets
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_WIDGET_LINEEDIT_H
