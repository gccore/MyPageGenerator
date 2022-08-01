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

#include <MyPageGenerator/Structure/ProjectDescription.H>
#include <MyPageGenerator/Utility/Optional.H>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QAction>

#include <QtCore/QPointer>
#include <QtCore/QObject>

namespace gccore {
namespace my_page_generator {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* const parent = nullptr);

 private:
  QPointer<QAction> createFileNewAction() const;
  QPointer<QAction> createFileOpenAction() const;

  void generateView();
  void generateCenteralWidget();
  void generateLayout();
  void generateMenuBar();
  void generateFileMenu();

  static utilities::Optional<QString> GetExistingDirectoryPath(
      QWidget* const parent = nullptr);
  static utilities::Optional<QString> GetExistingProjectFile(
      QWidget* const parent = nullptr);

  structures::ProjectDescription createProjectWindow(
      QString const& directory_path);
  structures::ProjectDescription addProjectWindow(
      QString const& directory_path);

  Q_SLOT void onNewProjectClicked();
  Q_SLOT void onOpenProjectClicked();
  Q_SLOT void onProjectSaveMeClicked(QUuid const& project_id);

  QPointer<QMdiArea> centeral_widget_;
  structures::ProjectDescription::Map projects_map_;
};
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_MYPAGEGENERATOR_MAINWINDOW_H
