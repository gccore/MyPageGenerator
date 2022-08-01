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

#include <MyPageGenerator/NodeEditor/DataModel/BaseNodeDataModel.H>

#include <MyPageGenerator/NodeEditor/DataModel/BaseNodeEmbeddedWidget.H>
#include <MyPageGenerator/NodeEditor/DataModel/NodeDescriptionWidget.H>
#include <MyPageGenerator/Utility/CommonWidgetUtilities.H>
#include <MyPageGenerator/Utility/CommonCoreUtilities.H>
#include <MyPageGenerator/Utility/MarkdownConvertor.H>
#include <MyPageGenerator/Widget/MDEditor.H>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
BaseNodeDataModel::BaseNodeDataModel() { generateView(); }
BaseNodeDataModel::~BaseNodeDataModel() {
  if (embedded_widget_ != nullptr) embedded_widget_->deleteLater();
}

QPointer<embedded_widgets::BaseNodeEmbeddedWidget>
BaseNodeDataModel::baseEmbeddedWidget() const {
  assert(base_embedded_widget_ != nullptr);
  return base_embedded_widget_;
}

void BaseNodeDataModel::setFilePath(QString const& new_file_path) {
  baseEmbeddedWidget()->nodeDescription()->setFileName(new_file_path);
}
QString BaseNodeDataModel::filePath() const {
  return baseEmbeddedWidget()->nodeDescription()->fileName();
}

void BaseNodeDataModel::setRawMd(QString const& new_raw_md) {
  baseEmbeddedWidget()->mdEditor()->setText(new_raw_md);
}
QString BaseNodeDataModel::rawMd() const {
  return baseEmbeddedWidget()->mdEditor()->text();
}

QString BaseNodeDataModel::exportToHtml() const {
  return utilities::core::MarkdownConvertor(baseEmbeddedWidget()->content())
      .exportToHtml();
}

QWidget* BaseNodeDataModel::embeddedWidget() { return embedded_widget_; }

QPointer<BaseNodeDataModel::LayoutType> BaseNodeDataModel::layout() const {
  assert(embedded_widget_ != nullptr);
  assert(embedded_widget_->layout() != nullptr);
  return qobject_cast<LayoutType*>(embedded_widget_->layout());
}

void BaseNodeDataModel::generateView() {
  generateEmbeddedWidget();
  generateLayout();
  generateBaseEmbeddedWidget();
  generateStyleSheet();
}
void BaseNodeDataModel::generateEmbeddedWidget() {
  embedded_widget_ = new QWidget;
}
void BaseNodeDataModel::generateLayout() {
  assert(embedded_widget_ != nullptr);
  LayoutType* layout = new LayoutType;
  layout->setMargin(0);
  embedded_widget_->setLayout(layout);
}
void BaseNodeDataModel::generateBaseEmbeddedWidget() {
  base_embedded_widget_ = new embedded_widgets::BaseNodeEmbeddedWidget;
  layout()->addWidget(base_embedded_widget_);
}
void BaseNodeDataModel::generateStyleSheet() {
  assert(embedded_widget_ != nullptr);
  assert(base_embedded_widget_ != nullptr);
  utilities::widgets::SetTransparentStyleSheet(embedded_widget_);
  utilities::widgets::SetTransparentStyleSheet(base_embedded_widget_);
}
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore
