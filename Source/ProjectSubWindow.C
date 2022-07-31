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

QPointer<ProjectSubWindow::LayoutType> ProjectSubWindow::layout() const {
  assert(this->QWidget::layout() != nullptr);
  return qobject_cast<LayoutType*>(this->QWidget::layout());
}

void ProjectSubWindow::configure() { configureProjectId(); }
void ProjectSubWindow::configureProjectId() {
  project_id_ = QUuid::createUuid();
}

void ProjectSubWindow::generateView() {
  generateLayout();
  generateNodeEditor();
  generateGenerateButton();
}
void ProjectSubWindow::generateLayout() {
  LayoutType* const layout = new LayoutType;
  this->QWidget::setLayout(layout);
}
void ProjectSubWindow::generateNodeEditor() {
  node_editor_widget_ = new node_editor::Widget;
  layout()->addWidget(node_editor_widget_);
}
void ProjectSubWindow::generateGenerateButton() {
  generate_button_ = new QToolButton;
  generate_button_->setText("Generate");
  connect(generate_button_, &QToolButton::clicked, this,
          &ProjectSubWindow::onGenerateButtonClicked);
  layout()->addWidget(generate_button_);
}

void ProjectSubWindow::onGenerateButtonClicked() {
  assert(sender() != nullptr);
  assert(node_editor_widget_ != nullptr);

  /* node_editor_widget_->exportTo(node_editor::EK_HTML,
                                root_directory_widget_->path()); */
}
}  // namespace my_page_generator
}  // namespace gccore
