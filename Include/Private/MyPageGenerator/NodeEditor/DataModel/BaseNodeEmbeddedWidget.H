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

#ifndef MYPAGEGENERATOR_NODEEDITOR_DATAMODEL_BASENODEEMBEDDEDWIDGET_H
#define MYPAGEGENERATOR_NODEEDITOR_DATAMODEL_BASENODEEMBEDDEDWIDGET_H

#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>

#include <QtCore/QPointer>
#include <QtCore/QObject>
#include <QtCore/QString>

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
class BaseNodeEmbeddedWidget : public QWidget {
  Q_OBJECT

 public:
  using LayoutType = QVBoxLayout;

  explicit BaseNodeEmbeddedWidget(QWidget* const parent = nullptr);
  virtual ~BaseNodeEmbeddedWidget();

  QPointer<NodeDescription> nodeDescription() const;
  QPointer<widgets::MDEditor> mdEditor() const;

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
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_NODEEDITOR_DATAMODEL_BASENODEEMBEDDEDWIDGET_H
