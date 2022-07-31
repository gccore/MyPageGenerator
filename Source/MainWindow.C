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

#include <MyPageGenerator/ProjectSubWindow.H>
#include <MyPageGenerator/Constants.H>

#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>

namespace gccore {
namespace my_page_generator {
MainWindow::MainWindow(QWidget* const parent) : QMainWindow(parent) {
  generateView();
}

void MainWindow::generateView() {
  generateLayout();
  generateCenteralWidget();
  generateMenuBar();
  generateFileMenu();
}
void MainWindow::generateCenteralWidget() {
  centeral_widget_ = new QMdiArea;
  setCentralWidget(centeral_widget_);
}
void MainWindow::generateLayout() { setWindowTitle(constants::kWindowTitle); }
void MainWindow::generateMenuBar() {
  QMenuBar* const menu_bar = new QMenuBar;
  this->QMainWindow::setMenuBar(menu_bar);
}
void MainWindow::generateFileMenu() {
  assert(this->QMainWindow::menuBar() != nullptr);

  QAction* const new_project_action = new QAction;
  new_project_action->setText("&New");
  connect(new_project_action, &QAction::triggered, this,
          &MainWindow::onNewProjectClicked);

  QMenu* const file_menu = new QMenu;
  file_menu->setTitle("File");
  file_menu->addAction(new_project_action);

  this->QMainWindow::menuBar()->addMenu(file_menu);
}

void MainWindow::onNewProjectClicked() {
  assert(centeral_widget_ != nullptr);

  ProjectSubWindow* const project_sub_window = new ProjectSubWindow;
  centeral_widget_->addSubWindow(project_sub_window);
  project_sub_window->show();

  QString const& file = QFileDialog::getExistingDirectory(
      this, "Project Directory", qApp->applicationDirPath());

  if (!file.isEmpty()) {
    structures::ProjectDescription new_project;
    new_project.root_directory = file;
    new_project.window = project_sub_window;

    projects_map_[project_sub_window->projectId()] = new_project;
  } else {
    centeral_widget_->closeActiveSubWindow();
  }
}
}  // namespace my_page_generator
}  // namespace gccore
