#include "../../include/visualizer/graph_manipulator_app.h"
#include "cinder/Text.h"

namespace graph {
    namespace visualizer {
        GraphVisualizerApp::GraphVisualizerApp() :
                kDefaultFont(ci::Font("Times New Roman", 35)),
                kDefaultColor(ci::Color("orange")),
                kFontColor(ci::Color("white")),
                kDefaultRadius(30.0),
                graph_visualizer_(kWindowSize, kMargin),
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
            } else if(app_setting_ == kShortestPath) {
                graph_editor_.MarkNode(&visualized_graph, event.getPos());
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
                    if(app_setting_ != kInAlgorithmProcess) {
                        graph_visualizer_.ResetColors(&visualized_graph);
                        app_setting_ = kMoveMode;
                    }
                    break;

                case ci::app::KeyEvent::KEY_n:
                    if(app_setting_ != kInAlgorithmProcess) {
                        graph_visualizer_.ResetColors(&visualized_graph);
                        app_setting_ = kAddNodeMode;
                    }
                    break;

                case ci::app::KeyEvent::KEY_d:
                    if(app_setting_ != kInAlgorithmProcess) {
                        graph_visualizer_.ResetColors(&visualized_graph);
                        app_setting_ = kDeleteNodeMode;
                    }
                    break;

                case ci::app::KeyEvent::KEY_e:
                    if(app_setting_ != kInAlgorithmProcess) {
                        graph_visualizer_.ResetColors(&visualized_graph);
                        app_setting_ = kAddEdgeMode;
                        graph_editor_.clear();
                    }
                    break;
                    
                case ci::app::KeyEvent::KEY_r:
                    if(app_setting_ != kInAlgorithmProcess) {
                        graph_visualizer_.ResetColors(&visualized_graph);
                        app_setting_ = kDeleteEdgeMode;
                        graph_editor_.clear();
                    }
                    break;

                case ci::app::KeyEvent::KEY_s:
                    if(app_setting_ != kInAlgorithmProcess) {
                        graph_visualizer_.ResetColors(&visualized_graph);
                        app_setting_ = kShortestPath;
                        graph_editor_.clear();
                    }
                    break;
                    
                case ci::app::KeyEvent::KEY_RETURN:
                    if(app_setting_ == kShortestPath && graph_editor_.size() == 2) {
                        app_setting_ = kInAlgorithmProcess;
                        vector<Node> path_from = graph_editor_.GetNodes();
                        path_finder_.InitalizeValues(&visualized_graph, path_from[0], path_from[1]);
                        graph_editor_.clear();
                        graph_visualizer_.ResetColors(&visualized_graph);
                    }
                    break;
                    
                //show one step of shortest path algorithm    
                case ci::app::KeyEvent::KEY_PERIOD:
                    if(app_setting_ == kInAlgorithmProcess) {
                        bool finished_running = path_finder_.RunSingleStepDijkstra();
                        if(finished_running) {
                            path_finder_.ColorShortestPath();
                        }
                    }
                    break;

                //show one step of shortest path algorithm    
                case ci::app::KeyEvent::KEY_w:
                    if(app_setting_ == kInAlgorithmProcess) {
                        path_finder_.RunEntireAlgorithm();
                        path_finder_.ColorShortestPath();
                    }
                    break;
                
                //end shortest path algorithm running    
                case ci::app::KeyEvent::KEY_ESCAPE:
                    if(app_setting_ == kInAlgorithmProcess) {
                        graph_visualizer_.ResetColors(&visualized_graph);
                        app_setting_ = kMoveMode;
                    }
                    break;
            }
        }

        void GraphVisualizerApp::InitializeGraph() {
            Node test_node1(10, vec2(200,200));
            Node test_node2(20, vec2(400,200));
            Node test_node3(30, vec2(600, 300));
            Node test_node4(40, vec2(200, 400));
            Node test_node5(50, vec2(400, 400));

            visualized_graph.AddNode(test_node1);
            visualized_graph.AddNode(test_node2);
            visualized_graph.AddNode(test_node3);
            visualized_graph.AddNode(test_node4);
            visualized_graph.AddNode(test_node5);

            visualized_graph.AddEdge(test_node1, test_node2, ci::Color("blue"), 6, false);
            visualized_graph.AddEdge(test_node1, test_node4, ci::Color("blue"), 1, false);
            visualized_graph.AddEdge(test_node2, test_node3, ci::Color("blue"), 5, false);
            visualized_graph.AddEdge(test_node2, test_node4, ci::Color("blue"), 2, false);
            visualized_graph.AddEdge(test_node2, test_node5, ci::Color("blue"), 2, false);
            visualized_graph.AddEdge(test_node5, test_node3, ci::Color("blue"), 5, false);
            visualized_graph.AddEdge(test_node5, test_node4, ci::Color("blue"), 1, false);
        }

        void GraphVisualizerApp::WriteCommandInstructions() const {
            if(app_setting_ == kShortestPath) {
                std::string instructions;
                instructions += "Press Enter When Two Nodes Selected";
                ci::gl::drawStringCentered(instructions, vec2(500, 900), kFontColor,
                                           kDefaultFont);
                
            } else if(app_setting_ != kInAlgorithmProcess) {
                std::string instructions;
                instructions += "M: " + kMoveMode + "\n";
                instructions += "N: " + kAddNodeMode + "\n";
                instructions += "D: " + kDeleteNodeMode;
                ci::gl::drawStringCentered(instructions, vec2(400, 900), kFontColor,
                                           kDefaultFont);

                std::string add_instructions;
                add_instructions += "E: " + kAddEdgeMode+ "\n";
                add_instructions += "R: " + kDeleteEdgeMode + "\n";
                add_instructions += "S: " + kShortestPath;
                ci::gl::drawStringCentered(add_instructions, vec2(600, 900), kFontColor,
                                           kDefaultFont);
            } else {
                std::string instructions;
                instructions += ">: " + kInAlgorithmProcess + "\n";
                instructions += "W: " + kRunWholeAlgorithm + "\n";
                instructions += "Esc: " + kStopAlgorithmRunning;
                ci::gl::drawStringCentered(instructions, vec2(400, 900), kFontColor,
                                           kDefaultFont);
            }
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
            if (app_setting_ != kAddEdgeMode && app_setting_ != kDeleteEdgeMode && app_setting_ != kShortestPath) {
                return;
            }

            ci::gl::color(ci::Color("white"));
            ci::gl::drawStrokedRect(ci::Rectf(vec2(kWindowSize - 270, 1), vec2(kWindowSize - 1, 90)));
            ci::gl::drawStringCentered("Current Node Selected:", vec2(kWindowSize - 140, 10), kFontColor,
                                       kDefaultFont);
            ci::gl::drawStringCentered(graph_editor_.GetVectorValues(), vec2(kWindowSize - 135, 40), ci::Color("red"),
                                       kDefaultFont);
        }

        void GraphVisualizerApp::ResetColors() {
            for(auto& node: visualized_graph.GetNodes()) {
                visualized_graph.SetNodeColor(node, ci::Color("orange"));
                for(auto& target_edge: visualized_graph.GetAdjacentNodes(node)) {
                    visualized_graph.SetEdgeColor(node, *target_edge.GetEndNode(), ci::Color("blue"));
                }
            }
        }
    }
}