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

#ifndef MYPAGEGENERATOR_NODEEDITOR_DATAMODEL_BASENODEDATAMODEL_H
#define MYPAGEGENERATOR_NODEEDITOR_DATAMODEL_BASENODEDATAMODEL_H

#include <nodes/NodeDataModel>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>

#include <QtCore/QPointer>
#include <QtCore/QObject>
#include <QtCore/QString>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
namespace embedded_widgets {
class BaseNodeEmbeddedWidget;
}  // namespace embedded_widgets
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
class BaseNodeDataModel : public QtNodes::NodeDataModel {
  Q_OBJECT
  Q_PROPERTY(QString FilePath READ filePath WRITE setFilePath)
  Q_PROPERTY(QString RawMd READ rawMd WRITE setRawMd)
  Q_PROPERTY(QString Html READ exportToHtml CONSTANT)

 public:
  using LayoutType = QVBoxLayout;

  explicit BaseNodeDataModel();
  virtual ~BaseNodeDataModel();

  QPointer<embedded_widgets::BaseNodeEmbeddedWidget> baseEmbeddedWidget() const;

  void setFilePath(QString const& new_file_path);
  QString filePath() const;

  void setRawMd(QString const& new_raw_md);
  QString rawMd() const;

  QString exportToHtml() const;

  QWidget* embeddedWidget() override;

 protected:
  QPointer<LayoutType> layout() const;

 private:
  void generateView();
  void generateLayout();
  void generateEmbeddedWidget();
  void generateBaseEmbeddedWidget();
  void generateStyleSheet();

  QPointer<QWidget> embedded_widget_;
  QPointer<embedded_widgets::BaseNodeEmbeddedWidget> base_embedded_widget_;
  QString file_path_;
};
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_NODEEDITOR_DATAMODEL_BASENODEDATAMODEL_H
