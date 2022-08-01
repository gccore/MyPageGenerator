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

#include <MyPageGenerator/NodeEditor/DataModel/BaseNodeEmbeddedWidget.H>

#include <MyPageGenerator/NodeEditor/DataModel/NodeDescriptionWidget.H>
#include <MyPageGenerator/Utility/CommonWidgetUtilities.H>
#include <MyPageGenerator/Utility/CommonCoreUtilities.H>
#include <MyPageGenerator/Widget/MDEditor.H>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
namespace embedded_widgets {
BaseNodeEmbeddedWidget::BaseNodeEmbeddedWidget(QWidget* const parent)
    : QWidget(parent) {
  generateView();
}
BaseNodeEmbeddedWidget::~BaseNodeEmbeddedWidget() {
  if (md_editor_ != nullptr) md_editor_->deleteLater();
}

QPointer<NodeDescription> BaseNodeEmbeddedWidget::nodeDescription() const {
  assert(node_description_ != nullptr);
  return node_description_;
}
QPointer<widgets::MDEditor> BaseNodeEmbeddedWidget::mdEditor() const {
  assert(md_editor_ != nullptr);
  return md_editor_;
}

void BaseNodeEmbeddedWidget::setContent(QString const& new_content) {
  mdEditor()->setText(new_content);
}
QString BaseNodeEmbeddedWidget::content() const { return mdEditor()->text(); }

QPointer<BaseNodeEmbeddedWidget::LayoutType> BaseNodeEmbeddedWidget::layout()
    const {
  assert(QWidget::layout() != nullptr);
  return qobject_cast<LayoutType*>(QWidget::layout());
}

void BaseNodeEmbeddedWidget::generateView() {
  generateLayout();
  generateStyleSheet();
  generateNodeDescriptionSection();
  generateButton();
  generateMDEditor();
}
void BaseNodeEmbeddedWidget::generateLayout() {
  LayoutType* const layout = new LayoutType;
  setLayout(layout);
}
void BaseNodeEmbeddedWidget::generateStyleSheet() {
  utilities::widgets::SetTransparentStyleSheet(this);
}
void BaseNodeEmbeddedWidget::generateNodeDescriptionSection() {
  node_description_ = new NodeDescription;
  layout()->addWidget(node_description_);
}
void BaseNodeEmbeddedWidget::generateButton() {
  button_ = new QToolButton;
  button_->setText("Edit Page Content");
  connect(button_, &QToolButton::clicked, this,
          &BaseNodeEmbeddedWidget::onButtonClicked);
  layout()->addWidget(button_);
}
void BaseNodeEmbeddedWidget::generateMDEditor() {
  md_editor_ = new widgets::MDEditor;
}

void BaseNodeEmbeddedWidget::onButtonClicked() { md_editor_->show(); }
}  // namespace embedded_widgets
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore
