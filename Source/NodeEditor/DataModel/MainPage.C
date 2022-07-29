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

#include <MyPageGenerator/NodeEditor/DataModel/MainPage.H>

#include <MyPageGenerator/NodeEditor/DataModel/NodeDescriptionWidget.H>
#include <MyPageGenerator/Widget/MDEditor.H>
#include <MyPageGenerator/Utility/MarkdownConvertor.H>
#include <MyPageGenerator/Constants.H>

#include <QtCore/QFileInfo>
#include <QtWidgets/QMessageBox>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
namespace embedded_widgets {
MainPageWidget::MainPageWidget(QWidget* const parent) : QWidget(parent) {
  generateView();
}

void MainPageWidget::setContent(QString const& new_content) {
  assert(md_editor_ != nullptr);
  md_editor_->setText(new_content);
}
QString MainPageWidget::content() const {
  assert(md_editor_ != nullptr);
  return md_editor_->text();
}

QPointer<MainPageWidget::LayoutType> MainPageWidget::layout() const {
  assert(QWidget::layout() != nullptr);
  return qobject_cast<LayoutType*>(QWidget::layout());
}

void MainPageWidget::generateView() {
  generateLayout();
  generateStyleSheet();
  generateNodeDescriptionSection();
  generateButton();
  generateMDEditor();
}
void MainPageWidget::generateLayout() {
  LayoutType* const layout = new LayoutType;
  setLayout(layout);
}
void MainPageWidget::generateStyleSheet() {
  this->QWidget::setObjectName("MainPageWidget_generateStyleSheet");
  setStyleSheet(
      "QWidget#MainPageWidget_generateStyleSheet { "
      "background-color: transparent; }");
}
void MainPageWidget::generateNodeDescriptionSection() {
  node_description_ = new NodeDescription;
  layout()->addWidget(node_description_);
}
void MainPageWidget::generateButton() {
  button_ = new QToolButton;
  button_->setText("Edit Page Content");
  connect(button_, &QToolButton::clicked, this,
          &MainPageWidget::onButtonClicked);
  layout()->addWidget(button_);
}
void MainPageWidget::generateMDEditor() { md_editor_ = new widgets::MDEditor; }

void MainPageWidget::onButtonClicked() { md_editor_->show(); }
}  // namespace embedded_widgets

MainPage::MainPage() { generateView(); }

void MainPage::setFilePath(QString const& new_file_path) {
  file_path_ = new_file_path;
}
QString MainPage::filePath() const { return /*file_path_*/ "index.html"; }

QString MainPage::exportToHtml() const {
  return utilities::MarkdownConvertor(embedded_widget_->content())
      .exportTo(utilities::MarkdownConvertor::EK_Html);
}

QWidget* MainPage::embeddedWidget() {
  assert(embedded_widget_ != nullptr);
  return embedded_widget_;
}

QString MainPage::name() const { return constants::kMainPageCaption; }
QString MainPage::caption() const { return constants::kMainPageCaption; }
bool MainPage::captionVisible() const { return true; }

QString MainPage::portCaption(QtNodes::PortType port_type,
                              QtNodes::PortIndex port_index) const {
  Q_UNUSED(port_index)

  if (port_type == QtNodes::PortType::In) {
    return constants::kMainPageInputPortCaption;
  }

  return QString();
}
bool MainPage::portCaptionVisible(QtNodes::PortType port_type,
                                  QtNodes::PortIndex port_index) const {
  Q_UNUSED(port_type)
  Q_UNUSED(port_index)
  return true;
}

unsigned int MainPage::nPorts(QtNodes::PortType port_type) const {
  std::uint32_t constexpr kInputPortsCount = 1;
  std::uint32_t constexpr kOutputPortsCount = 0;

  switch (port_type) {
    case QtNodes::PortType::In:
      return kInputPortsCount;
    case QtNodes::PortType::Out:
      return kOutputPortsCount;
    case QtNodes::PortType::None:
      break;
  }

  throw std::runtime_error("You shouldn't be here.");
}
QtNodes::NodeDataType MainPage::dataType(QtNodes::PortType port_type,
                                         QtNodes::PortIndex port_index) const {
  Q_UNUSED(port_type)
  Q_UNUSED(port_index)
  return QtNodes::NodeDataType{"text", "Text"};
}

void MainPage::setInData(std::shared_ptr<QtNodes::NodeData> node_data,
                         QtNodes::PortIndex port) {
  Q_UNUSED(node_data)
  Q_UNUSED(port)
}
void MainPage::setInData(std::shared_ptr<QtNodes::NodeData> node_data,
                         QtNodes::PortIndex port, QUuid const& connection_id) {
  Q_UNUSED(node_data)
  Q_UNUSED(port)
  Q_UNUSED(connection_id)
}

std::shared_ptr<QtNodes::NodeData> MainPage::outData(QtNodes::PortIndex port) {
  Q_UNUSED(port)
  return nullptr;
}
QtNodes::NodeDataModel::ConnectionPolicy MainPage::portInConnectionPolicy(
    QtNodes::PortIndex port_index) const {
  Q_UNUSED(port_index)
  return QtNodes::NodeDataModel::ConnectionPolicy::Many;
}

void MainPage::generateView() {
  embedded_widget_ = new embedded_widgets::MainPageWidget;
}
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore
