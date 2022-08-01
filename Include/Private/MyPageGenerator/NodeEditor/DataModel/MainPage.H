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

#ifndef MYPAGEGENERATOR_PRIVATE_NODEEDITOR_DATAMODEL_MAINPAGE_H
#define MYPAGEGENERATOR_PRIVATE_NODEEDITOR_DATAMODEL_MAINPAGE_H

#include <MyPageGenerator/NodeEditor/DataModel/BaseNodeDataModel.H>

#include <QtCore/QPointer>
#include <QtCore/QString>
#include <QtCore/QObject>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
class MainPage : public BaseNodeDataModel {
  Q_OBJECT

 public:
  QString name() const override;
  QString caption() const override;
  bool captionVisible() const override;

  QString portCaption(QtNodes::PortType port_type,
                      QtNodes::PortIndex port_index) const override;
  bool portCaptionVisible(QtNodes::PortType port_type,
                          QtNodes::PortIndex port_index) const override;

  unsigned int nPorts(QtNodes::PortType port_type) const override;
  QtNodes::NodeDataType dataType(QtNodes::PortType port_type,
                                 QtNodes::PortIndex port_index) const override;

  void setInData(std::shared_ptr<QtNodes::NodeData> node_data,
                 QtNodes::PortIndex port) override;
  void setInData(std::shared_ptr<QtNodes::NodeData> node_data,
                 QtNodes::PortIndex port, QUuid const& connection_id) override;

  std::shared_ptr<QtNodes::NodeData> outData(QtNodes::PortIndex port) override;
  ConnectionPolicy portInConnectionPolicy(
      QtNodes::PortIndex port_index) const override;
};
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_NODEEDITOR_DATAMODEL_MAINPAGE_H
