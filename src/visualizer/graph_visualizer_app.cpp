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
            InitializeGraph();
        }

        void GraphVisualizerApp::InitializeGraph() {
            Node n1(10, vec2(200,200));
            Node n2(20, vec2(750,200));
            Node n3(30, vec2(500,300));
            Node n4(40, vec2(200,750));
            Node n5(50, vec2(750,750));
            Node n6(60, vec2(400,700));
            Node n7(70, vec2(800,500));
            
            visualized_graph.AddNode(n1);
            visualized_graph.AddNode(n2);
            visualized_graph.AddNode(n3);
            visualized_graph.AddNode(n4);
            visualized_graph.AddNode(n5);
            visualized_graph.AddNode(n6);
            visualized_graph.AddNode(n7);
            
            visualized_graph.AddEdge(0, 1, false);
            visualized_graph.AddEdge(0, 2, false);
            visualized_graph.AddEdge(0, 3, false);
            visualized_graph.AddEdge(0, 5, false);
            visualized_graph.AddEdge(1, 2, false);
            visualized_graph.AddEdge(1, 4, false);
            visualized_graph.AddEdge(1, 6, false);
            visualized_graph.AddEdge(1, 4, false);
            visualized_graph.AddEdge(1, 5, false);
            visualized_graph.AddEdge(2, 3, false);
            visualized_graph.AddEdge(2, 4, false);
            visualized_graph.AddEdge(5, 6, false);
        }
        
        void GraphVisualizerApp::draw() {
            ci::gl::clear();
            DrawEdges();
            DrawNodes();
        }
        
        void GraphVisualizerApp::DrawEdges() {
            vector<Node> nodes = visualized_graph.GetNodes();
            
            for (size_t index = 0; index < nodes.size(); index++) {

                vec2 location = nodes[index].GetLocation();
                vector<Node*> adjacent_nodes = nodes[index].GetAdjacentNodes();
                for(size_t nodes = 0; nodes < adjacent_nodes.size(); nodes++) {
                    ci::gl::color(ci::Color("blue"));
                    ci::gl::lineWidth(5);
                    ci::gl::drawLine(location, adjacent_nodes[nodes]->GetLocation());
                }
            }
        }

        void GraphVisualizerApp::DrawNodes() {
            vector<Node> nodes = visualized_graph.GetNodes();
            for (size_t index = 0; index < nodes.size(); index++) {

                vec2 location = nodes[index].GetLocation();
                
                ci::gl::color(kDefaultColor);
                ci::gl::drawSolidCircle(location, kDefaultRadius);
                location[0] = location[0] - kDefaultRadius/2;
                location[1] = location[1] - kDefaultRadius/2;
                ci::gl::drawString(std::to_string(nodes[index].GetValue()), location, kFontColor,
                                   kDefaultFont);
            }
        }

        void GraphVisualizerApp::mouseDown(ci::app::MouseEvent event) {
            vector<Node> nodes = visualized_graph.GetNodes();
            vec2 mouse_loc = event.getPos();
            
            if(LocationOutOfBounds(mouse_loc)){
                return;
            }
            
            for(size_t index = 0; index < nodes.size(); index++) {
                vec2 node_loc = nodes[index].GetLocation();
                if (glm::distance(mouse_loc, node_loc) <= kDefaultRadius) {
                    visualized_graph.SetLocation(index, mouse_loc);
                }

            }
        }

        void GraphVisualizerApp::mouseDrag(ci::app::MouseEvent event) {
            vector<Node> nodes = visualized_graph.GetNodes();
            vec2 mouse_loc = event.getPos();

            if(LocationOutOfBounds(mouse_loc)){
                return;
            }
            
            for(size_t index = 0; index < nodes.size(); index++) {

                vec2 node_loc = nodes[index].GetLocation();
                if (glm::distance(mouse_loc, node_loc) <= kDefaultRadius) {
                    visualized_graph.SetLocation(index, mouse_loc);
                }

            }
        }
        
        bool GraphVisualizerApp::LocationOutOfBounds(vec2 loc) {
            
            float x = loc[0];
            float y = loc[1];
            
            return x >= kWindowSize || y >= kWindowSize || x <= 0 || y <= 0;
        }

    }
}