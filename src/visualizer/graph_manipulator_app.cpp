#include "../../include/visualizer/graph_manipulator_app.h"

namespace graph {
    namespace visualizer {
        GraphVisualizerApp::GraphVisualizerApp():
                graph_visualizer_(kWindowSize, kMargin),
                kDefaultFont(ci::Font("Times New Roman", 45)),
                kDefaultColor(ci::Color("orange")),
                kFontColor(ci::Color("white")),
                kDefaultRadius(30.0),
                graph_editor_(kDefaultRadius),
                app_setting_(kMoveMode){
            ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
            InitializeGraph();
        }
        
        void GraphVisualizerApp::draw() {
            graph_visualizer_.Draw(visualized_graph);
            ci::gl::drawString(std::to_string(app_setting_), vec2(500, 50), kFontColor,
                               kDefaultFont);
        }
        
        void GraphVisualizerApp::mouseDown(ci::app::MouseEvent event) {
            if(app_setting_ == kMoveMode){
                graph_visualizer_.MoveNode(&visualized_graph, event.getPos());
            } else if (app_setting_ == kAddNodeMode) {
                graph_editor_.CreateNode(&visualized_graph, event.getPos());
            } else if (app_setting_ == kAddEdgeMode) {
                graph_editor_.CreateEdge(&visualized_graph, event.getPos());
            }
        }

        void GraphVisualizerApp::mouseDrag(ci::app::MouseEvent event) {
            if(app_setting_ == kMoveMode){
                graph_visualizer_.MoveNode(&visualized_graph, event.getPos());
            }
        }
        
        void GraphVisualizerApp::keyDown(ci::app::KeyEvent event) {

            switch (event.getCode()) {
                case ci::app::KeyEvent::KEY_m:
                    app_setting_ = kMoveMode;
                    break;

                case ci::app::KeyEvent::KEY_n:
                    app_setting_ = kAddNodeMode;
                    break;
                    
                case ci::app::KeyEvent::KEY_d:
                    app_setting_ = kDeleteMode;
                    break;

                case ci::app::KeyEvent::KEY_e:
                    app_setting_ = kAddEdgeMode;
                    break;
            }
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

            visualized_graph.AddEdge(&n1, &n2, false);
            visualized_graph.AddEdge(&n1, &n3, false);
            visualized_graph.AddEdge(&n1, &n4, false);
            visualized_graph.AddEdge(&n1, &n6, false);
            visualized_graph.AddEdge(&n2, &n3, false);
            visualized_graph.AddEdge(&n2, &n5, false);
            visualized_graph.AddEdge(&n2, &n7, false);
            visualized_graph.AddEdge(&n2, &n6, false);
            visualized_graph.AddEdge(&n3, &n4, false);
            visualized_graph.AddEdge(&n3, &n5, false);
            visualized_graph.AddEdge(&n6, &n7, false);
        }
    }
}