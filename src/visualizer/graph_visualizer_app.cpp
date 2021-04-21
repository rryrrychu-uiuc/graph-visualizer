#include "../../include/visualizer/graph_visualizer_app.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace graph {
    namespace visualizer {
        GraphVisualizerApp::GraphVisualizerApp():
                kDefaultFont(ci::Font("Times New Roman", 45)),
                kDefaultColor(ci::Color("orange")),
                kFontColor(ci::Color("black")),
                kDefaultRadius(30.0) {
            ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
        }

        GraphVisualizerApp::GraphVisualizerApp(Graph to_visualize) : visualized_nodes_(to_visualize.GetNodes()),
                                                                     kDefaultFont(ci::Font("Times New Roman", 45)),
                                                                     kDefaultColor(ci::Color("orange")),
                                                                     kFontColor(ci::Color("black")),
                                                                     kDefaultRadius(30.0) {
            ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
        }

        void GraphVisualizerApp::UpdateGraph(Graph to_visualize) {
            visualized_nodes_ = to_visualize.GetNodes();
        }

        void GraphVisualizerApp::draw() {
            for (size_t index = 0; index < visualized_nodes_.size(); index++) {

                vec2 location = visualized_nodes_[index].GetLocation();
                ci::gl::color(kDefaultColor);
                ci::gl::drawSolidCircle(location, kDefaultRadius);
                ci::gl::drawString(std::to_string(visualized_nodes_[index].GetValue()), location, kFontColor,
                                   kDefaultFont);
                
                vector<Node*> adjacent_nodes = visualized_nodes_[index].GetAdjacentNodes();
                for(size_t nodes = 0; nodes < adjacent_nodes.size(); nodes++) {
                    ci::gl::color(ci::Color("blue"));
                    ci::gl::drawLine(location, adjacent_nodes[nodes]->GetLocation());
                }
            }
        }
    }
}