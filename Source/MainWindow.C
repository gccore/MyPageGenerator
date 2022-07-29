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
#include <MyPageGenerator/Widget/PathInput.H>
#include <MyPageGenerator/Constants.H>

#include <QtWidgets/QLabel>

namespace gccore {
namespace my_page_generator {
MainWindow::MainWindow(QWidget* const parent) : QMainWindow(parent) {
  generateView();
}

QPointer<QVBoxLayout> MainWindow::layout() const {
  assert(centeral_widget_ != nullptr);
  assert(centeral_widget_->layout() != nullptr);
  return qobject_cast<QVBoxLayout*>(centeral_widget_->layout());
}

void MainWindow::generateView() {
  generateLayout();
  generateCenteralWidget();
  generateNodeEditor();
  generateRootDirectoryWidget();
  generateGenerateButtonWidget();
}
void MainWindow::generateCenteralWidget() {
  centeral_widget_ = new QWidget;
  QVBoxLayout* const layout = new QVBoxLayout;

  centeral_widget_->setLayout(layout);
  setCentralWidget(centeral_widget_);
}
void MainWindow::generateLayout() { setWindowTitle(constants::kWindowTitle); }
void MainWindow::generateNodeEditor() {
  node_editor_widget_ = new node_editor::Widget;
  layout()->addWidget(node_editor_widget_);
}
void MainWindow::generateRootDirectoryWidget() {
  root_directory_widget_ = new widgets::PathInput;
  layout()->addWidget(root_directory_widget_);
}
void MainWindow::generateGenerateButtonWidget() {
  generate_button_widget_ = new QToolButton;
  generate_button_widget_->setText("Generate");
  connect(generate_button_widget_, &QToolButton::clicked, this,
          &MainWindow::onGenerateButtonClicked);
  layout()->addWidget(generate_button_widget_);
}

void MainWindow::onGenerateButtonClicked() {
  assert(sender() != nullptr);
  assert(node_editor_widget_ != nullptr);
  assert(root_directory_widget_ != nullptr);

  node_editor_widget_->exportTo(node_editor::EK_HTML,
                                root_directory_widget_->path());
}
}  // namespace my_page_generator
}  // namespace gccore
