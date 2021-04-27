#include "visualizer/graph_view.h"

namespace graph {
    namespace visualizer {
        GraphView::GraphView(double window_size, double margin): kWindowSize(window_size), kMargin(margin),
                                                                 kDefaultFont(ci::Font("Times New Roman", 45)),
                                                                 kDefaultColor(ci::Color("orange")),
                                                                 kFontColor(ci::Color("black")),
                                                                 kDefaultRadius(30.0) {
        }

        void GraphView::Draw(Graph visualized_graph) {
            ci::gl::clear();
            DrawEdges(visualized_graph);
            DrawNodes(visualized_graph);
        }
        
        void GraphView::MoveNode(Graph* visualized_graph, vec2 new_location) {
            if(LocationOutOfBounds(new_location)){
                return;
            }

            //Graph changed_graph = visualized_graph;
            vector<Node> nodes = visualized_graph->GetNodes();
            for(size_t index = 0; index < nodes.size(); index++) {
                vec2 node_loc = nodes[index].GetLocation();
                if (glm::distance(new_location, node_loc) <= kDefaultRadius) {
                    visualized_graph->SetLocation(nodes[index], new_location);
                }
            }
        }
        
        void GraphView::DrawEdges(Graph visualized_graph) {
            vector<Node> nodes = visualized_graph.GetNodes();

            for (size_t index = 0; index < nodes.size(); index++) {

                vec2 location = nodes[index].GetLocation();
                vector<const Node *> adjacent_nodes = visualized_graph.GetAdjacentNodes(nodes[index]);
                for (size_t node_index = 0; node_index < adjacent_nodes.size(); node_index++) {
                    ci::gl::color(ci::Color("blue"));
                    ci::gl::lineWidth(5);
                    ci::gl::drawLine(location, adjacent_nodes[node_index]->GetLocation());
                }
            }
        }

        void GraphView::DrawNodes(Graph visualized_graph) {
            vector<Node> nodes = visualized_graph.GetNodes();
            for (size_t index = 0; index < nodes.size(); index++) {

                vec2 location = nodes[index].GetLocation();

                ci::gl::color(kDefaultColor);
                ci::gl::drawSolidCircle(location, kDefaultRadius);
                location[0] = location[0] - kDefaultRadius / 2;
                location[1] = location[1] - kDefaultRadius / 2;
                ci::gl::drawString(std::to_string(nodes[index].GetValue()), location, kFontColor,
                                   kDefaultFont);
            }
        }

        bool GraphView::LocationOutOfBounds(vec2 loc) {
            float x = loc[0];
            float y = loc[1];

            return x >= kWindowSize - kMargin || y >= kWindowSize - kMargin || x <= kMargin || y <= kMargin;
        }
    }
}