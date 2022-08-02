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

#include <MyPageGenerator/Utility/CommonCoreUtilities.H>
#include <MyPageGenerator/ProjectSubWindow.H>
#include <MyPageGenerator/Constants.H>

#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>

#include <QtCore/QDataStream>

namespace gccore {
namespace my_page_generator {
MainWindow::MainWindow(QWidget* const parent) : QMainWindow(parent) {
  generateView();
}

QPointer<QAction> MainWindow::createFileNewAction() const {
  QPointer<QAction> action = new QAction;
  action->setText("&New");
  connect(action, &QAction::triggered, this, &MainWindow::onNewProjectClicked);
  return action;
}
QPointer<QAction> MainWindow::createFileOpenAction() const {
  QPointer<QAction> action = new QAction;
  action->setText("&Open");
  connect(action, &QAction::triggered, this, &MainWindow::onOpenProjectClicked);
  return action;
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

  QMenu* const file_menu = new QMenu;
  file_menu->setTitle("File");
  file_menu->addAction(createFileNewAction());
  file_menu->addAction(createFileOpenAction());

  this->QMainWindow::menuBar()->addMenu(file_menu);
}

utilities::core::Optional<QString> MainWindow::GetExistingDirectoryPath(
    QWidget* const parent) {
  QString const directory = QFileDialog::getExistingDirectory(
      parent, "Project Directory", qApp->applicationDirPath());
  return directory.isEmpty() ? utilities::core::kNullOptional
                             : utilities::core::Optional<QString>(directory);
}
utilities::core::Optional<QString> MainWindow::GetExistingProjectFile(
    QWidget* const parent) {
  QString const file = QFileDialog::getOpenFileName(
      parent, "Project File", qApp->applicationDirPath(),
      "Project File (*.MyPageGenerator.GCCORE)");
  return file.isEmpty() ? utilities::core::kNullOptional
                        : utilities::core::Optional<QString>(file);
}

structures::ProjectDescription MainWindow::createProjectWindow(
    QString const& directory_path) {
  structures::ProjectDescription project_description;
  project_description.root_directory = directory_path;
  project_description.window = new ProjectSubWindow;
  project_description.window->setProjectDirectory(directory_path);
  connect(project_description.window, &ProjectSubWindow::saveMe, this,
          std::bind(&MainWindow::onProjectSaveMeClicked, this,
                    project_description.window->projectId()));
  return project_description;
}
structures::ProjectDescription MainWindow::addProjectWindow(
    QString const& directory_path) {
  structures::ProjectDescription project_description =
      createProjectWindow(directory_path);
  centeral_widget_->addSubWindow(project_description.window)->showMinimized();
  projects_map_[project_description.window->projectId()] = project_description;
  return project_description;
}

void MainWindow::onNewProjectClicked() {
  assert(centeral_widget_ != nullptr);
  assert(sender() != nullptr);

  if (utilities::core::Optional<QString> const directory_path =
          GetExistingDirectoryPath())
    addProjectWindow(directory_path.value());
}
void MainWindow::onOpenProjectClicked() {
  assert(centeral_widget_ != nullptr);
  assert(sender() != nullptr);

  if (utilities::core::Optional<QString> const file_path =
          GetExistingProjectFile()) {
    structures::ProjectDescription project =
        addProjectWindow(QFileInfo(file_path.value()).dir().path());

    QFile project_file(file_path.value());
    project_file.open(QIODevice::ReadOnly);
    assert(project_file.isOpen());
    QDataStream file_deserializer(&project_file);
    project.window->deserialize(file_deserializer);
  }
}
void MainWindow::onProjectSaveMeClicked(QUuid const& uuid) {
  assert(projects_map_.contains(uuid));

  structures::ProjectDescription const& project_data = projects_map_[uuid];

  QFile config_file;
  config_file.setFileName(utilities::core::JoinPath(project_data.root_directory,
                                                    constants::kSaveFileName));
  config_file.open(QIODevice::WriteOnly);

  QDataStream config_stream(&config_file);
  project_data.window->serialize(config_stream);
  project_data.window->saveMdFiles();
}
}  // namespace my_page_generator
}  // namespace gccore
