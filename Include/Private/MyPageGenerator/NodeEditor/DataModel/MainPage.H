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

#include <nodes/NodeDataModel>

#include <QtCore/QPointer>
#include <QtCore/QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
namespace embedded_widgets {
class MainPageWidget : public QWidget {
  Q_OBJECT

 public:
  explicit MainPageWidget(QWidget* const parent = nullptr);

  void setText(QString const& new_text);

 private:
  QPointer<QHBoxLayout> getLayout() const;

  void generateView();
  void generateLayout();
  void generateWidget();

  QPointer<QLabel> label_;
};
}  // namespace embedded_widgets

class MainPage : public QtNodes::NodeDataModel {
 public:
  MainPage();

  QWidget* embeddedWidget() override;

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

 private:
  void generateView();

  QPointer<embedded_widgets::MainPageWidget> embedded_widget_;
};
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_NODEEDITOR_DATAMODEL_MAINPAGE_H
