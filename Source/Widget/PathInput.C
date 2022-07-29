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

#include <MyPageGenerator/Widget/PathInput.H>

#include <QtWidgets/QFileDialog>

namespace gccore {
namespace my_page_generator {
namespace widgets {
PathInput::PathInput(QWidget* const parent) : QWidget(parent) {
  generateView();
}

void PathInput::setPath(QString const& new_path) {
  assert(input_path_widget_ != nullptr);
  input_path_widget_->setText(new_path);
}
QString PathInput::path() const {
  assert(input_path_widget_ != nullptr);
  return input_path_widget_->text();
}

void PathInput::setPlaceholderText(QString const& new_placeholder_text) {
  assert(input_path_widget_ != nullptr);
  input_path_widget_->setPlaceholderText(new_placeholder_text);
}
QString PathInput::placeholderText() const {
  assert(input_path_widget_ != nullptr);
  return input_path_widget_->placeholderText();
}

QPointer<QHBoxLayout> PathInput::layout() const {
  assert(this->QWidget::layout() != nullptr);
  return qobject_cast<QHBoxLayout*>(this->QWidget::layout());
}

void PathInput::generateView() {
  generateLayout();
  generateInputPathWidget();
  generateBrowseButtonWidget();
}
void PathInput::generateLayout() {
  QHBoxLayout* const layout = new QHBoxLayout;
  this->QWidget::setLayout(layout);
}
void PathInput::generateInputPathWidget() {
  input_path_widget_ = new QLineEdit;
  connect(input_path_widget_, &QLineEdit::textChanged, this,
          &PathInput::pathChanged);
  layout()->addWidget(input_path_widget_);
}
void PathInput::generateBrowseButtonWidget() {
  browse_button_widget_ = new QToolButton;
  connect(browse_button_widget_, &QToolButton::clicked, this,
          &PathInput::onBrowseButtonClicked);
  layout()->addWidget(browse_button_widget_);
}

void PathInput::onBrowseButtonClicked() {
  assert(input_path_widget_ != nullptr);

  QString const root_directory = QFileDialog::getExistingDirectory(this);
  if (!root_directory.isEmpty()) {
    setPath(root_directory);
  }
}
}  // namespace widgets
}  // namespace my_page_generator
}  // namespace gccore
