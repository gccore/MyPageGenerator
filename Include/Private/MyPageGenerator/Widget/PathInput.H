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

#ifndef MYPAGEGENERATOR_PRIVATE_WIDGET_PATHINPUT_H
#define MYPAGEGENERATOR_PRIVATE_WIDGET_PATHINPUT_H

#include <QtCore/QPointer>
#include <QtCore/QObject>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>

namespace gccore {
namespace my_page_generator {
namespace widgets {
class PathInput : public QWidget {
  Q_OBJECT

 public:
  explicit PathInput(QWidget* const parent = nullptr);

  void setPath(QString const& new_path);
  QString path() const;

  void setPlaceholderText(QString const& new_placeholder_text);
  QString placeholderText() const;

  Q_SIGNAL void pathChanged(QString const& path);

 private:
  QPointer<QHBoxLayout> layout() const;

  void generateView();
  void generateLayout();
  void generateInputPathWidget();
  void generateBrowseButtonWidget();

  Q_SLOT void onBrowseButtonClicked();

  QPointer<QToolButton> browse_button_widget_;
  QPointer<QLineEdit> input_path_widget_;
};
}  // namespace widgets
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_WIDGET_PATHINPUT_H
