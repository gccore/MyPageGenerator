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

#include <MyPageGenerator/Constants.H>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
namespace embedded_widgets {
MainPageWidget::MainPageWidget(QWidget* const parent) : QWidget(parent) {
  generateView();
}

void MainPageWidget::setText(QString const& new_text) {
  assert(label_ != nullptr);
  label_->setText(new_text);
}

QPointer<QHBoxLayout> MainPageWidget::getLayout() const {
  assert(layout() != nullptr);
  return qobject_cast<QHBoxLayout*>(layout());
}

void MainPageWidget::generateView() {
  generateLayout();
  generateWidget();
}
void MainPageWidget::generateLayout() {
  QHBoxLayout* const layout = new QHBoxLayout;
  setLayout(layout);
}
void MainPageWidget::generateWidget() {
  label_ = new QLabel("Testing");
  getLayout()->addWidget(label_);
}
}  // namespace embedded_widgets

MainPage::MainPage() { generateView(); }

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

  if (embedded_widget_ != nullptr) {
    embedded_widget_->setText(QTime::currentTime().toString());
  }
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
