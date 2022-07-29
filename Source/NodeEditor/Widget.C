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

#include <MyPageGenerator/NodeEditor/DataModel/MainPage.H>
#include <MyPageGenerator/Utility/File.H>
#include <MyPageGenerator/Constants.H>

#include <QtCore/QDir>

#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>
#include <nodes/FlowViewStyle>
#include <nodes/NodeStyle>

namespace gccore {
namespace my_page_generator {
namespace node_editor {
Widget::Widget(QWidget* const parent) : QWidget(parent) { generateView(); }

void Widget::exportTo(ExportKinds const mode, QString const& path) {
  switch (mode) {
    case EK_HTML:
      exportToHtml(path);
      break;
  }
}
void Widget::exportToHtml(QString const& path) {
  assert(flow_scene_ != nullptr);

  flow_scene_->iterateOverNodeData(
      [directory_path = path](QtNodes::NodeDataModel* const data_model) {
        assert(data_model != nullptr);

        QString const file_path =
            data_model->property(constants::properties::kPath).toString();
        QString const file_content =
            data_model->property(constants::properties::kHtml).toString();

        utilities::File(directory_path + QDir::separator() + file_path)
            .write(file_content);
      });
}

QPointer<QHBoxLayout> Widget::layout() const {
  assert(this->QWidget::layout() != nullptr);
  return qobject_cast<QHBoxLayout*>(this->QWidget::layout());
}

void Widget::generateView() {
  generateNodeEditorStyle();
  generateLayout();
  generateNodeEditor();
  generateNodeDataModel();
}
void Widget::generateLayout() {
  QHBoxLayout* const layout = new QHBoxLayout;
  layout->setMargin(0);
  setLayout(layout);
}
void Widget::generateNodeEditor() {
  flow_scene_ = new QtNodes::FlowScene;
  flow_view_ = new QtNodes::FlowView(flow_scene_);

  connect(flow_scene_, &QtNodes::FlowScene::nodeCreated, this,
          &Widget::nodeCreated);

  layout()->addWidget(flow_view_);
}
void Widget::generateNodeDataModel() {
  assert(flow_scene_ != nullptr);

  std::shared_ptr<QtNodes::DataModelRegistry> registery(
      new QtNodes::DataModelRegistry);
  registery->registerModel<data_models::MainPage>();

  flow_scene_->setRegistry(registery);
}
void Widget::generateNodeEditorStyle() {
  QtNodes::FlowViewStyle::setStyle(
      R"(
        {
          "FlowViewStyle": {
            "BackgroundColor": [255, 255, 221],
            "FineGridColor": [245, 245, 230],
            "CoarseGridColor": [235, 235, 220]
          }
        }
        )");
  QtNodes::NodeStyle::setNodeStyle(
      R"(
        {
          "NodeStyle": {
            "NormalBoundaryColor": "darkgray",
            "SelectedBoundaryColor": "deepskyblue",
            "GradientColor0": "mintcream",
            "GradientColor1": "mintcream",
            "GradientColor2": "mintcream",
            "GradientColor3": "mintcream",
            "ShadowColor": [200, 200, 200],
            "FontColor": [10, 10, 10],
            "FontColorFaded": [100, 100, 100],
            "ConnectionPointColor": "white",
            "PenWidth": 2.0,
            "HoveredPenWidth": 2.5,
            "ConnectionPointDiameter": 10.0,
            "Opacity": 1.0
          }
        }
        )");
  QtNodes::ConnectionStyle::setConnectionStyle(
      R"(
        {
          "ConnectionStyle": {
            "ConstructionColor": "gray",
            "NormalColor": "black",
            "SelectedColor": "gray",
            "SelectedHaloColor": "deepskyblue",
            "HoveredColor": "deepskyblue",

            "LineWidth": 3.0,
            "ConstructionLineWidth": 2.0,
            "PointDiameter": 10.0,

            "UseDataDefinedColors": false
          }
        }
        )");
}

void Widget::nodeCreated(QtNodes::Node& new_node) {
  assert(nullptr != new_node.nodeDataModel());

  QtNodes::NodeDataModel* const data_model = new_node.nodeDataModel();
  if (data_models::MainPage* const main_page =
          qobject_cast<data_models::MainPage*>(data_model)) {
  }
}
}  // namespace node_editor
}  // namespace my_page_generator
}  // namespace gccore
