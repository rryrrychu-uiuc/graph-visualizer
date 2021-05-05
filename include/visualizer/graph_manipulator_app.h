#pragma once
#ifndef FINAL_PROJECT_GRAPH_MANIPULATOR_APP_H
#define FINAL_PROJECT_GRAPH_MANIPULATOR_APP_H

#include <core/graph.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "graph_view.h"
#include "graph_editor.h"
#include "shortest_path_algorithms.h"

namespace graph {

    namespace visualizer {

        class GraphVisualizerApp : public ci::app::App {
        public:
            GraphVisualizerApp();

            void draw() override;

            void mouseDown(ci::app::MouseEvent event) override;

            void mouseDrag(ci::app::MouseEvent event) override;

            void keyDown(ci::app::KeyEvent event) override;
            
        private:
            const double kWindowSize = 1000;
            const double kMargin = 150;
            
            const float kDefaultRadius;
            const ci::Color kDefaultColor;
            const ci::Color kFontColor;
            const ci::Font kDefaultFont;

            const std::string kMoveMode = "Move Node";
            const std::string kAddNodeMode = "Add Node";
            const std::string kAddEdgeMode = "Add Edge";
            const std::string kDeleteNodeMode = "Delete Node";
            const std::string kDeleteEdgeMode = "Delete Edge";
            const std::string kShortestPath = "Choose Nodes";
            const std::string kInAlgorithmProcess = "Increment Algorithm";
            const std::string kRunWholeAlgorithm = "Run Entire Algorithm";
            const std::string kStopAlgorithmRunning = "Stop Running Algorithm";
            
            std::string app_setting_;

            GraphView graph_visualizer_;
            GraphEditor graph_editor_;
            ShortestPath path_finder_;
            Graph visualized_graph;

            //create a graph
            void InitializeGraph();

            //show what each command does
            void WriteCommandInstructions() const;

            //show which command is selected
            void DisplayCurrentCommand() const;
            
            //show which edges are selected
            void DisplayEdgeEditing() const;
            
            //get normal colors for the graph
            void ResetColors();
        };
    }
}

#endif //FINAL_PROJECT_GRAPH_MANIPULATOR_APP_H
