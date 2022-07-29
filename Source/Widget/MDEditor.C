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

#include <MyPageGenerator/Widget/MDEditor.H>

namespace gccore {
namespace my_page_generator {
namespace widgets {
MDEditor::MDEditor(QWidget* const parent) : QWidget(parent) { generateView(); }

void MDEditor::setText(QString const& content) {
  assert(text_edit_ != nullptr);
  text_edit_->setText(content);
}
QString MDEditor::text() const {
  assert(text_edit_ != nullptr);
  return text_edit_->toPlainText();
}

QPointer<QHBoxLayout> MDEditor::layout() const {
  assert(this->QWidget::layout() != nullptr);
  return qobject_cast<QHBoxLayout*>(this->QWidget::layout());
}

void MDEditor::generateView() {
  generateLayout();
  generateTextEditWidget();
}
void MDEditor::generateLayout() {
  QHBoxLayout* const layout = new QHBoxLayout;
  setLayout(layout);
}
void MDEditor::generateTextEditWidget() {
  text_edit_ = new QTextEdit;
  layout()->addWidget(text_edit_);
}
}  // namespace widgets
}  // namespace my_page_generator
}  // namespace gccore
