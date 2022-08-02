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

#include <MyPageGenerator/NodeEditor/DataModel/SubPage.H>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
QString SubPage::caption() const { return "Sub Page"; }
QString SubPage::name() const { return "Sub Page Node"; }

QtNodes::NodeDataModel::ConnectionPolicy SubPage::portInConnectionPolicy(
    QtNodes::PortIndex port_index) const {
  Q_UNUSED(port_index)
  return QtNodes::NodeDataModel::ConnectionPolicy::One;
}
QtNodes::NodeDataModel::ConnectionPolicy SubPage::portOutConnectionPolicy(
    QtNodes::PortIndex port_index) const {
  Q_UNUSED(port_index)
  return QtNodes::NodeDataModel::ConnectionPolicy::One;
}

bool SubPage::portCaptionVisible(QtNodes::PortType port_type,
                                 QtNodes::PortIndex port_index) const {
  Q_UNUSED(port_type)
  Q_UNUSED(port_index)
  return true;
}
QString SubPage::portCaption(QtNodes::PortType port_type,
                             QtNodes::PortIndex port_index) const {
  switch (port_type) {
    case QtNodes::PortType::None:
      return "None";
    case QtNodes::PortType::In:
      return "Previous";
    case QtNodes::PortType::Out:
      if (port_index == 0)
        return "Next";
      else
        return "To Main Page";
  }
}

unsigned int SubPage::nPorts(QtNodes::PortType port_type) const {
  return port_type == QtNodes::PortType::In ? 1 : 2;
}

QtNodes::NodeDataType SubPage::dataType(QtNodes::PortType port_type,
                                        QtNodes::PortIndex port_index) const {
  Q_UNUSED(port_type)
  Q_UNUSED(port_index)
  return QtNodes::NodeDataType{"text", "Text"};
}
void SubPage::setInData(std::shared_ptr<QtNodes::NodeData> node_data,
                        QtNodes::PortIndex port_index) {
  Q_UNUSED(node_data)
  Q_UNUSED(port_index)
}

std::shared_ptr<QtNodes::NodeData> SubPage::outData(
    QtNodes::PortIndex port_index) {
  Q_UNUSED(port_index)
  return nullptr;
}
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore
