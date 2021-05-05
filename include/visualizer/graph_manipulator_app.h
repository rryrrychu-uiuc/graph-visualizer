#pragma once
#ifndef FINAL_PROJECT_GRAPH_MANIPULATOR_APP_H
#define FINAL_PROJECT_GRAPH_MANIPULATOR_APP_H

#include <core/graph.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "graph_view.h"
#include "graph_editor.h"

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
            const std::string kShortestPath = "Find Shortest Path";
            
            std::string app_setting_;

            GraphView graph_visualizer_;
            GraphEditor graph_editor_;
            Graph visualized_graph;

            void InitializeGraph();

            void WriteCommandInstructions() const;

            void DisplayCurrentCommand() const;
            
            void DisplayEdgeEditing() const;
        };
    }
}

#endif //FINAL_PROJECT_GRAPH_MANIPULATOR_APP_H
