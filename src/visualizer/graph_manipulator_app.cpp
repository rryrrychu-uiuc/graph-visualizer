#include "../../include/visualizer/graph_manipulator_app.h"

namespace graph {
    namespace visualizer {
        GraphVisualizerApp::GraphVisualizerApp():
                graph_visualizer_(kWindowSize, kMargin),
                kDefaultFont(ci::Font("Times New Roman", 45)),
                kDefaultColor(ci::Color("orange")),
                kFontColor(ci::Color("black")),
                kDefaultRadius(30.0) {
            ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
            InitializeGraph();
            //TODO: Change this to initalize GraphView
            //TODO: Instance varaibles shoudl be GraphView, GraphEditor, Graph
        }
        
        void GraphVisualizerApp::draw() {
            graph_visualizer_.Draw(visualized_graph);
        }
        
        void GraphVisualizerApp::mouseDown(ci::app::MouseEvent event) {
           graph_visualizer_.MoveNode(&visualized_graph, event.getPos());
        }

        void GraphVisualizerApp::mouseDrag(ci::app::MouseEvent event) {
            graph_visualizer_.MoveNode(&visualized_graph, event.getPos());
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