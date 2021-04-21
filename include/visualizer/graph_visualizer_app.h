#pragma once
#ifndef FINAL_PROJECT_GRAPH_VISUALIZER_APP_H
#define FINAL_PROJECT_GRAPH_VISUALIZER_APP_H

#include <core/graph.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace graph {
    
namespace visualizer {

class GraphVisualizerApp : public ci::app::App {
public:
    
    GraphVisualizerApp();
    
    GraphVisualizerApp(Graph to_visualize);
    
    void UpdateGraph(Graph to_visualize);

    void draw() override;

    // provided that you can see the entire UI on your screen.
    const double kWindowSize = 1000;
    const double kMargin = 100;
    const float kDefaultRadius;
    
    const ci::Color kDefaultColor;
    const ci::Color kFontColor;
    const ci::Font kDefaultFont;
    
    vector<Node> visualized_nodes_;
};
}
}

#endif //FINAL_PROJECT_GRAPH_VISUALIZER_APP_H
