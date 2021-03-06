#include <visualizer/graph_manipulator_app.h>

using graph::visualizer::GraphVisualizerApp;

void prepareSettings(GraphVisualizerApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(GraphVisualizerApp, ci::app::RendererGl, prepareSettings);