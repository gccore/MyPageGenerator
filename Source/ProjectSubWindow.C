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

#include <MyPageGenerator/ProjectSubWindow.H>

#include <MyPageGenerator/Utility/CommonWidgetUtilities.H>
#include <MyPageGenerator/NodeEditor/Widget.H>

namespace gccore {
namespace my_page_generator {
ProjectSubWindow::ProjectSubWindow(QWidget* const parent) : QWidget(parent) {
  configure();
  generateView();
}

void ProjectSubWindow::setProjectId(QUuid const& new_project_id) {
  project_id_ = new_project_id;
}
QUuid ProjectSubWindow::projectId() const { return project_id_; }

void ProjectSubWindow::setProjectDirectory(
    QString const& new_project_directory) {
  project_directory_ = new_project_directory;
}
QString ProjectSubWindow::projectDirectory() const {
  return project_directory_;
}

QPointer<ProjectSubWindow::LayoutType> ProjectSubWindow::layout() const {
  assert(this->QWidget::layout() != nullptr);
  return qobject_cast<LayoutType*>(this->QWidget::layout());
}

void ProjectSubWindow::serialize(QDataStream& data_stream) const {
  assert(node_editor_widget_ != nullptr);
  node_editor_widget_->serialize(data_stream);
}
void ProjectSubWindow::deserialize(QDataStream& data_stream) {
  assert(node_editor_widget_ != nullptr);
  assert(!project_directory_.isEmpty());
  node_editor_widget_->deserialize(data_stream, project_directory_);
}
void ProjectSubWindow::saveMdFiles() {
  assert(node_editor_widget_ != nullptr);
  assert(!project_directory_.isEmpty());
  node_editor_widget_->saveNodesContentToFile(project_directory_);
}

void ProjectSubWindow::configure() { configureProjectId(); }
void ProjectSubWindow::configureProjectId() {
  project_id_ = QUuid::createUuid();
}

void ProjectSubWindow::generateView() {
  generateLayout();
  generateNodeEditor();
  generateGenerateButton();
  generateSaveMeButton();
  generateStatusButtonsSpacerItem();
}
void ProjectSubWindow::generateLayout() {
  LayoutType* const layout = new LayoutType;
  this->QWidget::setLayout(layout);

  status_button_layout_ = new QHBoxLayout;
  layout->addWidget(utilities::widgets::CreateHorizontalFrame());
  layout->addLayout(status_button_layout_);
}
void ProjectSubWindow::generateNodeEditor() {
  node_editor_widget_ = new node_editor::Widget;
  layout()->insertWidget(0, node_editor_widget_);
}
void ProjectSubWindow::generateGenerateButton() {
  assert(status_button_layout_ != nullptr);
  QToolButton* const generate_button = new QToolButton;
  generate_button->setText("Generate HTML");
  connect(generate_button, &QToolButton::clicked, this,
          &ProjectSubWindow::onGenerateButtonClicked);
  status_button_layout_->addWidget(generate_button);
}
void ProjectSubWindow::generateSaveMeButton() {
  assert(status_button_layout_ != nullptr);
  QToolButton* const save_me_button = new QToolButton;
  save_me_button->setText("Save Project");
  connect(save_me_button, &QToolButton::clicked, this,
          &ProjectSubWindow::saveMe);
  status_button_layout_->addWidget(save_me_button);
}
void ProjectSubWindow::generateStatusButtonsSpacerItem() {
  assert(status_button_layout_ != nullptr);
  status_button_layout_->addSpacerItem(
      utilities::widgets::CreateHorizontalSpacer());
}

void ProjectSubWindow::onGenerateButtonClicked() {
  assert(sender() != nullptr);
  assert(!project_directory_.isEmpty());
  node_editor_widget_->exportTo(node_editor::EK_HTML, project_directory_);
}
}  // namespace my_page_generator
}  // namespace gccore
