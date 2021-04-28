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

    // provided that you can see the entire UI on your screen.
    const double kWindowSize = 1000;
    const double kMargin = 100;
    
    const float kDefaultRadius;
    
    const ci::Color kDefaultColor;
    const ci::Color kFontColor;
    const ci::Font kDefaultFont;
private:
    
    GraphView graph_visualizer_;
    GraphEditor graph_editor_;
    Graph visualized_graph;
    
    char app_setting_;
    //Change to enums
    const char kMoveMode = 'M';
    const char kAddNodeMode = 'N';
    const char kDeleteMode = 'D';
    const char kAddEdgeMode = 'E';
    
    void InitializeGraph();
};
}
}

#endif //FINAL_PROJECT_GRAPH_MANIPULATOR_APP_H
