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

#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>

#include <QtCore/QPointer>
#include <QtCore/QString>
#include <QtCore/QObject>

namespace gccore {
namespace my_page_generator {
namespace widgets {
class MDEditor;
}  // namespace widgets
namespace node_editor {
namespace data_models {
namespace embedded_widgets {
class NodeDescription;
}  // namespace embedded_widgets
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
namespace embedded_widgets {
class MainPageWidget : public QWidget {
  Q_OBJECT

 public:
  using LayoutType = QVBoxLayout;

  explicit MainPageWidget(QWidget* const parent = nullptr);

  QPointer<NodeDescription> nodeDescription();
  QPointer<widgets::MDEditor> mdEditor();

  void setContent(QString const& new_content);
  QString content() const;

 private:
  QPointer<LayoutType> layout() const;

  void generateView();
  void generateLayout();
  void generateStyleSheet();
  void generateNodeDescriptionSection();
  void generateButton();
  void generateMDEditor();

  Q_SLOT void onButtonClicked();

  QPointer<QToolButton> button_;
  QPointer<NodeDescription> node_description_;
  QPointer<widgets::MDEditor> md_editor_;
};
}  // namespace embedded_widgets

class MainPage : public QtNodes::NodeDataModel {
  Q_OBJECT

  Q_PROPERTY(QString FilePath READ filePath WRITE setFilePath)
  Q_PROPERTY(QString Html READ exportToHtml CONSTANT)
  Q_PROPERTY(QString RawMd READ rawMd WRITE setRawMd)

 public:
  MainPage();
  virtual ~MainPage();

  void setFilePath(QString const& new_file_path);
  QString filePath() const;

  void setRawMd(QString const& new_raw_md);
  QString rawMd() const;

  QString exportToHtml() const;

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
  QString file_path_;
};
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_NODEEDITOR_DATAMODEL_MAINPAGE_H
