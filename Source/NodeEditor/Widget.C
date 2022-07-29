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

#include <MyPageGenerator/NodeEditor/Widget.H>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
Widget::Widget(QWidget* const parent) : QWidget(parent) { generateView(); }

QPointer<QHBoxLayout> Widget::getLayout() const {
  assert(layout() != nullptr);
  return qobject_cast<QHBoxLayout*>(layout());
}

void Widget::generateView() {
  generateLayout();
  generateNodeEditor();
}
void Widget::generateLayout() {
  QHBoxLayout* const layout = new QHBoxLayout;
  setLayout(layout);
}
void Widget::generateNodeEditor() {
  flow_scene_ = new QtNodes::FlowScene;
  flow_view_ = new QtNodes::FlowView(flow_scene_);

  getLayout()->addWidget(flow_view_);
}
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore
