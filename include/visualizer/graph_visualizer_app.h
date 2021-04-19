#pragma once
#ifndef FINAL_PROJECT_GRAPH_VISUALIZER_APP_H
#define FINAL_PROJECT_GRAPH_VISUALIZER_APP_H

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

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
    const size_t kImageDimension = 28;
};
}
}

#endif //FINAL_PROJECT_GRAPH_VISUALIZER_APP_H
