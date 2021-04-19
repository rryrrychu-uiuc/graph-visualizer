#include <visualizer/graph_visualizer_app.h>

using graph::visualizer::GraphVisualizerApp;

void prepareSettings(NaiveBayesApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(GraphVisualizerApp, ci::app::RendererGl, prepareSettings);