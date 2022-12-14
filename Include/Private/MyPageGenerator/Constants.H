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

#ifndef MYPAGEGENERATOR_PRIVATE_CONSTANTS_H
#define MYPAGEGENERATOR_PRIVATE_CONSTANTS_H

namespace gccore {
namespace my_page_generator {
namespace constants {
auto constexpr kWindowTitle = "Page Generator - GCCORE";
auto constexpr kMainPageCaption = "Main Page";
auto constexpr kMainPageInputPortCaption = "Subpages";
auto constexpr kNameProperty = "NameProperty";
auto constexpr kMainPageNameProperty = kMainPageCaption;
auto constexpr kSaveFileName = "Settings.MyPageGenerator.GCCORE";
auto constexpr kMdDirectory = "MD";
auto constexpr kDefaultMainPathFileName = "index.html";
auto constexpr kMainPageOutputPortIndex = 1;
auto constexpr kHtmlSuffix = ".html";
auto constexpr kMarkdownSuffix = ".md";
auto constexpr kMaximumRecentProjects = 10;
auto constexpr kEmptyActionText = "[ EMPTY ]";
auto constexpr kSettingsFileName = "Settings.GCCORE.MyPageGenerator.ini";

namespace settings {
auto constexpr kRecentProjects = "RecentProjects/Names";
} // namespace settings
namespace properties {
auto constexpr kPath = "FilePath";
auto constexpr kHtml = "Html";
auto constexpr kRawMd = "RawMd";
} // namespace properties
} // namespace constants
} // namespace my_page_generator
} // namespace gccore

#endif // MYPAGEGENERATOR_PRIVATE_CONSTANTS_H
