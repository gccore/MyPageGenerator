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

#ifndef MYPAGEGENERATOR_UTILITY_COMMONWIDGETUTILITIES_H
#define MYPAGEGENERATOR_UTILITY_COMMONWIDGETUTILITIES_H

#include <MyPageGenerator/Utility/CommonCoreUtilities.H>

#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QFrame>
#include <QtCore/QPointer>

#include <cstdint>

namespace gccore {
namespace my_page_generator {
namespace widgets {
namespace utilities {
inline QSpacerItem* CreateHorizontalSpacer() {
  return new QSpacerItem(-1, 1, QSizePolicy::Expanding);
}
inline QSpacerItem* CreateVerticalSpacer() {
  return new QSpacerItem(1, -1, QSizePolicy::Minimum, QSizePolicy::Expanding);
}

inline QPointer<QFrame> CreateHorizontalFrame() {
  QFrame* const line_frame = new QFrame;
  line_frame->setFrameShape(QFrame::HLine);
  line_frame->setFrameShadow(QFrame::Sunken);
  return line_frame;
}
inline QPointer<QFrame> CreateVerticalFrame() {
  QFrame* const line_frame = new QFrame;
  line_frame->setFrameShape(QFrame::VLine);
  line_frame->setFrameShadow(QFrame::Sunken);
  return line_frame;
}

inline void SetTransparentStyleSheet(QWidget* const widget) {
  assert(widget != nullptr);

  if (widget->objectName().isEmpty()) {
    using gccore::my_page_generator::utilities::GenerateUniqueObjectName;
    widget->setObjectName(GenerateUniqueObjectName());
  }

  widget->setStyleSheet(QString("QWidget#%1 { background-color: transparent; }")
                            .arg(widget->objectName()));
}
}  // namespace utilities
}  // namespace widgets
}  // namespace my_page_generator
}  // namespace gccore

#endif  // MYPAGEGENERATOR_UTILITY_COMMONWIDGETUTILITIES_H
