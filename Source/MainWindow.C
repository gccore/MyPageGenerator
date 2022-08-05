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
#include <MyPageGenerator/ProjectSubWindow.H>
#include <MyPageGenerator/Utility/CommonCoreUtilities.H>

#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>

#include <QtCore/QDataStream>
#include <QtCore/QStringList>

namespace gccore {
namespace my_page_generator {
MainWindow::MainWindow(QWidget* const parent) : QMainWindow(parent) {
  generateView();
  loadSettings();
}
MainWindow::~MainWindow() { saveSettings(); }

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
QPointer<QAction> MainWindow::CreateEmptyAction() {
  QPointer<QAction> action = new QAction;
  action->setText("[ EMPTY ]");
  action->setEnabled(false);
  return action;
}
QPointer<QMenu> MainWindow::CreateFileRecentMenu() {
  QPointer<QMenu> menu = new QMenu;
  menu->setTitle("Recent Projects:");
  menu->addAction(MainWindow::CreateEmptyAction());
  return menu;
}
QPointer<QAction>
MainWindow::createRecentProjectAction(QString const& project_path) {
  QPointer<QAction> action = new QAction;
  action->setText(project_path);
  connect(action, &QAction::triggered, this,
          [this, project_path] { onRecentProjectClicked(project_path); });
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

  recent_projects_menu_ = CreateFileRecentMenu();
  file_menu->addSeparator();
  file_menu->addMenu(recent_projects_menu_);

  this->QMainWindow::menuBar()->addMenu(file_menu);
}

QSharedPointer<QSettings> MainWindow::CreateQSettings() {
  QSharedPointer<QSettings> settings;
  settings.reset(
      new QSettings(utilities::core::JoinPath(qApp->applicationDirPath(),
                                              constants::kSettingsFileName),
                    QSettings::Format::IniFormat));
  return settings;
}
void MainWindow::saveSettings() const {
  QSharedPointer<QSettings> settings = CreateQSettings();
  saveSettingsRecentProjects(settings.get());
}
void MainWindow::saveSettingsRecentProjects(
    QPointer<QSettings> const& settings) const {
  assert(settings != nullptr);
  assert(recent_projects_menu_ != nullptr);

  QStringList list;
  for (QAction const* const action : recent_projects_menu_->actions()) {
    if (action->text() != constants::kEmptyActionText) {
      list.push_back(action->text());
    }
  }
  settings->setValue(constants::settings::kRecentProjects, list);
}

void MainWindow::loadSettings() {
  QSharedPointer<QSettings> settings = CreateQSettings();
  loadSettingsRecentProjects(settings.get());
}
void MainWindow::loadSettingsRecentProjects(
    QPointer<QSettings> const& settings) {
  assert(settings != nullptr);

  QStringList const list =
      settings->value(constants::settings::kRecentProjects).toStringList();
  for (QString const& item : list) {
    addProjectToRecentMenu(item);
  }
}

utilities::core::Optional<QString>
MainWindow::GetExistingDirectoryPath(QWidget* const parent) {
  QString const directory = QFileDialog::getExistingDirectory(
      parent, "Project Directory", qApp->applicationDirPath());
  return directory.isEmpty() ? utilities::core::kNullOptional
                             : utilities::core::Optional<QString>(directory);
}
utilities::core::Optional<QString>
MainWindow::GetExistingProjectFile(QWidget* const parent) {
  QString const file = QFileDialog::getOpenFileName(
      parent, "Project File", qApp->applicationDirPath(),
      "Project File (*.MyPageGenerator.GCCORE)");
  return file.isEmpty() ? utilities::core::kNullOptional
                        : utilities::core::Optional<QString>(file);
}

structures::ProjectDescription
MainWindow::createProjectWindow(QString const& directory_path) {
  structures::ProjectDescription project_description;
  project_description.root_directory = directory_path;
  project_description.window = new ProjectSubWindow;
  project_description.window->setProjectDirectory(directory_path);
  connect(project_description.window, &ProjectSubWindow::saveMe, this,
          std::bind(&MainWindow::onProjectSaveMeClicked, this,
                    project_description.window->projectId()));
  return project_description;
}
structures::ProjectDescription
MainWindow::addProjectWindow(QString const& directory_path) {
  structures::ProjectDescription project_description =
      createProjectWindow(directory_path);
  centeral_widget_->addSubWindow(project_description.window)->showMinimized();
  projects_map_[project_description.window->projectId()] = project_description;
  return project_description;
}

void MainWindow::ShrinkActionsToFit(std::int32_t const upper,
                                    QPointer<QMenu> const& menu) {
  assert(menu != nullptr);
  for (std::int32_t counter = menu->actions().size(); counter >= upper;
       counter = menu->actions().size()) {
    menu->removeAction(menu->actions()[counter]);
  }
}
void MainWindow::removeEmptyActionFrom(QPointer<QMenu> const& menu) const {
  assert(menu != nullptr);

  QList<QAction*> const actions = menu->actions();
  if (actions.size() == 1 &&
      actions.first()->text() == constants::kEmptyActionText) {
    menu->removeAction(actions.first());
  }
}
void MainWindow::addProjectToRecentMenu(QString const& project_path) {
  assert(recent_projects_menu_ != nullptr);
  MainWindow::ShrinkActionsToFit(constants::kMaximumRecentProjects,
                                 recent_projects_menu_);
  removeEmptyActionFrom(recent_projects_menu_);
  recent_projects_menu_->addAction(createRecentProjectAction(project_path));
}
void MainWindow::openProject(QString const& project_path) {
  if (QFileInfo(project_path).exists()) {
    structures::ProjectDescription const project =
        addProjectWindow(QFileInfo(project_path).dir().path());

    QFile project_file(project_path);
    project_file.open(QIODevice::ReadOnly);
    assert(project_file.isOpen());
    QDataStream file_deserializer(&project_file);
    project.window->deserialize(file_deserializer);
  } else {
    QMessageBox::critical(this, "Error",
                          "File: " + project_path + " deosn't exists");
  }
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
    addProjectToRecentMenu(file_path.value());
    openProject(file_path.value());
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
void MainWindow::onRecentProjectClicked(QString const& project) {
  assert(!project.isEmpty());
  openProject(project);
}
} // namespace my_page_generator
} // namespace gccore
