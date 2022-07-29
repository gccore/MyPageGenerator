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

#include <MyPageGenerator/Widget/LineEdit.H>

namespace gccore {
namespace my_page_generator {
namespace widgets {
LineEdit::LineEdit(QWidget* const parent) : QWidget(parent) { generateView(); }

void LineEdit::setText(QString const& new_text) {
  assert(line_edit_ != nullptr);
  line_edit_->setText(new_text);
}
QString LineEdit::text() const {
  assert(line_edit_ != nullptr);
  return line_edit_->text();
}

void LineEdit::setPlaceholderText(QString const& new_placeholder_text) {
  assert(line_edit_ != nullptr);
  line_edit_->setPlaceholderText(new_placeholder_text);
}
QString LineEdit::placeholderText() const {
  assert(line_edit_ != nullptr);
  return line_edit_->placeholderText();
}

void LineEdit::setLabelText(QString const& new_label_text) {
  assert(label_ != nullptr);
  label_->setText(new_label_text);
}
QString LineEdit::labelText() const {
  assert(label_ != nullptr);
  return label_->text();
}

QPointer<LineEdit::LayoutType> LineEdit::layout() const {
  assert(this->QWidget::layout() != nullptr);
  return qobject_cast<LayoutType*>(this->QWidget::layout());
}

void LineEdit::generateView() {
  generateLayout();
  generateLabel();
  generateLineEdit();
}
void LineEdit::generateLayout() {
  LayoutType* const layout = new LayoutType;
  layout->setMargin(0);
  setLayout(layout);
}
void LineEdit::generateLabel() {
  label_ = new QLabel;
  layout()->addWidget(label_);
}
void LineEdit::generateLineEdit() {
  line_edit_ = new QLineEdit;
  connect(line_edit_, &QLineEdit::textChanged, this, &LineEdit::textChanged);
  layout()->addWidget(line_edit_);
}
}  // namespace widgets
}  // namespace my_page_generator
}  // namespace gccore
