#include <iostream>
#include <fstream>
#include "stdafx.h"
#include "Snap.h"
typedef PNGraph PGraph;

void graphMl(PNGraph Graph){
        std::ofstream graphml;
        graphml.open("graph.graphml");

        graphml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        graphml << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"\n";
        graphml << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
        graphml << "    xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns\n";
        graphml << "     http://graphml.graphdrawing.org/xmlns/1.1/graphml.xsd\">\n";
        graphml << "  <graph id=\"G\" edgedefault=\"directed\">\n";

        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++)
                graphml << "    <node id=\"" << NI.GetId() << "\"/>\n";
        int i = 1;
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++) {
                graphml << "    <edge id=\"e" << i++ << "\" directed=\"true"
                        << "\" source=\""     << EI.GetSrcNId()
                        << "\" target=\""     << EI.GetDstNId() << "\"/>\n";
        }
        graphml << "  </graph>\n";
        graphml << "</graphml>\n";
        graphml.close();
}



void gexf(PNGraph Graph){
        std::ofstream graph;
        graph.open("graph.gexf");
        graph << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
              << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n"
              << "  <graph mode=\"static\" defaultedgetype=\"directed\">\n"
              << "    <nodes>\n";
        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++)
                graph << "      <node id=\"" << NI.GetId() << "\"/>\n";

        graph << "    </nodes>\n";
        graph << "    <edges>\n";
        int i = 1;
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++)
                graph << "      <edge id=\"e" << i++
                      << "\" directed=\"true" << "\" source=\""
                      << EI.GetSrcNId()       << "\" target=\""
                      << EI.GetDstNId()      << "\"/>\n";

        graph << "    </edges>\n"
              << "  </graph>\n"
              << "</gexf>\n";
        graph.close();
}


void gdf(PNGraph Graph){
        std::ofstream graph;
        graph.open("graph.gdf");
        graph << "nodedef>name VARCHAR\n";

        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++)
                graph << NI.GetId() << ",\n";
        graph << "edgedef>node1 VARCHAR,node2 VARCHAR\n";
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++)
                graph << EI.GetSrcNId() << "," << EI.GetDstNId() << "\n";
        graph.close();
}


void graphson(PNGraph Graph){
        std::ofstream graph;
        graph.open("graph.json");
        graph << "{\n";
        graph << "    \"graph\": {\n";
        graph << "        " << "\"mode\": \"NORMAL\", \n";
        graph << "        " << "\"vertices\": [\n";
        int i = 0;
        for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
                i++;
                graph << "            " << "{\n";
                graph << "                " << "\"_id\": \"" << NI.GetId() << "\",\n";
                graph << "                " << "\"_type\": \"vertex\"\n";
                if (i == Graph->GetNodes()) {
                        graph << "            " << "}\n";
                } else {
                        graph << "            " << "},\n";
                }
        }


        graph << "        " << "],\n";
        graph << "        " << "\"edges\": [\n";

        i = 0;
        printf("Edges: %d", Graph->GetEdges());
        for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++) {
                graph << "            " << "{\n"
                      << "                " << "\"_id\": \"" << i++ << "\",\n"
                      << "                " << "\"_type\": \"edge\"\n"
                      << "                " << "\"_outV\": \"" << EI.GetSrcNId() << "\"\n"
                      << "                " << "\"_inV\": \""<< EI.GetDstNId() << "\"\n";

                if (i == Graph->GetEdges())
                        graph << "            " << "}\n";
                else
                        graph << "            " << "},\n";

        }
        graph << "        " << "]\n";
        graph << "    " << "}\n";
        graph << "}\n";

        graph.close();
}


int main(int argc, char* argv[]) {
        PGraph Graph = TSnap::LoadEdgeList<PNGraph>("facebook_combined.txt",0,1);

        graphMl(Graph);
        gexf(Graph);
        gdf(Graph);
        graphson(Graph);
        IAssert(Graph->IsOk());
        return 0;
}
