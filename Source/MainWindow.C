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

#include <MyPageGenerator/MainWindow.H>

#include <MyPageGenerator/NodeEditor/Widget.H>
#include <MyPageGenerator/Constants.H>

namespace gccore {
namespace my_page_generator {
MainWindow::MainWindow(QWidget* const parent) : QMainWindow(parent) {
  generateView();
}

QPointer<QHBoxLayout> MainWindow::getLayout() const {
  assert(centeral_widget_ != nullptr);
  assert(centeral_widget_->layout() != nullptr);
  return qobject_cast<QHBoxLayout*>(centeral_widget_->layout());
}

void MainWindow::generateView() {
  generateLayout();
  generateCenteralWidget();
  generateNodeEditor();
}
void MainWindow::generateCenteralWidget() {
  centeral_widget_ = new QWidget;
  QHBoxLayout* const layout = new QHBoxLayout;

  layout->setMargin(0);
  centeral_widget_->setLayout(layout);
  setCentralWidget(centeral_widget_);
}
void MainWindow::generateLayout() { setWindowTitle(constants::kWindowTitle); }
void MainWindow::generateNodeEditor() {
  node_editor_widget_ = new node_editor::Widget;
  getLayout()->addWidget(node_editor_widget_);
}
}  // namespace my_page_generator
}  // namespace gccore
