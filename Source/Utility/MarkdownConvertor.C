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

#include <MyPageGenerator/Utility/MarkdownConvertor.H>

#include <md4c-html.h>

#include <string>

namespace gccore {
namespace my_page_generator {
namespace utilities {
namespace core {
MarkdownConvertor::MarkdownConvertor(QString const& markdown)
    : markdown_(markdown) {}

QString MarkdownConvertor::exportTo(ExportKinds const mode) const {
  switch (mode) {
    case EK_Html:
      return exportToHtml();
  }
}
QString MarkdownConvertor::exportToHtml() const {
  std::string result;

  std::uint32_t constexpr kMdParserFlags =
      MD_FLAG_TABLES | MD_FLAG_STRIKETHROUGH | MD_FLAG_PERMISSIVEWWWAUTOLINKS |
      MD_FLAG_TASKLISTS | MD_FLAG_LATEXMATHSPANS | MD_FLAG_WIKILINKS |
      MD_FLAG_UNDERLINE;
  std::uint32_t constexpr kMdRendererFlags = MD_HTML_FLAG_DEBUG;
  std::int32_t constexpr kMdHtmlFailCode = -1;

  std::int32_t const return_code = ::md_html(
      markdown_.toStdString().c_str(), markdown_.size(),
      +[](MD_CHAR const* data, MD_SIZE const size, void* const user_data) {
        std::string* const buffer = reinterpret_cast<std::string*>(user_data);
        assert(buffer != nullptr);
        buffer->append(data, size);
      },
      reinterpret_cast<void*>(&result), kMdParserFlags, kMdRendererFlags);

  assert(return_code != kMdHtmlFailCode);
  return QString::fromStdString(result);
}
}  // namespace core
}  // namespace utilities
}  // namespace my_page_generator
}  // namespace gccore
