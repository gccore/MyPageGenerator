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

#include <MyPageGenerator/NodeEditor/DataModel/NodeDescriptionWidget.H>

#include <MyPageGenerator/Widget/LineEdit.H>

#include <QtWidgets/QLabel>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
namespace embedded_widgets {
NodeDescription::NodeDescription(QWidget* const parent) : QWidget(parent) {
  generateView();
}

void NodeDescription::setFileName(QString const& new_file_name) {
  assert(file_name_widget_ != nullptr);
  file_name_widget_->setText(new_file_name);
}
QString NodeDescription::fileName() const {
  assert(file_name_widget_ != nullptr);
  return file_name_widget_->text();
}

QPointer<NodeDescription::LayoutType> NodeDescription::layout() const {
  assert(this->QWidget::layout() != nullptr);
  return qobject_cast<LayoutType*>(this->QWidget::layout());
}

void NodeDescription::generateView() {
  generateLayout();
  generateFileNameSection();
}
void NodeDescription::generateLayout() {
  LayoutType* const layout = new LayoutType;
  setLayout(layout);
}
void NodeDescription::generateFileNameSection() {
  file_name_widget_ = new widgets::LineEdit;
  file_name_widget_->setLabelText("File Name: ");
  layout()->addWidget(file_name_widget_);
}
}  // namespace embedded_widgets
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore
