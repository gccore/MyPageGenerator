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

#include <MyPageGenerator/Constants.H>

namespace gccore {
namespace my_page_generator {
MainWindow::MainWindow(QWidget* const parent) : QMainWindow(parent) {
  generateView();
}

void MainWindow::generateView() {
  generateLayout();
  generateCenteralWidget();
}
void MainWindow::generateCenteralWidget() {
  centeral_widget_ = new QMdiArea;
  setCentralWidget(centeral_widget_);
}
void MainWindow::generateLayout() { setWindowTitle(constants::kWindowTitle); }
}  // namespace my_page_generator
}  // namespace gccore
