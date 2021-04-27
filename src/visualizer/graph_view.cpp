#include "visualizer/graph_view.h"

namespace graph {
    namespace visualizer {
        GraphView::GraphView(double window_size, double margin): kWindowSize(window_size), kMargin(margin),
                                                                 kDefaultFont(ci::Font("Times New Roman", 45)),
                                                                 kDefaultColor(ci::Color("orange")),
                                                                 kFontColor(ci::Color("black")),
                                                                 kDefaultRadius(30.0) {
        }

        void GraphView::Draw(const Graph& visualized_graph) {
            ci::gl::clear();
            DrawEdges(visualized_graph);
            DrawNodes(visualized_graph);
        }
        
        void GraphView::MoveNode(Graph* visualized_graph, vec2 new_location) {
            if(LocationOutOfBounds(new_location)){
                return;
            }

            //check every node to see if it is at the location passed in and change its value
            vector<Node> nodes = visualized_graph->GetNodes();
            for(auto & node : nodes) {
                vec2 node_loc = node.GetLocation();
                if (glm::distance(new_location, node_loc) <= kDefaultRadius) {
                    visualized_graph->SetLocation(node, new_location);
                }
            }
        }

        void GraphView::DrawNodes(Graph visualized_graph) {
            vector<Node> nodes = visualized_graph.GetNodes();
            
            //draw a circle a filled in circle at the location of every node
            for (auto & target_node : nodes) {
                vec2 location = target_node.GetLocation();
                ci::gl::color(kDefaultColor);
                ci::gl::drawSolidCircle(location, kDefaultRadius);
                DrawLabel(target_node);
            }
        }
        
        void GraphView::DrawEdges(Graph visualized_graph) {
            vector<Node> nodes = visualized_graph.GetNodes();

            //draw a line from every node to the location of every adjacent node
            for (auto & node : nodes) {
                vec2 location = node.GetLocation();
                vector<const Node *> adjacent_nodes = visualized_graph.GetAdjacentNodes(node);
                for (auto & adjacent_node : adjacent_nodes) {
                    ci::gl::color(ci::Color("blue"));
                    ci::gl::lineWidth(5);
                    ci::gl::drawLine(location, adjacent_node->GetLocation());
                }
            }
        }
        
        void GraphView::DrawLabel(const Node& target_node) {
            vec2 location = target_node.GetLocation();
            location[0] = location[0] - kDefaultRadius / 2;
            location[1] = location[1] - kDefaultRadius / 2;
            ci::gl::drawString(std::to_string(target_node.GetValue()), location, kFontColor,
                               kDefaultFont);
        }

        bool GraphView::LocationOutOfBounds(vec2 loc) const {
            float x = loc[0];
            float y = loc[1];

            return x >= kWindowSize - kMargin || y >= kWindowSize - kMargin || x <= kMargin || y <= kMargin;
        }
    }
}