#include "../../include/visualizer/graph_manipulator_app.h"
#include "cinder/Text.h"

namespace graph {
    namespace visualizer {
        GraphVisualizerApp::GraphVisualizerApp() :
                graph_visualizer_(kWindowSize, kMargin),
                kDefaultFont(ci::Font("Times New Roman", 35)),
                kDefaultColor(ci::Color("orange")),
                kFontColor(ci::Color("white")),
                kDefaultRadius(30.0),
                graph_editor_(30.0, kWindowSize, kMargin),
                app_setting_("Move Node") {
            ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
            InitializeGraph();
        }

        void GraphVisualizerApp::draw() {
            graph_visualizer_.Draw(visualized_graph);

            WriteCommandInstructions();
            DisplayCurrentCommand();
            DisplayEdgeEditing();
        }

        void GraphVisualizerApp::mouseDown(ci::app::MouseEvent event) {
            if (app_setting_ == kMoveMode) {
                graph_visualizer_.MoveNode(&visualized_graph, event.getPos());
            } else if (app_setting_ == kAddNodeMode) {
                graph_editor_.CreateNode(&visualized_graph, event.getPos());
            } else if (app_setting_ == kAddEdgeMode) {
                graph_editor_.CreateEdge(&visualized_graph, event.getPos());
            } else if (app_setting_ == kDeleteNodeMode) {
                graph_editor_.DeleteNode(&visualized_graph, event.getPos());
            } else if (app_setting_ == kDeleteEdgeMode) {
                graph_editor_.DeleteEdge(&visualized_graph, event.getPos());
            }
        }

        void GraphVisualizerApp::mouseDrag(ci::app::MouseEvent event) {
            if (app_setting_ == kMoveMode) {
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
                    app_setting_ = kDeleteNodeMode;
                    break;

                case ci::app::KeyEvent::KEY_e:
                    app_setting_ = kAddEdgeMode;
                    graph_editor_.clear();
                    break;
                    
                case ci::app::KeyEvent::KEY_r:
                    app_setting_ = kDeleteEdgeMode;
                    graph_editor_.clear();
                    break;
            }
        }

        void GraphVisualizerApp::InitializeGraph() {
            Node n1(10, vec2(200, 200));
            Node n2(20, vec2(750, 200));
            Node n3(30, vec2(500, 300));
            Node n4(40, vec2(200, 750));
            Node n5(50, vec2(750, 750));
            Node n6(60, vec2(400, 700));
            Node n7(70, vec2(800, 500));

            visualized_graph.AddNode(n1);
            visualized_graph.AddNode(n2);
            visualized_graph.AddNode(n3);
            visualized_graph.AddNode(n4);
            visualized_graph.AddNode(n5);
            visualized_graph.AddNode(n6);
            visualized_graph.AddNode(n7);

            visualized_graph.AddEdge(n1, n2, false);
            visualized_graph.AddEdge(n1, n3, false);
            visualized_graph.AddEdge(n1, n4, false);
            visualized_graph.AddEdge(n1, n6, false);
            visualized_graph.AddEdge(n2, n3, false);
            visualized_graph.AddEdge(n2, n5, false);
            visualized_graph.AddEdge(n2, n7, false);
            visualized_graph.AddEdge(n2, n6, false);
            visualized_graph.AddEdge(n3, n4, false);
            visualized_graph.AddEdge(n3, n5, false);
            visualized_graph.AddEdge(n6, n7, false);
        }

        void GraphVisualizerApp::WriteCommandInstructions() const {
            std::string instructions;
            instructions += "M: " + kMoveMode + "\n";
            instructions += "N: " + kAddNodeMode + "\n";
            instructions += "D: " + kDeleteNodeMode;
            ci::gl::drawStringCentered(instructions, vec2(400, 900), kFontColor,
                                       kDefaultFont);

            std::string add_instructions;
            add_instructions += "E: " + kAddEdgeMode+ "\n";
            add_instructions += "R: " + kDeleteEdgeMode;
            ci::gl::drawStringCentered(add_instructions, vec2(600, 900), kFontColor,
                                       kDefaultFont);
        }

        void GraphVisualizerApp::DisplayCurrentCommand() const {
            ci::gl::color(ci::Color("white"));
            ci::gl::drawStrokedRect(ci::Rectf(vec2(1, 1), vec2(220, 90)));
            ci::gl::drawStringCentered("Current Command:", vec2(110, 10), kFontColor,
                                       kDefaultFont);
            ci::gl::drawStringCentered(app_setting_, vec2(110, 45), ci::Color("Red"),
                                       kDefaultFont);
        }

        void GraphVisualizerApp::DisplayEdgeEditing() const {
            if (app_setting_ != kAddEdgeMode && app_setting_ != kDeleteEdgeMode) {
                return;
            }

            ci::gl::color(ci::Color("white"));
            ci::gl::drawStrokedRect(ci::Rectf(vec2(kWindowSize - 270, 1), vec2(kWindowSize - 1, 90)));
            ci::gl::drawStringCentered("Current Node Selected:", vec2(kWindowSize - 140, 10), kFontColor,
                                       kDefaultFont);
            ci::gl::drawStringCentered(graph_editor_.GetVectorValues(), vec2(kWindowSize - 135, 40), ci::Color("red"),
                                       kDefaultFont);
        }
    }
}