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

#ifndef MYPAGEGENERATOR_PRIVATE_MYPAGEGENERATOR_MAINWINDOW_H
#define MYPAGEGENERATOR_PRIVATE_MYPAGEGENERATOR_MAINWINDOW_H

#include <QtCore/QPointer>
#include <QtCore/QObject>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
class Widget;
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore

namespace gccore {
namespace my_page_generator {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* const parent = nullptr);

 private:
  QPointer<QHBoxLayout> getLayout() const;

  void generateView();
  void generateCenteralWidget();
  void generateLayout();
  void generateNodeEditor();

  QPointer<QWidget> centeral_widget_;
  QPointer<node_editor::Widget> node_editor_widget_;
};
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_MYPAGEGENERATOR_MAINWINDOW_H