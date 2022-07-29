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

#ifndef MYPAGEGENERATOR_PRIVATE_NODEEDITOR_DATAMODEL_NODEDESCRIPTION_H
#define MYPAGEGENERATOR_PRIVATE_NODEEDITOR_DATAMODEL_NODEDESCRIPTION_H

#include <QtCore/QPointer>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>

namespace gccore {
namespace my_page_generator {
namespace widgets {
class LineEdit;
}  // namespace widgets
}  // namespace my_page_generator
}  // namespace gccore

namespace gccore {
namespace my_page_generator {
namespace node_editor {
namespace data_models {
namespace embedded_widgets {
class NodeDescription : public QWidget {
  Q_OBJECT
 public:
  using LayoutType = QVBoxLayout;

  explicit NodeDescription(QWidget* const parent = nullptr);

  void setFileName(QString const& new_file_name);
  QString fileName() const;

 private:
  QPointer<LayoutType> layout() const;

  void generateView();
  void generateLayout();
  void generateFileNameSection();

  QPointer<widgets::LineEdit> file_name_widget_;
};
}  // namespace embedded_widgets
}  // namespace data_models
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_PRIVATE_NODEEDITOR_DATAMODEL_NODEDESCRIPTION_H
