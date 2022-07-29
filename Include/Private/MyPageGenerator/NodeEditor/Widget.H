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

#ifndef MYPAGEGENERATOR_PRIVATE_NODEEDITORWIDGET_H
#define MYPAGEGENERATOR_PRIVATE_NODEEDITORWIDGET_H

#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/Node>

#include <QtCore/QPointer>
#include <QtCore/QObject>
#include <QtWidgets/QLayout>
#include <QtWidgets/QWidget>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
enum ExportKinds { EK_HTML };

class Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget* const parent = nullptr);

  void exportTo(ExportKinds const mode, QString const& path);
  void exportToHtml(QString const& path);

 private:
  QPointer<QHBoxLayout> layout() const;

  void generateView();
  void generateLayout();
  void generateNodeEditor();
  void generateNodeDataModel();
  void generateNodeEditorStyle();

  Q_SLOT void nodeCreated(QtNodes::Node& new_node);

  QPointer<QtNodes::FlowScene> flow_scene_;
  QPointer<QtNodes::FlowView> flow_view_;
};
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_NODEEDITORWIDGET_H
