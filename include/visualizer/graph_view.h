#pragma once
#ifndef FINAL_PROJECT_GRAPH_CREATOR_H
#define FINAL_PROJECT_GRAPH_CREATOR_H

#include "core/graph.h"
#include <core/graph.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace graph {
    namespace visualizer {
        class GraphView {
        public:
            /**
             * Initialize the possible range of locations to draw the graph 
             */
            GraphView(double window_size, double margin);
            
            /**
             * Draw all of the nodes and edges of a certain graph
             * @param visualized_graph 
             */
            void Draw(const Graph& visualized_graph);
            
            /**
             * Change the location of a node
             * @param visualized_graph the graph that the node is in 
             * @param new_location the new location of the node
             */
            void MoveNode(Graph* visualized_graph, vec2 new_location);
            
        private:
            const double kWindowSize;
            const double kMargin;
            const float kDefaultRadius;
            const ci::Color kDefaultColor;
            const ci::Color kFontColor;
            const ci::Font kDefaultFont;

            //draw the nodes of a given graph
            void DrawNodes(Graph visualized_graph);

            //draw the edges of a given graph
            void DrawEdges(Graph visualized_graph);
            
            //write the value of the label on the node
            void DrawLabel(const Node& target_node);

            //check if a location is not in the bounds of the GraphView
            bool LocationOutOfBounds(vec2 loc) const;
        };
    }
}
#endif //FINAL_PROJECT_GRAPH_CREATOR_H
